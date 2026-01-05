#include <iostream>
#include <string>
#include <limits>
#include <fstream>     // ===== TAMBAHAN LOGIN =====
#include <sstream>     // ===== TAMBAHAN LOGIN =====
using namespace std;

// ==================== STRUCT USER LOGIN ====================
struct UserLogin {
    string username;
    string password;
};

// ==================== FUNGSI LOGIN DARI FILE TXT ====================
bool loginSystem() {
    ifstream file("user.txt");
    if (!file.is_open()) {
        cout << "File user.txt tidak ditemukan!\n";
        return false;
    }

    string inputUser, inputPass;
    cout << "=========== LOGIN SISTEM ===========\n";
    cout << "Username: ";
    cin >> inputUser;
    cout << "Password: ";
    cin >> inputPass;

    string line, user, pass;
    while (getline(file, line)) {
        stringstream ss(line);
        ss >> user >> pass;
        if (user == inputUser && pass == inputPass) {
            cout << "\nLogin berhasil. Selamat datang, " << user << "!\n";
            file.close();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return true;
        }
    }

    file.close();
    cout << "\nLogin gagal! Username atau password salah.\n";
    return false;
}

// ==================== CLASS TRANSPORTASI ====================
class Transportasi {
protected:
    string nama;
    string tujuan[3];
    int harga[3];
public:
    Transportasi(string n = "", string t1 = "", string t2 = "", string t3 = "", int h1 = 0, int h2 = 0, int h3 = 0) {
        nama = n;
        tujuan[0] = t1; tujuan[1] = t2; tujuan[2] = t3;
        harga[0] = h1;  harga[1] = h2;  harga[2] = h3;
    }

    void tampilkanMenu() {
        cout << "\n=== Tiket " << nama << " ===" << endl;
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << ". Tujuan " << tujuan[i]
                 << " - Harga: Rp" << harga[i] << endl;
        }
    }

    int getHarga(int pilihan) {
        if (pilihan < 1 || pilihan > 3) return 0;
        return harga[pilihan - 1];
    }

    string getTujuan(int pilihan) {
        if (pilihan < 1 || pilihan > 3) return "";
        return tujuan[pilihan - 1];
    }

    string getNama() {
        return nama;
    }
};

// ==================== DETAIL ENTITIES (Pesawat/Kereta/Bus/Kapal) ====================
// (Sama seperti kode asli, ditaruh sebagai kelas detail)
class PesawatDetail {
public:
    string namaMaskapai;
    string kodePesawat;
    string asal, tujuan;
    string tglBerangkat, blnBerangkat, thnBerangkat, jamBerangkat;
    string tglDatang, blnDatang, thnDatang, jamDatang;
    int harga;

    PesawatDetail(string nama = "", string kode = "", string as = "", string tuju = "",
                  string tglB = "", string blnB = "", string thnB = "", string jamB = "",
                  string tglD = "", string blnD = "", string thnD = "", string jamD = "",
                  int h = 0) {
        namaMaskapai = nama;
        kodePesawat = kode;
        asal = as;
        tujuan = tuju;
        tglBerangkat = tglB; blnBerangkat = blnB; thnBerangkat = thnB; jamBerangkat = jamB;
        tglDatang = tglD; blnDatang = blnD; thnDatang = thnD; jamDatang = jamD;
        harga = h;
    }

    void tampilkanInfo() {
        cout << "Maskapai  : " << namaMaskapai << " (" << kodePesawat << ")\n";
        cout << "Rute      : " << asal << " -> " << tujuan << "\n";
        cout << "Berangkat : " << tglBerangkat << " " << blnBerangkat << " " << thnBerangkat
             << ", Jam " << jamBerangkat << endl;
        cout << "Tiba      : " << tglDatang << " " << blnDatang << " " << thnDatang
             << ", Jam " << jamDatang << endl;
        cout << "Harga     : Rp" << harga << endl;
    }
};

class KeretaDetail {
public:
    string namaKereta, kodeKereta, stasiunAwal, stasiunTujuan;
    string tglBerangkat, blnBerangkat, thnBerangkat, jamBerangkat;
    string tglDatang, blnDatang, thnDatang, jamDatang;
    int harga;

    KeretaDetail(string nama = "", string kode = "", string awal = "", string tujuan = "",
                 string tB = "", string bB = "", string thB = "", string jB = "",
                 string tD = "", string bD = "", string thD = "", string jD = "",
                 int h = 0) {
        namaKereta = nama;
        kodeKereta = kode;
        stasiunAwal = awal;
        stasiunTujuan = tujuan;
        tglBerangkat = tB; blnBerangkat = bB; thnBerangkat = thB; jamBerangkat = jB;
        tglDatang = tD; blnDatang = bD; thnDatang = thD; jamDatang = jD;
        harga = h;
    }

    void tampilkanInfo() {
        cout << "Kereta   : " << namaKereta << " (" << kodeKereta << ")\n";
        cout << "Rute     : " << stasiunAwal << " -> " << stasiunTujuan << "\n";
        cout << "Berangkat: " << tglBerangkat << " " << blnBerangkat << " "
             << thnBerangkat << ", Jam " << jamBerangkat << endl;
        cout << "Tiba     : " << tglDatang << " " << blnDatang << " " << thnDatang
             << ", Jam " << jamDatang << endl;
        cout << "Harga    : Rp" << harga << endl;
    }
};

class BusDetail {
public:
    string namaBus, kodeBus, terminalAwal, terminalTujuan;
    string tglBerangkat, blnBerangkat, thnBerangkat, jamBerangkat;
    string tglDatang, blnDatang, thnDatang, jamDatang;
    int harga;

    BusDetail(string nama = "", string kode = "", string awal = "", string tujuan = "",
              string tB = "", string bB = "", string thB = "", string jB = "",
              string tD = "", string bD = "", string thD = "", string jD = "",
              int h = 0) {
        namaBus = nama;
        kodeBus = kode;
        terminalAwal = awal;
        terminalTujuan = tujuan;
        tglBerangkat = tB; blnBerangkat = bB; thnBerangkat = thB; jamBerangkat = jB;
        tglDatang = tD; blnDatang = bD; thnDatang = thD; jamDatang = jD;
        harga = h;
    }

    void tampilkanInfo() {
        cout << "Bus      : " << namaBus << " (" << kodeBus << ")\n";
        cout << "Rute     : " << terminalAwal << " -> " << terminalTujuan << "\n";
        cout << "Berangkat: " << tglBerangkat << " " << blnBerangkat << " "
             << thnBerangkat << ", Jam " << jamBerangkat << endl;
        cout << "Tiba     : " << tglDatang << " " << blnDatang << " "
             << thnDatang << ", Jam " << jamDatang << endl;
        cout << "Harga    : Rp" << harga << endl;
    }
};

class KapalDetail {
public:
    string namaKapal, kodeKapal, pelabuhanAwal, pelabuhanTujuan;
    string tglBerangkat, blnBerangkat, thnBerangkat, jamBerangkat;
    string tglDatang, blnDatang, thnDatang, jamDatang;
    int harga;

    KapalDetail(string nama = "", string kode = "", string awal = "", string tujuan = "",
                string tB = "", string bB = "", string thB = "", string jB = "",
                string tD = "", string bD = "", string thD = "", string jD = "",
                int h = 0) {
        namaKapal = nama;
        kodeKapal = kode;
        pelabuhanAwal = awal;
        pelabuhanTujuan = tujuan;
        tglBerangkat = tB; blnBerangkat = bB; thnBerangkat = thB; jamBerangkat = jB;
        tglDatang = tD; blnDatang = bD; thnDatang = thD; jamDatang = jD;
        harga = h;
    }

