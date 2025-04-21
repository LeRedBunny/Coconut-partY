


typedef struct {
	int x, y;
} Vector;

typedef struct {
	int width, height;
	char **map;
	Vector *path;
	int path_length;
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



	// Crabs

int move (Crab *crab, Map map);

void kill (Crab *crab);

Crab randomCrab (int round_number);
Crab *randomCrabs (int n, int round_number);



	// Monkeys

void shoot (Monkey monkey, Crab *crabs, int n_crabs);


	// Game

void round (Map map, Monkey *monkeys, int n_monkeys, int round_number);

int game (char *save); // save is a string containing the save file path, or NULL if new game






