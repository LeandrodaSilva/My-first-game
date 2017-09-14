/*
* Autor: Leandro da Silva
* RA: 1916041
* Curso: Engenharia de Software
* Turma: ES21
* Disciplina: Técnicas de Programação
* Objetivo: criar um jogo de luta, contendo 3 rodadas, entre mago, arqueiro e anao. O personagens que vencer o maior numero de rodadas
* vence.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#define t 20 // velocidade da animação de combate
#define t_archer 200


enum opcoes{
	iniciar = 1,
	instrucoes,
	sair
};

typedef enum Classes{

	MAGE,    //Bonus 3
	ARCHER,  //Bonus 2
	DWARF    //Bonus 5

}classes;

enum resultado{
	p1wins,
	p2wins
};

typedef struct Atributos{

	char name[50];
	int hp;
	int strength;
	int spell;
	classes class;

}atrib;

enum  ostype{
	windows = 1,
	macos,
	linux
};


typedef enum Teclado{

	up = 72,
	down = 80,
	left = 75,
	right = 77,
	enter = 13,
	esc = 27
}key;


/*coleta de dados*/
void scanome(char nome[],int n, int pos, int heroe);
void coletadados(atrib heroe[], int n, int pos);
/*animacoes*/
void magevsmage(int dano, int atacante);
void archervsarcher(int dano, int atacante);
void dwarfvsdwarf(int dano, int atacante);
void magevsarcher(int dano, int atacante);
void archervsmage(int dano, int atacante);
void magevsdwarf(int dano, int atacante);
void dwarfvsmage(int dano, int atacante);
void archervsdwarf(int dano, int atacante);
void dwarfvsarcher(int dano, int atacante);
/*sistema*/
void clear(int sistema);
void color(int sistema, int cor);
/*interface*/
void titulo();
int menu(int sis);
void os(int *sistema);
void aviso(int sistema);
int classe(classes *heroeclass, atrib heroe[], int sis, int n);
void luta(classes *heroe1class, classes *heroe2class, int dano, int atacante);
void contagem();
/*calculos*/
float random();
void damage(atrib heroe[], int HeroeNumber);
int rodadas(atrib heroe[], int atacante);


void main()
{
	int op,          // armazena a escolha das opcoes do menu principal
	sis = 0, 		 // armazena a escolha do sistema operacional
	i,        	     // contador
	winner = -1,
	score1 = 0,
	score2 = 0,
	ok = 0,
	hp1,
	hp2;     // armazena o ganhador de cada rodada

	atrib heroe[2];  // armazena os dois herois

	system("mode con:cols=115 lines=30"); //Define o tamanho do terminal




	srand( (unsigned)time(NULL) ); // semente do numero randomico de acordo com a hora do computador

	os(&sis);   // escolha do sistema operacional
	aviso(sis); // instrucoes da navegacao do menu principal

	while(1){

		op = menu(sis);

		switch(op){

			case iniciar: clear(sis);
			/*escolha da classe e atributos do heroi 1*/
			do{
				if (classe(&heroe[0].class, heroe, sis, 0) == 1) // se o usuario pressionar a tecla ESC atribui 1 em ok e sai da coleta
				{
					ok = 1;
					break;
				}else{
					/*escolha da classe e atributos do heroi 2*/
					ok = classe(&heroe[1].class, heroe, sis, 1);
				}
			}while(ok == 0);

			/*COMBATE DOS PERSONAGENS*/

			if (ok != 1) // Caso ele tenha cancelado a coleta ele ignora o combate
			{
				/*armazena o hp definido pelo usuario para curar os herois apos o combate*/
				hp1 = heroe[0].hp;
				hp2 = heroe[1].hp;

				for (int i = 0; i < 3; i++)    // inicia o combate de 3 rodadas
				{
					contagem();
					if (score1 == score2)
					{
						winner = rodadas(heroe, 1); // retorna o ganhador para a contagem de pontos
					}
					if (score1 > score2)
					{
						winner = rodadas(heroe, 2); // retorna o ganhador para a contagem de pontos
					}
					if(score2 > score1)
					{
						winner = rodadas(heroe, 1); // retorna o ganhador para a contagem de pontos
					}


					if (winner == 0)
					{
						/*daz a contagem dos pontos*/
						score1++;
					}else{
						score2++;
					}
					/*anuncia o ganhador da rodada*/
					printf("\t\t\t\t       Ganhador da rodada %d\n\t\t\t\t           Jogador %d\n\nVida do jogador 1 = %d | Vida do jogador 2 = %d\n\n", i+1, winner+1, heroe[0].hp, heroe[1].hp);
					Sleep(5000);

					/*Cura os herois*/
					heroe[0].hp = hp1;
					heroe[1].hp = hp2;
				}

				if (score1 > score2) // emprime a classe do ganhador 1
				{
					printf("\t\t\t\t       O Heroi 1\nNome: %s\n", heroe[0].name);
					switch(heroe[0].class){
						case MAGE: printf("\t\t\t\t       Classe: Mago\n"); break;
						case ARCHER: printf("\t\t\t\t       Classe: Arqueiro\n"); break;
						case DWARF: printf("\t\t\t\t       Classe: Anao\n"); break;
					}
					printf("\t\t\t\t       Ganhou!!\n\n");
					system("PAUSE");
				}else{ // emprime a classe do ganhador 2
					printf("\t\t\t\t       O Heroi 2\nNome: %s\n", heroe[1].name);
					switch(heroe[1].class){
						case MAGE: printf("\t\t\t\t       Classe: Mago\n"); break;
						case ARCHER: printf("\t\t\t\t       Classe: Arqueiro\n"); break;
						case DWARF: printf("\t\t\t\t       Classe: Anao\n"); break;
					}
					printf("\t\t\t\t       Ganhou!!\n\n");
					system("PAUSE");
				}
			}

			break;

			case instrucoes: clear(sis);
			printf("\n\n\tEscolha dois personagens para lutarem por 3 rodadas,\n\tescolha seus nomes e atributos como hp, forca e spell,\n\to primeiro a ficar com 0 de vida, perde a rodada,\n\t");
			printf("quem vencer mais vezes, ganha a partida.\n\n\n");
			system("PAUSE");
			break;
			case sair: exit(0); break;
			default: printf("Ocorreu um erro\n");
		}
	}

}


void scanome(char nome[],int n, int pos, int heroe)
{
	int i = 0,espaco = 0;
	char tecla;
	while (i < n) {
		fflush(stdin);
		tecla = getch();

		if (i == 0) { // primeira letra em maiusculo
			if (tecla >= 'a' && tecla <= 'z' && espaco == 0) {
				nome[i] = tecla - 32;
				printf("%c", nome[i]);
				i++;
				fflush(stdin);
				tecla  = '\x00';
			}
			if (tecla >= 'A' && tecla <= 'Z' && espaco == 0) {
				nome[i] = tecla;
				printf("%c", nome[i]);
				i++;
				fflush(stdin);
			}
		}

		if (i >= 1) { // preenche a string normalmente
			if (tecla >= 'a' && tecla <= 'z' && espaco == 0) {
				nome[i] = tecla;
				printf("%c", nome[i]);
				i++;
				fflush(stdin);
			}
			if (tecla >= 'A' && tecla <= 'Z' && espaco == 0) {
				nome[i] = tecla;
				printf("%c", nome[i]);
				i++;
				fflush(stdin);
			}
			/*caso seja a proxima letra apos o espaco, torna a letra maiscula*/
			if (tecla >= 'a' && tecla <= 'z' && espaco == 1) {
				nome[i] = tecla - 32;
				printf("%c", nome[i]);
				i++;
				espaco = 0;
				fflush(stdin);
			}
			if (tecla >= 'A' && tecla <= 'Z' && espaco == 1) {
				nome[i] = tecla;
				printf("%c", nome[i]);
				i++;
				espaco = 0;
				fflush(stdin);
			}

			if (tecla == ' ') { // se pressionar a tecla espaco adiciona o espaco na string
				nome[i] = tecla;
				printf(" ");
				espaco = 1;
				i++;
				fflush(stdin);
			}

			if (tecla == 13) { // se pressionar o Enter finaliza a coleta da string
				nome[i] = '\0';
				break;
			}
			/* caso pressione o backspace apaga a string regressivamente*/
			if (tecla == 8 && i > 0) {
				printf("\x08");
				i--;
				if (nome[i-1] == ' ') {
					espaco = 1;
				}
				if (nome[i] == ' ') {
					espaco = 0;
				}
				nome[i] = '\0';
				system("cls");
				switch(pos){
					case 0:
					printf(" Selecione o Her\xA2i  %d                        **\n", heroe);
					printf("  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\t\t\t    *  *\n");
					printf("  \xBA %c Mago       \xBA\t\t\t   *    *\n", 254);
					printf("  \xBA %c Arqueiro   \xBA\t\t\t  *      *\n", 255);
					printf("  \xBA %c An\xC6o       \xBA\t\t\t *        *\n", 255);
					printf("  \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\t\t    *****          *****\n");
					printf("\t\t\t           *                    *\n");
					printf("\t\t\t           *   --------------   *\n");
					printf("\t\t\t            ******************** \n");
					printf("\t\t\t               *            *    \n");
					printf("\t\t\t               *  (0)  (0)  *    \n");
					printf("\t\t\t               *     (      *    \n");
					printf("\t\t\t               *            *    \n");
					printf("\t\t\t                *   -__-   *    \n");
					printf("\t\t\t              *  *||    ||*  *  \n");
					printf("\t\t\t           *       ||||||       *\n");
					printf("\t\t\t         *          ||||          *\n");
					printf("\t\t\t       *             ||             *\n");
					printf("  ESC para voltar\n");
					printf("Nome do personagem: ");
					break;
					case 1:
					printf(" Selecione o Her\xA2i  %d                        ****\n", heroe);
					printf("  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\t\t\t  *        *\n");
					printf("  \xBA %c Mago       \xBA\t\t        *            *\n", 255);
					printf("  \xBA %c Arqueiro   \xBA\t\t      *                *\n", 254);
					printf("  \xBA %c An\xC6o       \xBA\t\t     *                  *\n", 255);
					printf("  \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\t\t    *                    *\n");
					printf("\t\t\t           *      **********      *\n");
					printf("\t\t\t          *     *            *     *\n");
					printf("\t\t\t          *    *              *    *\n");
					printf("\t\t\t          *    *   (0)  (0)   *    *\n");
					printf("\t\t\t          *    *      <       *    *\n");
					printf("\t\t\t          *    *              *    *\n");
					printf("\t\t\t          *    *     ____     *    *\n");
					printf("\t\t\t          *    *              *    *\n");
					printf("\t\t\t         *      *            *      *\n");
					printf("\t\t\t       **         *        *         **\n");
					printf("\t\t\t      *             *    *             *\n");
					printf("\t\t\t     *                **                *\n");
					printf("  ESC para voltar\n");
					printf("Nome do personagem: ");
					break;
					case 2:
					printf(" Selecione o Her\xA2i  %d                        ***\n", heroe);
					printf("  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\t\t\t  *       *\n");
					printf("  \xBA %c Mago       \xBA\t\t        *           *\n", 255);
					printf("  \xBA %c Arqueiro   \xBA\t\t      *               *\n", 255);
					printf("  \xBA %c An\xC6o       \xBA\t\t     *       ***       *\n", 254);
					printf("  \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\t\t    *      *     *      *\n");
					printf("\t\t\t           *     *         *     *\n");
					printf("\t\t\t          *     *           *     *\n");
					printf("\t\t\t          *    *  ```\\ /```  *    *\n");
					printf("\t\t\t         *    *   (0)| |(0)   *    *\n");
					printf("\t\t\t        *    *      (   )      *    *\n");
					printf("\t\t\t       *    *     ```` ````     *    *\n");
					printf("\t\t\t        ****    ``   ___   ``    ****\n");
					printf("\t\t\t            * ``             `` *\n");
					printf("\t\t\t          *|||||||||||||||||||||||*\n");
					printf("\t\t\t       *   |||||||||||||||||||||||   *\n");
					printf("\t\t\t    *      |||||||||||||||||||||||      *\n");
					printf("\t\t\t *          |||||||||||||||||||||          *\n");
					printf("\t\t       *              |||||||||||||||||              *\n");
					printf("  ESC para voltar\n");
					printf("Nome do personagem: ");
					break;
				}
				if (i > 0) {
					printf("%s",nome);
				}
				fflush(stdin);
			}
		}

	}
}


void coletadados(atrib heroe[], int n, int pos){
	int valor = 0;

	printf("Nome do personagem: ");
	scanome(heroe[n].name, 50, pos, n+1);

	while(1){
		printf("\nQuantidade do hp: ");
		scanf("%d", &valor);
		if (valor >= 0 && valor <=100)
		{
			heroe[n].hp = valor;
			valor = 0;
			break;
		}else{
			printf("Informe um valor de 0 a 100\n");
		}
	}


	while(1){
		printf("Quantidade da forca: ");
		scanf("%d", &valor);
		if (valor >= 50 && valor <=100)
		{
			heroe[n].strength = valor;
			valor = 0;
			break;
		}else{
			printf("Informe um valor de 50 a 100\n");
		}
	}

	while(1){
		printf("Quantidade do spell: ");
		scanf("%d", &valor);
		if (valor >= 50 && valor <=100)
		{
			heroe[n].spell = valor;
			valor = 0;
			break;
		}else{
			printf("Informe um valor de 50 a 100\n");
		}
	}
}