    void tampilkanInfo() {
        cout << "Kapal     : " << namaKapal << " (" << kodeKapal << ")\n";
        cout << "Rute      : " << pelabuhanAwal << " -> " << pelabuhanTujuan << "\n";
        cout << "Berangkat : " << tglBerangkat << " " << blnBerangkat << " "
             << thnBerangkat << ", Jam " << jamBerangkat << endl;
        cout << "Tiba      : " << tglDatang << " " << blnDatang << " "
             << thnDatang << ", Jam " << jamDatang << endl;
        cout << "Harga     : Rp" << harga << endl;
    }
};

// ==================== UTIL: rekursi total harga ====================
// ==================== STRUCT TIKET (CETAK OUTPUT) ====================
struct Tiket {
    string namaPemesan;
    string transportasi;
    string rute;
    string tanggal;
    string jam;
    string metodeBayar;
    int jumlah;
    int total;
};

int hitungTotal(int harga[], int n) {
	
    if (n == 0) return 0;
    return harga[n - 1] + hitungTotal(harga, n - 1);
}

// ==================== PEMBAYARAN ====================
bool prosesPembayaran(Tiket &t) {
    int pilih;
    cout << "\n=== METODE PEMBAYARAN ===\n";
    cout << "1. Cash\n";
    cout << "2. Transfer\n";
    cout << "Pilih: ";
    cin >> pilih;
    cin.ignore();

    if (pilih == 1) {
        t.metodeBayar = "Cash";
        cout << "Pembayaran cash diterima.\n";
    }
    else if (pilih == 2) {
        t.metodeBayar = "Transfer";
        cout << "Silakan transfer ke VA 123-456-789\n";
        cout << "Pembayaran berhasil diverifikasi.\n";
    }
    else {
        cout << "Metode tidak valid!\n";
        return false;
    }
    return true;
}

// ==================== CETAK TIKET ====================
void cetakTiket(const Tiket &t) {
    cout << "\n=========================================\n";
    cout << "          TIKET TRANSPORTASI\n";
    cout << "=========================================\n";
    cout << "Nama Pemesan : " << t.namaPemesan << endl;
    cout << "Transportasi : " << t.transportasi << endl;
    cout << "Rute         : " << t.rute << endl;
    cout << "Tanggal      : " << t.tanggal << endl;
    cout << "Jam          : " << t.jam << endl;
    cout << "Jumlah Tiket : " << t.jumlah << endl;
    cout << "Total Bayar  : Rp" << t.total << endl;
    cout << "Metode Bayar : " << t.metodeBayar << endl;
    cout << "=========================================\n";
}

// ==================== DOUBLE LINKED LIST FOR PEMESANAN (Pengganti SINGLE) ====================
struct BookingNode {
    string namaPemesan;
    string namaTransportasi;
    string tujuan;
    int jumlahTiket;
    int totalHarga;
    BookingNode* next;
    BookingNode* prev;
    BookingNode(string np = "", string nt = "", string tu = "", int j = 0, int t = 0)
        : namaPemesan(np), namaTransportasi(nt), tujuan(tu), jumlahTiket(j), totalHarga(t),
          next(NULL), prev(NULL) {}
};

BookingNode* bookingHead = NULL;
BookingNode* bookingTail = NULL;

void tambahPemesananDLL(const string& namaPemesan, const string& transport, const string& tujuan, int jumlah, int total) {
    BookingNode* baru = new BookingNode(namaPemesan, transport, tujuan, jumlah, total);
    if (bookingHead == NULL) {
        bookingHead = bookingTail = baru;
    } else {
        bookingTail->next = baru;
        baru->prev = bookingTail;
        bookingTail = baru;
    }
}

void tampilkanRiwayatDLL() {
    if (bookingHead == NULL) {
        cout << "\nBelum ada riwayat pemesanan.\n";
        return;
    }
    cout << "\n=========== RIWAYAT PEMESANAN (Double Linked List) ===========\n";
    BookingNode* temp = bookingHead;
    int no = 1;
    while (temp != NULL) {
        cout << no++ << ". " << temp->namaPemesan << " | " << temp->namaTransportasi
             << " | " << temp->tujuan << " | Tiket: " << temp->jumlahTiket
             << " | Total: Rp" << temp->totalHarga << endl;
        temp = temp->next;
    }
}

void cariPemesananDLL(const string& namaCari) {
    BookingNode* temp = bookingHead;
    bool ketemu = false;
    cout << "\nHasil pencarian untuk '" << namaCari << "':\n";
    while (temp != NULL) {
        if (temp->namaPemesan == namaCari) {
            cout << "Nama: " << temp->namaPemesan
                 << " | Transportasi: " << temp->namaTransportasi
                 << " | Tujuan: " << temp->tujuan
                 << " | Tiket: " << temp->jumlahTiket
                 << " | Total: Rp" << temp->totalHarga << endl;
            ketemu = true;
        }
        temp = temp->next;
    }
    if (!ketemu) cout << "Data tidak ditemukan.\n";
}

