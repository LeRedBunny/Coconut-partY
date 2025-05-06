#ifndef MAP_H
#define MAP_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



#include "header.h"
#include "vector.h"





#define MAP_SIZE_X_MAX 60    //la taille maximum ne doit pas etre en dessous de 10
#define MAP_SIZE_Y_MAX 40    //la taille maximum ne doit pas etre en dessous de 10
#define DIR_RIGHT vector(-1, 0)


//void display (Map map, Crab *crabs, int n_crabs, Monkey *monkeys, int n_monkeys) {
void display (Map map) {
	/* Displays the current state of the game */
	
	char **screen = malloc(sizeof(char*) * MAP_SIZE_Y_MAX);
	if (screen == NULL) {
		printf("Allocation error: void display (Map map, Crab *crabs, int n_crabs, Monkey *monkeys, int n_monkeys)\nscreen");
        	exit(4110);//4110 for AllO-cation
    	}
	for (int y = 0; y < MAP_SIZE_Y_MAX; y++) {
		screen[y] = malloc(sizeof(char) * MAP_SIZE_X_MAX);
		if (screen[y] == NULL) {
    	    		printf("Allocation error: void display (Map map, Crab *crabs, int n_crabs, Monkey *monkeys, int n_monkeys)\nscreen[y]");
            		exit(4110);//4110 for AllO-cation
        	}
	}
	
	
	for (int y = 0; y < MAP_SIZE_Y_MAX; y++) {
		for (int x = 0; x < MAP_SIZE_X_MAX; x++) {
			screen[y][x] = map.map[y][x];
		}
	}
	
	
	Vector p;
	for (int i = 0; i < map.path_length; i++) {
		p = map.path[i];
		screen[p.y][p.x] = 'p';
	}
	
	/*
	for (Crab *crab = crabs; crab < crabs + n_crabs; crab++) {
	
		if (crab->path_index < 0) {
			continue;
		}
		
		p = map.path[crab->path_index];
		screen[p.y][p.x] = 'c';
	}
	
	for (Monkey *monkey = monkeys; monkey < monkeys + n_monkeys; monkey++) {
		p = monkey->position;
		screen[p.y][p.x] = 'm';
	}
	*/
	
	
	for(int y = 0; y<MAP_SIZE_Y_MAX; y++) {
		for(int x = 0; x<MAP_SIZE_X_MAX; x++) {
			if(screen[y][x] == 'w') {
                		printf("\033[44m");
                		printf("  ");
				//printf("\U0001f30a ");
			}
			if(screen[y][x] == 'T') {
				printf("\033[42m");
				printf("  ");
				//printf("\U0001f333 ");
			}
			if(screen[y][x] == 't') {
				printf("\e[48;2;2;131;6m");
				printf("  ");
				//printf("\U0001f333 ");
			}
			if(screen[y][x] == 'o') {
				printf("\e[48;2;200;0;0m");
				printf("  ");
				//printf("\U0001f333 ");
			}
			if(screen[y][x] == 's') {
				printf("\e[48;2;223;198;65m");
				printf("  ");
			}
			if(screen[y][x] == 'p') {
				printf("\e[48;2;23;4;220m");
				printf("  ");
			}
			printf("\033[0m");
		}
		printf("\n");
	}

}


void mapMakeIsland (Map* map, int seed){
	if(map->map != NULL){
        	printf("erreur possible, on demande de générer un terrain alors qu'il existe déja\n");
        	exit(234);
    	}
    
    
    
    
    	//initialise les variables utiles
    	srand(seed);
    	map->map = malloc(sizeof(char*) * MAP_SIZE_Y_MAX);
	if (map->map == NULL){
		printf("Allocation error: char** mapGenerate (int radius, int width, int height)\nchar ** map");
        	exit(4110);//4110 for AllO-cation
	}
	for(int y = 0; y<MAP_SIZE_Y_MAX; y++) {
		map->map[y] = NULL;
		map->map[y] = malloc(sizeof(char) * MAP_SIZE_X_MAX);
		if (map->map[y] == NULL) {
			printf("Allocation error: char** mapGenerate (int radius, int width, int height)\nchar* map[y]");
            		exit(4110);//4110 for AllO-cation
		}
	}
	
    	float center_x = MAP_SIZE_X_MAX/2.0 ;
	float center_y = MAP_SIZE_Y_MAX/2.0 ;
	double distance_x, distance_y;

	float radius_x = map->width/2.0;
	
	float radius_y = map->height/2.0;
	float teta;
	
	int shift_x = 0;
	int shift = 0;
	int* shift_y = malloc(sizeof(int) * MAP_SIZE_X_MAX);
	if (shift_y == NULL){
		printf("Allocation error: char** mapGenerate (int radius, int width, int height)\nint* shift_y");
        	exit(4110);//4110 for AllO-cation
	}
	for (int x=0; x<MAP_SIZE_X_MAX;x++){
		if (shift<0-(map->width/map->height)){
        	shift++;
        } else if ((map->width/map->height)<shift){
        	shift--;
        }
		shift_y[x] = shift;
	    	shift+=randint(-1,1);
	}

    
	//systeme de génération de l'ile
	for (int y = 0; y < MAP_SIZE_Y_MAX; y++) {
        	if (shift_x<0-(map->height/map->width)){
            		shift_x++;
        	} else if ((map->height/map->width)<shift_x){
            		shift_x--;
        	}
        
        	shift_x += randint(-1, 1);
        
		for (int x = 0; x < MAP_SIZE_X_MAX; x++) {
			distance_y = pow(center_y - y+ shift_y[x], 2);
			distance_x = pow(center_x -x+shift_x, 2);
		    
			teta = atan2(center_y-y+shift_y[x],center_x-x+shift_x);
			if(distance_x + distance_y >= pow(((radius_x+1) * (radius_y+1)) / sqrt(pow((radius_x+1) * sin(teta),2) + pow((radius_y+1) * cos(teta),2)),2 ) ){
				map->map[y][x] = 'w';
				
			} else if(distance_x + distance_y >= pow(((radius_x-1) * (radius_y-1)) / sqrt(pow((radius_x-1) * sin(teta),2) + pow((radius_y-1) * cos(teta),2)),2 ) ) {
				map->map[y][x] = 's';
			}else {
				map->map[y][x] = 'T';
			}
		}
	}
}



