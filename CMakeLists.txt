cmake_minimum_required(VERSION 3.0.0)
project(TCPFrontLoader VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    main.cpp
    src/httprequest.cpp
    src/tcpclient.cpp
    src/urlresolver.cpp
)

find_package(Threads REQUIRED)

add_executable(TCPFrontLoader ${SOURCES})
target_include_directories(TCPFrontLoader PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(TCPFrontLoader PRIVATE Threads::Threads)