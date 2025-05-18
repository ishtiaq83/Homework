#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char training_results[8] = {'-', '-', '-', '-', '-', '-', '-', '-'};

// Clear input buffer
void clear_input() {
    while (getchar() != '\n');
}

// Check if a stage is unlocked based on prior completion
int is_stage_unlocked(int stage) {
    if (stage == 1) return 1;
    if (stage == 2 && training_results[0] == 'P') return 1;
    if (stage >= 3 && training_results[0] == 'P' && training_results[1] == 'P') return 1;
    return 0;
}

// Handle evaluation input and result recording
void evaluate_stage(int stage) {
    if (training_results[stage - 1] == 'P') {
        printf("Stage %d already completed.\n", stage);
        return;
    }

    char input;
    printf("Would you like to enter the evaluation result? (Y/N): ");
    scanf(" %c", &input);
    clear_input();

    if (toupper(input) == 'Y') {
        printf("Did you complete the training and pass the certification? (Y/N): ");
        scanf(" %c", &input);
        clear_input();

        if (toupper(input) == 'Y') {
            training_results[stage - 1] = 'P';
            printf("Stage %d marked as Passed.\n", stage);
        } else {
            training_results[stage - 1] = 'F';
            printf("Stage %d marked as Failed.\n", stage);
        }
    }
}

// Handles training stage selection and evaluation
void handle_training_menu() {
    const char *training_menu[8] = {
        "1. Physical Strength & Knowledge",
        "2. Self-Management & Teamwork",
        "3. Language & Pronunciation",
        "4. Vocal",
        "5. Dance",
        "6. Visual & Image",
        "7. Acting & Stage Performance",
        "8. Fan Communication"
    };

    while (1) {
        printf("\n=== Training Menu ===\n");
        for (int i = 0; i < 8; i++) {
            printf("%s [%c]\n", training_menu[i], training_results[i]);
        }
        printf("Enter stage number to evaluate (0/Q to return): ");

        char input[10];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (input[0] == '0' || toupper(input[0]) == 'Q') {
            break;
        }

        int stage = atoi(input);
        if (stage >= 1 && stage <= 8) {
            if (is_stage_unlocked(stage)) {
                evaluate_stage(stage);
            } else {
                printf("Stage %d is locked. Complete the required prior stages first.\n", stage);
            }
        } else {
            printf("Invalid selection.\n");
        }
    }
}

void audition_menu() {
    printf("\n--- Audition Management ---\n");
    printf("This feature is not implemented yet.\n");
    printf("Press Enter to return to main menu...\n");
    getchar();
}

void debut_menu() {
    printf("\n--- Debut Menu ---\n");
    printf("This feature is not implemented yet.\n");
    printf("Press Enter to return to main menu...\n");
    getchar();
}

// Main menu handler
void main_menu() {
    const char *main_menu_options[3] = {
        "1. Audition Management",
        "2. Training",
        "3. Debut"
    };

    while (1) {
        printf("\n=== Main Menu ===\n");
        for (int i = 0; i < 3; i++) {
            printf("%s\n", main_menu_options[i]);
        }
        printf("Enter your choice (0/Q to quit): ");

        char input[10];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (input[0] == '0' || toupper(input[0]) == 'Q') {
            printf("Exiting the program...\n");
            break;
        }

        switch (input[0]) {
            case '1':
                audition_menu();
                break;
            case '2':
                handle_training_menu();
                break;
            case '3':
                debut_menu();
                break;
            default:
                printf("Invalid input. Please try again.\n");
                break;
        }
    }
}

int main() {
    main_menu();
    return 0;
}
