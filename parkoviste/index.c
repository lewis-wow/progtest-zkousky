#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char rz[11];
    int isFree; //0 = no, 1 = yes
    int index;
    char floor;
} ParkPlace;

ParkPlace newParkPlace(int index) {
    ParkPlace place;
    place.isFree = 1;
    place.rz[0] = '\0';
    place.index = index;    

    return place;
}

typedef struct {
    int id;
    char idAsChar;
    int placesCount;
    ParkPlace* places;
} Floor;

Floor floorInit(char id, int maxPlaces) {
    Floor f;

    f.places = (ParkPlace*)malloc(sizeof(ParkPlace) * maxPlaces);
    for(int i = 0; i < maxPlaces; i++) {
        f.places[i] = newParkPlace(i);
    }

    f.placesCount = maxPlaces;
    f.idAsChar = id;
    f.id = getFloorsCount(id);

    return f;
}

typedef struct {
    Floor* floors;
    int floorsCount;
    int placesCount;
    int firstI;
    int firstJ;
} Park;

Park initPark(int floors, int maxPlaces) {
    Park p;
    p.floors = (Floor*)malloc(sizeof(*(p.floors)) * floors);
    p.floorsCount = floors;
    p.firstI = 0;
    p.firstJ = 0;
    p.placesCount = maxPlaces;

    for(int i = 0; i < floors; i++) {
        p.floors[i] = floorInit(getFloorId(i), maxPlaces);
    }

    return p;
}

void freePark(Park* p) {
    for(int i = 0; i < p->floorsCount; i++) {
        free(p->floors[i].places);
    }
    free(p->floors);
    p->floors = NULL;
    p->floorsCount = 0;
}


int findParkPlace(Park* p, char currentRZ[10]) {
    int lastTimestampI, lastTimestampJ;

    for(int i = 0; i < p->floorsCount; i++) {
        for(int j = 0; j < p->floors[i].placesCount; j++) {
            if(p->floors[i].places[j].isFree) {
                p->floors[i].places[j].isFree = 0;
                strcpy(p->floors[i].places[j].rz, currentRZ);

                printf(
                    "Pozice: %c%d\n",  
                    p->floors[i].idAsChar, 
                    p->floors[i].places[j].index
                );
                return 1;
            }
        }
    }

    printf(
        "Odtah vozu %s z pozice %c%d\n", 
        p->floors[p->firstI].places[p->firstJ].rz, 
        p->floors[p->firstI].idAsChar,
        p->floors[p->firstI].places[p->firstJ].index
    );
    printf(
        "Pozice: %c%d\n", 
        p->floors[p->firstI].idAsChar,
        p->floors[p->firstI].places[p->firstJ].index
    );
    p->floors[p->firstI].places[p->firstJ].rz[0] = '\0';
    strcpy(p->floors[p->firstI].places[p->firstJ].rz, currentRZ);

    if(p->firstJ == (p->placesCount - 1)) {
        if(p->firstI == (p->floorsCount - 1)) {
            p->firstI = 0;
        } else {
            p->firstI += 1;
        }
        p->firstJ = 0;
    } else {
        p->firstJ += 1;
    }
    
    return 0;
}

int freeParkPlace(Park* p, char currentRZ[10]) {
    for(int i = 0; i < p->floorsCount; i++) {
        for(int j = 0; j < p->floors[i].id; j++) {
            if(!strcmp(p->floors[i].places[j].rz, currentRZ)) {
                p->floors[i].places[j].rz[0] = '\0';
                p->floors[i].places[j].isFree = 1;

                printf("Pozice: %c%d\n", p->floors[i].idAsChar, p->floors[i].places[j].index);
                return 1;
            }
        }
    }
    return 0;
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

    printf("Pozadavky:\n");

    char currentRZ[11];
    char symbol;
    int scanfRes;

    while((scanfRes = scanf(" %c", &symbol)) != EOF) {
        if(scanfRes != 1 || (symbol != '+' && symbol != '-')) {
            freePark(&p);
            printf("Nespravny vstup.\n");
            return 1;
        }

        if(scanf(" %10s", currentRZ) != 1) {
            freePark(&p);
            printf("Nespravny vstup.\n");
            return 1;
        }

        if(symbol == '+') {
            //add
            findParkPlace(&p, currentRZ);
        } else {
            //remove
            if(!freeParkPlace(&p, currentRZ)) {
                printf("Nenalezeno.\n");
            }
        }   
    }


    if(feof(stdin)) {
        freePark(&p);
        printf("Nespravny vstup.\n");
        return 1;
    }

    freePark(&p);
    return 0;
}
