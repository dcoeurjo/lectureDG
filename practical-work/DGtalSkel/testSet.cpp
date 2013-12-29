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


void ConstructMeASet(DigitalSet & aSet, int aParam, int aParam2)
{
  //construct a simple set (points (3,i) here)
  for(int i = aParam; i < aParam2; i++)
    aSet.insert( Point(3,i) );
}

int main()
{
  trace.beginBlock ( "Examples on DigitalSet" );

  Point p1( 0, 0 );
  Point p2( 32, 32 );
  Domain domain( p1, p2 );
  
  Board2D board;
  
  //We define a Set (set of points in a domain)
  DigitalSet mySet(domain);

  //The set will contain point of the domain with even
  //x-,y-coordinates
  
  //We first iterate on a domain
  for(Domain::ConstIterator it = domain.begin();
      it != domain.end(); ++it)
    {
      Point p = *it; //Domain::ConstIterator returns a point when
		     //dereferrenced

      //we test if we have to insert p
      if ((p[0] %2 == 0) && (p[1] %2==0))
	mySet.insert( p );
    }
  
  //We just test if a point belong to a set
  // note that all DGtal objects can be traced out in the terminal
  // with std::cout << ..
  Point q(2,4);
  if ( mySet(q) )
    std::cout << "The point "<< q << " is in the Set"<<std::endl;
  else
    std::cout << "The point "<< q << " is not in the Set"<<std::endl;
  
  //Fine.. we remove q
  mySet.erase( q );
  
  //We iterate on the set to cehck its size
  int cpt=0;
  for(DigitalSet::ConstIterator it = mySet.begin();
      it != mySet.end();
      ++it)
    {
      //Again, (*it) corresponds to a point.
      //Here we just count the points.
      cpt++;
    }
  
  //Check
  if (cpt == mySet.size())
    std::cout << "All fine for the size: "<< cpt << std::endl;

  //We display the set
  board << domain ;
  board << mySet;
  //Export
  board.saveEPS("testSet.eps");
  
  //Call to a function to fill up a set
  mySet.clear();
  ConstructMeASet( mySet , 5, 15);
  
  //Display
  board.clear();
  board << domain ;
  board << mySet;
  board.saveEPS("testSet-bis.eps");


  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

