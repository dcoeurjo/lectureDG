///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <DGtal/base/Common.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/geometry/curves/ArithmeticalDSSComputer.h>
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers


int main()
{

  Board2D board;
  Domain domain(Point(0,0),Point(8,4));

  //We construct a sequence of points
  std::vector<Point> sequence;
  sequence.push_back(Point(0,0));
  sequence.push_back(Point(1,0));
  sequence.push_back(Point(2,1));
  sequence.push_back(Point(3,1));

  board << domain;

  //We check the sequence
  typedef std::vector<Point>::const_iterator Iterator;

  for(Iterator it=sequence.begin(),
	itend = sequence.end(); it != itend ; ++it)
    board << (*it); //We trace out the sequence
  board.saveEPS("sequence.eps");

  //a 8-connected arithmetical DSS
  // to define a 4-connected one, change the last template parameter
  ArithmeticalDSSComputer< Iterator, Integer, 8> a8DSS;

  //We branch the DSS to the point sequence
  a8DSS.init( sequence.begin() );

  //We display the parameters
  std::cout << a8DSS <<std::endl;

  //We do one step and check if the next point was in the DSS
  if ( a8DSS.extendFront() )
    {
      std::cout << "All fine.. DSS = "<< a8DSS;
    }
  else
    {
      std::cout << "Oops...not a DSS anymore"<<std::endl;
    }

  //We process all points in the sequence
  while ( ( a8DSS.end() != sequence.end() ) &&
          ( a8DSS.extendFront())) ;

  //we display the DSS
  std::cout << "Final parameters DSS="<<a8DSS<<std::endl;

  //..and generate a drawing
  board.clear();
  board << domain ;
  //We draw the DSS points
  board << SetMode(Point().className(), "Grid")
    	<< SetMode(a8DSS.primitive().className(), "Points")
	<< a8DSS.primitive() ;
  //..and the DSS bounding box
  board << SetMode(Point().className(), "Grid")
    	<< SetMode(a8DSS.primitive().className(), "BoundingBox")
	<< a8DSS.primitive() ;

  // export in SVG this time..
  board.saveSVG("DSS.svg");


  return 0;
}
