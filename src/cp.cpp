#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdio>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <stdio.h>
#include "Timer.h"

using namespace std;

void funcOne(char *name1, char* name2)
{
	char var;
	ifstream infile;
	ofstream outfile;
	infile.open(name1);
	if(!infile.is_open())
	{
		cerr << "did not open";
	}
	outfile.open(name2);
	if(!outfile.is_open())
	{
		cerr << "did not open";
	}
	while(infile.good())
	{
		var = infile.get();
		if(infile.good())
			outfile.put(var);
	}	
}

void funcTwo(char *name1, char *name2)
{
	char var[1];
	memset(var,0,1);
	int in = 0;
	int out = 0;
	int n = 0;
	ifstream infile;
	ofstream outfile;
	in = open(name1, O_RDONLY);
	if(in == -1)
	{
		cerr << "did not open" << endl;
	}
	out = open(name2, O_WRONLY | O_CREAT);
	if(out == -1)
	{
		cerr << "did not open" << endl;
	}
	while((n = read(in,var,1)) > 0)
	{	
		write(out,var,1);
	}
}

void funcThree(char *name1, char *name2)
{
	char var[BUFSIZ];
	memset(var,0,BUFSIZ);
	int in = 0;
	int out = 0;
	int n = 0;
	ifstream infile;
	ofstream outfile;
	in = open(name1, O_RDONLY);
	if(in == -1)
	{
		cerr << "did not open" << endl;
	}
	out = open(name2, O_WRONLY | O_CREAT);
	if(out == -1)
	{
		cerr << "did not open" << endl;
	}
	while((n = read(in,var,BUFSIZ)) > 0)
	{	
		write(out,var,BUFSIZ);
	}
}


int main(int argc, char ** argv)
{
	Timer t;
	double eTime;
	t.start();
	funcOne(argv[1],argv[2]);
	t.elapsedUserTime(eTime);
	cout << eTime << endl;


	Timer tt;
	double eeTime;
	tt.start();
	funcTwo(argv[1],argv[2]);
	tt.elapsedUserTime(eeTime);
	cout << eeTime << endl;


	Timer ttt;
	double eeeTime;
	ttt.start();
	funcThree(argv[1],argv[2]);
	ttt.elapsedUserTime(eeeTime);
	cout << eeeTime << endl;

	if(argc == 3)
	{
		funcThree(argv[1],argv[2]);
	}
	else
	{
		if(argv[3] == "1" )
			funcOne(argv[1],argv[2]);
		if(argv[3] == "2")
			funcTwo(argv[1],argv[2]);
		if(argv[3] == "3")
			funcThree(argv[1],argv[2]);
	}

	return 0;
}
