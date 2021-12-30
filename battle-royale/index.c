#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

/*
    UKOL:
    https://www.fit-wiki.cz/%C5%A1kola/p%C5%99edm%C4%9Bty/bi-pa1/pa1_zkouska_2016_11_1
*/

typedef struct {
    int x;
    int y;
} Enemy;

Enemy newEnemy(int x, int y) {
    Enemy e;
    e.x = x;
    e.y = y;

    return e;
}

typedef struct {
    Enemy* data;
    size_t used;
    size_t size;
} Enemies;

void initEnemies(Enemies* e, size_t initSize) {
    e->data = (Enemy*)malloc(sizeof(*(e->data)) * initSize);
    e->size = initSize;
    e->used = 0;
}

void pushEnemies(Enemies* e, Enemy en) {
    if(e->size == e->used) {
        e->size *= 2;
        e->data = (Enemy*)realloc(e->data, sizeof(*(e->data)) * e->size);
    }
    e->data[e->used] = en;
    e->used += 1;
}

void freeEnemies(Enemies* e) {
    free(e->data);
    e->data = NULL;
    e->size = e->used = 0;
}

double countMax(Enemies* e, int targetX, int targetY) {
    double currentMax = 0;
    double max = 0;

    for(size_t i = 0; i < e->used; i++) {
        currentMax = sqrt(pow((targetX - e->data[i].x), 2) + pow((targetY - e->data[i].y), 2));
        if(currentMax > max) {
            max = currentMax;
        }
    }

    return max;
}

int main(void) {

    char delimiter;

    printf("Nepritel:\n");
    if(scanf(" %c", &delimiter) != 1 || delimiter != '{') {
        printf("Nespravny vstup.\n");
        return 1;
    }

    Enemies enemies;
    initEnemies(&enemies, 10);

    int x, y;
    int scanfRes = 0;
    while((scanfRes = scanf( " [ %d , %d ] %c", &x, &y, &delimiter)) != EOF) {
        if(scanfRes != 3 || (delimiter != ',' && delimiter != '}')) {
            freeEnemies(&enemies);
            printf("Nespravny vstup.\n");
            return 1;
        }

        Enemy created = newEnemy(x, y);
        pushEnemies(&enemies, created);

        if(delimiter == '}') {
            break;
        }
    }

    printf("Cile:\n");
    while((scanfRes = scanf( " [ %d , %d ]", &x, &y)) != EOF) {
        if(scanfRes != 2) {
            freeEnemies(&enemies);
            printf("Nespravny vstup.\n");
            return 1;
        }

        printf("Max: %lf\n", countMax(&enemies, x, y));
    }

    freeEnemies(&enemies);

    return 0;
}
