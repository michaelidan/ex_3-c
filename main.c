#include "StrList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 20

char* read_word() {
    char* buffer = malloc(BUFSZ);
    if (!buffer) return NULL;

    int bufferSize = BUFSZ;
    int length = 0;
    int c;

    while ((c = getchar()) != EOF && (c == ' ' || c == '\n' || c == '\t'));

    if (c == EOF) {
        free(buffer);
        return NULL;
    }

    buffer[length++] = c;

    while ((c = getchar()) != EOF && c != ' ' && c != '\n' && c != '\t') {
        if (length + 1 >= bufferSize) {
            bufferSize *= 2;
            char* newBuffer = realloc(buffer, bufferSize);
            if (!newBuffer) {
                free(buffer);
                return NULL;
            }
            buffer = newBuffer;
        }
        buffer[length++] = c;
    }

    buffer[length] = '\0';
    return buffer;
}

int main() {
    StrList* list = StrList_alloc();
    int choice;
    char* word;
    int index;

    while (1) {
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input, please try again!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n'); 
        
        switch (choice) {
            case 1:    
                int numWords;
                if (scanf("%d", &numWords) != 1) {
                    printf("Invalid input, please try again!\n");
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');

                for (int i = 0; i < numWords; i++) {
                    word = read_word();
                    if (word) {
                        StrList_insertLast(list, word);
                        free(word);
                    }
                }
                break;
            case 2:
                if (scanf("%d", &index) != 1) {
                    printf("Invalid input, please try again!\n");
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n'); 

                word = read_word();
                if (word) {
                    StrList_insertAt(list, word, index);
                    free(word);
                }
                break;
            case 3:
                StrList_print(list);
                break;
            case 4:
                printf("%zu\n", StrList_size(list));
                break;
            case 5:
                if (scanf("%d", &index) != 1) {
                    printf("Invalid input, please try again!\n");
                    while (getchar() != '\n');
                    continue;
                }
                StrList_printAt(list, index);
                break;
            case 6:
                printf("%d\n", StrList_printLen(list));
                break;
            case 7:
                word = read_word();
                if (word) {
                    printf("%d\n", StrList_count(list, word));
                    free(word);
                }
                break;
            case 8:
                word = read_word();
                if (word) {
                    StrList_remove(list, word);
                    free(word);
                }
                break;
            case 9:
                if (scanf("%d", &index) != 1) {
                    printf("Invalid input, please try again!\n");
                    while (getchar() != '\n');
                    continue;
                }
                StrList_removeAt(list, index);
                break;
            case 10:
                StrList_reverse(list);
                break;
            case 11:
                StrList_free(list);
                list = StrList_alloc();
                break;
            case 12:
                StrList_sort(list);
                break;
            case 13:
                if (StrList_isSorted(list)) {
                    printf("true\n");
                } else {
                    printf("false\n");
                }
                break;
            case 0:
                StrList_free(list);
                return 0;
            default:
                printf("Invalid choice, please try again!\n");
                break;
        }
    }
    return 0;
}
