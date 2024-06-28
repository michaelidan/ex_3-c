#include "StrList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* StrList_duplicateString(const char* s) {
    char* d = malloc(strlen(s) + 1);   
    if (d == NULL) return NULL;        
    strcpy(d, s);                      
    return d;                          
}

struct Node {
    char* data;
    struct Node* next;
};

struct _StrList {
    struct Node* head;
    size_t size;
};

StrList* StrList_alloc() {
    StrList* list = (StrList*)malloc(sizeof(StrList));
    if (!list) return NULL;
    list->head = NULL;
    list->size = 0;
    return list;
}

void StrList_free(StrList* list) {
    if (!list) return;
    struct Node* current = list->head;
    while (current) {
        struct Node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(list);
}

size_t StrList_size(const StrList* list) {
    return list ? list->size : 0;
}

void StrList_insertLast(StrList* list, const char* data) {
    if (!list || !data) return;
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) return;
    newNode->data = StrList_duplicateString(data);
    newNode->next = NULL;

    if (!list->head) {
        list->head = newNode;
    } else {
        struct Node* temp = list->head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    list->size++;
}

void StrList_insertAt(StrList* list, const char* data, int index) {
    if (!list || !data || index < 0 || index > (int)list->size) return;
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) return;
    newNode->data = StrList_duplicateString(data);

    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        struct Node* temp = list->head;
        for (int i = 0; i < index - 1; ++i) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
    list->size++;
}

char* StrList_firstData(const StrList* list) {
    return (list && list->head) ? list->head->data : NULL;
    }

void StrList_print(const StrList* list) {
    if (!list) return;
    struct Node* temp = list->head;
    while (temp) {
        printf("%s", temp->data);
        if (temp->next) {
            printf(" ");
        }
        temp = temp->next;
    }
    printf("\n");
}



void StrList_printAt(const StrList* list, int index) {
    if (!list || index < 0 || index >= (int)list->size) return;
    
    struct Node* temp = list->head;
    for (int i = 0; i < index; ++i) {
        temp = temp->next;
    }
    
    if (temp) {
        printf("%s\n", temp->data);
    }
}


int StrList_printLen(const StrList* list) {
    if (!list) return 0;
    int len = 0;
    struct Node* temp = list->head;
    while (temp) {
        len += strlen(temp->data);
        temp = temp->next;
    }
    return len;
}

int StrList_count(StrList* list, const char* data) {
    if (!list || !data) return 0;
    int count = 0;
    struct Node* temp = list->head;
    while (temp) {
        if (strcmp(temp->data, data) == 0) {
            count++;
        }
        temp = temp->next;
    }
    return count;
}

void StrList_remove(StrList* list, const char* data) {
    if (!list || !data) return;
    struct Node *temp = list->head, *prev = NULL;
    while (temp) {
        if (strcmp(temp->data, data) == 0) {
            if (prev) {
                prev->next = temp->next;
            } else {
                list->head = temp->next;
            }
            free(temp->data);
            free(temp);
            temp = (prev) ? prev->next : list->head;
            list->size--;
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
}

void StrList_removeAt(StrList* list, int index) {
    if (!list || index < 0 || index >= (int)list->size) return;
    struct Node *temp = list->head, *prev = NULL;
    for (int i = 0; i < index; ++i) {
        prev = temp;
        temp = temp->next;
    }
    if (prev) {
        prev->next = temp->next;
    } else { // if index = 0
        list->head = temp->next;
    }
    if (temp->data) { 
        free(temp->data); 
    }
    free(temp);
    list->size--;
}

int StrList_isEqual(const StrList* list1, const StrList* list2) {
    if (!list1 || !list2 || list1->size != list2->size) return 0;
    struct Node *temp1 = list1->head, *temp2 = list2->head;
    while (temp1 && temp2) {
        if (strcmp(temp1->data, temp2->data) != 0) return 0;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return 1;
}

StrList* StrList_clone(const StrList* list) {
    if (!list) return NULL;
    StrList* newList = StrList_alloc();
    if (!newList) return NULL;
    struct Node* temp = list->head;
    while (temp) {
        StrList_insertLast(newList, temp->data);
        temp = temp->next;
    }
    return newList;
}

void StrList_reverse(StrList* list) {
    if (!list || !list->head || !list->head->next) return;
    struct Node *Prev = NULL;
    struct Node *Curr = list->head;
    struct Node *Next = list->head->next;
    while (Next) {
        Curr->next = Prev;
        Prev = Curr;
        Curr = Next;
        Next = Next->next;
    }
    Curr->next = Prev;
    list->head = Curr;
}

void StrList_sort(StrList* list) {
    if (!list || !list->head || !list->head->next) return;
    for (struct Node* i = list->head; i != NULL; i = i->next) {
        for (struct Node* j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->data, j->data) > 0) { 
                char* temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

int StrList_isSorted(StrList* list) {
    if (!list || list->size < 2) return 1;
    struct Node* temp = list->head;
    while (temp->next) {
        if (strcmp(temp->data, temp->next->data) > 0) {
            return 0;
        }
        temp = temp->next;
    }
    return 1;
}
