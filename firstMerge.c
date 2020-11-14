#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void PrintBoard(char board[30][80]);
void UpdateBoard(char words[],char board[30][80]);
void MoveWords(char board[30][80]);
void generateWord(FILE *fileName, char* randomWords, int *w);

int main(){
	char playOrAdd;
	char userAddWord[10];
	char board[30][80];
	char userWants;
	char tempWordVar[50];
	int d = 0;
	for(int w = 0; w < 30; w++){
		for(int i = 0; i < 80; i++){
			board[w][i] = ' ';
		}
	}
	FILE *fp;
	printf("Hello, this is a typing game. You will need to type the words as they " 
	"appear.\nWould you like to play or add a word?\n(Type ‘p’ for play or ‘a’ to add words)\n");
    scanf(" %c", &playOrAdd);
    srand(time(NULL));
	printf("Enter p to play or anything else to exit\n");
	scanf(" %c", &userWants);
	while(playOrAdd == 'a'){
        FILE *fp = fopen("wordList.txt", "a+");
        printf("Type a word that you want to add(one word, no spaces)\n");
		scanf(" %s",userAddWord);
		fprintf(fp, "\n");
		fprintf(fp, "%s", userAddWord);  //make word go to file
		printf("Your word has been added.\n Would you like to add another word? (Type "
        "'p' or 'a')\n");
		scanf(" %c", &playOrAdd);
		fclose(fp);
	}
	
	while(userWants == 'p'){
		generateWord(fp, &tempWordVar, &d);
		UpdateBoard(tempWordVar, board);
		printf("Enter p to keep playing\n");
		scanf(" %c", &userWants);
	}	
}

void PrintBoard(char board[30][80]){
	printf(" ");
	for(int j = 0; j < 8; j++)
		printf("----------");
	printf("\n");
	for(int i = 0; i < 30; i++){
		printf("|");
		for(int w = 0; w < 80; w++){
			printf("%c", board[i][w]);
			if(w == 79)
				printf("|\n");
		}
	}
}

void UpdateBoard(char words[],char board[30][80]){
	int length = 0;
	int i = 0;
	while(words[i] != '\0'){
	    length++;
	    i++;
	}
	int temp = rand() % (78 - length); //need to add a strlen() function to make it the proper size from the end of the board
	MoveWords(board);
	for(int i = 0; i < length - 2; i++){
		board[0][temp+i] = words[i];
	}
	PrintBoard(board);
}

void MoveWords(char board[30][80]){
	for(int i = 29; i >= 0; i--){
		for(int j = 0; j < 79; j++){
 			if(board[i][j] != ' '){
				if(i == 29){
					printf("Game Over"); //ends game if the word is on the bottom line
					exit(0);
				}
				else{
					board[i+1][j] = board[i][j]; //moves the word down
					board[i][j] = ' ';  //resets the words previous spot to empty
				}
			}
		}
	}
}

void generateWord(FILE *fileName, char* randomWords, int *w){
    srand(time(NULL));
    char thrownLine[50]; //Stores the previous lines so that they do not get put onto the board
    int randomLine = 0;
    int usedWords[1000];
    randomLine = (rand() % 999) + 1; //Generates which line the word will be at in the file
    fileName = fopen("wordList.txt", "r");
    for(int j = 0; j < 1000; j++){
        if(usedWords[j] == randomLine){
            randomLine = (rand() % 999) + 1;
        }
    }
    //The loop puts the values of the preceding lines into the thrownLine so it does not mix with the actual value
    for(int i = 1; i < randomLine; i++){
        fgets(thrownLine, randomLine, fileName);
    }
    usedWords[*w] = randomLine;
    w++;
    fgets(randomWords, randomLine, fileName);
    fclose(fileName);
}
