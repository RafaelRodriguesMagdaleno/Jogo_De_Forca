# Jogo da Forca

Jogo da forca em C para terminal. O código foi escrito acompanhando o livro [Introdução à programação em C: Os primeiros passos de um desenvolvedor](https://www.casadocodigo.com.br/products/livro-introducao-c), de [Maurício Aniche](https://www.linkedin.com/in/mauricioaniche/), publicado pela [Casa do Código](https://www.casadocodigo.com.br/), que ensina programação por meio da construção de jogos.

## Sumário

- [Sobre o projeto](#sobre-o-projeto)
- [Como jogar](#como-jogar)
- [Melhorias implementadas](#melhorias-implementadas)
- [Estrutura do projeto](#estrutura-do-projeto)
- [Como o código funciona](#como-o-código-funciona)
  - [Arquivo de cabeçalho](#arquivo-de-cabeçalho)
  - [Variáveis globais](#variáveis-globais)
  - [Arrays e strings](#arrays-e-strings)
  - [Ponteiros e arquivos](#ponteiros-e-arquivos)
  - [Leitura e escrita com fscanf e fprintf](#leitura-e-escrita-com-fscanf-e-fprintf)
  - [Movendo a posição no arquivo com fseek](#movendo-a-posição-no-arquivo-com-fseek)
  - [Sorteio da palavra](#sorteio-da-palavra)
  - [Lendo um único caractere com scanf(" %c")](#lendo-um-único-caractere-com-scanf-c)
  - [Validando o chute com a tabela ASCII](#validando-o-chute-com-a-tabela-ascii)
  - [Comparando palavras com strcmp](#comparando-palavras-com-strcmp)
  - [Número com largura fixa no arquivo](#número-com-largura-fixa-no-arquivo)
  - [Escolha da dificuldade com do...while e switch](#escolha-da-dificuldade-com-dowhile-e-switch)
  - [Operador ternário](#operador-ternário)
  - [Laço principal com do...while](#laço-principal-com-dowhile)
  - [Extração de funções](#extração-de-funções)
- [Banco de palavras](#banco-de-palavras)
- [Ranking](#ranking)
- [Pré-requisitos](#pré-requisitos)
- [Como compilar e executar](#como-compilar-e-executar)
  - [Terminal (GCC)](#terminal-gcc)
  - [Code::Blocks](#codeblocks)
  - [Eclipse CDT](#eclipse-cdt)
  - [Visual Studio Code](#visual-studio-code)
  - [Dev-C++](#dev-c)
  - [Visual Studio](#visual-studio)
- [Problemas comuns](#problemas-comuns)
- [Conceitos praticados](#conceitos-praticados)
- [Referências](#referências)
- [Créditos](#créditos)

## Sobre o projeto

Este repositório registra meus estudos da linguagem C. O jogo é o segundo dos três projetos propostos no livro e foi implementado seguindo os capítulos passo a passo. O projeto e o código original são de autoria de Maurício Aniche. Além do código desenvolvido nos capítulos, o jogo recebeu as funcionalidades descritas em [Melhorias implementadas](#melhorias-implementadas).

O programa sorteia uma palavra secreta de um arquivo de texto e o jogador precisa descobri-la chutando uma letra por vez, antes que o boneco seja enforcado. O jogador escolhe o nível de dificuldade, e ao final da partida sua pontuação é registrada em um ranking. Quem vence pode cadastrar uma nova palavra, que passa a fazer parte do sorteio nas próximas partidas.

## Como jogar

1. Escolha o nível de dificuldade, que define quantos erros são permitidos.
2. A cada rodada, o jogo exibe a forca e a palavra secreta, com as letras ainda não descobertas representadas por `_`.
3. Digite uma letra em maiúscula.
4. O jogo informa se a letra existe na palavra e revela todas as posições em que ela aparece.
5. Cada letra que não existe na palavra conta como um erro e acrescenta uma parte ao boneco na forca.
6. O jogo termina quando o jogador descobre todas as letras (vitória) ou atinge o limite de erros do nível escolhido (derrota). Na derrota, a palavra secreta é revelada.
7. Em caso de vitória, o jogo pergunta se o jogador deseja adicionar uma nova palavra ao banco. Responda `S` para cadastrar ou qualquer outra tecla para seguir.
8. Por fim, informe seu nome para registrar a pontuação no ranking.

| Nível   | Erros permitidos |
|---------|------------------|
| Fácil   | 10               |
| Médio   | 8                |
| Difícil | 5                |

Opções de nível fora da lista são recusadas, e o menu é exibido novamente. O desenho do boneco fica completo a partir do quarto erro; nos níveis Fácil e Médio, a partida continua até o limite do nível.

Apenas letras maiúsculas são aceitas como chute. Letras minúsculas, números e outros caracteres são recusados com um aviso e não contam como erro. A resposta `S` para cadastrar uma palavra também deve ser digitada em maiúscula.

### Pontuação

| Resultado | Pontos                     |
|-----------|----------------------------|
| Vitória   | 100 menos 10 por erro      |
| Derrota   | 0                          |

Uma vitória sem erros vale 100 pontos; com 3 erros, vale 70.

## Melhorias implementadas

Além do código desenvolvido nos capítulos, o jogo recebeu as seguintes funcionalidades:

- **Níveis de dificuldade:** o jogador escolhe entre Fácil, Médio e Difícil, e cada nível define o limite de erros. Os limites ficam em constantes no `Forca.h`.
- **Chutes apenas em maiúsculas:** o jogo recusa letras minúsculas e outros caracteres, sem contá-los como erro. Antes, uma letra minúscula era registrada como erro mesmo que existisse na palavra.
- **Cadastro de palavra apenas após vitória:** a opção de adicionar uma palavra ao banco só aparece quando o jogador vence a partida.
- **Bloqueio de palavras repetidas:** antes de cadastrar, o jogo percorre o banco e recusa a palavra se ela já existir.
- **Quantidade de palavras com largura fixa:** a quantidade no início do `palavras.txt` passou a ser gravada sempre com 4 dígitos. Isso evita que, ao passar de 9 para 10 palavras (ou de 99 para 100), o número sobrescreva a quebra de linha ou o início da primeira palavra do arquivo.
- **Ranking:** ao final de cada partida, o jogador informa o nome, e a pontuação é registrada no arquivo `ranking.txt`.

## Estrutura do projeto

| Arquivo           | Conteúdo                                                                            |
|-------------------|-------------------------------------------------------------------------------------|
| `Jogo_De_Forca.c` | Código do jogo, com a função `main` e a implementação de todas as funções           |
| `Forca.h`         | Arquivo de cabeçalho com as declarações das funções e as constantes do jogo          |
| `palavras.txt`    | Banco de palavras usado no sorteio                                                  |
| `ranking.txt`     | Pontuações registradas; é criado automaticamente na primeira partida                |

O código é dividido em funções com responsabilidades separadas:

| Função                 | Responsabilidade                                                 |
|------------------------|------------------------------------------------------------------|
| `abertura()`           | Exibe o cabeçalho do jogo                                        |
| `escolhedificuldade()` | Exibe o menu de níveis e define o limite de erros                |
| `escolhepalavra()`     | Lê o banco de palavras e sorteia a palavra secreta               |
| `desenhaforca()`       | Desenha a forca de acordo com os erros e exibe a palavra parcial |
| `chuta()`              | Lê o chute do jogador, valida e o registra                       |
| `jachutou()`           | Verifica se uma letra já foi chutada                             |
| `letraexiste()`        | Verifica se uma letra faz parte da palavra secreta               |
| `chuteserrados()`      | Conta quantos chutes não existem na palavra                      |
| `ganhou()`             | Verifica se todas as letras da palavra foram descobertas         |
| `enforcou()`           | Verifica se o jogador atingiu o limite de erros                  |
| `adicionarpalavra()`   | Cadastra uma nova palavra no banco, se ela ainda não existir     |
| `salvaranking()`       | Calcula a pontuação e a registra no ranking                      |

As constantes definidas no `Forca.h` são:

| Constante         | Valor | Uso                                       |
|-------------------|-------|-------------------------------------------|
| `TAMANHO_PALAVRA` | 20    | Tamanho máximo das palavras               |
| `FACIL`           | 10    | Erros permitidos no nível Fácil           |
| `MEDIO`           | 8     | Erros permitidos no nível Médio           |
| `DIFICIL`         | 5     | Erros permitidos no nível Difícil         |
| `TAMANHO_NOME`    | 20    | Tamanho máximo do nome no ranking         |

## Como o código funciona

Esta seção explica os principais conceitos usados no jogo, com trechos do próprio código.

### Arquivo de cabeçalho

Em C, uma função precisa ser declarada antes de ser usada. No jogo, `ganhou()` chama `jachutou()`, que só é definida mais abaixo no arquivo. O `Forca.h` resolve isso: ele lista as assinaturas de todas as funções, e o `#include "Forca.h"` no início do código faz o compilador conhecê-las antes de encontrar qualquer chamada.

```c
#include "Forca.h"   // aspas: arquivo do próprio projeto
#include <stdio.h>   // sinais de menor e maior: biblioteca do sistema
```

O cabeçalho também guarda as constantes do jogo, como `TAMANHO_PALAVRA` e os limites de erro de cada nível. Para ajustar a dificuldade, basta alterar os valores ali.

### Variáveis globais

As variáveis declaradas fora de qualquer função podem ser lidas e alteradas por todas elas:

```c
char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;
int maxerros = DIFICIL;
```

É assim que `chuta()` registra uma letra e, depois, `desenhaforca()` e `ganhou()` conseguem consultar os mesmos chutes sem precisar recebê-los como parâmetro. Da mesma forma, `escolhedificuldade()` grava o limite em `maxerros`, e `enforcou()` o consulta no fim de cada rodada.

### Arrays e strings

Um array guarda vários valores do mesmo tipo em sequência. `chutes` guarda as letras já chutadas, e `chutesdados` indica quantas posições já foram preenchidas.

Em C, uma palavra é um array de `char` terminado pelo caractere especial `\0`, que marca onde ela acaba. Por isso `palavrasecreta`, com 20 posições, comporta palavras de até 19 letras. A função `strlen` conta os caracteres até o `\0`, e é com ela que os laços percorrem a palavra letra por letra.

### Ponteiros e arquivos

Para trabalhar com um arquivo, o C usa um ponteiro do tipo `FILE*`, que aponta para o arquivo aberto e para a posição atual de leitura ou escrita dentro dele. O `fopen` abre o arquivo e devolve esse ponteiro; se não conseguir, devolve `0` (nulo), e o jogo encerra com `exit(1)`:

```c
FILE* f;
f = fopen("palavras.txt", "r");
if(f == 0) {
    printf("Banco de dados de palavras não disponível\n\n");
    exit(1);
}
```

O segundo parâmetro do `fopen` define o modo de abertura:

| Modo | O que faz                                                                         |
|------|-----------------------------------------------------------------------------------|
| `r`  | Abre um arquivo existente apenas para leitura                                     |
| `w`  | Abre para escrita; cria o arquivo se não existir e apaga o conteúdo se existir    |
| `a`  | Abre para escrita no final do arquivo, mantendo o conteúdo existente              |
| `r+` | Abre um arquivo existente para leitura e escrita, sem apagar o conteúdo           |

O jogo usa `r` para sortear a palavra, `r+` para cadastrar uma nova, já que precisa ler o banco e depois escrever no mesmo arquivo, e `a` para o ranking, que só recebe linhas novas no final. Ao terminar, `fclose` fecha o arquivo e garante que tudo o que foi escrito seja salvo.

### Leitura e escrita com `fscanf` e `fprintf`

As duas funções funcionam como `scanf` e `printf`, mas recebem o arquivo como primeiro parâmetro:

```c
fscanf(f, "%d", &qtd);   // lê um número do arquivo
fprintf(f, "%d", qtd);   // escreve um número no arquivo
```

### Movendo a posição no arquivo com `fseek`

Cada leitura ou escrita avança a posição do ponteiro dentro do arquivo. O `fseek` muda essa posição e recebe três parâmetros: o arquivo, quantos bytes andar (positivo para frente, negativo para trás) e o ponto de partida:

| Ponto de partida | Significado                   |
|------------------|-------------------------------|
| `SEEK_SET`       | A partir do início do arquivo |
| `SEEK_CUR`       | A partir da posição atual     |
| `SEEK_END`       | A partir do final do arquivo  |

Em `adicionarpalavra()`, ele é usado duas vezes: primeiro volta ao início para sobrescrever a quantidade de palavras, depois vai ao final para escrever a palavra nova. O `\n` antes da palavra cria a quebra de linha, porque o arquivo normalmente não termina com uma:

```c
fseek(f, 0, SEEK_SET);
fprintf(f, "%04d", qtd);

fseek(f, 0, SEEK_END);
fprintf(f, "\n%s", novapalavra);
```

### Sorteio da palavra

`escolhepalavra()` lê a quantidade de palavras na primeira linha, sorteia um número entre 0 e essa quantidade menos 1 e lê as palavras do arquivo, uma a uma, até chegar à sorteada. Cada `fscanf` com `%s` sobrescreve `palavrasecreta`, então ao final do laço ela guarda a última palavra lida, que é a escolhida:

```c
int randomico = rand() % qtddepalavras;

for(int i = 0; i <= randomico; i++) {
    fscanf(f, "%s", palavrasecreta);
}
```

### Lendo um único caractere com `scanf(" %c")`

O espaço antes de `%c` faz o `scanf` ignorar espaços e quebras de linha pendentes. Sem ele, o Enter digitado no chute anterior seria lido como se fosse a próxima letra.

### Validando o chute com a tabela ASCII

Em C, um `char` é guardado como um número, definido pela tabela ASCII. As letras maiúsculas ocupam os códigos de 65 (`A`) a 90 (`Z`), então qualquer chute fora desse intervalo não é uma letra maiúscula. Nesse caso, o `return` encerra a função antes de o chute ser registrado, e ele não conta como erro:

```c
if(chute < 65 || chute > 90) {
    printf("Digite apenas letras maiúsculas!\n");
    return;
}
```

A mesma condição pode ser escrita como `chute < 'A' || chute > 'Z'`, já que o compilador troca cada letra entre aspas simples pelo seu código.

### Comparando palavras com `strcmp`

Comparar duas strings com `==` não funciona em C, porque o operador compara os endereços de memória dos arrays, e não o conteúdo. A função `strcmp` compara as palavras caractere por caractere e devolve `0` quando são iguais. Em `adicionarpalavra()`, ela é usada para percorrer o banco e recusar uma palavra repetida:

```c
for(int i = 0; i < qtd; i++) {
    fscanf(f, "%s", palavraarquivo);

    if(strcmp(palavraarquivo, novapalavra) == 0) {
        printf("Essa palavra já existe no jogo!\n");
        fclose(f);
        return;
    }
}
```

Antes de sair, o arquivo é fechado com `fclose`, para não ficar aberto quando a função termina mais cedo.

### Número com largura fixa no arquivo

Ao cadastrar uma palavra, o jogo volta ao início do arquivo e escreve a nova quantidade por cima da antiga. Se o número ganhar um dígito, por exemplo de 9 para 10, ele ocupa um caractere a mais e apaga o que vinha logo depois: a quebra de linha ou o começo da primeira palavra.

O formato `%04d` resolve isso, porque escreve o número sempre com 4 dígitos, completando com zeros à esquerda (`0009`, `0010`, `0100`). Assim, o valor novo ocupa exatamente o espaço do anterior. Ao ler, o `fscanf` com `%d` interpreta `0010` normalmente como 10.

### Escolha da dificuldade com `do...while` e `switch`

O menu de dificuldade usa um `do...while` para repetir a pergunta enquanto a opção digitada não estiver entre `1` e `3`. Depois, o `switch` traduz a opção para o limite de erros:

```c
do {
    // exibe o menu e lê a opção
    scanf(" %c", &opcao);
} while(opcao < '1' || opcao > '3');

switch(opcao) {
    case '1': maxerros = FACIL;   break;
    case '2': maxerros = MEDIO;   break;
    case '3': maxerros = DIFICIL; break;
}
```

A opção é lida como `char`, e não como número. Assim, se o jogador digitar uma letra por engano, ela é apenas recusada, sem travar o `scanf`.

### Operador ternário

O ternário é um `if/else` em uma única expressão: `condição ? valor_se_verdadeiro : valor_se_falso`. Em `desenhaforca()`, ele decide se cada parte do boneco é desenhada ou se aparece um espaço em branco, conforme o número de erros:

```c
printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
```

Com 1 erro ou mais, a cabeça `(_)` aparece; com menos, são impressos três espaços.

### Laço principal com `do...while`

O `do...while` executa o bloco primeiro e testa a condição depois, garantindo que a forca seja desenhada e o primeiro chute pedido antes de qualquer verificação. O laço continua enquanto o jogador não ganhou e não foi enforcado:

```c
do {
    desenhaforca();
    chuta();
} while (!ganhou() && !enforcou());
```

### Extração de funções

Cada função faz uma única tarefa, e as funções maiores são montadas a partir das menores. `enforcou()` usa `chuteserrados()`, que por sua vez usa `letraexiste()`. Assim, a regra "a letra existe na palavra?" é escrita uma vez só e reaproveitada em vários pontos, e a função `main` fica curta e fácil de ler.

## Banco de palavras

As palavras ficam no arquivo `palavras.txt`. A primeira linha informa a quantidade de palavras, sempre com 4 dígitos, e cada linha seguinte contém uma palavra, em letras maiúsculas e sem espaços:

```
0003
MELANCIA
BANANA
MORANGO
```

A quantidade na primeira linha precisa corresponder ao número de palavras do arquivo, pois é ela que define o intervalo do sorteio. Ao cadastrar uma palavra pelo próprio jogo, esse número é atualizado automaticamente. Ao editar o arquivo manualmente, mantenha os 4 dígitos (`0003`, e não `3`), pois o jogo grava a quantidade nesse formato e um número mais curto faria a gravação apagar parte da primeira palavra. O banco comporta até 9999 palavras.

Cada palavra pode ter até 19 caracteres, limite definido pela constante `TAMANHO_PALAVRA` em `Forca.h`.

O arquivo precisa estar na pasta de onde o programa é executado. Se ele não for encontrado, o jogo exibe a mensagem `Banco de dados de palavras não disponível` e encerra.

Uma palavra já cadastrada não pode ser adicionada de novo. A comparação diferencia maiúsculas de minúsculas, por isso as palavras novas também devem ser digitadas em maiúsculas.

## Ranking

Ao final de cada partida, o jogo pede o nome do jogador e registra a pontuação no arquivo `ranking.txt`, criado automaticamente na mesma pasta do `palavras.txt` na primeira vez. Cada partida acrescenta uma linha ao final do arquivo, com o nome e os pontos:

```
RAFAEL 80
MARIA 0
```

O nome deve ser uma única palavra, sem espaços, com até 19 caracteres. O ranking é apenas gravado; para consultá-lo, abra o `ranking.txt` em qualquer editor de texto.

## Pré-requisitos

O projeto usa apenas a biblioteca padrão do C e precisa de um compilador com suporte a C99 ou superior. A tabela resume o que cada ambiente exige:

| Ambiente           | Compilador incluído          | O que instalar                                                     | Sistemas              |
|--------------------|------------------------------|--------------------------------------------------------------------|-----------------------|
| Terminal (GCC)     | Não se aplica                | GCC (MinGW-w64 no Windows)                                         | Windows, Linux, macOS |
| Code::Blocks       | Sim, no instalador com MinGW | Apenas a IDE                                                       | Windows, Linux, macOS |
| Eclipse CDT        | Não                          | IDE e GCC                                                          | Windows, Linux, macOS |
| Visual Studio Code | Não                          | Editor, extensão C/C++ e GCC                                       | Windows, Linux, macOS |
| Dev-C++            | Sim (TDM-GCC)                | Apenas a IDE                                                       | Windows               |
| Visual Studio      | Sim (MSVC)                   | IDE com a carga de trabalho "Desenvolvimento para desktop com C++" | Windows               |

### Instalando o GCC

Necessário para o terminal, o Eclipse CDT e o Visual Studio Code.

**Windows**

1. Instale o [MSYS2](https://www.msys2.org/).
2. No terminal do MSYS2, execute:

```bash
   pacman -S mingw-w64-ucrt-x86_64-gcc
```

3. Adicione `C:\msys64\ucrt64\bin` à variável de ambiente `PATH`.

**Linux (Debian/Ubuntu)**

```bash
sudo apt update
sudo apt install build-essential
```

**macOS**

```bash
xcode-select --install
```

Para confirmar a instalação em qualquer sistema:

```bash
gcc --version
```

## Como compilar e executar

Primeiro, obtenha o código:

```bash
git clone https://github.com/RafaelRodriguesMagdaleno/Jogo_De_Forca.git
cd Jogo_De_Forca
```

Em todos os ambientes, mantenha `Jogo_De_Forca.c`, `Forca.h` e `palavras.txt` na mesma pasta. O `Forca.h` é incluído pelo próprio código e não precisa ser compilado separadamente.

### Terminal (GCC)

```bash
gcc Jogo_De_Forca.c -o jogo_de_forca
```

Para executar no Linux ou macOS:

```bash
./jogo_de_forca
```

Para executar no Windows:

```bash
.\jogo_de_forca.exe
```

Execute o programa a partir da pasta do projeto, onde está o `palavras.txt`.

### Code::Blocks

**Requisitos:** [Code::Blocks](https://www.codeblocks.org/downloads/). No Windows, baixe o instalador que tem `mingw` no nome, pois ele já inclui o compilador. No Linux e no macOS, instale o GCC separadamente.

1. Abra o Code::Blocks.
2. Acesse `File > Open` e selecione `Jogo_De_Forca.c`.
3. Pressione `F9` ou acesse `Build > Build and run`.

O jogo abre em uma janela de console própria.

Para trabalhar com um projeto em vez de um arquivo avulso:

1. Acesse `File > New > Project > Console application`.
2. Selecione a linguagem `C` e defina nome e pasta do projeto.
3. Substitua o `main.c` gerado pelo conteúdo de `Jogo_De_Forca.c`.
4. Copie `Forca.h` e `palavras.txt` para a pasta do projeto.
5. Pressione `F9`.

### Eclipse CDT

**Requisitos:** [Eclipse IDE for C/C++ Developers](https://www.eclipse.org/downloads/packages/) e GCC instalado e disponível no `PATH`. O Eclipse não inclui compilador.

1. Acesse `File > New > C/C++ Project`.
2. Selecione `C Managed Build` e avance.
3. Informe o nome do projeto e escolha `Executable > Empty Project`.
4. Em `Toolchains`, selecione `MinGW GCC` (Windows), `Linux GCC` ou `MacOSX GCC`.
5. Copie `Jogo_De_Forca.c`, `Forca.h` e `palavras.txt` para a pasta raiz do projeto, ou use `File > Import > General > File System`.
6. Compile com `Project > Build All` (`Ctrl+B`).
7. Execute com `Run > Run As > Local C/C++ Application`.

O Eclipse executa o programa a partir da pasta raiz do projeto, por isso o `palavras.txt` deve ficar nela. Os nomes dos menus podem variar um pouco entre versões do Eclipse.

### Visual Studio Code

**Requisitos:** [Visual Studio Code](https://code.visualstudio.com/), a extensão **C/C++** da Microsoft e GCC instalado e disponível no `PATH`.

1. Acesse `File > Open Folder` e abra a pasta do projeto.
2. Instale a extensão C/C++ pela aba de extensões (`Ctrl+Shift+X`).
3. Abra `Jogo_De_Forca.c`.
4. Clique na seta de execução no canto superior direito e escolha `Run C/C++ File`.
5. Selecione o compilador `gcc` quando solicitado.

Como alternativa, abra o terminal integrado (`` Ctrl+` ``) e use os comandos da seção [Terminal (GCC)](#terminal-gcc).

### Dev-C++

**Requisitos:** [Embarcadero Dev-C++](https://www.embarcadero.com/free-tools/dev-cpp), que já inclui o compilador TDM-GCC. Disponível apenas para Windows.

1. Acesse `Arquivo > Abrir` e selecione `Jogo_De_Forca.c`.
2. Pressione `F11` ou acesse `Executar > Compilar & Executar`.

Versões antigas, como o Orwell Dev-C++ 5.11, compilam em C90 por padrão. Nesse caso, acesse `Ferramentas > Opções do Compilador` e adicione `-std=c99` aos comandos de compilação.

### Visual Studio

**Requisitos:** [Visual Studio Community](https://visualstudio.microsoft.com/) com a carga de trabalho **Desenvolvimento para desktop com C++**. Disponível apenas para Windows.

1. Acesse `Arquivo > Novo > Projeto` e escolha `Projeto Vazio`.
2. No Gerenciador de Soluções, clique com o botão direito em `Arquivos de Origem` e escolha `Adicionar > Item Existente`.
3. Selecione `Jogo_De_Forca.c`. A extensão `.c` faz o arquivo ser compilado como C.
4. Da mesma forma, adicione `Forca.h` em `Arquivos de Cabeçalho`.
5. Copie `palavras.txt` para a pasta do projeto, onde fica o arquivo `.vcxproj`. É dessa pasta que o Visual Studio executa o programa, e é nela que o `ranking.txt` será criado.
6. Acesse `Projeto > Propriedades > C/C++ > Pré-processador > Definições do Pré-processador` e adicione `_CRT_SECURE_NO_WARNINGS`. Sem isso, o compilador da Microsoft rejeita o uso de `scanf`, `fscanf` e `fopen`.
7. Pressione `Ctrl+F5` para compilar e executar.

## Problemas comuns

**`Banco de dados de palavras não disponível`**
O programa não encontrou o `palavras.txt`. Confirme que o arquivo está na pasta de onde o programa é executado, conforme as instruções de cada ambiente.

**`Forca.h: No such file or directory`**
O arquivo de cabeçalho não está na mesma pasta que `Jogo_De_Forca.c`. Copie os dois para a mesma pasta.

**`Digite apenas letras maiúsculas!`**
O chute foi digitado em minúscula ou não é uma letra. Ative o Caps Lock e chute novamente; a tentativa recusada não conta como erro.

**Palavra nova não aparece no sorteio**
A quantidade na primeira linha do `palavras.txt` não corresponde ao número de palavras. Ajuste o número ao editar o arquivo manualmente.

**A primeira palavra do banco aparece cortada**
A quantidade na primeira linha do `palavras.txt` foi escrita com menos de 4 dígitos, e o jogo sobrescreveu parte da palavra seguinte ao cadastrar uma nova. Corrija a palavra e reescreva a quantidade com 4 dígitos, como `0012`.

**A opção de adicionar palavra não aparece**
A opção só é oferecida após uma vitória.

**Nome com espaço registra só a primeira parte**
O `scanf` com `%s` lê até o primeiro espaço. Use um nome sem espaços, como `RAFAEL` ou `RAFAEL_M`.

**`gcc` não é reconhecido como comando**
O compilador não está no `PATH`. Revise a seção [Instalando o GCC](#instalando-o-gcc) e reabra o terminal ou a IDE.

**`'for' loop initial declarations are only allowed in C99 mode`**
O compilador está em modo C90. Adicione a opção `-std=c99` na compilação.

**Acentos aparecem como caracteres estranhos**
A codificação do arquivo não corresponde à do terminal. Verifique em qual codificação o arquivo está salvo (UTF-8 ou ANSI) e ajuste a do terminal ou a do editor para a mesma.

**Eclipse: `Launch failed. Binary not found`**
O projeto ainda não foi compilado ou o Eclipse não encontrou o compilador. Compile com `Ctrl+B` e confira os erros na aba `Console`.

**Eclipse no Windows: as perguntas só aparecem depois de digitar**
O console interno do Eclipse armazena a saída em buffer. Execute o programa em um terminal externo ou adicione `setvbuf(stdout, NULL, _IONBF, 0);` no início da função `main`.

**Visual Studio: erro C4996 em `scanf`, `fscanf` ou `fopen`**
Adicione `_CRT_SECURE_NO_WARNINGS` às definições do pré-processador, conforme a seção [Visual Studio](#visual-studio).

## Conceitos praticados

- Arrays e strings (`char[]`, `strlen` e `strcmp`)
- Entrada e saída de dados (`scanf` e `printf`)
- Validação de entrada com a tabela ASCII
- Leitura e escrita de arquivos (`fopen`, `fscanf`, `fprintf`, `fseek` e `fclose`), incluindo os modos `r`, `r+` e `a`
- Formatação com largura fixa (`%04d`)
- Ponteiros (`FILE*`)
- Funções e extração de funções para reaproveitar código
- Arquivos de cabeçalho (`.h`) e constantes com `#define`
- Variáveis globais
- Laços de repetição (`for`, `do...while` e `break`)
- Estruturas condicionais (`if`, `else` e `switch`), incluindo o operador ternário (`condição ? valor1 : valor2`)
- Geração de números aleatórios (`rand`, `srand` e `time`)

## Referências

ANICHE, Maurício. [Introdução à programação em C: Os primeiros passos de um desenvolvedor](https://www.casadocodigo.com.br/products/livro-introducao-c). São Paulo: [Casa do Código](https://www.casadocodigo.com.br/), 2015. ISBN 978-85-5519-088-9.

## Créditos

- Projeto e código original: [Maurício Aniche](https://www.linkedin.com/in/mauricioaniche/), no livro [Introdução à programação em C](https://www.casadocodigo.com.br/products/livro-introducao-c)
- Implementação para estudo: [Rafael Rodrigues Magdaleno](https://github.com/RafaelRodriguesMagdaleno) ([LinkedIn](https://linkedin.com/in/rafael-rodrigues-magdaleno-5476a0271))
