#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define lines 25
#define columns 80
#define live '*'
#define dead '.'

void input(char **points);
void print(char **points);
void proverka(char **points);
int schet_sosed(char **points, int y, int x);

int main(void) {
    char **points = malloc((int)lines * sizeof(char *) + (int)lines * (int)columns * sizeof(char));
    char *first = (char *)(points + lines);
    for (int y = 0; y < (int)lines; ++y) points[y] = first + (int)columns * y;
    printf("|                   Please input '.' or '*' on field 25x80:                    |\n");
    printf("|------------------------------------------------------------------------------|\n");
    input(points);
    while (1) {
        print(points);
        usleep(50000);
        proverka(points);
    }
    free(points);
    return 0;
}

void input(char **points) {
    for (int y = 0; y < (int)lines; ++y) {
        for (int x = 0; x < (int)columns; ++x) {
            scanf("%c", &points[y][x]);
            if (points[y][x] == '\n') scanf("%c", &points[y][x]);
        }
    }
}

void print(char **points) {
    for (int y = 0; y < (int)lines; ++y) {
        for (int x = 0; x < (int)columns; ++x) {
            if (x == (int)columns - 1) {
                printf("%c\n", points[y][x]);
            } else {
                printf("%c", points[y][x]);
            }
        }
    }
    printf("|------------------------------------------------------------------------------|\n");
}

void proverka(char **points) {
    char **tmpoints = malloc((int)lines * sizeof(char *) + (int)lines * (int)columns * sizeof(char));
    char *tmpfirst = (char *)(tmpoints + lines);
    for (int t = 0; t < (int)lines; ++t) tmpoints[t] = tmpfirst + (int)columns * t;
    for (int y = 0; y < (int)lines; ++y) {
        for (int x = 0; x < (int)columns; ++x) {
            if (schet_sosed(points, y, x) == 3)
                tmpoints[y][x] = live;
            else if (schet_sosed(points, y, x) < 2 || schet_sosed(points, y, x) > 3)
                tmpoints[y][x] = dead;
            else
                tmpoints[y][x] = points[y][x];
        }
    }
    for (int y = 0; y < (int)lines; ++y) {
        for (int x = 0; x < (int)columns; ++x) {
            points[y][x] = tmpoints[y][x];
        }
    }
    free(tmpoints);
}

int schet_sosed(char **points, int y, int x) {
    int count = 0;
    for (int i = y - 1; i <= y + 1; ++i) {
        int tmpi = i;
        if (i == -1)
            i = (int)lines - 1;
        else if (i == (int)lines)
            i = 0;
        for (int j = x - 1; j <= x + 1; ++j) {
            int tmpj = j;
            if (j == -1)
                j = (int)columns - 1;
            else if (j == (int)columns)
                j = 0;
            if (points[i][j] == live) {
                ++count;
                if (i == y && j == x) --count;
            }
            j = tmpj;
        }
        i = tmpi;
    }
    return count;
}