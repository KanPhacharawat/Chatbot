#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

typedef struct {
    char* question[50];
    char* response[50];
}Keyword;


int main() {
    FILE *question, *response, *keywordF;
    char line[100];
    char lineK[100];
    int lineNumber = 0;
    int lineNum, innerLineNum = 0;
    bool dict, yesNo, keyword, reflect = false;

    question = fopen("data/canned_question.txt", "r");
    response = fopen("data/canned_response.txt", "r");
    keywordF = fopen("data/keyword_response.tsv", "r");

    char input[100];
    Keyword keywordData[50];
    int keywordCount = 0;


    srand(time(NULL));

    while (fgets(lineK, sizeof(lineK), keywordF) != NULL) {
        char* token = strtok(lineK, " ");

        if (token != NULL) {
            strcpy(keywordData[keywordCount].question, token);

            char response[256] = "";
            while ((token = strtok(NULL, " ")) != NULL) {
                strcat(response, token);
                strcat(response, " ");
            }

            if (strlen(response) > 0) {
                response[strlen(response) - 1] = '\0';
                strcpy(keywordData[keywordCount].response, response);
            }
        }
        keywordCount++;
    }

    while (1) {
        printf("You >> ");
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';

        if (strcasecmp(input, "bye") == 0) {
            printf("Goodbye.\n");
            break;
        } else {
            rewind(question);
            rewind(response);

            while (fgets(line, sizeof(line), question)) {
                line[strcspn(line, "\n")] = '\0';

                if (strcasecmp(input, line) == 0) {
                    while (fgets(line, sizeof(line), response)) {
                        if(innerLineNum == lineNum){
                            dict = true;
                           printf("Bot >> %s\n", line);
                           break;
                        }
                        else {
                            innerLineNum++;
                        }

                    }
                    break;
                }
                else {
                    ++lineNum;
                }
                dict = false;
            }
            innerLineNum = 0;
            lineNum = 0;

            if(!dict){
                bool isYesNo = false;
                char *verbs[] = {"Do", "Are", "Have", "Will", "Would", "Should", "Can", "Could"};

                for(int i = 0; i < 8; ++i){
                    if(strstr(input, verbs[i]) != NULL){
                        isYesNo = true;
                        break;
                    }
                }

                if(isYesNo){
                    yesNo = true;
                    bool random = rand() % 2;
                    char *answerYes[] = {"Yes!", "Sure!", "Yep!", "Maybe", "That's right!"};
                    char *answerNo[] = {"No", "Nope", "Wrong"};

                    if(random){ int randomAnswer = rand() % 5; printf("Bot >> %s\n", answerYes[randomAnswer]); }
                    else { int randomAnswer = rand() % 3; printf("Bot >> %s\n", answerNo[randomAnswer]); }
                }
                else {
                    bool isKeyword = false;
                    int numArr = 0;
                    for(int i = 0; i < keywordCount; ++i){
                        if(strstr(input, keywordData[i].question)){
                            isKeyword = true;
                            numArr = i;
                        }
                    }

                    if(isKeyword) {
                        keyword = true;
                        printf("Bot >> %s\n", keywordData[numArr].response);
                    }
                    else {

                    }
                }
            }
        }
    }

    fclose(question);
    fclose(response);
    fclose(keywordF);

    return 0;
}

/*
char* give_up_response[] = {
                                  "I heard you!",
                                  "So, you are talking to me.",
                                  "Continue, I'm listening.",
                                  "Very interesting conversation.",
                                  "Tell me more..."
                              };
                              int randomGiveUp = rand() % 5;

                              printf("Bot >> %s\n", give_up_response[randomGiveUp]);
*/
