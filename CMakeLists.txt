#  Iridium wallet Graphical User Interface
#  Based on Bytecoin wallet
#
#  First update submodules :
#  git submodule update --init --recursive
#  git submodule foreach git pull origin master
#

cmake_minimum_required(VERSION 3.5)

message(STATUS "------- Starting configuration ---------")

#Set build version
set(VERSION_MAJOR "5")
set(VERSION_MINOR "0.1")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}")

# Enabling C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(ARCH native CACHE STRING "CPU to build for: -march value or default")
if("${ARCH}" STREQUAL "default")
    set(ARCH_FLAG "default")
else()
    set(ARCH_FLAG "-march=${ARCH}")
endif()
find_package(Git QUIET)
if(Git_FOUND OR GIT_FOUND)
    message(STATUS "Found Git: ${GIT_EXECUTABLE}")
    execute_process(COMMAND git rev-parse --abbrev-ref HEAD  # Get the current branch
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE)

    execute_process(COMMAND git log -1 --format=%h # Get latest commit hash
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE COMMIT_ID
        OUTPUT_STRIP_TRAILING_WHITESPACE)
else()
    message(STATUS "Git not found !")
    set(GIT_BRANCH "unknown")
    set(COMMIT_ID "unknown")
endif()

set(GIT_REVISION "${COMMIT_ID}-${CMAKE_BUILD_TYPE}")
foreach(p
        CMP0071 # 3.1: Let AUTOMOC and AUTOUIC process GENERATED files
        )
    if(POLICY ${p})
        cmake_policy(SET ${p} NEW)
    endif()
endforeach()
# for ninja
cmake_policy(SET CMP0058 NEW)

include(CryptoNoteWallet.cmake)
include(externals/QR-Code-generator.cmake)


project(${CN_PROJECT_NAME})

set(CRYPTONOTE_LIB cryptonote)

find_package(Qt5 REQUIRED
    Gui
    Widgets
    Network
    DBus
    Svg
    )

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    src
    include
    cryptonote/external
    cryptonote/external/rocksdb/include/
    cryptonote/include
    cryptonote/src
    externals/QR-Code-generator/cpp/
    ${Qt5DBus_INCLUDE_DIRS}
    )

  set(WALLET_RESOURCES src/resources.qrc)
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTOUIC ON)
  set(CMAKE_AUTORCC ON)

#include_directories( "${CMAKE_CURRENT_BINARY_DIR}/version")

set(Boost_USE_STATIC_LIBS ON)
if(WIN32)
    set(Boost_USE_STATIC_RUNTIME ON)
endif(WIN32)

find_package(Boost 1.60 REQUIRED COMPONENTS date_time filesystem program_options regex serialization system thread chrono)
if ((${Boost_MAJOR_VERSION} EQUAL 1) AND (${Boost_MINOR_VERSION} EQUAL 54))
    message(SEND_ERROR "Boost version 1.58 is unsupported, more details are available here http://goo.gl/RrCFmA")
endif ()

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_definitions(-DGIT_REVISION="${GIT_REVISION}")

