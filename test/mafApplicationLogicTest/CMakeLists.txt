#
#  CMakeLists.txt
#  maf
#
#  Created by Daniele Giunchi - Paolo Quadrani on 10/09/10.
#  Copyright 2009 B3C. All rights reserved.
#
#  See Licence at: http://tiny.cc/QXJ4D
#
#

## #################################################################
## Find the external packages.
## #################################################################

include(${MAF_SOURCE_DIR}/CMakeExternals/Find_qxmlrpc.cmake)
include(${MAF_SOURCE_DIR}/CMakeExternals/Find_QtSOAP.cmake)

## #################################################################
## Init Project
## #################################################################

mafMacroInitProject(1)

## #################################################################
## Build rules
## #################################################################

# Create the executable.
ADD_EXECUTABLE(${PROJECT_NAME} ${PROJECT_SRCS} ${MY_MOC_CXX} ${${PROJECT_NAME}_SOURCES_WRAP})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${PROJECT_LIBS})

## #################################################################
## Installation
## #################################################################

mafMacroInstallProject()
