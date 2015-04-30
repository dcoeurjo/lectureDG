#include <iostream>
#include <DGtal/base/Common.h>
#include "DGtal/io/readers/GenericReader.h"
#include "DGtal/io/writers/GenericWriter.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/helpers/StdDefs.h"

using namespace DGtal;

int main(int argc, char**argv)
{

  typedef ImageContainerBySTLVector<Z2i::Domain, unsigned char >MyImage;

  MyImage image1 = GenericReader<MyImage>::import( argv[1] );
  MyImage image2 = GenericReader<MyImage>::import( argv[2] );

  double sum1=0.0;
  int cpt1=0;  
  for(auto it= image1.constRange().begin(),
        itend = image1.constRange().end();
      it!=itend; ++it, cpt1++)
    sum1 += *it;
  
  double sum2=0.0;
  int cpt2=0;
  for(auto it= image2.constRange().begin(),
        itend = image2.constRange().end();

      it!=itend; ++it, cpt2++)
    sum2 += *it;

  std::cout << 1- std::abs(sum1/cpt1 - sum2/cpt2)/255.0<<std::endl;
  
}
