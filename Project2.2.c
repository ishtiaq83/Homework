#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_MEMBERS 5
#define TEST_CATEGORIES 7
#define MAX_NAME_LEN 30
#define MAX_NICKNAME_LEN 20

char training_results[8] = {'-', '-', '-', '-', '-', '-', '-', '-'};

char member_names[MAX_MEMBERS][MAX_NAME_LEN] = {
    "Lee Goeun", "Kim Woncheol", "Park Youngjin", "Yoon Hyekyung", "Arthur Dent"
};

char member_nicknames[MAX_MEMBERS][MAX_NICKNAME_LEN] = {
    "Goeun", "Woncheol", "Youngjin", "Hyekyung", "Arthur"
};

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

void setHealth() {
    printf("\n--- Enter Fitness Data ---\n");
    printf("Format: Nickname,1mile,sprint,pushups,squats,armstrength,swimming,weightlifting\n");

    char input[200];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    char *token = strtok(input, ",");
    if (!token) {
        printf("Invalid input.\n");
        return;
    }

    int member_index = -1;
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(member_nicknames[i], token) == 0) {
            member_index = i;
            break;
        }
    }

    if (member_index == -1) {
        printf("Nickname not found.\n");
        return;
    }

    for (int i = 0; i < TEST_CATEGORIES; i++) {
        token = strtok(NULL, ",");
        if (!token) {
            printf("Not enough fitness test values.\n");
            return;
        }
        health_scores[member_index][i] = atof(token);
    }

    printf("Fitness data for %s saved.\n", member_nicknames[member_index]);
}

void getHealth() {
    printf("\n--- View Fitness Data ---\n");
    printf("1. View all data\n2. View one member\n3. View one test for a member\nSelect option: ");

    int option;
    scanf("%d", &option);
    clear_input();

    const char* test_names[TEST_CATEGORIES] = {
        "1-Mile Running", "Speed Sprint", "Push-ups", "Squats",
        "Arm Strength", "Swimming", "Weightlifting"
    };

    if (option == 1) {
        for (int i = 0; i < MAX_MEMBERS; i++) {
            printf("\nName: %s | Nickname: %s\n", member_names[i], member_nicknames[i]);
            for (int j = 0; j < TEST_CATEGORIES; j++) {
                printf("%s: %.2f\n", test_names[j], health_scores[i][j]);
            }
        }
    } else if (option == 2) {
        char nickname[MAX_NICKNAME_LEN];
        printf("Enter nickname: ");
        fgets(nickname, sizeof(nickname), stdin);
        nickname[strcspn(nickname, "\n")] = 0;

        int found = -1;
        for (int i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(member_nicknames[i], nickname) == 0) {
                found = i;
                break;
            }
        }

        if (found != -1) {
            printf("Name: %s | Nickname: %s\n", member_names[found], member_nicknames[found]);
            for (int j = 0; j < TEST_CATEGORIES; j++) {
                printf("%s: %.2f\n", test_names[j], health_scores[found][j]);
            }
        } else {
            printf("Member not found.\n");
        }
    } else if (option == 3) {
        char nickname[MAX_NICKNAME_LEN];
        int test_index;

        printf("Enter nickname: ");
        fgets(nickname, sizeof(nickname), stdin);
        nickname[strcspn(nickname, "\n")] = 0;

        printf("Select test (0-6):\n");
        for (int i = 0; i < TEST_CATEGORIES; i++)
            printf("%d. %s\n", i, test_names[i]);
        scanf("%d", &test_index);
        clear_input();

        if (test_index < 0 || test_index >= TEST_CATEGORIES) {
            printf("Invalid test index.\n");
            return;
        }

        int found = -1;
        for (int i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(member_nicknames[i], nickname) == 0) {
                found = i;
                break;
            }
        }

        if (found != -1) {
            printf("%s (%s) - %s: %.2f\n",
                member_names[found], member_nicknames[found],
                test_names[test_index], health_scores[found][test_index]);
        } else {
            printf("Member not found.\n");
        }
    } else {
        printf("Invalid option.\n");
    }
}

void physical_training_menu() {
    while (1) {
        printf("\n--- Physical Strength & Knowledge ---\n");
        printf("A. Enter Fitness Data\n");
        printf("B. View Fitness Data\n");
        printf("Q. Return\n");
        printf("Select option: ");

        char choice[10];
        fgets(choice, sizeof(choice), stdin);

        if (choice[0] == 'A' || choice[0] == 'a') {
            setHealth();
        } else if (choice[0] == 'B' || choice[0] == 'b') {
            getHealth();
        } else if (choice[0] == 'Q' || choice[0] == 'q') {
            break;
        } else {
            printf("Invalid selection.\n");
        }
    }
}

void main_menu() {
    while (1) {
        printf("\n=== Main Menu ===\n");
        printf("1. Training\nQ. Quit\nSelect: ");
        char input[10];
        fgets(input, sizeof(input), stdin);

        if (input[0] == '1') {
            if (is_stage_unlocked(1)) {
                physical_training_menu();
            } else {
                printf("Stage 1 is locked.\n");
            }
        } else if (toupper(input[0]) == 'Q') {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid selection.\n");
        }
    }
}

int main() {
    main_menu();
    return 0;
}
