#include <stdio.h>
#include <string.h>
#include <locale.h>

char palavrasecreta[20];
char chutes[26];
int tentativas = 0;

int enforcou() {

    int erros = 0;

    //Vamos fazer o loop de todos os chutes dados
    for(int i = 0; i < tentativas; i++) {

        int existe = 0;

        //Agora vamos olhar letra a letra da palavra secretra e ber se encontramos o chute aqui
        for(int j = 0; j < strlen(palavrasecreta); j++) {
            if(chutes[i] == palavrasecreta[j]) {

                //encontramos, vamos quebrar o loop
                existe = 1;
                break;
            }
        }

        //Se não encontrou, soma um na quantidade de erros
        if(!existe) erros ++;
    }

    //Se tivermos mais do que 5 erros, retornamos 1, caso contrário, retornamos 0
    return erros >= 5;
}

void abertura() {
	printf("/****************/\n");
	printf("/ Jogo de Forca */\n");
	printf("/****************/\n\n");
}

void chuta() {
	char chute;
	printf("Qual letra? ");
	scanf(" %c", &chute);

	chutes[tentativas] = chute;
}

int jachutou(char letra) {
	int achou = 0;

	 //A letra já foi chutada?
	for(int j = 0; j < tentativas; j++) {
		if(chutes[j] == letra) {
			achou = 1;
			break;
		}
	}

	return achou;
}

void desenhaforca() {

	printf("Você já deu %d chutes\n", tentativas);

	//Imprime a palavra secreta
	for(int i = 0; i < strlen(palavrasecreta); i++) {

		if(jachutou(palavrasecreta[i])) {
			printf("%c ", palavrasecreta[i]);
		} else {
			printf("_ ");
		}

	}
	printf("\n");

}

void escolhepalavra() {
	sprintf(palavrasecreta, "MELANCIA");
}



void main() {

    setlocale(LC_ALL, "Portuguese");

	int acertou = 0;

	abertura();
	escolhepalavra();

	do {

		desenhaforca();
		chuta();

		enforcou();
		tentativas ++;

	} while (!acertou && !enforcou());

}
