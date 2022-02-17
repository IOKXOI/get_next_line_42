#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"


int main()
{
//	int fd1;
//	int fd2;
	int fd3;
//	int fd4;
	int i = 0;
	char *str;

	str = NULL;

		fd3 = open("./test3", O_RDONLY);
	//	fd1 = open("test1", O_RDONLY);
	//	fd2 = open("test2", O_RDONLY);
	//	fd4 = open("test4", O_RDONLY);
	while (i < 10)
	{
		if (i == 0)
		{
			str = get_next_line(fd3);
		}
		if (i == 1)
		{
			str = get_next_line(fd3);
		}
		if (i == 2)
		{
			str = get_next_line(fd3);
		}
		if (i == 3)
		{
			str = get_next_line(fd3);
		}
		if (i == 4)
		{
			str = get_next_line(fd3);
		}
		if (i == 5)
		{
			str = get_next_line(fd3);
		}
printf("LIGNE RETOURNEE =  %s\n", str);
printf("------------------------------i = %d \n" , i);

		free(str);
		i++;
	}
	return 0;
}
