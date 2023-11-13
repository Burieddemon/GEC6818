#include "dir.h"


char** isdir(char* path,int* num)
{
	DIR* dp;
	struct dirent* dr;
	dp = opendir(path);
	if (NULL == dp)
	{
		printf("open %s dir failed:%s", path, strerror(errno));
		exit(0);
	}
	char** filename = (char**)malloc(sizeof(char*) * 20);
	for (int i = 0; i < 20; i++)
	{
		filename[i] = (char*)malloc(sizeof(char) * 1024);
		memset(filename[i], '\0', sizeof(char) * 1024);
	}	
	int i = 0;
	while (dr =readdir(dp))
	{
		if ('.' == dr->d_name[0])
			continue;
		strcpy(filename[i], path);
		strcat(filename[i], "/");
		strcat(filename[i], dr->d_name);
		printf("%s\n", filename[i]);
		printf("%s", filename[i]);
		i++;		
	}
	*num = i - 1;
	return filename;
}