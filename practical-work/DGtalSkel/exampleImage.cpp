#include <DGtal/base/Common.h>

#include <DGtal/io/readers/GenericReader.h>
#include <DGtal/io/writers/GenericWriter.h>
#include <DGtal/io/writers/MagickWriter.h>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/errors.hpp>

struct Options
{
  std::string filename;
};

Options
parse_options(int argc, char* argv[])
{
  namespace po = boost::program_options;

  using DGtal::trace;
  using std::endl;

  Options options;

  po::options_description po_options("mesh_laplacian_3D [options]");
  po_options.add_options()
    ("filename,i", po::value<std::string>(&options.filename)->default_value("church.pgm"), "filename of the image")
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

int main(int argc, char** argv)
{
  using namespace DGtal;

  trace.beginBlock("Simple Image Reader Example");
  Options options = parse_options( argc, argv );

  typedef ImageContainerBySTLMap<DGtal::Z2i::Domain, unsigned char> Image;

  trace.info() << "Input Image: " << options.filename << std::endl;

  //Importing the image into DGtal container
  Image image = DGtal::GenericReader<Image>::import(options.filename);

  //Modifying the image
  image.setValue( Z2i::Domain::Point( 10, 10 ), 21 );

  //Writting the image
  GenericWriter<Image>::exportFile( "modified.pgm", image );

  //We create a color map from unsigned char to DGtal::Color
  typedef HueShadeColorMap<unsigned char, 2> ColorMap;
  ColorMap cmap(0, 255);
  //Writting the image to another format
  MagickWriter<Image, ColorMap>::exportMagick( "modified.png", image, cmap );

  trace.endBlock();
  return 0;
}

