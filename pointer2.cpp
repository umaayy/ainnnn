#include <iostream>
using namespace std;

// Definisi struktur node
struct Node {
    int data;
    Node* next;
};

// Fungsi untuk menghitung jumlah node dalam linked list
int hitungJumlahNode(Node* head) {
    int count = 0;
    Node* current = head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

// Fungsi untuk menambahkan node di akhir list
void tambahNode(Node*& head, int dataBaru) {
    Node* nodeBaru = new Node;
    nodeBaru->data = dataBaru;
    nodeBaru->next = NULL;

    if (head == NULL) {
        head = nodeBaru;
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nodeBaru;
    }
}

// Fungsi untuk menampilkan isi linked list
void tampilkanList(Node* head) {
    Node* current = head;
    cout << "Isi Linked List: ";
    while (current != NULL) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "NULL" << endl;
}

// Fungsi utama
int main() {
    Node* head = NULL;

    // Tambahkan beberapa node ke linked list
    tambahNode(head, 10);
    tambahNode(head, 20);
    tambahNode(head, 30);
    tambahNode(head, 40);

    // Tampilkan isi linked list
    tampilkanList(head);

    // Hitung jumlah node
    int jumlah = hitungJumlahNode(head);
    cout << "Jumlah elemen dalam linked list: " << jumlah << endl;

    return 0;
}

