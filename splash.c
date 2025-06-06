#include <stdio.h>
#include <stdlib.h>

void delaySeconds(int seconds) {
    for (int i = 0; i < seconds * 100000000; i++) {
    }
}

void drawTriangles(int line) {
    int i, j;
    for (i = 1; i <= line; i++) {
        for (j = 1; j <= i; j++) {
            printf("*");
        }
        for (j = 1; j <= 100; j++) {
            printf(" ");
        }
        for (j = line; j >= i; j--) {
            printf("*");
        }
        printf("\n");
    }
}


void displaySplash(const char *name, const char *date) {
    int i;
    printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");

    drawTriangles(5); 

    printf("                                        [Magrathea ver 0.1]                              \n");
    printf("               Magrathea, where a shining planet is created in a wasteland with no grass,        \n");
    printf("       a place where unseen potential is discovered and gems are polished by the hands of experts, \n");
    printf("                                        Welcome to Magrathea.                                      \n");

    drawTriangles(5); 

    printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("[User]: %s", name);
    printf("                                   [Execution Time]: %s\n", date);
    printf("=============================================================================================================\n");
}

int main() {
    char name[100];
    char date[20];

    printf("[Please enter the current date in the \"yyyy-mm-dd\" format]: ");
    fgets(date, sizeof(date), stdin);

    printf("[Please enter your name]: ");
    fgets(name, sizeof(name), stdin);

    printf("**The input has been processed successfully.**\n");

    delaySeconds(3);

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    displaySplash(name, date);

    return 0;
}
