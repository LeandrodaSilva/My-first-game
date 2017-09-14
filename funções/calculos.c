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
