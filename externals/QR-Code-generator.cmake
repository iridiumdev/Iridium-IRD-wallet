set(QRENCODE_LIB qrencode)

file(GLOB QRENCODE_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} externals/QR-Code-generator/cpp/*.cpp)
file(GLOB QRENCODE_HEADERS RELATIVE ${CMAKE_SOURCE_DIR} externals/QR-Code-generator/cpp/*.hpp)

list(APPEND my_definitions "")
#list(APPEND my_definitions VERSION="4.1.0")
#if(WIN32)
#  list(APPEND my_definitions "inline=__inline")
#endif(WIN32)
add_library(${QRENCODE_LIB} ${QRENCODE_SOURCES} ${QRENCODE_HEADERS})
set_target_properties(${QRENCODE_LIB} PROPERTIES COMPILE_DEFINITIONS "${my_definitions}")
