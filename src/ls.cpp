#include <iostream>
#include <string>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <pwd.h>
#include <time.h>
#include <cstring>
#include <cstdlib>
#include <stack>

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
		perror("Error opening");		
		//ADD PERROR STATEMENT!!!!!!
	}
	dirent *direntp;
		//ADD PERROR STATEMENT!!!!!!
	struct stat s;
	while((direntp = readdir(dirp)))
	{
		if(direntp == NULL)
			perror("readdir failed");
		if((direntp->d_name)[0] != '.')
		{
			if(stat(direntp->d_name, &s) == -1)
				perror("stat failed");
			if(S_ISDIR(s.st_mode))
				printf("\033[0;34m%s \033[0m",direntp->d_name);
			//cout << direntp->d_name << " ";
			else if((s.st_mode & S_IEXEC) != 0)
				printf("\033[0;32m%s ",direntp->d_name);
			else
				printf("\033[0m%s ",direntp->d_name);
		}
	}
		//ADD PERROR STATEMENT!!!!!!
	if(closedir(dirp) == -1)
		perror("closedir failed");
	cout << endl;
	//exit(0);
}

void aFlagLs()
{
	//const string direct = "\033[0"
	char const *dirName = ".";
	DIR *dirp;
	if(!(dirp = opendir(dirName)))
	{
		//ADD PERROR STATEMENT!!!!!!
		perror("Error opening ");
	}
	dirent *direntp;
		//ADD PERROR STATEMENT!!!!!!
	struct stat s;
	while((direntp = readdir(dirp)))
	{
	//	cout << direntp->d_name << endl;
		if(direntp == NULL)
			perror("readdir failed");
		if(stat(direntp->d_name, &s) == -1)
			perror("stat failed");
		if(S_ISDIR(s.st_mode))
		{
			if((direntp->d_name)[0] == '.')
				printf("\033[0;34m\033[0;47m%s \033[0m",direntp->d_name);
			else
				printf("\033[0;34m%s \033[0m",direntp->d_name);
		}
		else if((s.st_mode & S_IEXEC) != 0)
			printf("\033[0;32m%s ",direntp->d_name);
		else if((direntp->d_name)[0] == '.')
		{
			cout << "in hidden else if" << endl;
			printf("\033[7;37m%s ",direntp->d_name);
		}
		else
			printf("%s ",direntp->d_name);
		//cout << direntp->d_name << " ";
	}
		//ADD PERROR STATEMENT!!!!!!
	if(closedir(dirp) == -1)
		perror("closedir failed");
	cout << endl;
	exit(0);
}

void lFlagLs()
{
	char const *dirName = ".";
	DIR *dirp;
	if(!(dirp = opendir(dirName)))
	{
		//ADD PERROR STATEMENT!!!!!!
		perror("Error opening ");
	}
	dirent *direntp;
		//ADD PERROR STATEMENT!!!!!!
	struct stat s;
	while((direntp = readdir(dirp)))
	{
		if(direntp == NULL)
			perror("readdir failed");
		if((direntp->d_name)[0] != '.')
		{
			if((stat(direntp->d_name,&s)) == -1)
				perror("stat not called properly");
			else
			{
				if(S_ISDIR(s.st_mode))
					cout << 'd';
				else
					cout << '-';
				if(s.st_mode & S_IRUSR)
					cout << 'r';
				else
					cout << '-';
				if(s.st_mode & S_IWUSR)
					cout << 'w';
				else
					cout << '-';
				if(s.st_mode & S_IXUSR)
					cout << 'x';
				else
					cout << '-';
				
				if(s.st_mode & S_IRGRP)
					cout << 'r';
				else
					cout << '-';
				if(s.st_mode & S_IWGRP)
					cout << 'w';
				else
					cout << '-';
				if(s.st_mode & S_IXGRP)
					cout << 'x';
				else
					cout << '-';
				

				if(s.st_mode & S_IROTH)
					cout << 'r';
				else
					cout << '-';
				if(s.st_mode & S_IWOTH)
					cout << 'w';
				else
					cout << '-';
				if(s.st_mode & S_IXOTH)
					cout << 'x';
				else
					cout << '-';

				struct passwd *result;
				struct passwd *result2;
				
				time_t t = s.st_mtime;
				const char *format = "%b %d %I:%M";
				struct tm tt;
				char buf[1024];
				localtime_r(&t, &tt);
				strftime(buf,1024,format,&tt);

				uid_t uid;
				gid_t gid;
				uid = geteuid();
				gid = getegid();
				if((result = getpwuid(uid)) == NULL)
					perror("getpwuid failed");
				if((result2 = getpwuid(gid)) == NULL)
					perror("getpwuid failed");
				cout << " " << result->pw_name;
				cout << " " << result2->pw_name;
				cout << " " << s.st_size;
				cout << " " << buf;
				if(S_ISDIR(s.st_mode))
					printf(" \033[0;34m%s\033[0m",direntp->d_name);
			
				else if((s.st_mode & S_IEXEC) != 0)
					printf(" \033[0;32m%s\033[0m",direntp->d_name);
				else
					printf(" \033[0m%s",direntp->d_name);
				cout << endl;
			}
		}
	}

		//ADD PERROR STATEMENT!!!!!!
	if(closedir(dirp) == -1)
		perror("close failed");
	cout << endl;
	exit(0);
}

