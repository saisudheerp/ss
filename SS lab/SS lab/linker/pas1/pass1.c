#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char line[100];
char csname[100];
char extsym[100];
char csaddress[100];
char startingaddress[100];
char length[100];
char addresssum[100];
char nextcsaddress[100];

int isEndLine() {
    if (line[0] == 'E') {
        return 1;
    }
    return 0;
}

int isHeadLine() {
    if (line[0] == 'H') {
        return 1;
    }
    return 0;
}

void getcsname() {
    char linebackup[100];
    strcpy(linebackup, line);
    char *token = strtok(linebackup, " ");
    token = strtok(NULL, " ");
    strcpy(csname, token);
}

void getlength() {
    char linebackup[100];
    strcpy(linebackup, line);
    char *token = strtok(linebackup, " ");
    token = strtok(NULL, " ");
    token = strtok(NULL, " ");
    token = strtok(NULL, " ");
    strcpy(length, token);
}

void getcsaddress() {
    char linebackup[100];
    strcpy(linebackup, line);
    char *token = strtok(linebackup, " ");
    token = strtok(NULL, " ");
    token = strtok(NULL, " ");
    strcpy(csaddress, token);
}

int isDefine() {
    if (line[0] == 'D') {
        return 1;
    }
    return 0;
}

int main() {
    printf("Enter starting address\n");
    scanf("%s", startingaddress);

    FILE *inputFP = fopen("input.txt", "r");
    FILE *outputFP = fopen("output.txt", "w");

    while (!feof(inputFP)) {
        fscanf(inputFP, "%[^\n]%*c", line);

        if (isEndLine()) {
            strcpy(startingaddress, nextcsaddress);
        }

        if (isHeadLine()) {
            getcsaddress();
            getcsname();
            getlength();

            char temp[100];
            sprintf(temp, "%d", atoi(startingaddress) + atoi(csaddress));
            strcpy(addresssum, temp);
            sprintf(temp, "%d", atoi(addresssum) + atoi(length));
            strcpy(nextcsaddress, temp);

            printf("%s \t\t %s %s\n", csname, addresssum, length);
            fprintf(outputFP, "%s \t\t %s %s\n", csname, addresssum, length);
        }

        if (isDefine()) {
            char linebackup[100];
            strcpy(linebackup, line);

            char *token = strtok(linebackup, " ");

            while (token != NULL) {
                token = strtok(NULL, " ");

                if (token != NULL) {
                    printf("**\t %s \t", token);
                    token = strtok(NULL, " ");
                    char temp[100];
                    sprintf(temp, "%d", atoi(addresssum) + atoi(token));
                    printf(" %s\t0\n", temp);
                    fprintf(outputFP, "**\t %s \t %s\t0\n", token, temp);
                }
            }
        }
    }
    fclose(outputFP);
    fclose(inputFP);
    return 0;
}
