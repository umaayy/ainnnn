#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct KTP {
    string nama;
    string nik;
    string tempatlahir;
    string tanggallahir;
    string jeniskelamin;
    string alamat;
    string rtrw;
    string kelurahan;
    string kecamatan;
    string agama;
    string statusperkawinan;
    string pekerjaan;
    string kewarganegaraan;
    string berlakuhingga;
    string golongandarah;
};

void tampilkanData(const KTP& ktp, int index) {
    cout << "\n============ DATA KTP KE-" << index + 1 << " ==============" << endl;
    cout << "Nama               : " << ktp.nama << endl;
    cout << "NIK                : " << ktp.nik << endl;
    cout << "Tempat Lahir       : " << ktp.tempatlahir << endl;
    cout << "Tanggal Lahir      : " << ktp.tanggallahir << endl;
    cout << "Jenis Kelamin      : " << ktp.jeniskelamin << endl;
    cout << "Alamat             : " << ktp.alamat << endl;
    cout << "RT/RW              : " << ktp.rtrw << endl;
    cout << "Kelurahan/Desa     : " << ktp.kelurahan << endl;
    cout << "Kecamatan          : " << ktp.kecamatan << endl;
    cout << "Agama              : " << ktp.agama << endl;
    cout << "Status Perkawinan  : " << ktp.statusperkawinan << endl;
    cout << "Pekerjaan          : " << ktp.pekerjaan << endl;
    cout << "Kewarganegaraan    : " << ktp.kewarganegaraan << endl;
    cout << "Berlaku Hingga     : " << ktp.berlakuhingga << endl;
    cout << "Golongan Darah     : " << ktp.golongandarah << endl;
    cout << "\n======================================="<< endl;
}
string toLowerCase(const string& str) {
    string lower = str;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}
//buat cari true false dari kata kunci
bool cocok(const KTP& ktp, const string& keyword) {
    string key = toLowerCase(keyword);
    return toLowerCase(ktp.nama).find(key) != string::npos ||
           toLowerCase(ktp.nik).find(key) != string::npos ||
           toLowerCase(ktp.tempatlahir).find(key) != string::npos ||
           toLowerCase(ktp.tanggallahir).find(key) != string::npos ||
           toLowerCase(ktp.jeniskelamin).find(key) != string::npos ||
           toLowerCase(ktp.alamat).find(key) != string::npos ||
           toLowerCase(ktp.rtrw).find(key) != string::npos ||
           toLowerCase(ktp.kelurahan).find(key) != string::npos ||
           toLowerCase(ktp.kecamatan).find(key) != string::npos ||
           toLowerCase(ktp.agama).find(key) != string::npos ||
           toLowerCase(ktp.statusperkawinan).find(key) != string::npos ||
           toLowerCase(ktp.pekerjaan).find(key) != string::npos ||
           toLowerCase(ktp.kewarganegaraan).find(key) != string::npos ||
           toLowerCase(ktp.berlakuhingga).find(key) != string::npos ||
           toLowerCase(ktp.golongandarah).find(key) != string::npos;
}

void cariKTP(KTP arr[], int n) {
    string keyword;
    bool ditemukan = false;

    cin.ignore();
    cout << "\nMasukkan kata kunci untuk mencari di semua data: ";
    getline(cin, keyword);

    for (int i = 0; i < n; i++) {
        if (cocok(arr[i], keyword)) {
            tampilkanData(arr[i], i);
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "\nTidak ada data yang cocok dengan kata kunci \"" << keyword << "\".\n";
    }
}

void bubbleSort(KTP arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j].nama > arr[j + 1].nama) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    const int MAX = 100;
    KTP data[MAX];
    int jumlah = 0;
    char ulang;

    do {
        cout << "\n================= Input Data KTP =================" << endl;
        cout << "Masukkan nama               : ";
        cin.ignore();
        getline(cin, data[jumlah].nama);
        cout << "Masukkan NIK                : ";
        getline(cin, data[jumlah].nik);
        cout << "Masukkan Tempat Lahir       : ";
        getline(cin, data[jumlah].tempatlahir);
        cout << "Masukkan Tanggal Lahir      : ";
        getline(cin, data[jumlah].tanggallahir);
        cout << "Masukkan Jenis Kelamin      : ";
        getline(cin, data[jumlah].jeniskelamin);
        cout << "Masukkan Alamat             : ";
        getline(cin, data[jumlah].alamat);
        cout << "Masukkan RT/RW              : ";
        getline(cin, data[jumlah].rtrw);
        cout << "Masukkan Kelurahan/Desa     : ";
        getline(cin, data[jumlah].kelurahan);
        cout << "Masukkan Kecamatan          : ";
        getline(cin, data[jumlah].kecamatan);
        cout << "Masukkan Agama              : ";
        getline(cin, data[jumlah].agama);
        cout << "Masukkan Status Perkawinan  : ";
        getline(cin, data[jumlah].statusperkawinan);
        cout << "Masukkan Pekerjaan          : ";
        getline(cin, data[jumlah].pekerjaan);
        cout << "Masukkan Kewarganegaraan    : ";
        getline(cin, data[jumlah].kewarganegaraan);
        cout << "Masukkan Berlaku Hingga     : ";
        getline(cin, data[jumlah].berlakuhingga);
        cout << "Masukkan Golongan Darah     : ";
        getline(cin, data[jumlah].golongandarah);
        cout << "\n==================================================" << endl;
        
        jumlah++;

        cout << "\nApakah Anda ingin memasukkan data lagi? (y/n): ";
        cin >> ulang;

    } while ((ulang == 'y' || ulang == 'Y') && jumlah < MAX);

    bubbleSort(data, jumlah);

    // tampil semua data
    cout << "\n========== DATA KTP SETELAH DIURUTKAN BERDASARKAN NAMA ==========\n";
    for (int i = 0; i < jumlah; i++) {
        tampilkanData(data[i], i);
    }

   // flexibel dari kata apa aja 
    char cariLagi;
    do {
        cout << "\nIngin mencari data berdasarkan kata kunci? (y/n): ";
        cin >> cariLagi;
        if (cariLagi == 'y' || cariLagi == 'Y') {
            cariKTP(data, jumlah);
        }
    } while (cariLagi == 'y' || cariLagi == 'Y');

    return 0;
}

