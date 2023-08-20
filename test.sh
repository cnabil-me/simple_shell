#/bin/bash
# gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
gcc *.c -o hsh

# echo "echo "qwerty" | ./hsh________________________________"
# ./hsh echo "qwerty" | ./hsh
# ./hsh echo "qwerty" | ./././hsh


# echo "echo "/bin/ls" | ./hsh________________________________"
# ./hsh echo "/bin/ls" | ./hsh

echo "cat AUTHORS________________________________"
./hsh | cat AUTHORS

echo "/bin/ls________________________________"
./hsh | /bin/ls

echo "ls -l /tmp ________________________________"
./hsh | ls -l /tmp

echo "env ________________________________"
./hsh | env


echo "SET AND UNSET ENV ___________________________"
./hsh | echo "Setting MY_VARIABLE to 'Hello, World!'"
./hsh | export MY_VARIABLE="Hello, World!"
./hsh | echo "Updated value of MY_VARIABLE: $MY_VARIABLE"
./hsh | echo "Unsetting MY_VARIABLE"
./hsh | unset MY_VARIABLE
./hsh | echo "Value of MY_VARIABLE after unset: $MY_VARIABLE"


# echo "EXIT 19 ________________________________"
# exit 19


echo "________________________________"
