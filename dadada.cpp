#include <iostream>
using namespace std;

struct MataKuliah {
    string namaMK;
    int sks;
    float tugas, uts, uas;
    float nilaiAkhir;
    float bobotNilai;
};

float konversiNilai(float nilai) {
    if (nilai >= 85) return 4.0;
    else if (nilai >= 75) return 3.0;
    else if (nilai >= 65) return 2.0;
    else if (nilai >= 50) return 1.0;
    else return 0.0;
}

int main() {
    int jumlahMK;
    cout << "Masukkan jumlah mata kuliah: ";
    cin >> jumlahMK;
    cin.ignore();

    MataKuliah* mk = new MataKuliah[jumlahMK];

    float totalBobot = 0;
    int totalSKS = 0;

    for (int i = 0; i < jumlahMK; i++) {
        cout << "\nMata Kuliah ke-" << i + 1 << endl;
        cout << "Nama MK       : ";
        getline(cin, mk[i].namaMK);
        cout << "Jumlah SKS    : ";
        cin >> mk[i].sks;
        cout << "Nilai Tugas   : ";
        cin >> mk[i].tugas;
        cout << "Nilai UTS     : ";
        cin >> mk[i].uts;
        cout << "Nilai UAS     : ";
        cin >> mk[i].uas;
        cin.ignore();

        // Hitung nilai akhir dan bobot
        mk[i].nilaiAkhir = (0.2 * mk[i].tugas) + (0.3 * mk[i].uts) + (0.5 * mk[i].uas);
        mk[i].bobotNilai = konversiNilai(mk[i].nilaiAkhir);

        totalBobot += mk[i].bobotNilai * mk[i].sks;
        totalSKS += mk[i].sks;
    }

    float ipk = totalBobot / totalSKS;

    // Tampilkan hasil
    cout << "\n=== REKAP NILAI DAN IPK ===\n";
    for (int i = 0; i < jumlahMK; i++) {
        cout << "Mata Kuliah : " << mk[i].namaMK << endl;
        cout << "SKS         : " << mk[i].sks << endl;
        cout << "Nilai Akhir : " << mk[i].nilaiAkhir << endl;
        cout << "Bobot Nilai : " << mk[i].bobotNilai << "\n\n";
    }

    cout << "Total SKS    : " << totalSKS << endl;
    cout << "IPK Semester : " << ipk << endl;

    delete[] mk;
    return 0;
}

