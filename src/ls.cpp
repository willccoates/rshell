#include <iostream>
#include <string>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>

using namespace std;

#define NOFLAG 0
#define a 2
#define l 4
#define R 8

void noFlagLs()
{
	char const *dirName = ".";
	DIR *dirp;
	if(!(dirp = opendir(dirName)))
	{
		cerr << "Error(" << errno << ") opening" << dirName << endl;		
	}
	dirent *direntp;
	while((direntp = readdir(dirp)))
	{
		if((direntp->d_name)[0] != '.')
			cout << direntp->d_name << " ";
	}
	closedir(dirp);
	cout << endl;
}

void aFlagLs()
{
	char const *dirName = ".";
	DIR *dirp;
	if(!(dirp = opendir(dirName)))
	{
		cerr << "Error(" << errno << ") opening " << dirName << endl;
	}
	dirent *direntp;
	while((direntp = readdir(dirp)))
	{
		cout << direntp->d_name << " ";
	}
	closedir(dirp);
	cout << endl;
}

//void lFlagLs()
//{
			
//}
int main(int argc, char **argv)
{
	if(argc == 1)
			noFlagLs();
	if(argc >= 2)
	{
		if(argv[1][0] == '-')
		{

			for(int i = 0; i < argc; ++i)
			{
				for(int j = 0; argv[i][j] != '\0'; ++j)
				{
					if(argv[i][j] == 'a')
					{
						aFlagLs();		
					}
				//	else if(argv[i][j] == 'l')
				//	else 
				//	{
							
				//	}
				}
			}
		}
	}	
	else
	{
		return 0;		
	}
}
