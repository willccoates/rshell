#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include <sys/wait.h>
using namespace std;

void WordParcing(string input,vector<string> &vec)
{
	string parsedword;
	for(int i = 0; i < input.size(); ++i)
	{
			if(input.at(i) == '\n'|| input.at(i) == ' ')
			{
					vec.push_back(parsedword);
					parsedword = "";
			}
			else
			{
					parsedword = parsedword + input.at(i);
			}
			

	}
	vec.push_back(parsedword);
}

void executeCommands(char** in)
{
	int pid = fork();
	if(pid == 0)
	{
		if(-1 == execvp(in[0],in))
			perror("exevp failed");
	}
	wait(0);
}

int main()
{
	string line;
	vector<string> parsevec;
	cout << "$ ";
	while(getline(cin,line))
	{
		if(line == "exit" || line == "Exit")
		{
			exit(0);
		}
		else
		{
			for(int i = 0; i < line.size(); ++i)
			{
				//fix this to stop when # key is found
				if(line.at(i) == '#')
				{
					line.erase(i,(line.size()-1) - (i));
				}
			}
			WordParcing(line, parsevec);
		}
		char ** usrIn = new char*[parsevec.size()+1];
		for(int i = 0; i <= parsevec.size(); ++i)
		{
			if(i == parsevec.size())
					usrIn[i] = '\0';
			else
			{
				usrIn[i] = new char[parsevec.at(i).size()+1];
				strcpy(usrIn[i],parsevec.at(i).c_str());
			}
		}
		executeCommands(usrIn);
		line = "";
		for(int i = 0; i < parsevec.size(); ++i)
		{
			delete usrIn[i];		
		}
		parsevec.clear();
		delete [] usrIn;
		cout << "$ ";
	}
}
