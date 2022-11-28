memory *createNode(char *process, int base, int limit) {
    memory *node = malloc(sizeof(memory));

    memcpy(node->process, process, 8);
    node->base = base;
    node->limit = limit;
    node->perv = NULL;
    node->next = NULL;

    return node;
}

void addNode(linklist *list, memory *node) {
    if (list->head == NULL) {
        list->head = node;
        list->tail = list->head;
    }
    node->perv = list->tail;
    list->tail->next = node;
    list->tail = node;
    list->head->perv = NULL;
}