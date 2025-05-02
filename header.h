


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


typedef struct {
	int round_number, rounds;
	Map map;
	Monkey *monkeys;
	int n_monkeys;
	int health;
	int bananas;
} GameData;


	// Vector

Vector vector (int x, int y);

Vector add (Vector u, Vector v);

Vector scale (Vector v, int scalar);

Vector subtract (Vector u, Vector v);

float length (Vector v);

float distance (Vector u, Vector v);




	// Map


Map generate (int ray, int seed, Vector direction);

void display (Map map, Crab *crabs, int n_crabs, Monkey *monkeys, int n_monkeys);

int roundNumber (Map map); // Calculates the number of rounds to play to win on the given map		<-


	// Crabs

int move (Crab *crab, Map map);

void kill (Crab *crab);

Crab randomCrab (int round_number); // Creates a random crab

Crab *randomCrabs (int n, int round_number); // Creates an array of random crabs

int isDead (Crab crab);

int allDead (Crab *crabs, int nb_crab);


	// Monkeys

void shoot (Monkey monkey, Crab *crabs, int n_crabs);

void newMonkey (Map map, Monkey *monkeys);

void upMonkey (Monkey *monkey);


	// Game

void gameRound (GameData data);

void manage (GameData data); // Phase of placing new monkeys and upgrading them				<-

int startGame (char *save); // save is a string containing the save file path, or NULL if new game	<-

int game (GameData data); // Should be given all the data needed to play

void load (char *save_file, GameData *data);								// <-

void save (char *save_name, GameData data);							        // <-

int score (GameData data); // Gives the player a score based on the final state of the game




	// Other

int randint (int a, int b);

int askInt (int a, int b); // Asks the player to input an integer in [a; b]

int choice (char **options, int n); // Prints the options and asks the player to choose, returns the chosen index



