#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include<limits>

using namespace std;

// ===================== STRUCT USER =====================
// Menyimpan data user dalam sistem
// ========================================================

struct User {

    string nama;      // nama lengkap user
    string username;  // username untuk login
    string password;  // password akun
    string email;     // email user
    string nohp;      // nomor HP user
};

// ===================== STRUCT IPHONE =====================
// Menyimpan data iPhone dalam sistem
// =========================================================

//=========================================================
// STRUCT CUSTOMER
//=========================================================

struct Customer
{
    string nama;
    string username;
    string password;
    string email;
    string hp;
};

struct Transaksi
{
    string id;
    string customer;
    string iphone;
    string lama;
    string total;
};

struct Pembayaran
{
    // Data transaksi
    string idTransaksi;
    string username;
    string metode;

    // Total tagihan
    int totalBayar;

    // Pembayaran tunai
    int bayar;
    int kembali;
};

struct Review
{
    string username;
    string rating;
    string komentar;
};

struct Iphone {

    string nama;   // nama tipe iPhone
    int stok;      // jumlah stok tersedia
    int harga;     // harga iPhone
};

struct Wishlist
{
    string username;
    string namaIphone;
};

struct StatistikCustomer
{
    string username;
    int jumlah;
};

struct Voucher
{
    string kode;
    int potongan;
};

struct Reservasi
{
    string idReservasi;
    string username;
    string namaIphone;
    string tanggalReservasi;
    string status;
};

struct Member
{
    string username;
    int poin;
    string level;
};

struct Promo
{
    string kodePromo;
    string namaPromo;
    int diskon;
    string tanggalMulai;
    string tanggalSelesai;
    string status;
};

struct Kerusakan
{
    string idKerusakan;
    string idTransaksi;
    string username;
    string namaIphone;
    string jenisKerusakan;
    string tingkatKerusakan;
    int biayaPerbaikan;
    string tanggal;
};

struct Servis
{
    string idServis;
    string namaIphone;
    string jenisKerusakan;
    string teknisi;
    string tanggalMasuk;
    string tanggalSelesai;
    string status;
};

struct Notifikasi
{
    string idNotifikasi;
    string username;
    string judul;
    string isi;
    string tanggal;
    string status;
};


//PROTOTYPE
	void pembayaran(string idTransaksi, string username, int totalBayar);
	void lihatCustomer();
	void editCustomer();
	void hapusCustomer();
	void riwayatSaya(string usernameAktif);
	void dashboardUser(string usernameAktif);
	void topIphoneTerlaris();
	void topCustomer();
	void backupDatabase();
	void salinFile(string sumber, string tujuan);
	void restoreDatabase();
	void exportLaporan();
	string levelMember(string usernameAktif);
	int gunakanVoucher(int totalHarga);
	void notifikasiStok();
	void menuWishlist(string usernameAktif);
    void tambahWishlist(string usernameAktif);
    void lihatWishlist(string usernameAktif);
    void hapusWishlist(string usernameAktif);
    void menuReservasiAdmin();
	void reservasiIphone(string usernameAktif);
	void lihatReservasi();
	void konfirmasiReservasi();
	void hapusReservasi();
	string generateIDReservasi();
	void tambahPoin(string username,int poinBaru);
	void updateLevelMember();
	void lihatMembership(string usernameAktif);
	void tukarPoin(string usernameAktif);
	void semuaMember();
	void menuPromoAdmin();
	void tambahPromo();
	void lihatPromo();
	void editPromo();
	void hapusPromo();
	void aktifkanPromo();
	void cariPromo();
	void menuKerusakanServis();
	void tambahKerusakan();
	void lihatKerusakan();
	void hapusKerusakan();
	void tambahServis();
	void lihatServis();
	void updateStatusServis();
	string generateIDKerusakan();
	string generateIDServis();
	void menuNotifikasiAdmin();
	void kirimNotifikasi(string username, string judul, string isi);
	void lihatNotifikasi(string usernameAktif);
	void tandaiSudahDibaca(string usernameAktif);
	void hapusNotifikasi();
	void semuaNotifikasi();
	string generateIDNotifikasi();

//=========================================================
// TAMBAH FITUR : VALIDASI INPUT ANGKA
//=========================================================

int inputAngka()
{
    int angka;

    while(true)
    {
        cin >> angka;

        if(cin.fail())
        {
            cin.clear();

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Input harus berupa angka, coba lagi : ";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return angka;
        }
    }
}

//=========================================================
// TAMBAH FITUR : VALIDASI NOMOR HP
//=========================================================

bool nomorHPValid(string hp)
{
    if(hp.length() < 10 || hp.length() > 15)
        return false;

    for(int i=0;i<hp.length();i++)
    {
        if(!isdigit(hp[i]))
            return false;
    }

    return true;
}

//=========================================================
// TAMBAH FITUR : VALIDASI EMAIL
//=========================================================

bool emailValid(string email)
{
    return email.find("@") != string::npos &&
           email.find(".") != string::npos;
}

void garis() {
    cout << "============================================================" << endl;
}

// ===================== PAUSE PROGRAM =====================
// Fungsi : Menahan program sampai user menekan ENTER
// =========================================================

void pauseProgram() {

    cout << "\nTekan ENTER untuk melanjutkan...";

    cin.ignore(); // membersihkan buffer input
    cin.get();    // menunggu user tekan ENTER
}


// ===================== LOGO =====================
// Menampilkan judul sistem di layar
// ===============================================

void tampilLogo() {

    cout << "=============================================================" << endl; 
    cout << "                SISTEM PENYEWAAN IPHONE                      " << endl; 
    cout << "=============================================================" << endl; 
}
// ===================== CEK USERNAME =====================
// Fungsi : Mengecek apakah username sudah terdaftar
// Return : true jika sudah ada, false jika belum ada
// =========================================================

//=========================================================
// PERBAIKAN BUG #1
// Registrasi menggunakan customer.txt
//=========================================================
bool cekUsername(string username) {

    ifstream file("customer.txt");

    Customer customer;

    while(getline(file, customer.nama, '|')) {

        getline(file, customer.username, '|');
getline(file, customer.password, '|');
getline(file, customer.email, '|');
getline(file, customer.hp);

        if(customer.username == username) {

            file.close();
            return true;
        }
    }

    file.close();

    return false;
}

// ===================== REGISTRASI USER =====================
// Fungsi : Mendaftarkan user baru dan menyimpan ke file
// ==========================================================

void registrasi() {

    system("cls");

    Customer customer;

    // ===================== HEADER =====================
    cout << "==================================================" << endl;
    cout << "              REGISTRASI CUSTOMER                " << endl;
    cout << "==================================================" << endl;

    cin.ignore();

    // ===================== INPUT DATA =====================
    cout << "Masukkan Nama     : ";
    getline(cin,customer.nama);

    cout << "Masukkan Username : ";
    getline(cin,customer.username);

    // VALIDASI USERNAME
    if(cekUsername(customer.username))
{
    cout << "\nUsername sudah digunakan!" << endl;
    cout << "Silakan gunakan username lain." << endl;

    system("pause");
    return;
}

    // ===================== PASSWORD =====================
cout << "Masukkan Password : ";
getline(cin, customer.password);

// ===================== EMAIL =====================
do
{
    cout << "Email : ";
    getline(cin, customer.email);

    if(!emailValid(customer.email))
        cout << "Format email salah!" << endl;

} while(!emailValid(customer.email));

// ===================== NOMOR HP =====================
do
{
    cout << "Nomor HP : ";
    getline(cin, customer.hp);

    if(!nomorHPValid(customer.hp))
        cout << "Nomor HP tidak valid!" << endl;

} while(!nomorHPValid(customer.hp));

    // ===================== SIMPAN DATA =====================
    ofstream file("customer.txt", ios::app);

    // CEK FILE
    if(!file.is_open()) {

        cout << "\nFile gagal dibuka!" << endl;
        system("pause");
        return;
    }

    file << customer.nama << "|"
     << customer.username << "|"
     << customer.password << "|"
     << customer.email << "|"
     << customer.hp << endl;

    file.close();

cout << "\n==================================================" << endl;
cout << "          REGISTRASI BERHASIL                    " << endl;
cout << "==================================================" << endl;

cout << "Nama     : " << customer.nama << endl;
cout << "Username : " << customer.username << endl;
cout << "Email    : " << customer.email << endl;
cout << "No HP    : " << customer.hp << endl;

system("pause");
}
// ===================== LOGIN USER =====================
// Fungsi : Mengecek username dan password dari file
// Return : true jika login berhasil, false jika gagal
// ======================================================

bool login(string &usernameAktif) {

    system("cls");

    // =====================================================
    // MENAMPILKAN JUDUL PROGRAM
    // =====================================================
    tampilLogo();

    Customer customer;
    string username;
    string password;
    //=========================================================
	// PERBAIKAN LOGIN
	//=========================================================
	bool usernameDitemukan = false;

    // =====================================================
    // HEADER LOGIN
    // =====================================================
    cout << "=============================================================" << endl;
    cout << "       SILAHKAN LOGIN DENGAN AKUN YANG SUDAH ANDA BUAT       " << endl;
    cout << "=============================================================" << endl;

    // =====================================================
    // INPUT USERNAME
    // =====================================================
    cout << "Masukkan Username : ";
    cin >> username;

    // =====================================================
    // INPUT PASSWORD
    // =====================================================
    cout << "Masukkan Password : ";
    cin >> password;

    // =====================================================
    // PROSES CEK DATA DARI FILE
    // =====================================================
    //=========================================================
// PERBAIKAN BUG #2
// Login membaca customer.txt
//=========================================================
ifstream file("customer.txt");

    // membaca data sampai akhir file
    //=========================================================
// PERBAIKAN BUG #3
// Membaca data dengan delimiter '|'
//=========================================================
while(getline(file, customer.nama, '|'))
{
    getline(file, customer.username, '|');
    getline(file, customer.password, '|');
    getline(file, customer.email, '|');
    getline(file, customer.hp);

    if(customer.username == username)
    {
        usernameDitemukan = true;

        if(customer.password == password)
        {
            usernameAktif = username;

            file.close();

            cout << "\nLogin berhasil!" << endl;

            pauseProgram();

            return true;
        }
    }
}

    file.close();

if(!usernameDitemukan)
{
    cout << "\nUsername belum terdaftar!" << endl;
}
else
{
    cout << "\nPassword yang Anda masukkan salah!" << endl;
}

pauseProgram();

return false;
}
// ===================== TAMPIL DATA IPHONE =====================
// Fungsi : Menampilkan seluruh data iPhone dalam bentuk tabel
// ===============================================================

void tampilDataIphone(vector<Iphone> iphone) {

    // header tabel
    cout << left << setw(5) << "No"
         << setw(20) << "Nama iPhone"
         << setw(15) << "Stok"
         << setw(15) << "Harga/Hari" << endl;

    garis(); // garis pemisah

    // isi data iPhone
    for (int i = 0; i < iphone.size(); i++) {

        cout << left << setw(5) << i + 1
             << setw(20) << iphone[i].nama
             << setw(15) << iphone[i].stok
             << "Rp " << iphone[i].harga << endl;
    }
    
    pauseProgram();
}

//=========================================================
// TAMBAH FITUR : DASHBOARD STATISTIK ADMIN
//=========================================================

void dashboardStatistik()
{
    system("cls");

    tampilLogo();

    int totalCustomer = 0;
    int totalIphone = 0;

    int iphoneReady = 0;
    int iphoneDisewa = 0;

    long long totalPendapatan = 0;
    int totalTransaksi = 0;

    //-----------------------------
    // Hitung Customer
    //-----------------------------

    ifstream customer("customer.txt");

    string baris;

    while(getline(customer, baris))
    {
        if(baris != "")
            totalCustomer++;
    }

    customer.close();

    //-----------------------------
    // Hitung Pendapatan
    //-----------------------------

    ifstream pembayaran("pembayaran.txt");

    while(getline(pembayaran, baris))
    {
        if(baris=="")
            continue;

        stringstream ss(baris);

        string temp;

        int harga = 0;

        while(getline(ss,temp,'|'))
        {
            try
            {
                harga = atoi(temp.c_str());
            }
            catch(...)
            {
            }
        }

        totalPendapatan += harga;
        totalTransaksi++;
    }

    pembayaran.close();

    //-----------------------------
    // TAMPILKAN DASHBOARD
    //-----------------------------

    cout<<"=========================================================="<<endl;
    cout<<"                 DASHBOARD ADMIN"<<endl;
    cout<<"=========================================================="<<endl;

    cout<<"Total Customer       : "<<totalCustomer<<endl;
    cout<<"Total iPhone         : "<<totalIphone<<endl;
    cout<<"iPhone Ready         : "<<iphoneReady<<endl;
    cout<<"iPhone Sedang Disewa : "<<iphoneDisewa<<endl;
    cout<<"Total Transaksi      : "<<totalTransaksi<<endl;
    cout<<"Total Pendapatan     : Rp "<<totalPendapatan<<endl;

    cout<<"=========================================================="<<endl;

    pauseProgram();
}

//=========================================================
// TAMBAH FITUR : PENCARIAN DATA
//=========================================================

