#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processor.h"
#include "processor.c"

int askUserCommand() {
    printf("%s",
           "1. load an input file\n2. merge holes\n3. compact memory\n4. print memory view\n5. Exit the program\n");
    int command;
    scanf("%d", &command);
    return command;
}

FILE *openFile() {
/** Change this to file name at the end
 * - Need to handle conner cases here
 * - Need to ask user for input for the file name
 * - */
    printf("%s", "1. Type the file name:\n");
    char *fileName = malloc(sizeof(char *));
    scanf("%s", fileName);
    FILE *userFile = fopen("../test.txt", "r");
    return userFile;
//    printf("%s\n", p);
//    printf("%d\n", base);
//    printf("%d", limit);
}


int main() {
    int command = 0;
    linklist *list = malloc(sizeof(list));
    list->head = malloc(4);
    list->head = NULL;
    list->tail = malloc(4);
    list->tail = NULL;

    while (command != 5) {
        command = askUserCommand();

        if (command == 1) {
            FILE *userFile = openFile();
            while (!feof(userFile)) {
                char *process = malloc(sizeof(char) * 2);
                int base;
                int limit;
                fscanf(userFile, "%s %d %d", process, &base, &limit);
                memory *node = createNode(process, base, limit);
                addNode(list, node);
            }
            printf("%s\n", "operation successful");
        }
        if (command == 2) {
            int limit = 0;
            memory *prev = NULL;
            memory *temp = malloc(sizeof(memory));
            memory *next = NULL;
            memcpy(temp, list->head, sizeof(memory));

            while (temp != NULL) {
                if ((!strcmp(temp->process, "H")) && prev == NULL) {
                    prev = temp;
                    limit += prev->limit;
//                    printf("This works\n");
                } else if (((!strcmp(temp->process, "H")) && next == NULL)) {
                    next = temp;
                    limit += next->limit;
//                    printf("This works now\n");
                } else if ((!strcmp(temp->process, "H")) && (!strcmp(next->next->process, "H"))) {
                    next = temp;
                    limit += next->limit;
//                    printf("This relly works now\n");
                } else {
                    prev = NULL;
                    next = NULL;
                    limit = 0;
                }
                if (prev != NULL && next != NULL && (next->next == NULL || (strcmp(next->next->process, "H")))) {
                    prev->limit = limit;
                    prev->next = next->next;
                }
                temp = temp->next;
            }
//            memcpy(list->head, temp, sizeof (memory));
//            free(temp);
        }

        if (command == 3) {
            int limit = 0;
            memory *temp = malloc(sizeof(memory));
            memcpy(temp, list->head, sizeof(memory));
            while (temp != NULL) {

                if ((!strcmp(temp->process, "H"))) {

                    limit += temp->limit;

                    if (temp->next != NULL) {
                        temp->next->base = temp->base ;
                    }
                    temp->perv->next = temp->next;
                }

                temp = temp->next;

            }

            printf("%d\n", limit);
        }

        if (command == 4) {
            memory *temp = list->head;
            while (temp != NULL) {
                printf("%s\t", temp->process);
                printf("%d\t", temp->base);
                printf("%d\n", temp->limit);
                temp = temp->next;
            }
        }
    }




    return 0;
}