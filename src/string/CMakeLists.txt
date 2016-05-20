target_sources(rfbase PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/common.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/commonp.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/conversion.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/core.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/corex.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/files.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/filesx.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/manipulation.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/manipulationx.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/module.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/retrieval.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/traversalx.c")

if (${PCRE2_FOUND})
  target_sources(rfbase PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/regex.c")
endif()
