# SET LIBNAME
SET( MENGINE_LIB_PREFIX "" )
SET( MENGINE_LIB_SUFFIX ".lib" )

set(CMAKE_DEBUG_POSTFIX "")

set(CMAKE_CXX_STANDARD 14)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W4 /wd4481 /wd4121 /Zm1000 /MP /EHsc /GR")
set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /Zi /Ob0 /Od /RTC1")
set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/Zi /O2 /DNDEBUG")

set(CMAKE_C_FLAGS "/DWIN32 /D_WINDOWS /W4 /wd4481 /Zm1000")
set(CMAKE_C_FLAGS_DEBUG "/D_DEBUG /Zi /Ob0 /Od /RTC1")
set(CMAKE_C_FLAGS_RELEASE "/O2 /DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "/Zi /O2 /DNDEBUG")

#set(CMAKE_EXE_LINKER_FLAGS "/STACK:10000000 /machine:I386")
#set(CMAKE_EXE_LINKER_FLAGS_DEBUG "/debug /INCREMENTAL:YES")
#set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO")

set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS_DEBUG} /DEBUG")
set(CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO} /DEBUG")

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /DEBUG")
set(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} /DEBUG")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MANIFEST:NO")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /DEBUG")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} /MT")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_SECURE_SCL=1 -D_HAS_ITERATOR_DEBUGGING=1")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -D_SECURE_SCL=0 -D_HAS_ITERATOR_DEBUGGING=0")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -D_SECURE_SCL=0 -D_HAS_ITERATOR_DEBUGGING=0 -DMENGINE_MASTER_RELEASE")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_SECURE_SCL=1 -D_HAS_ITERATOR_DEBUGGING=1")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -D_SECURE_SCL=0 -D_HAS_ITERATOR_DEBUGGING=0")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} -D_SECURE_SCL=0 -D_HAS_ITERATOR_DEBUGGING=0")

add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS)