void alFlags()
{
	char const *dirName = ".";
	DIR *dirp;
	if(!(dirp = opendir(dirName)))
	{
		//ADD PERROR STATEMENT!!!!!!
		perror("Error opening ");
	}
	dirent *direntp;
		//ADD PERROR STATEMENT!!!!!!
	struct stat s;
	while((direntp = readdir(dirp)))
	{
		if(direntp == NULL)
			perror("readdir failed");
		
			if((stat(direntp->d_name,&s)) == -1)
				perror("stat not called properly");
			else
			{
				if(S_ISDIR(s.st_mode))
					cout << 'd';
				else
					cout << '-';
				if(s.st_mode & S_IRUSR)
					cout << 'r';
				else
					cout << '-';
				if(s.st_mode & S_IWUSR)
					cout << 'w';
				else
					cout << '-';
				if(s.st_mode & S_IXUSR)
					cout << 'x';
				else
					cout << '-';
				
				if(s.st_mode & S_IRGRP)
					cout << 'r';
				else
					cout << '-';
				if(s.st_mode & S_IWGRP)
					cout << 'w';
				else
					cout << '-';
				if(s.st_mode & S_IXGRP)
					cout << 'x';
				else
					cout << '-';
				

				if(s.st_mode & S_IROTH)
					cout << 'r';
				else
					cout << '-';
				if(s.st_mode & S_IWOTH)
					cout << 'w';
				else
					cout << '-';
				if(s.st_mode & S_IXOTH)
					cout << 'x';
				else
					cout << '-';

				struct passwd *result;
				struct passwd *result2;
				
				time_t t = s.st_mtime;
				const char *format = "%b %d %I:%M";
				struct tm tt;
				char buf[1024];
				localtime_r(&t, &tt);
				strftime(buf,1024,format,&tt);

				uid_t uid;
				gid_t gid;
				uid = geteuid();
				gid = getegid();
				if((result = getpwuid(uid)) == NULL)
					perror("getpwuid failed");
				if((result2 = getpwuid(gid)) == NULL)
					perror("getpwuid failed");
				cout << " " << result->pw_name;
				cout << " " << result2->pw_name;
				cout << " " << s.st_size;
				cout << " " << buf;
				if(S_ISDIR(s.st_mode))
				{
					if((direntp->d_name)[0] == '.')
						printf(" \033[0;34m\033[0;47m%s \033[0m",direntp->d_name);
					else
						printf(" \033[0;34m%s \033[0m",direntp->d_name);
				}
				else if((s.st_mode & S_IEXEC) != 0)
					printf(" \033[0;32m%s \033[0m",direntp->d_name);
				else if((direntp->d_name)[0] == '.')
				{
					printf(" \033[7;37m%s ",direntp->d_name);
				}
				else
					printf(" %s ",direntp->d_name);
				cout << endl;
			}
		}
	//}

		//ADD PERROR STATEMENT!!!!!!
	if(closedir(dirp) == -1)
		perror("close failed");
	cout << endl;
	exit(0);
}

//
//Create R flag function
//
void rFlags()
{
	char const *dirName = ".";
	DIR *dirp;
	if(!(dirp = opendir(dirName)))
	{
		//ADD PERROR STATEMENT!!!!!!
		perror("Error opening ");
	}
	dirent *direntp;
		//ADD PERROR STATEMENT!!!!!!
	struct stat s;
	stack<dirent> stck;
	while((direntp = readdir(dirp)))
	{
		//cout << "in while loop" << endl;
		if(direntp == 0)
		{
			//cout << "direntp == 0" << endl;
			if(!errno)
				perror("readdir failed");		
			else
			{
				closedir(dirp);
				return;
			}
		}

		if((stat(direntp->d_name,&s)) == -1)
			perror("stat not called properly");
		else
		{
			//cout << "in else" << endl;
			if(S_ISDIR(s.st_mode))
			{
				//cout << "in directory check" << endl;
				noFlagLs();
				cout << endl;
				char *buf = new char[1024];
				getcwd(buf, 1024);
				strcat(buf, direntp->d_name);
				chdir(buf);
				cout << buf << ":" << endl;
				rFlags();
				delete [] buf;
				closedir(dirp);
				return;
			}
		}
	}
}

