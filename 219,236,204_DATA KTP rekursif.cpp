#include <iostream>
#include <string>

using namespace std;

class KTP{
public:
	string Nik;
	string Nama;
	string TempatLahir;
	string TanggalLahir;
	string JenisKelamin;
	string Alamat;
	string Agama;
	string StatusPerkawinan;
	string Pekerjaan;
	string Kewarganegaraan;
	string BerlakuHingga;
	string GolDarah;
	
	void inputData(){
		cout << "Masukkan NIK: ";
		getline(cin, Nik);
		cout << "Masukkan Nama: ";
		getline(cin, Nama);
		cout << "Masukkan Tempat Lahir: ";
		getline(cin, TempatLahir);
		cout << "Masukkan Tanggal Lahir: ";
		getline(cin, TanggalLahir);
		cout << "Masukkan Jenis Kelamin ";
		getline(cin, JenisKelamin);
		cout << "Masukkan Alamat: ";
		getline(cin, Alamat);
		cout << "Masukkan Agama: ";
		getline(cin, Agama);
		cout << "Masukkan Status Perkawinan: ";
		getline(cin,StatusPerkawinan);
			cout << "Masukkan Pekerjaan: ";
		getline(cin, Pekerjaan);
			cout << "Masukkan Kewarganegaraan: ";
		getline(cin,  Kewarganegaraan);
			cout << "Masukkan Berlaku Hingga: ";
		getline(cin,  BerlakuHingga);
		cout << "Masukkan Gol Darah: ";
		getline(cin, GolDarah);
		
	}
		
		void CetakData(){
			cout << "\n============ Data KTP =================\n";
			cout << "NIK              : " << Nik << endl;
			cout << "Nama             : " << Nama << endl;
			cout << "Tempat Lahir     : " << TempatLahir << endl;
			cout << "Tanggal Lahir    : " << TanggalLahir << endl;
			cout << "Jenis Kelamin    : " << JenisKelamin << endl;
			cout << "Alamat           : " << Alamat << endl;
			cout << "Agama            : " << Agama << endl;
			cout << "Status Perkawinan: " << StatusPerkawinan << endl;
			cout << "Pekerjaan        : " << Pekerjaan << endl;
			cout << "Kewarganegaraan  : " << Kewarganegaraan << endl;
			cout << "Berlaku Hingga   : " << BerlakuHingga	 << endl;
			cout << "Gol Darah        : " << GolDarah << endl;
			cout << "===========================================\n";
			
		}
};

void inputKTP(int n){
	if (n <= 0) return;
	
	KTP ktp;
	cout << "Input data KTP untuk orang ke-" << (n) << ":\n";
	ktp.inputData();
	ktp.CetakData();
	
	inputKTP(n -1);
}

int main() {
	int jumlah;
	cout << "Masukkan jumlah data KTP: ";
	cin >> jumlah;
	cin.ignore();
	
	inputKTP(jumlah);
	
	cout << "Terima kasih, Gumawoo, Arigato, Thanks.\n";
	return 0;
}