void pencarianData()
{
    system("cls");

    int pilih;

    cout << "==================================================" << endl;
    cout << "               MENU PENCARIAN DATA                " << endl;
    cout << "==================================================" << endl;

    cout << "1. Cari Customer" << endl;
    cout << "2. Cari iPhone" << endl;
    cout << "3. Cari Transaksi" << endl;
    cout << "4. Kembali" << endl;

    cout << "\nPilih Menu : ";
    cin >> pilih;

    switch(pilih)
    {

    //=================================================
    // CARI CUSTOMER
    //=================================================
    case 1:
    {

        system("cls");

        ifstream file("customer.txt");

        string cari;
        
        Customer customer;

        bool ditemukan=false;

        cin.ignore();

        cout<<"Masukkan Username Customer : ";
        getline(cin,cari);

        while(getline(file, customer.nama, '|'))
{
    getline(file, customer.username, '|');
    getline(file, customer.password, '|');
    getline(file, customer.email, '|');
    getline(file, customer.hp);

            if(customer.username == cari)
            {
                ditemukan=true;

                cout<<"\n===== DATA CUSTOMER ====="<<endl;

                cout << "Nama      : " << customer.nama << endl;
				cout << "Username  : " << customer.username << endl;
				cout << "Email     : " << customer.email << endl;
				cout << "No HP     : " << customer.hp << endl;

                break;
            }
        }

        if(!ditemukan)
        {
            cout<<"\nCustomer tidak ditemukan."<<endl;
        }

        file.close();

        pauseProgram();

        break;
    }

    //=================================================
    // CARI IPHONE
    //=================================================
    case 2:
    {

        system("cls");

        ifstream file("iphone.txt");

        Iphone hp;

        string stok;
        string harga;

        string cari;

        bool ditemukan=false;

        cin.ignore();

        cout<<"Masukkan Nama iPhone : ";
        getline(cin,cari);

        while(getline(file,hp.nama,'|'))
        {
            getline(file,stok,'|');
            getline(file,harga);

            if(hp.nama==cari)
            {
                ditemukan=true;

                cout<<"\n===== DATA IPHONE ====="<<endl;

                cout<<"Nama  : "<<hp.nama<<endl;
                cout<<"Stok  : "<<stok<<endl;
                cout<<"Harga : Rp "<<harga<<endl;

                break;
            }
        }

        if(!ditemukan)
        {
            cout<<"\nData iPhone tidak ditemukan."<<endl;
        }

        file.close();

        pauseProgram();

        break;
    }

    //=================================================
    // CARI TRANSAKSI
    //=================================================
    case 3:
    {

        system("cls");

        ifstream file("transaksi.txt");

        Transaksi transaksi;

        string cari;

        bool ditemukan=false;

        cin.ignore();

        cout<<"Masukkan ID Transaksi : ";
        getline(cin,cari);

       while(getline(file, transaksi.id, '|'))
{
    getline(file, transaksi.customer, '|');
    getline(file, transaksi.iphone, '|');
    getline(file, transaksi.lama, '|');
    getline(file, transaksi.total);

            if(transaksi.id == cari)
            {
                ditemukan=true;

                cout<<"\n===== DATA TRANSAKSI ====="<<endl;

                cout<<"ID          : "<<transaksi.id<<endl;
cout<<"Customer    : "<<transaksi.customer<<endl;
cout<<"iPhone      : "<<transaksi.iphone<<endl;
cout<<"Lama Sewa   : "<<transaksi.lama<<" Hari"<<endl;
cout<<"Total Bayar : Rp "<<transaksi.total<<endl;

                break;
            }
        }

        if(!ditemukan)
        {
            cout<<"\nTransaksi tidak ditemukan."<<endl;
        }

        file.close();

        pauseProgram();

        break;
    }

    case 4:

        return;

    default:

        cout<<"\nMenu tidak tersedia!"<<endl;

        pauseProgram();

    }
}

//=========================================================
// TAMBAH FITUR : LAPORAN PENDAPATAN
//=========================================================

void laporanPendapatan()
{
    system("cls");

    tampilLogo();

    ifstream file("pembayaran.txt");

    Pembayaran pembayaran;

    long long totalPendapatan=0;

    long long cash=0;
    long long transfer=0;
    long long qris=0;

    int jumlahTransaksi=0;

    while(getline(file, pembayaran.username, '|'))
{
    string totalStr;

getline(file, pembayaran.username, '|');
getline(file, pembayaran.metode, '|');
getline(file, totalStr);

pembayaran.totalBayar = atoi(totalStr.c_str());

        int nominal = pembayaran.totalBayar;

        totalPendapatan+=nominal;

        jumlahTransaksi++;

        if(pembayaran.metode=="Cash")
			{
			    cash += nominal;
			}
			else if(pembayaran.metode=="Transfer")
			{
			    transfer += nominal;
			}
			else if(pembayaran.metode=="QRIS")
			{
			    qris += nominal;
			}
    }

    file.close();

    cout<<"======================================================"<<endl;
    cout<<"             LAPORAN PENDAPATAN"<<endl;
    cout<<"======================================================"<<endl;

    cout<<"Jumlah Transaksi : "<<jumlahTransaksi<<endl;

    cout<<"Pendapatan Cash      : Rp "<<cash<<endl;
    cout<<"Pendapatan Transfer  : Rp "<<transfer<<endl;
    cout<<"Pendapatan QRIS      : Rp "<<qris<<endl;

    cout<<"------------------------------------------------------"<<endl;

    cout<<"TOTAL PENDAPATAN     : Rp "<<totalPendapatan<<endl;

    cout<<"======================================================"<<endl;

    pauseProgram();
}

//=========================================================
// TAMBAH FITUR : GENERATE ID TRANSAKSI OTOMATIS
//=========================================================

string generateIDTransaksi()
{
    ifstream file("transaksi.txt");

    string baris;
    int jumlah = 0;

    while(getline(file, baris))
    {
        if(baris != "")
            jumlah++;
    }

    file.close();

    jumlah++;

    stringstream ss;

    ss << "TRX";

    if(jumlah < 10)
        ss << "000";

    else if(jumlah < 100)
        ss << "00";

    else if(jumlah < 1000)
        ss << "0";

    ss << jumlah;

    return ss.str();
}

//=========================================================
// TAMBAH FITUR : STATISTIK PENYEWAAN IPHONE
//=========================================================

void statistikPenyewaan()
{
    system("cls");

    tampilLogo();

    vector<string> namaIphone;
    vector<int> jumlah;

    ifstream file("transaksi.txt");

    Transaksi transaksi;

    while(getline(file, transaksi.id, '|'))
{
    getline(file, transaksi.customer, '|');
    getline(file, transaksi.iphone, '|');
    getline(file, transaksi.lama, '|');
    getline(file, transaksi.total);

        bool ada=false;

        for(int i=0;i<namaIphone.size();i++)
        {
            if(namaIphone[i] == transaksi.iphone)
            {
                jumlah[i]++;
                ada=true;
                break;
            }
        }

        if(!ada)
        {
            namaIphone.push_back(transaksi.iphone);
            jumlah.push_back(1);
        }
    }

    file.close();

    // SORTING TERLARIS
    for(int i=0;i<jumlah.size()-1;i++)
    {
        for(int j=i+1;j<jumlah.size();j++)
        {
            if(jumlah[i] < jumlah[j])
            {
                swap(jumlah[i],jumlah[j]);
                swap(namaIphone[i],namaIphone[j]);
            }
        }
    }

    cout<<"=========================================================="<<endl;
    cout<<"          STATISTIK PENYEWAAN IPHONE"<<endl;
    cout<<"=========================================================="<<endl;

    for(int i=0;i<namaIphone.size();i++)
    {
        cout<<i+1<<". "<<namaIphone[i]<<endl;
        cout<<"   Disewa "<<jumlah[i]<<" kali"<<endl;
        cout<<"------------------------------------------------------"<<endl;
    }

    cout<<endl;

    cout<<"================ TOP 3 IPHONE TERLARIS ================"<<endl;

    if(namaIphone.size()>0)
        cout<<"?? "<<namaIphone[0]<<" ("<<jumlah[0]<<" kali)"<<endl;

    if(namaIphone.size()>1)
        cout<<"?? "<<namaIphone[1]<<" ("<<jumlah[1]<<" kali)"<<endl;

    if(namaIphone.size()>2)
        cout<<"?? "<<namaIphone[2]<<" ("<<jumlah[2]<<" kali)"<<endl;

    cout<<"=========================================================="<<endl;

    pauseProgram();
}

//=========================================================
// TAMBAH FITUR : SORTING DATA IPHONE
//=========================================================

void sortingDataIphone()
{
    system("cls");

    vector<Iphone> iphone;

    ifstream file("iphone.txt");

    Iphone hp;

    string stok;
    string harga;

    while(getline(file,hp.nama,'|'))
    {
        getline(file,stok,'|');
        getline(file,harga);

        hp.stok=atoi(stok.c_str());
        hp.harga=atoi(harga.c_str());

        iphone.push_back(hp);
    }

    file.close();

    int pilih;

    cout<<"===================================="<<endl;
    cout<<"        SORTING DATA IPHONE"<<endl;
    cout<<"===================================="<<endl;

    cout<<"1. Nama A-Z"<<endl;
    cout<<"2. Nama Z-A"<<endl;
    cout<<"3. Harga Termurah"<<endl;
    cout<<"4. Harga Termahal"<<endl;
    cout<<"5. Stok Terbanyak"<<endl;
    cout<<"6. Stok Tersedikit"<<endl;
    cout<<"7. Kembali"<<endl;

    cout<<"\nPilih : ";
    cin>>pilih;

    for(int i=0;i<iphone.size()-1;i++)
    {
        for(int j=i+1;j<iphone.size();j++)
        {

            bool tukar=false;

            switch(pilih)
            {

            case 1:

                if(iphone[i].nama>iphone[j].nama)
                    tukar=true;

                break;

            case 2:

                if(iphone[i].nama<iphone[j].nama)
                    tukar=true;

                break;

            case 3:

                if(iphone[i].harga>iphone[j].harga)
                    tukar=true;

                break;

            case 4:

                if(iphone[i].harga<iphone[j].harga)
                    tukar=true;

                break;

            case 5:

                if(iphone[i].stok<iphone[j].stok)
                    tukar=true;

                break;

            case 6:

                if(iphone[i].stok>iphone[j].stok)
                    tukar=true;

                break;

            case 7:

                return;
            }

            if(tukar)
            {
                Iphone temp=iphone[i];
                iphone[i]=iphone[j];
                iphone[j]=temp;
            }

        }
    }

    system("cls");

    cout<<"============================================================"<<endl;
    cout<<"                  HASIL SORTING DATA"<<endl;
    cout<<"============================================================"<<endl;

    cout<<left
        <<setw(5)<<"No"
        <<setw(25)<<"Nama iPhone"
        <<setw(10)<<"Stok"
        <<setw(15)<<"Harga"<<endl;

    garis();

    for(int i=0;i<iphone.size();i++)
    {
        cout<<left
            <<setw(5)<<i+1
            <<setw(25)<<iphone[i].nama
            <<setw(10)<<iphone[i].stok
            <<setw(15)<<iphone[i].harga
            <<endl;
    }

    pauseProgram();
}

// ===================== SEWA IPHONE =====================
// Fungsi : Proses penyewaan iPhone oleh user
// ========================================================

void sewaIphone(string usernameAktif) {

    system("cls");

    vector<Iphone> iphone;

    ifstream file("iphone.txt");

    Iphone hp;
    string stok;
    string harga;

    // ===================== BACA DATA IPHONE =====================
    while(getline(file, hp.nama, '|')) {

        getline(file, stok, '|');
        getline(file, harga);

        hp.stok = atoi(stok.c_str());
        hp.harga = atoi(harga.c_str());

        iphone.push_back(hp);
    }

    file.close();

    // ===================== TAMPIL DATA IPHONE =====================
    cout << "==================================================" << endl;
    cout << "               PENYEWAAN IPHONE                   " << endl;
    cout << "==================================================" << endl;

    for(int i = 0; i < iphone.size(); i++) {

        cout << i + 1 << ". "
             << iphone[i].nama
             << " | Stok : " << iphone[i].stok
             << " | Harga : Rp " << iphone[i].harga
             << endl;
    }

    // ===================== INPUT PILIHAN =====================
    int pilih;
    int lamaSewa;

    cout << "\nPilih iPhone : ";
    cin >> pilih;

    // VALIDASI PILIHAN
    if(pilih < 1 || pilih > iphone.size()) {

        cout << "\nPilihan tidak valid!" << endl;
        system("pause");
        return;
    }

    cout << "Input lama sewa (hari) : ";
    cin >> lamaSewa;

    // ===================== CEK STOK =====================
    if(iphone[pilih - 1].stok <= 0) {

        cout << "\nStok iPhone habis!" << endl;
        system("pause");
        return;
    }

    // ===================== GENERATE ID TRANSAKSI =====================

    string idTransaksi = generateIDTransaksi();

    // ===================== HITUNG TOTAL =====================
    int totalHarga = iphone[pilih-1].harga * lamaSewa;

	string level = levelMember(usernameAktif);
	
	int diskon = 0;
	
	int poinDidapat = totalHarga / 100000 * 10;

	tambahPoin(usernameAktif,poinDidapat);
	
	if(level == "Silver")
	    diskon = totalHarga * 5 / 100;
	
	else if(level == "Gold")
	    diskon = totalHarga * 10 / 100;
	
	else if(level == "Platinum")
	    diskon = totalHarga * 15 / 100;
	
	totalHarga -= diskon;
	totalHarga = gunakanVoucher(totalHarga);

    // ===================== SIMPAN TRANSAKSI =====================
    ofstream transaksi;

    transaksi.open("transaksi.txt", ios::app);

    // CEK FILE
    if(!transaksi.is_open()) {

        cout << "\nFile transaksi gagal dibuka!" << endl;
        system("pause");
        return;
    }

    transaksi << idTransaksi << "|"
               << usernameAktif << "|"
               << iphone[pilih - 1].nama << "|"
               << lamaSewa << "|"
               << totalHarga
               << endl;

    transaksi.close();

pembayaran(idTransaksi,
           usernameAktif,
           totalHarga);
           
        cout << "\nPenyewaan berhasil!\n";

    // ===================== UPDATE STOK =====================
    iphone[pilih - 1].stok--;

    ofstream update("iphone.txt");

    for(int i = 0; i < iphone.size(); i++) {

        update << iphone[i].nama << "|"
               << iphone[i].stok << "|"
               << iphone[i].harga
               << endl;
    }

    update.close();

    // ===================== OUTPUT TRANSAKSI =====================
    cout << "\n==================================================" << endl;
    cout << "               TRANSAKSI BERHASIL                 " << endl;
    cout << "==================================================" << endl;

    cout << "ID Transaksi : " << idTransaksi << endl;
    cout << "Customer     : " << usernameAktif << endl;
    cout << "iPhone       : " << iphone[pilih - 1].nama << endl;
    cout << "Lama Sewa    : " << lamaSewa << " Hari" << endl;
    cout<<"Level Member : "<<level<<endl;
cout<<"Diskon       : Rp "<<diskon<<endl;
cout<<"Total Harga  : Rp "<<totalHarga<<endl;
}

