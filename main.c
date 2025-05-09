


void mainMenu () {
	
	char *oui_non[2] = {"Oui", "Non"};
	
	printf("Bienvenue à Coconut PartY!");
	
	char *options[3] = {
			    "Démarrer",
			    "Continuer",
			    "Quitter"
			    };
	int option = choice(options, 3);
	
	switch (option) {
		
		case 1 :
			GameData data;
			printf("\nParamètres de la partie :");
			
			printf("\nHauteur de l'île :");
			int height = askInt(0, MAX_HEIGHT);
			
			printf("\nLargeur de l'île");
			int width = askInt(0, MAX_WIDTH);
			
			unsigned long seed;
			printf("\nSouhaitez-vous entrer une seed ?");
			if (binaryChoice()) {
				scanf("%d", &seed);
			} else {
				seed = time(NULL);
			}
			
			printf("\nEntrez le nombre de PV : ");
			data.health = askInt(1, 10);
			
			data.map = mapInit(width, height, DIR_RIGHT, seed);
			data.monkeys = malloc(sizeof(Monkey) * maxMonkeys(data.map));
			data.n_monkeys = 1;
			data.bananas = 0;
			data.rounds = roundNumber(data.map);
			data.round_number = 0;
			break
		
		case 2 :
			Save *saves = getSaves();
			char *save_names[3];
			for (int i = 0; i < 3; i++) {
				save_name[i] = saves[i].name;
			}
			GameData data = saves[choice(save_names, 3)].data;
			break
		
		case 3 :
			printf("\nAu revoir!");
			exit(0);
	}
	
	int score = game(data);
	if (score) {
		printf("\nVous avez eu un score de %d!", score);
	}
}

int main () {
	
	while(1) {
		mainMenu();
	}
	
	return 0;
}
