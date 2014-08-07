rshell
======
general:
	This program mimics the bash shell by taking in commands and performing their tasks as usual. You can perfrom tasks such as 
	-ls -lists the files in a directory
			-with all flags
	-cat -displays everything in a file
	-echo -prints out what is passed in as a parameter
	-mkdir -makes a new directory
	-# -everything after this is a comment and does not get executed
	-& -runs program in background allowing terminal to continue
	-exit -typing exit will kill the program
	-rm -removes a file
	-rmdir -removes a directory
	-for more features view the /bin page on your computer

how to run:
	-to run you just need to type make, this will build, compile and run the program
	-to clean the file, you type make clean and this will discard executibles and object files

bugs:
	-when an error is produced, it sometimes gets printed on the line with the "$" and the next line does not have a "$", just need to hit enter again
	-# right after a command does not work properly
		-for example (ls# -a) will not execute ls
	-when "exit" is typed, sometimes it will need to be typed twice, but it will still exit
