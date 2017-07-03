#/*
#-----------------------------------------------------------------------------
#Filename:    CMakeLists.txt
#-----------------------------------------------------------------------------
#
#This source file is part of the
# _____          _ _        _____ _             _ _
#|_   _|        | (_)      /  ___| |           | (_)
#  | | _ __   __| |_  ___  \ `--.| |_ _   _  __| |_  ___
#  | || '_ \ / _` | |/ _ \  `--. \ __| | | |/ _` | |/ _ \
# _| || | | | (_| | |  __/ /\__/ / |_| |_| | (_| | | (_) |
# \___/_| |_|\__,_|_|\___| \____/ \__|\__,_|\__,_|_|\___/
#
#-----------------------------------------------------------------------------
#*/

cmake_minimum_required(VERSION 3.8)

project(OgreBM)

set(EXECUTABLE_NAME OgreBM)

macro(use_cxx14)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "--std=gnu++14 ${CMAKE_CXX_FLAGS}")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 14)
  endif ()
endmacro(use_cxx14)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

use_cxx14()

if (WIN32)
    set(CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
    set(OGRE_SAMPLES_INCLUDEPATH
            $ENV{OGRE_HOME}/Samples/include
            )
endif (WIN32)

if(UNIX)
        # Ogre
        if(EXISTS "/usr/local/lib/OGRE/cmake/")
          set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
          set(OGRE_SAMPLES_INCLUDEPATH "/usr/local/share/OGRE/samples/Common/include/") # We could just *assume* that developers uses this basepath : /usr/local
        elseif(EXISTS "/usr/lib/OGRE/cmake/")
          set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
          set(OGRE_SAMPLES_INCLUDEPATH "/usr/share/OGRE/samples/Common/include/") # Otherwise, this one
        else()
          message(SEND_ERROR "Failed to find module path.")
        endif(EXISTS "/usr/local/lib/OGRE/cmake/")


endif(UNIX)

if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
  # differentiation between debug and release builds.
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

set(CMAKE_DEBUG_POSTFIX "_d")

find_package(OIS REQUIRED)

if(NOT OIS_FOUND)
        message(SEND_ERROR "Failed to find OIS.")
endif()

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}")

# =============================================================================
# == Find Ogre version 1.9
# =============================================================================

find_package(OGRE 1.9 REQUIRED)

# =============================================================================
# == Find SFML Version 2.X
# =============================================================================
# message("## status: " "Find the SFML Lib ...")
# message("# ENV SFML_DIR: " $ENV{SFML_DIR})

