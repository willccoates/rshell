#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/param.h>
#include <stdlib.h>

using namespace std;

void stringParse(string usrinput, vector<string> &vec)
{
	char str[usrinput.size()+1];
	strcpy(str,usrinput.c_str());
	char *pch = strtok(str, " ");
	while(pch != NULL)
	{
		vec.push_back(pch);
		pch = strtok(NULL, " ");
	}
}

void executeCommands(const char *path, char** in, bool ampersand)
{
	int pid = fork();
	if(pid == 0)
	{
		if(-1 == execv(path, in))
			perror("exevp failed");
	}
	if(!ampersand)
		wait(0);
}

void parsepath(char *path, vector<string> &p)
{
	string parsedpath;
	int i;
	for(i = 0; path[i] != '\0'; ++i)
	{
		if(path[i] == ':')
		{
			p.push_back(parsedpath);
			parsedpath = "";
		}
		else
			parsedpath += path[i];
		
	}
	parsedpath += path[i];
	p.push_back(parsedpath);
		
}

int main()
{
	string input;
	bool amper = false;
	vector<string> strvec;
	vector<string> pathvec;
	vector<string> concatpath;
	char *temp = getenv("PATH");
	char *temp2;
	char *temp3;
	char *concatstrpath;
	string concatstrpath2;
	string correctpath;
	int openInt = 0;

	while(1)
	{
		cout << "$ ";
		getline(cin, input);
		if(input == "exit")
			break;
		stringParse(input, strvec);
		for(int i = 0; i < strvec.size(); ++i)
		{
			if(strvec.at(i) == "&")
				amper = true;
			if(strvec.at(i) == "#")
				strvec.erase(strvec.begin()+i,strvec.end());

		}

		char **usrIn = new char *[strvec.size()+1];
		for(int i = 0; i < strvec.size(); ++i)
		{
			usrIn[i] = new char[strvec.at(i).size()+1];
			strcpy(usrIn[i], strvec.at(i).c_str());
		}
		usrIn[strvec.size()] = '\0';
		if(usrIn[0] == "cd")
		{
			char *abpath;
			getcwd(abpath,1024);
		//	cout << abpath << endl;
			strcat(abpath,usrIn[1]);
		//	cout << abpath << endl;
			if(chdir(abpath) == -1)
				perror("directory change failed");
		}
		else
		{

			parsepath(temp,pathvec);

			for(int i = 0; i < pathvec.size(); ++i)
			{
				char buf[1024];
				strcpy(buf,pathvec.at(i).c_str());
				buf[pathvec.at(i).size()+1] = '\0';
				concatstrpath = strncat(buf,"/",1024);
				concatstrpath2 = strncat(concatstrpath, usrIn[0],1024);
				concatpath.push_back(concatstrpath2);	
			

				if(openInt = open(concatpath.at(i).c_str(), O_RDONLY) != -1)
				{
					correctpath = concatpath.at(i);
					break;
				}
			}
			if(openInt == -1)
				perror("open failed");
			char **fin = new char *[1024];		
			int i;
			for(i = 0; usrIn[i] != '\0'; ++i)
			{
				fin[i] = new char[1024];
				strcpy(fin[i],usrIn[i]);
			}
			fin[i] = '\0';
			executeCommands(correctpath.c_str(), fin, amper);
			delete [] fin;
		}
		for(int i = 0; i < strvec.size(); ++i)
			delete usrIn[i];
		strvec.clear();
		delete [] usrIn;
		input = "";
		correctpath = "";
		pathvec.clear();
		concatpath.clear();
	}
		
}
