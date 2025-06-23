#include <iostream>
#include <string>

using namespace std;

const int MAX_KTP = 99; 
const int JUMLAH_KOLOM = 15; 

int main() {
    string dataKTP[MAX_KTP][JUMLAH_KOLOM];
    string label[JUMLAH_KOLOM] = {
        "Nama", "NIK", "Tempat Lahir", "Tanggal Lahir", "Jenis Kelamin",
        "Alamat", "RT/RW", "Kelurahan/Desa", "Kecamatan", "Agama",
        "Status Perkawinan", "Pekerjaan", "Kewarganegaraan", "Berlaku Hingga", "Golongan Darah"
    };

    int jumlahData = 0;
    char ulang;

    do {
        cout << "\n================= Input Data KTP ke-" << (jumlahData + 1) << " ================\n";
        cin.ignore(); 

        for (int i = 0; i < JUMLAH_KOLOM; i++) {
            cout << "Masukkan " << label[i] << ": ";
            getline(cin, dataKTP[jumlahData][i]);
        }

        jumlahData++;

        cout << "\nApakah ingin memasukkan data KTP lagi? (y/n): ";
        cin >> ulang;

    } while ((ulang == 'y' || ulang == 'Y') && jumlahData < MAX_KTP);

    cout << "\n================= DATA KTP YANG TEREKAM =================\n";
    for (int i = 0; i < jumlahData; i++) {
        cout << "\n--- KTP ke-" << (i + 1) << " ---\n";
        for (int j = 0; j < JUMLAH_KOLOM; j++) {
            cout << label[j] << " : " << dataKTP[i][j] << endl;
        }
    }

    return 0;
}

