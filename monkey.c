#include <stdio.h>
#include "header.h"
#include "vector.h"

#define RANGE_UPGRADE 1;
#define DAMAGE_UPGRADE 2;


void kill(Crab *crab){//a enlever
	printf("le crabe en position index %d à été tué\n\n", crab->path_index);
}











Monkey newMonkey(Vector position){
	/*add a monkey based on a position*/
    Monkey monkey;
    monkey.position = position;
    monkey.range = 1;
    monkey.damage = 2;
    return monkey;
}

void upMonkey(Monkey *monkey){
	/*level up a monkey in parameter*/
    monkey->range += RANGE_UPGRADE;
    monkey->damage += DAMAGE_UPGRADE;
}

void shoot (Monkey monkey, Crab *crabs, int n_crab, Map map){
	/*attacks the oldest crab created, near the monkey*/
	Vector distance;
	int n = n_crab-1;
	while(0<=n){
		if(0 < crabs[n].health){
			distance = substract(monkey.position, map.path[crabs[n].path_index]);
			if(distance.x * distance.x + distance.y * distance.y <= monkey.range*monkey.range){
				crabs[n].health -= monkey.damage;
				printf("attaque crabe n°%d par singe en position (%d,%d)!\n", n, monkey.position.x, monkey.position.y);// a enlever durant l'intégration dans le code principale
				if( crabs[n].health <= 0){
					kill(crabs + n);
				}
				n = -1;
			}
		}
		n--;
	}
}



 














//pour tester

int main(){
	//on défini une map qui servira a tester
	Map map;
	Vector path[23];
	for(int y=0; y<7; y++){
		path[y] = vector(5,y);
	}
	for(int x=5; x<15; x++){
		path[1+x] = vector(x,6);
	}
	for(int y=6; y<14; y++){
		path[9+y] = vector(14,y);
	}
	for(int i=0; i<23; i++){
		printf("(%d,%d)\n",path[i].x, path[i].y);
	}
	map.path = path;
	
	//on défini 5 crabe a des positions différentes (actuellement en ligne sur le début du chemin)
	Crab crabs[5];
	crabs[0].path_index = 2;
	crabs[0].health = 10;
	crabs[0].speed = 1;
	
	crabs[1].path_index = 3;
	crabs[1].health = 10;
	crabs[1].speed = 1;
	
	crabs[2].path_index = 4;
	crabs[2].health = 10;
	crabs[2].speed = 1;
	
	crabs[3].path_index = 5;
	crabs[3].health = 10;
	crabs[3].speed = 1;
	
	crabs[4].path_index = 6;
	crabs[4].health = 10;
	crabs[4].speed = 1;
	

	//liste de 3 singes
	Monkey monkeys[3];
	
	monkeys[0] = newMonkey(4,4);//création de singe
	upMonkey(&monkeys[0]);//amélioration du singe
	
	monkeys[1] = newMonkey(8,7);
	
	monkeys[2] = newMonkey(15,11);
	
	
	//effectue un tire pour tout les singes
	for(int m=0; m<3; m++){
		shoot(monkeys[m], crabs, 5, map);
	}
	
	
	
	
	
	return 0;
}
