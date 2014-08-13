all: rshell ls cp
rshell:
	g++ -Wall -Werror -ansi -pedantic src/main.cpp -o ./bin/rshell
ls:
	g++ -Wall -Werror -ansi -pedantic src/ls.cpp -o ./bin/ls
cp:
	g++ -Wall -Werror -ansi -pedantic src/cp.cpp -o ./bin/cp