int main(int argc, char **argv)
{
	string A = "-a";
	string L = "-l";
	string r = "-R";
	string AL = "-al";
	string LA = "-la";
	string Ar = "-aR";
	string rA = "-Ra";
	string Lr = "-lR";
	string rL = "-Rl";

	if(argc == 1)
			noFlagLs();
	if(argc >= 2)
	{
		if(argv[1][0] == '-')
		{

			for(int i = 1; i < argc; ++i)
			{
				for(int j = 0; argv[i][j] != '\0'; ++j)
				{
					if(argc == 2)
					{
						if(strlen(argv[i]) == 2)
						{
							if(strcmp(argv[i],A.c_str()) == 0)
								aFlagLs();
							if(strcmp(argv[i],L.c_str()) == 0)
								lFlagLs();
							if(strcmp(argv[i],r.c_str()) == 0)
							{
								cout << ".:" << endl;
								noFlagLs();
								//cout << endl << "hello" << endl;
								rFlags();
								exit(0);
							}
						}
						if(strlen(argv[i]) == 3)
						{
							if(strcmp(argv[i],AL.c_str()) == 0)
								alFlags();
							if(strcmp(argv[i],LA.c_str()) == 0)
								alFlags();
				
						//	if(strcmp(argv[i],Ar.c_str()) == 0)
						//		aRFlags();
						//	if(strcmp(argv[i],rA.c_str()) == 0)
						//		aRFlags();
						//	if(strcmp(argv[i],Lr.c_str()) == 0)
						//		lRFlags();
						//	if(strcmp(argv[i],rL.c_str()) == 0)
						//		lRFlags();
	
						}
					}
					else if(argc == 3)
					{
						if(strcmp(argv[1], A.c_str()) == 0
							&& strcmp(argv[2], L.c_str()) == 0)	
							alFlags();
						if(strcmp(argv[1], L.c_str()) == 0
							&& strcmp(argv[2], A.c_str()) == 0)
							alFlags();

					//	if(strcmp(argv[1], L.c_str()) == 0
					//		&& strcmp(argv[2],r.c_str()) == 0)	
					//		lRFlags();
					//	if(strcmp(argv[1], r.c_str()) == 0
					//		&& strcmp(argv[2],L.c_str()) == 0)	
					//		lRFlags();

					//	if(strcmp(argv[1], A.c_str()) == 0
					//		&& strcmp(argv[2],r.c_str()) == 0)	
					//		aRFlags();
					//	if(strcmp(argv[1], r.c_str()) == 0
					//		&& strcmp(argv[2],A.c_str()) == 0)	
					//		aRFlags();
					}
					//else if(argc == 4)
					//{
					//	if(strcmp(argv[1],A.c_str()) == 0
					//		&& strcmp(argv[2],L.c_str()) == 0
					//		&& strcmp(argv[3],r.c_str()) == 0)
					//		aLRFlags();
					//	if(strcmp(argv[1],A.c_str()) == 0
					//		&& strcmp(argv[2],r.c_str()) == 0
					//		&& strcmp(argv[3],L.c_str()) == 0)
					//		aLRFlags();	
					//	if(strcmp(argv[1],L.c_str()) == 0
					//		&& strcmp(argv[2],r.c_str()) == 0
					//		&& strcmp(argv[3],A.c_str()) == 0)
					//		aLRFlags();		
					//	if(strcmp(argv[1],L.c_str()) == 0
					//		&& strcmp(argv[2],A.c_str()) == 0
					//		&& strcmp(argv[3],r.c_str()) == 0)
					//		aLRFlags();		
					//	if(strcmp(argv[1],r.c_str()) == 0
					//		&& strcmp(argv[2],A.c_str()) == 0
					//		&& strcmp(argv[3],L.c_str()) == 0)
					//		aLRFlags();		
					//	if(strcmp(argv[1],r.c_str()) == 0
					//		&& strcmp(argv[2],L.c_str()) == 0
					//		&& strcmp(argv[3],A.c_str()) == 0)
					//		aLRFlags();		
					//}
				}
			}
		}
		else
		{
			char *buf = new char[1024];
			getcwd(buf,1024);
			strcat(buf,"/");
			strcat(buf,argv[1]);
			chdir(buf);
			noFlagLs();
		}
	}	
	else
	{
		return 0;		
	}
}