find_package(SFML 2 REQUIRED network system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
endif ()

# =============================================================================
# == Find Boost
# =============================================================================

if (WIN32)
        set(BOOST_ROOT $ENV{BOOST_ROOT})
        set(Boost_DIR $ENV{Boost_DIR})

        message("======================================")
        message("BOOST_ROOT : " ${BOOST_ROOT})
        message("BOOST_INCLUDEDIR : " ${BOOST_INCLUDEDIR})
        message("BOOST_LIBRARYDIR : " ${BOOST_LIBRARYDIR})
        message("======================================")
endif(WIN32)

# =============================================================================
# == Find Boost Init Env
# =============================================================================

if(NOT BOOST_ROOT AND NOT $ENV{BOOST_ROOT} STREQUAL "")
        FILE( TO_CMAKE_PATH $ENV{BOOST_ROOT} BOOST_ROOT )
        if( NOT EXISTS ${BOOST_ROOT} )
                MESSAGE( STATUS  ${BOOST_ROOT} " does not exist. Checking if BOOST_ROOT was a quoted string.." )
                STRING( REPLACE "\"" "" BOOST_ROOT ${BOOST_ROOT} )
                if( EXISTS ${BOOST_ROOT} )
                        MESSAGE( STATUS "After removing the quotes " ${BOOST_ROOT} " was now found by CMake" )
                endif( EXISTS ${BOOST_ROOT})
        endif( NOT EXISTS ${BOOST_ROOT} )
# Save the BOOST_ROOT in the cache
        if( NOT EXISTS ${BOOST_ROOT} )
                MESSAGE( WARNING ${BOOST_ROOT} " does not exist." )
        else(NOT EXISTS ${BOOST_ROOT})
                SET (BOOST_ROOT ${BOOST_ROOT} CACHE STRING "Set the value of BOOST_ROOT to point to the root folder of your boost install." FORCE)
                #SET (BOOST_INCLUDEDIR ${BOOST_ROOT}/Include)
                #SET (BOOST_LIBRARYDIR ${BOOST_ROOT}/lib)
        endif( NOT EXISTS ${BOOST_ROOT} )
endif(NOT BOOST_ROOT AND NOT $ENV{BOOST_ROOT} STREQUAL "")

if( WIN32 AND NOT BOOST_ROOT )
        MESSAGE( WARNING "Please set the BOOST_ROOT environment variable." )
endif( WIN32 AND NOT BOOST_ROOT )

# =============================================================================
# == Find Boost version 1.6x
# =============================================================================

if (NOT OGRE_BUILD_PLATFORM_IPHONE)
        if (WIN32 OR APPLE)
                set(Boost_USE_STATIC_LIBS TRUE)
        else ()
                # Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
                set(Boost_USE_STATIC_LIBS ${OGRE_STATIC})
        endif ()
        if (MINGW)
                # this is probably a bug in CMake: the boost find module tries to look for
                # boost libraries with name libboost_*, but CMake already prefixes library
                # search names with "lib". This is the workaround.
                set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "")
        endif ()
        set(Boost_ADDITIONAL_VERSIONS "1.63" "1.44" "1.44.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
        # Components that need linking (NB does not include header-only components like bind)
        set(OGRE_BOOST_COMPONENTS thread date_time)
        find_package(Boost 1.63 COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
        if (NOT Boost_FOUND)
                # Try again with the other type of libs
                set(Boost_USE_STATIC_LIBS NOT ${Boost_USE_STATIC_LIBS})
                find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} REQUIRED)
        endif()

        # Set up referencing of Boost
        include_directories(${Boost_INCLUDE_DIR})
        add_definitions(-DBOOST_ALL_NO_LIB)
        set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})
endif()

if(Boost_FOUND)
        MESSAGE ( STATUS "ROOT: " ${BOOST_ROOT})
        MESSAGE( STATUS "Setting up boost." )
        include_directories(${Boost_INCLUDE_DIRS})
        if(Boost_DEBUG)
                MESSAGE( STATUS "BOOST Libraries " ${Boost_LIBRARIES} )
                FOREACH(BOOST_COMPONENT ${OGRE_BOOST_COMPONENTS})
                        STRING( TOUPPER ${BOOST_COMPONENT} BOOST_COMPONENT_UPCASE )
                        MESSAGE( STATUS "Boost " ${BOOST_COMPONENT} ": " ${Boost_${BOOST_COMPONENT_UPCASE}_LIBRARY} )
                        MESSAGE( STATUS "Boost " ${BOOST_COMPONENT} " Debug: " ${BOOST_${BOOST_COMPONENT_UPCASE}_LIBRARY_DEBUG} )
                        MESSAGE( STATUS "Boost " ${BOOST_COMPONENT} " Release: " ${Boost_${BOOST_COMPONENT_UPCASE}_LIBRARY_RELEASE} )
                ENDFOREACH(BOOST_COMPONENT)
        endif(Boost_DEBUG)
endif(Boost_FOUND)

# =============================================================================
# == SOURCES
# =============================================================================

set(CLIENT_SRCS
        include/States/AppState.hpp
        include/States/AppStateManager.hpp
        include/States/MenuState.hpp
        src/States/MenuState.cpp
        src/States/AppStateManager.cpp
        src/States/AppState.cpp
        src/Application.cpp
        include/Application.hpp
        include/Map.hpp
        src/Map.cpp
        src/Main.cpp
        src/OgreFramework.cpp
        include/OgreFramework.hpp src/States/GameState.cpp include/States/GameState.hpp src/States/SplashState.cpp include/States/SplashState.hpp)

include_directories(
        include
                ${OIS_INCLUDE_DIRS}
                ${OGRE_INCLUDE_DIRS}
                ${OGRE_Overlay_INCLUDE_DIRS}
                ${OGRE_Terrain_INCLUDE_DIRS}
)

# =============================================================================
# == Client
# =============================================================================

add_executable(${EXECUTABLE_NAME} WIN32 ${CLIENT_SRCS})

set_target_properties(${EXECUTABLE_NAME} PROPERTIES DEBUG_POSTFIX _d)
set_target_properties(${EXECUTABLE_NAME} PROPERTIES COMPILE_DEFINITIONS_DEBUG "_DEBUG")