void pembayaran(string idTransaksi,
                string username,
                int totalBayar)
{
    system("cls");

    Pembayaran bayar;

    bayar.idTransaksi = idTransaksi;
    bayar.username = username;
    bayar.totalBayar = totalBayar;

    int pilih;

    cout<<"============================================"<<endl;
    cout<<"           METODE PEMBAYARAN"<<endl;
    cout<<"============================================"<<endl;

    cout<<"1. Cash"<<endl;
    cout<<"2. Transfer Bank"<<endl;
    cout<<"3. E-Wallet"<<endl;

    cout<<"\nPilih : ";
    cin>>pilih;

    switch(pilih)
    {
        case 1:
            bayar.metode="Cash";
            break;

        case 2:
            bayar.metode="Transfer";
            break;

        case 3:
            bayar.metode="E-Wallet";
            break;

        default:
            bayar.metode="Cash";
    }

    ofstream file("pembayaran.txt",ios::app);

    file<<bayar.idTransaksi<<"|"
        <<bayar.username<<"|"
        <<bayar.metode<<"|"
        <<bayar.totalBayar
        <<endl;

    file.close();

    cout<<"\n============================================"<<endl;
    cout<<"        PEMBAYARAN BERHASIL"<<endl;
    cout<<"============================================"<<endl;

    cout<<"ID Transaksi : "<<bayar.idTransaksi<<endl;
    cout<<"Username     : "<<bayar.username<<endl;
    cout<<"Metode       : "<<bayar.metode<<endl;
    cout<<"Total Bayar  : Rp "<<bayar.totalBayar<<endl;

    pauseProgram();
}

int gunakanVoucher(int totalHarga)
{
    Voucher voucher;

    voucher.kode="";
    voucher.potongan=0;

    char pilih;

    cout<<"\nGunakan Voucher? (Y/T) : ";
    cin>>pilih;

    if(pilih=='Y'||pilih=='y')
    {
        cout<<"Masukkan Kode : ";
        cin>>voucher.kode;

        if(voucher.kode=="WELCOME10")
        {
            voucher.potongan=100000;
        }
        else if(voucher.kode=="HEMAT50")
        {
            voucher.potongan=50000;
        }
        else if(voucher.kode=="IPHONE25")
        {
            voucher.potongan=25000;
        }
        else
        {
            cout<<"Voucher tidak valid!"<<endl;
        }

        totalHarga-=voucher.potongan;

        if(totalHarga<0)
            totalHarga=0;

        cout<<"Potongan : Rp "<<voucher.potongan<<endl;
    }

    return totalHarga;
}

// ===================== PEMBAYARAN =====================
// Fungsi : Memproses pembayaran transaksi sewa iPhone
// =======================================================


//=========================================================
// TAMBAH FITUR : HITUNG KONDISI IPHONE
//=========================================================

int hitungDendaKerusakan(string &kondisi)
{
    int pilih;

    cout << "\n======================================" << endl;
    cout << "        KONDISI IPHONE" << endl;
    cout << "======================================" << endl;

    cout << "1. Sangat Baik" << endl;
    cout << "2. Baik" << endl;
    cout << "3. Lecet Ringan" << endl;
    cout << "4. Rusak Ringan" << endl;
    cout << "5. Rusak Berat" << endl;

    cout << "\nPilih Kondisi : ";
    cin >> pilih;

    switch(pilih)
    {
        case 1:
            kondisi="Sangat Baik";
            return 0;

        case 2:
            kondisi="Baik";
            return 0;

        case 3:
            kondisi="Lecet Ringan";
            return 100000;

        case 4:
            kondisi="Rusak Ringan";
            return 300000;

        case 5:
            kondisi="Rusak Berat";
            return 750000;

        default:
            kondisi="Tidak Diketahui";
            return 0;
    }
}

void pengembalianIphone() {

    system("cls");

    string idCari;
    bool ditemukan = false;

    cout << "==================================================" << endl;
    cout << "              PENGEMBALIAN IPHONE                 " << endl;
    cout << "==================================================" << endl;

    cout << "Input ID Transaksi : ";
    cin >> idCari;

    ifstream transaksi("transaksi.txt");

    Transaksi data;

    vector<string> dataBaru;

    while(getline(transaksi, data.id, '|')) {

    getline(transaksi, data.customer, '|');
    getline(transaksi, data.iphone, '|');
    getline(transaksi, data.lama, '|');
    getline(transaksi, data.total);

        // CEK TRANSAKSI
        if(data.id == idCari) {

            ditemukan = true;

            int lamaSewa = atoi(data.lama.c_str());

            int telat;
            int denda = 0;
            string kondisi;
            int dendaKerusakan = 0;

            cout << "\nData Transaksi Ditemukan!" << endl;

            cout << "Customer      : " << data.customer << endl;
            cout << "iPhone        : " << data.iphone << endl;
            cout << "Lama Sewa     : " << lamaSewa << " Hari" << endl;

            // INPUT KETERLAMBATAN
            cout << "\nInput keterlambatan (hari) : ";
            cin >> telat;

            // HITUNG DENDA
            if(telat > 0) {

                denda = telat * 50000;
            }
            dendaKerusakan = hitungDendaKerusakan(kondisi);
            int totalDenda = denda + dendaKerusakan;

            cout << "\n======================================" << endl;
            cout << "          DETAIL PENGEMBALIAN        " << endl;
            cout << "======================================" << endl;

            cout << "ID Transaksi  : " << data.id << endl;
            cout << "Customer      : " << data.customer << endl;
            cout << "iPhone        : " << data.iphone << endl;
            cout << "Keterlambatan : " << telat << " Hari" << endl;
            cout << "Denda Keterlambatan : Rp " << denda << endl;
            cout << "Kondisi iPhone      : " << kondisi << endl;
            cout << "Biaya Kerusakan     : Rp " << dendaKerusakan << endl;
            cout << "--------------------------------------" << endl;
            cout << "TOTAL DENDA         : Rp " << totalDenda << endl;

            // TAMBAH STOK KEMBALI
            vector<Iphone> iphone;

            ifstream fileIphone("iphone.txt");

            Iphone hp;

            string stok;
            string harga;

            while(getline(fileIphone, hp.nama, '|')) {

                getline(fileIphone, stok, '|');
                getline(fileIphone, harga);

                hp.stok = atoi(stok.c_str());
                hp.harga = atoi(harga.c_str());

                // TAMBAH STOK
                if(hp.nama == data.iphone) {

                    hp.stok++;
                }

                iphone.push_back(hp);
            }

            fileIphone.close();

            // UPDATE FILE IPHONE
            ofstream update("iphone.txt");

            for(int i = 0; i < iphone.size(); i++) {

                update << iphone[i].nama << "|"
                       << iphone[i].stok << "|"
                       << iphone[i].harga << endl;
            }

            update.close();
            
            ofstream histori("pengembalian.txt", ios::app);

            histori << data.id << "|"
        << data.customer << "|"
        << data.iphone << "|"
        << kondisi << "|"
        << totalDenda
        << endl;

            histori.close();
            
            cout << "\nPengembalian berhasil!" << endl;
            cout << "Stok iPhone telah ditambahkan kembali." << endl;

        } else {

            dataBaru.push_back(
    data.id + "|" +
    data.customer + "|" +
    data.iphone + "|" +
    data.lama + "|" +
    data.total
);
    }
}
    transaksi.close();

    // UPDATE TRANSAKSI
    ofstream ulang("transaksi.txt");

    for(int i = 0; i < dataBaru.size(); i++) {

        ulang << dataBaru[i] << endl;
    }

    ulang.close();

    if(!ditemukan) {

        cout << "\nID Transaksi tidak ditemukan!" << endl;
    }

    system("pause");
}


void kelolaCustomer() {

    system("cls");

    int pilih;

    cout << "======================================" << endl;
    cout << "         KELOLA DATA CUSTOMER        " << endl;
    cout << "======================================" << endl;

    cout << "1. Lihat Data Customer" << endl;
    cout << "2. Edit Data Customer" << endl;
    cout << "3. Hapus Data Customer" << endl;

    cout << "\nPilih menu : ";
    cin >> pilih;

    switch(pilih) {

        case 1:
            lihatCustomer();
            break;

        case 2:
            editCustomer();
            break;

        case 3:
            hapusCustomer();
            break;

        default:

            cout << "\nMenu tidak tersedia!" << endl;
            system("pause");
    }
}

void lihatCustomer() {

    system("cls");

    ifstream file("customer.txt");

    Customer customer;

    cout << "============================================================" << endl;
    cout << "                     DATA CUSTOMER                          " << endl;
    cout << "============================================================" << endl;

    cout << "No\tNama\t\tUsername\tEmail\t\tNo HP" << endl;

    int no = 1;

    while(getline(file,customer.nama,'|')) {

        getline(file,customer.username,'|');
		getline(file,customer.password,'|');
		getline(file,customer.email,'|');
		getline(file,customer.hp);

        cout << no++ << "\t"
     << customer.nama << "\t"
     << customer.username << "\t"
     << customer.email << "\t"
     << customer.hp << endl;
    }

    file.close();

    system("pause");
}

// ===================== EDIT CUSTOMER =====================
// Fungsi : Mengedit data customer berdasarkan username
// =========================================================

void editCustomer() {

    system("cls");

    ifstream file("customer.txt");
    ofstream temp("temp.txt");

    Customer customer;

    string cariUsername;

    bool ditemukan = false;

    cout << "======================================" << endl;
    cout << "          EDIT CUSTOMER              " << endl;
    cout << "======================================" << endl;

    cin.ignore();

    cout << "Masukkan Username Customer : ";
    getline(cin, cariUsername);

    while(getline(file, customer.nama, '|'))
{
    getline(file, customer.username, '|');
    getline(file, customer.password, '|');
    getline(file, customer.email, '|');
    getline(file, customer.hp);

        if(customer.username == cariUsername)
		{

            ditemukan = true;

            cout << "\nData ditemukan!" << endl;

            cout << "Nama Baru     : ";
			getline(cin, customer.nama);
			
			cout << "Username Baru : ";
			getline(cin, customer.username);
			
			cout << "Password Baru : ";
			getline(cin, customer.password);
			
			cout << "Email Baru    : ";
			getline(cin, customer.email);
			
			cout << "No HP Baru    : ";
			getline(cin, customer.hp);
        }

        temp << customer.nama << "|"
     << customer.username << "|"
     << customer.password << "|"
     << customer.email << "|"
     << customer.hp << endl;
    }

    file.close();
    temp.close();

    remove("customer.txt");
    rename("temp.txt", "customer.txt");

    if(ditemukan) {

        cout << "\nData berhasil diupdate!" << endl;

    } else {

        cout << "\nCustomer tidak ditemukan!" << endl;
    }

    system("pause");
}

void hapusCustomer() {

    system("cls");

    ifstream file("customer.txt");
    ofstream temp("temp.txt");

    Customer customer;

    string cariUsername;

    bool ditemukan = false;

    cout << "======================================" << endl;
    cout << "          HAPUS CUSTOMER             " << endl;
    cout << "======================================" << endl;

    cin.ignore();

    cout << "Masukkan Username Customer : ";
    getline(cin, cariUsername);

    while (getline(file, customer.nama, '|')) {

        getline(file, customer.username, '|');
		getline(file, customer.password, '|');
		getline(file, customer.email, '|');
		getline(file, customer.hp);

        if (customer.username == cariUsername) {
    ditemukan = true;
    continue;
}

        temp << customer.nama << "|"
     << customer.username << "|"
     << customer.password << "|"
     << customer.email << "|"
     << customer.hp << endl;
    }

    file.close();
    temp.close();

    remove("customer.txt");
    rename("temp.txt", "customer.txt");

    if(ditemukan) {

        cout << "\nCustomer berhasil dihapus!" << endl;

    } else {

        cout << "\nCustomer tidak ditemukan!" << endl;
    }

    system("pause");
}





void riwayatPenyewaan() {

    system("cls");

    ifstream file("transaksi.txt");

    Transaksi transaksi;

    cout << "======================================================================" << endl;
    cout << "                       RIWAYAT PENYEWAAN                             " << endl;
    cout << "======================================================================" << endl;

    cout << "ID\tCustomer\tiPhone\t\tLama\tTotal" << endl;

   while(getline(file, transaksi.id, '|')) {

    getline(file, transaksi.customer, '|');
    getline(file, transaksi.iphone, '|');
    getline(file, transaksi.lama, '|');
    getline(file, transaksi.total);
        
        cout << transaksi.id << "\t"
     << transaksi.customer << "\t\t"
     << transaksi.iphone << "\t"
     << transaksi.lama << " Hari\t"
     << "Rp " << transaksi.total
     << endl;
    }

    file.close();

    system("pause");
}

