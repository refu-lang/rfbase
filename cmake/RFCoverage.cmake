function(rf_setup_coverage TARGET)
  if (NOT ${COVERAGE})
    return()
  endif()

  # Check prereqs
  find_program(GCOV_PATH gcov)
  find_program(LCOV_PATH lcov)
  find_program(GENHTML_PATH genhtml)
  find_program(GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/tests)

  if (NOT GCOV_PATH)
	message(FATAL_ERROR "gcov not found! Aborting...")
  endif()

  if (NOT LCOV_PATH)
	message(FATAL_ERROR "lcov not found! Aborting...")
  endif()

  if (NOT GENHTML_PATH)
	message(FATAL_ERROR "genhtml not found! Aborting...")
  endif()

  if (NOT CMAKE_COMPILER_IS_GNUCXX)
	# Clang version 3.0.0 and greater now supports gcov as well.
	message(WARNING "Compiler is not GNU gcc! Clang Version 3.0.0 and greater supports gcov as well, but older versions don't.")

	if (NOT "${CMAKE_CXX_COMPILER_ID}" Matches ".*Clang.*")
	  message(FATAL_ERROR "Compiler is not GNU gcc or clang! Aborting...")
	endif()
  endif()

  target_compile_options(${TARGET} PUBLIC -g -O0 --coverage -fprofile-arcs -ftest-coverage)
  target_link_libraries(${TARGET} PUBLIC gcov)
endfunction()
