/*
nécessite l'inclusion de :
header.h
stdlib.h
stdio.h
vector.h
*/


#define SIZE_OCEAN 40
#define DIR_RIGHT vector(-1, 0)


void display (Map map, Crab *crabs, int n_crabs, Monkey *monkeys, int n_monkeys) {
	/* Displays the current state of the game */
	
	char **screen = malloc(width * height);
	if (screen == NULL) {exit(1); }
	
	for (int y = 0; y < map.height; y++) {
		for (int x = 0; x < map.width; x++) {
			screen[y][x] = map[y][x];
		}
	}
	
	Vector p;
	for (int i = 0; i < map.path_length; i++) {
		p = map.path[i];
		screen[p.y][p.x] = 'p';
	}
	
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
	
	
	
	for (int y = 0; y < map.height; y++) {
		for (int x = 0; x < map.width; x++) {
			printf("%c", screen[y][x]);
		}
		printf("\n");
	}
}


Map generate (int ray, int seed, Vector direction) {
	
	if (ray<5){
        	ray=5;
    	}else if(ray>31){
        	ray = 31;
    	}
	/* Creates a new random map with the given width and height, generated with the given seed */
	srand(seed);

	//initialise la variable Map
	Map map;
	map.width = SIZE_OCEAN;
	map.height = SIZE_OCEAN;
	map.map = malloc(sizeof(char*) * map.height);
	if (map.map == NULL){
		printf("Allocation error: Map generate (int width, int height, int seed, int direction)\nmap.map");
		exit(4110);//4110 for AllO-cation
	}
	for(int y = 0; y<map.width; y++) {
		map.map[y] = NULL;
		map.map[y] = malloc(sizeof(char) * map.width);
		if (map.map[y] == NULL) {
			printf("Allocation error: Map generate (int width, int height, int seed, int direction)\nmap.map[y]");
        		exit(4110);//4110 for AllO-cation
		}
	}
	
	

	//crée un terrain
	float center_x = map.width/2.0 ;
	float center_y = map.height/2.0 ;
	float rayIsland = (ray -(1.25)) * (ray -(1.25)) ;
	float rayBeach = (ray +(1.25)) * (ray +(1.25)) ;
	

	int distance_x, distance_y;
	for (int y = 0; y < map.height; y++) {
		distance_y = (center_y-y)*(center_y-y);
		for (int x = 0; x < map.width; x++) {
			distance_x = (center_x-x)*(center_x-x);
		    
			if(distance_x + distance_y >= rayBeach) {
				map.map[y][x] = 'w';
			} else if(distance_x + distance_y >= rayIsland) {
				if(rand()%(distance_x + distance_y)<=2 * rayIsland -distance_x - distance_y){
					map.map[y][x] = 's';
				}else{
					map.map[y][x] = 'w';
			    	}
			}else {
				map.map[y][x] = 'T';
			}
		}
	}
	
	
	
	//positionne le début et l'arrivé
	map.path_length = 2;  
    	Vector path[2];
	
	
	Vector position = vector(map.width/2, map.height/2);
	if (direction.x ==0 && direction.y == 0){
		direction = DIR_RIGHT;
	}
	Vector deplacement = direction;
	
	for (int i = 0; i<2; i++){
    		for (int j = 0; j<2; j++){
        		while (0<=(position.y+ deplacement.y) && (position.y+ deplacement.y)<map.height && 0<=(position.x+ deplacement.x) && (position.x+ deplacement.x)<map.width){
        	    		if(map.map[position.y+ deplacement.y][position.x+ deplacement.x] == 'w'){
        	        		break;
        	    		}
        	    		position = add(position, deplacement);

        		}
        		if(j==1){
        	    		continue;
        		}else if(deplacement.x*deplacement.x < deplacement.y*deplacement.y){
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
    		}
    		if(i==1){
    	    		path[map.path_length - 1] = position;
    	    		continue;
        	}else{
            		path[0] = position;
            		position = vector(map.width/2, map.height/2);
            		deplacement = subtract(vector(0,0), direction) ;
        	}
    	
    	}

	//défini la taille du chemin ainsi que son tableau associé
    	if(path[0].x<path[1].x){
        	map.path_length = path[1].x - path[0].x;
    	}else{
        	map.path_length = path[0].x - path[1].x;
    	}
    	if(path[0].y<path[1].y){
        	map.path_length += path[1].y - path[0].y;
    	}else{
        	map.path_length += path[0].y - path[1].y;
    	}
    	map.path_length++;
    
    
	map.path = malloc(sizeof(Vector) * map.path_length);
	if(map.path == NULL){
		printf("Allocation error: Map generate (int width, int height, int seed, int direction)\nmap.path");
        	exit(4110);//4110 for AllO-cation
	}
	
	map.path[0] = path[0];
	map.path[map.path_length-1] = path[1];

	//crée un chemin entre la première et la dernière case du tableau
	Vector etap[3];
    
	Vector ray_start;
    	if(map.path[0].x < center_x){
        	ray_start.x = center_x - map.path[0].x;
        	direction.x = 1;
	}else{
        	ray_start.x = map.path[0].x - center_x;
        	direction.x = -1;
    	}
    	if(map.path[0].y < center_y){
        	ray_start.y = center_y - map.path[0].y;
        	direction.y = 1;
    	}else{
        	ray_start.y = map.path[0].y - center_y;
        	direction.y = -1;
    	}
    
    	if(ray_start.x < ray_start.y){
        	deplacement.x = 0;
        	deplacement.y = direction.y;
        	etap[0] = vector(map.path[0].x,center_y);
        	etap[1] = vector(map.path[map.path_length-1].x, center_y);
    	}else{
        	deplacement.x = direction.x;
        	deplacement.y = 0;
        	etap[0] = vector(center_x,map.path[0].y);
        	etap[1] = vector(center_x, map.path[map.path_length-1].y);
    	}
    	etap[2] = map.path[map.path_length-1];
    
    	position = map.path[0];
    	int num_case = 1;
    	for(int i = 0; i< 3; i++){
        	while(!(position.x == etap[i].x && position.y == etap[i].y)){
            		position = add(position, deplacement);
            		map.path[num_case] = position;
            		num_case++;
        	}
        	if(deplacement.x == 0){
            		deplacement.x = direction.x;
        	}else{
            		deplacement.x = 0;
        	}
        	if(deplacement.y == 0){
            		deplacement.y = direction.y;
        	}else{
            		deplacement.y = 0;
        	}
    	}

	
	
	return map;
}






