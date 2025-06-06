#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_JAMO 24
#define MAX_NAME 100
#define QUIZ_COUNT 5
#define MAX_RESULTS 100

typedef struct {
    char hangul[10];
    char eng[10];
    char pronunciation[30];
    char type; 
} Jamo;

typedef struct {
    char name[MAX_NAME];
    char type[3];
    int score;
    int attempts;
} Result;

Jamo jamos[MAX_JAMO] = {
    {"ㄱ", "g", "giyeok", 'C'}, {"ㄴ", "n", "nieun", 'C'}, {"ㄷ", "d", "digeut", 'C'},
    {"ㄹ", "r", "rieul", 'C'}, {"ㅁ", "m", "mieum", 'C'}, {"ㅂ", "b", "bieup", 'C'},
    {"ㅅ", "s", "siot", 'C'}, {"ㅇ", "ng", "ieung", 'C'}, {"ㅈ", "j", "jieut", 'C'},
    {"ㅊ", "ch", "chieut", 'C'}, {"ㅋ", "k", "kieuk", 'C'}, {"ㅌ", "t", "tieut", 'C'},
    {"ㅍ", "p", "pieup", 'C'}, {"ㅎ", "h", "hieut", 'C'},
    {"ㅏ", "a", "a", 'V'}, {"ㅑ", "ya", "ya", 'V'}, {"ㅓ", "eo", "eo", 'V'},
    {"ㅕ", "yeo", "yeo", 'V'}, {"ㅗ", "o", "o", 'V'}, {"ㅛ", "yo", "yo", 'V'},
    {"ㅜ", "u", "u", 'V'}, {"ㅠ", "yu", "yu", 'V'}, {"ㅡ", "eu", "eu", 'V'},
    {"ㅣ", "i", "i", 'V'}
};

Result results[MAX_RESULTS];
int resultCount = 0;

void shuffle(int *array, int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void playKor2EngGame(char *name, char jamoType) {
    int indices[MAX_JAMO], count = 0, score = 0;
    for (int i = 0; i < MAX_JAMO; i++) {
        if (jamos[i].type == jamoType) {
            indices[count++] = i;
        }
    }
    shuffle(indices, count);

    char input[50];
    for (int i = 0; i < QUIZ_COUNT; i++) {
        Jamo j = jamos[indices[i]];
        printf("\n[%d] %s: Enter English alphabet and pronunciation (e.g., g,giyeok): ", i + 1, j.hangul);
        scanf(" %[^\n]s", input);
        char *alpha = strtok(input, ",");
        char *pron = strtok(NULL, ",");
        if (alpha && pron && strcmp(alpha, j.eng) == 0 && strcmp(pron, j.pronunciation) == 0) {
            score += 10;
        }
    }

    strcpy(results[resultCount].name, name);
    strcpy(results[resultCount].type, "KE");
    results[resultCount].score = score;
    results[resultCount].attempts = 1;
    resultCount++;

    printf("\nYour score: %d/50\n", score);
}

void playEng2KorGame(char *name, char jamoType) {
    int indices[MAX_JAMO], count = 0, score = 0;
    for (int i = 0; i < MAX_JAMO; i++) {
        if (jamos[i].type == jamoType) {
            indices[count++] = i;
        }
    }
    shuffle(indices, count);

    char input[20];
    for (int i = 0; i < QUIZ_COUNT; i++) {
        Jamo j = jamos[indices[i]];
        printf("\n[%d] %s (%s): Enter Hangul: ", i + 1, j.eng, j.pronunciation);
        scanf(" %s", input);
        if (strcmp(input, j.hangul) == 0) {
            score += 10;
        }
    }

    strcpy(results[resultCount].name, name);
    strcpy(results[resultCount].type, "EK");
    results[resultCount].score = score;
    results[resultCount].attempts = 1;
    resultCount++;

    printf("\nYour score: %d/50\n", score);
}

void showResults() {
    printf("\n==== Results ====\n");
    for (int i = 0; i < resultCount; i++) {
        printf("Name: %s | Type: %s | Score: %d | Attempts: %d\n",
               results[i].name, results[i].type, results[i].score, results[i].attempts);
    }
    printf("=================\n");
}

void learnHangul() {
    char name[MAX_NAME];
    int choice, sub;
    printf("\nEnter trainee name: ");
    scanf(" %s", name);

    while (1) {
        printf("\n--- Hangul Jamo Learning ---\n");
        printf("1. Hangul to English\n");
        printf("2. English to Hangul\n");
        printf("3. View Results\n");
        printf("0. Back\n> ");
        scanf("%d", &choice);

        if (choice == 0) break;

        if (choice == 1 || choice == 2) {
            printf("\n1. Consonants\n2. Vowels\n> ");
            scanf("%d", &sub);
            char type = (sub == 1) ? 'C' : 'V';
            if (choice == 1) playKor2EngGame(name, type);
            else playEng2KorGame(name, type);
        } else if (choice == 3) {
            showResults();
        } else {
            printf("\nInvalid choice.\n");
        }
    }
}

int main() {
    srand(time(NULL));
    char mainChoice;
    while (1) {
        printf("\n[II. Training > 3. Language and Pronunciation Training]\n");
        printf("A. Korean Quiz (Not implemented here)\n");
        printf("B. Hangul Jamo Learning\n");
        printf("0. Exit\n> ");
        scanf(" %c", &mainChoice);

        if (mainChoice == '0') break;
        else if (mainChoice == 'B' || mainChoice == 'b') learnHangul();
        else printf("\nOnly option B is implemented in this module.\n");
    }
    return 0;
}
