#! /bin/env sh

echo $1
echo "gcc -Wall -Werror -ansi $1 -o bin && ./bin"
gcc -Wall -Werror -ansi $1 -o bin && ./bin
