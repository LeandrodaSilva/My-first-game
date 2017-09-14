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
