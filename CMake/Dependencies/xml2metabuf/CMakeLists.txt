CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
                                             
project(xml2metabuf)

SET( SOURCE_DIR ${THIRDPARTY_DIR}/metabuf )

set( sources
    ${SOURCE_DIR}/xml2metabuf/Xml2Metabuf.cpp
    ${SOURCE_DIR}/xml2metabuf/Xml2Metacode.cpp
    ${SOURCE_DIR}/xml2metabuf/XmlProtocol.cpp
    )
    
include_directories(${SOURCE_DIR})
include_directories(${SOURCE_DIR}/include)
include_directories(${THIRDPARTY_DIR}/pugixml/src)
include_directories(${THIRDPARTY_DIR}/stdex/include)         

add_library( ${PROJECT_NAME} STATIC ${sources} )