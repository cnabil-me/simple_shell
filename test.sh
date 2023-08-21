#/bin/bash

# COMPILING
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

# TESTING...


SHELL="./hsh"

# Function to run a command in your shell
run_command() {
    echo "$1" | $SHELL
}

# Test Ctrl+D (End of file)
echo -e "Testing Ctrl+D (End of file)"
echo "echo Testing Ctrl+D" | $SHELL

# Test command lines with arguments
echo -e "\nTesting command lines with arguments"
run_command "ls -l"
run_command "echo Hello, world!"
run_command "ls non_existent_directory"

# Test PATH handling
echo -e "\nTesting PATH handling"
run_command "ls"

# Test exit built-in
echo -e "\nTesting exit built-in"
run_command "exit"
run_command "exit 98"

# Test env built-in
echo -e "\nTesting env built-in"
run_command "env"

# Test getline function
echo -e "\nTesting getline function"
run_command "echo This is a test" | $SHELL

# Test setenv and unsetenv built-in
echo -e "\nTesting setenv and unsetenv built-in"
run_command "setenv TEST_VAR test_value"
run_command "unsetenv TEST_VAR"

# Test cd built-in
echo -e "\nTesting cd built-in"
run_command "cd"
run_command "cd -"
run_command "cd /"

# Test commands separator (;)
echo -e "\nTesting commands separator (;)"
run_command "ls -l; pwd"

# Test shell logical operators (&& and ||)
echo -e "\nTesting shell logical operators (&& and ||)"
run_command "ls -l && pwd"
run_command "ls non_existent_directory || echo Command failed"

# Test alias built-in
echo -e "\nTesting alias built-in"
run_command "alias"
run_command "alias ls"
run_command "alias test_alias='echo Alias test'"

# Test variable replacement
echo -e "\nTesting variable replacement"
run_command "echo Current status: $?"
run_command "echo Shell process ID: $$"

# Test comments (#)
echo -e "\nTesting comments"
run_command "echo This is a test # This should be ignored"

# Test file as input
echo -e "\nTesting file as input"
echo "echo Running command from file" > test_input_file
$SHELL test_input_file
rm test_input_file

echo "Testing complete"
