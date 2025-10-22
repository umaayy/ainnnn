#include <iostream>
using namespace std;

struct KTP {
    string nama;
    string nik;
    string alamat;
    string tgl;
};

int main() {
    KTP* data = NULL;        
    int jumlah = 0;            
    int kapasitas = 0;         
    int pilihan;

    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Tambah KTP\n";
        cout << "2. Tampilkan KTP\n";
        cout << "3. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();  

        switch(pilihan) {
            case 1: {
                if (jumlah == kapasitas) {
                   
                    kapasitas = kapasitas == 0 ? 2 : kapasitas * 2;
                    KTP* temp = new KTP[kapasitas];
                    for (int i = 0; i < jumlah; ++i) {
                        temp[i] = data[i];
                    }
                    delete[] data;
                    data = temp;
                }

                cout << "Masukkan NIK    : ";
                cin>>data[jumlah].nik;
                cout << "\nMasukkan Nama   : ";
                cin>>data[jumlah].nama; 
                cout << "Masukkan Alamat : ";
                cin>> data[jumlah].alamat; 
                cout<<"masukan tanggal lahir : ";
                cin>>data[jumlah].tgl;

                jumlah++;
                cout << "Data berhasil ditambahkan!\n";
                break;
            }

            case 2: {
                if (jumlah == 0) {
                    cout << "\nBelum ada data KTP.\n";
                } else {
                    cout << "\n=== Daftar KTP ===\n";
                    for (int i = 0; i < jumlah; ++i) {
                        cout << "Data ke-" << i + 1 << ":\n";
                        cout << "Nama          : " << data[i].nama << endl;
                        cout << "NIK           : " << data[i].nik << endl;
                        cout << "Alamat        : " << data[i].alamat << endl;
                        cout << "tanggal lahir : " << data[i].tgl<<endl;
                        cout << "-----------------------\n";
                    }
                }
                break;
            }

            case 3:
                cout << "Keluar dari program.\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 3);

    
    delete[] data;

    return 0;
}
