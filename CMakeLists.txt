cmake_minimum_required(VERSION 3.10)

project(termid-x VERSION 0.1 LANGUAGES CXX)

# Use a reasonable default C++ standard
if(NOT CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	set(CMAKE_CXX_EXTENSIONS OFF)
endif()

# Turn on some useful warnings for supported compilers
if(MSVC)
	add_compile_options(/W4 /permissive-)
else()
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Project layout: headers in include/, sources in src/
set(PROJECT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

set(SOURCES
	src/main.cpp
	src/account.cpp
	src/engine.cpp
	src/entity.cpp
	src/stock.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
	PRIVATE
		${PROJECT_INCLUDE_DIR}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Installation (optional)
install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin
)

# Simple CPack support for packaging (optional)
include(CPack)

