# Call to determine if the compiler supports a specific source construct
#
# Required Arguments:
#
# TARGET -- The target whose compile_definitions to populate with the results of the test
# ATTRIBUTE_NAME -- The name of the test. Will decide how the resulting macro define is
#                   named. If no attribute value is given the resulting define will be:
#                   RF_HAVE_${ATTRIBUTE_NAME}
# SOURCE -- The string of the source snippet to try and compile
#
# Optional Arguments:
# ATTRIBUTE_VALUE -- As an optional fourth argument the attribute value can be passed here.
#                    If passed then if the compile succeeds the resulting define will be:
#                    RF_${ATTRIBUTE_NAME}=${ATTRIBUTE_VALUE}


function(rf_try_compile TARGET ATTRIBUTE_NAME SOURCE)
  # write the source in a temporary file
  enable_language(C)
  file(WRITE "${CMAKE_BINARY_DIR}/temporary_cmake_file.c" ${SOURCE})
  # try to compile it
  try_compile(
    TEST_VARIABLE
    ${CMAKE_BINARY_DIR}
    SOURCES "${CMAKE_BINARY_DIR}/temporary_cmake_file.c"
    )
  # depending on compilation result populate definitions
  if(${TEST_VARIABLE})
    set_property(GLOBAL PROPERTY RF_${ATTRIBUTE_NAME} TRUE)

    if(${ARGC} GREATER 3)
      target_compile_definitions(${TARGET} PUBLIC RF_${ATTRIBUTE_NAME}=${ARGV3})
    else()
      target_compile_definitions(${TARGET} PUBLIC RF_HAVE_${ATTRIBUTE_NAME}=1)
    endif()
  else()
    set_property(GLOBAL PROPERTY RF_${ATTRIBUTE_NAME} FALSE)
    if(${ARGC} GREATER 3)
      target_compile_definitions(${TARGET} PUBLIC RF_${ATTRIBUTE_NAME})
    endif()
  endif()
  # cleanup
  file(REMOVE "${CMAKE_BINARY_DIR}/temporary_cmake_file.c")
endfunction()

