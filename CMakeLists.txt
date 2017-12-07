cmake_minimum_required(VERSION 3.10)
foreach(p
    CMP0071 # 3.10: Let AUTOMOC and AUTOUIC process GENERATED files
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

include(CryptoNoteWallet.cmake)

project(${CN_PROJECT_NAME})

execute_process(COMMAND git log -1 --pretty=format:%h
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
OUTPUT_VARIABLE GIT_REVISION)

message(INFO Git revision : ${GIT_REVISION})

set(CRYPTONOTE_LIB cryptoNote)

include_directories(${CMAKE_BINARY_DIR}
  src
  include
  iridium/external
  iridium/external/rocksdb/include/
  iridium/include
  iridium/src
)

find_package(Qt5 REQUIRED
    Gui
    Widgets
    Network
    DBus
    )

include_directories(${Qt5DBus_INCLUDE_DIRS} iridium/external/rocksdb/include/ include src external "${CMAKE_CURRENT_BINARY_DIR}/version")

set(Boost_USE_STATIC_LIBS ON)
if(WIN32)
  set(Boost_USE_STATIC_RUNTIME OFF)
else(WIN32)
  set(Boost_USE_STATIC_RUNTIME ON)
endif(WIN32)

find_package(Boost 1.58 REQUIRED COMPONENTS date_time filesystem program_options regex serialization system thread chrono)
if ((${Boost_MAJOR_VERSION} EQUAL 1) AND (${Boost_MINOR_VERSION} EQUAL 54))
  message(SEND_ERROR "Boost version 1.58 is unsupported, more details are available here http://goo.gl/RrCFmA")
endif ()

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

set(VERSION "2.1.2")
configure_file("iridium/src/version.h.in" "version.h")
configure_file("iridium/src/version.h.in" ${CMAKE_SOURCE_DIR}/src/version.h)
configure_file("src/CryptoNoteWalletConfig.h.in" "CryptoNoteWalletConfig.h")

add_definitions(-DGIT_REVISION="${GIT_REVISION}")

set(CMAKE_AUTOMOC ON)

file(GLOB_RECURSE CRYPTONOTE_SOURCES
  iridium/external/miniupnpc/connecthostport.c
  iridium/external/miniupnpc/igd_desc_parse.c
  iridium/external/miniupnpc/minisoap.c
  iridium/external/miniupnpc/miniupnpc.c
  iridium/external/miniupnpc/miniwget.c
  iridium/external/miniupnpc/minixml.c
  iridium/external/miniupnpc/portlistingparse.c
  iridium/external/miniupnpc/receivedata.c
  iridium/external/miniupnpc/upnpcommands.c
  iridium/external/miniupnpc/upnpreplyparse.c
  iridium/src/BlockchainExplorer/BlockchainExplorer.cpp
  iridium/src/BlockchainExplorer/BlockchainExplorerErrors.cpp
  iridium/src/Common/Base58.cpp
  iridium/src/Common/CommandLine.cpp
  iridium/src/Common/Util.cpp
  iridium/src/Common/StringTools.cpp
  iridium/src/Common/JsonValue.cpp
  iridium/src/Common/ConsoleTools.cpp
  iridium/src/Common/MemoryInputStream.cpp
  iridium/src/Common/PathTools.cpp
  iridium/src/Common/StdInputStream.cpp
  iridium/src/Common/StdOutputStream.cpp
  iridium/src/Common/StreamTools.cpp
  iridium/src/Common/StringOutputStream.cpp
  iridium/src/Common/StringView.cpp
  iridium/src/Common/VectorOutputStream.cpp
  iridium/src/Common/ScopeExit.cpp
  iridium/src/ConnectivityTool/ConnectivityTool.cpp
  iridium/src/crypto/blake256.c
  iridium/src/crypto/chacha8.c
  iridium/src/crypto/crypto-ops-data.c
  iridium/src/crypto/crypto-ops.c
  iridium/src/crypto/crypto.cpp
  iridium/src/crypto/groestl.c
  iridium/src/crypto/hash-extra-blake.c
  iridium/src/crypto/hash-extra-groestl.c
  iridium/src/crypto/hash-extra-jh.c
  iridium/src/crypto/hash-extra-skein.c
  iridium/src/crypto/hash.c
  iridium/src/crypto/jh.c
  iridium/src/crypto/keccak.c
  iridium/src/crypto/oaes_lib.c
  iridium/src/crypto/random.c
  iridium/src/crypto/skein.c
  iridium/src/crypto/slow-hash.c
  iridium/src/crypto/slow-hash.cpp
  iridium/src/crypto/tree-hash.c
  iridium/src/CryptoNoteCore/*.cpp
  iridium/src/CryptoNoteProtocol/*.cpp
  iridium/src/Daemon/*.cpp
  iridium/src/HTTP/*.cpp
  iridium/src/InProcessNode/InProcessNode.cpp
  iridium/src/InProcessNode/InProcessNodeErrors.cpp
  iridium/src/Logging/*.cpp
  iridium/src/NodeRpcProxy/NodeErrors.cpp
  iridium/src/NodeRpcProxy/NodeRpcProxy.cpp
  iridium/src/P2p/*.cpp
  iridium/src/Rpc/*.cpp
  iridium/src/Serialization/*.cpp
  iridium/src/Transfers/BlockchainSynchronizer.cpp
  iridium/src/Transfers/SynchronizationState.cpp
  iridium/src/Transfers/TransfersConsumer.cpp
  iridium/src/Transfers/TransfersContainer.cpp
  iridium/src/Transfers/TransfersSubscription.cpp
  iridium/src/Transfers/TransfersSynchronizer.cpp
  iridium/src/Wallet/*.cpp
  iridium/src/WalletLegacy/KeysStorage.cpp
  iridium/src/WalletLegacy/WalletLegacy.cpp
  iridium/src/WalletLegacy/WalletHelper.cpp
  iridium/src/WalletLegacy/WalletLegacySerializer.cpp
  iridium/src/WalletLegacy/WalletLegacySerialization.cpp
  iridium/src/WalletLegacy/WalletTransactionSender.cpp
  iridium/src/WalletLegacy/WalletUnconfirmedTransactions.cpp
  iridium/src/WalletLegacy/WalletUserTransactionsCache.cpp
  iridium/src/System/ContextGroup.cpp
  iridium/src/System/Event.cpp
  iridium/src/System/EventLock.cpp
  iridium/src/System/InterruptedException.cpp
  iridium/src/System/Ipv4Address.cpp
  iridium/src/System/TcpStream.cpp
  iridium/src/JsonRpcServer/*.cpp
  iridium/src/PaymentGate/*.cpp
  iridium/src/PaymentGateService/*.cpp
  iridium/src/Miner/*.cpp
)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE FORMS src/gui/ui/*.ui)

if(MSVC)
  include_directories(Platform/Windows)
  set(SOURCES ${SOURCES} ${CMAKE_SOURCE_DIR}/Platform/Windows/ApplicationEventHandler.cpp)
elseif(APPLE)
  include_directories(Platform/OSX)
  include_directories(Platform/Posix)
  file(GLOB_RECURSE SOURCES_MAC ${CMAKE_SOURCE_DIR}/Platform/OSX/*.mm)
  set(SOURCES ${SOURCES} ${SOURCES_MAC})
  set(SOURCES ${SOURCES} ${CMAKE_SOURCE_DIR}/Platform/Posix/System/MemoryMappedFile.cpp)
else()
  include_directories(Platform/Linux)
  include_directories(Platform/Posix)
  set(SOURCES ${SOURCES} ${CMAKE_SOURCE_DIR}/Platform/Linux/ApplicationEventHandler.cpp)
  set(SOURCES ${SOURCES} ${CMAKE_SOURCE_DIR}/Platform/Posix/System/MemoryMappedFile.cpp)
endif()

set(QRC src/resources.qrc)

qt5_wrap_ui(UIS ${FORMS})
qt5_add_resources(RCC ${QRC})

if (WIN32)
  if (NOT MSVC)
    message(FATAL_ERROR "Only MSVC is supported on this platform")
  endif ()
  add_definitions(/D_CRT_SECURE_NO_WARNINGS /D_WIN32_WINNT=0x0600 /DSTATICLIB)
  include_directories(iridium/src/Platform/msc)
  set(PLATFORM_DIR Windows)
  set(BUILD_PLATFORM WIN32)
  set(BUILD_RESOURCES src/iridiumwallet.rc)
  set(QTMAIN Qt5::WinMain)

elseif (UNIX)
  add_custom_target(
     rocksdb
     COMMAND make static_lib -Wno-undef -Wno-unused-result -Wno-unused-value
     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/iridium/external/rocksdb
  )
  add_library(rocksdblib STATIC IMPORTED GLOBAL)
  set_target_properties(rocksdblib PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/iridium/external/rocksdb/librocksdb.a)
  add_dependencies(rocksdblib rocksdb)
  set(CRYPTONOTE_SOURCES ${CRYPTONOTE_SOURCES} iridium/external/miniupnpc/minissdpc.c)

  if (APPLE)
    enable_language(ASM)
    file(GLOB_RECURSE OBJC_SOURCES src/*.mm)
    set(SOURCES ${SOURCES} ${OBJC_SOURCES})
    set(PLATFORM_DIR OSX)
    set(MACOSX_BUNDLE_INFO_STRING "Iridium GUI wallet v${VERSION} ( ${GIT_REVISION} )")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING "${VERSION} ( ${GIT_REVISION} )")
    set(MACOSX_BUNDLE_BUNDLE_NAME IridiumWallet)
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${VERSION}")
    set(MACOSX_BUNDLE_BUNDLE_VERSION "${VERSION}")

    find_package(Qt5PrintSupport REQUIRED)
    include_directories(/usr/include/malloc)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maes -std=c++11 -stdlib=libc++")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -maes -D_DARWIN_C_SOURCE")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework CoreFoundation -framework Carbon -framework IOKit -L/usr/lib")

    set(MACOSX_BUNDLE_ICON_FILE iridium.icns)
    set(APPLICATION_ICON src/images/iridium.icns)
    set_source_files_properties(${APPLICATION_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

    set(BUILD_PLATFORM MACOSX_BUNDLE)
    set(BUILD_RESOURCES ${APPLICATION_ICON})

    GET_TARGET_PROPERTY(QT_LIB_DIR "${Qt5Widgets_LIBRARIES}" LOCATION)
    GET_FILENAME_COMPONENT(QT_LIB_DIR "${QT_LIB_DIR}" PATH)

  else(APPLE)

    set(PLATFORM_DIR Linux)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maes -std=c++11")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -maes -std=c11")
  endif (APPLE)
endif ()

include_directories(iridium/src/Platform/${PLATFORM_DIR})

file(GLOB PLATFORM_SOURCES iridium/src/Platform/${PLATFORM_DIR}/System/*)
set(CRYPTONOTE_SOURCES ${CRYPTONOTE_SOURCES} ${PLATFORM_SOURCES} ${CRYPTONOTE_PLATFORM})

add_library(${CRYPTONOTE_LIB} STATIC ${CRYPTONOTE_SOURCES})
set_target_properties(${CRYPTONOTE_LIB} PROPERTIES COMPILE_DEFINITIONS _GNU_SOURCE)
target_link_libraries(${CRYPTONOTE_LIB} ${Boost_LIBRARIES} ${Qt5DBus_LIBRARIES} rocksdblib)

add_executable(${PROJECT_NAME} ${BUILD_PLATFORM} ${BUILD_RESOURCES} ${SOURCES} ${HEADERS} ${UIS} ${RCC})

set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS _GNU_SOURCE)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${QTMAIN} ${CRYPTONOTE_LIB} ${Qt5DBus_LIBRARIES} rocksdblib)

if (APPLE)
  qt5_use_modules(${PROJECT_NAME} PrintSupport)
elseif (UNIX)
  target_link_libraries(${PROJECT_NAME} -lpthread)
elseif (WIN32)
  target_link_libraries(${PROJECT_NAME} Imm32 Iphlpapi Winmm)
endif (APPLE)

qt5_use_modules(${PROJECT_NAME} Widgets Gui Network)
