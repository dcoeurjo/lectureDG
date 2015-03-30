PROJECT(Helloworld)
#Required in DGtal

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

### We need Boost Program Options library
SET(Boost_USE_STATIC_LIBS   ON)
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_USE_STATIC_RUNTIME OFF)
SET(Boost_FOUND FALSE)
FIND_PACKAGE(Boost 1.46.0 REQUIRED COMPONENTS program_options)
if ( Boost_FOUND )
  message(STATUS "Boost and boost_program_options found.")
  include_directories( ${Boost_INCLUDE_DIRS} )
 endif( Boost_FOUND )

 
FIND_PACKAGE(DGtal REQUIRED)
INCLUDE_DIRECTORIES(${DGTAL_INCLUDE_DIRS})
LINK_DIRECTORIES(${DGTAL_LIBRARY_DIRS})

SET(SRCs
  imgRotate
  imgScale
  imgAddNoise
  DSSCirculatorExample
  DSSExample
  testSet
  PGMReader
  simpleboard
  helloworld
  PGMObject)

IF ((WITH_QGLVIEWER) OR (WITH_VISU3D_QGLVIEWER))
  SET(SRCs
    image2mesh  ${SRCs})
  MESSAGE(STATUS "Viewer3D enabled")
ELSE()
  MESSAGE(STATUS "WITH_QGLVIEWER missing when building DGtal. I cannot construct image2mesh")
ENDIF()


FOREACH(FILE ${SRCs})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} ${DGTAL_LIBRARIES}  ${Boost_LIBRAIRIES}  ${Boost_PROGRAM_OPTIONS_LIBRARY})
ENDFOREACH(FILE)
