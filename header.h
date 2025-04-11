


typedef struct {
	int x, y;
} Vector;

typedef struct {
	int width, height;
	char **map;
} Map;


typedef struct {
	Vector position;
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

void display (Map map, Crab *crabs, Monkey *monkeys);



	// Crabes

Vector nextTile (Crab *crab, Map map);

void move (Crab *crab, Map map);



	// Monkeys

void shoot (Monkey monkey, Crab *crabs);