void ubahPemesananDLL(const string& namaUbah) {
    BookingNode* temp = bookingHead;
    bool ketemu = false;
    while (temp != NULL) {
        if (temp->namaPemesan == namaUbah) {
            cout << "\nData ditemukan. Masukkan data baru:\n";
            cout << "Nama baru: ";
            getline(cin, temp->namaPemesan);
            cout << "Transportasi baru: ";
            getline(cin, temp->namaTransportasi);
            cout << "Tujuan baru: ";
            getline(cin, temp->tujuan);
            cout << "Jumlah tiket baru: ";
            while (!(cin >> temp->jumlahTiket)) {
                cout << "Masukkan angka untuk jumlah tiket: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Total harga baru: ";
            while (!(cin >> temp->totalHarga)) {
                cout << "Masukkan angka untuk total harga: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Data berhasil diubah!\n";
            ketemu = true;
            break;
        }
        temp = temp->next;
    }
    if (!ketemu) cout << "Data tidak ditemukan.\n";
}

void hapusPemesananDLL(const string& namaHapus) {
    if (bookingHead == NULL) {
        cout << "Belum ada data.\n";
        return;
    }
    BookingNode* temp = bookingHead;
    while (temp != NULL && temp->namaPemesan != namaHapus) {
        temp = temp->next;
    }
    if (temp == NULL) {
        cout << "Data tidak ditemukan.\n";
        return;
    }
    if (temp->prev != NULL) temp->prev->next = temp->next;
    else bookingHead = temp->next;

    if (temp->next != NULL) temp->next->prev = temp->prev;
    else bookingTail = temp->prev;

    delete temp;
    cout << "Data berhasil dihapus!\n";
}

// ==================== DOUBLE LINKED LIST (CIRCULAR) ====================
// We'll implement circular DLL where tail->next = head and head->prev = tail
struct CircularDLLNode {
    string namaPemesan;
    string namaTransportasi;
    string tujuan;
    int jumlahTiket;
    int totalHarga;
    CircularDLLNode* next;
    CircularDLLNode* prev;
    CircularDLLNode(string np = "", string nt = "", string tu = "", int j = 0, int t = 0)
        : namaPemesan(np), namaTransportasi(nt), tujuan(tu), jumlahTiket(j), totalHarga(t),
          next(NULL), prev(NULL) {}
};

CircularDLLNode* circHead = NULL;
CircularDLLNode* circTail = NULL;

void tambahCircularDLL(const string& namaPemesan, const string& transport, const string& tujuan, int jumlah, int total) {
    CircularDLLNode* baru = new CircularDLLNode(namaPemesan, transport, tujuan, jumlah, total);
    if (circHead == NULL) {
        circHead = circTail = baru;
        circHead->next = circHead->prev = circHead;
    } else {
        circTail->next = baru;
        baru->prev = circTail;
        baru->next = circHead;
        circHead->prev = baru;
        circTail = baru;
    }
}

void tampilkanCircularDLL() {
    if (circHead == NULL) {
        cout << "\nBelum ada data Circular Linked List.\n";
        return;
    }
    cout << "\n=========== RIWAYAT PEMESANAN (Circular Double Linked List) ===========\n";
    CircularDLLNode* temp = circHead;
    int no = 1;
    do {
        cout << no++ << ". " << temp->namaPemesan
             << " | " << temp->namaTransportasi
             << " | " << temp->tujuan
             << " | Tiket: " << temp->jumlahTiket
             << " | Total: Rp" << temp->totalHarga << endl;
        temp = temp->next;
    } while (temp != circHead);
}

void cariCircularDLL(const string& namaCari) {
    if (circHead == NULL) {
        cout << "Belum ada data Circular Linked List.\n";
        return;
    }
    CircularDLLNode* temp = circHead;
    bool ketemu = false;
    cout << "\nHasil pencarian Circular untuk '" << namaCari << "':\n";
    do {
        if (temp->namaPemesan == namaCari) {
            cout << "Nama: " << temp->namaPemesan
                 << " | Transportasi: " << temp->namaTransportasi
                 << " | Tujuan: " << temp->tujuan
                 << " | Tiket: " << temp->jumlahTiket
                 << " | Total: Rp" << temp->totalHarga << endl;
            ketemu = true;
        }
        temp = temp->next;
    } while (temp != circHead);
    if (!ketemu) cout << "Data tidak ditemukan.\n";
}

void ubahCircularDLL(const string& namaUbah) {
    if (circHead == NULL) {
        cout << "Belum ada data Circular.\n";
        return;
    }
    CircularDLLNode* temp = circHead;
    bool ketemu = false;
    do {
        if (temp->namaPemesan == namaUbah) {
            cout << "\nData ditemukan. Masukkan data baru:\n";
            cout << "Nama baru: ";
            getline(cin, temp->namaPemesan);
            cout << "Transportasi baru: ";
            getline(cin, temp->namaTransportasi);
            cout << "Tujuan baru: ";
            getline(cin, temp->tujuan);
            cout << "Jumlah tiket baru: ";
            while (!(cin >> temp->jumlahTiket)) {
                cout << "Masukkan angka untuk jumlah tiket: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Total harga baru: ";
            while (!(cin >> temp->totalHarga)) {
                cout << "Masukkan angka untuk total harga: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Data berhasil diubah!\n";
            ketemu = true;
            break;
        }
        temp = temp->next;
    } while (temp != circHead);
    if (!ketemu) cout << "Data tidak ditemukan.\n";
}

void hapusCircularDLL(const string& namaHapus) {
    if (circHead == NULL) {
        cout << "Belum ada data Circular.\n";
        return;
    }
    CircularDLLNode* temp = circHead;
    CircularDLLNode* found = NULL;
    do {
        if (temp->namaPemesan == namaHapus) { found = temp; break; }
        temp = temp->next;
    } while (temp != circHead);

    if (found == NULL) {
        cout << "Data tidak ditemukan.\n";
        return;
    }

    if (found->next == found && found->prev == found) {
        // only node
        delete found;
        circHead = circTail = NULL;
    } else {
        found->prev->next = found->next;
        found->next->prev = found->prev;
        if (found == circHead) circHead = found->next;
        if (found == circTail) circTail = found->prev;
        delete found;
    }

    cout << "Data berhasil dihapus dari Circular Linked List!\n";
}

// ==================== DOUBLE LINKED LIST FOR STACK (LIFO) ====================
// Implement stack behaviour using DLL: push adds at head, pop removes head.
struct StackDLLNode {
    string namaPemesan;
    string namaTransportasi;
    string tujuan;
    int jumlahTiket;
    int totalHarga;
    StackDLLNode* next;
    StackDLLNode* prev;
    StackDLLNode(string np = "", string nt = "", string tu = "", int j = 0, int t = 0)
        : namaPemesan(np), namaTransportasi(nt), tujuan(tu), jumlahTiket(j), totalHarga(t),
          next(NULL), prev(NULL) {}
};

StackDLLNode* stackHead = NULL; // top of stack
StackDLLNode* stackTail = NULL; // not strictly needed but kept for cleanup

void pushStackDLL(const string& nama, const string& trans, const string& tujuan, int jumlah, int total) {
    StackDLLNode* baru = new StackDLLNode(nama, trans, tujuan, jumlah, total);
    if (stackHead == NULL) {
        stackHead = stackTail = baru;
    } else {
        baru->next = stackHead;
        stackHead->prev = baru;
        stackHead = baru;
    }
    cout << "\n(PUSH) Riwayat transaksi ditambahkan ke STACK (DLL).\n";
}

void popStackDLL() {
    if (stackHead == NULL) {
        cout << "\nSTACK kosong! Tidak ada transaksi yang dapat dibatalkan.\n";
        return;
    }
    StackDLLNode* hapus = stackHead;
    stackHead = stackHead->next;
    if (stackHead != NULL) stackHead->prev = NULL;
    else stackTail = NULL;

    cout << "\n(POP) Transaksi terakhir dibatalkan!\n";
    cout << "Nama: " << hapus->namaPemesan << endl;
    cout << "Transportasi: " << hapus->namaTransportasi << endl;
    cout << "Tujuan: " << hapus->tujuan << endl;
    cout << "Tiket: " << hapus->jumlahTiket << endl;
    cout << "Total: Rp" << hapus->totalHarga << endl;

    delete hapus;
}

void tampilkanStackDLL() {
    if (stackHead == NULL) {
        cout << "\nSTACK kosong! Belum ada riwayat transaksi.\n";
        return;
    }
    cout << "\n=========== STACK RIWAYAT TRANSAKSI (DLL) ===========\n";
    StackDLLNode* temp = stackHead;
    int no = 1;
    while (temp != NULL) {
        cout << no++ << ". " << temp->namaPemesan
             << " | " << temp->namaTransportasi
             << " | " << temp->tujuan
             << " | Tiket: " << temp->jumlahTiket
             << " | Total: Rp" << temp->totalHarga << endl;
        temp = temp->next;
    }
}

void clearStackDLL() {
    while (stackHead != NULL) {
        StackDLLNode* temp = stackHead;
        stackHead = stackHead->next;
        delete temp;
    }
    stackTail = NULL;
}

// ==================== DOUBLE LINKED LIST FOR PRIORITAS (sudah ada konsep DLL) ====================
struct PriorityNode {
    string namaPemesan;
    string keterangan;
    PriorityNode* next;
    PriorityNode* prev;
    PriorityNode(string n = "", string k = "") : namaPemesan(n), keterangan(k), next(NULL), prev(NULL) {}
};

PriorityNode* prioHead = NULL;
PriorityNode* prioTail = NULL;

void tambahPrioritasDLL(const string& nama, const string& ket) {
    PriorityNode* baru = new PriorityNode(nama, ket);
    if (prioHead == NULL) {
        prioHead = prioTail = baru;
    } else {
        prioTail->next = baru;
        baru->prev = prioTail;
        prioTail = baru;
    }
}

void tampilkanPrioritasMajuDLL() {
    if (prioHead == NULL) {
        cout << "\nDaftar Prioritas kosong.\n";
        return;
    }
    cout << "\n======== DAFTAR PRIORITAS (Maju) ========\n";
    PriorityNode* temp = prioHead;
    int no = 1;
    while (temp != NULL) {
        cout << no++ << ". " << temp->namaPemesan
             << " | Status: " << temp->keterangan << endl;
        temp = temp->next;
    }
}

void tampilkanPrioritasMundurDLL() {
    if (prioTail == NULL) {
        cout << "\nDaftar Prioritas kosong.\n";
        return;
    }
    cout << "\n======== DAFTAR PRIORITAS (Mundur) ========\n";
    PriorityNode* temp = prioTail;
    int no = 1;
    while (temp != NULL) {
        cout << no++ << ". " << temp->namaPemesan
             << " | Status: " << temp->keterangan << endl;
        temp = temp->prev;
    }
}

// ==================== QUEUE DOUBLE LINKED LIST (FIFO) ====================
struct QueueDLLNode {
    string namaPemesan;
    string namaTransportasi;
    string tujuan;
    int jumlahTiket;
    int totalHarga;
    QueueDLLNode* next;
    QueueDLLNode* prev;

    QueueDLLNode(string n="", string tr="", string t="", int j=0, int total=0) {
        namaPemesan = n;
        namaTransportasi = tr;
        tujuan = t;
        jumlahTiket = j;
        totalHarga = total;
        next = prev = NULL;
    }
};

QueueDLLNode* queueFront = NULL;
QueueDLLNode* queueRear  = NULL;

// ENQUEUE (tambah dari belakang)
void enqueueQueueDLL(string nama, string trans, string tujuan, int jumlah, int total) {
    QueueDLLNode* baru = new QueueDLLNode(nama, trans, tujuan, jumlah, total);
    if (queueFront == NULL) {
        queueFront = queueRear = baru;
    } else {
        queueRear->next = baru;
        baru->prev = queueRear;
        queueRear = baru;
    }
    cout << "\n(QUEUE) Data masuk ke antrian.\n";
}

// DEQUEUE (hapus dari depan)
void dequeueQueueDLL() {
    if (queueFront == NULL) {
        cout << "\nQUEUE kosong!\n";
        return;
    }

    QueueDLLNode* hapus = queueFront;
    cout << "\n(DEQUEUE) Melayani antrian:\n";
    cout << "Nama : " << hapus->namaPemesan << endl;
    cout << "Transportasi : " << hapus->namaTransportasi << endl;
    cout << "Tujuan : " << hapus->tujuan << endl;
    cout << "Total : Rp" << hapus->totalHarga << endl;

    queueFront = queueFront->next;
    if (queueFront != NULL)
        queueFront->prev = NULL;
    else
        queueRear = NULL;

    delete hapus;
}

// TAMPILKAN QUEUE
void tampilkanQueueDLL() {
    if (queueFront == NULL) {
        cout << "\nQUEUE kosong.\n";
        return;
    }
    cout << "\n=========== ANTRIAN PEMESANAN (QUEUE DLL) ===========\n";
    QueueDLLNode* temp = queueFront;
    int no = 1;
    while (temp != NULL) {
        cout << no++ << ". " << temp->namaPemesan
             << " | " << temp->namaTransportasi
             << " | " << temp->tujuan
             << " | Tiket: " << temp->jumlahTiket
             << " | Total: Rp" << temp->totalHarga << endl;
        temp = temp->next;
    }
}

// ==================== HUFFMAN CODING (DOUBLE LINKED LIST) ====================
struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode* next;
    HuffmanNode* prev;

    HuffmanNode(char d, int f) {
        data = d;
        freq = f;
        left = right = NULL;
        next = prev = NULL;
    }
};

HuffmanNode* huffHead = NULL;
HuffmanNode* huffTail = NULL;

void resetHuffman() {
    huffHead = NULL;
    huffTail = NULL;
}

void tambahHuffmanDLL(HuffmanNode* node) {
    if (huffHead == NULL) {
        huffHead = huffTail = node;
    } else {
        huffTail->next = node;
        node->prev = huffTail;
        huffTail = node;
    }
}

void hitungFrekuensi(const string& teks, int freq[]) {
    for (char c : teks) {
        freq[(int)c]++;
    }
}

void buildHuffmanDLL(const string& teks) {
    int freq[256] = {0};
    hitungFrekuensi(teks, freq);

    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            tambahHuffmanDLL(new HuffmanNode((char)i, freq[i]));
        }
    }
}

HuffmanNode* ambilMinNode() {
    if (huffHead == NULL) return NULL;

    HuffmanNode* minNode = huffHead;
    HuffmanNode* temp = huffHead;

    while (temp != NULL) {
        if (temp->freq < minNode->freq)
            minNode = temp;
        temp = temp->next;
    }

    // Lepas dari DLL
    if (minNode->prev)
        minNode->prev->next = minNode->next;
    else
        huffHead = minNode->next;

    if (minNode->next)
        minNode->next->prev = minNode->prev;
    else
        huffTail = minNode->prev;

    minNode->next = minNode->prev = NULL;
    return minNode;
}

HuffmanNode* buildHuffmanTree() {
    while (huffHead != huffTail) {
        HuffmanNode* left = ambilMinNode();
        HuffmanNode* right = ambilMinNode();

        HuffmanNode* parent = new HuffmanNode('#', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        tambahHuffmanDLL(parent);
    }
    return huffHead;
}

void cetakKodeHuffman(HuffmanNode* root, string kode) {
    if (!root) return;

    if (root->data != '#') {
        cout << root->data << " : " << kode << endl;
    }

    cetakKodeHuffman(root->left, kode + "0");
    cetakKodeHuffman(root->right, kode + "1");
}

void menuHuffman() {
    string teks;
    cout << "\n=== HUFFMAN CODING ===\n";
    cout << "Masukkan teks yang akan dikompresi: ";
    getline(cin, teks);

    if (teks.empty()) {
        cout << "Teks kosong!\n";
        return;
    }

    resetHuffman();          // 🔥 penting
    buildHuffmanDLL(teks);
    HuffmanNode* root = buildHuffmanTree();

    cout << "\nKode Huffman:\n";
    cetakKodeHuffman(root, "");
}


// ==================== BINARY TREE DARI DOUBLE LINKED LIST ====================
struct TreeNode {
    string namaPemesan;
    int totalHarga;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string n = "", int t = 0) {
        namaPemesan = n;
        totalHarga = t;
        left = right = NULL;
    }
};

TreeNode* rootTree = NULL;

// ==================== SKEWED TREE (DARI DOUBLE LINKED LIST) ====================
TreeNode* skewedLeftRoot = NULL;
TreeNode* skewedRightRoot = NULL;


// INSERT KE BINARY TREE (BERDASARKAN TOTAL HARGA)
TreeNode* insertTree(TreeNode* root, string nama, int total) {
    if (root == NULL) {
        return new TreeNode(nama, total);
    }
    if (total < root->totalHarga)
        root->left = insertTree(root->left, nama, total);
    else
        root->right = insertTree(root->right, nama, total);

    return root;
}

// BANGUN TREE DARI DOUBLE LINKED LIST
void buildTreeFromDLL() {
    rootTree = NULL;
    BookingNode* temp = bookingHead;
    while (temp != NULL) {
        rootTree = insertTree(rootTree, temp->namaPemesan, temp->totalHarga);
        temp = temp->next;
    }
    cout << "\nBinary Tree berhasil dibangun dari Double Linked List.\n";
}

// ==================== BANGUN SKEWED TREE ====================

// Skewed Left Tree (menurun ke kiri)
void buildSkewedLeftTree() {
    skewedLeftRoot = NULL;
    BookingNode* temp = bookingHead;
    TreeNode* prev = NULL;

    while (temp != NULL) {
        TreeNode* node = new TreeNode(temp->namaPemesan, temp->totalHarga);
        if (skewedLeftRoot == NULL) {
            skewedLeftRoot = node;
        } else {
            prev->left = node;
        }
        prev = node;
        temp = temp->next;
    }
    cout << "\nSkewed Left Tree berhasil dibangun.\n";
}

// Skewed Right Tree (menurun ke kanan)
void buildSkewedRightTree() {
    skewedRightRoot = NULL;
    BookingNode* temp = bookingHead;
    TreeNode* prev = NULL;

    while (temp != NULL) {
        TreeNode* node = new TreeNode(temp->namaPemesan, temp->totalHarga);
        if (skewedRightRoot == NULL) {
            skewedRightRoot = node;
        } else {
            prev->right = node;
        }
        prev = node;
        temp = temp->next;
    }
    cout << "\nSkewed Right Tree berhasil dibangun.\n";
}

// ==================== TRAVERSAL ====================
void inorder(TreeNode* node) {
    if (node != NULL) {
        inorder(node->left);
        cout << node->namaPemesan << " | Rp" << node->totalHarga << endl;
        inorder(node->right);
    }
}

void preorder(TreeNode* node) {
    if (node != NULL) {
        cout << node->namaPemesan << " | Rp" << node->totalHarga << endl;
        preorder(node->left);
        preorder(node->right);
    }
}

void postorder(TreeNode* node) {
    if (node != NULL) {
        postorder(node->left);
        postorder(node->right);
        cout << node->namaPemesan << " | Rp" << node->totalHarga << endl;
    }
}

// ==================== MENU EKSPLORASI TREE ====================
void eksplorasiBinaryTree() {
    if (bookingHead == NULL) {
        cout << "\nData kosong! Tidak bisa membangun Binary Tree.\n";
        return;
    }

    buildTreeFromDLL();

    int pilih;
    do {
        cout << "\n====== EKSPLORASI BINARY TREE ======\n";
        cout << "1. Inorder Traversal\n";
        cout << "2. Preorder Traversal\n";
        cout << "3. Postorder Traversal\n";
        cout << "4. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;
        cin.ignore();

        if (pilih == 1) {
            cout << "\n--- INORDER ---\n";
            inorder(rootTree);
        }
        else if (pilih == 2) {
            cout << "\n--- PREORDER ---\n";
            preorder(rootTree);
        }
        else if (pilih == 3) {
            cout << "\n--- POSTORDER ---\n";
            postorder(rootTree);
        }
    } while (pilih != 4);
}

// ==================== MENU EKSPLORASI SKEWED TREE ====================
void eksplorasiSkewedTree() {
    if (bookingHead == NULL) {
        cout << "\nData kosong! Tidak bisa membangun Skewed Tree.\n";
        return;
    }

    int pilih;
    do {
        cout << "\n====== EKSPLORASI SKEWED TREE ======\n";
        cout << "1. Skewed Left Tree (Inorder)\n";
        cout << "2. Skewed Right Tree (Inorder)\n";
        cout << "3. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;
        cin.ignore();

        if (pilih == 1) {
            buildSkewedLeftTree();
            cout << "\n--- INORDER SKEWED LEFT ---\n";
            inorder(skewedLeftRoot);
        }
        else if (pilih == 2) {
            buildSkewedRightTree();
            cout << "\n--- INORDER SKEWED RIGHT ---\n";
            inorder(skewedRightRoot);
        }
    } while (pilih != 3);
}

// ==================== AVL TREE (DARI DOUBLE LINKED LIST) ====================
struct AVLNode {
    string namaPemesan;
    int totalHarga;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(string n = "", int t = 0) {
        namaPemesan = n;
        totalHarga = t;
        height = 1;
        left = right = NULL;
    }
};

AVLNode* avlRoot = NULL;

// ==================== UTIL AVL ====================
int heightAVL(AVLNode* node) {
    if (node == NULL) return 0;
    return node->height;
}

int getBalance(AVLNode* node) {
    if (node == NULL) return 0;
    return heightAVL(node->left) - heightAVL(node->right);
}

int maxAVL(int a, int b) {
    return (a > b) ? a : b;
}

// ==================== ROTASI AVL ====================
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = maxAVL(heightAVL(y->left), heightAVL(y->right)) + 1;
    x->height = maxAVL(heightAVL(x->left), heightAVL(x->right)) + 1;

    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = maxAVL(heightAVL(x->left), heightAVL(x->right)) + 1;
    y->height = maxAVL(heightAVL(y->left), heightAVL(y->right)) + 1;

    return y;
}

