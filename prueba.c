#include "get_next_line_bonus.h"
#include <stdio.h>

//! WARNING Main para probar 
int main() {
    int fd = open("file", O_RDONLY);
    char *line;

    while(1) {
        line = get_next_line(fd);
        if (!line) {
            break ;
        }
        printf("%s", line);
        free(line);
    }
    close(fd);
    fd = open("texto.txt", O_RDONLY);
    while(1) {
        line = get_next_line(fd);
        if (!line) {
            return 0;
        }
        printf("%s", line);
        free(line);
    }
    close(fd); 
    return 0;
}
