#include <stdio.h>
#include <stdlib.h>

// Struktur Node untuk Double Linked List
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* head = NULL;
Node* tail = NULL;

// Fungsi untuk membuat node baru
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Insert di posisi tengah
void push_mid(int value) {
    Node* newNode = createNode(value);

    // Jika list kosong atau hanya ada satu elemen
    if (!head || head->next == NULL) {
        newNode->next = head;
        if (head) head->prev = newNode;
        head = newNode;
        if (!tail) tail = newNode;
        return;
    }

    // Cari posisi tengah
    Node* slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Sisipkan di tengah sebelum slow
    newNode->next = slow;
    newNode->prev = slow->prev;
    if (slow->prev) slow->prev->next = newNode;
    slow->prev = newNode;

    // Jika newNode menjadi head baru
    if (slow == head) head = newNode;
}

// Hapus node dari depan
void delete_front() {
    if (!head) {
        printf("List kosong!\n");
        return;
    }

    Node* temp = head;
    head = head->next;
    if (head) head->prev = NULL;
    else tail = NULL; // Jika list kosong

    free(temp);
    printf("Node depan dihapus!\n");
}

// Hapus node dari belakang
void delete_back() {
    if (!tail) {
        printf("List kosong!\n");
        return;
    }

    Node* temp = tail;
    tail = tail->prev;
    if (tail) tail->next = NULL;
    else head = NULL; // Jika list kosong

    free(temp);
    printf("Node belakang dihapus!\n");
}

// Hapus node di tengah
void delete_mid() {
    if (!head || !head->next) {
        delete_front();
        return;
    }

    // Cari posisi tengah
    Node* slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Hapus node tengah
    if (slow->prev) slow->prev->next = slow->next;
    if (slow->next) slow->next->prev = slow->prev;
    if (slow == head) head = slow->next;
    if (slow == tail) tail = slow->prev;

    free(slow);
    printf("Node tengah dihapus!\n");
}

// Cetak isi linked list
void printList() {
    Node* temp = head;
    printf("List: ");
    while (temp) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Menu utama dengan switch-case
void menu() {
    int choice, value;
    do {
        printf("\n--- MENU DOUBLE LINKED LIST ---\n");
        printf("1. Tambah Node di Tengah (push_mid)\n");
        printf("2. Hapus Node Depan (delete_front)\n");
        printf("3. Hapus Node Belakang (delete_back)\n");
        printf("4. Hapus Node Tengah (delete_mid)\n");
        printf("5. Tampilkan List\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Masukkan nilai: ");
                scanf("%d", &value);
                push_mid(value);
                printf("Node dengan nilai %d ditambahkan di tengah.\n", value);
                break;
            case 2:
                delete_front();
                break;
            case 3:
                delete_back();
                break;
            case 4:
                delete_mid();
                break;
            case 5:
                printList();
                break;
            case 0:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (choice != 0);
}

// Driver program
int main() {
    menu();
    return 0;
}

