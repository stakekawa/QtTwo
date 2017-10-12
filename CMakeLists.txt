#
# CMakeLists.txt for the Qt Two library
#
# Author: Stefano Takekawa s.takekawa_at_gmail.com
#
# Date: 2017
#
# Copyright: Apache Licence 2.0
#


#
# cmake version
#
cmake_minimum_required(VERSION 3.7)


#
# common include
#
include(support/common.cmake)


#
# variables
#
set(PROJECT_BASENAME "QtTwo")
set(PROJECT_BASEDESCRIPTION "Qt Two library extensions")
set(PROJECT_BASEDIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PROJECT_SRC_DIR "${PROJECT_BASEDIR}")
set(PROJECT_BASEVERSION_MAJOR "0")
set(PROJECT_BASEVERSION_MINOR "0")
set(PROJECT_BASEVERSION_PATCH "1")
set(PROJECT_BASEVERSION "${PROJECT_BASEVERSION_MAJOR}.${PROJECT_BASEVERSION_MINOR}.${PROJECT_BASEVERSION_PATCH}")
set(PROJECT_BASESOVERSION "0")
set(PROJECT_INCLUDE_DIR "${PROJECT_BASEDIR}/include")
set(PROJECT_SRC_DIR "${PROJECT_BASEDIR}/src")
set(PROJECT_SUPPORT_DIR "${PROJECT_BASEDIR}/support")


#
# project
#
project(${PROJECT_BASENAME} LANGUAGES CXX)


#
# add GNU stuff
#
include(GNUInstallDirs)


#
# Qt stuff
#
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)


#
# sources
#
set(PROJECT_SOURCES ${PROJECT_SRC_DIR}/QCenteredComboBox.cpp
                    ${PROJECT_SRC_DIR}/QDpiHelper.cpp
                    ${PROJECT_SRC_DIR}/QTabHorizontalLabelsProxyStyle.cpp
                    ${PROJECT_SRC_DIR}/QUnixSignalCatcher.cpp
                    ${PROJECT_SRC_DIR}/QtTwoUtils.cpp)

#
# headers
#
set(PROJECT_HEADERS ${PROJECT_INCLUDE_DIR}/${PROJECT_BASENAME}.h
                    ${PROJECT_INCLUDE_DIR}/${PROJECT_BASENAME}/QCenteredComboBox.h
                    ${PROJECT_INCLUDE_DIR}/${PROJECT_BASENAME}/QDpiHelper.h
                    ${PROJECT_INCLUDE_DIR}/${PROJECT_BASENAME}/QTabHorizontalLabelsProxyStyle.h
                    ${PROJECT_INCLUDE_DIR}/${PROJECT_BASENAME}/QUnixSignalCatcher.h
                    ${PROJECT_INCLUDE_DIR}/${PROJECT_BASENAME}/QtTwoUtils.h)


#
# includes
#
set(PROJECT_INCLUDES ${PROJECT_INCLUDE_DIR}/${PROJECT_BASENAME}.h)
include_directories(/usr/include)
include_directories(${PROJECT_INCLUDE_DIR})
include_directories(${PROJECT_INCLUDE_DIR}/${PROJECT_BASENAME})


#
# library configuration
#
add_library(${PROJECT_BASENAME} SHARED ${PROJECT_SOURCES} ${PROJECT_HEADERS})

set_target_properties(${PROJECT_BASENAME} PROPERTIES
                      VERSION ${PROJECT_BASEVERSION}
                      SOVERSION ${PROJECT_BASESOVERSION}
                      PUBLIC_HEADER ${PROJECT_INCLUDE_DIR}/${PROJECT_BASENAME}.h
                      DESCRIPTION ${PROJECT_BASEDESCRIPTION})

#
# link libraries
#
target_link_libraries(${PROJECT_BASENAME} Threads::Threads
                                          Qt5::Core
                                          Qt5::Gui
                                          Qt5::Widgets)


#
# configure files
#
configure_file(${PROJECT_SUPPORT_DIR}/${PROJECT_BASENAME}.pc.in ${PROJECT_SUPPORT_DIR}/${PROJECT_BASENAME}.pc @ONLY)
configure_file(${PROJECT_INCLUDE_DIR}/${PROJECT_BASENAME}.h.in ${PROJECT_INCLUDE_DIR}/${PROJECT_BASENAME}.h @ONLY)


#
# include stuff
#
target_include_directories(${PROJECT_BASENAME} PRIVATE)


#
# install
#
install(TARGETS ${PROJECT_BASENAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY ${PROJECT_INCLUDE_DIR}/${PROJECT_BASENAME} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${PROJECT_SUPPORT_DIR}/${PROJECT_BASENAME}.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
