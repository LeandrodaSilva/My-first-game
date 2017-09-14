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


