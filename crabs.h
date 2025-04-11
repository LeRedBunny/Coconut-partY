#include<stdio.h>
#include<stdlib.h>
#include"header.h"
#include"vector.h"
define SIZE 4
void kill (Crab *crab){
	crab->path_index = -1;
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
		if(tab_crabs[i].path_index == -2){
			tab_crabs[i].path_index == 0;
			return 1;
		}
	}
	return 0;
} //Pour le premier crabe du tableau des crabes qui a un indice de chemin égale à -2, on le place  sur le terrain. S'il y en a plus, la fonction retourne 0.

int main(){
	Crab **tab_crabs[SIZE];
	MAP map;
	map.path_length = 8;
	for(int i = 0; i < 40; i++){
		
	}
	
}
