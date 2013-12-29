///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <DGtal/base/Common.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/readers/PointListReader.h>
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers

///////////////////////////////////////////////////////////////////////////////

int main()
{
  trace.beginBlock ( "PointlistReader example" );
  Board2D board;
  
  std::string filename = "pointList1.pl";
  std::vector<unsigned int> vectPos;
  vectPos.push_back(1); //first column -> x
  vectPos.push_back(2); //second column -> y
  
  //Reading the file (make sure that the file is in the executable path
  std::vector<Z2i::Point> vectPoints = PointListReader<Z2i::Point>::getPointsFromFile(filename,
                     vectPos);
  trace.info()<< "Number of points= "<< vectPoints.size()<<std::endl; 

  //Display
  for(std::vector<Z2i::Point>::iterator it = vectPoints.begin(), itend= vectPoints.end();
      it != itend ; ++it)
    board << (*it);

  //Export
  board.saveEPS("test2.eps");


  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

