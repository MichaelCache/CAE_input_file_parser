if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/deps/PEGTL)
   message(FATAL_ERROR "The PEGTL git submodule is not available. Please run
        git submodule update --init" )
endif()
add_subdirectory(app)
add_subdirectory(deps)
add_subdirectory(lib)
