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

memory *linkListMid(memory *head) {
    memory *tortoise = head;
    memory *hare = head->next;
    while (hare != NULL && hare->next != NULL) {
        tortoise = tortoise->next;
        hare = hare->next;
        hare = hare->next;
    }
    return tortoise;
}

memory *linkListMidPrev(memory *tail) {
    memory *tortoise = tail;
    memory *hare = tail->perv;
    while (hare != NULL && hare->perv != NULL) {
        tortoise = tortoise->perv;
        hare = hare->perv;
        hare = hare->perv;
    }
    return tortoise;
}

memory *merge(memory *head1, memory *head2) {
    memory *finalLinkList = malloc(sizeof(memory));
    memory *aux = malloc(sizeof(memory));
    // The finalLinkList will be returned
    finalLinkList = aux;
    while (head1 != NULL && head2 != NULL) {
        // need to pass in an actually command
        if (head1->base < head2->base) {
            aux->next = head1;
            head1 = head1->next;
        } else {
            aux->next = head2;
            head2 = head2->next;
        }
        aux = aux->next;
    }
    while (head1 != NULL) {
        aux->next = head1;
        head1 = head1->next;
        aux = aux->next;
    }
    while (head2 != NULL) {
        aux->next = head2;
        head2 = head2->next;
        aux = aux->next;
    }
    return finalLinkList->next;
}

memory *mergeTail(memory *tail1, memory *tail2) {
    memory *finalLinkList = malloc(sizeof(memory));
    memory *aux = malloc(sizeof(memory));
    // The finalLinkList will be returned
    finalLinkList = aux;
    while (tail1 != NULL && tail2 != NULL) {
        // need to pass in an actually command
        if (tail1->base > tail2->base) {
            aux->perv = tail1;
            tail1 = tail1->perv;
        } else {
            aux->perv = tail2;
            tail2 = tail2->perv;
        }
        aux = aux->perv;
    }
    while (tail1 != NULL) {
        aux->perv = tail1;
        tail1 = tail1->perv;
        aux = aux->perv;
    }
    while (tail2 != NULL) {
        aux->perv = tail2;
        tail2 = tail2->perv;
        aux = aux->perv;
    }
    return finalLinkList->perv;
}

void *spiltPrev(memory *tail) {
    if (tail->perv == NULL)
        return tail;
    memory *midNode = malloc(sizeof(memory));
    memory *tail2 = malloc(sizeof(memory));

    midNode = linkListMidPrev(tail);
    // head pointer for the second linklist
    tail2 = midNode->perv;
    // tail pointer for the first linked list
    midNode->perv = NULL;
    memory *sortedLink = mergeTail(spiltPrev(tail), spiltPrev(tail2));
    return sortedLink;
}

void *spilt(memory *head) {
    if (head->next == NULL)
        return head;
    memory *midNode = malloc(sizeof(memory));
    memory *head2 = malloc(sizeof(memory));

    midNode = linkListMid(head);
    // head pointer for the second linklist
    head2 = midNode->next;
    // tail pointer for the first linked list
    midNode->next = NULL;
    memory *sortedLink = merge(spilt(head), spilt(head2));
    return sortedLink;
}

void mergeHoles(linklist *list) {
    int limit = 0;
    memory *prev = NULL;
    memory *temp = list->head;
    memory *next = NULL;

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
        if ((prev != NULL && next != NULL) && (next->next == NULL || (strcmp(next->next->process, "H")))) {
            prev->limit = limit;
            prev->next = next->next;
            // there might be a problem with this it works for all holes but not when their processer their
            // maybe in this line in a if statement next->perv = prev->perv;
            if (prev->perv == NULL)
                next->perv = prev;
            else {
                next->perv = prev->perv;
            }
        }
        temp = temp->next;
    }
}

void compactMemory(linklist *list) {
    int limit = 0;
    memory *temp = malloc(sizeof(memory));
    memcpy(temp, list->head, sizeof(memory));
    // case for if all are holes
    if (!strcmp(temp->process, "H") && temp->next == NULL)
        return;
    while (temp != NULL) {
        // case for starts with hole
        if ((!strcmp(temp->process, "H")) && temp->perv == NULL) {
            limit = temp->limit;
            temp = temp->next;
            list->head = temp;
            continue;
        }
        // this checks if curr node is a hole
        // if it is safes its limit
        if ((!strcmp(temp->process, "H"))) {
            limit += temp->limit;
            if (temp->next != NULL) {
                // reassign the base value for next node
                temp->next->base = temp->perv->base + temp->perv->limit;
            }
            // change the pointer connection
            temp->perv->next = temp->next;

        }
        temp = temp->next;
    }
    temp = list->head;
    while (temp->next != NULL)
        temp = temp->next;
    // case for if starts with head
    if (!((!strcmp(temp->process, "H")) && temp->perv == NULL))
        temp->next = createNode("H", (temp->base + temp->limit), limit);

}
