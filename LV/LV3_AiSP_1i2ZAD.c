#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Cvor {
    int n;
    int m;
    int rezultat;
    struct Cvor *sljedeci;
} Cvor;

int binomski_rekurzivno(int n, int m) {
    if (m == 0 || m == n) {
        return 1;
    }
    return binomski_rekurzivno(n - 1, m - 1) + binomski_rekurzivno(n - 1, m);
}

void push(Cvor **vrh, int n, int m) {
    Cvor *novi_cvor = (Cvor *)malloc(sizeof(Cvor));
    if (novi_cvor == NULL) {
        printf("Greska pri alokaciji!\n");
        exit(1);
    }
    novi_cvor->n = n;
    novi_cvor->m = m;
    novi_cvor->rezultat = -1;  
    novi_cvor->sljedeci = *vrh;
    *vrh = novi_cvor;
}

Cvor* pop(Cvor **vrh) {
    if (*vrh == NULL) return NULL;
    Cvor *temp = *vrh;
    *vrh = (*vrh)->sljedeci;
    return temp;
}

int binomski_stog(int n, int m) {
    int *stog = (int *)malloc((n + 1) * sizeof(int));
    int vrh = -1; 
    stog[++vrh] = n;
    stog[++vrh] = m;
    int rezultat = 0;

    while (vrh >= 0) {
        m = stog[vrh--];
        n = stog[vrh--];

        if (m == 0 || m == n) {
            rezultat = 1;
        } else {
            stog[++vrh] = n - 1;
            stog[++vrh] = m - 1;

            stog[++vrh] = n - 1;
            stog[++vrh] = m;
        }
    }

    free(stog);
    return rezultat;
}

int binomski_povezani_popis(int n, int m) {
    Cvor *stog = NULL;
    push(&stog, n, m);
    int rezultat = 0;

    while (stog != NULL) {
        Cvor *top_cvor = pop(&stog);
        n = top_cvor->n;
        m = top_cvor->m;
        free(top_cvor);  

        if (m == 0 || m == n) {
            rezultat = 1;
        } else {
            push(&stog, n - 1, m - 1);
            push(&stog, n - 1, m);
        }
    }

    return rezultat;
}

int main() {
    int n, m;

    printf("Unesite n (gdje je n >= 0): ");
    scanf("%d", &n);

    m = n / 2;

    if (n >= m) {
        clock_t pocetak, kraj;
        double vrijeme;

        // Rekurzivno
        pocetak = clock();
        int rekurzivni_rezultat = binomski_rekurzivno(n, m);  
        kraj = clock();
        vrijeme = ((double)kraj - pocetak) / CLOCKS_PER_SEC * 1000;  
        printf("Rekurzivni rezultat za n = %d, m = %d: %d\n", n, m, rekurzivni_rezultat);
        printf("Vrijeme za rekurzivno: %f ms\n", vrijeme);

        // Stog (niz)
        pocetak = clock();
        binomski_stog(n, m);  
        kraj = clock();
        vrijeme = ((double)kraj - pocetak) / CLOCKS_PER_SEC * 1000;  
        printf("Vrijeme za stog (N): %f ms\n", vrijeme);

        // Stog (povezani popis)
        pocetak = clock();
        binomski_povezani_popis(n, m);  
        kraj = clock();
        vrijeme = ((double)kraj - pocetak) / CLOCKS_PER_SEC * 1000;  
        printf("Vrijeme za stog (PP): %f ms\n", vrijeme);
    } else {
        printf("n treba biti vece ili jednako m.\n");
    }

    return 0;
}
