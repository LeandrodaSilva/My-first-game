#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#define limpa (system("cls"))
#define baixo 80
#define cima 72
#define enter 13
#define pausa (system("pause"))
#elif __APPLE__
#include <termios.h>
static struct termios old, new;
void initTermios(int echo){
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new = old; /* make new settings same as old settings */
  new.c_lflag &= ~ICANON; /* disable buffered i/o */
  new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}
void resetTermios(void){
  tcsetattr(0, TCSANOW, &old);
}
char getch_(int echo){
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}
char getch(void){
  return getch_(0);
}
char getche(void){
  return getch_(1);
}
#define limpa (system("clear"))
#define pausa (system("read -n 1 -s -p \"Pressione uma Tecla...\""))
#define baixo 115
#define cima 119
#define enter 10
#else
exit(1);
#endif



typedef struct Pokemons
{
  float hp;      //Saúde
  float spd;     //Agilidade
  float atk;     //Ataque
  float def;     //Defesa
  char name[50]; //Nome
}pokemon;

pokemon *deck = NULL;
int  tamanho = 3, cont = 0;


void addpoke();
void rmvpoke();
void addspc();
void listpoke();

int menu();

int main()
{

  deck = (pokemon*) calloc(tamanho, sizeof(pokemon));
  if (deck == NULL)
  {
    printf("Erro de alocacao\n");
    free(deck);
    exit(0);
  }

  while (1)
  {
    switch (menu())
    {
      case 1: addpoke(); break;
      case 2: rmvpoke(); break;
      case 3: addspc(); break;
      case 4: listpoke(); break;
      case 5:
      free(deck);
      exit(0);
    }
  }
  return 0;
}

void addpoke()
{
  if (cont < tamanho)
  {
    printf("Informe o nome: ");
    fflush(stdin);
    scanf("%s", deck[cont].name);

    printf("Informe o HP: ");
    scanf("%f", &deck[cont].hp);

    printf("Informe a agilidade: ");
    scanf("%f", &deck[cont].spd);

    printf("Informe o ataque: ");
    scanf("%f", &deck[cont].atk);

    printf("Informe a defesa: ");
    scanf("%f", &deck[cont].def);


    cont++;
  }else{
    printf("Sem espaco, volte ao menu e adicione mais\n");
    pausa;
  }
}

void rmvpoke()
{

  free(deck);
  deck = NULL;
  cont = 0;
  tamanho = 3;

  if ((deck = (pokemon*) realloc(deck, tamanho*sizeof(pokemon))) == NULL)
  {
    printf("Erro de alocacao\n\n");
    free(deck);
    pausa;
  }else{
    printf("Liberado com sucesso\n");
    pausa;
  }
}

void addspc()
{
  tamanho += 3;
  deck = (pokemon*) realloc(deck, tamanho*sizeof(pokemon));
  if (deck == NULL) {
    printf("Erro de alocacao\n");
  }else{
    printf("Alocado mais 3 espacos\n\n");
    pausa;
  }
}

void listpoke()
{
  int i = 0;

  for (i = 0; i < cont; i++) {
    printf("Nome: %s\nHP: %0.2f\nAgilidade: %0.2f\nAtaque: %0.2f\nDefesa: %0.2f\n\n", deck[i].name, deck[i].hp, deck[i].spd, deck[i].atk, deck[i].def);
  }
  pausa;
}

#ifdef _WIN32
int menu()
{

  char tecla = 0;
  int slctvert = 1, a = 254, b = 255, c = 255, d = 255, e = 255;



  while(1){

    limpa;

    printf("\n\n\n\n\n\n\n\t\t\t\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n");
    printf("\t\t\t\xBA %c Adicionar Pok\x82mon         \xBA\n", a);
    printf("\t\t\t\xBA %c Remover Todos os Pok\x82mons \xBA\n", b);
    printf("\t\t\t\xBA %c Alocar mais 3 espa\x87os     \xBA\n", c);
    printf("\t\t\t\xBA %c Listar Pok\x82mons           \xBA\n", d);
    printf("\t\t\t\xBA %c Liberar mem\xA2ria e sair    \xBA\n", e);
    printf("\t\t\t\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n\n");
    fflush(stdin);
    tecla = getch();

    if (tecla == baixo && slctvert < 5)
    {
      slctvert++;

    }
    if (tecla == cima && slctvert > 1)
    {
      slctvert--;

    }
    if (slctvert == 1)
    {
      a = 254; //Quadrado
      b = 255;
      c = 255;
      d = 255;
      e = 255;
    }
    if (slctvert == 2)
    {
      a = 255;
      b = 254; //Quadrado
      c = 255;
      d = 255;
      e = 255;
    }
    if (slctvert == 3)
    {
      a = 255;
      b = 255;
      c = 254; //Quadrado
      d = 255;
      e = 255;
    }
    if (slctvert == 4)
    {
      a = 255;
      b = 255;
      c = 255;
      d = 254; //Quadrado
      e = 255;
    }
    if (slctvert == 5)
    {
      a = 255;
      b = 255;
      c = 255;
      d = 255;
      e = 254; //Quadrado
    }
    if (tecla == enter && slctvert < 5)
    {

      return slctvert;
    }
    if (tecla == enter && slctvert == 5)
    {
      return 5;
    }
  }

}
#elif __APPLE__
int menu()
{
  char tecla = 0;

  while(1){

    limpa;

    printf("(1) Adicionar Pokemon\n");
    printf("(2) Remover Todos os Pokemons\n");
    printf("(3) Alocar mais 3 espacos\n");
    printf("(4) Listar Pokemons\n");
    printf("(5) Liberar memoria e sair\n");
    fflush(stdin);
    tecla = getch();

    if (tecla >= 49 && tecla <= 53)
    {
      limpa;
      return (tecla - 48);
    }
  }
}
#endif
