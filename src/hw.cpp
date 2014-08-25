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
#include <cstdlib>

using namespace std;

void stringParse(string usrinput, vector<string> &vec)
{
	char *cstr = new char[usrinput.size()+1];
	strcpy(cstr,usrinput.c_str());
	char *pch = strtok(cstr, " ");
	while(pch != NULL)
	{
		vec.push_back(pch);
		pch = strtok(NULL, " ");
	}
}

void executeCommands(const char *path, char** in, bool ampersand)
{
	int pid;
	if((pid = fork()) == -1)
		perror("fork failed");
	if(pid == 0)
	{
		if(-1 == execv(path, in))
			perror("exevp failed");
	}
	if(!ampersand)
	{
		if(wait(0) == -1)
			perror("wait failed");
	}
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

void changec(int i)
{
	signal(SIGINT,SIG_IGN);
	cout << endl;
}

int main()
{
	string input;
	bool amper = false;
	vector<string> strvec;
	vector<string> pathvec;
	vector<string> concatpath;
	char *temp = getenv("PATH");
	if(temp == NULL)
		perror("no path");
//	char *temp2;
//	char *temp3;
	char *concatstrpath;
	string concatstrpath2;
	string correctpath;
	int openInt = 0;
	string cd = "cd";

	while(1)
	{
		cout << "$ ";
		getline(cin, input);
		if(input != "")
		{
			if(SIG_ERR == signal(SIGINT,changec))
				perror("signal failed");
		
			if(input == "exit")
				exit(1);
			stringParse(input, strvec);
			for(unsigned int i = 0; i < strvec.size(); ++i)
			{
				if(strvec.at(i) == "&")
					amper = true;
				if(strvec.at(i) == "#")
					strvec.erase(strvec.begin()+i,strvec.end());

			}	

			char **usrIn = new char *[strvec.size()+1];
			for(unsigned int i = 0; i < strvec.size(); ++i)
			{
				usrIn[i] = new char[strvec.at(i).size()+1];
				strcpy(usrIn[i], strvec.at(i).c_str());
			}
			usrIn[strvec.size()] = '\0';
			if(strcmp(usrIn[0],cd.c_str()) == 0)
			{
				char *abpath = new char[1024];
				if(usrIn[1] != NULL)
				{
					if(getcwd(abpath,1024) == NULL)
						perror("getcwd failed");
					strcat(abpath,"/");
					strcat(abpath,usrIn[1]);
					cout << abpath << endl;
					if(chdir(abpath) == -1)
						perror("directory change failed");
				}
				else
				{
					char *home = getenv("HOME");
					if(home == NULL)
						perror("getenv failed");
//				cout << home << endl;
					if(chdir(home) == -1)
						perror("directory change failed");
				}
			}
			else
			{

				parsepath(temp,pathvec);

				for(unsigned int i = 0; i < pathvec.size(); ++i)
				{
					char buf[1024];
					strcpy(buf,pathvec.at(i).c_str());
					buf[pathvec.at(i).size()+1] = '\0';
					concatstrpath = strncat(buf,"/",1024);
					concatstrpath2 = strncat(concatstrpath, usrIn[0],1024);
					concatpath.push_back(concatstrpath2);	
			

					if((openInt = open(concatpath.at(i).c_str(), O_RDONLY)) != -1)
					{
						correctpath = concatpath.at(i);
						break;
					}
				}	
				if(openInt == -1)
					perror("open failed");
				char **fin = new char *[1024];		
				unsigned int j;
				for(j = 0; usrIn[j] != '\0'; ++j)
				{
					fin[j] = new char[1024];
					strcpy(fin[j],usrIn[j]);
				}
				fin[j] = '\0';
				executeCommands(correctpath.c_str(), fin, amper);
				delete [] fin;
			}
			for(unsigned int i = 0; i < strvec.size(); ++i)
				delete usrIn[i];
			strvec.clear();
			delete [] usrIn;
			input = "";
			correctpath = "";
			pathvec.clear();
			concatpath.clear();
		}
	}
		
}
