#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pbs
{
	char c;
	struct pbs* lijevi;
	struct pbs* desni;
}PBS;


PBS* novi_cvor(char c, PBS* lijevi, PBS* desni)
{
	PBS* novi = (PBS*)calloc(1, sizeof(PBS));
	if (novi == NULL)
	{
		perror("Error pri zauzimanju memorije za novi PBS cvor...");
		exit(-1);
	}

	novi->c = c;
	novi->lijevi = lijevi;
	novi->desni = desni;

	return novi;
}

PBS* pretrazi_pbs(char trazeno, PBS* glavni_cvor)
{
	PBS* povratni_cvor = NULL;
	if (glavni_cvor == NULL)
		return NULL;
	if (glavni_cvor->c == trazeno)
		povratni_cvor = glavni_cvor;
	if (glavni_cvor->c < trazeno)
		povratni_cvor = pretrazi_pbs(trazeno, glavni_cvor->desni);
	if (glavni_cvor->c > trazeno)
		povratni_cvor = pretrazi_pbs(trazeno, glavni_cvor->lijevi);

	return povratni_cvor;
}

PBS* umetni_cvor(char c, PBS* glavni_cvor)
{
	PBS* novi = NULL;

	if (glavni_cvor == NULL)
	{
		glavni_cvor = novi_cvor(c, NULL, NULL);
		return glavni_cvor;
	}

	if (pretrazi_pbs(c, glavni_cvor) != NULL)
	{
		return glavni_cvor;
	}

	novi = novi_cvor(c, NULL, NULL);

	if (c < (glavni_cvor)->c)
	{
		(glavni_cvor)->lijevi = umetni_cvor(c, (glavni_cvor)->lijevi);
	}
	else
	{
		(glavni_cvor)->desni = umetni_cvor(c, (glavni_cvor)->desni);
	}

	return glavni_cvor;
}

void ispisi_preorder(PBS* glavni_cvor)
{
	if (glavni_cvor == NULL) return;

	printf("%c ", glavni_cvor->c);
	ispisi_preorder(glavni_cvor->lijevi);
	ispisi_preorder(glavni_cvor->desni);
}

void ispisi_inorder(PBS* glavni_cvor)
{
	if (glavni_cvor == NULL) return;

	ispisi_inorder(glavni_cvor->lijevi);
	printf("%c ", glavni_cvor->c);
	ispisi_inorder(glavni_cvor->desni);
}

void ispisi_postorder(PBS* glavni_cvor)
{
	if (glavni_cvor == NULL) return;

	ispisi_postorder(glavni_cvor->lijevi);
	ispisi_postorder(glavni_cvor->desni);
	printf("%c ", glavni_cvor->c);
}

void oslobodi_PBS(PBS* glavni_cvor)
{
	if (glavni_cvor == NULL) return;
	oslobodi_PBS(glavni_cvor->lijevi);
	oslobodi_PBS(glavni_cvor->desni);

	free(glavni_cvor);
}

int main()
{
	char string[50] = { '\0' };
	PBS* stablo = NULL;
	int i;

	printf("Unesi ime i prezime: ");
	scanf("%99[^\n]", string);

	for (i = 0; i < strlen(string); i++)
	{
		if (string[i] == ' ')
			continue;
		stablo = umetni_cvor(string[i], stablo);
	}

	printf("Preorder(NLD): ");
	ispisi_preorder(stablo);
	printf("\n");

	printf("Inorder(LND): ");
	ispisi_inorder(stablo);
	printf("\n");

	printf("Postorder(LDN): ");
	ispisi_postorder(stablo);
	printf("\n");

	oslobodi_PBS(stablo);
}

