set(MY_LIB_NAME DevelopmentConverterPlugin)

ADD_FILTER(
src
	DevelopmentConverter.cpp
    DevelopmentConverter.h
	DevelopmentConverterPlugin.cpp
    DevelopmentConverterPlugin.def
    DevelopmentConverterPlugin.h
    
	HotspotImageConverterPNGToHIT.cpp
    HotspotImageConverterPNGToHIT.h
    SoundConverterFFMPEGToOGG.cpp
	SoundConverterFFMPEGToOGG.h
	VideoConverterFFMPEGToWEBM.cpp
	VideoConverterFFMPEGToWEBM.h
    VideoConverterFFMPEGToOGV.cpp
    VideoConverterFFMPEGToOGV.h
    VideoConverterFFMPEGToOGVA.cpp
    VideoConverterFFMPEGToOGVA.h
	ParticleConverterPTCToPTZ.cpp
	ParticleConverterPTCToPTZ.h    
    MovieKeyConverterXMLToAEK.cpp
    MovieKeyConverterXMLToAEK.h
    ImageConverterPVRToHTF.cpp
    ImageConverterPVRToHTF.h
    ImageConverterDDSToHTF.cpp
    ImageConverterDDSToHTF.h
    ImageConverterPNGToACF.cpp
    ImageConverterPNGToACF.h    
)

add_definitions(-DMENGINE_PLUGIN_DLL)

INCLUDE_DIRECTORIES(${THIRDPARTY_DIR}/pybind/include)
INCLUDE_DIRECTORIES(${THIRDPARTY_DIR}/libmath/include)
INCLUDE_DIRECTORIES(${THIRDPARTY_DIR}/metabuf/include)
INCLUDE_DIRECTORIES(${THIRDPARTY_DIR}/poly2tri)

ADD_MENGINE_SHARED()

set_target_properties (${MY_LIB_NAME} PROPERTIES
    FOLDER Plugins
)

TARGET_LINK_LIBRARIES(${MY_LIB_NAME} Metacode)
TARGET_LINK_LIBRARIES(${MY_LIB_NAME} Kernel)

TARGET_LINK_LIBRARIES(${MY_LIB_NAME} ${THIRDPARTY_LIB_DIR}/${MENGINE_LIB_PREFIX}stdex${MENGINE_LIB_SUFFIX})
TARGET_LINK_LIBRARIES(${MY_LIB_NAME} ${THIRDPARTY_LIB_DIR}/${MENGINE_LIB_PREFIX}math${MENGINE_LIB_SUFFIX})
TARGET_LINK_LIBRARIES(${MY_LIB_NAME} ${THIRDPARTY_LIB_DIR}/${MENGINE_LIB_PREFIX}metabuf${MENGINE_LIB_SUFFIX})
TARGET_LINK_LIBRARIES(${MY_LIB_NAME} ${THIRDPARTY_LIB_DIR}/${MENGINE_LIB_PREFIX}lz4${MENGINE_LIB_SUFFIX})
TARGET_LINK_LIBRARIES(${MY_LIB_NAME} ${THIRDPARTY_LIB_DIR}/${MENGINE_LIB_PREFIX}poly2tri${MENGINE_LIB_SUFFIX})