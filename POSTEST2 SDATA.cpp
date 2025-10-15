#include <iostream>
using namespace std;

#define MAKS 10

class Array1D {
public:
    char A[MAKS];

    Array1D() {
        for (int i = 0; i < MAKS; i++)
        	A[i] = '0';
    }

    void input() {
    	A[0] = 'A';
    	A[1] = 'B';
    	A[2] = 'C';
    	A[3] = 'D';
		A[4] = 'E';
    	A[5] = 'F';
    	A[6] = 'G';
    	A[7] = 'H';
    	A[8] = 'I';
    	A[9] = 'J';
   }

    void cetak() {
        for (int i = 0; i < MAKS; i++)
            cout << A[i] << " ";
        cout << endl;
    }

    void geserKiri() {
        char temp = A[0];
        for (int i = 0; i < MAKS - 1; i++)
            A[i] = A[i + 1];
        A[MAKS - 1] = temp;
    }

    void geserKanan() {
        char temp = A[MAKS - 1];
        for (int i = MAKS - 1; i > 0; i--)
            A[i] = A[i - 1];
        A[0] = temp;
    }
};

int main() {
    Array1D x;

//    cout << "Array masih kosong: ";
//    x.cetak();

    x.input();
    cout << "Isi array saat ini: ";
    x.cetak();

    x.geserKanan();
    cout << "Isi array setelah digeser ke kanan: ";
    x.cetak();
    
     x.geserKiri();
    cout << "Isi array setelah digeser ke kiri: ";
    x.cetak();

    return 0;
}
