#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRAINEES 20
#define MAX_MENTORS 8
#define NAME_LEN 32

typedef struct {
    char codename[NAME_LEN];
    int ascii_signature; // Unique ID based on ASCII sum
    int potential_score;
} Trainee;

typedef struct {
    int mentor_code; // 1–8
    char alias[NAME_LEN];
    int linked_trainee_signature;
} Mentor;

int generateAsciiSignature(const char *name) {
    int sum = 0;
    for (int i = 0; name[i] != '\0'; ++i) {
        sum += (int)name[i];
    }
    return sum;
}

int generatePotentialScore() {
    return 100 + rand() % 901; // Score range: 100–1000
}

void initializeTrainees(Trainee crew[], int *count) {
    const char *roster[] = {"Nova", "Orion", "Lyra", "Vega", "Drake", "Zara", "Echo", "Atlas", "Mira", "Jett"};
    int total = sizeof(roster) / sizeof(roster[0]);
    *count = total;

    for (int i = 0; i < total; ++i) {
        strncpy(crew[i].codename, roster[i], NAME_LEN);
        crew[i].ascii_signature = generateAsciiSignature(crew[i].codename);
        crew[i].potential_score = generatePotentialScore();
    }
}

void collectMentorData(Mentor guides[], int *count) {
    *count = MAX_MENTORS;
    for (int i = 0; i < MAX_MENTORS; ++i) {
        guides[i].mentor_code = i + 1;
        printf("Enter alias for Mentor-%d: ", i + 1);
        scanf("%s", guides[i].alias);
        guides[i].linked_trainee_signature = -1;
    }
}

void executeMentorLinking(Trainee crew[], int crewSize, Mentor guides[], int guideCount, int enforceOneToOne) {
    int occupied[MAX_MENTORS] = {0};

    for (int i = 0; i < crewSize; ++i) {
        int index = crew[i].ascii_signature % guideCount;

        if (enforceOneToOne) {
            int start = index;
            while (occupied[index]) {
                index = (index + 1) % guideCount;
                if (index == start) {
                    printf("[!] No available mentor for trainee %s\n", crew[i].codename);
                    index = -1;
                    break;
                }
            }
            if (index == -1) continue;
        }

        guides[index].linked_trainee_signature = crew[i].ascii_signature;
        occupied[index] = 1;
    }
}

void displayAssignments(Trainee crew[], int crewSize, Mentor guides[], int guideCount) {
    printf("\n--- Mentorship Allocation Overview ---\n");
    for (int i = 0; i < crewSize; ++i) {
        int mentorFound = -1;
        for (int j = 0; j < guideCount; ++j) {
            if (guides[j].linked_trainee_signature == crew[i].ascii_signature) {
                mentorFound = j;
                break;
            }
        }
        if (mentorFound != -1) {
            printf("[Crew %s] (ID: %d) → [Mentor %s] (Code: %d)\n",
                   crew[i].codename,
                   crew[i].ascii_signature,
                   guides[mentorFound].alias,
                   guides[mentorFound].mentor_code);
        } else {
            printf("[Crew %s] (ID: %d) → No Mentor Assigned\n",
                   crew[i].codename, crew[i].ascii_signature);
        }
    }
}

void mentoringSystemMenu() {
    Trainee crew[MAX_TRAINEES];
    Mentor guides[MAX_MENTORS];
    int crewCount = 0, guideCount = 0;

    srand((unsigned int)time(NULL));
    initializeTrainees(crew, &crewCount);
    collectMentorData(guides, &guideCount);
    executeMentorLinking(crew, crewCount, guides, guideCount, 1);
    displayAssignments(crew, crewCount, guides, guideCount);
}

int main() {
    int selection;
    do {
        printf("\n=== Millieway Trainee Support Console ===\n");
        printf("1. Initiate Mentorship Protocol\n");
        printf("0. Shutdown\n");
        printf("Input Command: ");
        scanf("%d", &selection);

        switch (selection) {
            case 1:
                mentoringSystemMenu();
                break;
            case 0:
                printf("Terminating program...\n");
                break;
            default:
                printf("Invalid selection. Please retry.\n");
        }
    } while (selection != 0);

    return 0;
}
