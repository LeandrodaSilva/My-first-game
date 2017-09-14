#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#define t 20 // velocidade da animação de combate
#define t_archer 200 // velocidade da animação de combate
#include "regenum.c"
#include "nomeio.c"
#include "animation.c"
#include "sistema.c"
#include "interface.c"
#include "calculos.c"




void main()
{
	int op,          // armazena a escolha das opcoes do menu principal
	sis = 1, 		 // armazena a escolha do sistema operacional
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
