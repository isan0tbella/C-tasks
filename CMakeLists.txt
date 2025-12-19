cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra")

cmake_path(SET LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

include_directories(${LIB_DIR}/Graph_lib)
include_directories(${LIB_DIR})



project("fractal" CXX)

set(TARGET "fractal")

set(HEADERS
        ${LIB_DIR}/Graph_lib/fltk.h
        ${LIB_DIR}/Graph_lib/Graph.h
        ${LIB_DIR}/Graph_lib/GUI.h
        ${LIB_DIR}/Graph_lib/Point.h
        ${LIB_DIR}/Graph_lib/Simple_window.h
        ${LIB_DIR}/Graph_lib/Window.h
        ${LIB_DIR}/vec2d.h
        ${LIB_DIR}/poly.h
        
)
set(SOURCES
        ${LIB_DIR}/Graph_lib/Graph.cpp
        ${LIB_DIR}/Graph_lib/GUI.cpp
        ${LIB_DIR}/Graph_lib/Window.cpp
        ${LIB_DIR}/vec2d.cpp
        ${LIB_DIR}/poly.cpp
        
)

project(${TARGET} CXX)

set(FLTK_SKIP_FLUID True)
set(FLTK_SKIP_FORMS True)
set(FLTK_ROOT "D:\\FLTK\\bin")
find_package(FLTK 1.3.8 EXACT REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(SYSTEM ${FLTK_INCLUDE_DIR})
link_directories(${FLTK_INCLUDE_DIR}/../lib)

add_executable(${TARGET} 
    hometasks/graphics.cpp
    ${LIB_DIR}/Graph_lib/Graph.cpp
    ${LIB_DIR}/Graph_lib/GUI.cpp
    ${LIB_DIR}/Graph_lib/Window.cpp
    ${LIB_DIR}/vec2d.cpp
    ${LIB_DIR}/poly.cpp
    hometasks/graphics.cpp
)
    



target_link_libraries(${TARGET} ${FLTK_LIBRARIES} ${OPENGL_LIBRARIES} gdiplus)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(${TARGET} fltk_jpeg fltk_png fltk_z)
endif()






