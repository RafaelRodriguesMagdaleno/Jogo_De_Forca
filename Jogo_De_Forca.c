#include <stdio.h>
#include <string.h>
#include <locale.h>

void abertura() {
    printf("/****************/\n");
	printf("/ Jogo de Forca */\n");
	printf("/****************/\n");
}

//Aqui utilizamos o ponteiro para fazer a váriavel tentativas da função chuta, acessar o valor de tentativas da função Main
void chuta(char chutes[26], int* tentativas) {
    char chute;
    printf("Qual letra ? ");
    scanf(" %c", &chute);

    chutes[*tentativas] = chute;
    (*tentativas)++;
}



void main() {

    setlocale(LC_ALL, "Portuguese");

	char palavrasecreta[20];
	sprintf(palavrasecreta, "MELANCIA");

	int acertou = 0;
	int enforcou = 0;

	char chutes[26];
	int tentativas = 0;

	abertura();

	do {
	    printf("Você já deu %i tentativas\n", tentativas);

        //Imprime a palavra secreta
		for(int i = 0; i < strlen(palavrasecreta); i++) {
			int achou = 0;

			//A letra ja foi chutada ?
			for(int j = 0; j < tentativas; j++) {
				if(chutes[j] == palavrasecreta[i]) {
					achou = 1;
					break;
				}
			}

			if(achou) {
				printf("%c ", palavrasecreta[i]);
			} else {
				printf("_ ");
			}
		}
		printf("\n");

		chuta(chutes, &tentativas);
	} while (!acertou && !enforcou);

}
