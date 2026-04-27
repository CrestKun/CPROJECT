#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int i;
    char userName[50];
    char questions[][100] = {
        "What does printf() do in C?",
        "Which symbol is used to end a statement in C?",
        "Which header file is required for printf() and scanf()?",
        "Which data type is used to store a single character?",
        "What is the correct way to declare an integer variable?",
        "Which loop is guaranteed to run at least once?",
        "Which operator is used for comparison?",
        "Which function is used to read input from the user?",
        "What is the starting index of an array in C?",
        "What symbol is used for multiplication?"
    };

    char options[][100] = {
        "A. Reads input from the user\nB. Reads output from the user\nC.Stores a variable\nD. Opens a file",
        "A.:\nB. ,\nC. ;\nD. .",
        "A. stdlib.h\nB. stdio.h\nC. string.h\nD. math.h",
        "A. int\nB. float\nC. char\nD. double",
        "A. int number;\nB. number int;\nC. integer number;\nD. num = int;",
        "A. for loop\nB. while loop\nC. do-while loop\nD. if statement",
        "A. =\nB. ==\nC. :=\nD. !=",
        "A. printf()\nB. get()\nC. scanf()\nD. input()",
        "A. 1\nB. -1\nC. 0\nD. 10",
        "A. *\nB. x\nC. #\nD. %\n"
    };

    char answerKey[] = {'B', 'C', 'B', 'C', 'A', 'C', 'B', 'C', 'C', 'A'};
    int questionCount = sizeof(questions) / sizeof(questions[0]);
    int score = 0;
    int totalScore = 0;
    int menuChoice;
    char fileName[60];

    // Loading screen & welcome message
    SetConsoleTextAttribute(hConsole, 2);
    printf("Loading");
    for(i = 0; i < 3; i++) {
    Beep(5500, 100);
    printf("."); 
    sleep(1); }
    printf("\n");
    SetConsoleTextAttribute(hConsole, 1);
    printf("===============");
    SetConsoleTextAttribute(hConsole, 11);
    printf("==============\n");
    SetConsoleTextAttribute(hConsole, 6);
    printf("||  WELCOME TO QUIZ GAME!  ||\n");
    SetConsoleTextAttribute(hConsole, 14);
    printf("||       (^__^)<3          ||\n");
    SetConsoleTextAttribute(hConsole, 4);
    printf("===============");
    SetConsoleTextAttribute(hConsole, 12);
    printf("==============\n");

    // Ask for user name
    SetConsoleTextAttribute(hConsole, 7);
    printf("Enter your username: ");
    scanf(" %[^\n]", userName);
    SetConsoleTextAttribute(hConsole, 4);
    printf("(CAUTION: Remember your username!)");

    // File for storing total score
    snprintf(fileName, sizeof(fileName), "%s.txt", userName);
    FILE *file = fopen(fileName, "r");
    if(file != NULL) { fscanf(file, "%d", &totalScore); fclose(file); }

    do {
        // Display Menu
        SetConsoleTextAttribute(hConsole, 2);
        printf("\n*** QUIZ GAME MENU ***\n");
        SetConsoleTextAttribute(hConsole, 6); 
        printf("1. Start Quiz\n");
        SetConsoleTextAttribute(hConsole, 9); 
        printf("2. Score\n");
        SetConsoleTextAttribute(hConsole, 5); 
        printf("3. About Game\n");
        SetConsoleTextAttribute(hConsole, 4); 
        printf("4. Exit\n");
        SetConsoleTextAttribute(hConsole, 7); 
        printf("Enter your choice: ");
        scanf("%d", &menuChoice);

        switch(menuChoice) {
            case 1: {
                char guess;
                score = 0; // reset current game score

                // === START COLORIZED QUIZ ===
                for(int i = 0; i < questionCount; i++){
                    // Question in white
                    SetConsoleTextAttribute(hConsole, 7);
                    printf("\n%s\n", questions[i]);

                    // Print each choice in its color
                    char *token;
                    char optionCopy[100];
                    strcpy(optionCopy, options[i]); // make a copy

                    token = strtok(optionCopy, "\n");
                    int count = 0;
                    while(token != NULL){
                        if(count == 0) SetConsoleTextAttribute(hConsole, 14); // A - Yellow
                        else if(count == 1) SetConsoleTextAttribute(hConsole, 9); // B - Blue
                        else if(count == 2) SetConsoleTextAttribute(hConsole, 12); // C - Orange
                        else if(count == 3) SetConsoleTextAttribute(hConsole, 2); // D - Green

                        printf("%s\n", token);
                        token = strtok(NULL, "\n");
                        count++;
                    }

                    // Reset for input
                    SetConsoleTextAttribute(hConsole, 7);
                    printf("Enter your choice: ");
                    scanf(" %c", &guess);
                    guess = toupper(guess);

                    // Feedback
                    if(guess == answerKey[i]){
                        SetConsoleTextAttribute(hConsole, 2); // green
                        printf("CORRECT!\n");
                        score++;
                    } else {
                        SetConsoleTextAttribute(hConsole, 4); // red
                        printf("WRONG!\n");
                    }
                    SetConsoleTextAttribute(hConsole, 7); // reset
                }
                // === END COLORIZED QUIZ ===

                printf("\nYou scored %d points in this game.\n", score);
                totalScore += score;

                file = fopen(fileName, "w");
                if(file != NULL) { fprintf(file, "%d", totalScore); fclose(file); }
                break;
            }

            case 2:
                printf("\n%s, your total accumulated score: %d points\n", userName, totalScore);
                break;

            case 3:
                SetConsoleTextAttribute(hConsole, 2);
                printf("\nAbout Game:\n");
                SetConsoleTextAttribute(hConsole, 8);
                printf("This is a simple quiz game created using C language. Answer the questions by typing the letter of your choice. Credits to the rightful owner (Brocode on yt) of the code I used as a basis upon making this program.\n");
                SetConsoleTextAttribute(hConsole, 7);
                break;

            case 4:
                SetConsoleTextAttribute(hConsole, 4);
                printf("Exiting the game");
                for(i = 0; i < 3; i++) {
                Beep(5500, 100);
                printf(".");
                sleep(1);
                }
                SetConsoleTextAttribute(hConsole, 12);
                printf("Goodbye %s!\n", userName);
                SetConsoleTextAttribute(hConsole, 7);
                break;

            default:
                printf("Invalid choice! Please select 1-4.\n");
        }

    } while(menuChoice != 4);

    return 0;
}