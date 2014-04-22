PROJECT(Helloworld)
#Required in DGtal

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

FIND_PACKAGE(DGtal REQUIRED)
INCLUDE_DIRECTORIES(${DGTAL_INCLUDE_DIRS})
LINK_DIRECTORIES(${DGTAL_LIBRARY_DIRS})

SET(SRCs
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
  target_link_libraries (${FILE} ${DGTAL_LIBRARIES})
ENDFOREACH(FILE)
