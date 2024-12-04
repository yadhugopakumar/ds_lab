#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10
#define EMPTY -1

typedef struct HashSet {
    int* table;
} HashSet;


unsigned int hash(int key) {
    return key % TABLE_SIZE;
}

HashSet* createSet() {
    HashSet* set = (HashSet*)malloc(sizeof(HashSet));
    set->table = (int*)malloc(sizeof(int) * TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++) {
        set->table[i] = EMPTY; 
    }
    return set;
}

void insert(HashSet* set, int value) {
    unsigned int index = hash(value);

    while (set->table[index] != EMPTY) {
        if (set->table[index] == value) {
            printf("%d already exists in the set.\n", value);
            return;
        }
        index = (index + 1) % TABLE_SIZE;
    }

    set->table[index] = value;
    printf("%d inserted into the set.\n", value);
}

int search(HashSet* set, int value) {
    unsigned int index = hash(value);

    while (set->table[index] != EMPTY) {
        if (set->table[index] == value) {
            return 1; 
        }
        index = (index + 1) % TABLE_SIZE; 
    }
    return 0; 
}

void removeValue(HashSet* set, int value) {
    unsigned int index = hash(value);

    while (set->table[index] != EMPTY) {
        if (set->table[index] == value) {
            set->table[index] = EMPTY; 
            printf("%d removed from the set.\n", value);
            return;
        }
        index = (index + 1) % TABLE_SIZE;
    }
    printf("%d not found in the set.\n", value);
}

void display(HashSet* set) {
    printf("Set contents:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (set->table[i] != EMPTY) {
            printf("Index %d: %d\n", i, set->table[i]);
        }
    }
}

void freeSet(HashSet* set) {
    free(set->table);
    free(set);
}

int main() {
    HashSet* set = createSet();
    int choice, value;

    while (1) {
        printf("\n--- Set Menu ---\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Remove\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(set, value);
                break;
            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (search(set, value)) {
                    printf("%d is in the set.\n", value);
                } else {
                    printf("%d is not in the set.\n", value);
                }
                break;
            case 3:
                printf("Enter value to remove: ");
                scanf("%d", &value);
                removeValue(set, value);
                break;
            case 4:
                display(set);
                break;
            case 5:
                freeSet(set);
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
