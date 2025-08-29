cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(Fase3)

set(CMAKE_CXX_STANDARD 20)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Define the path to the toolkits folder relative to the current directory
set(TOOLKITS_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/toolkits")

# Add the directory containing xmlparser.h and catmull_rom.h to the include directories
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Engine")

# Find DevIL
find_package(DevIL REQUIRED)
include_directories(${IL_INCLUDE_DIR})

# Check DevIL found
if(NOT DevIL_FOUND)
    message(FATAL_ERROR " DevIL not found!")
endif(NOT DevIL_FOUND)

add_executable(engine "Eng/engine.cpp" "Eng/catmullrom.cpp" "Eng/xmlparser.cpp" "Eng/tinyxml2.cpp")

# Add generator target
add_executable(generator "Gen/generator.cpp" "Gen/functions.cpp")

# Include OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
    message(FATAL_ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

if (WIN32)
    message(STATUS "Toolkits_DIR set to: " ${TOOLKITS_FOLDER})
    set(TOOLKITS_FOLDER "" CACHE PATH "Path to Toolkits folder")
    
    if (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")
        message(ERROR ": GLUT not found")
    endif (NOT EXISTS "${TOOLKITS_FOLDER}/glut/GL/glut.h" OR NOT EXISTS "${TOOLKITS_FOLDER}/glut/glut32.lib")    
    
    include_directories(${TOOLKITS_FOLDER}/glut)
    target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${IL_LIBRARIES} ${TOOLKITS_FOLDER}/glut/glut32.lib)
    target_link_libraries(generator ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${IL_LIBRARIES} ${TOOLKITS_FOLDER}/glut/glut32.lib)
    
    if (EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll")
        file(COPY ${TOOLKITS_FOLDER}/glut/glut32.dll DESTINATION ${CMAKE_BINARY_DIR})
    endif(EXISTS "${TOOLKITS_FOLDER}/glut/glut32.dll")    
    
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT engine)

else (WIN32) #Linux and Mac
    # Set compiler flags for non-Windows systems
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated")

    # Find GLUT
    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIR})
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})

    # Find GLEW (if not Apple)
    if (NOT APPLE)
        find_package(GLEW REQUIRED)
        include_directories(${GLEW_INCLUDE_DIRS})
        link_libraries(${GLEW_LIBRARIES})
        target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${IL_LIBRARIES})
        target_link_libraries(generator ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${IL_LIBRARIES})
    else (NOT APPLE)
        target_link_libraries(engine ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${IL_LIBRARIES})
        target_link_libraries(generator ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${IL_LIBRARIES})
    endif() # NOT APPLE

    if(NOT GLUT_FOUND)
       message(FATAL_ERROR " GLUT not found!")
    endif(NOT GLUT_FOUND)

endif(WIN32)

