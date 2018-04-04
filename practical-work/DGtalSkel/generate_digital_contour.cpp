#include <DGtal/helpers/StdDefs.h>

#include "DGtal/shapes/ShapeFactory.h"
#include "DGtal/shapes/GaussDigitizer.h"

#include <DGtal/topology/DigitalSurface.h>
#include <DGtal/topology/DigitalSetBoundary.h>
#include <DGtal/topology/CanonicCellEmbedder.h>
#include <DGtal/topology/CanonicSCellEmbedder.h>

#include <DGtal/shapes/Shapes.h>

#include <DGtal/io/boards/Board2D.h>
#include <DGtal/io/colormaps/GradientColorMap.h>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/errors.hpp>

#include <stack>

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
  bool contour_points;
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
    ("contour-points,c", po::value<bool>(&options.contour_points)->default_value(true), "true: only contour points, false: all points")
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
void generate_points( Options& options, TShape shape, std::vector<DGtal::Z2i::Space::Point>& v )
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
  typedef KSpace::Cell Cell;
  typedef SurfelAdjacency<Space::dimension> SurfelAdjacency;

  trace.beginBlock("Extracting Contour Points");

  trace.info() << "h=" << options.h << std::endl;

  Digitizer digitizer;
  digitizer.attach( shape );
  digitizer.init( shape.getLowerBound() + RealVector(-1,-1), shape.getUpperBound() + RealVector(1,1), options.h );

  Domain domain = digitizer.getDomain();

  if( options.contour_points )
  {
    KSpace kspace;
    bool ok = kspace.init(domain.lowerBound(), domain.upperBound(), true);
    if( !ok ) trace.error() << "KSpace init failed" << std::endl;

    SurfelAdjacency SAdj(true);
    typename KSpace::Surfel bel = Surfaces<KSpace>::findABel(kspace, digitizer, 100000);

    typedef CanonicSCellEmbedder<KSpace> CanonicSCellEmbedder;
    CanonicSCellEmbedder canonicSCellEmbedder( kspace );

    std::vector<SCell> sCells1;
    Surfaces<KSpace>::track2DBoundary(sCells1, kspace, SAdj, digitizer, bel);

    for( int i = 0; i < sCells1.size(); i++ )
    {
      const auto sCells = kspace.sUpperIncident( sCells1[i] );
      for( auto const& s : sCells )
        if( digitizer( canonicSCellEmbedder( s ) ) ) v.push_back( canonicSCellEmbedder( s ) );
    }
  }
  else
    for( auto const& p : domain )
      if( digitizer( p ) ) v.push_back( p );

  trace.endBlock();
}

int main( int argc, char** argv )
{
  Options options = parse_options( argc, argv );

  using namespace DGtal;

  typedef Z2i::Space::Point Point;

  trace.beginBlock("Convex Hull");

  std::vector<Point> points;

  if( options.shape_type == BALL )       generate_points( options,
          DGtal::Ball2D< DGtal::Z2i::Space >( DGtal::Z2i::Point(0., 0.), 1. ),
          points );
  if( options.shape_type == FLOWER )     generate_points( options,
          DGtal::Flower2D< DGtal::Z2i::Space >( DGtal::Z2i::Point(0., 0.), 1., 0.3, 5, 0. ),
          points );
  if( options.shape_type == ACC_FLOWER ) generate_points( options,
          DGtal::AccFlower2D< DGtal::Z2i::Space >( DGtal::Z2i::Point(0., 0.), 1., 0.3, 5, 0. ),
          points );

  trace.info() << "Extracted " << points.size() << " points." << std::endl;

  //TODO

  trace.endBlock();
}
