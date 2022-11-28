struct memory_t {
    char process[2];
    int base;
    int limit;
    struct memory_t *perv;
    struct memory_t *next;
};

typedef struct memory_t memory;

struct linkList_t {
    memory *head;
    memory *tail;
};

typedef struct linkList_t linklist;