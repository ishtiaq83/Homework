#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JUDGES 100
#define MAX_INPUT 512
#define REQUIRED_FIELDS 7

int count_commas(const char *str) {
    int count = 0;
    while (*str) {
        if (*str == ',') count++;
        str++;
    }
    return count;
}

void trim_newline(char *str) {
    char *p = strchr(str, '\n');
    if (p) *p = '\0';
}

void display_judge(int index, const char *data) {
    char buffer[MAX_INPUT];
    strcpy(buffer, data);
    char *token = strtok(buffer, ",");
    const char *fields[] = {"Name", "Gender", "Affiliation", "Title", "Expertise", "Email", "Phone"};
    
    printf("[Judge %d]\n", index + 1);
    int i = 0;
    while (token != NULL && i < REQUIRED_FIELDS) {
        trim_newline(token);
        printf("%s: %s\n", fields[i], token);
        token = strtok(NULL, ",");
        i++;
    }
    printf("-----------------------------------\n");
}

int main() {
    char judges_array[MAX_JUDGES][MAX_INPUT];
    char project[100];
    int total_judges = 0;
    int selected_members = 4;  

    printf("####################################\n");
    printf("#      Judge List Data Entry      #\n");
    printf("####################################\n");

    printf("Participating Project: ");
    fgets(project, sizeof(project), stdin);
    trim_newline(project);

    printf("Total Number of Judges: ");
    scanf("%d", &total_judges);
    getchar(); 

    printf("Number of Selected Members: %d\n", selected_members);
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Starting to input information for %d judges.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    int entered = 0;
    while (entered < total_judges) {
        printf("Judge %d: ", entered + 1);
        fgets(judges_array[entered], MAX_INPUT, stdin);
        trim_newline(judges_array[entered]);

        if (count_commas(judges_array[entered]) != REQUIRED_FIELDS - 1) {
            printf("The input items are incorrect. Please enter them again.\n");
            continue;
        }

        entered++;
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Judge information entry is complete.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    char view_choice;
    printf("\"Should we check the judge information?\" (Y/N): ");
    scanf(" %c", &view_choice);

    if (view_choice == 'Y') {
        printf("\n[%s] Should we check the judge information? %c\n", project, view_choice);
        printf("####################################\n");
        printf("#        Display Judge Data        #\n");
        printf("####################################\n");

        for (int i = 0; i < total_judges; i++) {
            display_judge(i, judges_array[i]);
        }
    } else {
        printf("Program terminated.\n");
    }

    return 0;
}
