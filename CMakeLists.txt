# CMakeLists file to build a SFML project

# Set the minimum required version of CMake
cmake_minimum_required(VERSION 2.8)

# Ignore MSVC deprecated warnings
if (MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# Set project name
project(SFML-Learning)

# List your files here
set(my_source_files
)
set(my_header_files
)

# Set option to use the static SFML libraries (static libraries are used by default)
set(SFML_STATIC_LIBRARIES TRUE CACHE BOOL "Use SFML static libraries")

# Add compiler definition to use static SFML libraries
if (SFML_STATIC_LIBRARIES)
	add_definitions(-DSFML_STATIC)
endif()

# SFML installation path 
set (SFML_INSTALLATION_DIR "" CACHE PATH "Path to find SFML: <sfml root prefix>/lib/cmake/SFML")

if(SFML_INSTALLATION_DIR)
	# Set path to find SFML
	set(SFML_DIR "${SFML_INSTALLATION_DIR}/lib/cmake/SFML") 

	# Find SFML
	find_package(SFML 2.5 COMPONENTS audio graphics network system window REQUIRED)
	
	add_executable(HelloWorld HelloWorld.cpp)
	target_link_libraries(HelloWorld sfml-graphics sfml-audio sfml-network sfml-window sfml-system)
else()
	message("Set SFML_INSTALLATION_DIR and press Configurate again")
endif()