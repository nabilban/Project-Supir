#include <iostream>
#include <string>

using namespace std;

// Model data construct
struct Date
{
    int tanggal;
    int bulan;
    int tahun;
};

struct DataSupir
{
    string id;
    string nama;
    string alamat;
    Date tanggalLahir;
    char jenisKelamin;
    string noHp;
    DataSupir *next;
};

DataSupir *head = nullptr;
void membersihkanConsole();
void hapusSemuaSopir(DataSupir *head);
string IdGenerator(const string &nama, char jenisKelamin, const Date &tanggalLahir);
bool isIdExist(const string &id);
void TambahDataSupir();
void LihatDataSupir();
void EditDataSupir();
void HapusDataSupir();
void AdminPriviliage();
void UserPrivilage();
void membersihkanConsole();

// Function to clear the console
void membersihkanConsole()
{
    cout << "\033[2J\033[1;1H"; // Clears the console
}

// Function to generate ID
string IdGenerator(const string &nama, char jenisKelamin, const Date &tanggalLahir)
{
    int firstDigits = abs(nama.front() - 'A' + 1) + abs(nama.back() - 'A' + 1);
    firstDigits = (firstDigits < 10) ? firstDigits : firstDigits % 10;

    int thirdDigit = (jenisKelamin == 'L') ? 1 : 0;

    int lastDigitDay = tanggalLahir.tanggal % 10;
    int lastDigitMonth = tanggalLahir.bulan % 10;
    int lastDigitYear = (tanggalLahir.tahun % 100) % 10;
    int fourthDigit = (lastDigitDay + lastDigitMonth + lastDigitYear) % 9;

    bool isIdExist(const string &id);

    string finalFirstDigits = to_string(firstDigits);
    if (finalFirstDigits.length() < 3)
    {
        finalFirstDigits = "0" + finalFirstDigits;
    }

    int lastDigit = 0;
    string id;
    do
    {
        id = finalFirstDigits + to_string(thirdDigit) +
             to_string(fourthDigit) + to_string(lastDigit);
        lastDigit++;
    } while (isIdExist(id));

    return id;
}