void riwayatSaya(string usernameAktif)
{
    system("cls");

    tampilLogo();

    int pilih;

    cout << "======================================================" << endl;
    cout << "              RIWAYAT PENYEWAAN SAYA                  " << endl;
    cout << "======================================================" << endl;
    cout << "1. Semua Riwayat" << endl;
    cout << "2. Cari Berdasarkan ID Transaksi" << endl;
    cout << "3. Cari Berdasarkan Nama iPhone" << endl;
    cout << "4. Kembali" << endl;

    cout << "\nPilih Menu : ";
    pilih = inputAngka();

    if(pilih == 4)
    {
        return;
    }

    cin.ignore();

    ifstream file("transaksi.txt");

    if(!file.is_open())
    {
        cout << "\nFile transaksi tidak ditemukan!" << endl;
        pauseProgram();
        return;
    }

    Transaksi transaksi;

    bool ditemukan = false;
    string keyword;

    if(pilih == 2)
    {
        cout << "Masukkan ID Transaksi : ";
        getline(cin, keyword);
    }
    else if(pilih == 3)
    {
        cout << "Masukkan Nama iPhone : ";
        getline(cin, keyword);
    }

    cout << "\n======================================================" << endl;
    cout << "                 HASIL RIWAYAT                        " << endl;
    cout << "======================================================" << endl;

    while(getline(file, transaksi.id, '|'))
    {
        getline(file, transaksi.customer, '|');
        getline(file, transaksi.iphone, '|');
        getline(file, transaksi.lama, '|');
        getline(file, transaksi.total);

        // hanya tampilkan transaksi milik user yang login
        if(transaksi.customer != usernameAktif)
            continue;

        // filter ID
        if(pilih == 2 && transaksi.id != keyword)
            continue;

        // filter nama iphone
        if(pilih == 3 && transaksi.iphone != keyword)
            continue;

        ditemukan = true;

        cout << "ID Transaksi : " << transaksi.id << endl;
        cout << "Customer     : " << transaksi.customer << endl;
        cout << "iPhone       : " << transaksi.iphone << endl;
        cout << "Lama Sewa    : " << transaksi.lama << " Hari" << endl;
        cout << "Total Bayar  : Rp " << transaksi.total << endl;
        cout << "------------------------------------------------------" << endl;
    }

    if(!ditemukan)
    {
        cout << "\nData tidak ditemukan." << endl;
    }

    file.close();

    pauseProgram();
}

void dashboardUser(string usernameAktif)
{
    system("cls");

    tampilLogo();

    ifstream file("transaksi.txt");

    if(!file.is_open())
    {
        cout << "\nFile transaksi tidak ditemukan!" << endl;
        pauseProgram();
        return;
    }

    Transaksi transaksi;

    int totalSewa = 0;
    int totalHari = 0;
    int totalBayar = 0;

    string transaksiTerakhir = "-";
    
        while(getline(file, transaksi.id, '|'))
    {
        getline(file, transaksi.customer, '|');
        getline(file, transaksi.iphone, '|');
        getline(file, transaksi.lama, '|');
        getline(file, transaksi.total);

        if(transaksi.customer == usernameAktif)
        {
            totalSewa++;

            totalHari += atoi(transaksi.lama.c_str());

            totalBayar += atoi(transaksi.total.c_str());

            transaksiTerakhir = transaksi.id;
        }
    }

    file.close();
    
        cout << "==========================================================" << endl;
    cout << "                 DASHBOARD USER" << endl;
    cout << "==========================================================" << endl;

    cout << "Username             : " << usernameAktif << endl;
    cout << "Level Member         : " << levelMember(usernameAktif) << endl;
	cout << "Total Penyewaan      : " << totalSewa << endl;
	cout << "Total Hari Sewa      : " << totalHari << " Hari" << endl;
	cout << "Total Pengeluaran    : Rp " << totalBayar << endl;
	cout << "Transaksi Terakhir   : " << transaksiTerakhir << endl;
	
	if(totalSewa > 0)
	{
	    cout << "Rata-rata Hari Sewa  : "
	         << totalHari / totalSewa
	         << " Hari" << endl;
	}
	else
	{
	    cout << "Rata-rata Hari Sewa  : 0 Hari" << endl;
	}
	
	if(totalSewa >= 10)
	{
	    cout << "Status Customer      : Member Platinum" << endl;
	}
	else if(totalSewa >= 5)
	{
	    cout << "Status Customer      : Member Gold" << endl;
	}
	else
	{
	    cout << "Status Customer      : Member Aktif" << endl;
	}

    cout << "==========================================================" << endl;

    pauseProgram();
}

void menuWishlist(string usernameAktif)
{
    int pilih;

    do
    {
        system("cls");

        cout << "======================================" << endl;
        cout << "          MENU WISHLIST" << endl;
        cout << "======================================" << endl;
        cout << "1. Tambah Wishlist" << endl;
        cout << "2. Lihat Wishlist" << endl;
        cout << "3. Hapus Wishlist" << endl;
        cout << "4. Kembali" << endl;

        cout << "\nPilih : ";
        cin >> pilih;

        switch(pilih)
        {
            case 1:
                tambahWishlist(usernameAktif);
                break;

            case 2:
                lihatWishlist(usernameAktif);
                break;

            case 3:
                hapusWishlist(usernameAktif);
                break;
        }

    } while(pilih != 4);
}


void tambahWishlist(string usernameAktif)
{
    system("cls");

    vector<Iphone> iphone;

    ifstream file("iphone.txt");

    Iphone hp;
    string stok;
    string harga;

    while(getline(file, hp.nama, '|'))
    {
        getline(file, stok, '|');
        getline(file, harga);

        hp.stok = atoi(stok.c_str());
        hp.harga = atoi(harga.c_str());

        iphone.push_back(hp);
    }

    file.close();

    cout << "========================================" << endl;
    cout << "         TAMBAH WISHLIST" << endl;
    cout << "========================================" << endl;

    for(int i = 0; i < iphone.size(); i++)
    {
        cout << i + 1 << ". "
             << iphone[i].nama
             << " | Rp " << iphone[i].harga
             << endl;
    }

    int pilih;

    cout << "\nPilih iPhone : ";
    cin >> pilih;

    if(pilih < 1 || pilih > iphone.size())
    {
        cout << "\nPilihan tidak valid!" << endl;
        pauseProgram();
        return;
    }

    ofstream wishlist("wishlist.txt", ios::app);

    wishlist << usernameAktif << "|"
             << iphone[pilih - 1].nama
             << endl;

    wishlist.close();

    cout << "\nBerhasil ditambahkan ke Wishlist." << endl;

    pauseProgram();
}

void lihatWishlist(string usernameAktif)
{
    system("cls");

    ifstream file("wishlist.txt");

    Wishlist wishlist;

    bool ada = false;

    cout << "==========================================" << endl;
    cout << "           WISHLIST SAYA" << endl;
    cout << "==========================================" << endl;

    while(getline(file, wishlist.username, '|'))
    {
        getline(file, wishlist.namaIphone);

        if(wishlist.username == usernameAktif)
        {
            ada = true;
            cout << "- " << wishlist.namaIphone << endl;
        }
    }

    if(!ada)
    {
        cout << "Wishlist masih kosong." << endl;
    }

    file.close();

    pauseProgram();
}

void hapusWishlist(string usernameAktif)
{
    system("cls");

    ifstream file("wishlist.txt");
    ofstream temp("temp.txt");

    Wishlist wishlist;

    string namaHapus;

    bool ditemukan = false;

    cin.ignore();

    cout << "==========================================" << endl;
    cout << "         HAPUS WISHLIST" << endl;
    cout << "==========================================" << endl;

    cout << "Masukkan Nama iPhone : ";
    getline(cin, namaHapus);

    while(getline(file, wishlist.username, '|'))
    {
        getline(file, wishlist.namaIphone);

        if(wishlist.username == usernameAktif &&
           wishlist.namaIphone == namaHapus)
        {
            ditemukan = true;
            continue;
        }

        temp << wishlist.username << "|"
             << wishlist.namaIphone
             << endl;
    }

    file.close();
    temp.close();

    remove("wishlist.txt");
    rename("temp.txt","wishlist.txt");

    if(ditemukan)
        cout << "\nWishlist berhasil dihapus." << endl;
    else
        cout << "\nData tidak ditemukan." << endl;

    pauseProgram();
}


string levelMember(string usernameAktif)
{
    ifstream file("transaksi.txt");

    if(!file.is_open())
        return "Bronze";

    Transaksi transaksi;

    int jumlah = 0;

    while(getline(file, transaksi.id, '|'))
    {
        getline(file, transaksi.customer, '|');
        getline(file, transaksi.iphone, '|');
        getline(file, transaksi.lama, '|');
        getline(file, transaksi.total);

        if(transaksi.customer == usernameAktif)
        {
            jumlah++;
        }
    }

    file.close();

    if(jumlah > 10)
        return "Platinum";

    if(jumlah >= 6)
        return "Gold";

    if(jumlah >= 3)
        return "Silver";

    return "Bronze";
}
		
		Transaksi transaksi;
		
		bool ada=false;
		
		string keyword;

void manajemenStok() {

    system("cls");

    ifstream file("iphone.txt");

    Iphone hp;
    
    string stokStr;
    string hargaStr;

    int no = 1;

    cout << "============================================================" << endl;
    cout << "                 LAPORAN STOK IPHONE                        " << endl;
    cout << "============================================================" << endl;

    cout << "No\tNama iPhone\t\tStok\tStatus" << endl;

    // MEMBACA DATA STOK
    while(getline(file, hp.nama, '|')) {

        getline(file, stokStr, '|');
        getline(file, hargaStr);

        hp.stok = atoi(stokStr.c_str());
hp.harga = atoi(hargaStr.c_str());

        cout << no++ << "\t"
             << hp.nama << "\t\t"
             << hp.stok << "\t";

        // MONITORING STOK
        if(hp.stok <= 0) {

            cout << "STOK HABIS";
        }
        else if(hp.stok <= 2) {

            cout << "STOK MENIPIS";
        }
        else {

            cout << "TERSEDIA";
        }

        cout << endl;
    }

    file.close();

    cout << "\n============================================================" << endl;
    cout << "KETERANGAN :" << endl;
    cout << "- Admin dapat melihat seluruh stok iPhone" << endl;
    cout << "- Sistem memonitor stok habis dan stok menipis" << endl;
    cout << "- Data stok tersimpan di file iphone.txt" << endl;
    cout << "============================================================" << endl;

    system("pause");
}

void simpanDataTXT() {

    system("cls");

    Customer customer;

    cout << "==================================================" << endl;
    cout << "            SIMPAN DATA CUSTOMER                  " << endl;
    cout << "==================================================" << endl;

    cin.ignore();

    // INPUT DATA
    cout << "Input Nama     : ";
    getline(cin, customer.nama);

    cout << "Input Username : ";
    getline(cin, customer.username);

    cout << "Input Password : ";
    getline(cin, customer.password);

    cout << "Input Email    : ";
    getline(cin, customer.email);

    cout << "Input No HP    : ";
    getline(cin, customer.hp);

    // MEMBUKA FILE TXT
    ofstream file("customer.txt", ios::app);

    // SIMPAN DATA
    file
<< customer.nama << "|"
<< customer.username << "|"
<< customer.password << "|"
<< customer.email << "|"
<< customer.hp << endl;

    // TUTUP FILE
    file.close();

    cout << "\n======================================" << endl;
    cout << "      DATA BERHASIL DISIMPAN         " << endl;
    cout << "======================================" << endl;

    system("pause");
}





// ===================== PROFIL USER =====================
// Fungsi : Menampilkan data profil user yang sedang login
// =======================================================
void tampilProfil(string usernameAktif) {
	

    system("cls");
    tampilLogo(); // tampilkan judul program

    //=========================================================
// PERBAIKAN BUG #4
// Profil membaca customer.txt
//=========================================================
ifstream file("customer.txt");

    Customer customer;

    // mencari data user di file
    //=========================================================
// PERBAIKAN BUG #5
// Membaca data customer dengan delimiter '|'
//=========================================================
while(getline(file, customer.nama, '|')) {

    getline(file, customer.username, '|');
    getline(file, customer.password, '|');
    getline(file, customer.email, '|');
    getline(file, customer.hp);

    if(customer.username == usernameAktif) {

        cout << "\nPROFIL USER" << endl;
        cout << "====================================" << endl;

        cout << "Nama     : " << customer.nama << endl;
        cout << "Username : " << customer.username << endl;
        cout << "Email    : " << customer.email << endl;
        cout << "No HP    : " << customer.hp << endl;
    }
}

    file.close();

    pauseProgram(); // jeda program
}

//=========================================================
// TAMBAH FITUR : EDIT PROFIL USER
//=========================================================

void editProfil(string usernameAktif)
{
    system("cls");

    tampilLogo();

    ifstream file("customer.txt");
    ofstream temp("temp.txt");

    Customer customer;

    bool ditemukan = false;

    while(getline(file, customer.nama, '|'))
    {
        getline(file, customer.username, '|');
		getline(file, customer.password, '|');
		getline(file, customer.email, '|');
		getline(file, customer.hp);

        if(customer.username == usernameAktif)
        {
            ditemukan=true;

            cout<<"\n========== EDIT PROFIL ==========\n";

            cin.ignore();

            cout << "Nama Baru     : ";
			getline(cin, customer.nama);

			cout << "Password Baru : ";
			getline(cin, customer.password);

			cout << "Email Baru    : ";
			getline(cin, customer.email);
			
			cout << "Nomor HP Baru : ";
			getline(cin, customer.hp);
        }

        temp << customer.nama << "|"
		     << customer.username << "|"
		     << customer.password << "|"
		     << customer.email << "|"
		     << customer.hp << endl;
    }

    file.close();
    temp.close();

    remove("customer.txt");
    rename("temp.txt","customer.txt");

    if(ditemukan)
        cout<<"\nProfil berhasil diperbarui!\n";
    else
        cout<<"\nUser tidak ditemukan!\n";

    pauseProgram();
}

//=========================================================
// TAMBAH FITUR : REVIEW DAN RATING CUSTOMER
//=========================================================

