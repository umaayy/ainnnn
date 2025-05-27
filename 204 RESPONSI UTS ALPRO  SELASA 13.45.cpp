#include <iostream>
using namespace std;

int main(){
	string user;
	int passwor,saldo,jenisbarang,hapus,alamat,diskon;
	char pil;
	char ulang;
	char hapus;
	
	cout<<"======================= LOGIN =============== "<<endl;
	cout<<"Masukkan username :";
	cin>>user;
	cout << "MAsukkan Password :";
	cin >> password;
	cout<<"Masukkan pilahan anda :";
	cin>>pil;
	
	do{
		cout<<" Masukkan pilahan kamu"<<endl;
		cout<<"1. Isi saldo"<<endl;
		cout<<"2. pilih jenis barang "<<endl;
		cout<<"4. menghapus barang "<<endl;
		cout<<"5. tentukan Alamat "<<endl;
		cout<<"2. Gunakan voucher Diskon "<<endl;
		cout<<"3. Gunakan proteksi "<<endl;
		cout<<"4. Gunakan gratis ongkir "<<endl;
		cout<<"5. pilih ekspedisi "<<endl;
		cin>>pil;
	}
	
	switch(pil){
	case 1; 
		cout<<"Masukkan saldo kamu"<<endl;
		cout<<"1. 300.000"<<endl;
		cout<<"2. 400.000"<<endl;
		cout<<"3. 500.000"<<endl;
		cout<<"4. 600.000"<<endl;
		cout<<"5. 1.000.000"<<endl;
		cin>>saldo;
		break;
	case 2;
		cout<<"jenis barang "<<endl;
		cout<<" 1. pena "<<endl;
		cout<<"2. buku "<<endl;
		cout<<"3. baju"<<endl;
		cout<<"4. cincin"<<endl;
		cout<<"5. celana jiniso"<<endl;
		cin>>jenisbarang;
		break;
	case 3; 
		cout<<"Masukkan barang yang ingin dihapus"<<endl; 
		cout<<"jenis barang "<<endl;
		cout<<" 1. pena "<<endl;
		cout<<"2. buku "<<endl;
		cout<<"3. laptop"<<endl;
		cout<<"4. cincin"<<endl;
		cin>>hapus;
		break;
	case 4;
		cout<<"tentukan Alamat Kamu "<<endl;
		cout<<"1. jalan mawar dekat rumah nadiya "<<endl;
		cout<<"2. jalan kulon progo rumah hijau"<<endl;
		cout<<"3. jalan nitikan umbul harjo"<<endl;
		cout<<"4. jalan tamanan kota masuk gang ainun"<<endl;
		cout<<tentukanAlamatKamu;
		break;
	case 5;
		cout<<"gunakan diskon"endl;
		cout<<"1. Diskon 4% + ainun "<<endl;
		cout<<"2. Diskon 15% "<<endl;
		break;
	default;
		cout<<"pilihan tidak sesuai "<<endl;
		cin>>tidakSesuai;	
	}
 
	return 0;
}