bool isIdExist(const string &id)
{
    DataSupir *temp = head;
    while (temp != nullptr)
    {
        if (temp->id == id)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Function to add new driver data
void TambahDataSupir()
{
    DataSupir *supirBaru = new DataSupir;

    cout << "Nama                      : ";
    cin.ignore();
    getline(cin, supirBaru->nama);

    cout << "Kelamin (L/P)             : ";
    cin >> supirBaru->jenisKelamin;

    cout << "Tanggal Lahir (dd-mm-yyyy): ";
    cin >> supirBaru->tanggalLahir.tanggal >> supirBaru->tanggalLahir.bulan >> supirBaru->tanggalLahir.tahun;

    cout << "Alamat                    : ";
    cin.ignore();
    getline(cin, supirBaru->alamat);

    cout << "No HP                     : ";
    cin.ignore();
    getline(cin, supirBaru->noHp);

    supirBaru->id = IdGenerator(supirBaru->nama, supirBaru->jenisKelamin, supirBaru->tanggalLahir);

    supirBaru->next = nullptr;

    if (head == nullptr)
    {
        head = supirBaru;
    }
    else
    {
        DataSupir *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = supirBaru;
    }

    membersihkanConsole();
    cout << "Data supir berhasil ditambahkan." << endl;
    return AdminPriviliage();
}

// Function to view driver data
// Function to display the details of the current driver
void TampilkanDetailSupir(DataSupir *supir)
{
    if (supir == nullptr)
    {
        cout << "Tidak ada data supir." << endl;
        return;
    }

    cout << "<==============================>" << endl;
    cout << "ID       : " << supir->id << endl;
    cout << "Nama     : " << supir->nama << endl;
    cout << "Kelamin  : " << ((supir->jenisKelamin == 'L') ? "Laki-laki" : "Perempuan") << endl;
    cout << "Tgl Lahir: " << supir->tanggalLahir.tanggal << "-" << supir->tanggalLahir.bulan << "-" << supir->tanggalLahir.tahun << endl;
    cout << "Alamat   : " << supir->alamat << endl;
    cout << "No HP    : " << supir->noHp << endl;
}

// Function to move to the next driver in the list
void MoveToNextDriver()
{
    if (head != nullptr && head->next != nullptr)
    {
        if (head->next != nullptr)
        {
            head = head->next;
            TampilkanDetailSupir(head);
        }
        else
        {
            cout << "Anda sudah berada pada data supir terakhir." << endl;
        }
    }
    else
    {
        cout << "Tidak ada data supir." << endl;
    }
}

// Function to move to the previous driver in the list
void MoveToPreviousDriver()
{
    if (head != nullptr && head->next != nullptr)
    {
        DataSupir *temp = head;
        DataSupir *prev = nullptr;
        while (temp->next != nullptr)
        {
            prev = temp;
            temp = temp->next;
        }
        head = prev;
        TampilkanDetailSupir(head);
    }
    else
    {
        cout << "Tidak ada data supir." << endl;
    }
}

// Function to view driver data one by one with previous and next options
void LihatDataSupir()
{
    if (head == nullptr)
    {
        cout << "Tidak ada data supir." << endl;
        return;
    }

    if (head == nullptr)
    {
        head = head;
    }

    TampilkanDetailSupir(head);

    int pilihan;
    while (true)
    {
        cout << "<==============================>" << endl;
        cout << "1) Berikutnya" << endl;
        cout << "2) Sebelumnya" << endl;
        cout << "3) Kembali" << endl;
        cout << "> ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            MoveToNextDriver();
            break;
        case 2:
            MoveToPreviousDriver();
            break;
        case 3:
            membersihkanConsole();
            cout << "Kembali ke menu utama" << endl;
            return;
        default:
            membersihkanConsole();
            cout << "Opsi tidak valid." << endl;
            break;
        }
    }
}

// Function to search driver data by ID

DataSupir CariDataSupirById()
{
    if (head == nullptr)
    {
        cout << "Tidak ada data supir." << endl;
        return DataSupir();
    }

    cout << "Masukkan ID Supir yang ingin dicari: ";
    string inputId;
    cin >> inputId;

    DataSupir *current = head;
    while (current != nullptr)
    {
        if (current->id == inputId)
        {
            cout << "<==============================>" << endl;
            cout << "ID       : " << current->id << endl;
            cout << "Nama     : " << current->nama << endl;
            cout << "Kelamin  : " << ((current->jenisKelamin == 'L') ? "Laki-laki" : "Perempuan") << endl;
            cout << "Tgl Lahir: " << current->tanggalLahir.tanggal << "-" << current->tanggalLahir.bulan << "-" << current->tanggalLahir.tahun << endl;
            cout << "Alamat   : " << current->alamat << endl;
            cout << "No HP    : " << current->noHp << endl;
            current = current->next;
        }
        else
        {
            cout << "Data supir dengan ID " << inputId << " tidak ditemukan." << endl;
            return DataSupir();
        }
    }
    return DataSupir();
}

// Function to edit driver data
void EditDataSupir()
{
    if (head == nullptr)
    {
        cout << "Tidak ada data supir." << endl;
        return;
    }

    cout << "Masukkan ID Supir yang ingin diubah: ";
    string inputId;
    cin >> inputId;
    DataSupir *supirYangDiubah = head;
    while (supirYangDiubah != nullptr)
    {
        if (supirYangDiubah->id == inputId)
        {
            cout << "- Mengubah supir dengan Id " << inputId << " -" << endl;
            cout << "<==============================>" << endl;
            cout << "ID       : " << supirYangDiubah->id << endl;
            cout << "Nama     : " << supirYangDiubah->nama << endl;
            cout << "Kelamin  : " << ((supirYangDiubah->jenisKelamin == 'L') ? "Laki-laki" : "Perempuan") << endl;
            cout << "Tgl Lahir: " << supirYangDiubah->tanggalLahir.tanggal << "-" << supirYangDiubah->tanggalLahir.bulan << "-" << supirYangDiubah->tanggalLahir.tahun << endl;
            cout << "Alamat   : " << supirYangDiubah->alamat << endl;
            cout << "No HP    : " << supirYangDiubah->noHp << endl;
            cout << "<==============================>" << endl;
            cout << "1. Ubah Nama" << endl;
            cout << "2. Ubah Kelamin" << endl;
            cout << "3. Ubah Alamat" << endl;
            cout << "4. Ubah Tanggal Lahir" << endl;
            cout << "5. Kembali" << endl;
            cout << "<==============================>" << endl;
            cout << ">  ";
            int inputOpsi;
            cin >> inputOpsi;

            switch (inputOpsi)
            {
            case 1:
                cout << "Masukkan Nama yang baru: ";
                cin.ignore();
                getline(cin, supirYangDiubah->nama);
                break;
            case 2:
                cout << "Masukkan Kelamin yang baru (L/P): ";
                cin >> supirYangDiubah->jenisKelamin;
                break;
            case 3:
                cout << "Masukkan Alamat yang baru: ";
                cin.ignore();
                getline(cin, supirYangDiubah->alamat);
                break;
            case 4:
                cout << "Masukkan Tanggal Lahir yang baru (dd-mm-yyyy): ";
                cin >> supirYangDiubah->tanggalLahir.tanggal >> supirYangDiubah->tanggalLahir.bulan >> supirYangDiubah->tanggalLahir.tahun;
                break;
            case 5:
                membersihkanConsole();
                cout << "Kembali ke menu utama" << endl;
                return;
            default:
                cout << "Opsi tidak valid." << endl;
                break;
            }
            membersihkanConsole();
            cout << "Data supir dengan ID " << inputId << " telah diubah." << endl;
            return;
        }
        supirYangDiubah = supirYangDiubah->next;
    }
    cout << "Data supir dengan ID " << inputId << " tidak ditemukan." << endl;
}

// Function to delete driver data
void HapusDataSupir()
{
    if (head == nullptr)
    {
        cout << "Tidak ada data supir yang tersedia." << endl;
        return;
    }

    cout << "Masukkan ID Supir yang ingin dihapus: ";
    string inputId;
    cin >> inputId;

    DataSupir *current = head;
    DataSupir *previous = nullptr;

    while (current != nullptr)
    {
        if (current->id == inputId)
        {
            membersihkanConsole();
            cout << "<==============================>" << endl;
            cout << "\nSupir dengan data berikut akan dihapus :" << endl;
            cout << "Nama     : " << current->nama << endl;
            cout << "ID       : " << current->id << endl;
            cout << "Kelamin  : " << ((current->jenisKelamin == 'L') ? "Laki-laki" : "Perempuan") << endl;
            cout << "Tgl Lahir: " << current->tanggalLahir.tanggal << "-" << current->tanggalLahir.bulan << "-" << current->tanggalLahir.tahun << endl;
            cout << "Alamat   : " << current->alamat << endl;
            cout << "No HP    : " << current->noHp << endl;
            cout << "<==============================>" << endl;

            cout << "apakah supir dengan id " << inputId << " yang dihapus? (y/n) : ";
            char opsi;
            cin >> opsi;
            if (opsi == 'n' || opsi == 'N')
            {
                membersihkanConsole();
                cout << "Penghapusan data supir dibatalkan." << endl;
                return;
            }
            else if (previous == nullptr)
            {
                head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            delete current;
            membersihkanConsole();
            cout << "| Data sopir dengan ID " << inputId << " berhasil dihapus |\n";
            return;
        }

        previous = current;
        current = current->next;
    }
    cout << "Data supir dengan ID " << inputId << " tidak ditemukan." << endl;
}

// admin role
void AdminPriviliage()
{
    int pilihanAdmin;
    do
    {
        cout << "<==============================>" << endl;
        cout << "Admin Menu:" << endl;
        cout << "1) Mencari Data Supir " << endl;
        cout << "2) Lihat Semua Data Supir" << endl;
        cout << "3) Menghapus Data Supir " << endl;
        cout << "4) Edit Data Supir " << endl;
        cout << "5) Menambah Data Supir " << endl;
        cout << "6) Proses Pesanan " << endl;
        cout << "7) Kembali" << endl;
        cout << "<==============================>" << endl;
        cout << "> ";
        cin >> pilihanAdmin;

        switch (pilihanAdmin)
        {
        case 1:
            membersihkanConsole();
            cout << "Cari Data Supir BY ID" << endl;
            CariDataSupirById();
            break;
        case 2:
            membersihkanConsole();
            cout << "Lihat Semua Data" << endl;
            LihatDataSupir();
            break;
        case 3:
            membersihkanConsole();
            cout << "Hapus Data Supir" << endl;
            HapusDataSupir();
            break;
        case 4:
            membersihkanConsole();
            cout << "Edit Data Supir" << endl;
            EditDataSupir();
            break;
        case 5:
            membersihkanConsole();
            cout << "Tambah Data Supir" << endl;
            TambahDataSupir();
            break;
        case 6:
            membersihkanConsole();
            cout << "Proses Pesanan" << endl;
            //**TODO: Add order processing function
            break;
        case 7:
            membersihkanConsole();
            cout << "Kembali ke menu utama" << endl;
            return;
        default:
            membersihkanConsole();
            cout << "Pilihan tidak valid" << endl;
            cin.clear();
            cin.ignore();
        }

    } while (pilihanAdmin != 5);
}

// user role
void UserPrivilage()
{
    int pilihan;
    while (true)
    {

        cout << "<==============================>" << endl;
        cout << "User Menu:" << endl;
        cout << "1) Next " << endl;
        cout << "2) Previous" << endl;
        cout << "3) Order" << endl;
        cout << "4) Kembali" << endl;
        cout << "<==============================>" << endl;
        cout << "> ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            membersihkanConsole();
            cout << "Next Page" << endl;
            LihatDataSupir();
            break;

        case 2:
            membersihkanConsole();
            cout << "Previous" << endl;
            return;
        case 3:
            membersihkanConsole();
            cout << "Order" << endl;
        case 4:
            membersihkanConsole();
            cout << "Kembali ke menu utama" << endl;
            return;
        default:
            membersihkanConsole();
            cout << " Opsi Tidak Valid                  " << endl;
            cout << " Mohon Masukkan Opsi Yang Tersedia " << endl;
            cin.ignore();
        }
    }
}

// Function to delete all driver data
void hapusSemuaSopir(DataSupir *head)
{
    DataSupir *current = head;
    while (current != nullptr)
    {
        DataSupir *next = current->next;
        delete current;
        current = next;
    }
}

// Function to initialize dummy data
void InitializeDummyData()
{
    DataSupir *supir1 = new DataSupir;
    supir1->id = "D001";
    supir1->nama = "John Doe";
    supir1->jenisKelamin = 'L';
    supir1->tanggalLahir.tanggal = 15;
    supir1->tanggalLahir.bulan = 5;
    supir1->tanggalLahir.tahun = 1985;
    supir1->alamat = "123 Street, City";
    supir1->noHp = "1234567890";
    supir1->next = nullptr;

    DataSupir *supir2 = new DataSupir;
    supir2->id = "D002";
    supir2->nama = "Jane Doe";
    supir2->jenisKelamin = 'P';
    supir2->tanggalLahir.tanggal = 20;
    supir2->tanggalLahir.bulan = 8;
    supir2->tanggalLahir.tahun = 1990;
    supir2->alamat = "456 Avenue, Town";
    supir2->noHp = "9876543210";
    supir2->next = nullptr;

    // Add dummy data to the linked list
    if (head == nullptr)
    {
        head = supir1;
        supir1->next = supir2;
    }
    else
    {
        DataSupir *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = supir1;
        supir1->next = supir2;
    }
}
int main()
{
    InitializeDummyData();
    membersihkanConsole();
    cout << " Selamat Datang " << endl;
    cout << " di Project Supir " << endl;

    int pilihan;

    while (true)
    {
        cout << "<==============================>" << endl;
        cout << "Menu:" << endl;
        cout << "1) Admin " << endl;
        cout << "2) User" << endl;
        cout << "3) Keluar" << endl;
        cout << "<==============================>" << endl;
        cout << "> ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            membersihkanConsole();
            AdminPriviliage();
            break;
        case 2:
            membersihkanConsole();
            UserPrivilage();
            break;
        case 3:
        {
            membersihkanConsole();
            char opsi_keluar;

            cout << "<==============================>" << endl;
            cout << " Apakah Anda Yakin Keluar dari Program? " << endl;
            cout << " (y/Y) Untuk keluar dari program        " << endl;
            cout << " (n/N) Untuk tetap berada di program    " << endl;
            cout << "<==============================>" << endl;
            cout << "> Input: ";
            cin >> opsi_keluar;

            if (opsi_keluar == 'y' || opsi_keluar == 'Y')
            {
                membersihkanConsole();
                hapusSemuaSopir(head);
                return 0;
            }
            else if (opsi_keluar == 'n' || opsi_keluar == 'N')
            {
                membersihkanConsole();
                cout << " Selamat Datang " << endl;
                cout << " di Project Supir " << endl;
            }
            else
            {
                membersihkanConsole();
                cout << " Opsi Tidak Valid                  " << endl;
                cout << " Mohon Masukkan Opsi Yang Tersedia " << endl;
            }
        }
        default:
            membersihkanConsole();
            cout << " Opsi Tidak Valid                  " << endl;
            cout << " Mohon Masukkan Opsi Yang Tersedia " << endl;
            cin.ignore();
            break;
        }
    }

    return 0;
}
