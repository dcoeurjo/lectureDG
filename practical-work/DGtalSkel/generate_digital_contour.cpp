#include <DGtal/helpers/StdDefs.h>

#include "DGtal/shapes/ShapeFactory.h"
#include "DGtal/shapes/GaussDigitizer.h"

#include <DGtal/topology/DigitalSurface.h>
#include <DGtal/topology/DigitalSetBoundary.h>

#include <DGtal/shapes/Shapes.h>

#include <DGtal/io/boards/Board2D.h>
#include <DGtal/io/colormaps/GradientColorMap.h>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/errors.hpp>

enum SHAPE_TYPE
{
  BALL,
  FLOWER,
  ACC_FLOWER
};

std::istream& operator>>( std::istream& is, SHAPE_TYPE& shape_type )
{
  namespace po = boost::program_options;

  std::string token;
  is >> token;
  if( token == "ball" ) { shape_type = BALL; return is; }
  if( token == "flower" ) { shape_type = FLOWER; return is; }
  if( token == "accFlower" ) { shape_type = ACC_FLOWER; return is; }

  throw po::validation_error( po::validation_error::invalid_option_value );
  return is;
}

std::ostream& operator<<( std::ostream& os, SHAPE_TYPE& shape_type )
{
  switch( shape_type )
  {
    case BALL:
      os << "ball";
      break;
    case FLOWER:
      os << "flower";
      break;
    case ACC_FLOWER:
      os << "accFlower";
      break;
  }

  return os;
}

struct Options
{
  SHAPE_TYPE shape_type;
  double h;
};

Options
parse_options(int argc, char* argv[])
{
  namespace po = boost::program_options;

  using DGtal::trace;
  using std::endl;

  Options options;

  po::options_description po_options("contour extraction [options]");
  po_options.add_options()
    ("shape-type,t", po::value<SHAPE_TYPE>(&options.shape_type)->default_value(BALL), "ball, flower or accFlower")
    ("grid-step,s", po::value<double>(&options.h)->default_value(0.1), "grid step")
    ("help,h", "display this message")
    ;

  try
  {
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(po_options).run(), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
      trace.info() << po_options;
      std::exit(0);
    }
  }
  catch (std::exception& ex)
  {
    trace.error() << ex.what() << endl;
    trace.info() << po_options;
    std::exit(1);
  }

  return options;
}

