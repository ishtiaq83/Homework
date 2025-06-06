#include <stdio.h>
#include <stdlib.h>

#define MAX 6
#define MAX_LEN 100

char candidate01[MAX_LEN], candidate02[MAX_LEN], candidate03[MAX_LEN],
     candidate04[MAX_LEN], candidate05[MAX_LEN], candidate06[MAX_LEN];

char *member_info[MAX] = {candidate01, candidate02, candidate03, candidate04, candidate05, candidate06};

void read_line(char *buffer, int length) {
    int i = 0;
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF && i < length - 1) {
        buffer[i++] = ch;
    }
    buffer[i] = '\0';
}

int calculate_age(const char *dob) {
    int year = 0;
    for (int i = 0; i < 4; ++i) {
        year = year * 10 + (dob[i] - '0');
    }
    return 2025 - year;
}

int main() {
    char group_name[MAX_LEN];
    char name[MAX][MAX_LEN], dob[MAX][MAX_LEN], gender[MAX][2], email[MAX][MAX_LEN];
    char nationality[MAX][MAX_LEN], primary[MAX][MAX_LEN], secondary[MAX][MAX_LEN];
    char mbti[MAX][MAX_LEN], intro[MAX][MAX_LEN];
    float bmi[MAX];
    int topik[MAX], age[MAX];

    printf("Enter Audition Group Name (e.g., Milliways): ");
    read_line(group_name, MAX_LEN);

    printf("\n####################################\n");
    printf("[%s] Audition Candidate Data Entry\n", group_name);
    printf("####################################\n");

    int index = 0;
    while (index < MAX) {
        printf("\nEntering information for candidate %d.\n", index + 1);
        printf("---------------------------------\n");

        printf("1. Name: ");
        read_line(name[index], MAX_LEN);

        printf("2. Date of Birth (YYYY/MM/DD): ");
        read_line(dob[index], MAX_LEN);
        age[index] = calculate_age(dob[index]);

        printf("3. Gender (F/M): ");
        read_line(gender[index], 2);

        printf("4. Email: ");
        read_line(email[index], MAX_LEN);

        printf("5. Nationality: ");
        read_line(nationality[index], MAX_LEN);

        printf("6. BMI: ");
        scanf("%f", &bmi[index]);
        getchar();

        printf("7. Primary Skill: ");
        read_line(primary[index], MAX_LEN);

        printf("8. Secondary Skill: ");
        read_line(secondary[index], MAX_LEN);

        printf("9. Korean Proficiency Level (TOPIK): ");
        scanf("%d", &topik[index]);
        getchar();

        printf("10. MBTI: ");
        read_line(mbti[index], MAX_LEN);

        printf("11. Introduction: ");
        read_line(intro[index], MAX_LEN);
        
        snprintf(member_info[index], MAX_LEN, "[Stored] %s", name[index]);

        index++;
    }
    printf("\n####################################\n");
    printf("[%s] Audition Candidate Data Review\n", group_name);
    printf("####################################\n");
    printf("=============================================================================================\n");
    printf("Name              | Age | DOB       | Gender | Email                 | Nationality | BMI  | Primary Skill | Secondary Skill     | TOPIK     | MBTI\n");
    printf("=============================================================================================\n");

    for (int i = 0; i < MAX; ++i) {
        char *topik_level;
        switch (topik[i]) {
            case 0: topik_level = "Native"; break;
            case 1: topik_level = "Beginner"; break;
            case 2: topik_level = "Basic"; break;
            case 3: topik_level = "Intermediate"; break;
            case 4: topik_level = "Advanced"; break;
            default: topik_level = "Unknown"; break;
        }

        printf("%-17s | %-3d | %-9s | %-6s | %-21s | %-11s | %-4.1f | %-13s | %-19s | %-9s | %-4s\n",
               name[i], age[i], dob[i], gender[i], email[i], nationality[i],
               bmi[i], primary[i], secondary[i], topik_level, mbti[i]);

        printf("---------------------------------------------------------------------------------------------\n");
        printf("%s\n", intro[i]);
        printf("---------------------------------------------------------------------------------------------\n");
    }

    return 0;
}
