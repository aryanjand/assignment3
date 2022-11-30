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
    if (userFile == NULL) {
        printf("%s", "Error: File failed to open");
        exit(0);
    }
    return userFile;
}


int main() {
    int command = askUserCommand();
    linklist *list = malloc(sizeof(list));
    list->head = malloc(8);
    list->head = NULL;
    list->tail = malloc(8);
    list->tail = NULL;

    if (command < 1 || command > 5) {
        printf("%s", "Error: Invalid Command");
        exit(0);
    }

    while (command != 5) {
        if (command == 1) {
            FILE *userFile = openFile();
            while (!feof(userFile)) {
                char *process = malloc(sizeof(char) * 2);
                int base;
                int limit;
                int items = fscanf(userFile, "%s %d %d", process, &base, &limit);
                if (items != 3) {
                    printf("%s", "Error: Invalid file data");
                    exit(0);
                }
                if (limit <= 0) {
                    printf("%s", "Error: Invalid file data");
                    exit(0);
                }
                if (base < 0) {
                    printf("%s", "Error: Invalid file data");
                    exit(0);
                }
                memory *node = createNode(process, base, limit);
                addNode(list, node);
            }
            list->head = spilt(list->head);
            list->tail = spiltPrev(list->tail);
            printf("%s\n", "operation successful");
        }
        if (command == 2) {
            mergeHoles(list);
            printf("%s", "operation successful\n");
        }
        if (command == 3) {
            mergeHoles(list);
            compactMemory(list);
            printf("%s", "operation successful\n");
        }
        if (command == 4) {
            int count = 1;
            memory *temp = list->head;
            while (temp != NULL) {
                printf("Node %d: %s, base = %d, limit = %d\n", count, temp->process, temp->base, temp->limit);
                temp = temp->next;
                count++;
            }
        }
        command = askUserCommand();
    }

    if (command == 5) {
        printf("%s",
               "I\'ll Just Keep Moving Forward... \nUntil I\'ve Killed My Enemies.");
    }
    return 0;
}