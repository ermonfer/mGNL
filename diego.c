#include "get_next_line.h" //#define BUFFER_SIZE 42
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h> // Para el write, en la practica no tienes que meterlo.
#include <stdio.h>

// TODO: Cambiar los for por whiles, eliminar headers no permitidos, sacar funciones auxiliares

// Es un strlen
static size_t len(const char *s)
{
    size_t i = 0;

    while (s[i++])
        ;
    return i;
}

// Es un concat
static char *concat(const char *s1, const char *s2)
{
    char *str;
    int i;
    int j;
    
    str = malloc(len(s1) + len(s2) + 1);
    if (!str) 
        return NULL;
    i = 0;
    while (str[i])
    {
        str[i] = s1[i];
        i++;
    }
    j = 0;
    while(str[j])
        str[i++] = s2[j++];
    str[i] = '\0';
    return str;
}

// Dada un strig aloca la primera linea, sin contar con el salto del linea
static char *get_line(const char *str)
{
    char    *line;
    int     pos;
    int     i;

    pos = 0;
    while (str[pos] && str[pos] != '\n')
    	pos++;
    line = malloc(pos+2);
    i = 0;
    while(i <= pos)
    {
        line[i] = str[i];
        i++;
    }
    line[pos + 1] = '\0';
    return line;
}

// Aloca y devuelve el resto de la cadena, sin contar el salto de linea, si la cadena acaba con el salto de linea, aloca una vacia.
static char *get_rest(char *str)
{
    char    *start = str;
    int     len_rest;
    char    *rest;
    int     i;

	start = str;
    while (*start && *start != '\n')
        start++;
    if (*start == '\n')
        start++;
    len_rest = len(start);
    rest = malloc((len_rest + 1));
    if (!rest) 
        return NULL;  
    i = 0;
    while (i < len_rest)
    {
        rest[i] = start[i];
        i++;
    }
    rest[len_rest] = '\0';
    return rest;
}

// Comprueba si una cadena tiene un salto de linea o no
static int has_line_end(const char *str)
{
    while (*str && *str != '\n')
        str++;
    return *str == '\n';
}

char *get_next_line(int fd)
{
    static char *acc; //Variable estatica, entiendo que es el acumulador.
    char        buffer[BUFFER_SIZE + 1];
    char        *line;
    char        *tmp;
    int         bytes;

    if (!acc) //Si acc es nulo aloca una cadena vacia. Lo es al comienzo porque es una estatica
    {
        acc = malloc(1);
        acc[0] = '\0';
    }
    else if (has_line_end(acc)) //Si el acumulador tiene un salto de linea, devuelve la linea y deja que el resto sea el nuevo acumulador
    {
        line = get_line(acc);
        tmp = get_rest(acc);
        free(acc);
        acc = tmp;
        return line;
    }
    while ((bytes = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes] = '\0';
        tmp = concat(acc, buffer);
        free(acc);
        acc = tmp; //Sobre el acumulador va metiendo nuevas lineas con concat
        if (has_line_end(acc)) //Hace el mismo if que antes
        {
            *line = get_line(acc);
            tmp = get_rest(acc);
            free(acc);
            acc = tmp;
            return line; //Aqui corta la funcion sin estar claro lo que vale acc.
        }       
    }
    if (bytes == 0 && *acc)
    {
        char *line = acc;
        acc = NULL;
        return line;
    }

    free(acc);
    acc = NULL;
    return NULL;
}

//! WARNING Main para probar 
int main() {
    int fd = open("texto.txt", O_RDONLY);
    char *line;
    while(1) {
        line = get_next_line(fd);
        if (!line) {
            printf("End!\n");
            return 0;
        }
        printf("%s", line);
        free(line);
    }

    return 0;
}
char *get_next_line(int fd) {
    static char *acc;
    char buffer[BUFFER_SIZE+1];

    if (!acc) {
        acc = malloc(1);
        acc[0] = '\0';
    } else if (has_line_end(acc)) {
        char *line = get_line(acc);
        char *tmp = get_rest(acc);
        free(acc);
        acc = tmp;
        return line;
    }

    int bytes;
    while ((bytes = read(fd, buffer, BUFFER_SIZE)) > 0) {
        buffer[bytes] = '\0';
        char *tmp = concat(acc, buffer);
        free(acc);
        acc = tmp;

        if (has_line_end(acc)) {
            char *line = get_line(acc);
            char *tmp = get_rest(acc);
            free(acc);
            acc = tmp;
            return line;
        }       
    }
    if (bytes == 0 && *acc) {
        char *line = acc;
        acc = NULL;
        return line;
    }

    free(acc);
    acc = NULL;
    return NULL;
}

//! WARNING Main para probar 
int main() {
    int fd = open("texto.txt", O_RDONLY);
    char *line;
    while(1) {
        line = get_next_line(fd);
        if (!line) {
            printf("End!\n");
            return 0;
        }
        printf("%s", line);
        free(line);
    }

    return 0;
}