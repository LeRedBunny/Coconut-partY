#include<stdio.h>
#include<stdlib.h>
#include"header.h"
#include"vector.h"
#include "random.h"
#define SIZE 4

#define AVG_CRAB_TIMER 4
#define TIMER_VARIANCE 3

#define DEATH_INDEX -1
#define BEFORE_SPAWN_INDEX -2

#define COEF_EVOLUTION 0.125

int crabTimer () {
	/* Returns a new value for the crab spawn timer */
	return AVG_CRAB_TIMER + randint(-TIMER_VARIANCE, TIMER_VARIANCE);
}
	
void kill (Crab *crab){
	crab->path_index = DEATH_INDEX;
}  // si le crabe meurt, il va à l'adresse -1 du chemin pour le sortir de la map.

int move (Crab *crab, Map map){
	while(crab->health > 0 && crab->path_index > Map.path_length){
		crab->path_index += crab->speed;
			if(crab->path_index >= Map.path_length){
				kill(crab);
				return 1;
			}
	}
} //Si le crabe est en vie, et qu'il n'a pas atteint la fin du chemin, il avance de n cases selon sa vitesse. S'il atteint la fin de la map, il meurt et fait perdre 1 point de vie au joueur.

int spawnCrab(Crab *tab_crabs, int length_tab_crab){
	for(int i = 0; i < length_tab_crab; i++){
		if(tab_crabs[i].path_index == BEFORE_SPAWN_INDEX){
			tab_crabs[i].path_index == 0;
			return 1;
		}
	}
	return 0;
} //Pour le premier crabe du tableau des crabes qui a un indice de chemin égale à -2, on le place  sur le terrain. S'il y en a plus, la fonction retourne 0.

Crab randomCrab (int round_number){
    if (round_number <= 0){
        round_number = 1;
    }else if (round_number > 20){
        round_number = 20;
    }
    
    Crab crab;
    crab.path_index = 0;
    crab.health = (round_number * COEF_EVOLUTION) * randint(16,28);
    if ((round_number * COEF_EVOLUTION) * randint(1,11) >10){
        crab.speed =2;
    }else{
        crab.speed =1;
    }
    
    return crab;
}//En fonction du nombre de tour joué, crée un crab de caracteristique variable

int main(){
	Crab **tab_crabs[SIZE];
	MAP map;
	map.path_length = 8;
	for(int i = 0; i < 40; i++){
		
	}
	
}
