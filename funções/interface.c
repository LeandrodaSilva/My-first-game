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
