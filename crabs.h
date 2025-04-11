#include<stdio.h>
#include<stdlib.h>
#include"header.h"
#include"vector.h"

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