target_link_libraries(${EXECUTABLE_NAME}
                                        ${OGRE_LIBRARIES}
                                        ${OGRE_Overlay_LIBRARIES}
                                        ${OGRE_Terrain_LIBRARIES}
                                        ${OIS_LIBRARIES})

target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

if (UNIX)
        target_link_libraries(${EXECUTABLE_NAME} pthread)
endif(UNIX)

# =============================================================================
# == Cpy Binary output
# =============================================================================

if (MINGW OR UNIX)
        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
                set_target_properties(${EXECUTABLE_NAME}
                PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
        else()
                set_target_properties(${EXECUTABLE_NAME}
                PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
        endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
endif (MINGW OR UNIX)

if (WIN32)
        if (MSVC)
        message ( STATUS "=================================================")
        message ( STATUS "===============Configuration MSVC================")
        message ( STATUS "=================================================")
    # Visual Studio

        message ( STATUS "=> set_target_properties ${EXECUTABLE_NAME}")
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/tmp)
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR})
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR})
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES SOURCE ${PROJECT_BINARY_DIR})

    # Visual Studio DEBUGGER Working DIRECTORY
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${PROJECT_BINARY_DIR})

    message ( STATUS "=> MSVC select ${EXECUTABLE_NAME}")
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "${EXECUTABLE_NAME}")
    endif (MSVC)
endif(WIN32)

# =============================================================================
# == Windows Visual Studio
# =============================================================================

if (WIN32)
        message ( STATUS "=================================================")
        message ( STATUS "===============Configuration Deps================")
        message ( STATUS "=====================Win32=======================")

        install(FILES $ENV{SFML_ROOT}/bin/sfml-network-2.dll
        DESTINATION .
        CONFIGURATIONS Release RelWithDebInfo)

        # =============================================================================
        # == Realse
        # =============================================================================

        install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/media
        DESTINATION .
        CONFIGURATIONS Release RelWithDebInfo)

        install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/media
        DESTINATION .
        CONFIGURATIONS Release RelWithDebInfo)

        install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/bin/win32
        DESTINATION .
        CONFIGURATIONS Release RelWithDebInfo
            FILES_MATCHING PATTERN "*" PATTERN "*_d*" EXCLUDE)

        install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/bin/win32
        DESTINATION .
        CONFIGURATIONS Release RelWithDebInfo
            FILES_MATCHING PATTERN "*" PATTERN "*_d*" EXCLUDE)

        # ===========
        # OGRE DLL
        # ===========

        install(DIRECTORY ${OGRE_PLUGIN_DIR_REL}/.
            DESTINATION .
            CONFIGURATIONS Release RelWithDebInfo
        FILES_MATCHING PATTERN "*_d*" EXCLUDE PATTERN "*.dll" PATTERN "Sample*" EXCLUDE)

        install(DIRECTORY ${OGRE_PLUGIN_DIR_REL}/.
        DESTINATION .
            CONFIGURATIONS Release RelWithDebInfo
            FILES_MATCHING PATTERN "*_d*" EXCLUDE PATTERN "*.dll" PATTERN "Sample*" EXCLUDE)

        # ===========
        # SFML DLL
        # ===========

        install(FILES $ENV{SFML_ROOT}/bin/sfml-network-2.dll
        DESTINATION .
        CONFIGURATIONS Release RelWithDebInfo)

        install(FILES $ENV{SFML_ROOT}/bin/sfml-network-2.dll
        DESTINATION .
        CONFIGURATIONS Release RelWithDebInfo)

        install(FILES $ENV{SFML_ROOT}/bin/sfml-server-2.dll
        DESTINATION .
        CONFIGURATIONS Release RelWithDebInfo)

        install(FILES $ENV{SFML_ROOT}/bin/sfml-server-2.dll
        DESTINATION .
        CONFIGURATIONS Release RelWithDebInfo)

        # =============================================================================
        # == Debug
        # =============================================================================

        install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/media
        DESTINATION .
        CONFIGURATIONS Debug)

        install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/media
        DESTINATION .
        CONFIGURATIONS Debug)

        install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/bin/win32/.
        DESTINATION .
        CONFIGURATIONS Debug
            FILES_MATCHING PATTERN "*_d*")

        install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/bin/win32/.
        DESTINATION .
        CONFIGURATIONS Debug
            FILES_MATCHING PATTERN "*_d*")

        # ===========
        # OGRE DLL
        # ===========
        install(DIRECTORY ${OGRE_PLUGIN_DIR_DBG}/.
        DESTINATION .
            CONFIGURATIONS Debug
            FILES_MATCHING PATTERN "*_d.dll" PATTERN "Sample*" EXCLUDE)

        install(DIRECTORY ${OGRE_PLUGIN_DIR_DBG}/.
        DESTINATION .
            CONFIGURATIONS Debug
            FILES_MATCHING PATTERN "*_d.dll" PATTERN "Sample*" EXCLUDE)

        # ===========
        # SFML DLL
        # ===========

        install(FILES $ENV{SFML_ROOT}/bin/sfml-network-d-2.dll
        DESTINATION .
        CONFIGURATIONS Debug)

        install(FILES $ENV{SFML_ROOT}/bin/sfml-network-d-2.dll
        DESTINATION .
        CONFIGURATIONS Debug)

        install(FILES $ENV{SFML_ROOT}/bin/sfml-system-d-2.dll
        DESTINATION .
        CONFIGURATIONS Debug)

        install(FILES $ENV{SFML_ROOT}/bin/sfml-system-d-2.dll
        DESTINATION .
        CONFIGURATIONS Debug)

        install(FILES ${OGRE_PLUGIN_DIR_REL}/glut32.dll
        ${OGRE_PLUGIN_DIR_REL}/cg.dll
        ${OGRE_PLUGIN_DIR_REL}/d3dcompiler_47.dll
        DESTINATION .
        CONFIGURATIONS Release RelWithDebInfo)

        install(FILES ${OGRE_PLUGIN_DIR_REL}/glut32.dll
        ${OGRE_PLUGIN_DIR_REL}/cg.dll
        ${OGRE_PLUGIN_DIR_REL}/d3dcompiler_47.dll
        DESTINATION .
        CONFIGURATIONS Release RelWithDebInfo)

        install(FILES ${OGRE_PLUGIN_DIR_REL}/glut32.dll
        ${OGRE_PLUGIN_DIR_REL}/cg.dll
        ${OGRE_PLUGIN_DIR_REL}/d3dcompiler_47.dll
        DESTINATION .
        CONFIGURATIONS Debug)

        install(FILES ${OGRE_PLUGIN_DIR_REL}/glut32.dll
        ${OGRE_PLUGIN_DIR_REL}/cg.dll
        ${OGRE_PLUGIN_DIR_REL}/d3dcompiler_47.dll
        DESTINATION .
        CONFIGURATIONS Debug)