// ==================== INSERT AVL ====================
AVLNode* insertAVL(AVLNode* node, string nama, int total) {
    if (node == NULL)
        return new AVLNode(nama, total);

    if (total < node->totalHarga)
        node->left = insertAVL(node->left, nama, total);
    else if (total > node->totalHarga)
        node->right = insertAVL(node->right, nama, total);
    else
        return node;

    node->height = 1 + maxAVL(heightAVL(node->left), heightAVL(node->right));

    int balance = getBalance(node);

    // Left Left
    if (balance > 1 && total < node->left->totalHarga)
        return rightRotate(node);

    // Right Right
    if (balance < -1 && total > node->right->totalHarga)
        return leftRotate(node);

    // Left Right
    if (balance > 1 && total > node->left->totalHarga) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left
    if (balance < -1 && total < node->right->totalHarga) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// ==================== BANGUN AVL DARI DOUBLE LINKED LIST ====================
void buildAVLFromDLL() {
    avlRoot = NULL;
    BookingNode* temp = bookingHead;
    while (temp != NULL) {
        avlRoot = insertAVL(avlRoot, temp->namaPemesan, temp->totalHarga);
        temp = temp->next;
    }
    cout << "\nAVL Tree berhasil dibangun dari Double Linked List.\n";
}

// ==================== TRAVERSAL AVL ====================
void inorderAVL(AVLNode* node) {
    if (node != NULL) {
        inorderAVL(node->left);
        cout << node->namaPemesan << " | Rp" << node->totalHarga << endl;
        inorderAVL(node->right);
    }
}

void preorderAVL(AVLNode* node) {
    if (node != NULL) {
        cout << node->namaPemesan << " | Rp" << node->totalHarga << endl;
        preorderAVL(node->left);
        preorderAVL(node->right);
    }
}

void postorderAVL(AVLNode* node) {
    if (node != NULL) {
        postorderAVL(node->left);
        postorderAVL(node->right);
        cout << node->namaPemesan << " | Rp" << node->totalHarga << endl;
    }
}

// ==================== MENU EKSPLORASI AVL TREE ====================
void eksplorasiAVLTree() {
    if (bookingHead == NULL) {
        cout << "\nData kosong! Tidak bisa membangun AVL Tree.\n";
        return;
    }

    buildAVLFromDLL();

    int pilih;
    do {
        cout << "\n====== EKSPLORASI AVL TREE ======\n";
        cout << "1. Inorder Traversal\n";
        cout << "2. Preorder Traversal\n";
        cout << "3. Postorder Traversal\n";
        cout << "4. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;
        cin.ignore();

        if (pilih == 1) {
            cout << "\n--- INORDER AVL ---\n";
            inorderAVL(avlRoot);
        }
        else if (pilih == 2) {
            cout << "\n--- PREORDER AVL ---\n";
            preorderAVL(avlRoot);
        }
        else if (pilih == 3) {
            cout << "\n--- POSTORDER AVL ---\n";
            postorderAVL(avlRoot);
        }
    } while (pilih != 4);
}

// ==================== MAIN PROGRAM ====================
int main() {
    // ===== LOGIN USER (DITAMBAHKAN TANPA MENGUBAH KODE LAMA) =====
    if (!loginSystem()) {
        return 0;
    }

    int pilihanMenu, pilihanTransport, jumlahTiket;
    string namaPemesan;

    string daftarTransportasi[4] = {"Pesawat", "Kereta", "Bus", "Kapal"};

    do {
        cout << "\n========================================\n";
        cout << "  SISTEM PEMESANAN TIKET TRANSPORTASI\n";
        cout << "========================================\n";
        cout << "1. Pesan Tiket (CREATE)\n";
        cout << "2. Tampilkan Riwayat (Double Linked List)\n";
        cout << "3. Cari Data Pemesanan (SEARCH)\n";
        cout << "4. Ubah Data Pemesanan (UPDATE)\n";
        cout << "5. Hapus Data Pemesanan (DELETE)\n";
        cout << "6. Kelola Riwayat Selesai (Circular DLL)\n";
        cout << "7. Kelola Daftar Prioritas (Double Linked List)\n";
        cout << "8. Kelola Stack Riwayat Transaksi (DLL)\n";
        cout << "9. Kelola Antrian Pemesanan (QUEUE DLL)\n";
        cout << "10. Eksplorasi Binary Tree (Dari Double Linked List)\n";
        cout << "11. Eksplorasi Skewed Tree (Double Linked List)\n";
        cout << "12. Eksplorasi AVL Tree (Double Linked List)\n";
        cout << "13. Huffman Coding (Kompresi Data)\n";
        cout << "14. Keluar\n";
        cout << "Pilih menu: ";
        if (!(cin >> pilihanMenu)) {
            cout << "Masukkan angka yang valid!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pilihanMenu == 1) {
            cout << "\nDaftar Transportasi (Array Statis):\n";
            for (int i = 0; i < 4; i++)
                cout << i + 1 << ". " << daftarTransportasi[i] << endl;

            Transportasi pesawat("Pesawat", "Jakarta", "Bali", "Surabaya", 1500000, 1200000, 900000);
            Transportasi kereta("Kereta", "Bandung", "Yogyakarta", "Malang", 300000, 350000, 400000);
            Transportasi bus("Bus", "Semarang", "Solo", "Tegal", 150000, 170000, 120000);
            Transportasi kapal("Kapal", "Makassar", "Balikpapan", "Ambon", 700000, 850000, 950000);

            // Detail Pesawat
            PesawatDetail flight1("Garuda", "GA-123", "Jakarta", "Bali", "5", "Nov", "2025", "08:00",
                                  "5", "Nov", "2025", "10:30", 1500000);
            PesawatDetail flight2("Lion Air", "JT-456", "Jakarta", "Surabaya", "6", "Nov", "2025", "09:00",
                                  "6", "Nov", "2025", "10:15", 900000);
            PesawatDetail flight3("Air Asia", "QZ-789", "Bandung", "Bali", "7", "Nov", "2025", "11:00",
                                  "7", "Nov", "2025", "13:20", 1200000);
            PesawatDetail flights[] = {flight1, flight2, flight3};

            cout << "\nPilih jenis transportasi (1-4): ";
            if (!(cin >> pilihanTransport)) {
                cout << "Input tidak valid.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nMasukkan nama pemesan: ";
            getline(cin, namaPemesan);
            Tiket tiket;
			tiket.namaPemesan = namaPemesan;


            // PESAWAT
            if (pilihanTransport == 1) {
                cout << "\n=== Pilih Penerbangan Tersedia ===\n";
                cout << "1.\n"; flights[0].tampilkanInfo();
                cout << "\n2.\n"; flights[1].tampilkanInfo();
                cout << "\n3.\n"; flights[2].tampilkanInfo();

                int pilihanPesawat;
                cout << "\nPilih penerbangan (1-3): ";
                if (!(cin >> pilihanPesawat)) {
                    cout << "Input tidak valid.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (pilihanPesawat < 1 || pilihanPesawat > 3) {
                    cout << "Pilihan tidak valid!\n";
                    continue;
                }

                PesawatDetail* pilihan = &flights[pilihanPesawat - 1];

                cout << "Masukkan jumlah tiket: ";
                if (!(cin >> jumlahTiket) || jumlahTiket <= 0) {
                    cout << "Jumlah tiket tidak valid.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                int* daftarHarga = new int[jumlahTiket];
                for (int i = 0; i < jumlahTiket; i++)
                    daftarHarga[i] = pilihan->harga;

                string* namaPenumpang = new string[jumlahTiket];
                cout << "\nMasukkan nama penumpang:\n";
                for (int i = 0; i < jumlahTiket; i++) {
                    cout << "Penumpang ke-" << i + 1 << ": ";
                    getline(cin, namaPenumpang[i]);
                }

                int total = hitungTotal(daftarHarga, jumlahTiket);
                tiket.transportasi = daftarTransportasi[pilihanTransport - 1];
				tiket.jumlah = jumlahTiket;
				tiket.total = total;
				tiket.rute = "Sesuai pilihan";
				tiket.tanggal = "Sesuai jadwal";
				tiket.jam = "Sesuai jadwal";
				
				if (!prosesPembayaran(tiket)) {
    cout << "Transaksi dibatalkan.\n";
    delete[] namaPenumpang;
    break;
}

char cetak;
cout << "Cetak tiket? (Y/N): ";
cin >> cetak;
cin.ignore();

if (cetak == 'Y' || cetak == 'y') {
    cetakTiket(tiket);
}

string namaTujuan = pilihan->asal + " ke " + pilihan->tujuan;

// ==================== SIMPAN KE STRUKTUR DATA ====================
tambahPemesananDLL(
    tiket.namaPemesan,
    tiket.transportasi,
    namaTujuan,
    tiket.jumlah,
    tiket.total
);

// OPSIONAL (nilai plus)
tambahCircularDLL(
    tiket.namaPemesan,
    tiket.transportasi,
    namaTujuan,
    tiket.jumlah,
    tiket.total
);

pushStackDLL(
    tiket.namaPemesan,
    tiket.transportasi,
    namaTujuan,
    tiket.jumlah,
    tiket.total
);

enqueueQueueDLL(
    tiket.namaPemesan,
    tiket.transportasi,
    tiket.rute,
    tiket.jumlah,
    tiket.total
);

cout << "\nPemesanan berhasil ditambahkan.\n";

// ==================== HUFFMAN COMPRESSION ====================
cout << "\n=== HUFFMAN CODING (Nama Pemesan) ===\n";
buildHuffmanDLL(tiket.namaPemesan);
HuffmanNode* huffRoot = buildHuffmanTree();
cetakKodeHuffman(huffRoot, "");

delete[] daftarHarga;
delete[] namaPenumpang;
}

				
            // KERETA
            else if (pilihanTransport == 2) {
                KeretaDetail k1("Argo Bromo", "KA-101", "Jakarta", "Surabaya",
                                "10", "Nov", "2025", "07:30",
                                "10", "Nov", "2025", "15:45", 350000);
                KeretaDetail k2("Taksaka", "KA-202", "Yogyakarta", "Bandung",
                                "11", "Nov", "2025", "09:00",
                                "11", "Nov", "2025", "16:20", 300000);
                KeretaDetail k3("Mutiara Selatan", "KA-303", "Bandung", "Malang",
                                "12", "Nov", "2025", "06:45",
                                "12", "Nov", "2025", "18:30", 400000);

                KeretaDetail daftarKereta[] = {k1, k2, k3};

                cout << "\n=== Pilih Jadwal Kereta ===\n";
                for (int i = 0; i < 3; i++) {
                    cout << "\n" << i + 1 << ". ";
                    daftarKereta[i].tampilkanInfo();
                }

                int pilihanKereta;
                cout << "\nPilih kereta (1-3): ";
                if (!(cin >> pilihanKereta)) {
                    cout << "Input tidak valid.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (pilihanKereta < 1 || pilihanKereta > 3) {
                    cout << "Pilihan tidak valid!\n";
                    continue;
                }

                KeretaDetail* pilihK = &daftarKereta[pilihanKereta - 1];

                cout << "Masukkan jumlah tiket: ";
                if (!(cin >> jumlahTiket) || jumlahTiket <= 0) {
                    cout << "Jumlah tiket tidak valid.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                int* daftarHarga = new int[jumlahTiket];
                for (int i = 0; i < jumlahTiket; i++)
                    daftarHarga[i] = pilihK->harga;

                string* namaPenumpang = new string[jumlahTiket];
                cout << "\nMasukkan nama penumpang:\n";
                for (int i = 0; i < jumlahTiket; i++) {
                    cout << "Penumpang ke-" << i + 1 << ": ";
                    getline(cin, namaPenumpang[i]);
                }

                int total = hitungTotal(daftarHarga, jumlahTiket);
                // ===== ISI DATA TIKET KERETA =====
Tiket tiket;
tiket.namaPemesan = namaPemesan;
tiket.transportasi = pilihK->namaKereta + " (" + pilihK->kodeKereta + ")";
tiket.rute = pilihK->stasiunAwal + " ke " + pilihK->stasiunTujuan;
tiket.tanggal = pilihK->tglBerangkat + " " + pilihK->blnBerangkat + " " + pilihK->thnBerangkat;
tiket.jam = pilihK->jamBerangkat;
tiket.jumlah = jumlahTiket;
tiket.total = total;

if (!prosesPembayaran(tiket)) {
    cout << "Transaksi dibatalkan.\n";
    delete[] daftarHarga;
    delete[] namaPenumpang;
    break;
}
char cetak;
cout << "Cetak tiket? (Y/N): ";
cin >> cetak;
cin.ignore();

if (cetak == 'Y' || cetak == 'y') {
    cetakTiket(tiket);
}
tambahPemesananDLL(
    tiket.namaPemesan,
    tiket.transportasi,
    tiket.rute,
    tiket.jumlah,
    tiket.total
);

tambahCircularDLL(
    tiket.namaPemesan,
    tiket.transportasi,
    tiket.rute,
    tiket.jumlah,
    tiket.total
);

pushStackDLL(
    tiket.namaPemesan,
    tiket.transportasi,
    tiket.rute,
    tiket.jumlah,
    tiket.total
);
delete[] daftarHarga;
delete[] namaPenumpang;

            }

            // BUS
            else if (pilihanTransport == 3) {
                BusDetail b1("Sinar Jaya", "BS-101", "Jakarta", "Semarang",
                             "13", "Nov", "2025", "06:00",
                             "13", "Nov", "2025", "14:30", 150000);
                BusDetail b2("Rosalia Indah", "BS-202", "Bandung", "Solo",
                             "14", "Nov", "2025", "08:00",
                             "14", "Nov", "2025", "16:45", 170000);
                BusDetail b3("Harapan Jaya", "BS-303", "Yogyakarta", "Tegal",
                             "15", "Nov", "2025", "07:30",
                             "15", "Nov", "2025", "15:00", 120000);

                BusDetail daftarBus[] = {b1, b2, b3};

                cout << "\n=== Pilih Jadwal Bus ===\n";
                for (int i = 0; i < 3; i++) {
                    cout << "\n" << i + 1 << ". ";
                    daftarBus[i].tampilkanInfo();
                }

                int pilihanBus;
                cout << "\nPilih bus (1-3): ";
                if (!(cin >> pilihanBus)) {
                    cout << "Input tidak valid.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (pilihanBus < 1 || pilihanBus > 3) {
                    cout << "Pilihan tidak valid!\n";
                    continue;
                }

                BusDetail* pilihB = &daftarBus[pilihanBus - 1];

                cout << "Masukkan jumlah tiket: ";
                if (!(cin >> jumlahTiket) || jumlahTiket <= 0) {
                    cout << "Jumlah tiket tidak valid.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                int* daftarHarga = new int[jumlahTiket];
                for (int i = 0; i < jumlahTiket; i++)
                    daftarHarga[i] = pilihB->harga;

                string* namaPenumpang = new string[jumlahTiket];
                cout << "\nMasukkan nama penumpang:\n";
                for (int i = 0; i < jumlahTiket; i++) {
                    cout << "Penumpang ke-" << i + 1 << ": ";
                    getline(cin, namaPenumpang[i]);
                }

                int total = hitungTotal(daftarHarga, jumlahTiket);

                // ===== ISI DATA TIKET BUS =====
Tiket tiket;
tiket.namaPemesan = namaPemesan;
tiket.transportasi = pilihB->namaBus;
tiket.rute = pilihB->terminalAwal + " ke " + pilihB->terminalTujuan;
tiket.tanggal = pilihB->tglBerangkat + " " + pilihB->blnBerangkat + " " + pilihB->thnBerangkat;
tiket.jam = pilihB->jamBerangkat;
tiket.jumlah = jumlahTiket;
tiket.total = total;

// PEMBAYARAN
if (!prosesPembayaran(tiket)) {
    cout << "Transaksi dibatalkan.\n";
    delete[] daftarHarga;
    delete[] namaPenumpang;
    break;
}

// CETAK
char cetak;
cout << "Cetak tiket? (Y/N): ";
cin >> cetak;
cin.ignore();

if (cetak == 'Y' || cetak == 'y') {
    cetakTiket(tiket);
}

// SIMPAN
tambahPemesananDLL(
    tiket.namaPemesan,
    tiket.transportasi,
    tiket.rute,
    tiket.jumlah,
    tiket.total
);

tambahCircularDLL(
    tiket.namaPemesan,
    tiket.transportasi,
    tiket.rute,
    tiket.jumlah,
    tiket.total
);

pushStackDLL(
    tiket.namaPemesan,
    tiket.transportasi,
    tiket.rute,
    tiket.jumlah,
    tiket.total
);

delete[] daftarHarga;
delete[] namaPenumpang;
}

        

            // KAPAL
            else if (pilihanTransport == 4) {
                KapalDetail kpl1("KM Labobar", "KP-001", "Makassar", "Balikpapan",
                                 "16", "Nov", "2025", "08:00",
                                 "16", "Nov", "2025", "20:00", 700000);
                KapalDetail kpl2("KM Sinabung", "KP-002", "Surabaya", "Ambon",
                                 "17", "Nov", "2025", "09:00",
                                 "18", "Nov", "2025", "07:00", 850000);
                KapalDetail kpl3("KM Dobonsolo", "KP-003", "Jakarta", "Makassar",
                                 "18", "Nov", "2025", "10:00",
                                 "19", "Nov", "2025", "13:30", 950000);

                KapalDetail daftarKapal[] = {kpl1, kpl2, kpl3};

                cout << "\n=== Pilih Jadwal Kapal ===\n";
                for (int i = 0; i < 3; i++) {
                    cout << "\n" << i + 1 << ". ";
                    daftarKapal[i].tampilkanInfo();
                }

                int pilihanKapal;
                cout << "\nPilih kapal (1-3): ";
                if (!(cin >> pilihanKapal)) {
                    cout << "Input tidak valid.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (pilihanKapal < 1 || pilihanKapal > 3) {
                    cout << "Pilihan tidak valid!\n";
                    continue;
                }
                KapalDetail* pilihKp = &daftarKapal[pilihanKapal - 1];


                KapalDetail* pilihKapal = &daftarKapal[pilihanKapal - 1];

                cout << "Masukkan jumlah tiket: ";
                if (!(cin >> jumlahTiket) || jumlahTiket <= 0) {
                    cout << "Jumlah tiket tidak valid.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                int* daftarHarga = new int[jumlahTiket];
                for (int i = 0; i < jumlahTiket; i++)
                    daftarHarga[i] = pilihKapal->harga;

                string* namaPenumpang = new string[jumlahTiket];
                cout << "\nMasukkan nama penumpang:\n";
                for (int i = 0; i < jumlahTiket; i++) {
                    cout << "Penumpang ke-" << i + 1 << ": ";
                    getline(cin, namaPenumpang[i]);
                }

                int total = hitungTotal(daftarHarga, jumlahTiket);

                // ===== ISI DATA TIKET KAPAL =====
Tiket tiket;
tiket.namaPemesan = namaPemesan;
tiket.transportasi = pilihKp->namaKapal;
tiket.rute = pilihKp->pelabuhanAwal + " ke " + pilihKp->pelabuhanTujuan;
tiket.tanggal = pilihKp->tglBerangkat + " " + pilihKp->blnBerangkat + " " + pilihKp->thnBerangkat;
tiket.jam = pilihKp->jamBerangkat;
tiket.jumlah = jumlahTiket;
tiket.total = total;

// PEMBAYARAN
if (!prosesPembayaran(tiket)) {
    cout << "Transaksi dibatalkan.\n";
    delete[] daftarHarga;
    delete[] namaPenumpang;
    break;
}

// CETAK
char cetak;
cout << "Cetak tiket? (Y/N): ";
cin >> cetak;
cin.ignore();

if (cetak == 'Y' || cetak == 'y') {
    cetakTiket(tiket);
}

// SIMPAN
tambahPemesananDLL(
    tiket.namaPemesan,
    tiket.transportasi,
    tiket.rute,
    tiket.jumlah,
    tiket.total
);

tambahCircularDLL(
    tiket.namaPemesan,
    tiket.transportasi,
    tiket.rute,
    tiket.jumlah,
    tiket.total
);

pushStackDLL(
    tiket.namaPemesan,
    tiket.transportasi,
    tiket.rute,
    tiket.jumlah,
    tiket.total
);

delete[] daftarHarga;
delete[] namaPenumpang;
}

            else {
                cout << "Pilihan tidak valid!\n";
                continue;
            }
        }

        // MENU 2â€"5 (DLL utama)
        else if (pilihanMenu == 2) {
            tampilkanRiwayatDLL();
        }
        else if (pilihanMenu == 3) {
            string cari;
            cout << "Masukkan nama yang ingin dicari: ";
            getline(cin, cari);
            cariPemesananDLL(cari);
        }
        else if (pilihanMenu == 4) {
            string ubah;
            cout << "Masukkan nama yang ingin diubah: ";
            getline(cin, ubah);
            ubahPemesananDLL(ubah);
        }
        else if (pilihanMenu == 5) {
            string hapus;
            cout << "Masukkan nama yang ingin dihapus: ";
            getline(cin, hapus);
            hapusPemesananDLL(hapus);
        }

        // MENU 6 (CIRCULAR DLL)
        else if (pilihanMenu == 6) {
            int s;
            cout << "\n--- CIRCULAR DLL ---\n";
            cout << "1. Tampilkan\n2. Cari\n3. Ubah\n4. Hapus\nPilih: ";
            if (!(cin >> s)) {
                cout << "Input tidak valid.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (s == 1) tampilkanCircularDLL();
            else if (s == 2) {
                string cari;
                cout << "Masukkan nama: "; getline(cin, cari);
                cariCircularDLL(cari);
            }
            else if (s == 3) {
                string ubah;
                cout << "Masukkan nama: "; getline(cin, ubah);
                ubahCircularDLL(ubah);
            }
            else if (s == 4) {
                string hapus;
                cout << "Masukkan nama: "; getline(cin, hapus);
                hapusCircularDLL(hapus);
            } else cout << "Pilihan tidak valid.\n";
        }

        // MENU 7 (PRIORITAS DLL)
        else if (pilihanMenu == 7) {
            int s;
            cout << "\n--- DOUBLE LINKED LIST PRIORITAS ---\n";
            cout << "1. Tambah Prioritas\n2. Tampilkan Maju\n3. Tampilkan Mundur\nPilih: ";
            if (!(cin >> s)) {
                cout << "Input tidak valid.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (s == 1) {
                string nama, ket;
                cout << "Nama: "; getline(cin, nama);
                cout << "Keterangan: "; getline(cin, ket);
                tambahPrioritasDLL(nama, ket);
            }
            else if (s == 2) tampilkanPrioritasMajuDLL();
            else if (s == 3) tampilkanPrioritasMundurDLL();
            else cout << "Pilihan tidak valid.\n";
        }

        // MENU 8 (STACK DLL)
        else if (pilihanMenu == 8) {
            int s;
            cout << "\n--- STACK RIWAYAT (DLL) ---\n";
            cout << "1. Tampilkan Stack\n2. Batalkan Transaksi Terakhir (POP)\nPilih: ";
            if (!(cin >> s)) {
                cout << "Input tidak valid.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (s == 1) tampilkanStackDLL();
            else if (s == 2) popStackDLL();
            else cout << "Pilihan tidak valid.\n";
        }

		// MENU 9 (QUEUE)
		else if (pilihanMenu == 9) {
    		int q;
   			cout << "\n--- QUEUE PEMESANAN ---\n";
    		cout << "1. Tampilkan Antrian\n";
    		cout << "2. Layani Antrian (DEQUEUE)\n";
    		cout << "Pilih: ";
    		cin >> q;
    		cin.ignore();
    		if (q == 1) tampilkanQueueDLL();
    		else if (q == 2) dequeueQueueDLL();
    		else cout << "Pilihan tidak valid.\n";
		}

		// MENU 10 (EKSPLORASI BINARY TREE)
		else if (pilihanMenu == 10) {
    		eksplorasiBinaryTree();
		}
		
		// MENU 11 (EKSPLORASI SKEWED TREE)
		else if (pilihanMenu == 11) {
    		eksplorasiSkewedTree();
		}

		// MENU 12 (EKSPLORASI AVL TREE)
		else if (pilihanMenu == 12) {
    		eksplorasiAVLTree();
		}

		// MENU 13 (EKSPLORASI HUFFMAN)
		else if (pilihanMenu == 13) {
    		menuHuffman();
		}

		// MENU 14 (KELUAR)
        else if (pilihanMenu == 14)
            cout << "Terima kasih telah menggunakan sistem.\n";
        else
            cout << "Pilihan tidak valid!\n";

    } while (pilihanMenu != 13);

    // ================ BERSIHKAN MEMORI ================
    // booking DLL
    while (bookingHead != NULL) {
        BookingNode* tmp = bookingHead;
        bookingHead = bookingHead->next;
        delete tmp;
    }
    bookingTail = NULL;

    // circular DLL
    if (circHead != NULL) {
        CircularDLLNode* cur = circHead->next;
        while (cur != circHead) {
            CircularDLLNode* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        delete circHead;
        circHead = circTail = NULL;
    }

    // priority DLL
    while (prioHead != NULL) {
        PriorityNode* tmp = prioHead;
        prioHead = prioHead->next;
        delete tmp;
    }
    prioTail = NULL;

    // stack DLL
    clearStackDLL();

    return 0;
}