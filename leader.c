#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>


int guess_num;
int random_num;
double square_root;
char c;
int num_guesses;
char name[20];
int playerPosition = -1;

struct player
{
	char name[20];
	int guesses;
};
struct player leaders[5];


int getLeaderboard() {

	FILE* file = NULL;
	char line[100];
	char pastName[20];
	int pastGuesses;

	file = fopen("leaders.txt", "r");

	if (file == NULL) {
		return 0;
	}

	int i = 0;
	while (fgets(line, sizeof(line), file))
	{
		sscanf(line, "%s made %d guesses", pastName, &pastGuesses);
		strcpy(leaders[i].name, pastName);
		leaders[i].guesses = pastGuesses;

		i++;
	}
	return 1;
}

void updateLeaderboard()
{
	for (int i = 0; i < 5; i++)
	{

		if (num_guesses < leaders[i].guesses)
		{
			for (int j = 4; j > i; j--)
			{
				strcpy(leaders[j].name, leaders[j - 1].name);
				leaders[j].guesses = leaders[j - 1].guesses;
			}
			strcpy(leaders[i].name, name);
			leaders[i].guesses = num_guesses;
			break;
		}
		else if (leaders[i].guesses == 0)
		{
			strcpy(leaders[i].name, name);
			leaders[i].guesses = num_guesses;
			break;
		}
	}
}

void displayLeaderboard()
{
	printf("\nHere are the current leaders: \n");
	for (int i = 0; i < 5; i++)
	{
		if (leaders[i].guesses != 0)
			printf("%s made %d guesses\n", leaders[i].name, leaders[i].guesses);
	}
	printf("\n");
}

int writeLeaderboard()
{
	FILE* file = NULL;

	file = fopen("leaders.txt", "w");
	if (file == NULL) {
		printf("Error opening file\n");
		return 0;
	}

	for (int i = 0; i < 5; i++)
	{
		if(leaders[i].guesses != 0)
			fprintf(file, "%s made %d guesses\n", leaders[i].name, leaders[i].guesses);
	}
	fclose(file);
}


void PlayGuessingGame()//function to structure the whole game and print whether the user is correct or not
{
	printf("%.3f is the square root of what number? ", square_root);
	scanf("%d", &guess_num);
	num_guesses = 1;
	while (guess_num != random_num)
	{
		num_guesses++;
		if (guess_num > random_num)
		{
			printf("too high, guess again: ");
		}
		else
		{
			printf("too low, guess again: ");
		}
		scanf("%d", &guess_num);
	}
	printf("you got it baby!\n");
	printf("You made %d guesses. \n", num_guesses);

}


int main()
{
	//initialize leaderboard
	for (int i = 0; i < 5; i++)
	{
		strcpy(leaders[i].name, "");
		leaders[i].guesses = 0;
	}

	//search for existing leaderboard
	if (getLeaderboard()) {
		displayLeaderboard();
	}
	else {
		printf("No existing leaderboard\n");
	}

	printf("Welcome! Press q to quit or any key to continue: ");
	scanf("%s", &c);
	while (getchar() != '\n');

	while (c != 'q')
	{
		printf("Please enter your name to start: ");
		scanf("%s", name);

		//generate number to guess
		srand(time(NULL)); //to change the value of rand, otherwise rand was generating the same number
		random_num = rand() % 91 + 10;
		square_root = sqrt(random_num);

		PlayGuessingGame();
		updateLeaderboard();
		displayLeaderboard();

		printf("Press q to quit or any key to continue: ");
		scanf("%s", &c);

	}
	writeLeaderboard();
	printf("Bye Bye !");

}