Vector mapPositionAway(Map map, Vector direction){
    
	//initialise les variables utiles
	Vector deplacement = direction;
    	Vector position = add(vector(MAP_SIZE_X_MAX/2, MAP_SIZE_Y_MAX/2), scale(direction, MAP_SIZE_Y_MAX+MAP_SIZE_X_MAX));
	Vector next_position;
	
	//se rapproche de l'ile depuis l'exterieur
	while(position.x<0 || MAP_SIZE_X_MAX<=position.x || position.y<0 || MAP_SIZE_Y_MAX<=position.y ){
		position = subtract(position,direction);
	}
	while(map.map[position.y][position.x] == 'w'){
		position = subtract(position,direction);
		if(position.x<0 || MAP_SIZE_X_MAX<=position.x || position.y<0 || MAP_SIZE_Y_MAX<=position.y ){
	        	printf("Le point de départ ou d'arriver na pas trouvé d'ile\nSEED: %i    WIDTH: %i    HEIGHT: %i\nWIDTH MAX: %i    HEIGHT MAX: %i",map.seed, map.width, map.height, MAP_SIZE_X_MAX, MAP_SIZE_Y_MAX);
	        	exit(8);
	    	}
	}
	
	//deplacement vers le bord de l'ile

	if(deplacement.x*deplacement.x < deplacement.y*deplacement.y){
        	if (deplacement.y<0){
            		deplacement = vector(0,-1);
        	}else{
            		deplacement = vector(0,1);
        	}
    	}else{
        	if (deplacement.x<0){
            		deplacement = vector(-1,0);
        	}else{
            		deplacement = vector(1, 0);
        	}
    	}
    	next_position = add(position, deplacement);
	while (0<=next_position.y && next_position.y<MAP_SIZE_Y_MAX && 0<=next_position.x && next_position.x<MAP_SIZE_X_MAX){
		if(map.map[next_position.y][next_position.x] == 'w'){
	        	break;
	    	}
	    	position = next_position;
	    	next_position = add(position, deplacement);
	}
	
	return position;
}



