#include "get_next_line.h"
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
int main() {
    int fd = open("texto.txt", O_RDONLY);
    int fd2 = open("texto2.txt", O_RDONLY);
    char *line;
    while(1) {

        line = get_next_line(fd);
        if (!line) {
            return 0;
        }
        printf("%s", line);
        free(line);
        line = get_next_line(fd2);
        if (!line) {
            return 0;
        }
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
