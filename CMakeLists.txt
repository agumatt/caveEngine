set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)
cmake_minimum_required(VERSION 3.15)
project(caveEngine C CXX)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
find_package(OpenGL REQUIRED)
set(THIRD_PARTY_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glad/include"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glfw-3.3.2/include"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/spdlog-1.9.2/include"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/imgui-1.78"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/openal-soft/include"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/dr_wav"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/stb"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/ogre/OgreMain/include"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/ogre/Components/Bites/include"
									"${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/OIS/includes")

set(CAVE_INCLUDE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/source")
if(NOT ${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
	set(THIRD_PARTY_INCLUDE_DIRECTORIES ${THIRD_PARTY_INCLUDE_DIRECTORIES} PARENT_SCOPE)
	set(CAVE_INCLUDE_DIRECTORY ${CAVE_INCLUDE_DIRECTORY} PARENT_SCOPE)
endif()
if(MSVC)
	set(THIRD_PARTY_LIBRARIES glad glfw ${OPENGL_LIBRARIES} ImGui ${BULLET_LIBRARIES} OpenAL dr_wav stb ogre OIS)
else()
	set(THIRD_PARTY_LIBRARIES glad glfw ${OPENGL_LIBRARIES} ImGui ${BULLET_LIBRARIES} stdc++fs OpenAL dr_wav stb ogre OIS)
endif(MSVC)
configure_file(CMakeConfigFiles/RootDirectory.hpp.in "${CMAKE_CURRENT_SOURCE_DIR}/source/Core/RootDirectory.hpp")
add_subdirectory(thirdParty)
add_subdirectory(source)
add_subdirectory(tests)
add_subdirectory(examples)
