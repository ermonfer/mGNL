#include "get_next_line_bonus.h"
#include <stdio.h>

//int main(void)
//{   
    //char *str1 = ft_strdup("patatas\nfritas");
	//char *str = get_line(&str1);
	//printf("%s", str);
    //printf("%s", str1);
    //free(str);
    //free(str1);
    //return 0;
//}


//! WARNING Main para probar 
int main(void)
{
    int fd = open("texto.txt", O_RDONLY);
    int fd2 = open("texto2.txt", O_RDONLY);
    char *line = get_next_line(fd);
    char *line2 = get_next_line(fd2);
    char *line3;
    while (line || line2)
    {
        if (line)
        {
            printf("%s", line);
            free(line);
            line = get_next_line(fd);
        }
        if (line2)
        {
            printf("%s", line2);
            free(line2);
            line2 = get_next_line(fd2);
        }
        line3 = get_next_line(0);
        printf("%s", line3);
        free(line3);
    }
}
