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

	src/backend_engine/account.cpp
	src/backend_engine/engine.cpp
	src/backend_engine/entity.cpp

	src/ui_engine/order_book.cpp
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

include(FetchContent)

FetchContent_Declare(
	ftxui
	GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
	GIT_TAG v6.1.9  # Replace with a version, tag, or commit hash if needed
)

FetchContent_MakeAvailable(ftxui)

# Link FTXUI imported targets to the project's executable (don't create a second
# "main" target). If your project name is `${PROJECT_NAME}` (set above), link
# the ftxui libraries to that target so your sources can use the library.
target_link_libraries(${PROJECT_NAME}
	PRIVATE
		ftxui::screen
		ftxui::dom
		ftxui::component
)