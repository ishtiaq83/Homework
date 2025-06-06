#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h> 

#define MAX_QUESTIONS 10
#define MAX_TRAINEES 4
#define MAX_LEN 100
#define QUIZ_SIZE 5

typedef struct {
    int id;
    char question[MAX_LEN];
    char answer[MAX_LEN];
} Question;

typedef struct {
    char name[MAX_LEN];
    char nickname[MAX_LEN];
    char nationality[MAX_LEN];
    int score;
    char passed;
} Trainee;

typedef struct {
    int qid;
    char correct;
} Answer;

Question questionBank[MAX_QUESTIONS] = {
    {1, "How do you say 'Hello' in Korean?", "안녕하세요"},
    {2, "Translate to Korean: Thank you", "감사합니다"},
    {3, "What is 'Yes' in Korean?", "네"},
    {4, "What is 'No' in Korean?", "아니요"},
    {5, "Translate to Korean: I love you", "사랑해요"},
    {6, "Translate to Korean: Goodbye", "안녕히 가세요"},
    {7, "What is 'Delicious' in Korean?", "맛있어요"},
    {8, "Translate to Korean: Excuse me", "실례합니다"},
    {9, "What is 'Friend' in Korean?", "친구"},
    {10, "What is 'Family' in Korean?", "가족"}
};

Trainee trainees[MAX_TRAINEES] = {
    {"Park Ji-yeon", "Jiyeon", "Korean", 0, 'X'},
    {"Lena Smith", "Lena", "USA", 0, 'X'},
    {"Carlos Ruiz", "Carlos", "Mexico", 0, 'X'},
    {"Mina Tanaka", "Mina", "Japan", 0, 'X'}
};

int isAnswer(const Question *q, const char *input) {
    return strcmp(q->answer, input) == 0;
}

void serveQuiz(int tIndex) {
    int score = 0;
    int used[MAX_QUESTIONS] = {0};
    Answer answers[QUIZ_SIZE];
    char userInput[MAX_LEN];
    srand((unsigned int)time(NULL));

    printf("\nThe quiz will start in 30 seconds. Prepare yourself...\n");
    Sleep(30000); 

    for (int i = 0; i < QUIZ_SIZE; ) {
        int qIndex = rand() % MAX_QUESTIONS;
        if (used[qIndex]) continue;

        used[qIndex] = 1;
        Question q = questionBank[qIndex];

        printf("\n[Q%d] %s\n> ", q.id, q.question);
        scanf(" %[^\n]", userInput); 

        answers[i].qid = q.id;
        answers[i].correct = isAnswer(&q, userInput) ? 'O' : 'X';
        if (answers[i].correct == 'O') score += 20;

        i++;
    }

    trainees[tIndex].score = score;
    trainees[tIndex].passed = score >= 80 ? 'O' : 'X';

    printf("\n========= Answer Sheet =========\n");
    for (int i = 0; i < QUIZ_SIZE; i++) {
        printf("Question ID %d: %c\n", answers[i].qid, answers[i].correct);
    }
    printf("Total Score: %d\n", score);
    printf("Pass Status: %c\n", trainees[tIndex].passed);
    printf("================================\n");
}

void testKoreanLang() {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    int hour = timeinfo->tm_hour;
    int index = hour % MAX_TRAINEES;

    if (strcmp(trainees[index].nationality, "Korean") == 0) {
        for (int i = 0; i < MAX_TRAINEES; i++) {
            if (strcmp(trainees[i].nationality, "Korean") != 0) {
                index = i;
                break;
            }
        }
    }

    printf("Welcome, %s, to the Korean quiz session!\n", trainees[index].name);
    Sleep(3000);
    serveQuiz(index);
}

int main() {
    printf("\n[II. Training > 3. Language and Pronunciation Training > A. Korean Quiz]\n");
    testKoreanLang();
    return 0;
}
