cmake_minimum_required(VERSION 3.1.0)

# project name and version should be set after cmake_policy CMP0048
project(rfbase VERSION "0.5")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(RFTryCompile)
include(RFTryRun)
include(RFOption)
# Needs to come before compiler_test
add_library(rfbase STATIC "")

# --- Add RFBASE specific options
rf_numerical_option(rfbase LOG_BUFFER_SIZE
  "The initial size to allocate for the Logging"
  4096)
rf_numerical_option(rfbase DEBUG
  "Determines if this will be a Debug Build (0 or 1), and if \
more than 1 it can indicate a different debug level"
  0)
rf_numerical_option(rfbase FGETS_READ_BYTESN
  "This option is the number of bytes that will \
be read each time by the library\'s version of fgets. Must be a \
positive integer number."
  512)
rf_numerical_option(rfbase STRINGX_CAPACITY_MULTIPLIER
  "This is the multiplier by which a\
StringX\'s buffer will get allocated/reallocated by when there \
is a need for buffer extension. Also when the StringX gets \
initialized this is how much bigger than the input String the \
buffer will be. Must be a positive integer."
  2)
rf_numerical_option(rfbase DYNAMICARRAY_CAPACITY_MULTIPLIER
  "This is the multiplier by which \
a Dynamic array\'s buffer will get allocated/reallocated by when \
there is a need for buffer extension. Also when the List gets \
initialized this is how much bigger than the given initial size \
the buffer will be. Must be a positive integer."
  2)
rf_numerical_option(rfbase LOCALSTACK_MEMORY_SIZE
  "This is the default size in bytes of the main \
thread\'s Local Stack of the Refu Library. All objects that are \
initialized as temporary objects such as with the  RFS_() macro \
or the RFXML_() macro are initialized in this stack. Make sure \
to provide a big enough value so that no overflow happens for your \
program. The default value is used if \
no specific value is provided at rf_init()."
  1048576)
rf_numerical_option(rfbase MAX_WORKER_THREADS
  "The maximum number of worker threads we can have." 32)
rf_numerical_option(rfbase WORKER_SLEEP_MICROSECONDS
  "The amount of time in microseconds for worker threads to sleep \
while waiting for jobs to appear on their queues." 32)
rf_numerical_option(rfbase THREADX_MSGQUEUE_SIZE
"This option affects The extended thread \
objects RF_ThreadX, and it denotes what should the default value \
of the size of the message queue of a newly created RF_ThreadX. \
You still have the option to change that in run-rime through the \
initialization functions but if a value is not provided this will \
be the default value."
10)
rf_numerical_option(rfbase HASHMAP_LOAD_FACTOR
"This option determines when the hashmap \
will rehash all of its slots. When during a hashmap insertion \
the ratio of occupied slots over the map\'s size is greater \
than this value then rehashing of the map will take place."
0.7)
rf_numerical_option(rfbase INPUT_FILE_BUFF_INITIAL_SIZE
  "The initial size in bytes of the buffer that will hold the input of each file"
  1024)

rf_bool_option(rfbase SAFE_MEMORY_ALLOCATION
"If true then the malloc and calloc \
calls of the library check for failure and in case of \
failure log an error and exit the process. "
TRUE)
rf_bool_option(rfbase NULLPTR_CHECK
"If true then the library\'s null pointers checks will be \
activated. Some tests rely on this to be active since there \
are some functions tested even with invalid input"
TRUE)
rf_bool_option(rfbase TEXTFILE_ADD_BOM
  "This controls whether to add a BOM(ByteOrderMark) at the beginning of newly created TextFiles"
  TRUE)

rf_list_option(rfbase LOG_LEVEL_DEFAULT
  "Specify the default logging level that the log system will be using."
  "LOG_EMERGENCY;\
LOG_ALERT;\
LOG_CRITICAL;\
LOG_ERROR;\
LOG_WARNING;\
LOG_NOTICE;\
LOG_INFO;\
LOG_DEBUG"
  LOG_ERROR)

include(RFProjectConfig)
rf_project_config(rfbase)
configure_file(${CMAKE_MODULE_PATH}/rf_options.h.in ../include/rf_options.h)
# try to find Perl Compatibe Regex v2, if found then rfbase's regex is also compiled
find_package(PCRE2)


target_include_directories(rfbase PUBLIC include)
add_subdirectory(src)
add_subdirectory(test)