endif (WIN32)

# =============================================================================
# == Unix
# =============================================================================

if (UNIX)
        message ( STATUS "=================================================")
        message ( STATUS "===============Configuration Deps================")
        message ( STATUS "=====================UNIX========================")

        # =============================================================================
        # == Realse
        # =============================================================================

        install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/media
        DESTINATION .
        CONFIGURATIONS Release RelWithDebInfo)


        install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/media
        DESTINATION .
        CONFIGURATIONS Release RelWithDebInfo)

        install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/bin/unix/.
        DESTINATION .
        CONFIGURATIONS Release RelWithDebInfo
        FILES_MATCHING PATTERN "*" PATTERN "*_d*" EXCLUDE)

        install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/bin/unix/.
        DESTINATION .
        CONFIGURATIONS Release RelWithDebInfo
        FILES_MATCHING PATTERN "*" PATTERN "*_d*" EXCLUDE)

        # =============================================================================
        # == Debug
        # =============================================================================

        install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/media
        DESTINATION .
        CONFIGURATIONS Debug)

        install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/media
        DESTINATION .
        CONFIGURATIONS Debug)

        install(FILES ${CMAKE_SOURCE_DIR}/assets/bin/unix/plugins.cfg DESTINATION .)
        install(FILES ${CMAKE_SOURCE_DIR}/assets/bin/unix/resources.cfg DESTINATION .)

        # =============================================================================
        # == Makefile target install
        # =============================================================================

        add_custom_target(install_${PROJECT_NAME}
        $(MAKE) install
        DEPENDS ${PROJECT_NAME}
        COMMENT "Installing ${PROJECT_NAME}")

endif (UNIX)
