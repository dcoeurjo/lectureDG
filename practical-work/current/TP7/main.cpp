#include "TinyOBJ.h"

int main(int argc, char **argv)
{

  Geometry geometry;

  geometry.readOBJ("bunnyReset.obj");

  std::cout<<"OBJ has "<< geometry.vertices.size()<<" vertices" <<std::endl;
  std::cout<<"OBJ has "<< geometry.indices.size()<<" faces" <<std::endl;

  //scale X coords
  for(auto i=0; i < geometry.vertices.size(); ++i)
    geometry.vertices[i].x *=2.0;
  
  geometry.writeOBJ("output.obj");
  
  return 0;
}
