/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

/**
 * @file shape2obj
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/11/28
 *
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"

#include "DGtal/io/readers/GenericReader.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/io/viewers/Viewer3D.h"

#include "DGtal/io/colormaps/HueShadeColorMap.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
///////////////////////////////////////////////////////////////////////////////


/**
 * Missing parameter error message.
 *
 * @param param
 */
void missingParam(std::string param)
{
  trace.error() <<" Parameter: "<<param<<" is required..";
  trace.info()<<std::endl;
  exit(1);
}

int main(int argc, char **argv)
{
  //Reading the image
  try
    {
      typedef ImageContainerBySTLVector< Z2i::Domain, unsigned char> Image;
      Image image = GenericReader<Image>::import("small.pgm");

      //Creating the viewer
      // press 'h' for help
      QApplication application(argc,argv);
      Viewer3D<> viewer;
      viewer.setWindowTitle("simpleViewer");
      viewer.show();



      //Display 2 voxels
      viewer << Z3i::Point(2,3,5) ;
      viewer << Z3i::Point(3,2,1) ;

      //Display a triangle
      Z3i::RealPoint p1(1.0,0.0,0.0),
        p2(0.0,1.0,0.0),
        p3(0.0,0.0,1.0);
      viewer.addTriangle(p1,p2,p3);

      //Display a green triangle (with shift)
      Z3i::RealPoint shift(3.0,0.0,0.0);
      viewer<< CustomColors3D(Color(0, 250,0),Color(0, 250,0));
      viewer.addTriangle(p1+shift,
                         p2+shift,
                         p3+shift);

      //A triangle whose color is given by a colormap on scalar function
      // (see colormaps http://libdgtal.org/doc/nightly/moduleIO.html)
      // scalar are 'unsigned char' type here (and we want the 128th color)
      unsigned char maxscalar=255;
      unsigned char minscalar=0;
      HueShadeColorMap<unsigned> huemap(minscalar,maxscalar);
      Z3i::RealPoint shift2(5.0,0.0,0.0);
      viewer<< CustomColors3D(huemap(128),
                              huemap(128));
      viewer.addTriangle(p1+shift2,
                         p2+shift2,
                         p3+shift2);


      //Important: we need to update the display
      viewer  << Display3D<>::updateDisplay;

      //infinite loop (ESC to close the viewer)
      bool res = application.exec();
      return res;
    }
  catch(const std::exception& ex)
    {
      trace.info()<< "Error when reading the file "<< ex.what()<< std::endl;
      exit(2);
    }
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
