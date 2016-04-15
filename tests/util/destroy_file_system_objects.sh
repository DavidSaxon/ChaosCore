#!/bin/bash

# variables
CWD=$(pwd)
BASE_DIR="${CWD}/tests/data/file_system"
TEST_DIR="${BASE_DIR}/test_dir"
UNI_DIR1="${BASE_DIR}/測試_निर्देशिका"

# remove files
rm "${BASE_DIR}/test_file.txt" 2> /dev/null
rm "${TEST_DIR}/test_file.txt" 2> /dev/null
rm "${BASE_DIR}/file with spaces.png" 2> /dev/null
rm "${BASE_DIR}/ການທົດສອບ.טֶקסט" 2> /dev/null
rm "${UNI_DIR1}/ການທົດສອບ.טֶקסט" 2> /dev/null

# remove symbolic links to files
rm "${BASE_DIR}/symlink" 2> /dev/null
rm "${TEST_DIR}/symlink" 2> /dev/null
rm "${BASE_DIR}/rəmzi링크" 2> /dev/null
rm "${UNI_DIR1}/प्रतिकात्मकਲਿੰਕ" 2> /dev/null

# remove symbolic links to directories
rm "${BASE_DIR}/dir_symlink" 2> /dev/null
rm "${TEST_DIR}/dir_symlink" 2> /dev/null

# remove broken symbolic links
rm "${BASE_DIR}/broken_link" 2> /dev/null
rm "${TEST_DIR}/broken_link" 2> /dev/null

# remove directories
# rm "${TEST_DIR}"
# rm "${TEST_DIR}/test_dir"
# rm "${UNI_DIR1}"
# rm "${UNI_DIR1}/測試_निर्देशिका"
