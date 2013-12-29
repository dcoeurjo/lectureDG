///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <DGtal/base/Common.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/helpers/StdDefs.h>
#include <DGtal/geometry/curves/ArithmeticalDSS.h>
#include <DGtal/base/Circulator.h>
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i; //We'll only consider Z² digital space on
			    //32bit integers


int main()
{
  
  Board2D board;
  Domain domain(Point(-1,-1),Point(8,4));
  
  //We construct a sequence of points
  std::vector<Point> sequence;
  sequence.push_back(Point(0,0));
  sequence.push_back(Point(1,0));
  sequence.push_back(Point(2,1));
  sequence.push_back(Point(2,2));
  sequence.push_back(Point(1,3));
  sequence.push_back(Point(0,3));
  sequence.push_back(Point(-1,2));
  sequence.push_back(Point(-1,1));
  
  board << domain;

  //We check the sequence
  typedef std::vector<Point>::const_iterator Iterator;

  for(Iterator it=sequence.begin(),
	itend = sequence.end(); it != itend ; ++it)
    board << (*it); //We trace out the sequence
  board.saveEPS("sequenceCirculator.eps");
  
  //Circulator on the sequence
  typedef Circulator<Iterator> MyCirculator;

  //We create a circulator on the complete sequence starting at
  //position sequence.begin()
  Iterator position = sequence.begin();
  MyCirculator it (position, sequence.begin(), sequence.end());

  //Now, ++it and --it are always defined whatever the sequence
  //extremities.
  //For example, let's display the triplet of consecutive points
  MyCirculator itbegin = it;
  
  do
    {
      MyCirculator next = it, nextnext= it ;
      next++;
      nextnext ++; nextnext ++;
      trace.info() << "current = "<< (*it) 
		   << " next = "<< (*next) 
		   << " next-next = " << (*nextnext)<<std::endl;

      ++it;
    }
  while (it != itbegin);
  
  //We can now define a DSS on the Circulator to be able to recognize
  //DSS on circular contours (e.g. there may exist a DSS covering
  //sequence extremities). 
  ArithmeticalDSS< MyCirculator, Integer, 8> a8DSS;
  
  //API on aDSS remains valid (extend, retract, ...)
  //...
 
  return 0;
}
