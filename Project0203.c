#include <stdio.h>
#include <string.h>

#define MAX_MEMBERS 10
#define MAX_NAME_LENGTH 50
#define MAX_NICKNAME_LENGTH 50
#define DAYS_IN_WEEK 6
#define MAX_EXERCISES_PER_DAY 3
#define TOTAL_EXERCISES 11

// Data structures
typedef struct {
    char full_name[MAX_NAME_LENGTH];
    char nickname[MAX_NICKNAME_LENGTH];
} Member;

typedef struct {
    char daily[DAYS_IN_WEEK][MAX_EXERCISES_PER_DAY][MAX_NAME_LENGTH];
} WorkoutRoutine;

// Global data
Member members[MAX_MEMBERS] = {
    {"Lee Goeun", "Goeun"},
    {"Kim Woncheol", "Woncheol"},
    {"Park Youngjin", "Youngjin"},
    {"Yoon Hyekyung", "Hyekyung"},
    {"Arthur Dent", "Arthur"}
};
WorkoutRoutine routines[MAX_MEMBERS];
int member_count = 5;

const char *exercises[TOTAL_EXERCISES] = {
    "Cardio - Running", "Cardio - Cycling", "Cardio - Fast Walking",
    "Full-body - Push-ups", "Full-body - Squats",
    "Lower-body - Leg Press", "Lower-body - Leg Curl",
    "Upper-body - Pull-ups", "Upper-body - Chin-ups",
    "Core - Plank", "Core - Crunches"
};

// Utility functions
int find_member_index(const char *nickname) {
    for (int i = 0; i < member_count; i++) {
        if (strcmp(members[i].nickname, nickname) == 0) {
            return i;
        }
    }
    return -1;
}

void display_members() {
    printf("\nRegistered Members:\n");
    for (int i = 0; i < member_count; i++) {
        printf(" - %s (%s)\n", members[i].full_name, members[i].nickname);
    }
}

// Core features
void set_workout_routine() {
    char nickname[MAX_NICKNAME_LENGTH];
    int index;

    display_members();
    printf("\nEnter nickname to assign routine: ");
    fgets(nickname, MAX_NICKNAME_LENGTH, stdin);
    nickname[strcspn(nickname, "\n")] = 0;

    index = find_member_index(nickname);
    if (index == -1) {
        printf("❌ Member not found.\n");
        return;
    }

    int core_used = 0;
    for (int day = 0; day < DAYS_IN_WEEK; day++) {
        printf("\n--- Day %d Routine ---\n", day + 1);
        for (int i = 0; i < TOTAL_EXERCISES; i++) {
            printf("%2d. %s\n", i + 1, exercises[i]);
        }

        int cardio_ok = 0, strength_or_core_ok = 0;
        for (int ex = 0; ex < MAX_EXERCISES_PER_DAY;) {
            int choice;
            printf("Choose exercise %d: ", ex + 1);
            if (scanf("%d", &choice) != 1 || choice < 1 || choice > TOTAL_EXERCISES) {
                printf("Invalid input. Try again.\n");
                while (getchar() != '\n'); // flush buffer
                continue;
            }
            getchar(); // consume newline

            const char *selected = exercises[choice - 1];

            if (strstr(selected, "Core")) {
                if (core_used) {
                    printf("⚠️  Core exercise already used this week. Choose another.\n");
                    continue;
                }
                core_used = 1;
                strength_or_core_ok = 1;
            } else if (strstr(selected, "Cardio")) {
                cardio_ok = 1;
            } else if (strstr(selected, "Strength") || strstr(selected, "Full-body") || strstr(selected, "Upper-body") || strstr(selected, "Lower-body")) {
                strength_or_core_ok = 1;
            }

            strcpy(routines[index].daily[day][ex], selected);
            ex++;
        }

        if (!cardio_ok || !strength_or_core_ok) {
            printf("⚠️  Each day needs at least one cardio and one strength/core. Re-enter this day's plan.\n");
            day--; // repeat this day
        }
    }

    printf("✅ Workout routine set for %s (%s).\n", members[index].full_name, members[index].nickname);
}

void get_workout_routine() {
    char nickname[MAX_NICKNAME_LENGTH];
    int index;

    printf("\nEnter nickname to view routine: ");
    fgets(nickname, MAX_NICKNAME_LENGTH, stdin);
    nickname[strcspn(nickname, "\n")] = 0;

    index = find_member_index(nickname);
    if (index == -1) {
        printf("❌ Member not found.\n");
        return;
    }

    printf("\n📋 Weekly Routine for %s (%s):\n", members[index].full_name, members[index].nickname);
    for (int day = 0; day < DAYS_IN_WEEK; day++) {
        printf("Day %d:\n", day + 1);
        for (int ex = 0; ex < MAX_EXERCISES_PER_DAY; ex++) {
            printf(" - %s\n", routines[index].daily[day][ex]);
        }
    }
}

// Menu
void main_menu() {
    char option;

    do {
        printf("\n=== MAGRATHEA TRAINING STAGE 1 ===\n");
        printf("1. Display Member List\n");
        printf("2. Set Workout Routine\n");
        printf("3. View Workout Routine\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        option = getchar();
        getchar(); // consume newline

        switch (option) {
            case '1':
                display_members();
                break;
            case '2':
                set_workout_routine();
                break;
            case '3':
                get_workout_routine();
                break;
            case '0':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid selection.\n");
        }
    } while (option != '0');
}

int main() {
    main_menu();
    return 0;
}
