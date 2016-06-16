#!/usr/bin/env bash
# author: Lefteris Karapetsas <lefteris@refu.co>
#
# A script to run tests for the rfbase project

TEST_CMD="./build/test/test_rfbase CK_VERBOSE False"
COVERAGE=0
function print_help {
    echo "Usage: test.sh [extra-options]"
    echo "Arguments:"
    echo "    --help                  Print this help message."
    echo "    --coverage              If given then generate coverage report"
}

if [[ ! -d ./build/test/ ]]; then
    echo "test.sh - ERROR: Could not find build/test/ directory"
    exit 1
fi

if [[ ! -x ./build/test/test_rfbase ]]; then
    echo "test.sh - ERROR: Could not find test_rfbase. Have you already built the tests?"
    exit 1
fi


for arg in ${@:1}
do
    if [[ $arg == "--help" ]]; then
        print_help
        exit 1
    fi

    if [[ $arg == "--coverage" ]]; then
        COVERAGE=1
        continue
    fi

    # if we get here the argument is not recognized
    echo "test.sh: Unrecognized argument ${arg}."
    print_help
    exit 1
done


# zero out previous lcov data
if [[ $COVERAGE -ne 0 ]]; then
    lcov --zerocounters  --directory build
fi
# Execute the tests
$TEST_CMD
if [[ $? -ne 0 ]]; then
    echo "test.sh - ERROR: tests failed"
    exit 1
fi

echo "test.sh - INFO: tests passed"

command -v valgrind >/dev/null 2>&1
if [[ $? -eq 0 ]]; then
    echo "test.sh - INFO: Valgrind found. Running tests under valgrind"
    valgrind --tool=memcheck --leak-check=yes --track-origins=yes --show-reachable=yes --num-callers=20 --track-fds=yes $TEST_CMD
else
    echo "test.sh - INFO: Valgrind not found."
fi


if [[ $COVERAGE -ne 0 ]]; then
    echo "Generating coverage report ..."
    cd build
    lcov --directory . --capture --output-file rfbase.info
    genhtml --output-directory coverage \
            --demangle-cpp --num-spaces 4 --sort \
            --title "RFbase Test Coverage" \
            --function-coverage --branch-coverage --legend \
            rfbase.info
    echo "Coverage report generated!"
fi