void reviewCustomer(string usernameAktif)
{
    system("cls");

    tampilLogo();

    int rating;
    string komentar;

    cout<<"=========================================="<<endl;
    cout<<"         REVIEW PENYEWAAN IPHONE"<<endl;
    cout<<"=========================================="<<endl;

    cout<<"Berikan Rating (1-5) : ";
    cin>>rating;

    while(rating<1 || rating>5)
    {
        cout<<"Rating harus 1 sampai 5 : ";
        cin>>rating;
    }

    cin.ignore();

    cout<<"Komentar : ";
    getline(cin,komentar);

    ofstream file("review.txt",ios::app);

    file<<usernameAktif<<"|"
        <<rating<<"|"
        <<komentar<<endl;

    file.close();

    cout<<"\n=========================================="<<endl;
    cout<<"Review berhasil disimpan."<<endl;
    cout<<"Terima kasih atas penilaian Anda."<<endl;
    cout<<"=========================================="<<endl;

    pauseProgram();
}

//=========================================================
// TAMBAH FITUR : LIHAT REVIEW CUSTOMER
//=========================================================

void lihatReview()
{
    system("cls");

    tampilLogo();

    ifstream file("review.txt");

    Review review;

    int no=1;

    cout<<"==============================================================="<<endl;
    cout<<"                 REVIEW CUSTOMER"<<endl;
    cout<<"==============================================================="<<endl;

    while(getline(file, review.username, '|'))
    {
        getline(file, review.rating, '|');
getline(file, review.komentar);

        cout<<no++<<". "<<review.username<<endl;

        cout<<"Rating : ";

        for(int i=0;i<atoi(review.rating.c_str());i++)
            cout<<"*";

        cout<<endl;

        cout<<"Komentar : "<<review.komentar<<endl;

        cout<<"---------------------------------------------------------"<<endl;
    }

    file.close();

    pauseProgram();
}



// ===================== MENU USER =====================
// Fungsi : Menampilkan menu user dan data iPhone
// =====================================================
void menuUser(string usernameAktif) {

    vector<Iphone> iphone;

    ifstream file("iphone.txt");

    Iphone hp;
    string stok, harga;
    int pilih;

    // ===================== BACA DATA IPHONE =====================
    while (getline(file, hp.nama, '|')) {

        getline(file, stok, '|');
        getline(file, harga);

        hp.stok = atoi(stok.c_str());
        hp.harga = atoi(harga.c_str());

        iphone.push_back(hp);
    }

    file.close();

    // ===================== MENU USER =====================
    do {

        system("cls");
        tampilLogo();

        cout << "\nSelamat datang, " << usernameAktif << endl;
        cout << "==============================================" << endl;

        cout << "==================================================" << endl;
		cout << "                 MENU USER                        " << endl;
		cout << "==================================================" << endl;
		cout << "1. Dashboard Saya" << endl;
		cout << "2. Lihat Daftar iPhone" << endl;
		cout << "3. Wishlist iPhone" << endl;
		cout << "4. Sewa iPhone" << endl;
		cout << "5. Pengembalian iPhone" << endl;
		cout << "6. Riwayat Saya" << endl;
		cout << "7. Profil Saya" << endl;
		cout << "8. Edit Profil" << endl;
		cout << "9. Review" << endl;
		cout << "10. Reservasi iPhone" << endl;
		cout << "11. Sewa iPhone" << endl;
		cout << "12. Membership saya" << endl;
		cout << "13. Tukar Poin" << endl;
		cout << "14. Notifikasi" << endl;
		cout << "15. Logout" << endl;

        cout << "==============================================" << endl;

        cout<<"Pilih Menu : ";
        pilih = inputAngka();

        switch(pilih)
				{
				case 1:
				    dashboardUser(usernameAktif);
				    break;
				
				case 2:
				    tampilDataIphone(iphone);
				    break;
				
				case 3:
				    menuWishlist(usernameAktif);
				    break;
				
				case 4:
				    sewaIphone(usernameAktif);
				    break;
				
				case 5:
				    pengembalianIphone();
				    break;
				
				case 6:
				    riwayatSaya(usernameAktif);
				    break;
				
				case 7:
				    tampilProfil(usernameAktif);
				    break;
				
				case 8:
				    editProfil(usernameAktif);
				    break;
				
				case 9:
				    reviewCustomer(usernameAktif);
				    break;
				    
				case 10:
					reservasiIphone(usernameAktif);
    				break;
    				
    			case 11:
    				sewaIphone(usernameAktif);
    				break;
    				
    			case 12:
    				lihatMembership(usernameAktif);
    				break;

				case 13:
    				tukarPoin(usernameAktif);
    				break;
    				
    			case 14:
    				lihatNotifikasi(usernameAktif);
    				tandaiSudahDibaca(usernameAktif);
    				break;
				
				case 15:
				    cout << "\nLogout berhasil!" << endl;
				    pauseProgram();
				    break;
				
				default:
				    cout << "\nMenu tidak tersedia!" << endl;
				    pauseProgram();
				}

    } while (pilih != 10);
}

void tambahIphone() {

    system("cls");

    Iphone hp;

    ofstream file("iphone.txt", ios::app);

    cout << "====================================" << endl;
    cout << "         TAMBAH IPHONE             " << endl;
    cout << "====================================" << endl;

    cin.ignore();

    cout << "Masukkan Nama iPhone : ";
    getline(cin, hp.nama);

    cout << "Masukkan Stok        : ";
    cin >> hp.stok;

    cout << "Masukkan Harga       : ";
    cin >> hp.harga;

    file << hp.nama << "|"
         << hp.stok << "|"
         << hp.harga << endl;

    file.close();

    cout << "\nData berhasil ditambahkan!" << endl;

    system("pause");
}

void tampilIphone() {

    system("cls");

    ifstream file("iphone.txt");

    if (!file.is_open()) {
        cout << "File iphone.txt tidak ditemukan!" << endl;
        system("pause");
        return;
    }

    Iphone hp;
    string stok, harga;
    
    cout << left
     << setw(5) << "No"
     << setw(25) << "Nama iPhone"
     << setw(10) << "Stok"
     << setw(15) << "Harga"
     << endl;

cout << "==========================================================" << endl;

int no = 1;

while (getline(file, hp.nama, '|') &&
       getline(file, stok, '|') &&
       getline(file, harga)) {

    hp.stok = atoi(stok.c_str());
    hp.harga = atoi(harga.c_str());

    cout << left
         << setw(5)  << no++
         << setw(25) << hp.nama
         << setw(10) << hp.stok
         << setw(15) << hp.harga
         << endl;
}

    file.close();

    cout << "----------------------------------------------\n";

    system("pause");
}

// ===================== EDIT IPHONE =====================
// Fungsi : Mengubah data iPhone berdasarkan nama
// =======================================================

void editIphone() {

    system("cls");

    ifstream file("iphone.txt");
    ofstream temp("temp.txt");

    Iphone hp;

string cariNama;

bool ditemukan = false;

    cin.ignore();

    cout << "Masukkan Nama iPhone : ";
    getline(cin, cariNama);

    while(getline(file,hp.nama,'|'))
{
    string stokStr;
    string hargaStr;

    getline(file, stokStr, '|');
    getline(file, hargaStr);

        if(hp.nama == cariNama)
        {
            ditemukan = true;

            cout << "\nData ditemukan!\n";

            cout << "Nama Baru  : ";
            getline(cin, hp.nama);

            cout << "Stok Baru  : ";
            cin >> hp.stok;

            cout << "Harga Baru : ";
            cin >> hp.harga;
            cin.ignore();
        }

        temp << hp.nama << "|"
             << hp.stok << "|"
             << hp.harga << endl;
    }

    file.close();
    temp.close();

    remove("iphone.txt");
    rename("temp.txt", "iphone.txt");

    if(ditemukan)
        cout << "\nData berhasil diupdate!" << endl;
    else
        cout << "\nData tidak ditemukan!" << endl;

    system("pause");
}

// ===================== HAPUS IPHONE =====================
// Fungsi : Menghapus data iPhone berdasarkan nama
// ========================================================

void hapusIphone() {

    system("cls");

    ifstream file("iphone.txt");
    ofstream temp("temp.txt");

    Iphone hp;

string cariNama;

bool ditemukan = false;

    // ===================== HEADER =====================
    cout << "====================================" << endl;
    cout << "         HAPUS IPHONE              " << endl;
    cout << "====================================" << endl;

    cin.ignore();

    cout << "Masukkan Nama iPhone : ";
    getline(cin, cariNama);

    // ===================== PROSES HAPUS =====================
    while(getline(file, hp.nama, '|'))
{
    string stokStr;
    string hargaStr;

    getline(file, stokStr, '|');
    getline(file, hargaStr);

    hp.stok = atoi(stokStr.c_str());
    hp.harga = atoi(hargaStr.c_str());

    if(hp.nama == cariNama)
    {
        ditemukan = true;
        continue;
    }

    temp << hp.nama << "|"
         << hp.stok << "|"
         << hp.harga << endl;
}

    file.close();
    temp.close();

    // ===================== UPDATE FILE =====================
    remove("iphone.txt");
    rename("temp.txt", "iphone.txt");

    // ===================== HASIL =====================
    if (ditemukan) {
        cout << "\nData berhasil dihapus!" << endl;
    } else {
        cout << "\nData tidak ditemukan!" << endl;
    }

    system("pause");
}

// ======================= MENU ADMIN =======================
// Fungsi : Menampilkan menu admin dan mengatur pilihan fitur
// ==========================================================

void menuAdmin() {

    int pilih;

    do {

        system("cls"); // bersihkan layar

        // ======================= TAMPILAN MENU =======================
        cout << "================ MENU ADMIN ================\n";
        cout << "1. Tambah iPhone\n";
        cout << "2. Tampilkan iPhone\n";
        cout << "3. Edit iPhone\n";
        cout << "4. Hapus iPhone\n";
        cout << "5. Kelola Customer\n";
        cout << "6. Riwayat Penyewaan" << endl;
        cout << "7. Laporan Stok iPhone" << endl;
        cout << "8. Logout\n";
        cout << "9. Dashboard Statistik" << endl;
        cout << "10. Pencarian Data" << endl;
        cout << "11. Sorting Data" << endl;
        cout << "12. Lihat Review Customer" << endl;
        cout << "13. Laporan Pendapatan" << endl;
        cout << "14. Statistik Penyewaan" << endl;
        cout << "15. Top 5 iPhone Terlaris" << endl;
        cout << "16. Top Customer" << endl;
        cout << "17. Backup Database" << endl;
        cout << "18. Restore Database" << endl;
        cout << "19. Export Laporan" << endl;
        cout << "20. Notifikasi Stok" << endl;
        cout << "21. Kelola Reservasi" << endl;
        cout << "22. Data Membership" << endl;
        cout << "23. Kelola Promo" << endl;
        cout << "24. Data Kerusakan & Servis" << endl;
        cout << "25. Kelola Notifikasi" << endl;
        cout << "============================================\n";

        // ======================= INPUT =======================
        cout << "Pilih menu (1-25): ";
        cin >> pilih;

        cout << "============================================\n";

        // ======================= PROSES =======================
        switch(pilih) {

            case 1:
                tambahIphone();   // tambah data iPhone
                break;

            case 2:
                tampilIphone();   // tampilkan data iPhone
                break;

            case 3:
                editIphone();     // edit data iPhone
                break;

            case 4:
                hapusIphone();    // hapus data iPhone
                break;
                
            case 5:
            	kelolaCustomer();
            	break;
            	
            case 6:
            	riwayatPenyewaan();
            	break;
            	
            case 7:
                manajemenStok();
                break;

            case 8:
                cout << "Logout berhasil!\n";
                system("pause");
                break;
                
            case 9:
				dashboardStatistik();
				break;
				
			case 10:
                pencarianData();
                break;
                
            case 11:
                sortingDataIphone();
                break;
                
            case 12:
                lihatReview();
                break;
                
            case 13:
                laporanPendapatan();
                break;
                
            case 14:
                statistikPenyewaan();
                break;
                
            case 15:
			    cout << "\nFitur sedang dalam pengembangan." << endl;
			    pauseProgram();
			    break;
			    
			case 16:
                topCustomer();
                break;
                
            case 17:
                backupDatabase();
                break;
    
            case 18:
                restoreDatabase();
                break;
                
            case 19:
                exportLaporan();
                break;
                
            case 20:
                notifikasiStok();
                break;
                
            case 21:
    			menuReservasiAdmin();
    			break;
    			
    		case 22:
    			semuaMember();
    			break;
    			
    		case 23:
    			menuPromoAdmin();
    			break;
    			
    		case 24:
    			menuKerusakanServis();
    			break;
    			
    		case 25:
    			menuNotifikasiAdmin();
    			break;
                
            default:
                cout << "Menu tidak tersedia!\n";
                system("pause");
                break;
        }

    } while(pilih != 8);
}

void exportLaporan()
{
    system("cls");

    int pilih;

    cout<<"===================================="<<endl;
    cout<<"        EXPORT LAPORAN"<<endl;
    cout<<"===================================="<<endl;

    cout<<"1. Customer"<<endl;
    cout<<"2. iPhone"<<endl;
    cout<<"3. Transaksi"<<endl;
    cout<<"4. Pembayaran"<<endl;
    cout<<"5. Semua"<<endl;
    cout<<"6. Kembali"<<endl;

    cout<<"\nPilih : ";
    cin>>pilih;

    switch(pilih)
    {
        case 1:
            salinFile("customer.txt","laporan_customer.txt");
            break;

        case 2:
            salinFile("iphone.txt","laporan_iphone.txt");
            break;

        case 3:
            salinFile("transaksi.txt","laporan_transaksi.txt");
            break;

        case 4:
            salinFile("pembayaran.txt","laporan_pembayaran.txt");
            break;

        case 5:

            salinFile("customer.txt","laporan_customer.txt");
            salinFile("iphone.txt","laporan_iphone.txt");
            salinFile("transaksi.txt","laporan_transaksi.txt");
            salinFile("pembayaran.txt","laporan_pembayaran.txt");

            break;

        case 6:
            return;

        default:
            cout<<"Pilihan tidak tersedia!"<<endl;
            pauseProgram();
            return;
    }

    cout<<"\n===================================="<<endl;
    cout<<"Export berhasil!"<<endl;
    cout<<"File laporan berhasil dibuat."<<endl;
    cout<<"===================================="<<endl;

    pauseProgram();
}

