
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