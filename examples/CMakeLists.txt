function(Add_Example TARGETNAME FILENAME)
	add_executable(${TARGETNAME} ${FILENAME})
	set_property(TARGET ${TARGETNAME} PROPERTY CXX_STANDARD 20)
	set_property(TARGET ${TARGETNAME} PROPERTY FOLDER Examples)
	target_link_libraries(${TARGETNAME} PRIVATE caveEngine)
	target_include_directories(${TARGETNAME} PRIVATE ${CAVE_INCLUDE_DIRECTORY} ${THIRD_PARTY_INCLUDE_DIRECTORIES})
	add_custom_command(TARGET ${TARGETNAME} POST_BUILD        
		COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        $<TARGET_FILE:OpenAL> $<TARGET_FILE_DIR:${TARGETNAME}>)

endfunction(Add_Example)

Add_Example(Example1 Example1.cpp)