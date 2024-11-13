#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000  // Broj elemenata u nizu i popisu

// Struktura povezane liste
typedef struct OE_ {
    int x;
    struct OE_ *sljedeci;
} OE;

// Funkcija za generiranje slučajnog niza
void generirajNiz(int niz[], int n) {
    for (int i = 0; i < n; i++) {
        niz[i] = rand() % 100;  // Slučajan broj između 0 i 99
    }
}

// Funkcija za formiranje povezane liste iz niza
OE* formirajPovezanuListu(int niz[], int n) {
    OE *prvi = NULL;
    OE *posljednji = NULL;

    for (int i = 0; i < n; i++) {
        OE *novi = (OE*) malloc(sizeof(OE));
        novi->x = niz[i];
        novi->sljedeci = NULL;

        if (prvi == NULL) {
            prvi = novi;
        } else {
            posljednji->sljedeci = novi;
        }
        posljednji = novi;
    }
    return prvi;
}

// Sekvencijalno pretraživanje u nizu
int pretraziNiz(int niz[], int n, int cilj) {
    for (int i = 0; i < n; i++) {
        if (niz[i] == cilj) {
            return i;  // Vraća indeks gdje je element pronađen
        }
    }
    return -1;  // Ako element nije pronađen
}

// Sekvencijalno pretraživanje u povezanom popisu
int pretraziPovezanuListu(OE *prvi, int cilj) {
    OE *trenutni = prvi;
    int index = 0;
    
    while (trenutni != NULL) {
        if (trenutni->x == cilj) {
            return index;
        }
        trenutni = trenutni->sljedeci;
        index++;
    }
    return -1;  // Ako element nije pronađen
}

// Funkcija za mjerenje vremena za sve operacije
void mjerenjeVremena() {
    clock_t start, end;
    double cpu_time_used;

    // Generiranje slučajnog niza
    int niz[N];
    start = clock();
    generirajNiz(niz, N);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Vrijeme generiranja niza: %f sekundi\n", cpu_time_used);

    // Formiranje povezanog popisa
    start = clock();
    OE *prvi = formirajPovezanuListu(niz, N);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Vrijeme formiranja povezanog popisa: %f sekundi\n", cpu_time_used);

    // Sekvencijalno pretraživanje u nizu
    int cilj = 50;  // Nasumični cilj
    start = clock();
    pretraziNiz(niz, N, cilj);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Vrijeme sekvencijalnog pretraživanja u nizu: %f sekundi\n", cpu_time_used);

    // Sekvencijalno pretraživanje u povezanom popisu
    start = clock();
    pretraziPovezanuListu(prvi, cilj);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Vrijeme sekvencijalnog pretraživanja u povezanom popisu: %f sekundi\n", cpu_time_used);
}

// Glavna funkcija
int main() {
    srand(time(NULL));  // Inicijalizacija generatora slučajnih brojeva

    mjerenjeVremena();  // Pokretanje mjerenja vremena

    return 0;
}
