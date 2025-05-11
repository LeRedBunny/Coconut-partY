#ifndef MAP_H
#define MAP_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



#include "header.h"
#include "vector.h"
#include "random.h"
#include "test.h"





#define MAP_SIZE_X_MAX 40    //la taille maximum ne doit pas etre en dessous de 10
#define MAP_SIZE_Y_MAX 30    //la taille maximum ne doit pas etre en dessous de 10
#define DIR_RIGHT vector(-1, 0)

//fonctionne
void display (Map map, Crab *crabs, int n_crabs, Monkey *monkeys, int n_monkeys) {
    
	/* Displays the current state of the game */
	
	char **screen = malloc(sizeof(char*) * MAP_SIZE_Y_MAX);
	testAlloc(screen, "display(), screen");
	for (int y = 0; y < MAP_SIZE_Y_MAX; y++) {
		screen[y] = malloc(sizeof(char) * MAP_SIZE_X_MAX);
		testAlloc(screen[y], "display(), screen[y]");
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
	
	if(crabs != NULL){
    	for (Crab *crab = crabs; crab < crabs + n_crabs; crab++) {
    	
    		if (crab->path_index < 0) {
    			continue;
    		}
    		
    		p = map.path[crab->path_index];
    		screen[p.y][p.x] = 'c';
    	}
	}
	
	if(monkeys != NULL){
    	for (Monkey *monkey = monkeys; monkey < monkeys + n_monkeys; monkey++) {
    		p = monkey->position;
    		screen[p.y][p.x] = 'm';
    	}
    }
	
	
	printf("\n  ");
	for (int i = 0; i < MAP_SIZE_X_MAX; i++) {
		if (i < 10) {
			printf("%d ", i);
		} else {
			printf("%d", i);
		}
	}
	printf("\n");
	for(int y = 0; y<MAP_SIZE_Y_MAX; y++) {
		if (y < 10) {
			printf("%d ", y);
		} else {
			printf("%d", y);
		}
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
			if(screen[y][x] == 'c') {
				printf("\e[48;2;200;0;0m");
				printf("  ");
				//printf("\U0001f333 ");
			}
			if(screen[y][x] == 'm') {
				printf("\e[48;2;34;50;50m");
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
	
	for (int y = 0; y < MAP_SIZE_Y_MAX; y++) {
		free(screen[y]);
	}
	free(screen);
}

//fonctionne
void mapMakeIsland (Map* map){
	if(map->map != NULL){
	    for(int y = 0; y<MAP_SIZE_Y_MAX; y++) {
    		free(map->map[y]);
    	}
        	free(map->map);
    }
    
    
    
    
    	//initialise les variables utiles
    map->map = malloc(sizeof(char*) * MAP_SIZE_Y_MAX);
	testAlloc(map->map, "mapMakeIsland(), map->map");
	for(int y = 0; y<MAP_SIZE_Y_MAX; y++) {
		map->map[y] = malloc(sizeof(char) * MAP_SIZE_X_MAX);
		testAlloc(map->map[y], "mapMakeIsland(), map->map[y]");
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
	testAlloc(shift_y, "mapMakeIsland(), shift_y");
	for (int x=0; x<MAP_SIZE_X_MAX;x++){
		if (shift< -(map->width/map->height)){
        	shift++;
        } else if ((map->width/map->height)<shift){
        	shift--;
        }
		shift_y[x] = shift;
	    	shift+=randint(-1,1);
	}

    
	//systeme de génération de l'ile
	for (int y = 0; y < MAP_SIZE_Y_MAX; y++) {
        	if (shift_x< -(map->height/map->width)){
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
	free(shift_y);
}


//fonctionne
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

//fonctionne
int isBigger(int main, int second){
    return main>second;
}


int pathByBreadthFirst(int** digital_map, Map* map, Vector* to_visit, int* nb_visited, int* total_to_visit, int distance){
    Vector position = to_visit[(*nb_visited)];
    (*nb_visited)++;
    
    
    if (map->path[1].x == position.x && map->path[1].y == position.y){
        map->path_length = digital_map[position.y][position.x];
        map->path = realloc(map->path, sizeof(Vector) * (map->path_length));
        testAlloc(map->path, "pathByBreadthFirst(), map->path");
        return 1;
    }
    
    if(0<=position.x-1){
        if(digital_map[position.y][position.x-1] == -2){
            digital_map[position.y][position.x-1] = digital_map[position.y][position.x]+1;
            to_visit[(*total_to_visit)] = subtract(position, vector(1,0));
            (*total_to_visit)++;
        }
    }
    if(position.x+1<MAP_SIZE_X_MAX){
        if(digital_map[position.y][position.x+1] == -2){
            digital_map[position.y][position.x+1] = digital_map[position.y][position.x]+1;
            to_visit[(*total_to_visit)] = add(position, vector(1,0));
            (*total_to_visit)++;
        }
    }
    if(0<=position.y-1){
        if(digital_map[position.y-1][position.x] == -2){
            digital_map[position.y-1][position.x] = digital_map[position.y][position.x]+1;
            to_visit[(*total_to_visit)] = subtract(position, vector(0,1));
            (*total_to_visit)++;
        }
    }
    if(position.y+1<MAP_SIZE_Y_MAX){
        if(digital_map[position.y+1][position.x] == -2){
            digital_map[position.y+1][position.x] = digital_map[position.y][position.x]+1;
            to_visit[(*total_to_visit)] = add(position, vector(0,1));
            (*total_to_visit)++;
        }
    }
	
    if((*nb_visited) < (*total_to_visit)){
        if(pathByBreadthFirst(digital_map, map, to_visit, nb_visited, total_to_visit, distance+1)){
            return 1;
        }
    }
    
    return 0;
}


int placePath(int** digital_map, Map* map, Vector end){

    Vector position = end;
    int val = digital_map[position.y][position.x]-1;
    while (0 < val){
        map->path[val] = position;
        map->map[position.y][position.x] = 'p';
        if(0<=position.x-1){
            if (digital_map[position.y][position.x-1] == val){
                position = subtract(position, vector(1,0));
            }
        }
        if(position.x+1<MAP_SIZE_X_MAX){
            if (digital_map[position.y][position.x+1] == val){
                position = add(position, vector(1,0));
            }
        }
        if(0<=position.y-1){
            if (digital_map[position.y-1][position.x] == val){
                position = subtract(position, vector(0,1));
            }
        }
        if(position.y+1<MAP_SIZE_Y_MAX){
            if (digital_map[position.y+1][position.x] == val){
                position = add(position, vector(0,1));
            }
        }
        val--;
    }
    map->path[val] = position;
    map->map[position.y][position.x] = 'p';
}

//fonctionne
void changeCellValue(int** map, int val, int new){
    for(int y = 0; y<MAP_SIZE_Y_MAX; y++){
        for(int x = 0; x<MAP_SIZE_X_MAX; x++){
            if (map[y][x] == val){
                map[y][x] = new;
            }
        }
    }
}


void mapMakePath(Map* map){
	//vérifie les donnée récuppérer
	testAlloc(map->path, "mapMakePath(), map->path");
	testComparison(map->path_length == 2, "mapMakePath(), map->path_length");
	testComparison(10 <= map->width && map->width <= MAP_SIZE_X_MAX*2, "mapMakePath(), map.p->width");
	testComparison(10 <= map->height && map->height <= MAP_SIZE_Y_MAX*2, "mapMakePath(), map.p->height");
    
	//initialise les variables utiles
	int** digital_map = malloc(sizeof(int*) * MAP_SIZE_Y_MAX);
	testAlloc(digital_map, "mapMakerPath(), digital_map");
	for (int y=0; y<MAP_SIZE_Y_MAX; y++){
    	digital_map[y] = calloc(MAP_SIZE_X_MAX, sizeof(int));
    	testAlloc(digital_map[y], "mapMakePath(), digital_map[y]");
	}


    int nb_tree;
    if(MAP_SIZE_X_MAX%2 == 0){
	    nb_tree = (MAP_SIZE_X_MAX%2) * MAP_SIZE_Y_MAX;
    }else{
        nb_tree = (MAP_SIZE_X_MAX%2 +1) * MAP_SIZE_Y_MAX;
    }
    if(MAP_SIZE_Y_MAX%2 == 0){
	    nb_tree += (MAP_SIZE_Y_MAX%2) * MAP_SIZE_X_MAX;
    }else{
        nb_tree += (MAP_SIZE_Y_MAX%2 +1) * MAP_SIZE_X_MAX;
    }
    
	Vector* removable_tree = calloc(nb_tree, sizeof(Vector));
	testAlloc(removable_tree, "mapMakePath(), removable_tree");

	int nb_remaining_tree;
	int rand_tree;
	Vector position;
	
	int cell_val, cell1, cell2;

	float center_x = MAP_SIZE_X_MAX/2.0 ;
    float center_y = MAP_SIZE_Y_MAX/2.0 ;
    int is_y_axis;
    
    
    int total_to_visit;
    int nb_visited;
    Vector* to_visit = calloc(MAP_SIZE_X_MAX * MAP_SIZE_Y_MAX, sizeof(Vector));
    testAlloc(to_visit, "mapMakePath(), to_visit");


    
    //crée un acces, pour l'arriver et la fin, vers la parti boisser de l'ile
    for (int i = 0; i<2; i++){
        position = map->path[i];
        if (position.x*position.x < position.y*position.y){
            is_y_axis = 1;
        }else{
            is_y_axis = 0;
        }
        while(map->map[position.y][position.x] != 'T' || position.x%2 !=0 || position.y%2 !=0 ){
            digital_map[position.y][position.x] = i-2;
            switch (is_y_axis){
                case 0:
                    if(position.x%2 != 0 || position.y%2 == 0){
                        if(position.x<center_x){
                            position.x++;
                        }else{
                            position.x--;
                        }
                    }
                    is_y_axis = 1;
                    break;
                case 1:
                    if(position.y%2 != 0 || position.x%2 == 0){
                        if(position.y<center_y){
                            position.y++;
                        }else{
                            position.y--;
                        }
                    }
                    is_y_axis = 0;
                    break;
            }
        }
        digital_map[position.y][position.x] = i-2;
    }


	//parcours la map pour enregistrer les arbres suprimable et définir la map digital_map
	cell_val = 1;
	nb_tree = 0;
	for (int y = 0 ; y<MAP_SIZE_Y_MAX; y++){
    	for (int x = 0; x<MAP_SIZE_X_MAX; x++){
            	if(map->map[y][x] == 'T'){
                	if(y%2==0 && x%2==0){
                        map->map[y][x] = 't';//case de chemin possible
                        if(digital_map[y][x]==0){
                            digital_map[y][x] = cell_val;
                            cell_val++;
                        }
                    }
                    else if(y%2==0 || x%2==0){
                        removable_tree[nb_tree] = vector(x,y);//case de chemin liaison
                        nb_tree++;
                	}
            	}
    	}
	}
	nb_remaining_tree = nb_tree;


   //récupére alléatoirement des abres suprimable pour ouvrir un chemin


	while(digital_map[map->path[0].y][map->path[0].x] != digital_map[map->path[1].y][map->path[1].x]){
	    if(0>=nb_remaining_tree){
	        printf("erreur, plus d'arbre\n\n");
	        exit(93568);
	    }
    	rand_tree = rand()%nb_tree;
    	while(removable_tree[rand_tree].x ==-1 && removable_tree[rand_tree].y ==-1){
        		rand_tree++;
        		if(nb_tree<=rand_tree){
            		rand_tree = 0;
        		}
    	}
    	position = removable_tree[rand_tree]; 
    	removable_tree[rand_tree] = vector(-1,-1);
    	nb_remaining_tree--;
    	if(position.x%2==0){
    	    if(0<=position.y-1 && position.y+1<MAP_SIZE_Y_MAX){
    	        cell1 = digital_map[position.y-1][position.x];
    	        cell2 = digital_map[position.y+1][position.x];
    	        if(cell1 != 0 && cell2 != 0 && cell1 != cell2){
        	        if(cell1 < cell2){
        	            cell_val = cell1;
        	            changeCellValue(digital_map, cell2, cell_val);
        	        }
        	        else{
        	            cell_val = cell2;
        	            changeCellValue(digital_map, cell1, cell_val);
        	        }
        	        digital_map[position.y][position.x]= cell_val;
    	        }
    		}
    	}
    	else{
        	if(0<=position.x-1 && position.x+1<MAP_SIZE_X_MAX){
        	    cell1 = digital_map[position.y][position.x-1];
        	    cell2 = digital_map[position.y][position.x+1];
        	    if(cell1 != 0 && cell2 != 0 && cell1 != cell2){
            	    if( cell1 < cell2){
        	            cell_val = cell1;
        	            changeCellValue(digital_map, cell2, cell_val);
        	        }
        	        else{
        	            cell_val = cell2;
        	            changeCellValue(digital_map, cell1, cell_val);
        	        }
        	        digital_map[position.y][position.x]= cell_val;
        	    }
    		}	
    	}
        map->map[position.y][position.x] = 't';
    }


    //parcours en largeur pour trouver la valeur -2 qui est la valeur d'arriver
    to_visit[0] = map->path[0];
    digital_map[map->path[0].y][map->path[0].x] = 1;
    total_to_visit = 1;
    nb_visited = 0;
    
    Vector end = map->path[1];
    pathByBreadthFirst(digital_map, map, to_visit, &nb_visited, &total_to_visit, 2);
	//rebrouse chemin pour placer les casses du chemin
	placePath(digital_map, map, end);
    
    /*for (int y=0; y<MAP_SIZE_Y_MAX; y++){
    	free(digital_map[y]);
    	digital_map[y] = NULL;
	}
	free(digital_map);
	digital_map = NULL;*/
    //free(removable_tree);
    //removable_tree= NULL;
    //free(to_visit);
    //to_visit = NULL;

}








//fonctionne si mapMakePath(Map* map) fonctionne aussi 
Map mapInit(int width, int height, Vector direction, int seed) {
	/* Creates a new random map with the given width and height, generated with the given seed */
	
	//vérifie les donnée récuppérer et les rend compatible en cas d'erreur
	
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
    testAlloc(map.path, "mapInit(), map.path");
	
	
	//genere la map
	mapMakeIsland(&map);
	
	
	//genere le chemin
	map.path[0] = mapPositionAway(map, direction);
	map.path[1] = mapPositionAway(map, subtract(vector(0,0), direction));

	mapMakePath(&map);//cette fonction va changer la taille de map.path_length et va changer map.path pour un tableau plus grand contenant le chemin

	
	srand(time(NULL));
	return map;
}

void mapReset(Map* map){
    map->seed = 0;
    if (map->map != NULL){
        for (int y = 0; y<map->height;y++){
            if (map->map[y] != NULL){
                free(map->map[y]);
                map->map[y] = NULL;
            }
        }
        free(map->map);
        map->map = NULL;
    }
	map->width = 0;
	map->height = 0;
	if (map->path != NULL){
	    free(map->path);
	    map->path = NULL;
	}
	map->path_length = 0;
}

int roundNumber (Map map) {
    testComparison(5 <= map.path_length, "maxMonkeys(), map.path_length");
	return map.path_length / 5;
}

int maxMonkeys (Map map) {
    testComparison(5 <= map.path_length, "maxMonkeys(), map.path_length");
	return map.path_length / 5;
}

char getTile (Map map, Vector position) {
    testComparison(0 <= position.x && position.x < MAP_SIZE_X_MAX, "getTile(), position.x");
    testComparison(0 <= position.y && position.y < MAP_SIZE_Y_MAX, "getTile(), position.y");
	return map.map[position.y][position.x];
}

#endif
