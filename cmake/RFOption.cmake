# Various functions for setting options for a target
#
# - rf_numerical_option
#   Create an option with a numerical value. The final option is named
#   as RF_OPTION_${OPTION}, depending on the given option name.
#
#   Arguments:
#   TARGET -- The project to configure with the option
#   OPTION -- The name of the option
#   DESCRIPTION -- A docstring about the option
#   DEFAULT -- The option's default value
#
# - rf_system_numerical_option
#   Functions just like rf_numerical_option but the name stays as is
#
# - rf_bool_option
#   Create an option with a boolean value. The final option is named
#   as RF_OPTION_${OPTION}, depending on the given option name.
#
#   Arguments:
#   TARGET -- The project to configure with the option
#   OPTION -- The name of the option
#   DESCRIPTION -- A docstring about the option
#   DEFAULT -- The option's default value
#
# - rf_system_bool_option
#   Functions just like rf_bool_option but the name stays as is
#
# - rf_list_option
#   Create an option whose value can be one of a possible list. The final option is named
#   as RF_OPTION_${OPTION}, depending on the given option name.
#
#   Arguments:
#   TARGET -- The project to configure with the option
#   OPTION -- The name of the option
#   DESCRIPTION -- A docstring about the option
#   ALLOWED_VALUES -- A cmake list of the allowed options
#   DEFAULT -- The option's default value

function(rf_numerical_option TARGET OPTION DESCRIPTION DEFAULT)
  set(RF_OPTION_${OPTION} ${DEFAULT} CACHE STRING ${DESCRIPTION})
  message(STATUS "${OPTION} is set to ${RF_OPTION_${OPTION}}")
  target_compile_definitions(${TARGET} PUBLIC "RF_OPTION_${OPTION}=${RF_OPTION_${OPTION}}")
endfunction()

function(rf_system_numerical_option TARGET OPTION DESCRIPTION DEFAULT)
  set(${OPTION} ${DEFAULT} CACHE STRING ${DESCRIPTION})
  message(STATUS "${OPTION} is set to ${${OPTION}}")
  target_compile_definitions(${TARGET} PUBLIC "${OPTION}=${${OPTION}}")
endfunction()

function(rf_bool_option TARGET OPTION DESCRIPTION DEFAULT)
  set(RF_OPTION_${OPTION} ${DEFAULT} CACHE BOOL ${DESCRIPTION})
  message(STATUS "${OPTION} is set to ${RF_OPTION_${OPTION}}")
  if (${RF_OPTION_${OPTION}})
    target_compile_definitions(${TARGET} PUBLIC "RF_OPTION_${OPTION}")
  endif()
endfunction()

function(rf_system_bool_option TARGET OPTION DESCRIPTION DEFAULT)
  set(${OPTION} ${DEFAULT} CACHE BOOL ${DESCRIPTION})
  message(STATUS "${OPTION} is set to ${${OPTION}}")
  if (${${OPTION}})
    target_compile_definitions(${TARGET} PUBLIC "${OPTION}")
  endif()
endfunction()

function(rf_list_option TARGET OPTION DESCRIPTION ALLOWED_VALUES DEFAULT)
  set(RF_OPTION_${OPTION} ${DEFAULT} CACHE STRING ${DESCRIPTION})
  list(FIND ALLOWED_VALUES ${RF_OPTION_${OPTION}} INDEX)
  if (${INDEX} EQUAL -1)
    message(FATAL_ERROR "Given ${RF_OPTION_${OPTION}} for ${OPTION} but it can only be one of: ${ALLOWED_VALUES}")
  endif()
  message(STATUS "${OPTION} is set to ${RF_OPTION_${OPTION}}")
  target_compile_definitions(${TARGET} PUBLIC "RF_OPTION_${OPTION}=${RF_OPTION_${OPTION}}")
endfunction()
