#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_MEMBERS 5
#define TEST_CATEGORIES 7
#define MAX_NAME_LEN 30
#define MAX_NICKNAME_LEN 20

char training_results[8] = {'-', '-', '-', '-', '-', '-', '-', '-'};
char *milliways_members[MAX_MEMBERS] = {"Lee Goeun", "Kim Woncheol", "Park Youngjin", "Yoon Hyekyung", "Arthur Dent"};
char *nicknames[MAX_MEMBERS] = {"Goeun", "Woncheol", "Youngjin", "Hyekyung", "Arthur"};
float health_scores[MAX_MEMBERS][TEST_CATEGORIES];

void clear_input() {
    while (getchar() != '\n');
}

int is_stage_unlocked(int stage) {
    if (stage == 1) return 1;
    if (stage == 2 && training_results[0] == 'P') return 1;
    if (stage >= 3 && training_results[0] == 'P' && training_results[1] == 'P') return 1;
    return 0;
}

void evaluate_stage(int stage) {
    if (training_results[stage - 1] == 'P') {
        printf("Stage %d has already been completed.\n", stage);
        return;
    }

    char input;
    printf("Evaluate this stage? (Y/N): ");
    scanf(" %c", &input);
    clear_input();

    if (toupper(input) == 'Y') {
        printf("Was the stage passed? (Y/N): ");
        scanf(" %c", &input);
        clear_input();

        if (toupper(input) == 'Y') {
            training_results[stage - 1] = 'P';
            printf("Stage %d marked as PASSED.\n", stage);
        } else {
            training_results[stage - 1] = 'F';
            printf("Stage %d marked as FAILED.\n", stage);
        }
    }
}

void setHealth() {
    printf("\n-- Enter Fitness Data --\n");
    printf("Enter nickname of member: ");
    char input[MAX_NICKNAME_LEN];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    int found = -1;
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcasecmp(input, nicknames[i]) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Nickname not found.\n");
        return;
    }

    printf("Enter data for %s (%s):\n", milliways_members[found], nicknames[found]);
    printf("Format: MileRun, Sprint, Pushups, Squats, ArmPushups, Swim, Weightlift\n> ");

    char input_data[200];
    fgets(input_data, sizeof(input_data), stdin);

    char *token = strtok(input_data, ",");
    int j = 0;
    while (token != NULL && j < TEST_CATEGORIES) {
        health_scores[found][j++] = atof(token);
        token = strtok(NULL, ",");
    }
}

void getHealth() {
    printf("\n-- View Fitness Data --\n");
    printf("Enter nickname (or 'ALL' for all members): ");

    char input[20];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    if (strcasecmp(input, "ALL") == 0) {
        for (int i = 0; i < MAX_MEMBERS; i++) {
            printf("\n%s (%s):\n", milliways_members[i], nicknames[i]);
            for (int j = 0; j < TEST_CATEGORIES; j++) {
                printf("Test %d: %.2f\n", j + 1, health_scores[i][j]);
            }
        }
    } else {
        int found = 0;
        for (int i = 0; i < MAX_MEMBERS; i++) {
            if (strcasecmp(input, nicknames[i]) == 0) {
                found = 1;
                printf("\n%s (%s):\n", milliways_members[i], nicknames[i]);
                for (int j = 0; j < TEST_CATEGORIES; j++) {
                    printf("Test %d: %.2f\n", j + 1, health_scores[i][j]);
                }
                break;
            }
        }
        if (!found) {
            printf("Nickname not found.\n");
        }
    }
}

void main_menu() {
    while (1) {
        printf("\n==== Milliways Training System ====\n");
        printf("1. Audition Management\n");
        printf("2. Training\n");
        printf("3. Debut\n");
        printf("0. Exit\n> ");

        char input[10];
        fgets(input, sizeof(input), stdin);

        if (input[0] == '0' || toupper(input[0]) == 'Q') break;

        switch (input[0]) {
            case '2': {
                printf("\n-- Training Menu --\n");
                for (int i = 0; i < 8; i++) {
                    printf("%d. Training Stage %d [%c]\n", i + 1, i + 1, training_results[i]);
                }
                printf("Select stage (1-8): ");
                int stage;
                scanf("%d", &stage);
                clear_input();

                if (stage >= 1 && stage <= 8) {
                    if (!is_stage_unlocked(stage)) {
                        printf("Stage %d is locked. Complete previous required stages first.\n", stage);
                    } else if (stage == 1) {
                        printf("A. Enter Fitness Data\nB. View Fitness Data\nSelect A or B: ");
                        char sub;
                        scanf(" %c", &sub);
                        clear_input();
                        if (toupper(sub) == 'A') setHealth();
                        else if (toupper(sub) == 'B') getHealth();
                        else printf("Invalid option.\n");
                    } else {
                        evaluate_stage(stage);
                    }
                }
                break;
            }
            case '1':
            case '3':
                printf("Feature under development.\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    }
}

int main() {
    main_menu();
    return 0;
}
