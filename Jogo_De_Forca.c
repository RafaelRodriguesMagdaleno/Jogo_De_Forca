#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "Forca.h"

//Variaveis Globais
char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;
int maxerros = DIFICIL;

void escolhedificuldade() {
    char opcao;

    do {
        printf("Escolha a dificuldade:\n");
        printf("(1) Fácil   - %d chutes\n", FACIL);
        printf("(2) Médio   - %d chutes\n", MEDIO);
        printf("(3) Difícil - %d chutes\n", DIFICIL);
        printf("Opção: ");
        scanf(" %c", &opcao);
    } while(opcao < '1' || opcao > '3');

    switch(opcao) {
        case '1': maxerros = FACIL;   break;
        case '2': maxerros = MEDIO;   break;
        case '3': maxerros = DIFICIL; break;
    }
}

int letraexiste(char letra) {

    for(int j = 0; j< strlen(palavrasecreta); j++) {
        if(letra == palavrasecreta[j]) {
            return 1;
        }
    }
    return 0;
}

int chuteserrados() {
    int erros = 0;

    for(int i = 0; i < chutesdados; i++) {
        if(!letraexiste(chutes[i])) {
            erros++;
        }
    }

    return erros;
}

int enforcou() {

	return chuteserrados() >= maxerros;
}

int ganhou() {
	for(int i = 0; i < strlen(palavrasecreta); i++) {
		if(!jachutou(palavrasecreta[i])) {
			return 0;
		}
	}

	return 1;
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

	if(chute < 65 || chute > 90) {
        printf("Digite apenas letras maiúsculas!\n");
        return;
	}

	if(letraexiste(chute)) {
        printf("Você acertou: a palavra tem a letra %c\n\n", chute);
	}else {
	    printf("\nVocê errou: a palavra NÃO tem a letra %c\n\n", chute);
	}

	chutes[chutesdados] = chute;
	chutesdados++;
}

int jachutou(char letra) {
	int achou = 0;
	for(int j = 0; j < chutesdados; j++) {
		if(chutes[j] == letra) {
			achou = 1;
			break;
		}
	}

	return achou;
}

void desenhaforca() {

	int erros = chuteserrados();

	printf("  _______       \n");
	printf(" |/      |      \n");
	printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
	printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
	printf(" |       %c     \n", (erros>=2?'|':' '));
	printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
	printf(" |              \n");
	printf("_|___           \n");
	printf("\n\n");

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
	FILE* f;

	f = fopen("palavras.txt", "r");
	if(f == 0) {
        printf("Banco de dados de palavras não disponível\n\n");
        exit(1);
	}

	int qtddepalavras;
	fscanf(f, "%i", &qtddepalavras);

	//gera um número aleatório
	srand(time(0));
	int randomico = rand() % qtddepalavras;

	//Lê o arquivo até chegar na na linha desejada
	for(int i = 0; i <= randomico; i++) {
        fscanf(f, "%s", palavrasecreta);
	}

	fclose(f);
}

void adicionarpalavra() {
    char quer;

    printf("Você deseja adicionar uma nova palavra no jogo ? (S/N) ");
    scanf(" %c", &quer);

    if(quer == 'S') {
        char novapalavra[TAMANHO_PALAVRA];

        printf("Digite a nova palavra, em letras maiúsculas: ");
        scanf("%s", novapalavra);

        //Ponteiro para o arquivo
        FILE* f;

        //abre o arquivo, se quiser apenas ler, use a função 'r' no final, se quiser escrever no final usamos o 'a'

        //A letra 'W' ela ajuda a escrever em arquivos, mas apenas em arquivos novos, se o arquivo existir, ele apaga o primeiro

        //O 'R+" permite ler e alterar um arquivo
        f = fopen("palavras.txt", "r+");
        if(f == 0) {
            printf("Banco de dados de palavras não disponível\n\n");
            exit(1);
        }

        int qtd;

        //A função fscanf consegue ler dados de um arquivo
        fscanf(f, "%d", &qtd);

        //Verificando se a palavra já existe no arquivo
        char palavraarquivo[TAMANHO_PALAVRA];

        for(int i = 0; i < qtd; i++) {
            fscanf(f, "%s", palavraarquivo);

            if(strcmp(palavraarquivo, novapalavra) == 0) {
                printf("Essa palavra já existe no jogo!\n");
                fclose(f);
                return;
            }
        }
        qtd++;

        //Fseek muda o ponteiro de posição, recebe três parametros, o arquivo, quantos bytes ele deve andar (Esquerda ou Direita) e de onde ele deve começar(Começo, posição corrente, ou do final do arquivo)
        fseek(f, 0, SEEK_SET);

        //SEEK_CUR : Anda a partir do ponto atual
        //SEEK_END : Anda a partir do fim do arquivo

        //A função fprintf consegue escrever no arquivo
        fprintf(f, "%d", qtd);

        //Escreve a palavra nova no final do arquivo
        fseek(f, 0, SEEK_END);

        //escreve a palvra
        //Colocamos um \n pois o ponteiro nos posiciona bem no final do arquivo, e teoricamente não tem um enter, ent escrevemos um Enter e ai a palavra
        fprintf(f, "\n%s", novapalavra);


        //Fecha o arquivo
        fclose(f);
    }
}

void main() {

    setlocale(LC_ALL, "Portuguese");

	abertura();
	escolhedificuldade();
	escolhepalavra();

	do {

		desenhaforca();
		chuta();

	} while (!ganhou() && !enforcou());

	if(ganhou()) {
		printf("\nParabéns, você ganhou!\n\n");

		printf("       ___________      \n");
		printf("      '._==_==_=_.'     \n");
		printf("      .-\\:      /-.    \n");
		printf("     | (|:.     |) |    \n");
		printf("      '-|:.     |-'     \n");
		printf("        \\::.    /      \n");
		printf("         '::. .'        \n");
		printf("           ) (          \n");
		printf("         _.' '._        \n");
		printf("        '-------'       \n\n");

		adicionarpalavra();

	} else {
		printf("\nPuxa, você foi enforcado!\n");
		printf("A palavra era **%s**\n\n", palavrasecreta);

		printf("    _______________         \n");
		printf("   /               \\       \n");
		printf("  /                 \\      \n");
		printf("//                   \\/\\  \n");
		printf("\\|   XXXX     XXXX   | /   \n");
		printf(" |   XXXX     XXXX   |/     \n");
		printf(" |   XXX       XXX   |      \n");
		printf(" |                   |      \n");
		printf(" \\__      XXX      __/     \n");
		printf("   |\\     XXX     /|       \n");
		printf("   | |           | |        \n");
		printf("   | I I I I I I I |        \n");
		printf("   |  I I I I I I  |        \n");
		printf("   \\_             _/       \n");
		printf("     \\_         _/         \n");
		printf("       \\_______/           \n");
	}

}
