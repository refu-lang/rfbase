target_sources(rfbase PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/array.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/endianess.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/fixed_memory_pool.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/hash.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/log.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/rf_unicode.c")
