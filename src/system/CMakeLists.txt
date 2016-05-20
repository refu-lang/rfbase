if (WIN32)
  target_sources(rfbase PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/dlib_win32.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/system_win32.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/system_info_win32.c")
else()
  target_sources(rfbase PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/dlib_linux.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/system_linux.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/system_info_linux.c")
endif()