file(GLOB_RECURSE CRYPTONOTE_SOURCES
    cryptonote/external/miniupnpc/
    cryptonote/src/BlockchainExplorer/BlockchainExplorer.cpp
    cryptonote/src/BlockchainExplorer/BlockchainExplorerErrors.cpp
    cryptonote/src/Common/Base58.cpp
    cryptonote/src/Common/CommandLine.cpp
    cryptonote/src/Common/Util.cpp
    cryptonote/src/Common/StringTools.cpp
    cryptonote/src/Common/JsonValue.cpp
    cryptonote/src/Common/ConsoleTools.cpp
    cryptonote/src/Common/MemoryInputStream.cpp
    cryptonote/src/Common/PathTools.cpp
    cryptonote/src/Common/StdInputStream.cpp
    cryptonote/src/Common/StdOutputStream.cpp
    cryptonote/src/Common/StreamTools.cpp
    cryptonote/src/Common/StringOutputStream.cpp
    cryptonote/src/Common/StringView.cpp
    cryptonote/src/Common/VectorOutputStream.cpp
    cryptonote/src/Common/ScopeExit.cpp
    #cryptonote/src/ConnectivityTool/ConnectivityTool.cpp
    cryptonote/src/crypto/blake256.c
    cryptonote/src/crypto/chacha8.cpp
    cryptonote/src/crypto/crypto-ops-data.c
    cryptonote/src/crypto/crypto-ops.c
    cryptonote/src/crypto/crypto.cpp
    cryptonote/src/crypto/groestl.c
    cryptonote/src/crypto/hash-extra-blake.c
    cryptonote/src/crypto/hash-extra-groestl.c
    cryptonote/src/crypto/hash-extra-jh.c
    cryptonote/src/crypto/hash-extra-skein.c
    cryptonote/src/crypto/hash.c
    cryptonote/src/crypto/jh.c
    cryptonote/src/crypto/keccak.c
    cryptonote/src/crypto/oaes_lib.c
    cryptonote/src/crypto/random.c
    cryptonote/src/crypto/skein.c
    cryptonote/src/crypto/slow-hash.c
    cryptonote/src/crypto/aesb.c
    cryptonote/src/crypto/tree-hash.c
    cryptonote/src/CryptoNoteCore/*.cpp
    cryptonote/src/CryptoNoteProtocol/*.cpp
    cryptonote/src/Daemon/*.cpp
    cryptonote/src/HTTP/*.cpp
    cryptonote/src/InProcessNode/InProcessNode.cpp
    cryptonote/src/InProcessNode/InProcessNodeErrors.cpp
    cryptonote/src/Logging/*.cpp
    cryptonote/src/NodeRpcProxy/NodeErrors.cpp
    cryptonote/src/NodeRpcProxy/NodeRpcProxy.cpp
    cryptonote/src/P2p/*.cpp
    cryptonote/src/Rpc/*.cpp
    cryptonote/src/Serialization/*.cpp
    cryptonote/src/Transfers/BlockchainSynchronizer.cpp
    cryptonote/src/Transfers/SynchronizationState.cpp
    cryptonote/src/Transfers/TransfersConsumer.cpp
    cryptonote/src/Transfers/TransfersContainer.cpp
    cryptonote/src/Transfers/TransfersSubscription.cpp
    cryptonote/src/Transfers/TransfersSynchronizer.cpp
    cryptonote/src/Wallet/*.cpp
    cryptonote/src/WalletLegacy/KeysStorage.cpp
    cryptonote/src/WalletLegacy/WalletLegacy.cpp
    cryptonote/src/WalletLegacy/WalletHelper.cpp
    cryptonote/src/WalletLegacy/WalletLegacySerializer.cpp
    cryptonote/src/WalletLegacy/WalletLegacySerialization.cpp
    cryptonote/src/WalletLegacy/WalletTransactionSender.cpp
    cryptonote/src/WalletLegacy/WalletUnconfirmedTransactions.cpp
    cryptonote/src/WalletLegacy/WalletUserTransactionsCache.cpp
    cryptonote/src/System/ContextGroup.cpp
    cryptonote/src/System/Event.cpp
    cryptonote/src/System/EventLock.cpp
    cryptonote/src/System/InterruptedException.cpp
    cryptonote/src/System/Ipv4Address.cpp
    cryptonote/src/System/TcpStream.cpp
    cryptonote/src/JsonRpcServer/*.cpp
    cryptonote/src/PaymentGate/*.cpp
    cryptonote/src/PaymentGateService/*.cpp
    cryptonote/src/Miner/*.cpp
    )

file(GLOB_RECURSE WALLET_SOURCES src/*.cpp)
file(GLOB_RECURSE WALLET_HEADERS src/*.h)
file(GLOB_RECURSE WALLET_FORMS src/Gui/*/*.ui)

if(MSVC)
    include_directories(Platform/Windows)
    set(WALLET_SOURCES ${WALLET_SOURCES} ${CMAKE_SOURCE_DIR}/Platform/Windows/ApplicationEventHandler.cpp)
