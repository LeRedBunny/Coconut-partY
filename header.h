


typedef struct {
	int x, y;
} Vector;

typedef struct {
	int width, height;
	char **map;
	Vector *path;
} Map;


typedef struct {
	int path_index;
	int health;
	int speed;
} Crab;


typedef struct {
	Vector position;
	int range;
	int damage; 	
} Monkey;


	// Map


Map generate (int width, int height, int seed);

void display (Map map, Crab *crabs, int n_crabs, Monkey *monkeys, int n_monkeys);



	// Crabes

Vector nextTile (Crab *crab, Map map);

void move (Crab *crab, Map map);



	// Monkeys

void shoot (Monkey monkey, Crab *crabs, int n_crabs);





