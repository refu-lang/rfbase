# Call to generally configure a refu project
#
# Required Arguments:
#
# TARGET -- The project to configure

function(rf_project_config TARGET)

  # --- OS Specific macros
  if (WIN32)
    rf_bool_option(${TARGET} WIN32_VERSION "Win32 Version" TRUE)
    target_compile_definitions(${TARGET} PUBLIC "_WIN32_WINNT=0x501")
  elseif (APPLE)
    rf_bool_option(${TARGET} APPLE_VERSION "Apple Version" TRUE)
    target_link_libraries(${TARGET} PUBLIC pthread)
    target_link_libraries(${TARGET} PUBLIC m)
  elseif (UNIX)
    rf_bool_option(${TARGET} LINUX_VERSION "Linux Version" TRUE)
    rf_system_bool_option(${TARGET} _LARGEFILE64_SOURCE
      "If you define this macro an additional set of functions is made available which \
enables 32 bit systems to use files of sizes beyond the usual limit of 2GB. This interface \
is not available if the system does not support files that large. On systems where the \
natural file size limit is greater than 2GB (i.e., on 64 bit systems) the new functions are \
identical to the replaced functions"
      TRUE)
    target_compile_definitions(${TARGET} PUBLIC "_GNU_SOURCE")

    target_link_libraries(${TARGET} PUBLIC rt)
    target_link_libraries(${TARGET} PUBLIC pthread)
    target_link_libraries(${TARGET} PUBLIC m)
  else()
    message(FATAL_ERROR "Unsupported Operating System")
  endif()


  # --- General options
  # TODO: This should need a check
  rf_system_numerical_option(${TARGET} _FILE_OFFSET_BITS
    "This macro determines which file system interface shall be used, one replacing the other.\
 Whereas _LARGEFILE64_SOURCE makes the 64 bit interface available as an additional interface, \
_FILE_OFFSET_BITS allows the 64 bit interface to replace the old interface."
    64)

  rf_system_bool_option(${TARGET} COVERAGE "Enable coverage report analysis" FALSE)
  # --- Check what features the compiler supports
  rf_try_compile(${TARGET} TYPEOF "#include <stddef.h>\nint main(){typeof(int) a = 0\; return a\;}")
  rf_try_compile(${TARGET} ATTRIBUTE_COLD "int __attribute__((cold)) func(int x) { return x\; } int main() {return 0\;}" "__attribute__((cold))")
  rf_try_compile(${TARGET} ATTRIBUTE_CONST "static int __attribute__((const)) func(int x) { return x\; } int main() {return 0\;}" "__attribute__((const))")
  rf_try_compile(${TARGET} ATTRIBUTE_UNUSED "static int __attribute__((unused)) func(int x) { return x\; } int main() {return 0\;}" "__attribute__((unused))")
  rf_try_compile(${TARGET} BUILTIN_CHOOSE_EXPR "#include <stddef.h>\nint main(){return __builtin_choose_expr(1, 0, \"garbage\")\;}")
  rf_try_compile(${TARGET} BUILTIN_TYPES_COMPATIBLE_P "#include <stddef.h>\nint main(){return __builtin_types_compatible_p(char *, int) ? 1 : 0\;}")
  rf_try_compile(${TARGET} FLEXIBLE_ARRAY_MEMBER "#include <stddef.h>\nstruct foo { unsigned int x\; int arr[]\; }\;\nint main(){return 0\;}")
  rf_try_compile(${TARGET} STATEMENT_EXPR
    "int main(int argc, char **argv)\n\
   {return ({ int x = argc\; x == argc ? 0 : 1\; })\;}"
    )

  rf_try_run(${TARGET} 1 LITTLE_ENDIAN
    "#include <stdio.h>\n\
   #include <stdint.h>\n\
   int littleEndianCheck(void)\n\
   {\n\
       union\n\
       {\n\
           uint32_t i\;\n\
           char c[4]\;\n\
       } bint\;\n\
       bint.i = 42\;\n\
       return bint.c[0] == 42\;\n\
   }\n\
  int main(int argc, char **argv)\n\
  {return littleEndianCheck()\;}"

    BIG_ENDIAN
    )
  get_target_property(OUR_COMPILE_DEFS ${TARGET} COMPILE_DEFINITIONS)
  MESSAGE("${TARGET} Compile Definitions: ${OUR_COMPILE_DEFS}")
endfunction()
