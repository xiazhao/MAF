#
#  mafMacroInitProject.cmake
#  maf
#
#  Created by Daniele Giunchi - Paolo Quadrani on 10/09/10.
#  Copyright 2009 B3C. All rights reserved.
#
#  See Licence at: http://tiny.cc/QXJ4D
#
#
MACRO(filterForMoc outputList inputList)
set(${outputList})

foreach(file ${inputList})
  file(READ ${file} _contents)
  
  string(REGEX MATCHALL "Q_OBJECT" _match "${_contents}")
  if(_match)
    LIST(APPEND ${outputList} ${file})
  endif(_match)
    
endforeach(file ${inputList})

ENDMACRO()

MACRO(mafMacroInitProject test)

  # Extract current directory name to use as project name
  file(GLOB CUR_FILE "CMakeLists.txt")
  get_filename_component(CUR_ABSOLUTE_DIR ${CUR_FILE} PATH)
  get_filename_component(DIR_NAME ${CUR_ABSOLUTE_DIR} NAME)
  PROJECT(${DIR_NAME})

  FILE(GLOB input_include_file_list "${PROJECT_SOURCE_DIR}/*.h")
  filterForMoc(include_file_list "${input_include_file_list}")
  
  FILE(GLOB implementation_file_list "${PROJECT_SOURCE_DIR}/*.cpp")
  FILE(GLOB implementation_file_list_vtkMAF "${PROJECT_SOURCE_DIR}/*.cxx")
  FILE(GLOB templete_file_list1 "${PROJECT_SOURCE_DIR}/*.txx")
  FILE(GLOB templete_file_list2 "${PROJECT_SOURCE_DIR}/*.tpp")
  FILE(GLOB resource_file_list "${PROJECT_SOURCE_DIR}/*.qrc")
  FILE(GLOB ui_file_list "${PROJECT_SOURCE_DIR}/*.ui")
  # Set your list of sources here.
  SET(PROJECT_SRCS
	${implementation_file_list}
	${implementation_file_list_vtkMAF}
	${input_include_file_list}
	${templete_file_list1}
	${templete_file_list2}
	${ui_file_list}
	${resource_file_list}
  )

  IF(WIN32)
    ADD_DEFINITIONS(-DUNICODE)
  ELSE(WIN32)
    ADD_DEFINITIONS(-w)
  ENDIF(WIN32)
  
  ## Add the project binary dir as include dir for the .moc files.
  INCLUDE_DIRECTORIES("${PROJECT_BINARY_DIR}")

  set(MY_MOC_CXX)
  set(MY_UI_CXX)
  set(QtApp_RCC_SRCS)
  if(${test})
    ## Moc the tests:
    foreach(FILE_NAME_ABS ${implementation_file_list})
      ## extract the base file name.
      get_filename_component(FILE_NAME ${FILE_NAME_ABS} NAME_WE)
      ## Exclude the main.cpp file (it doesn't ned to be 'mocced')
      if(NOT ${FILE_NAME} STREQUAL "main")
        ## Assign the moc custom filename
        set(MOC_FILE "${FILE_NAME}.moc")
        QT4_GENERATE_MOC(${FILE_NAME_ABS} ${MOC_FILE})
        LIST(APPEND MY_MOC_CXX "${PROJECT_BINARY_DIR}/${MOC_FILE}")
      endif(NOT ${FILE_NAME} STREQUAL "main")
    endforeach()
  else(${test})
    if(BUILD_QA)
      find_program( CODECOV_GCOV gcov )
      add_definitions( -fprofile-arcs -ftest-coverage )
      link_libraries( gcov )
      set( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}  --lgcov" )
      set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  --lgcov" )
    endif(BUILD_QA)
  
    QT4_WRAP_UI(MY_UI_CXX ${ui_file_list})
    # generate rules for building source files from the resources
    QT4_ADD_RESOURCES(QtApp_RCC_SRCS ${resource_file_list})
    ## Moc the library's .h files
    QT4_WRAP_CPP(MY_MOC_CXX ${include_file_list})
  endif(${test})
  
  SET(PROJECT_SRCS 
    ${PROJECT_SRCS}
    ${MY_MOC_CXX}
    ${MY_UI_CXX}
    ${QtApp_RCC_SRCS}
    )

  # List libraries that are needed by this project.
  mafMacroGetTargetLibraries(dependency_libraries)
  SET(PROJECT_LIBS ${dependency_libraries})

ENDMACRO()
