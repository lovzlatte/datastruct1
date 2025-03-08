#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define TABLE_SIZE 10

// Struktur untuk chaining
struct Node {
    char key[100];
    struct Node* next;
};

struct Node* ht[TABLE_SIZE]; // Hash table dengan linked list

// Inisialisasi hash table
void initializationHT() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht[i] = NULL;
    }
}

// Konversi string ke integer (ASCII sum)
int StoI(char key[]) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum;
}

// Division Method
int DivHash(char key[]) {
    return StoI(key) % TABLE_SIZE;
}

// Folding Method
int FoldingHash(char key[]) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i += 2) {
        int part = (key[i] << 8);
        if (key[i + 1] != '\0') {
            part += key[i + 1];
        }
        sum += part;
    }
    return sum % TABLE_SIZE;
}

// Mid-Square Method
int MidSquareHash(char key[]) {
    int intKey = StoI(key);
    int square = intKey * intKey;
    return (square / 100) % TABLE_SIZE;
}

// Digit Extraction Method
int DigitExtractHash(char key[]) {
    int intKey = StoI(key);
    int extracted = (intKey / 10) % TABLE_SIZE;
    return extracted;
}

// Rotating Hash
int RotatingHash(char key[]) {
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = (hash << 4) ^ (hash >> 28) ^ key[i];
    }
    return abs(hash) % TABLE_SIZE;
}

// Linear Probing
int linearProbing(int index) {
    int i = 0;
    while (ht[(index + i) % TABLE_SIZE] != NULL && i < TABLE_SIZE) {
        i++;
    }
    return (index + i) % TABLE_SIZE;
}

// Chaining Insert
void insertChaining(char key[], int (*hashFunction)(char[])) {
    int index = hashFunction(key);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->key, key);
    newNode->next = ht[index];
    ht[index] = newNode;
    printf("Key %s dimasukkan ke index %d (Chaining).\n", key, index);
}

// Insert dengan Linear Probing
void insertLinear(char key[], int (*hashFunction)(char[])) {
    int index = hashFunction(key);
    if (ht[index] == NULL) {
        ht[index] = (struct Node*)malloc(sizeof(struct Node));
        strcpy(ht[index]->key, key);
        ht[index]->next = NULL;
        printf("Key %s dimasukkan ke index %d.\n", key, index);
    } else {
        printf("Collision! Mencari slot kosong dengan Linear Probing...\n");
        int newIndex = linearProbing(index);
        if (ht[newIndex] == NULL) {
            ht[newIndex] = (struct Node*)malloc(sizeof(struct Node));
            strcpy(ht[newIndex]->key, key);
            ht[newIndex]->next = NULL;
            printf("Key %s dimasukkan ke index %d setelah probing.\n", key, newIndex);
        } else {
            printf("Hash table penuh, tidak dapat memasukkan key %s!\n", key);
        }
    }
}

// Display Hash Table
void displayHT() {
    printf("\nHash Table\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        struct Node* temp = ht[i];
        if (temp == NULL) {
            printf("kosong\n");
        } else {
            while (temp != NULL) {
                printf("%s -> ", temp->key);
                temp = temp->next;
            }
            printf("NULL\n");
        }
    }
}

int main() {
    initializationHT();
    char key[100];
    int choice;
    int (*hashFunction)(char[]);
    void (*collisionHandling)(char[], int (*hashFunction)(char[]));
    
    printf("Pilih Hash Function:\n");
    printf("1. Division\n2. Folding\n3. Mid-Square\n4. Digit Extraction\n5. Rotating\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1: hashFunction = DivHash; break;
        case 2: hashFunction = FoldingHash; break;
        case 3: hashFunction = MidSquareHash; break;
        case 4: hashFunction = DigitExtractHash; break;
        case 5: hashFunction = RotatingHash; break;
        default: hashFunction = DivHash;
    }
    
    printf("Pilih Collision Handling:\n");
    printf("1. Linear Probing\n2. Chaining\n");
    scanf("%d", &choice);
    collisionHandling = (choice == 1) ? insertLinear : insertChaining;
    
    while (1) {
        printf("Masukkan key (string) atau 'exit' untuk berhenti: ");
        scanf("%s", key);
        if (strcmp(key, "exit") == 0) break;
        collisionHandling(key, hashFunction);
    }
    
    displayHT();
    return 0;
}

