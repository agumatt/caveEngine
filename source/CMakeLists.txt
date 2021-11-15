set(CAVE_HEADERS 
				Core/RootDirectory.hpp
				Rendering/RenderingManager.hpp
				Rendering/SkeletalMeshComponent.hpp
				EntityComponent/EntityComponentManager.hpp
				Audio/AudioSourceComponent.hpp
				Audio/AudioManager.hpp
				World/World.hpp
				Utils/Utils.hpp
				Engine.hpp
				Application.hpp)
set(CAVE_SOURCES 
				Rendering/RenderingManager.cpp
				Rendering/SkeletalMeshComponent.cpp
				EntityComponent/EntityComponentManager.cpp
				Audio/AudioSourceComponent.cpp
				Audio/AudioManager.cpp
				World/World.cpp
				Application.cpp)
file(GLOB_RECURSE Shaders  "${CMAKE_SOURCE_DIR}/Assets/Shaders/*")
source_group("Shaders" FILES ${Shaders})

add_library(caveEngine STATIC ${CAVE_SOURCES} ${CAVE_HEADERS} caveEngine.hpp ${Shaders})
if (MSVC)
    target_compile_options(caveEngine PUBLIC /wd5033)
endif(MSVC)
target_include_directories(caveEngine PRIVATE ${THIRD_PARTY_INCLUDE_DIRECTORIES} CAVE_INCLUDE_DIRECTORY)
target_link_libraries(caveEngine PRIVATE ${THIRD_PARTY_LIBRARIES})
set_property(TARGET caveEngine PROPERTY CXX_STANDARD 20)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${CAVE_SOURCES} ${CAVE_HEADERS})


