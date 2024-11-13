#include <stdio.h>
#include <stdlib.h>

#define SIZEOF_INT 4  // Pretpostavljamo da je sizeof(int) 4 bajta
#define SIZEOF_NODE 12  // Pretpostavljamo da je veličina jednog čvora popisa 12 bajta (4 bajta za int + 8 bajta za pokazivač)

int main() {
    size_t max_niz = 0;
    size_t max_popis = 0;

    // Testiranje za niz
    while (1) {
        int *niz = (int*) malloc((max_niz + 1) * SIZEOF_INT);
        if (niz == NULL) break;  // Ako malloc vrati NULL, znači da više ne možemo alocirati memoriju
        free(niz);  // Oslobađamo memoriju prije nego pokušamo s većim brojem
        max_niz++;
    }

    // Testiranje za povezani popis
    while (1) {
        void *popis = malloc((max_popis + 1) * SIZEOF_NODE);
        if (popis == NULL) break;  // Ako malloc vrati NULL, znači da više ne možemo alocirati memoriju
        free(popis);  // Oslobađamo memoriju prije nego pokušamo s većim brojem
        max_popis++;
    }

    printf("Najveći broj elemenata za niz: %zu\n", max_niz);
    printf("Najveći broj elemenata za povezani popis: %zu\n", max_popis);

    return 0;
}