void notifikasiStok()
{
    system("cls");

    ifstream file("iphone.txt");

    if(!file.is_open())
    {
        cout<<"File iphone tidak ditemukan!"<<endl;
        pauseProgram();
        return;
    }

    Iphone hp;

    string stokStr;
    string hargaStr;

    bool ada=false;

    cout<<"============================================"<<endl;
    cout<<"        NOTIFIKASI STOK IPHONE"<<endl;
    cout<<"============================================"<<endl;

    while(getline(file,hp.nama,'|'))
    {
        getline(file,stokStr,'|');
        getline(file,hargaStr);

        hp.stok=atoi(stokStr.c_str());
        hp.harga=atoi(hargaStr.c_str());

        if(hp.stok<=2)
        {
            ada=true;

            cout<<"? "<<hp.nama<<endl;
            cout<<"Sisa Stok : "<<hp.stok<<endl;
            cout<<"--------------------------------------"<<endl;
        }
    }

    if(!ada)
    {
        cout<<"Semua stok masih aman."<<endl;
    }

    file.close();

    pauseProgram();
}

void salinFile(string sumber, string tujuan)
{
    ifstream in(sumber.c_str(), ios::binary);
    ofstream out(tujuan.c_str(), ios::binary);

    char c;

    while(in.get(c))
    {
        out.put(c);
    }

    in.close();
    out.close();
}

void backupDatabase()
{
    system("cls");

    cout<<"========================================"<<endl;
    cout<<"          BACKUP DATABASE"<<endl;
    cout<<"========================================"<<endl;

    salinFile("customer.txt","backup_customer.txt");
    cout<<"[OK] customer.txt"<<endl;

    salinFile("iphone.txt","backup_iphone.txt");
    cout<<"[OK] iphone.txt"<<endl;

    salinFile("transaksi.txt","backup_transaksi.txt");
    cout<<"[OK] transaksi.txt"<<endl;

    salinFile("pembayaran.txt","backup_pembayaran.txt");
    cout<<"[OK] pembayaran.txt"<<endl;

    cout<<endl;
    cout<<"Semua database berhasil dibackup."<<endl;

    pauseProgram();
}

void restoreDatabase()
{
    system("cls");

    int pilih;

    cout<<"=========================================="<<endl;
    cout<<"         RESTORE DATABASE"<<endl;
    cout<<"=========================================="<<endl;

    cout<<"1. Restore Customer"<<endl;
    cout<<"2. Restore iPhone"<<endl;
    cout<<"3. Restore Transaksi"<<endl;
    cout<<"4. Restore Pembayaran"<<endl;
    cout<<"5. Restore Semua"<<endl;
    cout<<"6. Kembali"<<endl;

    cout<<"\nPilih : ";
    cin>>pilih;

    switch(pilih)
    {
        case 1:
            salinFile("backup_customer.txt","customer.txt");
            break;

        case 2:
            salinFile("backup_iphone.txt","iphone.txt");
            break;

        case 3:
            salinFile("backup_transaksi.txt","transaksi.txt");
            break;

        case 4:
            salinFile("backup_pembayaran.txt","pembayaran.txt");
            break;

        case 5:

            salinFile("backup_customer.txt","customer.txt");
            salinFile("backup_iphone.txt","iphone.txt");
            salinFile("backup_transaksi.txt","transaksi.txt");
            salinFile("backup_pembayaran.txt","pembayaran.txt");

            break;

        case 6:
            return;

        default:
            cout<<"Pilihan salah!"<<endl;
    }

    cout<<endl;
    cout<<"Restore berhasil!"<<endl;

    pauseProgram();
}

void topCustomer()
{
    system("cls");

    ifstream file("transaksi.txt");

    if(!file.is_open())
    {
        cout<<"File transaksi tidak ditemukan!"<<endl;
        pauseProgram();
        return;
    }

    vector<StatistikCustomer> data;

    Transaksi transaksi;

    while(getline(file, transaksi.id, '|'))
    {
        getline(file, transaksi.customer, '|');
        getline(file, transaksi.iphone, '|');
        getline(file, transaksi.lama, '|');
        getline(file, transaksi.total);

        bool ada=false;

        for(int i=0;i<data.size();i++)
        {
            if(data[i].username==transaksi.customer)
            {
                data[i].jumlah++;
                ada=true;
                break;
            }
        }

        if(!ada)
        {
            StatistikCustomer baru;

            baru.username=transaksi.customer;
            baru.jumlah=1;

            data.push_back(baru);
        }
    }

    file.close();

    for(int i=0;i<data.size()-1;i++)
    {
        for(int j=i+1;j<data.size();j++)
        {
            if(data[j].jumlah>data[i].jumlah)
            {
                StatistikCustomer temp=data[i];
                data[i]=data[j];
                data[j]=temp;
            }
        }
    }

    cout<<"===================================================="<<endl;
    cout<<"                  TOP CUSTOMER"<<endl;
    cout<<"===================================================="<<endl;

    cout<<"No\tUsername\tJumlah"<<endl;

    int batas=5;

    if(data.size()<5)
        batas=data.size();

    for(int i=0;i<batas;i++)
    {
        cout<<i+1<<"\t"
            <<data[i].username<<"\t\t"
            <<data[i].jumlah<<" Kali"<<endl;
    }

    pauseProgram();
}


void loading()
{
    system("cls");

    cout << "Memuat Sistem";

    for(int i=0; i<6; i++)
    {
        cout << ".";
        system("ping 127.0.0.1 -n 2 > nul");
    }

    cout << endl;
}

//=========================================================
// GENERATE ID RESERVASI
//=========================================================

string generateIDReservasi()
{
    ifstream file("reservasi.txt");

    string baris;

    int jumlah = 0;

    while(getline(file,baris))
    {
        if(baris!="")
            jumlah++;
    }

    file.close();

    jumlah++;

    stringstream ss;

    ss<<"RSV";

    if(jumlah<10)
        ss<<"000";

    else if(jumlah<100)
        ss<<"00";

    else if(jumlah<1000)
        ss<<"0";

    ss<<jumlah;

    return ss.str();
}

//=========================================================
// RESERVASI IPHONE
//=========================================================

void reservasiIphone(string usernameAktif)
{
    system("cls");

    vector<Iphone> iphone;

    Iphone hp;

    ifstream file("iphone.txt");

    string stok;
    string harga;

    while(getline(file,hp.nama,'|'))
    {
        getline(file,stok,'|');
        getline(file,harga);

        hp.stok=atoi(stok.c_str());
        hp.harga=atoi(harga.c_str());

        iphone.push_back(hp);
    }

    file.close();

    cout<<"======================================"<<endl;
    cout<<"        RESERVASI IPHONE"<<endl;
    cout<<"======================================"<<endl;

    for(int i=0;i<iphone.size();i++)
    {
        cout<<i+1<<". "
            <<iphone[i].nama
            <<" | Stok : "
            <<iphone[i].stok
            <<endl;
    }

    int pilih;

    cout<<"\nPilih iPhone : ";
    cin>>pilih;

    if(pilih<1 || pilih>iphone.size())
    {
        cout<<"Pilihan tidak valid!"<<endl;
        pauseProgram();
        return;
    }

    Reservasi data;

    data.idReservasi=generateIDReservasi();

    data.username=usernameAktif;

    data.namaIphone=iphone[pilih-1].nama;

    cin.ignore();

    cout<<"Tanggal Reservasi : ";
    getline(cin,data.tanggalReservasi);

    data.status="Menunggu";

    ofstream simpan("reservasi.txt",ios::app);

    simpan<<data.idReservasi<<"|"
          <<data.username<<"|"
          <<data.namaIphone<<"|"
          <<data.tanggalReservasi<<"|"
          <<data.status
          <<endl;

    simpan.close();

    cout<<"\nReservasi berhasil dibuat."<<endl;

    pauseProgram();
}

//=========================================================
// LIHAT RESERVASI
//=========================================================

void lihatReservasi()
{
    system("cls");

    ifstream file("reservasi.txt");

    Reservasi data;

    int no=1;

    cout<<"============================================================"<<endl;
    cout<<"                  DATA RESERVASI"<<endl;
    cout<<"============================================================"<<endl;

    cout<<left
        <<setw(5)<<"No"
        <<setw(10)<<"ID"
        <<setw(15)<<"User"
        <<setw(20)<<"iPhone"
        <<setw(15)<<"Tanggal"
        <<setw(15)<<"Status"<<endl;

    while(getline(file,data.idReservasi,'|'))
    {
        getline(file,data.username,'|');
        getline(file,data.namaIphone,'|');
        getline(file,data.tanggalReservasi,'|');
        getline(file,data.status);

        cout<<left
            <<setw(5)<<no++
            <<setw(10)<<data.idReservasi
            <<setw(15)<<data.username
            <<setw(20)<<data.namaIphone
            <<setw(15)<<data.tanggalReservasi
            <<setw(15)<<data.status
            <<endl;
    }

    file.close();

    pauseProgram();
}

//=========================================================
// KONFIRMASI RESERVASI
//=========================================================

void konfirmasiReservasi()
{
    system("cls");

    ifstream file("reservasi.txt");

    ofstream temp("temp.txt");

    Reservasi data;

    string id;

    bool ditemukan=false;

    cin.ignore();

    cout<<"Masukkan ID Reservasi : ";
    getline(cin,id);

    while(getline(file,data.idReservasi,'|'))
    {
        getline(file,data.username,'|');
        getline(file,data.namaIphone,'|');
        getline(file,data.tanggalReservasi,'|');
        getline(file,data.status);

        if(data.idReservasi==id)
        {
            ditemukan=true;

            int pilih;

            cout<<"\n1. Setujui"<<endl;
            cout<<"2. Tolak"<<endl;
            cout<<"Pilih : ";
            cin>>pilih;

            if(pilih==1)
                data.status="Disetujui";
            else
                data.status="Ditolak";
        }

        temp<<data.idReservasi<<"|"
            <<data.username<<"|"
            <<data.namaIphone<<"|"
            <<data.tanggalReservasi<<"|"
            <<data.status
            <<endl;
    }

    file.close();
    temp.close();

    remove("reservasi.txt");
    rename("temp.txt","reservasi.txt");

    if(ditemukan)
        cout<<"\nReservasi berhasil diperbarui."<<endl;
    else
        cout<<"\nID tidak ditemukan."<<endl;

    pauseProgram();
}

//=========================================================
// HAPUS RESERVASI
//=========================================================

void hapusReservasi()
{
    system("cls");

    ifstream file("reservasi.txt");

    ofstream temp("temp.txt");

    Reservasi data;

    string id;

    bool ditemukan=false;

    cin.ignore();

    cout<<"Masukkan ID Reservasi : ";
    getline(cin,id);

    while(getline(file,data.idReservasi,'|'))
    {
        getline(file,data.username,'|');
        getline(file,data.namaIphone,'|');
        getline(file,data.tanggalReservasi,'|');
        getline(file,data.status);

        if(data.idReservasi==id)
        {
            ditemukan=true;
            continue;
        }

        temp<<data.idReservasi<<"|"
            <<data.username<<"|"
            <<data.namaIphone<<"|"
            <<data.tanggalReservasi<<"|"
            <<data.status
            <<endl;
    }

    file.close();
    temp.close();

    remove("reservasi.txt");
    rename("temp.txt","reservasi.txt");

    if(ditemukan)
        cout<<"\nReservasi berhasil dihapus."<<endl;
    else
        cout<<"\nData tidak ditemukan."<<endl;

    pauseProgram();
}

//=========================================================
// MENU RESERVASI ADMIN
//=========================================================

void menuReservasiAdmin()
{
    int pilih;

    do
    {
        system("cls");

        cout<<"======================================"<<endl;
        cout<<"        MENU RESERVASI ADMIN"<<endl;
        cout<<"======================================"<<endl;

        cout<<"1. Lihat Reservasi"<<endl;
        cout<<"2. Konfirmasi Reservasi"<<endl;
        cout<<"3. Hapus Reservasi"<<endl;
        cout<<"4. Kembali"<<endl;

        cout<<"\nPilih : ";
        cin>>pilih;

        switch(pilih)
        {
            case 1:
                lihatReservasi();
                break;

            case 2:
                konfirmasiReservasi();
                break;

            case 3:
                hapusReservasi();
                break;
        }

    }while(pilih!=4);
}

//=========================================================
// TAMBAH POIN MEMBER
//=========================================================

void tambahPoin(string username,int poinBaru)
{
    ifstream file("member.txt");

    ofstream temp("temp.txt");

    Member member;

    bool ditemukan=false;

    while(getline(file,member.username,'|'))
    {
        string poin;

        getline(file,poin,'|');
        getline(file,member.level);

        member.poin=atoi(poin.c_str());

        if(member.username==username)
        {
            ditemukan=true;

            member.poin+=poinBaru;
        }

        temp<<member.username<<"|"
            <<member.poin<<"|"
            <<member.level
            <<endl;
    }

    if(!ditemukan)
    {
        temp<<username<<"|"
            <<poinBaru<<"|"
            <<"Bronze"
            <<endl;
    }

    file.close();
    temp.close();

    remove("member.txt");
    rename("temp.txt","member.txt");

    updateLevelMember();
}

//=========================================================
// UPDATE LEVEL MEMBER
//=========================================================

