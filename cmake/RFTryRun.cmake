# Attempts to compile and run a program and check the expected result
#
# Required Arguments:
#
# TARGET -- The target whose compile_definitions to populate with the results of the test
# EXPECTED_RESULT -- The expected return value of the program
# YES_ATTR -- If the ${EXPECTED_RESULT} is returned then the resulting macro define will be:
#                   RF_HAVE_${YES_ATTR}
# SOURCE -- The string of the source snippet to try and compile
#
# Optional Arguments:
# NO_ATTR -- If the ${EXPECTED_RESULT} is returned then the resulting macro define will be:
#                   RF_HAVE_${NO_ATTR}. If this option is not given, nothing will be defined.
#

function(rf_try_run TARGET EXPECTED_RESULT YES_ATTR SOURCE)
  # write the source in a temporary file
  enable_language(C)
  file(WRITE "${CMAKE_BINARY_DIR}/temporary_cmake_file.c" ${SOURCE})
  # try to compile it
  try_run(
    RUN_RESULT
    COMPILE_RESULT
    ${CMAKE_BINARY_DIR}
    SOURCES "${CMAKE_BINARY_DIR}/temporary_cmake_file.c"
    )

  if(NOT ${COMPILE_RESULT})
    message(FATAL_ERROR "At compiler_test_result: Could not compile source:\n${SOURCE}")
  endif()

  message("Run result was: ${RUN_RESULT}")
  if(${RUN_RESULT} EQUAL ${EXPECTED_RESULT})
    target_compile_definitions(${TARGET} PUBLIC RF_HAVE_${YES_ATTR})
  else()
    if(${ARGC} GREATER 4)
      target_compile_definitions(${TARGET} PUBLIC RF_HAVE_${ARGV4})
    endif()
  endif()

  # cleanup
  file(REMOVE "${CMAKE_BINARY_DIR}/temporary_cmake_file.c")
endfunction()