void magevsmage(int dano, int atacante)
{
	/****************************************************** COMBAT ******************************************************************/
	/*************************************************** MAGE VS MAGE ***************************************************************/
	if (atacante == 0)
	{
		/****************************************************** FRAME 1 *****************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                                                    *   --------------   *\n");
		printf("     ********************                                                      ********************\n");
		printf("        *            *             ______                      ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/                    \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                          ***              *            *\n");
		printf("         *   -__-   *              ***                            ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                              ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 2 ***************************************************************/
		system("cls");
		printf("2\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                                                    *   --------------   *\n");
		printf("     ********************                                                      ********************\n");
		printf("        *            *             ______                      ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\   )                / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/   )                \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                          ***              *            *\n");
		printf("         *   -__-   *              ***                            ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                              ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 3 ***************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                                                    *   --------------   *\n");
		printf("     ********************                                                      ********************\n");
		printf("        *            *             ______     )                ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\     )              / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/     )              \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***       )                  ***              *            *\n");
		printf("         *   -__-   *              ***                            ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                              ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 4 ***************************************************************/
		system("cls");
		printf("4\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                                                    *   --------------   *\n");
		printf("     ********************                     )                                ********************\n");
		printf("        *            *             ______      )               ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\      )             / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/      )             \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***        )                 ***              *            *\n");
		printf("         *   -__-   *              ***        )                   ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                              ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 5 ***************************************************************/
		system("cls");
		printf("5\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                    )                               *   --------------   *\n");
		printf("     ********************                      )                               ********************\n");
		printf("        *            *             ______       )              ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\       )            / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/       )            \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***         )                ***              *            *\n");
		printf("         *   -__-   *              ***         )                  ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***         )                    ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 6 ***************************************************************/
		system("cls");
		printf("6\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                     )                              *   --------------   *\n");
		printf("     ********************                       )                              ********************\n");
		printf("        *            *             ______        )             ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\        )           / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/        )           \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***          )               ***              *            *\n");
		printf("         *   -__-   *              ***          )                 ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***          )                   ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 7 ***************************************************************/
		system("cls");
		printf("7\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                      )                             *   --------------   *\n");
		printf("     ********************                        )                             ********************\n");
		printf("        *            *             ______         )            ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\         )          / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/         )          \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***           )              ***              *            *\n");
		printf("         *   -__-   *              ***           )                ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***           )                  ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 8 ***************************************************************/
		system("cls");
		printf("8\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                       )                            *   --------------   *\n");
		printf("     ********************                         )                            ********************\n");
		printf("        *            *             ______          )           ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\          )         / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/          )         \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***            )             ***              *            *\n");
		printf("         *   -__-   *              ***            )               ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***            )                 ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 9 ***************************************************************/
		system("cls");
		printf("9\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                        )                           *   --------------   *\n");
		printf("     ********************                          )                           ********************\n");
		printf("        *            *             ______           )          ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\           )        / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/           )        \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***             )            ***              *            *\n");
		printf("         *   -__-   *              ***             )              ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***             )                ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 10 **************************************************************/
		system("cls");
		printf("10\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                         )                          *   --------------   *\n");
		printf("     ********************                           )                          ********************\n");
		printf("        *            *             ______            )         ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\            )       / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/            )       \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***              )           ***              *            *\n");
		printf("         *   -__-   *              ***              )             ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***              )               ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 11 **************************************************************/
		system("cls");
		printf("11\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                          )                         *   --------------   *\n");
		printf("     ********************                            )                         ********************\n");
		printf("        *            *             ______             )        ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\             )      / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/             )      \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***               )          ***              *            *\n");
		printf("         *   -__-   *              ***               )            ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***               )              ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 12 **************************************************************/
		system("cls");
		printf("12\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                           )                        *   --------------   *\n");
		printf("     ********************                             )                        ********************\n");
		printf("        *            *             ______              )       ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\              )     / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/              )     \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                )         ***              *            *\n");
		printf("         *   -__-   *              ***                )           ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                )             ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 13 **************************************************************/
		system("cls");
		printf("13\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                            )                       *   --------------   *\n");
		printf("     ********************                              )                       ********************\n");
		printf("        *            *             ______               )      ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\               )    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/               )    \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                 )        ***              *            *\n");
		printf("         *   -__-   *              ***                 )          ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                 )            ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 14 **************************************************************/
		system("cls");
		printf("14\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                             )                      *   --------------   *\n");
		printf("     ********************                               )                      ********************\n");
		printf("        *            *             ______                )     ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                )   / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/                )   \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                  )       ***              *            *\n");
		printf("         *   -__-   *              ***                  )         ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                  )           ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 15 **************************************************************/
		system("cls");
		printf("15\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                              )                     *   --------------   *\n");
		printf("     ********************                                )                     ********************\n");
		printf("        *            *             ______                 )    ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                 )  / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/                 )  \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                   )      ***              *            *\n");
		printf("         *   -__-   *              ***                   )        ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                   )          ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 16 **************************************************************/
		system("cls");
		printf("16\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                               )                    *   --------------   *\n");
		printf("     ********************                                 )                    ********************\n");
		printf("        *            *             ______                  )   ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                  ) / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/                  ) \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                    )     ***              *            *\n");
		printf("         *   -__-   *              ***                    )       ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                    )         ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 17 **************************************************************/
		system("cls");
		printf("17\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                              -%d     *****          *****\n",dano);
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                                )                   *   --------------   *\n");
		printf("     ********************                                  )                   ********************\n");
		printf("        *            *             ______                   )  ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                   )/ /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/                   )\\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                     )    ***              *            *\n");
		printf("         *   -__-   *              ***                     )      ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                     )        ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 18 **************************************************************/
		system("cls");
		printf("18\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                     -%d        *        *\n",dano);
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                                 )                  *   --------------   *\n");
		printf("     ********************                                   )                  ********************\n");
		printf("        *            *             ______                    ) ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/                    \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                      )   ***              *            *\n");
		printf("         *   -__-   *              ***                      )     ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                      )       ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 19 **************************************************************/
		system("cls");
		printf("19\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                     -%d          *      *\n",dano);
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                                 )                  *   --------------   *\n");
		printf("     ********************                                   )                  ********************\n");
		printf("        *            *             ______                      ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/                    \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                          ***              *            *\n");
		printf("         *   -__-   *              ***                      )     ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                      )       ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 20 **************************************************************/
		system("cls");
		printf("20\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                           -%d      *    *\n",dano);
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                                                    *   --------------   *\n");
		printf("     ********************                                                      ********************\n");
		printf("        *            *             ______                      ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                    / /  \\ \\            * ( 0)  ( 0) *\n");
		printf("        *     (      *            \\_\\__/_/                    \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                          ***              *            *\n");
		printf("         *   -__-   *              ***                            ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                              ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(500);
	}
	if (atacante == 1)
	{
		/******************************************************** FRAME 21 **************************************************************/
		system("cls");
		printf("21\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                                                    *   --------------   *\n");
		printf("     ********************                                                      ********************\n");
		printf("        *            *             ______                      ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                    / /  \\ \\            * (0 )  ( 0) *\n");
		printf("        *     (      *            \\_\\__/_/                    \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                          ***              *            *\n");
		printf("         *   -__-   *              ***                            ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                              ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                                                    *   --------------   *\n");
		printf("     ********************                                                      ********************\n");
		printf("        *            *             ______                      ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                (   / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/                (   \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                          ***              *            *\n");
		printf("         *   -__-   *              ***                            ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                              ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 23 **************************************************************/
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                                                    *   --------------   *\n");
		printf("     ********************                                                      ********************\n");
		printf("        *            *             ______                      ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/                    \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                          ***              *            *\n");
		printf("         *   -__-   *              ***                            ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                              ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("2\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                                                    *   --------------   *\n");
		printf("     ********************                                                      ********************\n");
		printf("        *            *             ______                      ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                (   / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/                (   \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                          ***              *            *\n");
		printf("         *   -__-   *              ***                            ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                              ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 3 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                                                    *   --------------   *\n");
		printf("     ********************                                                      ********************\n");
		printf("        *            *             ______                 (    ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\               (    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/               (    \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                   (      ***              *            *\n");
		printf("         *   -__-   *              ***                            ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                              ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                                                    *   --------------   *\n");
		printf("     ********************                                 (                    ********************\n");
		printf("        *            *             ______                (     ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\              (     / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/              (     \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                  (       ***              *            *\n");
		printf("         *   -__-   *              ***                    (       ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                              ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                                (                   *   --------------   *\n");
		printf("     ********************                                (                     ********************\n");
		printf("        *            *             ______               (      ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\             (      / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/             (      \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                 (        ***              *            *\n");
		printf("         *   -__-   *              ***                   (        ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                     (        ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                               (                    *   --------------   *\n");
		printf("     ********************                               (                      ********************\n");
		printf("        *            *             ______              (       ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\            (       / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/            (       \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                (         ***              *            *\n");
		printf("         *   -__-   *              ***                  (         ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                    (         ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                              (                     *   --------------   *\n");
		printf("     ********************                              (                       ********************\n");
		printf("        *            *             ______             (        ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\           (        / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/           (        \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***               (          ***              *            *\n");
		printf("         *   -__-   *              ***                 (          ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                   (          ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                             (                      *   --------------   *\n");
		printf("     ********************                             (                        ********************\n");
		printf("        *            *             ______            (         ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\          (         / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/          (         \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***              (           ***              *            *\n");
		printf("         *   -__-   *              ***                (           ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                  (           ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                            (                       *   --------------   *\n");
		printf("     ********************                            (                         ********************\n");
		printf("        *            *             ______           (          ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\         (          / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/         (          \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***             (            ***              *            *\n");
		printf("         *   -__-   *              ***               (            ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                 (            ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                           (                        *   --------------   *\n");
		printf("     ********************                           (                          ********************\n");
		printf("        *            *             ______          (           ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\        (           / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/        (           \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***            (             ***              *            *\n");
		printf("         *   -__-   *              ***              (             ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                (             ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                          (                         *   --------------   *\n");
		printf("     ********************                          (                           ********************\n");
		printf("        *            *             ______         (            ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\       (            / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/       (            \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***           (              ***              *            *\n");
		printf("         *   -__-   *              ***             (              ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***               (              ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                         (                          *   --------------   *\n");
		printf("     ********************                         (                            ********************\n");
		printf("        *            *             ______        (             ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\      (             / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/      (             \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***          (               ***              *            *\n");
		printf("         *   -__-   *              ***            (               ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***              (               ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                        (                           *   --------------   *\n");
		printf("     ********************                        (                             ********************\n");
		printf("        *            *             ______       (              ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\     (              / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/     (              \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***         (                ***              *            *\n");
		printf("         *   -__-   *              ***           (                ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***             (                ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                       (                            *   --------------   *\n");
		printf("     ********************                       (                              ********************\n");
		printf("        *            *             ______      (               ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\    (               / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/    (               \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***        (                 ***              *            *\n");
		printf("         *   -__-   *              ***          (                 ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***            (                 ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                      (                             *   --------------   *\n");
		printf("     ********************                      (                               ********************\n");
		printf("        *            *             ______     (                ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\   (                / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/   (                \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***       (                  ***              *            *\n");
		printf("         *   -__-   *              ***         (                  ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***           (                  ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                     (                              *   --------------   *\n");
		printf("     ********************                     (                                ********************\n");
		printf("        *            *             ______    (                 ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\  (                 / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/  (                 \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***      (                   ***              *            *\n");
		printf("         *   -__-   *              ***        (                   ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***          (                   ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                    (                               *   --------------   *\n");
		printf("     ********************                    (                                 ********************\n");
		printf("        *            *             ______   (                  ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\ (                  / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/ (                  \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***     (                    ***              *            *\n");
		printf("         *   -__-   *              ***       (                    ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***         (                    ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****  -%d                                                 *****          *****\n",dano);
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                   (                                *   --------------   *\n");
		printf("     ********************                   (                                  ********************\n");
		printf("        *            *             ______  (                   ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\(                   / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/(                   \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***    (                     ***              *            *\n");
		printf("         *   -__-   *              ***      (                     ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***        (                     ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *     -%d                                                        *        *\n",dano);
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                   (                                *   --------------   *\n");
		printf("     ********************                   (                                  ********************\n");
		printf("        *            *             ______  (                   ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/                    \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***    (                     ***              *            *\n");
		printf("         *   -__-   *              ***      (                     ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***        (                     ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *     -%d                                                          *      *\n",dano);
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                   (                                *   --------------   *\n");
		printf("     ********************                   (                                  ********************\n");
		printf("        *            *             ______                      ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/                    \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                          ***              *            *\n");
		printf("         *   -__-   *              ***      (                     ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***        (                     ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *     -%d                                                            *    *\n",dano);
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                                                    *   --------------   *\n");
		printf("     ********************                                                      ********************\n");
		printf("        *            *             ______                      ______             *            *\n");
		printf("        * (0 )  (0 ) *            / /  \\ \\                    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/                    \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                          ***              *            *\n");
		printf("         *   -__-   *              ***                            ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                              ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(500);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                                                    *   --------------   *\n");
		printf("     ********************                                                      ********************\n");
		printf("        *            *             ______                      ______             *            *\n");
		printf("        * (0 )  ( 0) *            / /  \\ \\                    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/                    \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                          ***              *            *\n");
		printf("         *   -__-   *              ***                            ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                              ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("3\n");
		printf("              **                                                                        **\n");
		printf("             *  *                                                                      *  *\n");
		printf("            *    *                                                                    *    *\n");
		printf("           *      *                                                                  *      *\n");
		printf("          *        *                                                                *        *\n");
		printf("     *****          *****                                                      *****          *****\n");
		printf("    *                    *                                                    *                    *\n");
		printf("    *   --------------   *                                                    *   --------------   *\n");
		printf("     ********************                                                      ********************\n");
		printf("        *            *             ______                      ______             *            *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("        *     (      *            \\_\\__/_/                    \\_\\__/_/            *     (      *\n");
		printf("        *            *              ***                          ***              *            *\n");
		printf("         *   -__-   *              ***                            ***              *   -__-   * \n");
		printf("       *  *||    ||*  *           ***                              ***           *  *||    ||*  *\n");
		printf("    *       ||||||       *       ***                                ***       *       ||||||       *\n");
		printf("  *          ||||          *    ***                                  ***    *          ||||          *\n");
		printf("*             ||             * ***                                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t);
	}


}


void archervsarcher(int dano, int atacante)
{
	if (atacante == 0)
	{
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                     *                           *\n");
		printf("     * *     *************     * *                                     * *     *************     * * \n");
		printf("     *  *  *               *  *  *                                     *  *  *               *  *  *\n");
		printf("     *  **                   **  *                                      *  **                  **  *\n");
		printf("      * *      * * * * *      * *                                        * *      * * * * *      * *\n");
		printf("       *     *           *     *                                          *     *           *     * \n");
		printf("       *   *               *   *                                          *   *               *   * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                          *   *  (0 )   (0 )  *   *\n");
		printf("       *   *       <       *   *                                          *   *       <       *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("       *   *      ___      *   *                                          *   *      ___      *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("      *     *             *     *                                        *     *             *     * \n");
		printf("   **         * _______ *         **                                  **         * _______ *         **\n");
		printf(" *              *     *              *                              *              *     *              *\n");
		printf("*                  *                  *                            *                  *                  * \n");
		printf("*                   *                 *                            *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                     *                           *\n");
		printf("     * *     *************     * *                                     * *     *************     * * \n");
		printf("     *  *  *               *  *  *                                     *  *  *               *  *  *\n");
		printf("     *  **                   **  *                                      *  **                  **  *\n");
		printf("      * *      * * * * *      * *                                  -%d   * *      * * * * *      * *\n",dano);
		printf("       *     *           *     *                                          *     *           *     * \n");
		printf("       *   *               *   *                                          *   *               *   * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                          *   *  (0 )   (0 )  *   *\n");
		printf("       *   *       <       *   *                                          *   *       <       *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("       *   *      ___      *   *                                          *   *      ___      *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("      *     *             *     *                                        *     *             *     * \n");
		printf("   **         * _______ *         **                                  **         * _______ *         **\n");
		printf(" *              *     *              *                              *              *     *              *\n");
		printf("*                  *                  *                            *                  *                  * \n");
		printf("*                   *                 *                            *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 3 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                     *                           *\n");
		printf("     * *     *************     * *                                     * *     *************     * * \n");
		printf("     *  *  *               *  *  *                                     *  *  *               *  *  *\n");
		printf("     *  **                   **  *                                 -%d  *  **                  **  *\n",dano);
		printf("      * *      * * * * *      * *                                        * *      * * * * *      * *\n");
		printf("       *     *           *     *                                          *     *           *     * \n");
		printf("       *   *               *   *                                          *   *               *   * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                          *   *  (0 )   (0 )  *   *\n");
		printf("       *   *       <       *   *                                          *   *       <       *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("       *   *      ___      *   *                                          *   *      ___      *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("      *     *             *     *                                        *     *             *     * \n");
		printf("   **         * _______ *         **                                  **         * _______ *         **\n");
		printf(" *              *     *              *                              *              *     *              *\n");
		printf("*                  *                  *                            *                  *                  * \n");
		printf("*                   *                 *                            *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 4 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                     *                           *\n");
		printf("     * *     *************     * *                                     * *     *************     * * \n");
		printf("     *  *  *               *  *  *                                 -%d *  *  *               *  *  *\n",dano);
		printf("     *  **                   **  *                                      *  **                  **  *\n");
		printf("      * *      * * * * *      * *                                        * *      * * * * *      * *\n");
		printf("       *     *           *     *                                          *     *           *     * \n");
		printf("       *   *               *   *                                          *   *               *   * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                          *   *  ( 0)   ( 0)  *   *\n");
		printf("       *   *       <       *   *                                          *   *       <       *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("       *   *      ___      *   *                                          *   *      ___      *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("      *     *             *     *                                        *     *             *     * \n");
		printf("   **         * _______ *         **                                  **         * _______ *         **\n");
		printf(" *              *     *              *                              *              *     *              *\n");
		printf("*                  *                  *                            *                  *                  * \n");
		printf("*                   *                 *                            *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 5 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                     *                           *\n");
		printf("     * *     *************     * *                                     * *     *************     * * \n");
		printf("     *  *  *               *  *  *                                     *  *  *               *  *  *\n");
		printf("     *  **                   **  *                                      *  **                  **  *\n");
		printf("      * *      * * * * *      * *                                        * *      * * * * *      * *\n");
		printf("       *     *           *     *                                          *     *           *     * \n");
		printf("       *   *               *   *                                          *   *               *   * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                          *   *  (0 )   ( 0)  *   *\n");
		printf("       *   *       <       *   *                                          *   *       <       *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("       *   *      ___      *   *                                          *   *      ___      *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("      *     *             *     *                                        *     *             *     * \n");
		printf("   **         * _______ *         **                                  **         * _______ *         **\n");
		printf(" *              *     *              *                              *              *     *              *\n");
		printf("*                  *                  *                            *                  *                  * \n");
		printf("*                   *                 *                            *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(500);
		/******************************************************** FRAME 6 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                     *                           *\n");
		printf("     * *     *************     * *                                     * *     *************     * * \n");
		printf("     *  *  *               *  *  *                                     *  *  *               *  *  *\n");
		printf("     *  **                   **  *                                      *  **                  **  *\n");
		printf("      * *      * * * * *      * *                                        * *      * * * * *      * *\n");
		printf("       *     *           *     *                                          *     *           *     * \n");
		printf("       *   *               *   *                                          *   *               *   * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                          *   *  (0 )   (0 )  *   *\n");
		printf("       *   *       <       *   *                                          *   *       <       *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("       *   *      ___      *   *                                          *   *      ___      *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("      *     *             *     *                                        *     *             *     * \n");
		printf("   **         * _______ *         **                                  **         * _______ *         **\n");
		printf(" *              *     *              *                              *              *     *              *\n");
		printf("*                  *                  *                            *                  *                  * \n");
		printf("*                   *                 *                            *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 7 **************************************************************/
	}
	if (atacante == 1)
	{
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                     *                           *\n");
		printf("     * *     *************     * *                                     * *     *************     * * \n");
		printf("     *  *  *               *  *  *                                     *  *  *               *  *  *\n");
		printf("     *  **                   **  *                                      *  **                  **  *\n");
		printf("      * *      * * * * *      * *                                        * *      * * * * *      * *\n");
		printf("       *     *           *     *                                          *     *           *     * \n");
		printf("       *   *               *   *                                          *   *               *   * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                          *   *  (0 )   (0 )  *   *\n");
		printf("       *   *       <       *   *                                          *   *       <       *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("       *   *      ___      *   *                                          *   *      ___      *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("      *     *             *     *                                        *     *             *     * \n");
		printf("   **         * _______ *         **                                  **         * _______ *         **\n");
		printf(" *              *     *              *                              *              *     *              *\n");
		printf("*                  *                  *                            *                  *                  * \n");
		printf("*                   *                 *                            *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                     *                           *\n");
		printf("     * *     *************     * *                                     * *     *************     * * \n");
		printf("     *  *  *               *  *  *                                     *  *  *               *  *  *\n");
		printf("     *  **                   **  *                                      *  **                  **  *\n");
		printf("      * *      * * * * *      * *    -%d                                 * *      * * * * *      * *\n",dano);
		printf("       *     *           *     *                                          *     *           *     * \n");
		printf("       *   *               *   *                                          *   *               *   * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                          *   *  (0 )   (0 )  *   *\n");
		printf("       *   *       <       *   *                                          *   *       <       *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("       *   *      ___      *   *                                          *   *      ___      *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("      *     *             *     *                                        *     *             *     * \n");
		printf("   **         * _______ *         **                                  **         * _______ *         **\n");
		printf(" *              *     *              *                              *              *     *              *\n");
		printf("*                  *                  *                            *                  *                  * \n");
		printf("*                   *                 *                            *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 3 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                     *                           *\n");
		printf("     * *     *************     * *                                     * *     *************     * * \n");
		printf("     *  *  *               *  *  *                                     *  *  *               *  *  *\n");
		printf("     *  **                   **  *   -%d                                *  **                  **  *\n",dano);
		printf("      * *      * * * * *      * *                                        * *      * * * * *      * *\n");
		printf("       *     *           *     *                                          *     *           *     * \n");
		printf("       *   *               *   *                                          *   *               *   * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                          *   *  (0 )   (0 )  *   *\n");
		printf("       *   *       <       *   *                                          *   *       <       *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("       *   *      ___      *   *                                          *   *      ___      *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("      *     *             *     *                                        *     *             *     * \n");
		printf("   **         * _______ *         **                                  **         * _______ *         **\n");
		printf(" *              *     *              *                              *              *     *              *\n");
		printf("*                  *                  *                            *                  *                  * \n");
		printf("*                   *                 *                            *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 4 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                     *                           *\n");
		printf("     * *     *************     * *                                     * *     *************     * * \n");
		printf("     *  *  *               *  *  *    -%d                              *  *  *               *  *  *\n",dano);
		printf("     *  **                   **  *                                      *  **                  **  *\n");
		printf("      * *      * * * * *      * *                                        * *      * * * * *      * *\n");
		printf("       *     *           *     *                                          *     *           *     * \n");
		printf("       *   *               *   *                                          *   *               *   * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                          *   *  ( 0)   ( 0)  *   *\n");
		printf("       *   *       <       *   *                                          *   *       <       *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("       *   *      ___      *   *                                          *   *      ___      *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("      *     *             *     *                                        *     *             *     * \n");
		printf("   **         * _______ *         **                                  **         * _______ *         **\n");
		printf(" *              *     *              *                              *              *     *              *\n");
		printf("*                  *                  *                            *                  *                  * \n");
		printf("*                   *                 *                            *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 5 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                     *                           *\n");
		printf("     * *     *************     * *                                     * *     *************     * * \n");
		printf("     *  *  *               *  *  *                                     *  *  *               *  *  *\n");
		printf("     *  **                   **  *                                      *  **                  **  *\n");
		printf("      * *      * * * * *      * *                                        * *      * * * * *      * *\n");
		printf("       *     *           *     *                                          *     *           *     * \n");
		printf("       *   *               *   *                                          *   *               *   * \n");
		printf("       *   *  (0 )   ( 0)  *   *                                          *   *  (0 )   (0 )  *   *\n");
		printf("       *   *       <       *   *                                          *   *       <       *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("       *   *      ___      *   *                                          *   *      ___      *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("      *     *             *     *                                        *     *             *     * \n");
		printf("   **         * _______ *         **                                  **         * _______ *         **\n");
		printf(" *              *     *              *                              *              *     *              *\n");
		printf("*                  *                  *                            *                  *                  * \n");
		printf("*                   *                 *                            *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(500);
		/******************************************************** FRAME 6 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                     *                           *\n");
		printf("     * *     *************     * *                                     * *     *************     * * \n");
		printf("     *  *  *               *  *  *                                     *  *  *               *  *  *\n");
		printf("     *  **                   **  *                                      *  **                  **  *\n");
		printf("      * *      * * * * *      * *                                        * *      * * * * *      * *\n");
		printf("       *     *           *     *                                          *     *           *     * \n");
		printf("       *   *               *   *                                          *   *               *   * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                          *   *  (0 )   (0 )  *   *\n");
		printf("       *   *       <       *   *                                          *   *       <       *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("       *   *      ___      *   *                                          *   *      ___      *   *\n");
		printf("       *   *               *   *                                          *   *               *   *\n");
		printf("      *     *             *     *                                        *     *             *     * \n");
		printf("   **         * _______ *         **                                  **         * _______ *         **\n");
		printf(" *              *     *              *                              *              *     *              *\n");
		printf("*                  *                  *                            *                  *                  * \n");
		printf("*                   *                 *                            *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 7 **************************************************************/
	}
}

void dwarfvsdwarf(int dano, int atacante)
{
	if (atacante == 0)
	{
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("                      ***                                                               ***  \n");
		printf("                 *           *                                                     *           *   \n");
		printf("              *       ***       *                                               *       ***       *  \n");
		printf("             *      *     *      *                                             *      *     *      *   \n");
		printf("            *     *         *     *                                           *     *         *     *  \n");
		printf("           *     *           *     *                                         *     *           *     *\n");
		printf("           *    *  ```\\ /```  *    *                                        *    *  ```\\ /```  *    * \n");
		printf("          *    * (  0)| |(  0) *    *                                       *    * (0  )| |(0  ) *    *\n");
		printf("         *    *      (   )      *    *                                     *    *      (   )      *    *\n");
		printf("        *    *     ```` ````     *    *                                   *    *     ```` ````     *    * \n");
		printf("         ****    ``   ___   ``    ****                                     ****    ``   ___   ``    **** \n");
		printf("             * ``             `` *                                             * ``             `` *\n");
		printf("           *|||||||||||||||||||||||*                                         *|||||||||||||||||||||||*\n");
		printf("        *   |||||||||||||||||||||||   *                                   *   |||||||||||||||||||||||   *\n");
		printf("     *      |||||||||||||||||||||||      *                             *      |||||||||||||||||||||||      *\n");
		printf("  *          |||||||||||||||||||||          *                       *          |||||||||||||||||||||          *\n");
		printf("*              |||||||||||||||||              *                   *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                      ***                                                               ***  \n");
		printf("                 *           *                                                     *           *   \n");
		printf("              *       ***       *                                               *       ***       *  \n");
		printf("             *      *     *      *                                             *      *     *      *   \n");
		printf("            *     *         *     *                                           *     *         *     *  \n");
		printf("           *     *           *     *                                   -%d   *     *           *     *\n",dano);
		printf("           *    *  ```\\ /```  *    *                                        *    *  ```\\ /```  *    * \n");
		printf("          *    * (  0)| |(  0) *    *                                       *    * (0  )| |(0  ) *    *\n");
		printf("         *    *      (   )      *    *                                     *    *      (   )      *    *\n");
		printf("        *    *     ```` ````     *    *                                   *    *     ```` ````     *    * \n");
		printf("         ****    ``   ___   ``    ****                                     ****    ``   ___   ``    **** \n");
		printf("             * ``             `` *                                             * ``             `` *\n");
		printf("           *|||||||||||||||||||||||*                                         *|||||||||||||||||||||||*\n");
		printf("        *   |||||||||||||||||||||||   *                                   *   |||||||||||||||||||||||   *\n");
		printf("     *      |||||||||||||||||||||||      *                             *      |||||||||||||||||||||||      *\n");
		printf("  *          |||||||||||||||||||||          *                       *          |||||||||||||||||||||          *\n");
		printf("*              |||||||||||||||||              *                   *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                      ***                                                               ***  \n");
		printf("                 *           *                                                     *           *   \n");
		printf("              *       ***       *                                               *       ***       *  \n");
		printf("             *      *     *      *                                             *      *     *      *   \n");
		printf("            *     *         *     *                                      -%d  *     *         *     *  \n",dano);
		printf("           *     *           *     *                                         *     *           *     *\n");
		printf("           *    *  ```\\ /```  *    *                                        *    *  ```\\ /```  *    * \n");
		printf("          *    * (  0)| |(  0) *    *                                       *    * (0  )| |(0  ) *    *\n");
		printf("         *    *      (   )      *    *                                     *    *      (   )      *    *\n");
		printf("        *    *     ```` ````     *    *                                   *    *     ```` ````     *    * \n");
		printf("         ****    ``   ___   ``    ****                                     ****    ``   ___   ``    **** \n");
		printf("             * ``             `` *                                             * ``             `` *\n");
		printf("           *|||||||||||||||||||||||*                                         *|||||||||||||||||||||||*\n");
		printf("        *   |||||||||||||||||||||||   *                                   *   |||||||||||||||||||||||   *\n");
		printf("     *      |||||||||||||||||||||||      *                             *      |||||||||||||||||||||||      *\n");
		printf("  *          |||||||||||||||||||||          *                       *          |||||||||||||||||||||          *\n");
		printf("*              |||||||||||||||||              *                   *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                      ***                                                               ***  \n");
		printf("                 *           *                                                     *           *   \n");
		printf("              *       ***       *                                               *       ***       *  \n");
		printf("             *      *     *      *                                        -%d  *      *     *      *   \n",dano);
		printf("            *     *         *     *                                           *     *         *     *  \n");
		printf("           *     *           *     *                                         *     *           *     *\n");
		printf("           *    *  ```\\ /```  *    *                                        *    *  ```\\ /```  *    * \n");
		printf("          *    * (  0)| |(  0) *    *                                       *    * (  0)| |(  0) *    *\n");
		printf("         *    *      (   )      *    *                                     *    *      (   )      *    *\n");
		printf("        *    *     ```` ````     *    *                                   *    *     ```` ````     *    * \n");
		printf("         ****    ``   ___   ``    ****                                     ****    ``   ___   ``    **** \n");
		printf("             * ``             `` *                                             * ``             `` *\n");
		printf("           *|||||||||||||||||||||||*                                         *|||||||||||||||||||||||*\n");
		printf("        *   |||||||||||||||||||||||   *                                   *   |||||||||||||||||||||||   *\n");
		printf("     *      |||||||||||||||||||||||      *                             *      |||||||||||||||||||||||      *\n");
		printf("  *          |||||||||||||||||||||          *                       *          |||||||||||||||||||||          *\n");
		printf("*              |||||||||||||||||              *                   *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                      ***                                                               ***  \n");
		printf("                 *           *                                                     *           *   \n");
		printf("              *       ***       *                                               *       ***       *  \n");
		printf("             *      *     *      *                                             *      *     *      *   \n");
		printf("            *     *         *     *                                           *     *         *     *  \n");
		printf("           *     *           *     *                                         *     *           *     *\n");
		printf("           *    *  ```\\ /```  *    *                                        *    *  ```\\ /```  *    * \n");
		printf("          *    * (  0)| |(  0) *    *                                       *    * (0  )| |(  0) *    *\n");
		printf("         *    *      (   )      *    *                                     *    *      (   )      *    *\n");
		printf("        *    *     ```` ````     *    *                                   *    *     ```` ````     *    * \n");
		printf("         ****    ``   ___   ``    ****                                     ****    ``   ___   ``    **** \n");
		printf("             * ``             `` *                                             * ``             `` *\n");
		printf("           *|||||||||||||||||||||||*                                         *|||||||||||||||||||||||*\n");
		printf("        *   |||||||||||||||||||||||   *                                   *   |||||||||||||||||||||||   *\n");
		printf("     *      |||||||||||||||||||||||      *                             *      |||||||||||||||||||||||      *\n");
		printf("  *          |||||||||||||||||||||          *                       *          |||||||||||||||||||||          *\n");
		printf("*              |||||||||||||||||              *                   *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(500);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                      ***                                                               ***  \n");
		printf("                 *           *                                                     *           *   \n");
		printf("              *       ***       *                                               *       ***       *  \n");
		printf("             *      *     *      *                                             *      *     *      *   \n");
		printf("            *     *         *     *                                           *     *         *     *  \n");
		printf("           *     *           *     *                                         *     *           *     *\n");
		printf("           *    *  ```\\ /```  *    *                                        *    *  ```\\ /```  *    * \n");
		printf("          *    * (  0)| |(  0) *    *                                       *    * (0  )| |(0  ) *    *\n");
		printf("         *    *      (   )      *    *                                     *    *      (   )      *    *\n");
		printf("        *    *     ```` ````     *    *                                   *    *     ```` ````     *    * \n");
		printf("         ****    ``   ___   ``    ****                                     ****    ``   ___   ``    **** \n");
		printf("             * ``             `` *                                             * ``             `` *\n");
		printf("           *|||||||||||||||||||||||*                                         *|||||||||||||||||||||||*\n");
		printf("        *   |||||||||||||||||||||||   *                                   *   |||||||||||||||||||||||   *\n");
		printf("     *      |||||||||||||||||||||||      *                             *      |||||||||||||||||||||||      *\n");
		printf("  *          |||||||||||||||||||||          *                       *          |||||||||||||||||||||          *\n");
		printf("*              |||||||||||||||||              *                   *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
	}
	if (atacante == 1)
	{
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("                      ***                                                               ***  \n");
		printf("                 *           *                                                     *           *   \n");
		printf("              *       ***       *                                               *       ***       *  \n");
		printf("             *      *     *      *                                             *      *     *      *   \n");
		printf("            *     *         *     *                                           *     *         *     *  \n");
		printf("           *     *           *     *                                         *     *           *     *\n");
		printf("           *    *  ```\\ /```  *    *                                        *    *  ```\\ /```  *    * \n");
		printf("          *    * (  0)| |(  0) *    *                                       *    * (0  )| |(0  ) *    *\n");
		printf("         *    *      (   )      *    *                                     *    *      (   )      *    *\n");
		printf("        *    *     ```` ````     *    *                                   *    *     ```` ````     *    * \n");
		printf("         ****    ``   ___   ``    ****                                     ****    ``   ___   ``    **** \n");
		printf("             * ``             `` *                                             * ``             `` *\n");
		printf("           *|||||||||||||||||||||||*                                         *|||||||||||||||||||||||*\n");
		printf("        *   |||||||||||||||||||||||   *                                   *   |||||||||||||||||||||||   *\n");
		printf("     *      |||||||||||||||||||||||      *                             *      |||||||||||||||||||||||      *\n");
		printf("  *          |||||||||||||||||||||          *                       *          |||||||||||||||||||||          *\n");
		printf("*              |||||||||||||||||              *                   *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                      ***                                                               ***  \n");
		printf("                 *           *                                                     *           *   \n");
		printf("              *       ***       *                                               *       ***       *  \n");
		printf("             *      *     *      *                                             *      *     *      *   \n");
		printf("            *     *         *     *                                           *     *         *     *  \n");
		printf("           *     *           *     *    -%d                                  *     *           *     *\n",dano);
		printf("           *    *  ```\\ /```  *    *                                        *    *  ```\\ /```  *    * \n");
		printf("          *    * (  0)| |(  0) *    *                                       *    * (0  )| |(0  ) *    *\n");
		printf("         *    *      (   )      *    *                                     *    *      (   )      *    *\n");
		printf("        *    *     ```` ````     *    *                                   *    *     ```` ````     *    * \n");
		printf("         ****    ``   ___   ``    ****                                     ****    ``   ___   ``    **** \n");
		printf("             * ``             `` *                                             * ``             `` *\n");
		printf("           *|||||||||||||||||||||||*                                         *|||||||||||||||||||||||*\n");
		printf("        *   |||||||||||||||||||||||   *                                   *   |||||||||||||||||||||||   *\n");
		printf("     *      |||||||||||||||||||||||      *                             *      |||||||||||||||||||||||      *\n");
		printf("  *          |||||||||||||||||||||          *                       *          |||||||||||||||||||||          *\n");
		printf("*              |||||||||||||||||              *                   *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                      ***                                                               ***  \n");
		printf("                 *           *                                                     *           *   \n");
		printf("              *       ***       *                                               *       ***       *  \n");
		printf("             *      *     *      *                                             *      *     *      *   \n");
		printf("            *     *         *     *    -%d                                    *     *         *     *  \n",dano);
		printf("           *     *           *     *                                         *     *           *     *\n");
		printf("           *    *  ```\\ /```  *    *                                        *    *  ```\\ /```  *    * \n");
		printf("          *    * (  0)| |(  0) *    *                                       *    * (0  )| |(0  ) *    *\n");
		printf("         *    *      (   )      *    *                                     *    *      (   )      *    *\n");
		printf("        *    *     ```` ````     *    *                                   *    *     ```` ````     *    * \n");
		printf("         ****    ``   ___   ``    ****                                     ****    ``   ___   ``    **** \n");
		printf("             * ``             `` *                                             * ``             `` *\n");
		printf("           *|||||||||||||||||||||||*                                         *|||||||||||||||||||||||*\n");
		printf("        *   |||||||||||||||||||||||   *                                   *   |||||||||||||||||||||||   *\n");
		printf("     *      |||||||||||||||||||||||      *                             *      |||||||||||||||||||||||      *\n");
		printf("  *          |||||||||||||||||||||          *                       *          |||||||||||||||||||||          *\n");
		printf("*              |||||||||||||||||              *                   *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                      ***                                                               ***  \n");
		printf("                 *           *                                                     *           *   \n");
		printf("              *       ***       *                                               *       ***       *  \n");
		printf("             *      *     *      *    -%d                                      *      *     *      *   \n",dano);
		printf("            *     *         *     *                                           *     *         *     *  \n");
		printf("           *     *           *     *                                         *     *           *     *\n");
		printf("           *    *  ```\\ /```  *    *                                        *    *  ```\\ /```  *    * \n");
		printf("          *    * (0  )| |(0  ) *    *                                       *    * (0  )| |(0  ) *    *\n");
		printf("         *    *      (   )      *    *                                     *    *      (   )      *    *\n");
		printf("        *    *     ```` ````     *    *                                   *    *     ```` ````     *    * \n");
		printf("         ****    ``   ___   ``    ****                                     ****    ``   ___   ``    **** \n");
		printf("             * ``             `` *                                             * ``             `` *\n");
		printf("           *|||||||||||||||||||||||*                                         *|||||||||||||||||||||||*\n");
		printf("        *   |||||||||||||||||||||||   *                                   *   |||||||||||||||||||||||   *\n");
		printf("     *      |||||||||||||||||||||||      *                             *      |||||||||||||||||||||||      *\n");
		printf("  *          |||||||||||||||||||||          *                       *          |||||||||||||||||||||          *\n");
		printf("*              |||||||||||||||||              *                   *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                      ***                                                               ***  \n");
		printf("                 *           *                                                     *           *   \n");
		printf("              *       ***       *                                               *       ***       *  \n");
		printf("             *      *     *      *                                             *      *     *      *   \n");
		printf("            *     *         *     *                                           *     *         *     *  \n");
		printf("           *     *           *     *                                         *     *           *     *\n");
		printf("           *    *  ```\\ /```  *    *                                        *    *  ```\\ /```  *    * \n");
		printf("          *    * (0  )| |(  0) *    *                                       *    * (0  )| |(0  ) *    *\n");
		printf("         *    *      (   )      *    *                                     *    *      (   )      *    *\n");
		printf("        *    *     ```` ````     *    *                                   *    *     ```` ````     *    * \n");
		printf("         ****    ``   ___   ``    ****                                     ****    ``   ___   ``    **** \n");
		printf("             * ``             `` *                                             * ``             `` *\n");
		printf("           *|||||||||||||||||||||||*                                         *|||||||||||||||||||||||*\n");
		printf("        *   |||||||||||||||||||||||   *                                   *   |||||||||||||||||||||||   *\n");
		printf("     *      |||||||||||||||||||||||      *                             *      |||||||||||||||||||||||      *\n");
		printf("  *          |||||||||||||||||||||          *                       *          |||||||||||||||||||||          *\n");
		printf("*              |||||||||||||||||              *                   *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(500);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                      ***                                                               ***  \n");
		printf("                 *           *                                                     *           *   \n");
		printf("              *       ***       *                                               *       ***       *  \n");
		printf("             *      *     *      *                                             *      *     *      *   \n");
		printf("            *     *         *     *                                           *     *         *     *  \n");
		printf("           *     *           *     *                                         *     *           *     *\n");
		printf("           *    *  ```\\ /```  *    *                                        *    *  ```\\ /```  *    * \n");
		printf("          *    * (  0)| |(  0) *    *                                       *    * (0  )| |(0  ) *    *\n");
		printf("         *    *      (   )      *    *                                     *    *      (   )      *    *\n");
		printf("        *    *     ```` ````     *    *                                   *    *     ```` ````     *    * \n");
		printf("         ****    ``   ___   ``    ****                                     ****    ``   ___   ``    **** \n");
		printf("             * ``             `` *                                             * ``             `` *\n");
		printf("           *|||||||||||||||||||||||*                                         *|||||||||||||||||||||||*\n");
		printf("        *   |||||||||||||||||||||||   *                                   *   |||||||||||||||||||||||   *\n");
		printf("     *      |||||||||||||||||||||||      *                             *      |||||||||||||||||||||||      *\n");
		printf("  *          |||||||||||||||||||||          *                       *          |||||||||||||||||||||          *\n");
		printf("*              |||||||||||||||||              *                   *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
	}
}

void magevsarcher(int dano, int atacante)
{
	if (atacante == 0)
	{
		/****************************************************** FRAME 1 *****************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                            \n");
		printf("             *  *                                                         *                           *\n");
		printf("            *    *                                                        * *     *************     * * \n");
		printf("           *      *                                                       *  *  *               *  *  *\n");
		printf("          *        *                                                      *  **                  **  *\n");
		printf("     *****          *****                                                  * *      * * * * *      * *\n");
		printf("    *                    *                                                  *     *           *     * \n");
		printf("    *   --------------   *                                                  *   *               *   * \n");
		printf("     ********************                                                   *   *  (0 )   (0 )  *   *\n");
		printf("        *            *             ______                                   *   *       <       *   *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                                  *   *               *   *\n");
		printf("        *     (      *            \\_\\__/_/                                  *   *      ___      *   *\n");
		printf("        *            *              ***                                     *   *               *   *\n");
		printf("         *   -__-   *              ***                                     *     *             *     * \n");
		printf("       *  *||    ||*  *           ***                                   **         * _______ *         **\n");
		printf("    *       ||||||       *       ***                                  *              *     *              *\n");
		printf("  *          ||||          *    ***                                  *                  *                  * \n");
		printf("*             ||             * ***                                   *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/****************************************************** FRAME 1 *****************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                            \n");
		printf("             *  *                                                         *                           *\n");
		printf("            *    *                                                        * *     *************     * * \n");
		printf("           *      *                                                       *  *  *               *  *  *\n");
		printf("          *        *                                                      *  **                  **  *\n");
		printf("     *****          *****                                                  * *      * * * * *      * *\n");
		printf("    *                    *                                                  *     *           *     * \n");
		printf("    *   --------------   *                                           -%d    *   *               *   * \n",dano);
		printf("     ********************                                                   *   *  (0 )   (0 )  *   *\n");
		printf("        *            *             ______                                   *   *       <       *   *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                                  *   *               *   *\n");
		printf("        *     (      *            \\_\\__/_/                                  *   *      ___      *   *\n");
		printf("        *            *              ***                                     *   *               *   *\n");
		printf("         *   -__-   *              ***                                     *     *             *     * \n");
		printf("       *  *||    ||*  *           ***                                   **         * _______ *         **\n");
		printf("    *       ||||||       *       ***                                  *              *     *              *\n");
		printf("  *          ||||          *    ***                                  *                  *                  * \n");
		printf("*             ||             * ***                                   *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 ***************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                            \n");
		printf("             *  *                                                         *                           *\n");
		printf("            *    *                                                        * *     *************     * * \n");
		printf("           *      *                                                       *  *  *               *  *  *\n");
		printf("          *        *                                                      *  **                  **  *\n");
		printf("     *****          *****                                                  * *      * * * * *      * *\n");
		printf("    *                    *                                           -%d    *     *           *     * \n",dano);
		printf("    *   --------------   *                                                  *   *               *   * \n");
		printf("     ********************                                                   *   *  (0 )   (0 )  *   *\n");
		printf("        *            *             ______                                   *   *       <       *   *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                                  *   *               *   *\n");
		printf("        *     (      *            \\_\\__/_/                                  *   *      ___      *   *\n");
		printf("        *            *              ***                                     *   *               *   *\n");
		printf("         *   -__-   *              ***                                     *     *             *     * \n");
		printf("       *  *||    ||*  *           ***                                   **         * _______ *         **\n");
		printf("    *       ||||||       *       ***                                  *              *     *              *\n");
		printf("  *          ||||          *    ***                                  *                  *                  * \n");
		printf("*             ||             * ***                                   *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 ***************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                            \n");
		printf("             *  *                                                         *                           *\n");
		printf("            *    *                                                        * *     *************     * * \n");
		printf("           *      *                                                       *  *  *               *  *  *\n");
		printf("          *        *                                                      *  **                  **  *\n");
		printf("     *****          *****                                            -%d   * *      * * * * *      * *\n",dano);
		printf("    *                    *                                                  *     *           *     * \n");
		printf("    *   --------------   *                                                  *   *               *   * \n");
		printf("     ********************                                                   *   *  ( 0)   ( 0)  *   *\n");
		printf("        *            *             ______                                   *   *       <       *   *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                                  *   *               *   *\n");
		printf("        *     (      *            \\_\\__/_/                                  *   *      ___      *   *\n");
		printf("        *            *              ***                                     *   *               *   *\n");
		printf("         *   -__-   *              ***                                     *     *             *     * \n");
		printf("       *  *||    ||*  *           ***                                   **         * _______ *         **\n");
		printf("    *       ||||||       *       ***                                  *              *     *              *\n");
		printf("  *          ||||          *    ***                                  *                  *                  * \n");
		printf("*             ||             * ***                                   *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 ***************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                            \n");
		printf("             *  *                                                         *                           *\n");
		printf("            *    *                                                        * *     *************     * * \n");
		printf("           *      *                                                       *  *  *               *  *  *\n");
		printf("          *        *                                                      *  **                  **  *\n");
		printf("     *****          *****                                                  * *      * * * * *      * *\n");
		printf("    *                    *                                                  *     *           *     * \n");
		printf("    *   --------------   *                                                  *   *               *   * \n");
		printf("     ********************                                                   *   *  (0 )   ( 0)  *   *\n");
		printf("        *            *             ______                                   *   *       <       *   *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                                  *   *               *   *\n");
		printf("        *     (      *            \\_\\__/_/                                  *   *      ___      *   *\n");
		printf("        *            *              ***                                     *   *               *   *\n");
		printf("         *   -__-   *              ***                                     *     *             *     * \n");
		printf("       *  *||    ||*  *           ***                                   **         * _______ *         **\n");
		printf("    *       ||||||       *       ***                                  *              *     *              *\n");
		printf("  *          ||||          *    ***                                  *                  *                  * \n");
		printf("*             ||             * ***                                   *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(500);
		/****************************************************** FRAME 1 *****************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                            \n");
		printf("             *  *                                                         *                           *\n");
		printf("            *    *                                                        * *     *************     * * \n");
		printf("           *      *                                                       *  *  *               *  *  *\n");
		printf("          *        *                                                      *  **                  **  *\n");
		printf("     *****          *****                                                  * *      * * * * *      * *\n");
		printf("    *                    *                                                  *     *           *     * \n");
		printf("    *   --------------   *                                                  *   *               *   * \n");
		printf("     ********************                                                   *   *  (0 )   (0 )  *   *\n");
		printf("        *            *             ______                                   *   *       <       *   *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                                  *   *               *   *\n");
		printf("        *     (      *            \\_\\__/_/                                  *   *      ___      *   *\n");
		printf("        *            *              ***                                     *   *               *   *\n");
		printf("         *   -__-   *              ***                                     *     *             *     * \n");
		printf("       *  *||    ||*  *           ***                                   **         * _______ *         **\n");
		printf("    *       ||||||       *       ***                                  *              *     *              *\n");
		printf("  *          ||||          *    ***                                  *                  *                  * \n");
		printf("*             ||             * ***                                   *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/****************************************************** FRAME 1 *****************************************************************/
	}
	if (atacante == 1)
	{
		/****************************************************** FRAME 1 *****************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                            \n");
		printf("             *  *                                                         *                           *\n");
		printf("            *    *                                                        * *     *************     * * \n");
		printf("           *      *                                                       *  *  *               *  *  *\n");
		printf("          *        *                                                      *  **                  **  *\n");
		printf("     *****          *****                                                  * *      * * * * *      * *\n");
		printf("    *                    *                                                  *     *           *     * \n");
		printf("    *   --------------   *                                                  *   *               *   * \n");
		printf("     ********************                                                   *   *  (0 )   (0 )  *   *\n");
		printf("        *            *             ______                                   *   *       <       *   *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                                  *   *               *   *\n");
		printf("        *     (      *            \\_\\__/_/                                  *   *      ___      *   *\n");
		printf("        *            *              ***                                     *   *               *   *\n");
		printf("         *   -__-   *              ***                                     *     *             *     * \n");
		printf("       *  *||    ||*  *           ***                                   **         * _______ *         **\n");
		printf("    *       ||||||       *       ***                                  *              *     *              *\n");
		printf("  *          ||||          *    ***                                  *                  *                  * \n");
		printf("*             ||             * ***                                   *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/****************************************************** FRAME 1 *****************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                            \n");
		printf("             *  *                                                         *                           *\n");
		printf("            *    *                                                        * *     *************     * * \n");
		printf("           *      *                                                       *  *  *               *  *  *\n");
		printf("          *        *                                                      *  **                  **  *\n");
		printf("     *****          *****                                                  * *      * * * * *      * *\n");
		printf("    *                    *                                                  *     *           *     * \n");
		printf("    *   --------------   *       -%d                                        *   *               *   * \n",dano);
		printf("     ********************                                                   *   *  (0 )   (0 )  *   *\n");
		printf("        *            *             ______                                   *   *       <       *   *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                                  *   *               *   *\n");
		printf("        *     (      *            \\_\\__/_/                                  *   *      ___      *   *\n");
		printf("        *            *              ***                                     *   *               *   *\n");
		printf("         *   -__-   *              ***                                     *     *             *     * \n");
		printf("       *  *||    ||*  *           ***                                   **         * _______ *         **\n");
		printf("    *       ||||||       *       ***                                  *              *     *              *\n");
		printf("  *          ||||          *    ***                                  *                  *                  * \n");
		printf("*             ||             * ***                                   *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 ***************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                            \n");
		printf("             *  *                                                         *                           *\n");
		printf("            *    *                                                        * *     *************     * * \n");
		printf("           *      *                                                       *  *  *               *  *  *\n");
		printf("          *        *                                                      *  **                  **  *\n");
		printf("     *****          *****                                                  * *      * * * * *      * *\n");
		printf("    *                    *      -%d                                         *     *           *     * \n",dano);
		printf("    *   --------------   *                                                  *   *               *   * \n");
		printf("     ********************                                                   *   *  (0 )   (0 )  *   *\n");
		printf("        *            *             ______                                   *   *       <       *   *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                                  *   *               *   *\n");
		printf("        *     (      *            \\_\\__/_/                                  *   *      ___      *   *\n");
		printf("        *            *              ***                                     *   *               *   *\n");
		printf("         *   -__-   *              ***                                     *     *             *     * \n");
		printf("       *  *||    ||*  *           ***                                   **         * _______ *         **\n");
		printf("    *       ||||||       *       ***                                  *              *     *              *\n");
		printf("  *          ||||          *    ***                                  *                  *                  * \n");
		printf("*             ||             * ***                                   *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 ***************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                            \n");
		printf("             *  *                                                         *                           *\n");
		printf("            *    *                                                        * *     *************     * * \n");
		printf("           *      *                                                       *  *  *               *  *  *\n");
		printf("          *        *                                                      *  **                  **  *\n");
		printf("     *****          *****       -%d                                        * *      * * * * *      * *\n",dano);
		printf("    *                    *                                                  *     *           *     * \n");
		printf("    *   --------------   *                                                  *   *               *   * \n");
		printf("     ********************                                                   *   *  (0 )   (0 )  *   *\n");
		printf("        *            *             ______                                   *   *       <       *   *\n");
		printf("        * (0 )  (0 ) *            / /  \\ \\                                  *   *               *   *\n");
		printf("        *     (      *            \\_\\__/_/                                  *   *      ___      *   *\n");
		printf("        *            *              ***                                     *   *               *   *\n");
		printf("         *   -__-   *              ***                                     *     *             *     * \n");
		printf("       *  *||    ||*  *           ***                                   **         * _______ *         **\n");
		printf("    *       ||||||       *       ***                                  *              *     *              *\n");
		printf("  *          ||||          *    ***                                  *                  *                  * \n");
		printf("*             ||             * ***                                   *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 ***************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                            \n");
		printf("             *  *                                                         *                           *\n");
		printf("            *    *                                                        * *     *************     * * \n");
		printf("           *      *                                                       *  *  *               *  *  *\n");
		printf("          *        *                                                      *  **                  **  *\n");
		printf("     *****          *****                                                  * *      * * * * *      * *\n");
		printf("    *                    *                                                  *     *           *     * \n");
		printf("    *   --------------   *                                                  *   *               *   * \n");
		printf("     ********************                                                   *   *  (0 )   (0 )  *   *\n");
		printf("        *            *             ______                                   *   *       <       *   *\n");
		printf("        * (0 )  ( 0) *            / /  \\ \\                                  *   *               *   *\n");
		printf("        *     (      *            \\_\\__/_/                                  *   *      ___      *   *\n");
		printf("        *            *              ***                                     *   *               *   *\n");
		printf("         *   -__-   *              ***                                     *     *             *     * \n");
		printf("       *  *||    ||*  *           ***                                   **         * _______ *         **\n");
		printf("    *       ||||||       *       ***                                  *              *     *              *\n");
		printf("  *          ||||          *    ***                                  *                  *                  * \n");
		printf("*             ||             * ***                                   *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(500);
		/****************************************************** FRAME 1 *****************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                            \n");
		printf("             *  *                                                         *                           *\n");
		printf("            *    *                                                        * *     *************     * * \n");
		printf("           *      *                                                       *  *  *               *  *  *\n");
		printf("          *        *                                                      *  **                  **  *\n");
		printf("     *****          *****                                                  * *      * * * * *      * *\n");
		printf("    *                    *                                                  *     *           *     * \n");
		printf("    *   --------------   *                                                  *   *               *   * \n");
		printf("     ********************                                                   *   *  (0 )   (0 )  *   *\n");
		printf("        *            *             ______                                   *   *       <       *   *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                                  *   *               *   *\n");
		printf("        *     (      *            \\_\\__/_/                                  *   *      ___      *   *\n");
		printf("        *            *              ***                                     *   *               *   *\n");
		printf("         *   -__-   *              ***                                     *     *             *     * \n");
		printf("       *  *||    ||*  *           ***                                   **         * _______ *         **\n");
		printf("    *       ||||||       *       ***                                  *              *     *              *\n");
		printf("  *          ||||          *    ***                                  *                  *                  * \n");
		printf("*             ||             * ***                                   *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/****************************************************** FRAME 1 *****************************************************************/
	}
}

void archervsmage(int dano, int atacante)
{
	if (atacante == 0)
	{
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("                                                                                    **\n");
		printf("     *                           *                                                 *  *\n");
		printf("     * *     *************     * *                                                *    *\n");
		printf("     *  *  *               *  *  *                                               *      *\n");
		printf("     *  **                   **  *                                              *        *\n");
		printf("      * *      * * * * *      * *                                          *****          *****\n");
		printf("       *     *           *     *                                          *                    *\n");
		printf("       *   *               *   *                                          *   --------------   *\n");
		printf("       *   *  ( 0)   ( 0)  *   *                                           ********************\n");
		printf("       *   *       <       *   *                            ______             *            *\n");
		printf("       *   *               *   *                           / /  \\ \\            * (0 )  (0 ) *\n");
		printf("       *   *      ___      *   *                           \\_\\__/_/            *     (      *\n");
		printf("       *   *               *   *                              ***              *            *\n");
		printf("      *     *             *     *                              ***              *   -__-   * \n");
		printf("   **         * _______ *         **                            ***           *  *||    ||*  *\n");
		printf(" *              *     *              *                           ***       *       ||||||       *\n");
		printf("*                  *                  *                           ***    *          ||||          *\n");
		printf("*                   *                 *                            *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                    **\n");
		printf("     *                           *                                                 *  *\n");
		printf("     * *     *************     * *                                                *    *\n");
		printf("     *  *  *               *  *  *                                               *      *\n");
		printf("     *  **                   **  *                                              *        *\n");
		printf("      * *      * * * * *      * *                                          *****          *****\n");
		printf("       *     *           *     *                                          *                    *\n");
		printf("       *   *               *   *                                          *   --------------   *\n");
		printf("       *   *  ( 0)   ( 0)  *   *                                   -%d     ********************\n",dano);
		printf("       *   *       <       *   *                            ______             *            *\n");
		printf("       *   *               *   *                           / /  \\ \\            * (0 )  (0 ) *\n");
		printf("       *   *      ___      *   *                           \\_\\__/_/            *     (      *\n");
		printf("       *   *               *   *                              ***              *            *\n");
		printf("      *     *             *     *                              ***              *   -__-   * \n");
		printf("   **         * _______ *         **                            ***           *  *||    ||*  *\n");
		printf(" *              *     *              *                           ***       *       ||||||       *\n");
		printf("*                  *                  *                           ***    *          ||||          *\n");
		printf("*                   *                 *                            *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                    **\n");
		printf("     *                           *                                                 *  *\n");
		printf("     * *     *************     * *                                                *    *\n");
		printf("     *  *  *               *  *  *                                               *      *\n");
		printf("     *  **                   **  *                                              *        *\n");
		printf("      * *      * * * * *      * *                                          *****          *****\n");
		printf("       *     *           *     *                                          *                    *\n");
		printf("       *   *               *   *                                   -%d    *   --------------   *\n",dano);
		printf("       *   *  ( 0)   ( 0)  *   *                                           ********************\n");
		printf("       *   *       <       *   *                            ______             *            *\n");
		printf("       *   *               *   *                           / /  \\ \\            * (0 )  (0 ) *\n");
		printf("       *   *      ___      *   *                           \\_\\__/_/            *     (      *\n");
		printf("       *   *               *   *                              ***              *            *\n");
		printf("      *     *             *     *                              ***              *   -__-   * \n");
		printf("   **         * _______ *         **                            ***           *  *||    ||*  *\n");
		printf(" *              *     *              *                           ***       *       ||||||       *\n");
		printf("*                  *                  *                           ***    *          ||||          *\n");
		printf("*                   *                 *                            *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                    **\n");
		printf("     *                           *                                                 *  *\n");
		printf("     * *     *************     * *                                                *    *\n");
		printf("     *  *  *               *  *  *                                               *      *\n");
		printf("     *  **                   **  *                                              *        *\n");
		printf("      * *      * * * * *      * *                                          *****          *****\n");
		printf("       *     *           *     *                                   -%d    *                    *\n",dano);
		printf("       *   *               *   *                                          *   --------------   *\n");
		printf("       *   *  ( 0)   ( 0)  *   *                                           ********************\n");
		printf("       *   *       <       *   *                            ______             *            *\n");
		printf("       *   *               *   *                           / /  \\ \\            * ( 0)  ( 0) *\n");
		printf("       *   *      ___      *   *                           \\_\\__/_/            *     (      *\n");
		printf("       *   *               *   *                              ***              *            *\n");
		printf("      *     *             *     *                              ***              *   -__-   * \n");
		printf("   **         * _______ *         **                            ***           *  *||    ||*  *\n");
		printf(" *              *     *              *                           ***       *       ||||||       *\n");
		printf("*                  *                  *                           ***    *          ||||          *\n");
		printf("*                   *                 *                            *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                    **\n");
		printf("     *                           *                                                 *  *\n");
		printf("     * *     *************     * *                                                *    *\n");
		printf("     *  *  *               *  *  *                                               *      *\n");
		printf("     *  **                   **  *                                              *        *\n");
		printf("      * *      * * * * *      * *                                          *****          *****\n");
		printf("       *     *           *     *                                          *                    *\n");
		printf("       *   *               *   *                                          *   --------------   *\n");
		printf("       *   *  ( 0)   ( 0)  *   *                                           ********************\n");
		printf("       *   *       <       *   *                            ______             *            *\n");
		printf("       *   *               *   *                           / /  \\ \\            * (0 )  ( 0) *\n");
		printf("       *   *      ___      *   *                           \\_\\__/_/            *     (      *\n");
		printf("       *   *               *   *                              ***              *            *\n");
		printf("      *     *             *     *                              ***              *   -__-   * \n");
		printf("   **         * _______ *         **                            ***           *  *||    ||*  *\n");
		printf(" *              *     *              *                           ***       *       ||||||       *\n");
		printf("*                  *                  *                           ***    *          ||||          *\n");
		printf("*                   *                 *                            *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(500);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                    **\n");
		printf("     *                           *                                                 *  *\n");
		printf("     * *     *************     * *                                                *    *\n");
		printf("     *  *  *               *  *  *                                               *      *\n");
		printf("     *  **                   **  *                                              *        *\n");
		printf("      * *      * * * * *      * *                                          *****          *****\n");
		printf("       *     *           *     *                                          *                    *\n");
		printf("       *   *               *   *                                          *   --------------   *\n");
		printf("       *   *  ( 0)   ( 0)  *   *                                           ********************\n");
		printf("       *   *       <       *   *                            ______             *            *\n");
		printf("       *   *               *   *                           / /  \\ \\            * (0 )  (0 ) *\n");
		printf("       *   *      ___      *   *                           \\_\\__/_/            *     (      *\n");
		printf("       *   *               *   *                              ***              *            *\n");
		printf("      *     *             *     *                              ***              *   -__-   * \n");
		printf("   **         * _______ *         **                            ***           *  *||    ||*  *\n");
		printf(" *              *     *              *                           ***       *       ||||||       *\n");
		printf("*                  *                  *                           ***    *          ||||          *\n");
		printf("*                   *                 *                            *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
	}
	if (atacante == 1)
	{
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("                                                                                    **\n");
		printf("     *                           *                                                 *  *\n");
		printf("     * *     *************     * *                                                *    *\n");
		printf("     *  *  *               *  *  *                                               *      *\n");
		printf("     *  **                   **  *                                              *        *\n");
		printf("      * *      * * * * *      * *                                          *****          *****\n");
		printf("       *     *           *     *                                          *                    *\n");
		printf("       *   *               *   *                                          *   --------------   *\n");
		printf("       *   *  ( 0)   ( 0)  *   *                                           ********************\n");
		printf("       *   *       <       *   *                            ______             *            *\n");
		printf("       *   *               *   *                           / /  \\ \\            * (0 )  (0 ) *\n");
		printf("       *   *      ___      *   *                           \\_\\__/_/            *     (      *\n");
		printf("       *   *               *   *                              ***              *            *\n");
		printf("      *     *             *     *                              ***              *   -__-   * \n");
		printf("   **         * _______ *         **                            ***           *  *||    ||*  *\n");
		printf(" *              *     *              *                           ***       *       ||||||       *\n");
		printf("*                  *                  *                           ***    *          ||||          *\n");
		printf("*                   *                 *                            *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                    **\n");
		printf("     *                           *                                                 *  *\n");
		printf("     * *     *************     * *                                                *    *\n");
		printf("     *  *  *               *  *  *                                               *      *\n");
		printf("     *  **                   **  *                                              *        *\n");
		printf("      * *      * * * * *      * *                                          *****          *****\n");
		printf("       *     *           *     *                                          *                    *\n");
		printf("       *   *               *   *                                          *   --------------   *\n");
		printf("       *   *  ( 0)   ( 0)  *   *     -%d                                   ********************\n",dano);
		printf("       *   *       <       *   *                            ______             *            *\n");
		printf("       *   *               *   *                           / /  \\ \\            * (0 )  (0 ) *\n");
		printf("       *   *      ___      *   *                           \\_\\__/_/            *     (      *\n");
		printf("       *   *               *   *                              ***              *            *\n");
		printf("      *     *             *     *                              ***              *   -__-   * \n");
		printf("   **         * _______ *         **                            ***           *  *||    ||*  *\n");
		printf(" *              *     *              *                           ***       *       ||||||       *\n");
		printf("*                  *                  *                           ***    *          ||||          *\n");
		printf("*                   *                 *                            *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                    **\n");
		printf("     *                           *                                                 *  *\n");
		printf("     * *     *************     * *                                                *    *\n");
		printf("     *  *  *               *  *  *                                               *      *\n");
		printf("     *  **                   **  *                                              *        *\n");
		printf("      * *      * * * * *      * *                                          *****          *****\n");
		printf("       *     *           *     *                                          *                    *\n");
		printf("       *   *               *   *      -%d                                 *   --------------   *\n",dano);
		printf("       *   *  ( 0)   ( 0)  *   *                                           ********************\n");
		printf("       *   *       <       *   *                            ______             *            *\n");
		printf("       *   *               *   *                           / /  \\ \\            * (0 )  (0 ) *\n");
		printf("       *   *      ___      *   *                           \\_\\__/_/            *     (      *\n");
		printf("       *   *               *   *                              ***              *            *\n");
		printf("      *     *             *     *                              ***              *   -__-   * \n");
		printf("   **         * _______ *         **                            ***           *  *||    ||*  *\n");
		printf(" *              *     *              *                           ***       *       ||||||       *\n");
		printf("*                  *                  *                           ***    *          ||||          *\n");
		printf("*                   *                 *                            *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                    **\n");
		printf("     *                           *                                                 *  *\n");
		printf("     * *     *************     * *                                                *    *\n");
		printf("     *  *  *               *  *  *                                               *      *\n");
		printf("     *  **                   **  *                                              *        *\n");
		printf("      * *      * * * * *      * *                                          *****          *****\n");
		printf("       *     *           *     *       -%d                                *                    *\n",dano);
		printf("       *   *               *   *                                          *   --------------   *\n");
		printf("       *   *  (0 )   (0 )  *   *                                           ********************\n");
		printf("       *   *       <       *   *                            ______             *            *\n");
		printf("       *   *               *   *                           / /  \\ \\            * (0 )  (0 ) *\n");
		printf("       *   *      ___      *   *                           \\_\\__/_/            *     (      *\n");
		printf("       *   *               *   *                              ***              *            *\n");
		printf("      *     *             *     *                              ***              *   -__-   * \n");
		printf("   **         * _______ *         **                            ***           *  *||    ||*  *\n");
		printf(" *              *     *              *                           ***       *       ||||||       *\n");
		printf("*                  *                  *                           ***    *          ||||          *\n");
		printf("*                   *                 *                            *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                    **\n");
		printf("     *                           *                                                 *  *\n");
		printf("     * *     *************     * *                                                *    *\n");
		printf("     *  *  *               *  *  *                                               *      *\n");
		printf("     *  **                   **  *                                              *        *\n");
		printf("      * *      * * * * *      * *                                          *****          *****\n");
		printf("       *     *           *     *                                          *                    *\n");
		printf("       *   *               *   *                                          *   --------------   *\n");
		printf("       *   *  (0 )   ( 0)  *   *                                           ********************\n");
		printf("       *   *       <       *   *                            ______             *            *\n");
		printf("       *   *               *   *                           / /  \\ \\            * (0 )  (0 ) *\n");
		printf("       *   *      ___      *   *                           \\_\\__/_/            *     (      *\n");
		printf("       *   *               *   *                              ***              *            *\n");
		printf("      *     *             *     *                              ***              *   -__-   * \n");
		printf("   **         * _______ *         **                            ***           *  *||    ||*  *\n");
		printf(" *              *     *              *                           ***       *       ||||||       *\n");
		printf("*                  *                  *                           ***    *          ||||          *\n");
		printf("*                   *                 *                            *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(500);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                    **\n");
		printf("     *                           *                                                 *  *\n");
		printf("     * *     *************     * *                                                *    *\n");
		printf("     *  *  *               *  *  *                                               *      *\n");
		printf("     *  **                   **  *                                              *        *\n");
		printf("      * *      * * * * *      * *                                          *****          *****\n");
		printf("       *     *           *     *                                          *                    *\n");
		printf("       *   *               *   *                                          *   --------------   *\n");
		printf("       *   *  ( 0)   ( 0)  *   *                                           ********************\n");
		printf("       *   *       <       *   *                            ______             *            *\n");
		printf("       *   *               *   *                           / /  \\ \\            * (0 )  (0 ) *\n");
		printf("       *   *      ___      *   *                           \\_\\__/_/            *     (      *\n");
		printf("       *   *               *   *                              ***              *            *\n");
		printf("      *     *             *     *                              ***              *   -__-   * \n");
		printf("   **         * _______ *         **                            ***           *  *||    ||*  *\n");
		printf(" *              *     *              *                           ***       *       ||||||       *\n");
		printf("*                  *                  *                           ***    *          ||||          *\n");
		printf("*                   *                 *                            *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
	}
}


void magevsdwarf(int dano, int atacante)
{
	if (atacante == 0)
	{
		/****************************************************** FRAME 1 *****************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                     \n");
		printf("             *  *                                                                          ***  \n");
		printf("            *    *                                                                    *            *   \n");
		printf("           *      *                                                                 *      ***       *  \n");
		printf("          *        *                                                              *      *     *      *   \n");
		printf("     *****          *****                                                        *     *         *     *  \n");
		printf("    *                    *                                                      *     *           *    *\n");
		printf("    *   --------------   *                                                     *    *  ```\\ /```  *    * \n");
		printf("     ********************                                                     *    * (0  )| |(0  ) *    *\n");
		printf("        *            *             ______                                    *    *      (   )      *    *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                                  *    *     ```` ````     *    * \n");
		printf("        *     (      *            \\_\\__/_/                                   ****    ``   ___   ``    **** \n");
		printf("        *            *              ***                                          * ``             `` *\n");
		printf("         *   -__-   *              ***                                         *|||||||||||||||||||||||*\n");
		printf("       *  *||    ||*  *           ***                                       *   |||||||||||||||||||||||   *\n");
		printf("    *       ||||||       *       ***                                     *      |||||||||||||||||||||||      *\n");
		printf("  *          ||||          *    ***                                   *          |||||||||||||||||||||          *\n");
		printf("*             ||             * ***                                  *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/****************************************************** FRAME 1 *****************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                     \n");
		printf("             *  *                                                                          ***  \n");
		printf("            *    *                                                                    *            *   \n");
		printf("           *      *                                                                 *      ***       *  \n");
		printf("          *        *                                                              *      *     *      *   \n");
		printf("     *****          *****                                                        *     *         *     *  \n");
		printf("    *                    *                                                      *     *           *    *\n");
		printf("    *   --------------   *                                                     *    *  ```\\ /```  *    * \n");
		printf("     ********************                                            -%d      *    * (0  )| |(0  ) *    *\n",dano);
		printf("        *            *             ______                                    *    *      (   )      *    *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                                  *    *     ```` ````     *    * \n");
		printf("        *     (      *            \\_\\__/_/                                   ****    ``   ___   ``    **** \n");
		printf("        *            *              ***                                          * ``             `` *\n");
		printf("         *   -__-   *              ***                                         *|||||||||||||||||||||||*\n");
		printf("       *  *||    ||*  *           ***                                       *   |||||||||||||||||||||||   *\n");
		printf("    *       ||||||       *       ***                                     *      |||||||||||||||||||||||      *\n");
		printf("  *          ||||          *    ***                                   *          |||||||||||||||||||||          *\n");
		printf("*             ||             * ***                                  *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/****************************************************** FRAME 1 *****************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                     \n");
		printf("             *  *                                                                          ***  \n");
		printf("            *    *                                                                    *            *   \n");
		printf("           *      *                                                                 *      ***       *  \n");
		printf("          *        *                                                              *      *     *      *   \n");
		printf("     *****          *****                                                        *     *         *     *  \n");
		printf("    *                    *                                                      *     *           *    *\n");
		printf("    *   --------------   *                                             -%d     *    *  ```\\ /```  *    * \n",dano);
		printf("     ********************                                                     *    * (0  )| |(0  ) *    *\n");
		printf("        *            *             ______                                    *    *      (   )      *    *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                                  *    *     ```` ````     *    * \n");
		printf("        *     (      *            \\_\\__/_/                                   ****    ``   ___   ``    **** \n");
		printf("        *            *              ***                                          * ``             `` *\n");
		printf("         *   -__-   *              ***                                         *|||||||||||||||||||||||*\n");
		printf("       *  *||    ||*  *           ***                                       *   |||||||||||||||||||||||   *\n");
		printf("    *       ||||||       *       ***                                     *      |||||||||||||||||||||||      *\n");
		printf("  *          ||||          *    ***                                   *          |||||||||||||||||||||          *\n");
		printf("*             ||             * ***                                  *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/****************************************************** FRAME 1 *****************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                     \n");
		printf("             *  *                                                                          ***  \n");
		printf("            *    *                                                                    *            *   \n");
		printf("           *      *                                                                 *      ***       *  \n");
		printf("          *        *                                                              *      *     *      *   \n");
		printf("     *****          *****                                                        *     *         *     *  \n");
		printf("    *                    *                                             -%d      *     *           *    *\n",dano);
		printf("    *   --------------   *                                                     *    *  ```\\ /```  *    * \n");
		printf("     ********************                                                     *    * (  0)| |(  0) *    *\n");
		printf("        *            *             ______                                    *    *      (   )      *    *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                                  *    *     ```` ````     *    * \n");
		printf("        *     (      *            \\_\\__/_/                                   ****    ``   ___   ``    **** \n");
		printf("        *            *              ***                                          * ``             `` *\n");
		printf("         *   -__-   *              ***                                         *|||||||||||||||||||||||*\n");
		printf("       *  *||    ||*  *           ***                                       *   |||||||||||||||||||||||   *\n");
		printf("    *       ||||||       *       ***                                     *      |||||||||||||||||||||||      *\n");
		printf("  *          ||||          *    ***                                   *          |||||||||||||||||||||          *\n");
		printf("*             ||             * ***                                  *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/****************************************************** FRAME 1 *****************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                     \n");
		printf("             *  *                                                                          ***  \n");
		printf("            *    *                                                                    *            *   \n");
		printf("           *      *                                                                 *      ***       *  \n");
		printf("          *        *                                                              *      *     *      *   \n");
		printf("     *****          *****                                                        *     *         *     *  \n");
		printf("    *                    *                                                      *     *           *    *\n");
		printf("    *   --------------   *                                                     *    *  ```\\ /```  *    * \n");
		printf("     ********************                                                     *    * (0  )| |(  0) *    *\n");
		printf("        *            *             ______                                    *    *      (   )      *    *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                                  *    *     ```` ````     *    * \n");
		printf("        *     (      *            \\_\\__/_/                                   ****    ``   ___   ``    **** \n");
		printf("        *            *              ***                                          * ``             `` *\n");
		printf("         *   -__-   *              ***                                         *|||||||||||||||||||||||*\n");
		printf("       *  *||    ||*  *           ***                                       *   |||||||||||||||||||||||   *\n");
		printf("    *       ||||||       *       ***                                     *      |||||||||||||||||||||||      *\n");
		printf("  *          ||||          *    ***                                   *          |||||||||||||||||||||          *\n");
		printf("*             ||             * ***                                  *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(500);
		/****************************************************** FRAME 1 *****************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                     \n");
		printf("             *  *                                                                          ***  \n");
		printf("            *    *                                                                    *            *   \n");
		printf("           *      *                                                                 *      ***       *  \n");
		printf("          *        *                                                              *      *     *      *   \n");
		printf("     *****          *****                                                        *     *         *     *  \n");
		printf("    *                    *                                                      *     *           *    *\n");
		printf("    *   --------------   *                                                     *    *  ```\\ /```  *    * \n");
		printf("     ********************                                                     *    * (0  )| |(0  ) *    *\n");
		printf("        *            *             ______                                    *    *      (   )      *    *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                                  *    *     ```` ````     *    * \n");
		printf("        *     (      *            \\_\\__/_/                                   ****    ``   ___   ``    **** \n");
		printf("        *            *              ***                                          * ``             `` *\n");
		printf("         *   -__-   *              ***                                         *|||||||||||||||||||||||*\n");
		printf("       *  *||    ||*  *           ***                                       *   |||||||||||||||||||||||   *\n");
		printf("    *       ||||||       *       ***                                     *      |||||||||||||||||||||||      *\n");
		printf("  *          ||||          *    ***                                   *          |||||||||||||||||||||          *\n");
		printf("*             ||             * ***                                  *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/****************************************************** FRAME 1 *****************************************************************/
	}
	if (atacante == 1)
	{
		/****************************************************** FRAME 1 *****************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                     \n");
		printf("             *  *                                                                          ***  \n");
		printf("            *    *                                                                    *            *   \n");
		printf("           *      *                                                                 *      ***       *  \n");
		printf("          *        *                                                              *      *     *      *   \n");
		printf("     *****          *****                                                        *     *         *     *  \n");
		printf("    *                    *                                                      *     *           *    *\n");
		printf("    *   --------------   *                                                     *    *  ```\\ /```  *    * \n");
		printf("     ********************                                                     *    * (0  )| |(0  ) *    *\n");
		printf("        *            *             ______                                    *    *      (   )      *    *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                                  *    *     ```` ````     *    * \n");
		printf("        *     (      *            \\_\\__/_/                                   ****    ``   ___   ``    **** \n");
		printf("        *            *              ***                                          * ``             `` *\n");
		printf("         *   -__-   *              ***                                         *|||||||||||||||||||||||*\n");
		printf("       *  *||    ||*  *           ***                                       *   |||||||||||||||||||||||   *\n");
		printf("    *       ||||||       *       ***                                     *      |||||||||||||||||||||||      *\n");
		printf("  *          ||||          *    ***                                   *          |||||||||||||||||||||          *\n");
		printf("*             ||             * ***                                  *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/****************************************************** FRAME 1 *****************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                     \n");
		printf("             *  *                                                                          ***  \n");
		printf("            *    *                                                                    *            *   \n");
		printf("           *      *                                                                 *      ***       *  \n");
		printf("          *        *                                                              *      *     *      *   \n");
		printf("     *****          *****                                                        *     *         *     *  \n");
		printf("    *                    *                                                      *     *           *    *\n");
		printf("    *   --------------   *                                                     *    *  ```\\ /```  *    * \n");
		printf("     ********************       -%d                                           *    * (0  )| |(0  ) *    *\n",dano);
		printf("        *            *             ______                                    *    *      (   )      *    *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                                  *    *     ```` ````     *    * \n");
		printf("        *     (      *            \\_\\__/_/                                   ****    ``   ___   ``    **** \n");
		printf("        *            *              ***                                          * ``             `` *\n");
		printf("         *   -__-   *              ***                                         *|||||||||||||||||||||||*\n");
		printf("       *  *||    ||*  *           ***                                       *   |||||||||||||||||||||||   *\n");
		printf("    *       ||||||       *       ***                                     *      |||||||||||||||||||||||      *\n");
		printf("  *          ||||          *    ***                                   *          |||||||||||||||||||||          *\n");
		printf("*             ||             * ***                                  *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/****************************************************** FRAME 1 *****************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                     \n");
		printf("             *  *                                                                          ***  \n");
		printf("            *    *                                                                    *            *   \n");
		printf("           *      *                                                                 *      ***       *  \n");
		printf("          *        *                                                              *      *     *      *   \n");
		printf("     *****          *****                                                        *     *         *     *  \n");
		printf("    *                    *                                                      *     *           *    *\n");
		printf("    *   --------------   *     -%d                                             *    *  ```\\ /```  *    * \n",dano);
		printf("     ********************                                                     *    * (0  )| |(0  ) *    *\n");
		printf("        *            *             ______                                    *    *      (   )      *    *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                                  *    *     ```` ````     *    * \n");
		printf("        *     (      *            \\_\\__/_/                                   ****    ``   ___   ``    **** \n");
		printf("        *            *              ***                                          * ``             `` *\n");
		printf("         *   -__-   *              ***                                         *|||||||||||||||||||||||*\n");
		printf("       *  *||    ||*  *           ***                                       *   |||||||||||||||||||||||   *\n");
		printf("    *       ||||||       *       ***                                     *      |||||||||||||||||||||||      *\n");
		printf("  *          ||||          *    ***                                   *          |||||||||||||||||||||          *\n");
		printf("*             ||             * ***                                  *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/****************************************************** FRAME 1 *****************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                     \n");
		printf("             *  *                                                                          ***  \n");
		printf("            *    *                                                                    *            *   \n");
		printf("           *      *                                                                 *      ***       *  \n");
		printf("          *        *                                                              *      *     *      *   \n");
		printf("     *****          *****                                                        *     *         *     *  \n");
		printf("    *                    *     -%d                                              *     *           *    *\n",dano);
		printf("    *   --------------   *                                                     *    *  ```\\ /```  *    * \n");
		printf("     ********************                                                     *    * (0  )| |(0  ) *    *\n");
		printf("        *            *             ______                                    *    *      (   )      *    *\n");
		printf("        * (0 )  (0 ) *            / /  \\ \\                                  *    *     ```` ````     *    * \n");
		printf("        *     (      *            \\_\\__/_/                                   ****    ``   ___   ``    **** \n");
		printf("        *            *              ***                                          * ``             `` *\n");
		printf("         *   -__-   *              ***                                         *|||||||||||||||||||||||*\n");
		printf("       *  *||    ||*  *           ***                                       *   |||||||||||||||||||||||   *\n");
		printf("    *       ||||||       *       ***                                     *      |||||||||||||||||||||||      *\n");
		printf("  *          ||||          *    ***                                   *          |||||||||||||||||||||          *\n");
		printf("*             ||             * ***                                  *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/****************************************************** FRAME 1 *****************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                     \n");
		printf("             *  *                                                                          ***  \n");
		printf("            *    *                                                                    *            *   \n");
		printf("           *      *                                                                 *      ***       *  \n");
		printf("          *        *                                                              *      *     *      *   \n");
		printf("     *****          *****                                                        *     *         *     *  \n");
		printf("    *                    *                                                      *     *           *    *\n");
		printf("    *   --------------   *                                                     *    *  ```\\ /```  *    * \n");
		printf("     ********************                                                     *    * (0  )| |(0  ) *    *\n");
		printf("        *            *             ______                                    *    *      (   )      *    *\n");
		printf("        * (0 )  ( 0) *            / /  \\ \\                                  *    *     ```` ````     *    * \n");
		printf("        *     (      *            \\_\\__/_/                                   ****    ``   ___   ``    **** \n");
		printf("        *            *              ***                                          * ``             `` *\n");
		printf("         *   -__-   *              ***                                         *|||||||||||||||||||||||*\n");
		printf("       *  *||    ||*  *           ***                                       *   |||||||||||||||||||||||   *\n");
		printf("    *       ||||||       *       ***                                     *      |||||||||||||||||||||||      *\n");
		printf("  *          ||||          *    ***                                   *          |||||||||||||||||||||          *\n");
		printf("*             ||             * ***                                  *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(500);
		/****************************************************** FRAME 1 *****************************************************************/
		system("cls");
		printf("1\n");
		printf("              **                                                                                     \n");
		printf("             *  *                                                                          ***  \n");
		printf("            *    *                                                                    *            *   \n");
		printf("           *      *                                                                 *      ***       *  \n");
		printf("          *        *                                                              *      *     *      *   \n");
		printf("     *****          *****                                                        *     *         *     *  \n");
		printf("    *                    *                                                      *     *           *    *\n");
		printf("    *   --------------   *                                                     *    *  ```\\ /```  *    * \n");
		printf("     ********************                                                     *    * (0  )| |(0  ) *    *\n");
		printf("        *            *             ______                                    *    *      (   )      *    *\n");
		printf("        * ( 0)  ( 0) *            / /  \\ \\                                  *    *     ```` ````     *    * \n");
		printf("        *     (      *            \\_\\__/_/                                   ****    ``   ___   ``    **** \n");
		printf("        *            *              ***                                          * ``             `` *\n");
		printf("         *   -__-   *              ***                                         *|||||||||||||||||||||||*\n");
		printf("       *  *||    ||*  *           ***                                       *   |||||||||||||||||||||||   *\n");
		printf("    *       ||||||       *       ***                                     *      |||||||||||||||||||||||      *\n");
		printf("  *          ||||          *    ***                                   *          |||||||||||||||||||||          *\n");
		printf("*             ||             * ***                                  *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/****************************************************** FRAME 1 *****************************************************************/
	}
}


void dwarfvsmage(int dano, int atacante)
{
	if (atacante == 0)
	{
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("                                                                                     **\n");
		printf("                      ***                                                           *  *\n");
		printf("                 *           *                                                     *    *\n");
		printf("              *       ***       *                                                 *      *\n");
		printf("             *      *     *      *                                               *        *\n");
		printf("            *     *         *     *                                         *****          *****\n");
		printf("           *     *           *     *                                       *                    *\n");
		printf("           *    *  ```\\ /```  *    *                                       *   --------------   *\n");
		printf("          *    * (  0)| |(  0) *    *                                       ********************\n");
		printf("         *    *      (   )      *    *                      ______             *            *\n");
		printf("        *    *     ```` ````     *    *                    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("         ****    ``   ___   ``    ****                     \\_\\__/_/            *     (      *\n");
		printf("             * ``             `` *                            ***              *            *\n");
		printf("           *|||||||||||||||||||||||*                           ***              *   -__-   * \n");
		printf("        *   |||||||||||||||||||||||   *                         ***           *  *||    ||*  *\n");
		printf("     *      |||||||||||||||||||||||      *                       ***       *       ||||||       *\n");
		printf("  *          |||||||||||||||||||||          *                     ***    *          ||||          *\n");
		printf("*              |||||||||||||||||              *                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                     **\n");
		printf("                      ***                                                           *  *\n");
		printf("                 *           *                                                     *    *\n");
		printf("              *       ***       *                                                 *      *\n");
		printf("             *      *     *      *                                               *        *\n");
		printf("            *     *         *     *                                         *****          *****\n");
		printf("           *     *           *     *                                       *                    *\n");
		printf("           *    *  ```\\ /```  *    *                                       *   --------------   *\n");
		printf("          *    * (  0)| |(  0) *    *                              -%d      ********************\n",dano);
		printf("         *    *      (   )      *    *                      ______             *            *\n");
		printf("        *    *     ```` ````     *    *                    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("         ****    ``   ___   ``    ****                     \\_\\__/_/            *     (      *\n");
		printf("             * ``             `` *                            ***              *            *\n");
		printf("           *|||||||||||||||||||||||*                           ***              *   -__-   * \n");
		printf("        *   |||||||||||||||||||||||   *                         ***           *  *||    ||*  *\n");
		printf("     *      |||||||||||||||||||||||      *                       ***       *       ||||||       *\n");
		printf("  *          |||||||||||||||||||||          *                     ***    *          ||||          *\n");
		printf("*              |||||||||||||||||              *                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                     **\n");
		printf("                      ***                                                           *  *\n");
		printf("                 *           *                                                     *    *\n");
		printf("              *       ***       *                                                 *      *\n");
		printf("             *      *     *      *                                               *        *\n");
		printf("            *     *         *     *                                         *****          *****\n");
		printf("           *     *           *     *                                       *                    *\n");
		printf("           *    *  ```\\ /```  *    *                              -%d      *   --------------   *\n",dano);
		printf("          *    * (  0)| |(  0) *    *                                       ********************\n");
		printf("         *    *      (   )      *    *                      ______             *            *\n");
		printf("        *    *     ```` ````     *    *                    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("         ****    ``   ___   ``    ****                     \\_\\__/_/            *     (      *\n");
		printf("             * ``             `` *                            ***              *            *\n");
		printf("           *|||||||||||||||||||||||*                           ***              *   -__-   * \n");
		printf("        *   |||||||||||||||||||||||   *                         ***           *  *||    ||*  *\n");
		printf("     *      |||||||||||||||||||||||      *                       ***       *       ||||||       *\n");
		printf("  *          |||||||||||||||||||||          *                     ***    *          ||||          *\n");
		printf("*              |||||||||||||||||              *                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                     **\n");
		printf("                      ***                                                           *  *\n");
		printf("                 *           *                                                     *    *\n");
		printf("              *       ***       *                                                 *      *\n");
		printf("             *      *     *      *                                               *        *\n");
		printf("            *     *         *     *                                         *****          *****\n");
		printf("           *     *           *     *                               -%d     *                    *\n",dano);
		printf("           *    *  ```\\ /```  *    *                                       *   --------------   *\n");
		printf("          *    * (  0)| |(  0) *    *                                       ********************\n");
		printf("         *    *      (   )      *    *                      ______             *            *\n");
		printf("        *    *     ```` ````     *    *                    / /  \\ \\            * ( 0)  ( 0) *\n");
		printf("         ****    ``   ___   ``    ****                     \\_\\__/_/            *     (      *\n");
		printf("             * ``             `` *                            ***              *            *\n");
		printf("           *|||||||||||||||||||||||*                           ***              *   -__-   * \n");
		printf("        *   |||||||||||||||||||||||   *                         ***           *  *||    ||*  *\n");
		printf("     *      |||||||||||||||||||||||      *                       ***       *       ||||||       *\n");
		printf("  *          |||||||||||||||||||||          *                     ***    *          ||||          *\n");
		printf("*              |||||||||||||||||              *                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                     **\n");
		printf("                      ***                                                           *  *\n");
		printf("                 *           *                                                     *    *\n");
		printf("              *       ***       *                                                 *      *\n");
		printf("             *      *     *      *                                               *        *\n");
		printf("            *     *         *     *                                         *****          *****\n");
		printf("           *     *           *     *                                       *                    *\n");
		printf("           *    *  ```\\ /```  *    *                                       *   --------------   *\n");
		printf("          *    * (  0)| |(  0) *    *                                       ********************\n");
		printf("         *    *      (   )      *    *                      ______             *            *\n");
		printf("        *    *     ```` ````     *    *                    / /  \\ \\            * (0 )  ( 0) *\n");
		printf("         ****    ``   ___   ``    ****                     \\_\\__/_/            *     (      *\n");
		printf("             * ``             `` *                            ***              *            *\n");
		printf("           *|||||||||||||||||||||||*                           ***              *   -__-   * \n");
		printf("        *   |||||||||||||||||||||||   *                         ***           *  *||    ||*  *\n");
		printf("     *      |||||||||||||||||||||||      *                       ***       *       ||||||       *\n");
		printf("  *          |||||||||||||||||||||          *                     ***    *          ||||          *\n");
		printf("*              |||||||||||||||||              *                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(500);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                     **\n");
		printf("                      ***                                                           *  *\n");
		printf("                 *           *                                                     *    *\n");
		printf("              *       ***       *                                                 *      *\n");
		printf("             *      *     *      *                                               *        *\n");
		printf("            *     *         *     *                                         *****          *****\n");
		printf("           *     *           *     *                                       *                    *\n");
		printf("           *    *  ```\\ /```  *    *                                       *   --------------   *\n");
		printf("          *    * (  0)| |(  0) *    *                                       ********************\n");
		printf("         *    *      (   )      *    *                      ______             *            *\n");
		printf("        *    *     ```` ````     *    *                    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("         ****    ``   ___   ``    ****                     \\_\\__/_/            *     (      *\n");
		printf("             * ``             `` *                            ***              *            *\n");
		printf("           *|||||||||||||||||||||||*                           ***              *   -__-   * \n");
		printf("        *   |||||||||||||||||||||||   *                         ***           *  *||    ||*  *\n");
		printf("     *      |||||||||||||||||||||||      *                       ***       *       ||||||       *\n");
		printf("  *          |||||||||||||||||||||          *                     ***    *          ||||          *\n");
		printf("*              |||||||||||||||||              *                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
	}
	if (atacante == 1)
	{
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("                                                                                     **\n");
		printf("                      ***                                                           *  *\n");
		printf("                 *           *                                                     *    *\n");
		printf("              *       ***       *                                                 *      *\n");
		printf("             *      *     *      *                                               *        *\n");
		printf("            *     *         *     *                                         *****          *****\n");
		printf("           *     *           *     *                                       *                    *\n");
		printf("           *    *  ```\\ /```  *    *                                       *   --------------   *\n");
		printf("          *    * (  0)| |(  0) *    *                                       ********************\n");
		printf("         *    *      (   )      *    *                      ______             *            *\n");
		printf("        *    *     ```` ````     *    *                    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("         ****    ``   ___   ``    ****                     \\_\\__/_/            *     (      *\n");
		printf("             * ``             `` *                            ***              *            *\n");
		printf("           *|||||||||||||||||||||||*                           ***              *   -__-   * \n");
		printf("        *   |||||||||||||||||||||||   *                         ***           *  *||    ||*  *\n");
		printf("     *      |||||||||||||||||||||||      *                       ***       *       ||||||       *\n");
		printf("  *          |||||||||||||||||||||          *                     ***    *          ||||          *\n");
		printf("*              |||||||||||||||||              *                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                     **\n");
		printf("                      ***                                                           *  *\n");
		printf("                 *           *                                                     *    *\n");
		printf("              *       ***       *                                                 *      *\n");
		printf("             *      *     *      *                                               *        *\n");
		printf("            *     *         *     *                                         *****          *****\n");
		printf("           *     *           *     *                                       *                    *\n");
		printf("           *    *  ```\\ /```  *    *                                       *   --------------   *\n");
		printf("          *    * (  0)| |(  0) *    *     -%d                               ********************\n",dano);
		printf("         *    *      (   )      *    *                      ______             *            *\n");
		printf("        *    *     ```` ````     *    *                    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("         ****    ``   ___   ``    ****                     \\_\\__/_/            *     (      *\n");
		printf("             * ``             `` *                            ***              *            *\n");
		printf("           *|||||||||||||||||||||||*                           ***              *   -__-   * \n");
		printf("        *   |||||||||||||||||||||||   *                         ***           *  *||    ||*  *\n");
		printf("     *      |||||||||||||||||||||||      *                       ***       *       ||||||       *\n");
		printf("  *          |||||||||||||||||||||          *                     ***    *          ||||          *\n");
		printf("*              |||||||||||||||||              *                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                     **\n");
		printf("                      ***                                                           *  *\n");
		printf("                 *           *                                                     *    *\n");
		printf("              *       ***       *                                                 *      *\n");
		printf("             *      *     *      *                                               *        *\n");
		printf("            *     *         *     *                                         *****          *****\n");
		printf("           *     *           *     *                                       *                    *\n");
		printf("           *    *  ```\\ /```  *    *   -%d                                 *   --------------   *\n",dano);
		printf("          *    * (  0)| |(  0) *    *                                       ********************\n");
		printf("         *    *      (   )      *    *                      ______             *            *\n");
		printf("        *    *     ```` ````     *    *                    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("         ****    ``   ___   ``    ****                     \\_\\__/_/            *     (      *\n");
		printf("             * ``             `` *                            ***              *            *\n");
		printf("           *|||||||||||||||||||||||*                           ***              *   -__-   * \n");
		printf("        *   |||||||||||||||||||||||   *                         ***           *  *||    ||*  *\n");
		printf("     *      |||||||||||||||||||||||      *                       ***       *       ||||||       *\n");
		printf("  *          |||||||||||||||||||||          *                     ***    *          ||||          *\n");
		printf("*              |||||||||||||||||              *                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                     **\n");
		printf("                      ***                                                           *  *\n");
		printf("                 *           *                                                     *    *\n");
		printf("              *       ***       *                                                 *      *\n");
		printf("             *      *     *      *                                               *        *\n");
		printf("            *     *         *     *                                         *****          *****\n");
		printf("           *     *           *     *      -%d                              *                    *\n",dano);
		printf("           *    *  ```\\ /```  *    *                                       *   --------------   *\n");
		printf("          *    * (0  )| |(0  ) *    *                                       ********************\n");
		printf("         *    *      (   )      *    *                      ______             *            *\n");
		printf("        *    *     ```` ````     *    *                    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("         ****    ``   ___   ``    ****                     \\_\\__/_/            *     (      *\n");
		printf("             * ``             `` *                            ***              *            *\n");
		printf("           *|||||||||||||||||||||||*                           ***              *   -__-   * \n");
		printf("        *   |||||||||||||||||||||||   *                         ***           *  *||    ||*  *\n");
		printf("     *      |||||||||||||||||||||||      *                       ***       *       ||||||       *\n");
		printf("  *          |||||||||||||||||||||          *                     ***    *          ||||          *\n");
		printf("*              |||||||||||||||||              *                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                     **\n");
		printf("                      ***                                                           *  *\n");
		printf("                 *           *                                                     *    *\n");
		printf("              *       ***       *                                                 *      *\n");
		printf("             *      *     *      *                                               *        *\n");
		printf("            *     *         *     *                                         *****          *****\n");
		printf("           *     *           *     *                                       *                    *\n");
		printf("           *    *  ```\\ /```  *    *                                       *   --------------   *\n");
		printf("          *    * (0  )| |(  0) *    *                                       ********************\n");
		printf("         *    *      (   )      *    *                      ______             *            *\n");
		printf("        *    *     ```` ````     *    *                    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("         ****    ``   ___   ``    ****                     \\_\\__/_/            *     (      *\n");
		printf("             * ``             `` *                            ***              *            *\n");
		printf("           *|||||||||||||||||||||||*                           ***              *   -__-   * \n");
		printf("        *   |||||||||||||||||||||||   *                         ***           *  *||    ||*  *\n");
		printf("     *      |||||||||||||||||||||||      *                       ***       *       ||||||       *\n");
		printf("  *          |||||||||||||||||||||          *                     ***    *          ||||          *\n");
		printf("*              |||||||||||||||||              *                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(500);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                     **\n");
		printf("                      ***                                                           *  *\n");
		printf("                 *           *                                                     *    *\n");
		printf("              *       ***       *                                                 *      *\n");
		printf("             *      *     *      *                                               *        *\n");
		printf("            *     *         *     *                                         *****          *****\n");
		printf("           *     *           *     *                                       *                    *\n");
		printf("           *    *  ```\\ /```  *    *                                       *   --------------   *\n");
		printf("          *    * (  0)| |(  0) *    *                                       ********************\n");
		printf("         *    *      (   )      *    *                      ______             *            *\n");
		printf("        *    *     ```` ````     *    *                    / /  \\ \\            * (0 )  (0 ) *\n");
		printf("         ****    ``   ___   ``    ****                     \\_\\__/_/            *     (      *\n");
		printf("             * ``             `` *                            ***              *            *\n");
		printf("           *|||||||||||||||||||||||*                           ***              *   -__-   * \n");
		printf("        *   |||||||||||||||||||||||   *                         ***           *  *||    ||*  *\n");
		printf("     *      |||||||||||||||||||||||      *                       ***       *       ||||||       *\n");
		printf("  *          |||||||||||||||||||||          *                     ***    *          ||||          *\n");
		printf("*              |||||||||||||||||              *                    *** *             ||             *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
	}
}


void archervsdwarf(int dano, int atacante)
{
	if (atacante == 0)
	{
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                                        ***  \n");
		printf("     * *     *************     * *                                                   *           *   \n");
		printf("     *  *  *               *  *  *                                                *       ***       *  \n");
		printf("     *  **                   **  *                                               *      *     *      *   \n");
		printf("      * *      * * * * *      * *                                               *     *         *     *  \n");
		printf("       *     *           *     *                                               *     *           *     *\n");
		printf("       *   *               *   *                                              *    *  ```\\ /```  *    * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                             *    * (0  )| |(0  ) *    *\n");
		printf("       *   *       <       *   *                                            *    *      (   )      *    *\n");
		printf("       *   *               *   *                                           *    *     ```` ````     *    * \n");
		printf("       *   *      ___      *   *                                            ****    ``   ___   ``    **** \n");
		printf("       *   *               *   *                                                * ``             `` *\n");
		printf("      *     *             *     *                                             *|||||||||||||||||||||||*\n");
		printf("   **         * _______ *         **                                       *   |||||||||||||||||||||||   *\n");
		printf(" *              *     *              *                                  *      |||||||||||||||||||||||      *\n");
		printf("*                  *                  *                              *          |||||||||||||||||||||          *\n");
		printf("*                   *                 *                            *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                                        ***  \n");
		printf("     * *     *************     * *                                                   *           *   \n");
		printf("     *  *  *               *  *  *                                                *       ***       *  \n");
		printf("     *  **                   **  *                                               *      *     *      *   \n");
		printf("      * *      * * * * *      * *                                               *     *         *     *  \n");
		printf("       *     *           *     *                                      -%d      *     *           *     *\n",dano);
		printf("       *   *               *   *                                              *    *  ```\\ /```  *    * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                             *    * (0  )| |(0  ) *    *\n");
		printf("       *   *       <       *   *                                            *    *      (   )      *    *\n");
		printf("       *   *               *   *                                           *    *     ```` ````     *    * \n");
		printf("       *   *      ___      *   *                                            ****    ``   ___   ``    **** \n");
		printf("       *   *               *   *                                                * ``             `` *\n");
		printf("      *     *             *     *                                             *|||||||||||||||||||||||*\n");
		printf("   **         * _______ *         **                                       *   |||||||||||||||||||||||   *\n");
		printf(" *              *     *              *                                  *      |||||||||||||||||||||||      *\n");
		printf("*                  *                  *                              *          |||||||||||||||||||||          *\n");
		printf("*                   *                 *                            *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                                        ***  \n");
		printf("     * *     *************     * *                                                   *           *   \n");
		printf("     *  *  *               *  *  *                                                *       ***       *  \n");
		printf("     *  **                   **  *                                               *      *     *      *   \n");
		printf("      * *      * * * * *      * *                                      -%d      *     *         *     *  \n",dano);
		printf("       *     *           *     *                                               *     *           *     *\n");
		printf("       *   *               *   *                                              *    *  ```\\ /```  *    * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                             *    * (0  )| |(0  ) *    *\n");
		printf("       *   *       <       *   *                                            *    *      (   )      *    *\n");
		printf("       *   *               *   *                                           *    *     ```` ````     *    * \n");
		printf("       *   *      ___      *   *                                            ****    ``   ___   ``    **** \n");
		printf("       *   *               *   *                                                * ``             `` *\n");
		printf("      *     *             *     *                                             *|||||||||||||||||||||||*\n");
		printf("   **         * _______ *         **                                       *   |||||||||||||||||||||||   *\n");
		printf(" *              *     *              *                                  *      |||||||||||||||||||||||      *\n");
		printf("*                  *                  *                              *          |||||||||||||||||||||          *\n");
		printf("*                   *                 *                            *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                                        ***  \n");
		printf("     * *     *************     * *                                                   *           *   \n");
		printf("     *  *  *               *  *  *                                                *       ***       *  \n");
		printf("     *  **                   **  *                                        -%d    *      *     *      *   \n",dano);
		printf("      * *      * * * * *      * *                                               *     *         *     *  \n");
		printf("       *     *           *     *                                               *     *           *     *\n");
		printf("       *   *               *   *                                              *    *  ```\\ /```  *    * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                             *    * (  0)| |(  0) *    *\n");
		printf("       *   *       <       *   *                                            *    *      (   )      *    *\n");
		printf("       *   *               *   *                                           *    *     ```` ````     *    * \n");
		printf("       *   *      ___      *   *                                            ****    ``   ___   ``    **** \n");
		printf("       *   *               *   *                                                * ``             `` *\n");
		printf("      *     *             *     *                                             *|||||||||||||||||||||||*\n");
		printf("   **         * _______ *         **                                       *   |||||||||||||||||||||||   *\n");
		printf(" *              *     *              *                                  *      |||||||||||||||||||||||      *\n");
		printf("*                  *                  *                              *          |||||||||||||||||||||          *\n");
		printf("*                   *                 *                            *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                                        ***  \n");
		printf("     * *     *************     * *                                                   *           *   \n");
		printf("     *  *  *               *  *  *                                                *       ***       *  \n");
		printf("     *  **                   **  *                                               *      *     *      *   \n");
		printf("      * *      * * * * *      * *                                               *     *         *     *  \n");
		printf("       *     *           *     *                                               *     *           *     *\n");
		printf("       *   *               *   *                                              *    *  ```\\ /```  *    * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                             *    * (0  )| |(  0) *    *\n");
		printf("       *   *       <       *   *                                            *    *      (   )      *    *\n");
		printf("       *   *               *   *                                           *    *     ```` ````     *    * \n");
		printf("       *   *      ___      *   *                                            ****    ``   ___   ``    **** \n");
		printf("       *   *               *   *                                                * ``             `` *\n");
		printf("      *     *             *     *                                             *|||||||||||||||||||||||*\n");
		printf("   **         * _______ *         **                                       *   |||||||||||||||||||||||   *\n");
		printf(" *              *     *              *                                  *      |||||||||||||||||||||||      *\n");
		printf("*                  *                  *                              *          |||||||||||||||||||||          *\n");
		printf("*                   *                 *                            *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(500);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                                        ***  \n");
		printf("     * *     *************     * *                                                   *           *   \n");
		printf("     *  *  *               *  *  *                                                *       ***       *  \n");
		printf("     *  **                   **  *                                               *      *     *      *   \n");
		printf("      * *      * * * * *      * *                                               *     *         *     *  \n");
		printf("       *     *           *     *                                               *     *           *     *\n");
		printf("       *   *               *   *                                              *    *  ```\\ /```  *    * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                             *    * (0  )| |(0  ) *    *\n");
		printf("       *   *       <       *   *                                            *    *      (   )      *    *\n");
		printf("       *   *               *   *                                           *    *     ```` ````     *    * \n");
		printf("       *   *      ___      *   *                                            ****    ``   ___   ``    **** \n");
		printf("       *   *               *   *                                                * ``             `` *\n");
		printf("      *     *             *     *                                             *|||||||||||||||||||||||*\n");
		printf("   **         * _______ *         **                                       *   |||||||||||||||||||||||   *\n");
		printf(" *              *     *              *                                  *      |||||||||||||||||||||||      *\n");
		printf("*                  *                  *                              *          |||||||||||||||||||||          *\n");
		printf("*                   *                 *                            *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
	}
	if (atacante == 1)
	{
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                                        ***  \n");
		printf("     * *     *************     * *                                                   *           *   \n");
		printf("     *  *  *               *  *  *                                                *       ***       *  \n");
		printf("     *  **                   **  *                                               *      *     *      *   \n");
		printf("      * *      * * * * *      * *                                               *     *         *     *  \n");
		printf("       *     *           *     *                                               *     *           *     *\n");
		printf("       *   *               *   *                                              *    *  ```\\ /```  *    * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                             *    * (0  )| |(0  ) *    *\n");
		printf("       *   *       <       *   *                                            *    *      (   )      *    *\n");
		printf("       *   *               *   *                                           *    *     ```` ````     *    * \n");
		printf("       *   *      ___      *   *                                            ****    ``   ___   ``    **** \n");
		printf("       *   *               *   *                                                * ``             `` *\n");
		printf("      *     *             *     *                                             *|||||||||||||||||||||||*\n");
		printf("   **         * _______ *         **                                       *   |||||||||||||||||||||||   *\n");
		printf(" *              *     *              *                                  *      |||||||||||||||||||||||      *\n");
		printf("*                  *                  *                              *          |||||||||||||||||||||          *\n");
		printf("*                   *                 *                            *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                                        ***  \n");
		printf("     * *     *************     * *                                                   *           *   \n");
		printf("     *  *  *               *  *  *                                                *       ***       *  \n");
		printf("     *  **                   **  *                                               *      *     *      *   \n");
		printf("      * *      * * * * *      * *                                               *     *         *     *  \n");
		printf("       *     *           *     *       -%d                                     *     *           *     *\n",dano);
		printf("       *   *               *   *                                              *    *  ```\\ /```  *    * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                             *    * (0  )| |(0  ) *    *\n");
		printf("       *   *       <       *   *                                            *    *      (   )      *    *\n");
		printf("       *   *               *   *                                           *    *     ```` ````     *    * \n");
		printf("       *   *      ___      *   *                                            ****    ``   ___   ``    **** \n");
		printf("       *   *               *   *                                                * ``             `` *\n");
		printf("      *     *             *     *                                             *|||||||||||||||||||||||*\n");
		printf("   **         * _______ *         **                                       *   |||||||||||||||||||||||   *\n");
		printf(" *              *     *              *                                  *      |||||||||||||||||||||||      *\n");
		printf("*                  *                  *                              *          |||||||||||||||||||||          *\n");
		printf("*                   *                 *                            *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                                        ***  \n");
		printf("     * *     *************     * *                                                   *           *   \n");
		printf("     *  *  *               *  *  *                                                *       ***       *  \n");
		printf("     *  **                   **  *                                               *      *     *      *   \n");
		printf("      * *      * * * * *      * *     -%d                                       *     *         *     *  \n",dano);
		printf("       *     *           *     *                                               *     *           *     *\n");
		printf("       *   *               *   *                                              *    *  ```\\ /```  *    * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                             *    * (0  )| |(0  ) *    *\n");
		printf("       *   *       <       *   *                                            *    *      (   )      *    *\n");
		printf("       *   *               *   *                                           *    *     ```` ````     *    * \n");
		printf("       *   *      ___      *   *                                            ****    ``   ___   ``    **** \n");
		printf("       *   *               *   *                                                * ``             `` *\n");
		printf("      *     *             *     *                                             *|||||||||||||||||||||||*\n");
		printf("   **         * _______ *         **                                       *   |||||||||||||||||||||||   *\n");
		printf(" *              *     *              *                                  *      |||||||||||||||||||||||      *\n");
		printf("*                  *                  *                              *          |||||||||||||||||||||          *\n");
		printf("*                   *                 *                            *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                                        ***  \n");
		printf("     * *     *************     * *                                                   *           *   \n");
		printf("     *  *  *               *  *  *                                                *       ***       *  \n");
		printf("     *  **                   **  *     -%d                                       *      *     *      *   \n",dano);
		printf("      * *      * * * * *      * *                                               *     *         *     *  \n");
		printf("       *     *           *     *                                               *     *           *     *\n");
		printf("       *   *               *   *                                              *    *  ```\\ /```  *    * \n");
		printf("       *   *  (0 )   (0 )  *   *                                             *    * (0  )| |(0  ) *    *\n");
		printf("       *   *       <       *   *                                            *    *      (   )      *    *\n");
		printf("       *   *               *   *                                           *    *     ```` ````     *    * \n");
		printf("       *   *      ___      *   *                                            ****    ``   ___   ``    **** \n");
		printf("       *   *               *   *                                                * ``             `` *\n");
		printf("      *     *             *     *                                             *|||||||||||||||||||||||*\n");
		printf("   **         * _______ *         **                                       *   |||||||||||||||||||||||   *\n");
		printf(" *              *     *              *                                  *      |||||||||||||||||||||||      *\n");
		printf("*                  *                  *                              *          |||||||||||||||||||||          *\n");
		printf("*                   *                 *                            *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                                        ***  \n");
		printf("     * *     *************     * *                                                   *           *   \n");
		printf("     *  *  *               *  *  *                                                *       ***       *  \n");
		printf("     *  **                   **  *                                               *      *     *      *   \n");
		printf("      * *      * * * * *      * *                                               *     *         *     *  \n");
		printf("       *     *           *     *                                               *     *           *     *\n");
		printf("       *   *               *   *                                              *    *  ```\\ /```  *    * \n");
		printf("       *   *  (0 )   ( 0)  *   *                                             *    * (0  )| |(0  ) *    *\n");
		printf("       *   *       <       *   *                                            *    *      (   )      *    *\n");
		printf("       *   *               *   *                                           *    *     ```` ````     *    * \n");
		printf("       *   *      ___      *   *                                            ****    ``   ___   ``    **** \n");
		printf("       *   *               *   *                                                * ``             `` *\n");
		printf("      *     *             *     *                                             *|||||||||||||||||||||||*\n");
		printf("   **         * _______ *         **                                       *   |||||||||||||||||||||||   *\n");
		printf(" *              *     *              *                                  *      |||||||||||||||||||||||      *\n");
		printf("*                  *                  *                              *          |||||||||||||||||||||          *\n");
		printf("*                   *                 *                            *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(500);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                       \n");
		printf("     *                           *                                                        ***  \n");
		printf("     * *     *************     * *                                                   *           *   \n");
		printf("     *  *  *               *  *  *                                                *       ***       *  \n");
		printf("     *  **                   **  *                                               *      *     *      *   \n");
		printf("      * *      * * * * *      * *                                               *     *         *     *  \n");
		printf("       *     *           *     *                                               *     *           *     *\n");
		printf("       *   *               *   *                                              *    *  ```\\ /```  *    * \n");
		printf("       *   *  ( 0)   ( 0)  *   *                                             *    * (0  )| |(0  ) *    *\n");
		printf("       *   *       <       *   *                                            *    *      (   )      *    *\n");
		printf("       *   *               *   *                                           *    *     ```` ````     *    * \n");
		printf("       *   *      ___      *   *                                            ****    ``   ___   ``    **** \n");
		printf("       *   *               *   *                                                * ``             `` *\n");
		printf("      *     *             *     *                                             *|||||||||||||||||||||||*\n");
		printf("   **         * _______ *         **                                       *   |||||||||||||||||||||||   *\n");
		printf(" *              *     *              *                                  *      |||||||||||||||||||||||      *\n");
		printf("*                  *                  *                              *          |||||||||||||||||||||          *\n");
		printf("*                   *                 *                            *              |||||||||||||||||              *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
	}
}


void dwarfvsarcher(int dano, int atacante)
{
	if (atacante == 0)
	{
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("                                                                                                            \n");
		printf("                      ***                                               *                           *\n");
		printf("                 *           *                                         * *      *************      * * \n");
		printf("              *       ***       *                                      *  *  *                 *  *  *\n");
		printf("             *      *     *      *                                      *  **                   **  *\n");
		printf("            *     *         *     *                                      * *      * * * * *      * *\n");
		printf("           *     *           *     *                                      *     *           *     * \n");
		printf("           *    *  ```\\ /```  *    *                                      *   *               *   * \n");
		printf("          *    * (  0)| |(  0) *    *                                     *   *  (0 )   (0 )  *   *\n");
		printf("         *    *      (   )      *    *                                    *   *       <       *   *\n");
		printf("        *    *     ```` ````     *    *                                   *   *               *   *\n");
		printf("         ****    ``   ___   ``    ****                                    *   *      ___      *   *\n");
		printf("             * ``             `` *                                        *   *               *   *\n");
		printf("           *|||||||||||||||||||||||*                                     *     *             *     * \n");
		printf("        *   |||||||||||||||||||||||   *                               **         * _______ *         **\n");
		printf("     *      |||||||||||||||||||||||      *                          *              *     *              *\n");
		printf("  *          |||||||||||||||||||||          *                      *                  *                  * \n");
		printf("*              |||||||||||||||||              *                    *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                            \n");
		printf("                      ***                                               *                           *\n");
		printf("                 *           *                                         * *      *************      * * \n");
		printf("              *       ***       *                                      *  *  *                 *  *  *\n");
		printf("             *      *     *      *                                      *  **                   **  *\n");
		printf("            *     *         *     *                                      * *      * * * * *      * *\n");
		printf("           *     *           *     *                             -%d      *     *           *     * \n",dano);
		printf("           *    *  ```\\ /```  *    *                                      *   *               *   * \n");
		printf("          *    * (  0)| |(  0) *    *                                     *   *  (0 )   (0 )  *   *\n");
		printf("         *    *      (   )      *    *                                    *   *       <       *   *\n");
		printf("        *    *     ```` ````     *    *                                   *   *               *   *\n");
		printf("         ****    ``   ___   ``    ****                                    *   *      ___      *   *\n");
		printf("             * ``             `` *                                        *   *               *   *\n");
		printf("           *|||||||||||||||||||||||*                                     *     *             *     * \n");
		printf("        *   |||||||||||||||||||||||   *                               **         * _______ *         **\n");
		printf("     *      |||||||||||||||||||||||      *                          *              *     *              *\n");
		printf("  *          |||||||||||||||||||||          *                      *                  *                  * \n");
		printf("*              |||||||||||||||||              *                    *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                            \n");
		printf("                      ***                                               *                           *\n");
		printf("                 *           *                                         * *      *************      * * \n");
		printf("              *       ***       *                                      *  *  *                 *  *  *\n");
		printf("             *      *     *      *                                      *  **                   **  *\n");
		printf("            *     *         *     *                              -%d     * *      * * * * *      * *\n",dano);
		printf("           *     *           *     *                                      *     *           *     * \n");
		printf("           *    *  ```\\ /```  *    *                                      *   *               *   * \n");
		printf("          *    * (  0)| |(  0) *    *                                     *   *  (0 )   (0 )  *   *\n");
		printf("         *    *      (   )      *    *                                    *   *       <       *   *\n");
		printf("        *    *     ```` ````     *    *                                   *   *               *   *\n");
		printf("         ****    ``   ___   ``    ****                                    *   *      ___      *   *\n");
		printf("             * ``             `` *                                        *   *               *   *\n");
		printf("           *|||||||||||||||||||||||*                                     *     *             *     * \n");
		printf("        *   |||||||||||||||||||||||   *                               **         * _______ *         **\n");
		printf("     *      |||||||||||||||||||||||      *                          *              *     *              *\n");
		printf("  *          |||||||||||||||||||||          *                      *                  *                  * \n");
		printf("*              |||||||||||||||||              *                    *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                            \n");
		printf("                      ***                                               *                           *\n");
		printf("                 *           *                                         * *      *************      * * \n");
		printf("              *       ***       *                                      *  *  *                 *  *  *\n");
		printf("             *      *     *      *                               -%d    *  **                   **  *\n",dano);
		printf("            *     *         *     *                                      * *      * * * * *      * *\n");
		printf("           *     *           *     *                                      *     *           *     * \n");
		printf("           *    *  ```\\ /```  *    *                                      *   *               *   * \n");
		printf("          *    * (  0)| |(  0) *    *                                     *   *  ( 0)   ( 0)  *   *\n");
		printf("         *    *      (   )      *    *                                    *   *       <       *   *\n");
		printf("        *    *     ```` ````     *    *                                   *   *               *   *\n");
		printf("         ****    ``   ___   ``    ****                                    *   *      ___      *   *\n");
		printf("             * ``             `` *                                        *   *               *   *\n");
		printf("           *|||||||||||||||||||||||*                                     *     *             *     * \n");
		printf("        *   |||||||||||||||||||||||   *                               **         * _______ *         **\n");
		printf("     *      |||||||||||||||||||||||      *                          *              *     *              *\n");
		printf("  *          |||||||||||||||||||||          *                      *                  *                  * \n");
		printf("*              |||||||||||||||||              *                    *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                            \n");
		printf("                      ***                                               *                           *\n");
		printf("                 *           *                                         * *      *************      * * \n");
		printf("              *       ***       *                                      *  *  *                 *  *  *\n");
		printf("             *      *     *      *                                      *  **                   **  *\n");
		printf("            *     *         *     *                                      * *      * * * * *      * *\n");
		printf("           *     *           *     *                                      *     *           *     * \n");
		printf("           *    *  ```\\ /```  *    *                                      *   *               *   * \n");
		printf("          *    * (  0)| |(  0) *    *                                     *   *  (0 )   ( 0)  *   *\n");
		printf("         *    *      (   )      *    *                                    *   *       <       *   *\n");
		printf("        *    *     ```` ````     *    *                                   *   *               *   *\n");
		printf("         ****    ``   ___   ``    ****                                    *   *      ___      *   *\n");
		printf("             * ``             `` *                                        *   *               *   *\n");
		printf("           *|||||||||||||||||||||||*                                     *     *             *     * \n");
		printf("        *   |||||||||||||||||||||||   *                               **         * _______ *         **\n");
		printf("     *      |||||||||||||||||||||||      *                          *              *     *              *\n");
		printf("  *          |||||||||||||||||||||          *                      *                  *                  * \n");
		printf("*              |||||||||||||||||              *                    *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(500);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                            \n");
		printf("                      ***                                               *                           *\n");
		printf("                 *           *                                         * *      *************      * * \n");
		printf("              *       ***       *                                      *  *  *                 *  *  *\n");
		printf("             *      *     *      *                                      *  **                   **  *\n");
		printf("            *     *         *     *                                      * *      * * * * *      * *\n");
		printf("           *     *           *     *                                      *     *           *     * \n");
		printf("           *    *  ```\\ /```  *    *                                      *   *               *   * \n");
		printf("          *    * (  0)| |(  0) *    *                                     *   *  (0 )   (0 )  *   *\n");
		printf("         *    *      (   )      *    *                                    *   *       <       *   *\n");
		printf("        *    *     ```` ````     *    *                                   *   *               *   *\n");
		printf("         ****    ``   ___   ``    ****                                    *   *      ___      *   *\n");
		printf("             * ``             `` *                                        *   *               *   *\n");
		printf("           *|||||||||||||||||||||||*                                     *     *             *     * \n");
		printf("        *   |||||||||||||||||||||||   *                               **         * _______ *         **\n");
		printf("     *      |||||||||||||||||||||||      *                          *              *     *              *\n");
		printf("  *          |||||||||||||||||||||          *                      *                  *                  * \n");
		printf("*              |||||||||||||||||              *                    *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
	}
	if (atacante == 1)
	{
		/******************************************************** FRAME 1 **************************************************************/
		system("cls");
		printf("                                                                                                            \n");
		printf("                      ***                                               *                           *\n");
		printf("                 *           *                                         * *      *************      * * \n");
		printf("              *       ***       *                                      *  *  *                 *  *  *\n");
		printf("             *      *     *      *                                      *  **                   **  *\n");
		printf("            *     *         *     *                                      * *      * * * * *      * *\n");
		printf("           *     *           *     *                                      *     *           *     * \n");
		printf("           *    *  ```\\ /```  *    *                                      *   *               *   * \n");
		printf("          *    * (  0)| |(  0) *    *                                     *   *  (0 )   (0 )  *   *\n");
		printf("         *    *      (   )      *    *                                    *   *       <       *   *\n");
		printf("        *    *     ```` ````     *    *                                   *   *               *   *\n");
		printf("         ****    ``   ___   ``    ****                                    *   *      ___      *   *\n");
		printf("             * ``             `` *                                        *   *               *   *\n");
		printf("           *|||||||||||||||||||||||*                                     *     *             *     * \n");
		printf("        *   |||||||||||||||||||||||   *                               **         * _______ *         **\n");
		printf("     *      |||||||||||||||||||||||      *                          *              *     *              *\n");
		printf("  *          |||||||||||||||||||||          *                      *                  *                  * \n");
		printf("*              |||||||||||||||||              *                    *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                            \n");
		printf("                      ***                                               *                           *\n");
		printf("                 *           *                                         * *      *************      * * \n");
		printf("              *       ***       *                                      *  *  *                 *  *  *\n");
		printf("             *      *     *      *                                      *  **                   **  *\n");
		printf("            *     *         *     *                                      * *      * * * * *      * *\n");
		printf("           *     *           *     *     -%d                              *     *           *     * \n",dano);
		printf("           *    *  ```\\ /```  *    *                                      *   *               *   * \n");
		printf("          *    * (  0)| |(  0) *    *                                     *   *  (0 )   (0 )  *   *\n");
		printf("         *    *      (   )      *    *                                    *   *       <       *   *\n");
		printf("        *    *     ```` ````     *    *                                   *   *               *   *\n");
		printf("         ****    ``   ___   ``    ****                                    *   *      ___      *   *\n");
		printf("             * ``             `` *                                        *   *               *   *\n");
		printf("           *|||||||||||||||||||||||*                                     *     *             *     * \n");
		printf("        *   |||||||||||||||||||||||   *                               **         * _______ *         **\n");
		printf("     *      |||||||||||||||||||||||      *                          *              *     *              *\n");
		printf("  *          |||||||||||||||||||||          *                      *                  *                  * \n");
		printf("*              |||||||||||||||||              *                    *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                            \n");
		printf("                      ***                                               *                           *\n");
		printf("                 *           *                                         * *      *************      * * \n");
		printf("              *       ***       *                                      *  *  *                 *  *  *\n");
		printf("             *      *     *      *                                      *  **                   **  *\n");
		printf("            *     *         *     *    -%d                               * *      * * * * *      * *\n",dano);
		printf("           *     *           *     *                                      *     *           *     * \n");
		printf("           *    *  ```\\ /```  *    *                                      *   *               *   * \n");
		printf("          *    * (  0)| |(  0) *    *                                     *   *  (0 )   (0 )  *   *\n");
		printf("         *    *      (   )      *    *                                    *   *       <       *   *\n");
		printf("        *    *     ```` ````     *    *                                   *   *               *   *\n");
		printf("         ****    ``   ___   ``    ****                                    *   *      ___      *   *\n");
		printf("             * ``             `` *                                        *   *               *   *\n");
		printf("           *|||||||||||||||||||||||*                                     *     *             *     * \n");
		printf("        *   |||||||||||||||||||||||   *                               **         * _______ *         **\n");
		printf("     *      |||||||||||||||||||||||      *                          *              *     *              *\n");
		printf("  *          |||||||||||||||||||||          *                      *                  *                  * \n");
		printf("*              |||||||||||||||||              *                    *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                            \n");
		printf("                      ***                                               *                           *\n");
		printf("                 *           *                                         * *      *************      * * \n");
		printf("              *       ***       *                                      *  *  *                 *  *  *\n");
		printf("             *      *     *      *    -%d                               *  **                   **  *\n",dano);
		printf("            *     *         *     *                                      * *      * * * * *      * *\n");
		printf("           *     *           *     *                                      *     *           *     * \n");
		printf("           *    *  ```\\ /```  *    *                                      *   *               *   * \n");
		printf("          *    * (0  )| |(0  ) *    *                                     *   *  (0 )   (0 )  *   *\n");
		printf("         *    *      (   )      *    *                                    *   *       <       *   *\n");
		printf("        *    *     ```` ````     *    *                                   *   *               *   *\n");
		printf("         ****    ``   ___   ``    ****                                    *   *      ___      *   *\n");
		printf("             * ``             `` *                                        *   *               *   *\n");
		printf("           *|||||||||||||||||||||||*                                     *     *             *     * \n");
		printf("        *   |||||||||||||||||||||||   *                               **         * _______ *         **\n");
		printf("     *      |||||||||||||||||||||||      *                          *              *     *              *\n");
		printf("  *          |||||||||||||||||||||          *                      *                  *                  * \n");
		printf("*              |||||||||||||||||              *                    *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                            \n");
		printf("                      ***                                               *                           *\n");
		printf("                 *           *                                         * *      *************      * * \n");
		printf("              *       ***       *                                      *  *  *                 *  *  *\n");
		printf("             *      *     *      *                                      *  **                   **  *\n");
		printf("            *     *         *     *                                      * *      * * * * *      * *\n");
		printf("           *     *           *     *                                      *     *           *     * \n");
		printf("           *    *  ```\\ /```  *    *                                      *   *               *   * \n");
		printf("          *    * (0  )| |(  0) *    *                                     *   *  (0 )   (0 )  *   *\n");
		printf("         *    *      (   )      *    *                                    *   *       <       *   *\n");
		printf("        *    *     ```` ````     *    *                                   *   *               *   *\n");
		printf("         ****    ``   ___   ``    ****                                    *   *      ___      *   *\n");
		printf("             * ``             `` *                                        *   *               *   *\n");
		printf("           *|||||||||||||||||||||||*                                     *     *             *     * \n");
		printf("        *   |||||||||||||||||||||||   *                               **         * _______ *         **\n");
		printf("     *      |||||||||||||||||||||||      *                          *              *     *              *\n");
		printf("  *          |||||||||||||||||||||          *                      *                  *                  * \n");
		printf("*              |||||||||||||||||              *                    *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(500);
		/******************************************************** FRAME 2 **************************************************************/
		system("cls");
		printf("                                                                                                            \n");
		printf("                      ***                                               *                           *\n");
		printf("                 *           *                                         * *      *************      * * \n");
		printf("              *       ***       *                                      *  *  *                 *  *  *\n");
		printf("             *      *     *      *                                      *  **                   **  *\n");
		printf("            *     *         *     *                                      * *      * * * * *      * *\n");
		printf("           *     *           *     *                                      *     *           *     * \n");
		printf("           *    *  ```\\ /```  *    *                                      *   *               *   * \n");
		printf("          *    * (  0)| |(  0) *    *                                     *   *  (0 )   (0 )  *   *\n");
		printf("         *    *      (   )      *    *                                    *   *       <       *   *\n");
		printf("        *    *     ```` ````     *    *                                   *   *               *   *\n");
		printf("         ****    ``   ___   ``    ****                                    *   *      ___      *   *\n");
		printf("             * ``             `` *                                        *   *               *   *\n");
		printf("           *|||||||||||||||||||||||*                                     *     *             *     * \n");
		printf("        *   |||||||||||||||||||||||   *                               **         * _______ *         **\n");
		printf("     *      |||||||||||||||||||||||      *                          *              *     *              *\n");
		printf("  *          |||||||||||||||||||||          *                      *                  *                  * \n");
		printf("*              |||||||||||||||||              *                    *                   *                 *\n");
		printf("------------------------------------------------------------------------------------------------------------------\n");
		Sleep(t_archer);
		/******************************************************** FRAME 2 **************************************************************/
	}
}
void clear(int sistema){
	switch(sistema){
		case windows: system("cls"); break;
	}
}



void color(int sistema, int cor){
	switch(sistema){
		case windows:
		switch(cor){
			case 4: system("color 04"); break;
			case 8: system("color 08"); break;
		}
		break;
	}
}
void titulo(){

	/*Contem o Titulo do jogo "PROMPT FIGHT"*/

	printf("  \xC9\xCD\xCD\xBB  \xC9\xCD\xCD\xBB  \xC9\xCD\xCB\xCD\xBB  \xC9\xCD\xCD\xBB  \xCD\xCD\xCB\xCD\xCD   \t\t\xC9\xCD\xCD\xCD  \xFE  \xC9\xCD\xCD\xCD\xCD  \xBA  \xBA  \xCD\xCD\xCB\xCD\xCD");
	printf("\n  \xCC\xCD\xCD\xBC  \xBA  \xBA  \xBA \xBA \xBA  \xCC\xCD\xCD\xBC    \xBA   \t\t\xCC\xCD\xCD\xCD  \xBA  \xBA  \xCD\xBB  \xCC\xCD\xCD\xB9    \xBA");
	printf("\n  \xBA  \t\xC8\xCD\xCD\xBC  \xBA \xBA \xBA  \xBA       \xBA   \t\t\xBA     \xBA  \xC8\xCD\xCD\xCD\xBC  \xBA  \xBA    \xBA");
}





int menu(int sis){

	/*Contem o menu principal do jogo*/

	char tecla = 0;
	int slctvert = 1, a = 254, b = 255, c = 255;

	system("color 08");

	while(1){

		clear(sis);


		titulo();


		printf("\n\n\n\n\n\n\n\t\t\t\t\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n");
		printf("\t\t\t\t\xBA %c Iniciar    \xBA\n", a);
		printf("\t\t\t\t\xBA %c Instrucoes \xBA\n", b);
		printf("\t\t\t\t\xBA %c Sair       \xBA\n", c);
		printf("\t\t\t\t\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n\n");

		fflush(stdin);
		tecla = getch();

		if (tecla == down && slctvert < 3)
		{
			slctvert++;
			Beep(500, 250);

		}
		if (tecla == up && slctvert > 1)
		{
			slctvert--;
			Beep(500, 250);
		}
		if (slctvert == 1)
		{
			a = 254; //Quadrado
			b = 255;
			c = 255;
		}
		if (slctvert == 2)
		{
			a = 255;
			b = 254; //Quadrado
			c = 255;
		}
		if (slctvert == 3)
		{
			a = 255;
			b = 255;
			c = 254; //Quadrado
		}
		if (tecla == enter && slctvert < 3)
		{
			Beep(400, 250);
			return slctvert;
		}
		if (tecla == enter && slctvert == 3)
		{

			return 3;
		}
	}

}



void os(int *sistema){

	/*Coleta qual o sistema operacional o usuario esta utilizando*/

	printf("\n\n\n\n\n\n");
	printf("\t\t   | Indique qual o seu Sistema Operacional |\n\n");
	printf("\t\t\t     (1)  Windows\n");
	printf("\t\t\t     (2)  Mac Os\n");
	printf("\t\t\t     (3)  Linux\n");
	printf("\t\t\t\t:  ");
	scanf("%d", sistema);

}



void aviso(int sistema){

	/*Informa o usuario os comando para se utilizar o jogo*/

	clear(sistema);
	color(sistema, 4);
	printf("\n\n\n\n\t\t\t\tAtencao!\n\n");
	printf("   Para navegar nos menus use os direcionais para | Cima | e para | Baixo |.\n");
	printf("   Para selecionar use a tecla | Enter |.\n");
	printf("\n\n\n\n\t             Pressione uma tecla para continuar\n");
	Beep(500,800);
	getch();
	color(sistema, 8);
}



int classe(classes *heroeclass, atrib heroe[], int sis, int n){

	/*Contem o menu de selecao dos personagens e insercao dos atributos*/

	char tecla;
	int slctvert = 0, a = 254, b = 255, c = 255;

	while(1){

		clear(sis);
		switch(slctvert){

			case 0:  // MAGO
			printf(" Selecione o Her\xA2i  %d                        **\n", n+1);
			printf("  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\t\t\t    *  *\n");
			printf("  \xBA %c Mago       \xBA\t\t\t   *    *\n", a);
			printf("  \xBA %c Arqueiro   \xBA\t\t\t  *      *\n", b);
			printf("  \xBA %c An\xC6o       \xBA\t\t\t *        *\n", c);
			printf("  \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\t\t    *****          *****\n");
			printf("\t\t\t           *                    *\n");
			printf("\t\t\t           *   --------------   *\n");
			printf("\t\t\t            ******************** \n");
			printf("\t\t\t               *            *    \n");
			printf("\t\t\t               *  (0)  (0)  *    \n");
			printf("\t\t\t               *     (      *    \n");
			printf("\t\t\t               *            *    \n");
			printf("\t\t\t                *   -__-   *    \n");
			printf("\t\t\t              *  *||    ||*  *  \n");
			printf("\t\t\t           *       ||||||       *\n");
			printf("\t\t\t         *          ||||          *\n");
			printf("\t\t\t       *             ||             *\n");
			printf("  ESC para voltar\n");
			break;

			case 1:   // ARQUEIRO
			printf(" Selecione o Her\xA2i  %d                        ****\n", n+1);
			printf("  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\t\t\t  *        *\n");
			printf("  \xBA %c Mago       \xBA\t\t        *            *\n", a);
			printf("  \xBA %c Arqueiro   \xBA\t\t      *                *\n", b);
			printf("  \xBA %c An\xC6o       \xBA\t\t     *                  *\n", c);
			printf("  \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\t\t    *                    *\n");
			printf("\t\t\t           *      **********      *\n");
			printf("\t\t\t          *     *            *     *\n");
			printf("\t\t\t          *    *              *    *\n");
			printf("\t\t\t          *    *   (0)  (0)   *    *\n");
			printf("\t\t\t          *    *      <       *    *\n");
			printf("\t\t\t          *    *              *    *\n");
			printf("\t\t\t          *    *     ____     *    *\n");
			printf("\t\t\t          *    *              *    *\n");
			printf("\t\t\t         *      *            *      *\n");
			printf("\t\t\t       **         *        *         **\n");
			printf("\t\t\t      *             *    *             *\n");
			printf("\t\t\t     *                **                *\n");
			printf("  ESC para voltar\n");
			break;


			case 2:   // ANÃO
			printf(" Selecione o Her\xA2i  %d                        ***\n", n+1);
			printf("  \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\t\t\t  *       *\n");
			printf("  \xBA %c Mago       \xBA\t\t        *           *\n", a);
			printf("  \xBA %c Arqueiro   \xBA\t\t      *               *\n", b);
			printf("  \xBA %c An\xC6o       \xBA\t\t     *       ***       *\n", c);
			printf("  \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\t\t    *      *     *      *\n");
			printf("\t\t\t           *     *         *     *\n");
			printf("\t\t\t          *     *           *     *\n");
			printf("\t\t\t          *    *  ```\\ /```  *    *\n");
			printf("\t\t\t         *    *   (0)| |(0)   *    *\n");
			printf("\t\t\t        *    *      (   )      *    *\n");
			printf("\t\t\t       *    *     ```` ````     *    *\n");
			printf("\t\t\t        ****    ``   ___   ``    ****\n");
			printf("\t\t\t            * ``             `` *\n");
			printf("\t\t\t          *|||||||||||||||||||||||*\n");
			printf("\t\t\t       *   |||||||||||||||||||||||   *\n");
			printf("\t\t\t    *      |||||||||||||||||||||||      *\n");
			printf("\t\t\t *          |||||||||||||||||||||          *\n");
			printf("\t\t       *              |||||||||||||||||              *\n");
			printf("  ESC para voltar\n");
			break;

		}

		fflush(stdin);
		tecla = getch();

		if (tecla == down && slctvert < 2)
		{
			slctvert++;
			Beep(500, 250);
		}
		if (tecla == up && slctvert > 0)
		{
			slctvert--;
			Beep(500, 250);
		}
		if (slctvert == 0)
		{
			a = 254; //Quadrado
			b = 255;
			c = 255;
		}
		if (slctvert == 1)
		{
			a = 255;
			b = 254; //Quadrado
			c = 255;
		}
		if (slctvert == 2)
		{
			a = 255;
			b = 255;
			c = 254; //Quadrado
		}

		if (tecla == enter)
		{
			*heroeclass = slctvert;
			Beep(400, 250);
			coletadados(heroe, n, slctvert);
			return 5;
		}
		if (tecla == esc && n == 0)
		{
			Beep(380, 300);
			return 1;
		}
		if (tecla == esc && n == 1)
		{
			Beep(380, 300);
			return 0;
		}
	}
}




void luta(classes *heroe1class, classes *heroe2class, int dano, int atacante){  /*Chama a animacao de combate de acordo com as classes*/
	if (*heroe1class == MAGE && *heroe2class == MAGE)
	{
		magevsmage(dano, atacante);
	}
	if (*heroe1class == ARCHER && *heroe2class == ARCHER)
	{
		archervsarcher(dano, atacante);
	}
	if (*heroe1class == DWARF && *heroe2class == DWARF)
	{
		dwarfvsdwarf(dano, atacante);
	}
	if (*heroe1class == MAGE && *heroe2class == ARCHER)
	{
		magevsarcher(dano, atacante);
	}
	if (*heroe1class == ARCHER && *heroe2class == MAGE)
	{
		archervsmage(dano, atacante);
	}
	if (*heroe1class == MAGE && *heroe2class == DWARF)
	{
		magevsdwarf(dano, atacante);
	}
	if (*heroe1class == DWARF && *heroe2class == MAGE)
	{
		dwarfvsmage(dano, atacante);
	}
	if (*heroe1class == ARCHER && *heroe2class == DWARF)
	{
		archervsdwarf(dano, atacante);
	}
	if (*heroe1class == DWARF && *heroe2class == ARCHER)
	{
		dwarfvsarcher(dano, atacante);
	}
}


void contagem(){
	int i;

	for (i = 3; i > 0; i--)
	{
		system("cls");
		printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t%d\n", i);
		Sleep(1000);
	}
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\tLutar!!!\n");
	Sleep(1000);
}

float random(){
	float x;

	x = 1 + ( rand() % 3 );
	x = x/10;

	return x;
}


void damage(atrib heroe[], int HeroeNumber){

	int bonus, dano1 = 0, dano2 = 0;


	if (HeroeNumber == 0)  // Dano do heroi 1
	{
		dano1 = heroe[0].hp;
		switch(heroe[1].class){

			case MAGE: bonus = 3; break;
			case ARCHER: bonus = 2; break;
			case DWARF: bonus = 5; break;

		}
		heroe[0].hp = heroe[0].hp - ((((heroe[1].strength + heroe[1].spell)/2) + bonus) * random());


	}
	if (HeroeNumber == 1)  // Dano do heroi 2
	{
		dano2 = heroe[1].hp;
		switch(heroe[0].class){

			case MAGE: bonus = 3; break;
			case ARCHER: bonus = 2; break;
			case DWARF: bonus = 5; break;

		}
		heroe[1].hp = heroe[1].hp - ((((heroe[0].strength + heroe[0].spell)/2) + bonus) * random());


	}
}

int rodadas(atrib heroe[], int atacante){

	int dano1 = 0, dano2 = 0;

	do{
		if (atacante == 1)
		{
			dano1 = heroe[0].hp;
			dano2 = heroe[1].hp;

			damage(heroe,1); // Personagem 2 sofre dano
			dano2 = dano2 - heroe[1].hp; // calcula o dano da animacao de combate
			luta(&heroe[0].class, &heroe[1].class, dano2, 0);  // Chama a animacao de combate

			if (heroe[1].hp <= 0)
			{
				break;
			}

			damage(heroe,0); // Personagem 1 sofre dano
			dano1 = dano1 - heroe[0].hp; // calcula o dano da animacao de combate
			luta(&heroe[0].class, &heroe[1].class, dano1, 1);  // Chama a animacao de combate

			if (heroe[0].hp <= 0)
			{
				break;
			}

		}
		if (atacante == 2)
		{
			dano1 = heroe[0].hp;
			dano2 = heroe[1].hp;

			damage(heroe,0); // Personagem 1 sofre dano
			dano1 = dano1 - heroe[0].hp; // calcula o dano da animacao de combate
			luta(&heroe[0].class, &heroe[1].class, dano1, 1);  // Chama a animacao de combate

			if (heroe[0].hp <= 0)
			{
				break;
			}

			damage(heroe,1); // Personagem 2 sofre dano
			dano2 = dano2 - heroe[1].hp; // calcula o dano da animacao de combate
			luta(&heroe[0].class, &heroe[1].class, dano2, 0);  // Chama a animacao de combate

			if (heroe[1].hp <= 0)
			{
				break;
			}

		}


	}while(heroe[0].hp > 0 && heroe[1].hp > 0);		 // Equanto os dois personagens possuirem vida, eles tomam dano

	/*Retorna o ganhador da rodada*/

	if (heroe[0].hp > heroe[1].hp )
	{
		return p1wins;
	}

	if (heroe[1].hp > heroe[0].hp)
	{
		return p2wins;
	}
}