void updateLevelMember()
{
    ifstream file("member.txt");

    ofstream temp("temp.txt");

    Member member;

    while(getline(file,member.username,'|'))
    {
        string poin;

        getline(file,poin,'|');
        getline(file,member.level);

        member.poin=atoi(poin.c_str());

        if(member.poin>=1000)
            member.level="Diamond";

        else if(member.poin>=700)
            member.level="Platinum";

        else if(member.poin>=400)
            member.level="Gold";

        else if(member.poin>=200)
            member.level="Silver";

        else
            member.level="Bronze";

        temp<<member.username<<"|"
            <<member.poin<<"|"
            <<member.level
            <<endl;
    }

    file.close();
    temp.close();

    remove("member.txt");
    rename("temp.txt","member.txt");
}

//=========================================================
// LIHAT MEMBERSHIP
//=========================================================

void lihatMembership(string usernameAktif)
{
    system("cls");

    ifstream file("member.txt");

    Member member;

    bool ada=false;

    while(getline(file,member.username,'|'))
    {
        string poin;

        getline(file,poin,'|');
        getline(file,member.level);

        member.poin=atoi(poin.c_str());

        if(member.username==usernameAktif)
        {
            ada=true;

            cout<<"========================================"<<endl;
            cout<<"        MEMBERSHIP SAYA"<<endl;
            cout<<"========================================"<<endl;

            cout<<"Username : "<<member.username<<endl;
            cout<<"Level    : "<<member.level<<endl;
            cout<<"Poin     : "<<member.poin<<endl;

            break;
        }
    }

    if(!ada)
    {
        cout<<"Belum memiliki membership."<<endl;
    }

    file.close();

    pauseProgram();
}

//=========================================================
// TUKAR POIN
//=========================================================

void tukarPoin(string usernameAktif)
{
    system("cls");

    ifstream file("member.txt");

    ofstream temp("temp.txt");

    Member member;

    bool ditemukan=false;

    while(getline(file,member.username,'|'))
    {
        string poin;

        getline(file,poin,'|');
        getline(file,member.level);

        member.poin=atoi(poin.c_str());

        if(member.username==usernameAktif)
        {
            ditemukan=true;

            cout<<"Poin Anda : "<<member.poin<<endl;

            if(member.poin>=100)
            {
                char pilih;

                cout<<"Tukar 100 poin menjadi Voucher Rp50.000 ? (Y/T) : ";
                cin>>pilih;

                if(pilih=='Y'||pilih=='y')
                {
                    member.poin-=100;

                    ofstream voucher("voucher_customer.txt",ios::app);

                    voucher<<usernameAktif
                           <<"|"
                           <<"POIN50000"
                           <<endl;

                    voucher.close();

                    cout<<"Voucher berhasil diperoleh."<<endl;
                }
            }
            else
            {
                cout<<"Poin belum mencukupi."<<endl;
            }
        }

        temp<<member.username<<"|"
            <<member.poin<<"|"
            <<member.level
            <<endl;
    }

    file.close();
    temp.close();

    remove("member.txt");
    rename("temp.txt","member.txt");

    if(!ditemukan)
    {
        cout<<"Data member tidak ditemukan."<<endl;
    }

    pauseProgram();
}

//=========================================================
// DATA MEMBER
//=========================================================

void semuaMember()
{
    system("cls");

    ifstream file("member.txt");

    Member member;

    int no=1;

    cout<<"============================================================"<<endl;
    cout<<"                DATA MEMBER"<<endl;
    cout<<"============================================================"<<endl;

    cout<<left
        <<setw(5)<<"No"
        <<setw(20)<<"Username"
        <<setw(15)<<"Poin"
        <<setw(15)<<"Level"
        <<endl;

    while(getline(file,member.username,'|'))
    {
        string poin;

        getline(file,poin,'|');
        getline(file,member.level);

        member.poin=atoi(poin.c_str());

        cout<<left
            <<setw(5)<<no++
            <<setw(20)<<member.username
            <<setw(15)<<member.poin
            <<setw(15)<<member.level
            <<endl;
    }

    file.close();

    pauseProgram();
}

//=========================================================
// TAMBAH PROMO
//=========================================================

void tambahPromo()
{
    system("cls");

    Promo promo;

    cin.ignore();

    cout<<"======================================"<<endl;
    cout<<"          TAMBAH PROMO"<<endl;
    cout<<"======================================"<<endl;

    cout<<"Kode Promo      : ";
    getline(cin,promo.kodePromo);

    cout<<"Nama Promo      : ";
    getline(cin,promo.namaPromo);

    cout<<"Diskon (%)      : ";
    cin>>promo.diskon;

    cin.ignore();

    cout<<"Tanggal Mulai   : ";
    getline(cin,promo.tanggalMulai);

    cout<<"Tanggal Selesai : ";
    getline(cin,promo.tanggalSelesai);

    promo.status="Aktif";

    ofstream file("promo.txt",ios::app);

    file<<promo.kodePromo<<"|"
        <<promo.namaPromo<<"|"
        <<promo.diskon<<"|"
        <<promo.tanggalMulai<<"|"
        <<promo.tanggalSelesai<<"|"
        <<promo.status
        <<endl;

    file.close();

    cout<<"\nPromo berhasil ditambahkan."<<endl;

    pauseProgram();
}

//=========================================================
// LIHAT PROMO
//=========================================================

void lihatPromo()
{
    system("cls");

    ifstream file("promo.txt");

    Promo promo;

    string diskon;

    int no=1;

    cout<<"=========================================================================="<<endl;
    cout<<"                           DAFTAR PROMO"<<endl;
    cout<<"=========================================================================="<<endl;

    cout<<left
        <<setw(5)<<"No"
        <<setw(12)<<"Kode"
        <<setw(25)<<"Nama Promo"
        <<setw(10)<<"Diskon"
        <<setw(15)<<"Status"
        <<endl;

    while(getline(file,promo.kodePromo,'|'))
    {
        getline(file,promo.namaPromo,'|');
        getline(file,diskon,'|');
        getline(file,promo.tanggalMulai,'|');
        getline(file,promo.tanggalSelesai,'|');
        getline(file,promo.status);

        promo.diskon=atoi(diskon.c_str());

        cout<<left
            <<setw(5)<<no++
            <<setw(12)<<promo.kodePromo
            <<setw(25)<<promo.namaPromo
            <<setw(10)<<promo.diskon
            <<setw(15)<<promo.status
            <<endl;
    }

    file.close();

    pauseProgram();
}

//=========================================================
// EDIT PROMO
//=========================================================

void editPromo()
{
    system("cls");

    ifstream file("promo.txt");
    ofstream temp("temp.txt");

    Promo promo;

    string diskon;
    string kode;

    bool ditemukan=false;

    cin.ignore();

    cout<<"Masukkan Kode Promo : ";
    getline(cin,kode);

    while(getline(file,promo.kodePromo,'|'))
    {
        getline(file,promo.namaPromo,'|');
        getline(file,diskon,'|');
        getline(file,promo.tanggalMulai,'|');
        getline(file,promo.tanggalSelesai,'|');
        getline(file,promo.status);

        promo.diskon=atoi(diskon.c_str());

        if(promo.kodePromo==kode)
        {
            ditemukan=true;

            cout<<"\nNama Promo Baru : ";
            getline(cin,promo.namaPromo);

            cout<<"Diskon Baru (%) : ";
            cin>>promo.diskon;

            cin.ignore();

            cout<<"Tanggal Mulai : ";
            getline(cin,promo.tanggalMulai);

            cout<<"Tanggal Selesai : ";
            getline(cin,promo.tanggalSelesai);
        }

        temp<<promo.kodePromo<<"|"
            <<promo.namaPromo<<"|"
            <<promo.diskon<<"|"
            <<promo.tanggalMulai<<"|"
            <<promo.tanggalSelesai<<"|"
            <<promo.status
            <<endl;
    }

    file.close();
    temp.close();

    remove("promo.txt");
    rename("temp.txt","promo.txt");

    if(ditemukan)
        cout<<"\nPromo berhasil diubah."<<endl;
    else
        cout<<"\nPromo tidak ditemukan."<<endl;

    pauseProgram();
}

//=========================================================
// HAPUS PROMO
//=========================================================

void hapusPromo()
{
    system("cls");

    ifstream file("promo.txt");
    ofstream temp("temp.txt");

    Promo promo;

    string diskon;
    string kode;

    bool ditemukan=false;

    cin.ignore();

    cout<<"Masukkan Kode Promo : ";
    getline(cin,kode);

    while(getline(file,promo.kodePromo,'|'))
    {
        getline(file,promo.namaPromo,'|');
        getline(file,diskon,'|');
        getline(file,promo.tanggalMulai,'|');
        getline(file,promo.tanggalSelesai,'|');
        getline(file,promo.status);

        if(promo.kodePromo==kode)
        {
            ditemukan=true;
            continue;
        }

        temp<<promo.kodePromo<<"|"
            <<promo.namaPromo<<"|"
            <<diskon<<"|"
            <<promo.tanggalMulai<<"|"
            <<promo.tanggalSelesai<<"|"
            <<promo.status
            <<endl;
    }

    file.close();
    temp.close();

    remove("promo.txt");
    rename("temp.txt","promo.txt");

    if(ditemukan)
        cout<<"\nPromo berhasil dihapus."<<endl;
    else
        cout<<"\nPromo tidak ditemukan."<<endl;

    pauseProgram();
}

//=========================================================
// AKTIFKAN / NONAKTIFKAN PROMO
//=========================================================

void aktifkanPromo()
{
    system("cls");

    ifstream file("promo.txt");
    ofstream temp("temp.txt");

    Promo promo;

    string diskon;
    string kode;

    bool ditemukan=false;

    cin.ignore();

    cout<<"Masukkan Kode Promo : ";
    getline(cin,kode);

    while(getline(file,promo.kodePromo,'|'))
    {
        getline(file,promo.namaPromo,'|');
        getline(file,diskon,'|');
        getline(file,promo.tanggalMulai,'|');
        getline(file,promo.tanggalSelesai,'|');
        getline(file,promo.status);

        if(promo.kodePromo==kode)
        {
            ditemukan=true;

            if(promo.status=="Aktif")
                promo.status="Nonaktif";
            else
                promo.status="Aktif";
        }

        temp<<promo.kodePromo<<"|"
            <<promo.namaPromo<<"|"
            <<diskon<<"|"
            <<promo.tanggalMulai<<"|"
            <<promo.tanggalSelesai<<"|"
            <<promo.status
            <<endl;
    }

    file.close();
    temp.close();

    remove("promo.txt");
    rename("temp.txt","promo.txt");

    if(ditemukan)
        cout<<"\nStatus promo berhasil diubah."<<endl;
    else
        cout<<"\nPromo tidak ditemukan."<<endl;

    pauseProgram();
}

//=========================================================
// CARI PROMO
//=========================================================

void cariPromo()
{
    system("cls");

    ifstream file("promo.txt");

    Promo promo;

    string diskon;
    string keyword;

    bool ditemukan=false;

    cin.ignore();

    cout<<"Masukkan Nama Promo : ";
    getline(cin,keyword);

    while(getline(file,promo.kodePromo,'|'))
    {
        getline(file,promo.namaPromo,'|');
        getline(file,diskon,'|');
        getline(file,promo.tanggalMulai,'|');
        getline(file,promo.tanggalSelesai,'|');
        getline(file,promo.status);

        promo.diskon=atoi(diskon.c_str());

        if(promo.namaPromo.find(keyword)!=string::npos)
        {
            ditemukan=true;

            cout<<"\nKode   : "<<promo.kodePromo<<endl;
            cout<<"Promo  : "<<promo.namaPromo<<endl;
            cout<<"Diskon : "<<promo.diskon<<"%"<<endl;
            cout<<"Status : "<<promo.status<<endl;
        }
    }

    if(!ditemukan)
        cout<<"\nPromo tidak ditemukan."<<endl;

    file.close();

    pauseProgram();
}

//=========================================================
// MENU PROMO ADMIN
//=========================================================

void menuPromoAdmin()
{
    int pilih;

    do
    {
        system("cls");

        cout<<"======================================"<<endl;
        cout<<"          MENU PROMO"<<endl;
        cout<<"======================================"<<endl;

        cout<<"1. Tambah Promo"<<endl;
        cout<<"2. Lihat Promo"<<endl;
        cout<<"3. Edit Promo"<<endl;
        cout<<"4. Hapus Promo"<<endl;
        cout<<"5. Aktif / Nonaktif Promo"<<endl;
        cout<<"6. Cari Promo"<<endl;
        cout<<"7. Kembali"<<endl;

        cout<<"\nPilih : ";
        cin>>pilih;

        switch(pilih)
        {
            case 1:
                tambahPromo();
                break;

            case 2:
                lihatPromo();
                break;

            case 3:
                editPromo();
                break;

            case 4:
                hapusPromo();
                break;

            case 5:
                aktifkanPromo();
                break;

            case 6:
                cariPromo();
                break;
        }

    }while(pilih!=7);
}

string generateIDKerusakan()
{
    ifstream file("kerusakan.txt");

    string baris;

    int jumlah=0;

    while(getline(file,baris))
        jumlah++;

    file.close();

    stringstream ss;

    ss<<"KR";

    ss<<setfill('0')<<setw(4)<<jumlah+1;

    return ss.str();
}

string generateIDServis()
{
    ifstream file("servis.txt");

    string baris;

    int jumlah=0;

    while(getline(file,baris))
        jumlah++;

    file.close();

    stringstream ss;

    ss<<"SV";

    ss<<setfill('0')<<setw(4)<<jumlah+1;

    return ss.str();
}