elseif(APPLE)
    include_directories(Platform/OSX)
    include_directories(Platform/Posix)
    set(WALLET_SOURCES ${WALLET_SOURCES} ${CMAKE_SOURCE_DIR}/Platform/OSX/ApplicationEventHandler.h ${CMAKE_SOURCE_DIR}/Platform/OSX/ApplicationEventHandler.mm ${CMAKE_SOURCE_DIR}/Platform/OSX/INotificationMonitorObserver.h ${CMAKE_SOURCE_DIR}/Platform/OSX/NotificationMonitor.h ${CMAKE_SOURCE_DIR}/Platform/OSX/NotificationMonitor.mm ${CMAKE_SOURCE_DIR}/Platform/OSX/WalletApplication.mm )
    set(WALLET_SOURCES ${WALLET_SOURCES} ${CMAKE_SOURCE_DIR}/Platform/Posix/System/MemoryMappedFile.cpp)
else()
    include_directories(Platform/Linux)
    include_directories(Platform/Posix)
    set(WALLET_SOURCES ${WALLET_SOURCES} ${CMAKE_SOURCE_DIR}/Platform/Linux/ApplicationEventHandler.cpp)
    set(WALLET_SOURCES ${WALLET_SOURCES} ${CMAKE_SOURCE_DIR}/Platform/Posix/System/MemoryMappedFile.cpp)
endif()

#qt5_wrap_cpp(WALLET_HEADERS_MOC ${WALLET_HEADERS})
qt_wrap_ui(WALLET_FORMS_HEADERS ${WALLET_FORMS})
#qt5_add_resources(WALLET_RESOURCES_RCC ${WALLET_RESOURCES})

if (WIN32)
    if (NOT MSVC)
        message(FATAL_ERROR "Only MSVC is supported on this platform")
    endif ()

    add_definitions(/D_CRT_SECURE_NO_WARNINGS /D_WIN32_WINNT=0x0600 /DSTATICLIB)
    include_directories(cryptonote/src/Platform/msc)

    set(PLATFORM_DIR Windows)
    set(BUILD_PLATFORM WIN32)
    set(BUILD_RESOURCES src/iridiumwallet.rc)
    set(QTMAIN Qt5::WinMain)

   # Force static build mostly for rocksdb
    foreach(VAR CMAKE_C_FLAGS_DEBUG CMAKE_CXX_FLAGS_DEBUG CMAKE_C_FLAGS_RELWITHDEBINFO CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_C_FLAGS_RELEASE CMAKE_CXX_FLAGS_RELEASE)
            string(REPLACE "/MD" "/MT" ${VAR} "${${VAR}}")
    endforeach()

