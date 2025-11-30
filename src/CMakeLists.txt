if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/deps/PEGTL
   OR NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/deps/CLI11)
  message(
    FATAL_ERROR
      "The PEGTL/CLI11 git submodule is not available. Please run git submodule update --init"
  )
endif()
add_subdirectory(app)
add_subdirectory(deps)
add_subdirectory(lib)