void tambahKerusakan()
{
    system("cls");

    Kerusakan data;

    data.idKerusakan=generateIDKerusakan();

    cin.ignore();

    cout<<"ID Transaksi        : ";
    getline(cin,data.idTransaksi);

    cout<<"Username            : ";
    getline(cin,data.username);

    cout<<"Nama iPhone         : ";
    getline(cin,data.namaIphone);

    cout<<"Jenis Kerusakan     : ";
    getline(cin,data.jenisKerusakan);

    cout<<"Tingkat Kerusakan   : ";
    getline(cin,data.tingkatKerusakan);

    cout<<"Biaya Perbaikan     : ";
    cin>>data.biayaPerbaikan;

    cin.ignore();

    cout<<"Tanggal             : ";
    getline(cin,data.tanggal);

    ofstream file("kerusakan.txt",ios::app);

    file<<data.idKerusakan<<"|"
        <<data.idTransaksi<<"|"
        <<data.username<<"|"
        <<data.namaIphone<<"|"
        <<data.jenisKerusakan<<"|"
        <<data.tingkatKerusakan<<"|"
        <<data.biayaPerbaikan<<"|"
        <<data.tanggal
        <<endl;

    file.close();

    cout<<"\nData kerusakan berhasil ditambahkan.";

    pauseProgram();
}

void lihatKerusakan()
{
    system("cls");

    ifstream file("kerusakan.txt");

    Kerusakan data;

    string biaya;

    cout<<"================ DATA KERUSAKAN ================\n\n";

    while(getline(file,data.idKerusakan,'|'))
    {
        getline(file,data.idTransaksi,'|');
        getline(file,data.username,'|');
        getline(file,data.namaIphone,'|');
        getline(file,data.jenisKerusakan,'|');
        getline(file,data.tingkatKerusakan,'|');
        getline(file,biaya,'|');
        getline(file,data.tanggal);

        data.biayaPerbaikan=atoi(biaya.c_str());

        cout<<"ID          : "<<data.idKerusakan<<endl;
        cout<<"Transaksi   : "<<data.idTransaksi<<endl;
        cout<<"User        : "<<data.username<<endl;
        cout<<"iPhone      : "<<data.namaIphone<<endl;
        cout<<"Kerusakan   : "<<data.jenisKerusakan<<endl;
        cout<<"Tingkat     : "<<data.tingkatKerusakan<<endl;
        cout<<"Biaya       : "<<data.biayaPerbaikan<<endl;
        cout<<"Tanggal     : "<<data.tanggal<<endl;

        cout<<"-----------------------------------"<<endl;
    }

    file.close();

    pauseProgram();
}

void tambahServis()
{
    system("cls");

    Servis data;

    data.idServis=generateIDServis();

    cin.ignore();

    cout<<"Nama iPhone        : ";
    getline(cin,data.namaIphone);

    cout<<"Jenis Kerusakan    : ";
    getline(cin,data.jenisKerusakan);

    cout<<"Nama Teknisi       : ";
    getline(cin,data.teknisi);

    cout<<"Tanggal Masuk      : ";
    getline(cin,data.tanggalMasuk);

    data.tanggalSelesai="-";

    data.status="Dalam Servis";

    ofstream file("servis.txt",ios::app);

    file<<data.idServis<<"|"
        <<data.namaIphone<<"|"
        <<data.jenisKerusakan<<"|"
        <<data.teknisi<<"|"
        <<data.tanggalMasuk<<"|"
        <<data.tanggalSelesai<<"|"
        <<data.status
        <<endl;

    file.close();

    cout<<"\nData servis berhasil ditambahkan.";

    pauseProgram();
}

void lihatServis()
{
    system("cls");

    ifstream file("servis.txt");

    Servis data;

    cout<<"================ DATA SERVIS ================\n\n";

    while(getline(file,data.idServis,'|'))
    {
        getline(file,data.namaIphone,'|');
        getline(file,data.jenisKerusakan,'|');
        getline(file,data.teknisi,'|');
        getline(file,data.tanggalMasuk,'|');
        getline(file,data.tanggalSelesai,'|');
        getline(file,data.status);

        cout<<"ID Servis      : "<<data.idServis<<endl;
        cout<<"iPhone         : "<<data.namaIphone<<endl;
        cout<<"Kerusakan      : "<<data.jenisKerusakan<<endl;
        cout<<"Teknisi        : "<<data.teknisi<<endl;
        cout<<"Masuk          : "<<data.tanggalMasuk<<endl;
        cout<<"Selesai        : "<<data.tanggalSelesai<<endl;
        cout<<"Status         : "<<data.status<<endl;

        cout<<"--------------------------------"<<endl;
    }

    file.close();

    pauseProgram();
}

void updateStatusServis()
{
    system("cls");

    ifstream file("servis.txt");

    ofstream temp("temp.txt");

    Servis data;

    string id;

    cin.ignore();

    cout<<"Masukkan ID Servis : ";
    getline(cin,id);

    while(getline(file,data.idServis,'|'))
    {
        getline(file,data.namaIphone,'|');
        getline(file,data.jenisKerusakan,'|');
        getline(file,data.teknisi,'|');
        getline(file,data.tanggalMasuk,'|');
        getline(file,data.tanggalSelesai,'|');
        getline(file,data.status);

        if(data.idServis==id)
        {
            cout<<"Tanggal Selesai : ";
            getline(cin,data.tanggalSelesai);

            data.status="Selesai";
        }

        temp<<data.idServis<<"|"
            <<data.namaIphone<<"|"
            <<data.jenisKerusakan<<"|"
            <<data.teknisi<<"|"
            <<data.tanggalMasuk<<"|"
            <<data.tanggalSelesai<<"|"
            <<data.status
            <<endl;
    }

    file.close();

    temp.close();

    remove("servis.txt");

    rename("temp.txt","servis.txt");

    cout<<"\nStatus servis berhasil diperbarui.";

    pauseProgram();
}

void menuKerusakanServis()
{
    int pilih;

    do
    {
        system("cls");

        cout<<"===================================="<<endl;
        cout<<"    MENU KERUSAKAN & SERVIS"<<endl;
        cout<<"===================================="<<endl;

        cout<<"1. Tambah Data Kerusakan"<<endl;
        cout<<"2. Lihat Data Kerusakan"<<endl;
        cout<<"3. Tambah Data Servis"<<endl;
        cout<<"4. Lihat Data Servis"<<endl;
        cout<<"5. Update Status Servis"<<endl;
        cout<<"6. Kembali"<<endl;

        cout<<"\nPilih : ";
        cin>>pilih;

        switch(pilih)
        {
            case 1:
                tambahKerusakan();
                break;

            case 2:
                lihatKerusakan();
                break;

            case 3:
                tambahServis();
                break;

            case 4:
                lihatServis();
                break;

            case 5:
                updateStatusServis();
                break;
        }

    }while(pilih!=6);
}

//=========================================================
// GENERATE ID NOTIFIKASI
//=========================================================

string generateIDNotifikasi()
{
    ifstream file("notifikasi.txt");

    string baris;

    int jumlah=0;

    while(getline(file,baris))
        jumlah++;

    file.close();

    stringstream ss;

    ss<<"NTF";

    ss<<setfill('0')<<setw(4)<<jumlah+1;

    return ss.str();
}

//=========================================================
// KIRIM NOTIFIKASI
//=========================================================

void kirimNotifikasi(string username,
                     string judul,
                     string isi)
{
    ofstream file("notifikasi.txt",ios::app);

    file
    <<generateIDNotifikasi()<<"|"
    <<username<<"|"
    <<judul<<"|"
    <<isi<<"|"
    <<"09/07/2026|"
    <<"Belum Dibaca"
    <<endl;

    file.close();
}

//=========================================================
// LIHAT NOTIFIKASI
//=========================================================

void lihatNotifikasi(string usernameAktif)
{
    system("cls");

    ifstream file("notifikasi.txt");

    Notifikasi data;

    bool ada=false;

    cout<<"=============================================="<<endl;
    cout<<"          NOTIFIKASI SAYA"<<endl;
    cout<<"=============================================="<<endl;

    while(getline(file,data.idNotifikasi,'|'))
    {
        getline(file,data.username,'|');
        getline(file,data.judul,'|');
        getline(file,data.isi,'|');
        getline(file,data.tanggal,'|');
        getline(file,data.status);

        if(data.username==usernameAktif)
        {
            ada=true;

            cout<<"ID      : "<<data.idNotifikasi<<endl;
            cout<<"Judul   : "<<data.judul<<endl;
            cout<<"Isi     : "<<data.isi<<endl;
            cout<<"Tanggal : "<<data.tanggal<<endl;
            cout<<"Status  : "<<data.status<<endl;

            cout<<"------------------------------------------"<<endl;
        }
    }

    if(!ada)
    {
        cout<<"Belum ada notifikasi."<<endl;
    }

    file.close();

    pauseProgram();
}

//=========================================================
// TANDAI SUDAH DIBACA
//=========================================================

void tandaiSudahDibaca(string usernameAktif)
{
    ifstream file("notifikasi.txt");

    ofstream temp("temp.txt");

    Notifikasi data;

    while(getline(file,data.idNotifikasi,'|'))
    {
        getline(file,data.username,'|');
        getline(file,data.judul,'|');
        getline(file,data.isi,'|');
        getline(file,data.tanggal,'|');
        getline(file,data.status);

        if(data.username==usernameAktif)
        {
            data.status="Sudah Dibaca";
        }

        temp
        <<data.idNotifikasi<<"|"
        <<data.username<<"|"
        <<data.judul<<"|"
        <<data.isi<<"|"
        <<data.tanggal<<"|"
        <<data.status
        <<endl;
    }

    file.close();

    temp.close();

    remove("notifikasi.txt");

    rename("temp.txt","notifikasi.txt");

    cout<<"Semua notifikasi telah dibaca."<<endl;

    pauseProgram();
}

//=========================================================
// HAPUS NOTIFIKASI
//=========================================================

void hapusNotifikasi()
{
    system("cls");

    ifstream file("notifikasi.txt");

    ofstream temp("temp.txt");

    Notifikasi data;

    string id;

    bool ditemukan=false;

    cin.ignore();

    cout<<"Masukkan ID Notifikasi : ";

    getline(cin,id);

    while(getline(file,data.idNotifikasi,'|'))
    {
        getline(file,data.username,'|');
        getline(file,data.judul,'|');
        getline(file,data.isi,'|');
        getline(file,data.tanggal,'|');
        getline(file,data.status);

        if(data.idNotifikasi==id)
        {
            ditemukan=true;
            continue;
        }

        temp
        <<data.idNotifikasi<<"|"
        <<data.username<<"|"
        <<data.judul<<"|"
        <<data.isi<<"|"
        <<data.tanggal<<"|"
        <<data.status
        <<endl;
    }

    file.close();

    temp.close();

    remove("notifikasi.txt");

    rename("temp.txt","notifikasi.txt");

    if(ditemukan)
        cout<<"Notifikasi berhasil dihapus."<<endl;
    else
        cout<<"Data tidak ditemukan."<<endl;

    pauseProgram();
}

//=========================================================
// SEMUA NOTIFIKASI
//=========================================================

void semuaNotifikasi()
{
    system("cls");

    ifstream file("notifikasi.txt");

    Notifikasi data;

    int no=1;

    cout<<"==============================================================="<<endl;
    cout<<"                  DATA NOTIFIKASI"<<endl;
    cout<<"==============================================================="<<endl;

    while(getline(file,data.idNotifikasi,'|'))
    {
        getline(file,data.username,'|');
        getline(file,data.judul,'|');
        getline(file,data.isi,'|');
        getline(file,data.tanggal,'|');
        getline(file,data.status);

        cout<<no++<<". "
            <<data.username
            <<" | "
            <<data.judul
            <<" | "
            <<data.status
            <<endl;
    }

    file.close();

    pauseProgram();
}

//=========================================================
// MENU NOTIFIKASI ADMIN
//=========================================================

void menuNotifikasiAdmin()
{
    int pilih;

    do
    {
        system("cls");

        cout<<"===================================="<<endl;
        cout<<"      MENU NOTIFIKASI"<<endl;
        cout<<"===================================="<<endl;

        cout<<"1. Semua Notifikasi"<<endl;
        cout<<"2. Hapus Notifikasi"<<endl;
        cout<<"3. Kembali"<<endl;

        cout<<"\nPilih : ";

        cin>>pilih;

        switch(pilih)
        {
            case 1:
                semuaNotifikasi();
                break;

            case 2:
                hapusNotifikasi();
                break;
        }

    }while(pilih!=3);
}



int main() {
	
	srand(time(0));
    int pilih;
    string usernameAktif;

    do {

        system("cls");

        // ===================== MENU UTAMA =====================
        // Menampilkan pilihan awal sistem
        // ======================================================

        cout << "=================================================" << endl;
        cout << "              SISTEM PENYEWAAN IPHONE            " << endl;
        cout << "=================================================" << endl;

        // ===================== DAFTAR MENU =====================
        cout << "1. Registrasi User" << endl;   // daftar akun baru
        cout << "2. Login User" << endl;    // masuk sebagai user
        cout << "3. Login Admin" << endl;   // masuk sebagai admin
        cout << "4. Keluar" << endl;        // keluar dari program
        cout << "=================================================" << endl;
        cout << "=================================================" << endl;

        // ===================== INPUT ===========================
        cout<<"Pilih Menu : ";
        pilih = inputAngka();

        switch(pilih) {

            case 1:

                registrasi();
                break;

            case 2:

                if(login(usernameAktif)) {

                    menuUser(usernameAktif);
                }

                break;

            case 3: {

                string adminUser;
                string adminPass;

                cout << "\nUsername Admin : ";
                cin >> adminUser;

                cout << "Password Admin : ";
                cin >> adminPass;

                if(adminUser == "admin" && adminPass == "123") {

                    cout << "\nLogin admin berhasil!" << endl;

                    system("pause");

                    menuAdmin();

                } else {

                    cout << "\nLogin admin gagal!" << endl;

                    system("pause");
                }

                break;
            }

            case 4:

                cout << "\nProgram selesai..." << endl;
                break;

            default:

                cout << "\nMenu tidak tersedia!" << endl;

                system("pause");
                break;
        }

    } while(pilih != 4);

    return 0;
}