elseif (UNIX)

    set(CRYPTONOTE_SOURCES ${CRYPTONOTE_SOURCES} cryptonote/external/miniupnpc/minissdpc.c)

    if (APPLE)
        enable_language(ASM)
        file(GLOB_RECURSE OBJC_SOURCES src/*.mm)
        set(WALLET_SOURCES ${WALLET_SOURCES} ${OBJC_SOURCES})
        set(PLATFORM_DIR OSX)
        set(MACOSX_BUNDLE_INFO_STRING "Iridium GUI wallet v${VERSION} ${GIT_REVISION}")
        set(MACOSX_BUNDLE_LONG_VERSION_STRING "${VERSION} ${GIT_REVISION}")
        set(MACOSX_BUNDLE_BUNDLE_NAME IridiumWallet)
        set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${VERSION}")
        set(MACOSX_BUNDLE_BUNDLE_VERSION "${VERSION}")
#        if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
#        endif()

        find_package(Qt5 COMPONENTS PrintSupport REQUIRED)
        include_directories(/usr/include/malloc)

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maes")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -maes -std=c11 -D_DARWIN_C_SOURCE")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework CoreFoundation -framework Carbon -framework IOKit -L/usr/lib")

        set(MACOSX_BUNDLE_ICON_FILE iridium.icns)
        set(APPLICATION_ICON src/images/iridium.icns)
        set_source_files_properties(${APPLICATION_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

        set(BUILD_PLATFORM MACOSX_BUNDLE)
        set(BUILD_RESOURCES ${APPLICATION_ICON})

        GET_TARGET_PROPERTY(QT_LIB_DIR "${Qt5Widgets_LIBRARIES}" LOCATION)
        GET_FILENAME_COMPONENT(QT_LIB_DIR "${QT_LIB_DIR}" PATH)

        # remove ranlib complaining for no symbols
        set(CMAKE_C_ARCHIVE_CREATE   "<CMAKE_AR> Scr <TARGET> <LINK_FLAGS> <OBJECTS>")
        set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> Scr <TARGET> <LINK_FLAGS> <OBJECTS>")
        set(CMAKE_C_ARCHIVE_FINISH   "<CMAKE_RANLIB> -no_warning_for_no_symbols -c <TARGET>")
        set(CMAKE_CXX_ARCHIVE_FINISH "<CMAKE_RANLIB> -no_warning_for_no_symbols -c <TARGET>")
        set(RELEASE_FLAGS "-Wno-uninitialized -Wno-deprecated-declarations")
    else(APPLE)
        set(PLATFORM_DIR Linux)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maes")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -maes -std=c11")
    endif (APPLE)
endif ()

if(CMAKE_C_COMPILER_ID STREQUAL "GNU" AND NOT (CMAKE_C_COMPILER_VERSION VERSION_LESS 4.8))
        set(DEBUG_FLAGS "-g3 -Og -gdwarf-4 -fvar-tracking -fvar-tracking-assignments -fno-inline -fno-omit-frame-pointer")
    else()
        set(DEBUG_FLAGS "-g3 -O0 -fno-omit-frame-pointer")
    endif()

    if(CMAKE_C_COMPILER_ID STREQUAL "Clang" OR CMAKE_C_COMPILER_ID STREQUAL "AppleClang")
        set(DEBUG_FLAGS "${DEBUG_FLAGS} -Wno-delete-non-virtual-dtor")
    endif()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${DEBUG_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DEBUG_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${RELEASE_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${RELEASE_FLAGS}")

include_directories(cryptonote/src/Platform/${PLATFORM_DIR})
file(GLOB PLATFORM_SOURCES cryptonote/src/Platform/${PLATFORM_DIR}/System/*)
set(CRYPTONOTE_SOURCES ${CRYPTONOTE_SOURCES} ${PLATFORM_SOURCES} ${CRYPTONOTE_PLATFORM})

add_library(${CRYPTONOTE_LIB} STATIC ${CRYPTONOTE_SOURCES})
set_target_properties(${CRYPTONOTE_LIB} PROPERTIES COMPILE_DEFINITIONS _GNU_SOURCE)
target_link_libraries(${CRYPTONOTE_LIB} upnpc-static rocksdb ${Boost_LIBRARIES} ${Qt5DBus_LIBRARIES})

add_executable(${PROJECT_NAME} ${BUILD_PLATFORM} ${BUILD_RESOURCES} ${WALLET_SOURCES} ${WALLET_HEADERS} ${WALLET_FORMS_HEADERS} ${WALLET_RESOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS _GNU_SOURCE)
target_link_libraries(${PROJECT_NAME} rocksdb ${Boost_LIBRARIES} ${QTMAIN} ${CRYPTONOTE_LIB} ${Qt5DBus_LIBRARIES} ${QRENCODE_LIB})

if (APPLE)
  set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Platform/OSX/MacOSXBundleInfo.plist.in)
  find_package(Qt5 COMPONENTS PrintSupport REQUIRED)
  target_link_libraries(${PROJECT_NAME} Qt5::PrintSupport)
elseif (UNIX)
    target_link_libraries(${PROJECT_NAME} -lpthread)
elseif (WIN32)
    target_link_libraries(${PROJECT_NAME} rpcrt4.lib wtsapi32.lib  Imm32 Iphlpapi Winmm)
endif (APPLE)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Gui Qt5::Network Qt5::Svg)

add_subdirectory(cryptonote/external)
message(STATUS "--------------------- Iridium Wallet build details ----------------------------")
message(STATUS "Build : ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler : ${CMAKE_C_COMPILER_ID} version ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Branch : ${GIT_BRANCH}")
message(STATUS "Version : ${VERSION}")
message(STATUS "Revision : ${GIT_REVISION}")
message(STATUS "Portable : ${PORTABLE}" )
message(STATUS "----------------------------------------------------------")
message(STATUS "C Flags ${CMAKE_C_FLAGS_RELEASE}")
message(STATUS "CXX Flags ${CMAKE_CXX_FLAGS_RELEASE}")
configure_file("cryptonote/src/version.h.in" "version.h")
configure_file("cryptonote/src/version.h.in" ${CMAKE_SOURCE_DIR}/src/version.h)
configure_file("src/CryptoNoteWalletConfig.h.in" "CryptoNoteWalletConfig.h")
