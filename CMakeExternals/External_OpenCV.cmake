#
# OpenCV
#

SET(OpenCV_DEPENDS)
  
  SET(OpenCV_enabling_variable OpenCV_LIBRARY)
  
  SET(proj OpenCV)
  SET(proj_DEPENDENCIES)
  
  SET(OpenCV_DEPENDS ${proj})
  execute_process(COMMAND ${GIT_EXECUTABLE} remote show "${git_protocol}://github.com/SCS-B3C/OpenCV.git"
                  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
                  RESULT_VARIABLE RESULT)
                  
  IF(RESULT)
  IF(NOT DEFINED OpenCV_DIR)
    #MESSAGE("Adding project:${proj}")
    
    ExternalProject_Add(${proj}
      DOWNLOAD_DIR "${ep_build_dir}/${proj}"
      CMAKE_GENERATOR ${gen}
      INSTALL_COMMAND ""
      CMAKE_ARGS
        ${ep_common_args}
        -DBUILD_NEW_PYTHON_SUPPORT:BOOL=FALSE
        -DBUILD_DOXYGEN_DOCS:BOOL=FALSE
        -DQT_QMAKE_EXECUTABLE:FILEPATH=${QT_QMAKE_EXECUTABLE}
      DEPENDS
        ${proj_DEPENDENCIES}
      )
    SET(OpenCV_DIR ${ep_build_dir}/${proj})
    
    # Since OpenCV is statically build, there is not need to add its corresponding 
    # library output directory to CTK_EXTERNAL_LIBRARY_DIRS
  
  ELSE()
    include(CMake/mafMacroEmptyExternalProject.cmake)
    mafMacroEmptyExternalProject(${proj} "${proj_DEPENDENCIES}")
  ENDIF()

  ELSE(RESULT)
  IF(NOT DEFINED OpenCV_DIR)
    #MESSAGE("Adding project:${proj}")
    
    ExternalProject_Add(${proj}
      GIT_REPOSITORY "${git_protocol}://github.com/SCS-B3C/OpenCV.git"
      GIT_TAG "origin/master"
      CMAKE_GENERATOR ${gen}
      INSTALL_COMMAND ""
      CMAKE_ARGS
        ${ep_common_args}
        -DBUILD_NEW_PYTHON_SUPPORT:BOOL=FALSE
        -DBUILD_DOXYGEN_DOCS:BOOL=FALSE
        -DQT_QMAKE_EXECUTABLE:FILEPATH=${QT_QMAKE_EXECUTABLE}
      DEPENDS
        ${proj_DEPENDENCIES}
      )
    SET(OpenCV_DIR ${ep_build_dir}/${proj})
    
    # Since OpenCV is statically build, there is not need to add its corresponding 
    # library output directory to CTK_EXTERNAL_LIBRARY_DIRS
  
  ELSE()
    include(CMake/mafMacroEmptyExternalProject.cmake)
    mafMacroEmptyExternalProject(${proj} "${proj_DEPENDENCIES}")
  ENDIF()

  ENDIF(RESULT)
  SET(${OpenCV_enabling_variable}_INCLUDE_DIRS OpenCV_INCLUDE_DIRS)
  SET(${OpenCV_enabling_variable}_FIND_PACKAGE_CMD OpenCV)
    