void mapMakePath(Map* map, int seed){
	//vérifie les donnée récuppérer
    	if(map->path==NULL){
        	printf("Erreur la liste n'existe pas\n mapMakePath(Map* map, int seed)");
        	exit(243);
    	}

    
    
    	//initialise les variables utiles
    	srand(seed);
    
    
    	int digital_width = map->width+(2*(map->height/map->width));
    	if (digital_width>MAP_SIZE_X_MAX){
        	digital_width=MAP_SIZE_X_MAX;
    	}
    	int digital_height = map->height+(2*(map->width/map->height));
    	if (digital_height>MAP_SIZE_Y_MAX){
        	digital_height=MAP_SIZE_Y_MAX;
    	}
    	int** digital_map = malloc(sizeof(int*) * digital_height);
    	if (digital_map == NULL){
        	printf("Allocation error: void mapMakePath(Map* map, Vector* start_end)\ndigital_map");
            	exit(4110);//4110 for AllO-cation
        }
    	for (int y=0; y<digital_height; y++){
        	digital_map[y] = calloc(digital_width, sizeof(int));
        	if (digital_map[y] == NULL){
            		printf("Allocation error: void mapMakePath(Map* map, Vector* start_end)\ndigital_map[y]");
            		exit(4110);//4110 for AllO-cation
        	}
    	}
    	for (int y = 0 ; y<digital_height; y++){
        	for (int x = 0; x<digital_width; x++){
            		printf(" %i",digital_map[y][x]);
        	}
        	printf("\n");
    	}
    	printf("\n");printf("\n");printf("\n");
    	int nb_rem_tree = 0;
    	Vector* removable_tree = malloc(sizeof(Vector) * MAP_SIZE_X_MAX  * MAP_SIZE_Y_MAX);
    	if (removable_tree == NULL){
        	printf("Allocation error: void mapMakePath(Map* map, Vector* start_end)\nremovable_tree");
        	exit(4110);//4110 for AllO-cation
    	}

    	int nb_remaining_tree;
    	int rand_tree;
    	Vector tree;
    
    	float center_x = MAP_SIZE_X_MAX/2.0 ;
	float center_y = MAP_SIZE_Y_MAX/2.0 ;
    	Vector direction;


    	//parcours la map pour enregistrer les arbres suprimable et définir la map digital_map
    	for (int y = (MAP_SIZE_Y_MAX-digital_height)/2 ; y<MAP_SIZE_Y_MAX-((MAP_SIZE_Y_MAX-digital_height)/2); y++){
        	for (int x = (MAP_SIZE_X_MAX-digital_width)/2; x<MAP_SIZE_X_MAX-((MAP_SIZE_X_MAX-digital_width)/2); x++){
	            	printf(" %c",map->map[y][x]);
	            	if(map->map[y][x] == 'T'){
	                	if(y%2==1 && x%2==1){
	                    		map->map[y][x] = 't';
	                	}
	                	else if(y%2==1 || x%2==1){
	                    		removable_tree[nb_rem_tree] = vector(x,y);
	                    		nb_rem_tree++;
	                	}
	            	}
        	}
        	printf("\n");
    	}
    	printf("\n\n\n");
    	nb_remaining_tree = nb_rem_tree;
    
   	//récupére alléatoirement des abres suprimable pour ouvrir un chemin
    
    	while(nb_remaining_tree!=0){
        	rand_tree = rand()%nb_rem_tree;
        	while(removable_tree[rand_tree].x ==-1 && removable_tree[rand_tree].y ==-1){
            		rand_tree++;
            		if(nb_rem_tree<=rand_tree){
                		rand_tree = 0;
            		}
            
        	}
        	tree = removable_tree[rand_tree]; 
        	removable_tree[rand_tree] = vector(-1,-1);
        	nb_remaining_tree--;
        	if(tree.x%2==0){
            		if(0<=tree.x-1 && tree.x+1<MAP_SIZE_X_MAX){
                		map->map[tree.y][tree.x-1] = 'o';
                		map->map[tree.y][tree.x+1] = 'o';
            		}
        	}
        	else{
            		if(0<=tree.y-1 && tree.y+1<MAP_SIZE_Y_MAX){
                		map->map[tree.y-1][tree.x] = 'o';
                		map->map[tree.y+1][tree.x] = 'o';
            		}
        	}
    	}
	//je me suis arreter ici pour le moment, honnetement j'ai plus en tete ce qu'il y a à la suite en bas, tkt j'ai un plan de fonctionnement pour la suite de la fonction, il me faut juste le temps
    
    	//crée un acces, pour l'arriver et la fin, vers la parti boisser de l'ile
    	Vector radius_from_start;
    	for (int i = 0; i<2; i++){
        	if(map->path[i].x < center_x){
            		radius_from_start.x = center_x - map->path[i].x;
            		direction.x = 1;
        	}else{
            		radius_from_start.x = map->path[i].x - center_x;
            		direction.x = -1;
        	}
        	if(map->path[i].y < center_y){
            		radius_from_start.y = center_y - map->path[i].y;
            		direction.y = 1;
        	}else{
            		radius_from_start.y = map->path[i].y - center_y;
            		direction.y = -1;
        	}
        
        
        	if(radius_from_start.x < radius_from_start.y){
            		direction.x = 0;
        	}else{
            		direction.y = 0;
        	}
    	}
}

Map mapInit(int width, int height, Vector direction, int seed) {
	/* Creates a new random map with the given width and height, generated with the given seed */
	
	//vérifie les donnée récuppérer
	if(width<0){
		width = - width;
    	}
    	if(width> MAP_SIZE_X_MAX*2){
        	width = MAP_SIZE_X_MAX;
    	}else if (width<10){
        	width = 10;
    	}
    
    	if(height<0){
        	height = - height;
    	}
    	if(height> MAP_SIZE_Y_MAX*2){
        	height = MAP_SIZE_Y_MAX;
    	}else if (height<10){
        	height = 10;
    	}
    
    	if (direction.x ==0 && direction.y == 0){
	    	direction = DIR_RIGHT;
	}

	
	//initialise les valeurs
	srand(seed);
	
	Map map;
	map.seed = seed;
	map.width = width;
	map.height = height;
	map.map = NULL;
	map.path_length = 2;
	map.path = malloc(sizeof(Vector) * map.path_length);

	
	
	//genere la map
	mapMakeIsland(&map, seed);
	
	
	//genere le chemin
	map.path[0] = mapPositionAway(map, direction);
	map.path[1] = mapPositionAway(map, subtract(vector(0,0), direction));
	mapMakePath(&map, seed);//cette fonction va changer la taille de map.path_length et va changer map.path pour un tableau plus grand contenant le chemin

	
	srand(time(NULL));
	return map;
}


int roundNumber (Map map) {
	return (map.width + map.height) / 15;//n'est ce pas trop petit? la taille minimum est de 10|10 donc 20/15 = 1 (en int) ca risque d'etre trop peut 
}

#endif




