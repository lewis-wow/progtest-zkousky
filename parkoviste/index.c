#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
    UKOL:
    https://www.fit-wiki.cz/%C5%A1kola/p%C5%99edm%C4%9Bty/bi-pa1/pa1_zkouska_2019_7_2
*/

int getFloorsCount(char id) {
    return (id - 'A' + 1);
}

char getFloorId(int index) {
    return (index + 'A');
}

typedef struct {
    char* rz;
    int timestamp;
} ParkPlace;

typedef struct {
    char id;
    ParkPlace* places;
} Floor;

Floor floorInit(char id, int maxPlaces) {
    Floor f;
    f.places = (ParkPlace*)malloc(sizeof(ParkPlace) * maxPlaces);
    f.id = id;

    return f;
}

typedef struct {
    Floor* floors;
    int floorsCount;
} Park;

Park initPark(int floors, int maxPlaces) {
    Park p;
    p.floors = (Floor*)malloc(sizeof(*(p.floors)) * floors);
    p.floorsCount = floors;

    for(int i = 0; i < floors; i++) {
        p.floors[i] = floorInit(getFloorId(i), maxPlaces);
    }

    return p;
}

void freePark(Park* p) {
    for(int i = 0; i < p->floorsCount; i++) {
        for(int i = 0; i < p->floorsCount; i++) {
            free(p->floors[i].places);
        }
        free(p->floors);
    }
    free(p->floors);
    p->floors = NULL;
    p->floorsCount = 0;
}




int main(void) {

    char maxId;
    int maxPlaces;

    printf("Velikost:\n");

    if(scanf(" %c %d", &maxId, &maxPlaces) != 2) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    int maxFloors = getFloorsCount(maxId);
    Park p = initPark(maxFloors, maxPlaces);

    printf("%d", maxFloors);
    return 0;
}
