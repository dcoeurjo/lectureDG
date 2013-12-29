///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <DGtal/base/Common.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/helpers/StdDefs.h>
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

///////////////////////////////////////////////////////////////////////////////

int main()
{
  trace.beginBlock ( "Board example" );

  Point p1( -3, -2 );
  Point p2( 7, 3 );
  Point p3( 0, 0 );
  Domain domain( p1, p2 );
  

  Board2D board;
  
  //We display the underlying domain
  board << domain ;

  //We display points
  board << p1 << p2 << p3;


  //Output
  board.saveSVG("test.svg");
  board.saveEPS("test.eps");
  board.saveTikZ("test.tikz");
  
  //Clear
  board.clear();
  
  //Upade position + color
  p2[0] = 5; //x-coordinate
  board << domain << p1 << p3;
  
  Color red( 255, 0, 0 );
  
  //All points will be in red
  board  << CustomStyle( p2.className(), new CustomColors( red, red ) )
	 << p2;
  
  //Export again
  board.saveEPS("test2.eps");


  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

