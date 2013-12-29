///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <DGtal/base/Common.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/readers/PNMReader.h>
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers


int main()
{
  
  std::string filename = "hop.pgm";
  
  //Image type (image of unsigned int)
  typedef ImageContainerBySTLVector< Domain, unsigned int > Image;
  
  //We read the PGM file
  Image image = PNMReader<Image>::importPGM(filename); 

  trace.info() << "Image read :"<< image <<std::endl;

  //We convert pixels in ]0,255] into a digital set
  DigitalSet set2d( image.domain() );
  SetFromImage<DigitalSet>::append<Image>(set2d, image, 0, 255);
  
  //We display the set
  Board2D board;
  board << image.domain() << set2d; 
  board.saveEPS( "input-set.eps");

  //We add a topology on the point set using Object8_4 class
  //with the dt8_4 adjacency metric (defined in StdDefs.h)
  Object8_4 object(dt8_4, set2d);
  //Similarly, Object4_8 and dt4_8 exist if you want to change
  //connectivity
  std::cout << object << std::endl;
  std::cout << object.pointSet() << std::endl;
 
  //Now you can add/remove some points opf the object via its pointSet
  //e.g.
  //
  // object.pointSet().insert( Point(2,2) );
  //
  //Or using storing a reference on the Set (the object set is
  //automatically updated since we manipulate a reference to its set).
  //
  DigitalSet & S = object.pointSet();
  std::cout << S << std::endl;
  S.insert( Point(2,2) );
  std::cout << S << std::endl;
  S.erase( Point(2,2) );
  std::cout << S << std::endl;
 
  //Now, you have access to point simplicity test
  //for the (8,4)-jordan pair ( (0,1)-with notations in lecture)
  bool res = object.isSimple( Point(2,2) );
  if (res)
    std::cout << "Point(2,2) is simple"<<std::endl;
  else
    std::cout << "Point(2,2) is not simple"<<std::endl;
 
  //Object can also be displayed with its adjacency relationship
  board.clear();
  board << SetMode( object.className(), "DrawAdjacencies" )
	<< object;
  board.saveEPS("object-output.eps");


  //Nice display of first layer of simple points
  board.clear();
  Color red( 255, 0, 0 );
  Color gray( 64, 64, 64 );
  Color black( 0, 0,0);
  for(DigitalSet::ConstIterator it = S.begin(), itend = S.end();
      it != itend; ++it)
    {
      //Remember (*it) is a Point
      if (object.isSimple( *it ))
	board  << CustomStyle( Point().className(), new CustomColors( black, red ) );
      else
	board  << CustomStyle( Point().className(), new CustomColors( black, gray ) );
      
      board << *it;
    }
  board.saveEPS("object-simplepoints.eps");
  

  return 0;
}
