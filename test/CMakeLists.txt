add_executable(test_rfbase "")
target_sources(test_rfbase PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/test_main.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/test_log.c"

  "${CMAKE_CURRENT_SOURCE_DIR}/test_datastructs_darray.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/test_datastructs_htable.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/test_datastructs_mbuffer.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/test_datastructs_objset.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/test_datastructs_sbuffer.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/test_datastructs_strmap.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/test_intrusive_list.c"

  "${CMAKE_CURRENT_SOURCE_DIR}/test_io_files.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/test_io_textfile.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/test_io_textfile.c"

  "${CMAKE_CURRENT_SOURCE_DIR}/test_string_buffers.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/test_string_conversion.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/test_string_core.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/test_string_files.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/test_string_manipulation.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/test_string_retrieval.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/test_string_traversal.c"

  "${CMAKE_CURRENT_SOURCE_DIR}/test_utils_array.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/test_utils_memory_pools.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/test_utils_unicode.c"

  "${CMAKE_CURRENT_SOURCE_DIR}/utilities_for_testing.c"
  )

if (${PCRE2_FOUND})
  target_sources(test_rfbase PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/test_regex.c")
  target_compile_definitions(test_rfbase PUBLIC RF_WITH_PCRE2)
endif()


# --- general stuff needed for tests
target_compile_definitions(test_rfbase PUBLIC RF_UNIT_TESTS)
include(FindPkgConfig)
find_package(Check REQUIRED)
pkg_check_modules(LIBCHECK REQUIRED check) # <-- this sets a bunch of variables
target_link_libraries(test_rfbase PUBLIC check)
target_link_libraries(test_rfbase PUBLIC ${LIBCHECK_LDFLAGS})

# --- stuff needed for rfclib tests

target_include_directories(test_rfbase PUBLIC .)

# silence the clang warning for invalid unicode in the string literals
# for the invalid unicode string literal tests
SET_SOURCE_FILES_PROPERTIES("${CMAKE_CURRENT_SOURCE_DIR}/test_utils_unicode.c" PROPERTIES COMPILE_FLAGS -Wno-invalid-source-encoding)
# moves needed test files to the test directory
target_compile_definitions(test_rfbase PUBLIC "CLIB_TESTS_PATH=\"${CMAKE_BINARY_DIR}/test/\"")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/utf8stringfile"
  "${CMAKE_CURRENT_SOURCE_DIR}/utf16bestringfile"
  "${CMAKE_CURRENT_SOURCE_DIR}/utf16lestringfile"
  "${CMAKE_CURRENT_SOURCE_DIR}/utf32bestringfile"
  "${CMAKE_CURRENT_SOURCE_DIR}/utf32lestringfile"
  DESTINATION "${CMAKE_BINARY_DIR}/test")

target_link_libraries(test_rfbase PUBLIC rfbase)
