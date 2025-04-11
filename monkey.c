#include <stdio.h>
#include "header.h"



void kill(Crab *crab){//a enlever
	printf("le crabe en position index %d à été tué\n\n", crab->path_index,crab->path_index);
}





void shoot (Monkey monkey, Crab *crabs, int n_crab, Map map){
	Vector range;
	int n = 0;
	while(n<n_crab){
		range = substract(monkey.position, map.path[crabs[n].path_index]);
		if(range.x * range.x + range.y * range.y <= monkey.range*monkey.range){
			crabs[n].health -= monkey.damage;
			printf("attaque crabe n°%d par singe en position (%d,%d)!\n", n, monkey.position.x, monkey.position.y);// a enlever durant l'intégration dans le code principale
			if( crabs[n].health <= 0){
				kill(&crabs[n]);
			}
			n=n_crab;
		}
		n++;
	}
}




 














//pour tester

int main(){
	Vector path[23];
	for(int y=0; y<7; y++){
		path[y] = vector(0,y);
	}
	for(int x=5; x<15; x++){
		path[7+x] = vector(x,6);
	}
	for(int y=6; y<14; y++){
		path[y] = vector(14,y);
	}
	for(int i=0; i<23; i++){
		printf("(%d,%d)\n",path[i].x, path[i].y);
	}
	

	Crab crabs[5];
	crabs[0].path_index = 0;
	crabs[0].health = 10;
	crabs[0].speed = 1;
	
	crabs[1].path_index = 6;
	crabs[1].health = 10;
	crabs[1].speed = 1;
	
	crabs[2].path_index = 12;
	crabs[2].health = 10;
	crabs[2].speed = 1;
	
	crabs[3].path_index = 17;
	crabs[3].health = 10;
	crabs[3].speed = 1;
	
	crabs[4].path_index = 22;
	crabs[4].health = 10;
	crabs[4].speed = 1;
	
	
	Monkey monkeys[3];
	monkeys[0].position = vector(4, 4);
	monkeys[0].range = 3;
	monkeys[0].damage = 20;
	
	monkeys[1].position = vector(8, 7);
	monkeys[1].range = 3;
	monkeys[1].damage = 5;
	
	monkeys[2].position = vector(15, 11);
	monkeys[2].range = 3;
	monkeys[2].damage = 5;
	

	for(int m=0; m<3; m++){
		shoot(monkeys[m], crabs, 5, path);
	}





	return 0;
}
