#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
    MAPA
    vstup:
    [
        [0, 1, 1, 1],
        [0, 1, 0, 0],
        [0, 0, 1, 0],
        [1, 1, 0, 0]
    ]
    program: vyhledat ostrovy s cislem "1" a tyto ostrovy smazat (udelat z nich 0)
    ostrov: misto s jednickami, ktere neni spojene s koncema mapy
    mapa: muze byt jakkoliv velka, dulezite je aby byla na vstupu zadana jako 2d pole
    teorie: rozdelit si mapu na ostrovy, detekovat hrany ostrovu, odstranit cele ostrovy, ktere hranu nemaji na okraji mapy
    vystup:
    [
        [0, 1, 1, 1],
        [0, 1, 0, 0],
        [0, 0, 0, 0],
        [1, 1, 0, 0]
    ]
*/

typedef struct {
    int x;
    int y;
    int value;
    int visited;
} Position;

Position newPosition(int x, int y, int val) {
    Position a;
    a.value = val;
    a.x = x;
    a.y = y;
    a.visited = 0;

    return a;
}

typedef struct {
    Position* data;
    size_t size;
    size_t used;
} Island;

void initIsland(Island* i, size_t initSize) {
    //O(1)
    i->data = (Position*)malloc(sizeof(*(i->data)) * initSize);
    i->size = initSize;
    i->used = 0;
}

void pushIsland(Island* i, Position pos) {
    //O(1)
    if(i->size == i->used) {
        i->size *= 2;
        i->data = (Position*)realloc(i->data, sizeof(*(i->data)) * i->size);
    }

    i->data[i->used] = pos;
    i->used += 1;
}

void freeIsland(Island* i) {
    //O(1)
    free(i->data);
    i->data = NULL;
    i->size = i->used = 0;
}

typedef struct {
    Position** data;
    size_t size;
    size_t used;
    int cols;
    int rows;
} Map;

void initMap(Map* m, size_t initSize) {
    //O(1)
    m->data = (Position**)malloc(sizeof(*(m->data)) * initSize);
    m->size = initSize;
    m->used = 0;
}

void pushMap(Map* m, Position pos, int isLast) {
    //O(1)
    if(m->size == m->used) {
        m->size *= 2;
        m->data = (Position**)realloc(m->data, sizeof(*(m->data)) * m->size);
    }

    m->data[pos.y][pos.x] = pos;
    m->used += 1;

    m->rows = m->rows > pos.x ? m->rows : pos.x;
    m->cols = m->cols > pos.y ? m->cols : pos.y;
}

void freeMap(Map* m) {
    //O(1)
    free(m->data);
    m->data = NULL;
    m->size = m->used = 0;
}

int readMap(Map* m) {
    //O(n^2)

    char deli;
    if(scanf(" %c", &deli) != 1 || deli != '[') {
        printf("Nespravny vstup.\n");
        return 0;
    }

    int scanfRes;
    char startArr, endArr;
    int x = 0, y = 0;

    while((scanfRes = scanf(" %c", &startArr)) != EOF) {
        if(scanfRes != 1 || startArr != '[') {
            printf("Nespravny vstup.\n");
            return 0;
        }

        char inArrDeli;
        int num;
        int inArrScanfRes;
        while((inArrScanfRes = scanf(" %d %c", &num, &inArrDeli)) != EOF) {
            if(inArrScanfRes != 2 || num < 0 || num > 1 || (inArrDeli != ',' && inArrDeli != ']')) {
                printf("Nespravny vstup.\n");
                return 0;
            }

            Position pos = newPosition(x, y, num);
            x++;

            if(inArrDeli == ']') {
                pushMap(m, pos, 1);
                break;
            } else {
                pushMap(m, pos, 0);
            }
        }

        y++;
        x = 0;

        if(scanf(" %c", &deli) != 1 || (deli != ',' && deli != ']')) {
            printf("Nespravny vstup.\n");
            return 0;
        }

        if(deli == ']') {
            break;
        }
        
    }

    return 1;

}

void printMap(Map* m) {
    //O(n^2)
    printf("[\n");
    for(size_t i = 0; i < m->rows; i++) {
        printf("  [");
        for(size_t j = 0; j < m->cols; j++) {
            printf("%d", m->data[i][j].value);
            printf("%s", j == m->cols - 1 ? ", " : "");
        }
        printf("]%s", i == m->rows - 1 ? ",\n" : "");
    }
    printf("\n]\n");
}

/*
    [1, 0, 0],
    [1, 0, 0],
    [1, 1, 1]
*/

int main(void) {
    Map m;
    initMap(&m, 10);

    printf("Mapa: \n");
    if(!readMap(&m)) {
        freeMap(&m);
        return 1;
    }

    printMap(&m);

    freeMap(&m);
    return 0;
}
