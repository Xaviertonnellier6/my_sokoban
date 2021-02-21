/*
** EPITECH PROJECT, 2021
** my sokoban
** File description:
** bootstrap
*/

#include "sok.h"

char **double_tab(char **str, char *buff)
{
    int i = 0;
    int backline = 0;
    int a = 0;
    int b = 0;

    while (buff[i] != '\0') { if (buff[i] == '\n') backline++;
        if (buff[i] != 'O' && buff[i] != 'X' && buff[i] != ' '
            && buff[i] != '#' && buff[i] != 'P' && buff[i] != '\n')
            endwin(), exit(84);
        i++;
    } str = malloc(sizeof(char *) * backline + 1), i = 0;
    while (buff[i] != '\0') {
        if (buff[i] == '\n') str[b] = malloc(sizeof(char) * a + 1), b++, a = 0;
        i++, a++;
    } str[b] = malloc(sizeof(char) * a + 1), b = 0, a = 0, i = 0;
    while (buff[i] != '\0') {
        if (buff[i] == '\n') str[a][b] = '\0', b = 0, a++, i++;
        str[a][b] = buff[i], i++, b++;
    } str[a + 1] = NULL;
    return (str);
}

char **create_str(char **str, char *filepath)
{
    int ret = 0;
    int op = 0;
    char *buff;
    struct stat sb;

    if (stat(filepath, &sb) == -1)
        endwin(), exit (84);
    buff = malloc(sizeof(char) * sb.st_size + 1);
    op = open(filepath, O_RDONLY);
    if (op <= -1)
        endwin(), exit (84);
    ret = read(op, buff, sb.st_size);
    buff[ret] = '\0';
    str = double_tab(str, buff);
    free (buff);
    return (str);
}

int count_box(obj_t *obj, char **str)
{
    obj->nb_fall = 0;
    int y = 0;
    int x = 0;

    while (str[y] != NULL) {
        while (str[y][x] != '\0') {
            check_box(y, x, str, obj);
            x++;
        }
        x = 0, y++;
    }
    if (!(obj->fall = malloc(sizeof(obj->fall) * obj->nb_fall + 1)))
        endwin(), exit(84);
    count_boxs(obj, str);
}

int reset(char *filepath)
{
    int *pos = malloc(sizeof(int) * 2);
    char **str = create_str(str, filepath);
    int i = 0;
    obj_t obj;

    check_if_vl_map(str);
    count_box(&obj, str);
    my_win(str, filepath, pos, &obj);
    free(pos), free(str);
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (84);
    if (av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0') {
        my_printf("USAGE\n");
        my_printf("     ./my_sokoban map\n");
        my_printf("DESCRIPTION\n");
        my_printf("     map file representing the warehouse map, contai");
        my_printf("ning '#'");
        my_printf(" for walls,\n");
        my_printf("         'P' for the player, 'X' for boxes and");
        my_printf(" 'O' for storage locations.\n");
        return (0);
    }
    initscr();
    curs_set(0);
    reset(av[1]);
    return (0);
}