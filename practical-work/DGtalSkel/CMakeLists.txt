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


FOREACH(FILE ${SRCs})
  add_executable(${FILE} ${FILE})
  target_link_libraries (${FILE} ${DGTAL_LIBRARIES})
ENDFOREACH(FILE)