template <typename TShape>
void compute( Options& options, TShape shape )
{
  using namespace DGtal;

  typedef Z2i::Space Space;
  typedef Space::RealVector RealVector;
  typedef Space::Point Point;
  typedef Space::RealPoint RealPoint;
  typedef GaussDigitizer<Space, TShape> Digitizer;
  typedef typename Digitizer::Domain Domain;
  typedef KhalimskySpaceND<Space::dimension, int> KSpace;
  typedef KSpace::SCell SCell;
  typedef SurfelAdjacency<Space::dimension> SurfelAdjacency;

  trace.beginBlock("Computing");

  trace.beginBlock("Digitizing the shape");

  trace.info() << "h=" << options.h << std::endl;

  Digitizer digitizer;
  digitizer.attach( shape );
  digitizer.init( shape.getLowerBound() + RealVector(-1,-1), shape.getUpperBound() + RealVector(1,1), options.h );

  Domain domain = digitizer.getDomain();

  KSpace kspace;
  bool ok = kspace.init(domain.lowerBound(), domain.upperBound(), true);
  if( !ok ) trace.error() << "KSpace init failed" << std::endl;

  SurfelAdjacency SAdj(true);
  typename KSpace::Surfel bel = Surfaces<KSpace>::findABel(kspace, digitizer, 100000);

  typedef CanonicSCellEmbedder<KSpace> CanonicSCellEmbedder;
  CanonicSCellEmbedder canonicSCellEmbedder( kspace );

  std::vector<SCell> sCells0, sCells1;
  Surfaces<KSpace>::track2DBoundary(sCells1, kspace, SAdj, digitizer, bel);
  {
    typedef std::vector<Point> Points;
    Points points;
    Surfaces<KSpace>::track2DBoundaryPoints(points, kspace, SAdj, digitizer, bel);
    const SCell point_ref = kspace.sCell(Point(0,0));
    for(auto pi = points.begin(), pe = points.end(); pi != pe; ++pi) sCells0.push_back(kspace.sCell(*pi, point_ref));
  }

  trace.info() << "Shape has " << sCells0.size() << " pointels and " << sCells1.size() << " surfels." << std::endl;

  trace.endBlock();

  trace.beginBlock("Computing the real curvature");

  //Given any points in R² projects it onto the smooth contour
  const auto projection_function = [&]( const int& i )
  {
    functors::SCellToInnerPoint<KSpace> sCellToInnerPoint( kspace );
    functors::SCellToOuterPoint<KSpace> sCellToOuterPoint( kspace );

    const int prev = (i + sCells1.size() - 6) % sCells1.size(), next = (i + 6) % sCells1.size();

    RealPoint inner_prev = sCellToInnerPoint( sCells1[ prev ] );
    RealPoint inner_next = sCellToInnerPoint( sCells1[ next ] );

    RealPoint outer_prev = sCellToOuterPoint( sCells1[ prev ] );
    RealPoint outer_next = sCellToOuterPoint( sCells1[ next ] );

    inner_prev *= options.h;
    inner_next *= options.h;

    outer_prev *= options.h;
    outer_next *= options.h;

    RealPoint q_prev = shape.findIntersection( inner_prev, outer_prev, options.h * 0.008 );
    RealPoint q_next = shape.findIntersection( inner_next, outer_next, options.h * 0.008 );
    return shape.closestPointWithWitnesses( options.h * canonicSCellEmbedder( sCells1[i] ), q_prev, q_next, 400 );
  };

  std::vector<double> curvature_vector;
  curvature_vector.reserve( sCells1.size() );

  for( int i = 0; i < sCells1.size(); ++i )
  {
    //Computing the closest point on the surface
    const RealPoint p = projection_function( i );

    //Retrieving the shape parameter from p
    const double t = shape.parameter( p );

    //Computing the real curvature
    const double curvature = shape.curvature( t );

    //storing it
    curvature_vector.push_back( curvature );
  }

  const auto min_max = std::minmax_element( curvature_vector.begin(), curvature_vector.end() );

  trace.info() << "Curvature (min/max): " << *min_max.first << " " << *min_max.second << std::endl;

  trace.endBlock();

  trace.beginBlock("Shape output");

  typedef DGtal::GradientColorMap<double> Gradient;
  Gradient color( *min_max.first, *min_max.second );
  color.addColor( DGtal::Color( 50, 50, 255 ) );
  color.addColor( DGtal::Color( 255, 0, 0 ) );
  color.addColor( DGtal::Color( 255, 255, 10 ) );

  Board2D board;
  board.backgroundColor( Color::White );
  board << domain;

  for( int i = 0; i < sCells1.size(); ++i )
  {
    board << CustomStyle( sCells1[i].className(), new CustomColors( color( curvature_vector[i] ), color( curvature_vector[i] ) ) );
    board << sCells1[i];
  }

  for( int i = 0; i < sCells0.size(); ++i )
  {
    board << CustomStyle( sCells0[i].className(), new CustomColors( Color::Black, Color::Black ) );
    board << sCells0[i];
  }

  board.saveSVG( "curvature.svg" );

  trace.endBlock();

  trace.endBlock();
}

int main( int argc, char** argv )
{
  Options options = parse_options( argc, argv );

  if( options.shape_type == BALL )       compute( options, DGtal::Ball2D< DGtal::Z2i::Space >( DGtal::Z2i::Point(0., 0.), 1. ) );
  if( options.shape_type == FLOWER )     compute( options, DGtal::Flower2D< DGtal::Z2i::Space >( DGtal::Z2i::Point(0., 0.), 1., 0.3, 5, 0. ) );
  if( options.shape_type == ACC_FLOWER ) compute( options, DGtal::AccFlower2D< DGtal::Z2i::Space >( DGtal::Z2i::Point(0., 0.), 1., 0.3, 5, 0. ) );
}
