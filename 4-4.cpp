#include <iostream>
using namespace std;

int main(){
    int n;

    cout << "Masukkan jumlah data: ";
    cin >> n;

    int A[n];

    for(int i = 0; i < n; i++){
        cout << "Masukkan angka ke-" << i+1 << ": ";
        cin >> A[i];
    }

    int key, j;

    for(int i = 1; i < n; i++){
        key = A[i];
        j = i - 1;

        while(j >= 0 && A[j] > key){
            A[j + 1] = A[j];
            j = j - 1;
        }

        A[j + 1] = key;
    }

    cout << "Hasil setelah diurutkan: ";
    for(int i = 0; i < n; i++){
        cout << A[i] << " ";
    }

    return 0;
}
