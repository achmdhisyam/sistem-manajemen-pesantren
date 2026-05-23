#include <iostream>
#include <string>

using namespace std;

struct Pelanggaran {
    string jenis;
    Pelanggaran* next;
};

struct Santri {
    string id, nama, kamar;
    int kelas;
    Pelanggaran* pelanggaranTop = nullptr;
    Santri* next;
};
Santri* headSantri = nullptr;

struct SantriGraph {
    string idSantri;
    SantriGraph* next;
};

struct Ustadz {
    string nama;
    SantriGraph* listSantriBimbingan;
    Ustadz* next;
};
Ustadz* headUstadz = nullptr;

struct KamarData {
    string namaKamar; 
    KamarData* next;
};
KamarData* headKamar = nullptr;

const int SIZE_KAMAR_HASH = 20;
struct KamarHash {
    string namKamar; 
    string daftarSantri;
};
KamarHash* hashTableKamar[SIZE_KAMAR_HASH];

struct Izin {
    string namaSantri, keperluan;
    Izin* next;
};
Izin* frontIzin = nullptr;
Izin* rearIzin = nullptr;

struct NilaiNode {
    string namaSantri;
    int nilai;
    NilaiNode* kiri;
    NilaiNode* kanan;
};
NilaiNode* rootNilai = nullptr;


int hashKamar(string no) { // 'no' di sini adalah namaKamar
    int total = 0;
    for (char c : no) total += c;
    return total % SIZE_KAMAR_HASH;
}

Santri* cariSantriByNama(string nama) {
    Santri* temp = headSantri;
    while (temp != nullptr) {
        if (temp->nama == nama) return temp;
        temp = temp->next;
    }
    return nullptr;
}

Santri* cariSantriByID(string id) {
    Santri* temp = headSantri;
    while (temp != nullptr) {
        if (temp->id == id) return temp;
        temp = temp->next;
    }
    return nullptr;
}

Ustadz* cariUstadz(string nama) {
    Ustadz* temp = headUstadz;
    while (temp) {
        if (temp->nama == nama) return temp;
        temp = temp->next;
    }
    return nullptr;
}

KamarData* cariKamarDataByNama(string namaKamarInput) { 
    KamarData* temp = headKamar;
    while (temp) {
        if (temp->namaKamar == namaKamarInput) return temp; 
        temp = temp->next;
    }
    return nullptr;
}

KamarData* cariKamarByNomorUrut(int nomorUrut) {
    KamarData* temp = headKamar;
    int counter = 1;
    while(temp != nullptr) {
        if (counter == nomorUrut) {
            return temp;
        }
        temp = temp->next;
        counter++;
    }
    return nullptr;
}

Ustadz* cariUstadzByNomorUrut(int nomorUrut) {
    Ustadz* temp = headUstadz;
    int counter = 1;
    while(temp != nullptr) {
        if (counter == nomorUrut) {
            return temp;
        }
        temp = temp->next;
        counter++;
    }
    return nullptr;
}
void cariSantriMenu() { 
    string nama;
    cout << "Masukkan nama santri yang dicari: ";
    getline(cin, nama);
    Santri* s = cariSantriByNama(nama);
    if (s) {
        cout << "Ditemukan: ID: " << s->id << ", Nama: " << s->nama
             << ", Kamar: " << s->kamar << ", Kelas: " << s->kelas << endl;
    } else {
        cout << "Santri dengan nama '" << nama << "' tidak ditemukan.\n";
    }
}


void tampilSemuaKamar() { 
    KamarData* temp = headKamar;
    cout << "\n--- Daftar Kamar Tersedia --- \n";
    int no = 1;
    while (temp != nullptr) {
        cout << no++ << ". " << temp->namaKamar << endl; 
        temp = temp->next;
    }
    cout << "-----------------------------\n";
}

// ===== Fitur Manajemen Ustadz =====
void tampilSemuaUstadz() {
    Ustadz* temp = headUstadz;
    cout << "\n--- Daftar Ustadz Tersedia --- \n";
    int no = 1;
    while (temp != nullptr) {
        cout << no++ << ". " << temp->nama << endl;
        temp = temp->next;
    }
    cout << "-----------------------------\n";
}

void tambahUstadzBaru() { // Menu Nomor 1
    Ustadz* baru = new Ustadz;
    cout << "Nama Ustadz Baru: ";
    getline(cin, baru->nama);
    cin.ignore(); 
    baru->listSantriBimbingan = nullptr;
    baru->next = nullptr;

    if (cariUstadz(baru->nama)) {
        cout << "Ustadz dengan nama " << baru->nama << " sudah ada.\n";
        delete baru;
        return;
    }

    if (headUstadz == nullptr) {
        headUstadz = baru;
    } else {
        Ustadz* temp = headUstadz;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = baru;
    }
    cout << "Ustadz " << baru->nama << " berhasil ditambahkan.\n";
}


void tambahSantri() { // Menu Nomor 2
    Santri* baru = new Santri;
    cout << "ID Santri   : ";
    cin >> baru->id;
    cin.ignore(); 

    if (cariSantriByID(baru->id)) {
        cout << "Santri dengan ID " << baru->id << " sudah ada.\n";
        delete baru;
        return;
    }

    cout << "Nama        : ";
    getline(cin, baru->nama);
    cin.ignore(); 
    if (baru->nama.empty()){
        cout << "Nama santri tidak boleh kosong.\n";
        delete baru;
        return;
    }

    if (cariSantriByNama(baru->nama)) {
        cout << "Peringatan: Santri dengan nama '" << baru->nama << "' sudah ada\n";
        delete baru;
        return;
    }

    KamarData* kTerpilih = nullptr;
    while(true) { 
        tampilSemuaKamar(); 
        cout << "Masukkan NOMOR kamar dari daftar untuk " << baru->nama << "': ";
        int nomorKamarPilihan;
        cin >> nomorKamarPilihan;
        cin.ignore(); 

        if (cin.fail()) {
            cout << "Input nomor urut tidak valid. Harap masukkan angka.\n";
            cin.clear();          
            cin.ignore(); 
            continue;             
        }
        kTerpilih = cariKamarByNomorUrut(nomorKamarPilihan);
        if (kTerpilih) {
            baru->kamar = kTerpilih->namaKamar; 
            cout << "Santri bernama " << baru->nama << " akan ditempatkan di kamar " << baru->kamar << ".\n";
            break; 
        } else {
            cout << "Pilihan kamar tidak valid. Silakan pilih nomor kamar dari daftar.\n";
        }
    }
    
    cout << "Kelas (angka): ";
    cin >> baru->kelas;
    cin.ignore(); 
    if (cin.fail()) {
        cout << "Input kelas tidak valid.\n";
        delete baru; return;
    }

    if (!headUstadz) {
        cout << "Belum ada Ustadz daftar. Silakan tambah Ustadz dulu.\n";
        delete baru; 
        return;     
    }
    
    Ustadz* uTerpilih = nullptr;
    while(true) { 
        tampilSemuaUstadz(); 

        cout << "Masukkan NOMOR  Ustadz Pembimbing untuk " << baru->nama << "': ";
        int nomorUstadzPilihan;
        cin >> nomorUstadzPilihan;
        cin.ignore(); 
        
        if (cin.fail()) {
            cout << "Input nomor urut tidak valid. Harap masukkan angka.\n";
            cin.clear();
            cin.ignore(); 
            continue;
        }
        uTerpilih = cariUstadzByNomorUrut(nomorUstadzPilihan);
        if (uTerpilih) {
            break; 
        } else {
            cout << "Pilihan Ustadz tidak valid. Silakan pilih nomor urut dari daftar.\n";
        }
    }
    
    // Finalisasi penambahan santri
    baru->next = nullptr;
    baru->pelanggaranTop = nullptr;

    if (headSantri == nullptr) {
        headSantri = baru;
    } else {
        Santri* temp = headSantri;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = baru;
    }
    
    // Tambahkan ke bimbingan ustadz 
    if (uTerpilih) { 
        SantriGraph* sGraph = new SantriGraph;
        sGraph->idSantri = baru->id;
        sGraph->next = uTerpilih->listSantriBimbingan; 
        uTerpilih->listSantriBimbingan = sGraph;
        cout << "Santri bernama " << baru->nama << " berhasil ditambahkan ke bimbingan Ustadz " << uTerpilih->nama << ".\n";
    }


    // Update Hash Table Kamar
    if (!baru->kamar.empty()) { 
        string noKamarHash = baru->kamar;
        int idx = hashKamar(noKamarHash);
        int originalIdx = idx;
        int probes = 0;
        while (hashTableKamar[idx] != nullptr && hashTableKamar[idx]->namKamar != noKamarHash) {
            idx = (idx + 1) % SIZE_KAMAR_HASH;
            probes++;
            if (probes >= SIZE_KAMAR_HASH) {
                 cout << "Peringatan: Hash table kamar penuh atau tidak dapat menemukan slot untuk kamar " << noKamarHash << endl;
                 break;
            }
        }
         if (!(probes >= SIZE_KAMAR_HASH && (hashTableKamar[idx] != nullptr && hashTableKamar[idx]->namKamar != noKamarHash))) {
            if (hashTableKamar[idx] == nullptr) {
                hashTableKamar[idx] = new KamarHash{noKamarHash, baru->nama};
            } else if (hashTableKamar[idx]->namKamar == noKamarHash) {
                if (hashTableKamar[idx]->daftarSantri.empty()) hashTableKamar[idx]->daftarSantri = baru->nama;
                else hashTableKamar[idx]->daftarSantri += ", " + baru->nama;
            }
        }
    }
    cout << "Santri " << baru->nama << " berhasil ditambahkan\n";
}

void tampilSantri() { 
    if (headSantri == nullptr) {
        cout << "Belum ada data santri.\n";
        return;
    }
    Santri* temp = headSantri;
    cout << "\n=== Data Santri ===\n";
    while (temp != nullptr) {
        cout << "ID: " << temp->id << ", Nama: " << temp->nama
             << ", Kamar: " << temp->kamar << ", Kelas: " << temp->kelas << endl;
        temp = temp->next;
    }
}


void tambahPelanggaran() { 
    string namaSantri, jenis;
    cout << "Masukkan NAMA santri yang melanggar: ";
    getline(cin, namaSantri);

    Santri* s = cariSantriByNama(namaSantri);
    if (!s) {
        cout << "Santri dengan nama '" << namaSantri << "' tidak ditemukan.\n";
        return;
    }
    cout << "Santri ditemukan: " << s->nama << " (ID: " << s->id << ", Kelas: " << s->kelas << ")" << endl;
    cout << "Jenis pelanggaran: ";
    getline(cin, jenis);

    Pelanggaran* p = new Pelanggaran;
    p->jenis = jenis;
    p->next = s->pelanggaranTop;
    s->pelanggaranTop = p;

    cout << "Pelanggaran berhasil ditambahkan untuk " << s->nama << endl;
}

void lihatPelanggaranSantri() { 
    string namaSantri;
    cout << "Masukkan NAMA santri untuk lihat pelanggaran: ";
    getline(cin, namaSantri);

    Santri* s = cariSantriByNama(namaSantri);
    if (!s) {
        cout << "Santri dengan nama '" << namaSantri << "' tidak ditemukan.\n";
        return;
    }
    if (!s->pelanggaranTop) {
        cout << "Santri " << s->nama << " (ID: " << s->id << ") tidak pernah melakukan pelanggaran.\n";
        return;
    }
    cout << "Riwayat pelanggaran " << s->nama << " (ID: " << s->id << "):\n";
    Pelanggaran* p = s->pelanggaranTop;
    int no = 1;
    while (p) {
        cout << no++ << ". " << p->jenis << endl;
        p = p->next;
    }
}

void antriIzin() { 
    string namaSantri;
    cout << "Masukkan NAMA Santri yang akan izin: ";
    getline(cin, namaSantri);

    Santri* s = cariSantriByNama(namaSantri);
    if (!s) {
        cout << "Santri dengan nama '" << namaSantri << "' tidak ditemukan.\n";
        return;
    }
    cout << "Santri ditemukan: " << s->nama << " (ID: " << s->id << ", Kelas: " << s->kelas << ")" << endl;

    Izin* baru = new Izin;
    baru->namaSantri = s->nama;
    cout << "Keperluan izin: ";
    getline(cin, baru->keperluan);
    baru->next = nullptr;

    if (!frontIzin) {
        frontIzin = rearIzin = baru;
    } else {
        rearIzin->next = baru;
        rearIzin = baru;
    }
    cout << "Izin untuk " << s->nama << " ditambahkan ke antrean.\n";
}

void prosesIzin() { 
    if (!frontIzin) {
        cout << "Antrean izin kosong.\n";
        return;
    }
    cout << "Memproses izin: " << frontIzin->namaSantri
         << " - Keperluan: " << frontIzin->keperluan << endl;

    Izin* hapus = frontIzin;
    frontIzin = frontIzin->next;
    if (frontIzin == nullptr) {
        rearIzin = nullptr;
    }
    delete hapus;
    cout << "Izin berhasil diproses.\n";
}

void tampilAntrianIzin() { 
    if (!frontIzin) {
        cout << "Antrean izin kosong.\n";
        return;
    }
    Izin* temp = frontIzin;
    cout << "\n=== Antrian Izin ===\n";
    int no = 1;
    while (temp) {
        cout << no++ << ". " << temp->namaSantri
        << " - Keperluan: " << temp->keperluan << endl;
        temp = temp->next;
    }
}

NilaiNode* buatNodeNilai(string nama, int nilai) {
    NilaiNode* baru = new NilaiNode;
    baru->namaSantri = nama;
    baru->nilai = nilai;
    baru->kiri = baru->kanan = nullptr;
    return baru;
}

NilaiNode* masukkanNilaiRek(NilaiNode* root, string nama, int nilai) {
    if (!root) {
        return buatNodeNilai(nama, nilai);
    }
    if (nilai < root->nilai) {
        root->kiri = masukkanNilaiRek(root->kiri, nama, nilai);
    } else {
        root->kanan = masukkanNilaiRek(root->kanan, nama, nilai);
    }
    return root;
}

void tambahNilaiKitab() { 
    string namaSantriInput;
    int nilaiKitab;

    cout << "Masukkan NAMA Santri : ";
    getline(cin, namaSantriInput);

    Santri* s = cariSantriByNama(namaSantriInput);
    if (!s) {
        cout << "Santri dengan nama '" << namaSantriInput << "' tidak ditemukan.\n";
        return;
    }
    cout << "Santri ditemukan: " << s->nama << " (ID: " << s->id << ", Kelas: " << s->kelas << ")" << endl;

    cout << "Nilai baca Kitab untuk " << s->nama << " : ";
    cin >> nilaiKitab;
    cin.ignore(); 

    rootNilai = masukkanNilaiRek(rootNilai, s->nama, nilaiKitab);
    cout << "Nilai baca kitab untuk " << s->nama << " berhasil ditambahkan.\n";
}


void tampilNilaiInOrder(NilaiNode* root) {
    if (root) {
        tampilNilaiInOrder(root->kiri);
        cout << "Nama: " << root->namaSantri << " - Nilai: " << root->nilai << endl;
        tampilNilaiInOrder(root->kanan);
    }
}

void panggilTampilNilaiInOrder() { 
    if (!rootNilai) {
        cout << "Belum ada data nilai baca kitab santri.\n";
        return;
    }
    cout << "\n=== Daftar Nilai baca Kitab Santri ===\n";
    tampilNilaiInOrder(rootNilai);
}

void tampilKamarHash() { 
    bool adaData = false;
    cout << "\n=== Daftar Santri per Kamar  ===\n";
    for (int i = 0; i < SIZE_KAMAR_HASH; i++) {
        if (hashTableKamar[i]) {
            cout << "Kamar " << hashTableKamar[i]->namKamar << ": " << hashTableKamar[i]->daftarSantri << endl;
            adaData = true;
        }
    }
    if (!adaData) {
        cout << "Belum ada data santri yang di kamar .\n";
    }
}

void tampilRelasiUstadz() { 
    if (!headUstadz) {
        cout << "Belum ada data ustadz untuk ditampilkan relasinya.\n";
        return;
    }
    Ustadz* u = headUstadz;
    cout << "\n=== Relasi Ustadz - Santri Bimbingan ===\n";
    while (u) {
        cout << "Ustadz: " << u->nama;
        if (u->listSantriBimbingan) {
            cout << " membimbing: ";
            SantriGraph* sGraphNode = u->listSantriBimbingan;
            bool pertama = true;
            while (sGraphNode) {
                if (!pertama) {
                    cout << ", ";
                }
                Santri* detailSantri = cariSantriByID(sGraphNode->idSantri);
                if (detailSantri) {
                    cout << detailSantri->nama << " (ID: " << detailSantri->id << ")";
                } else {
                    cout << "Santri dengan ID " << sGraphNode->idSantri << " (Data tidak ditemukan)";
                }
                pertama = false;
                sGraphNode = sGraphNode->next;
            }
        } else {
            cout << " (belum ada santri bimbingan)";
        }
        cout << endl;
        u = u->next;
    }
}

void bubbleSortSantriByKelas() { 
    if (!headSantri) {
        cout << "Belum ada data santri untuk diurutkan.\n";
        return;
    }
    int n = 0;
    Santri* tempCounter = headSantri;
    while (tempCounter != nullptr) { n++; tempCounter = tempCounter->next; }
    if (n == 0) { cout << "Belum ada data santri untuk diurutkan.\n"; return; }

    Santri* arr[n];
    Santri* temp = headSantri;
    for (int i = 0; i < n; ++i) { arr[i] = temp; temp = temp->next; }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] && arr[j+1] && arr[j]->kelas > arr[j+1]->kelas) {
                Santri* t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
            }
        }
    }
    cout << "\n=== Santri Diurutkan Berdasarkan Kelas (Terendah ke Tertinggi) ===\n";
    for (int i = 0; i < n; i++) {
        if (arr[i]) {
            cout << i + 1 << ". ID: " << arr[i]->id << ", Nama: " << arr[i]->nama
                 << ", Kamar: " << arr[i]->kamar << ", Kelas: " << arr[i]->kelas << endl;
        }
    }
}

// =====Menu Utama =====
int main() {
    for (int i = 0; i < SIZE_KAMAR_HASH; i++) hashTableKamar[i] = nullptr;

    int jumlahKamarAwal;
    cout << "===== Pengaturan Awal Pondok Pesantren =====" << endl;
    cout << "Masukkan jumlah kamar: ";
    cin >> jumlahKamarAwal;
    cin.ignore(); 

    for (int i = 0; i < jumlahKamarAwal; ++i) {
        KamarData* baru = new KamarData;
        cout << "Masukkan Nama Kamar ke-" << i + 1 << ": "; 
        getline(cin, baru->namaKamar);

        baru->next = nullptr;
        if (!headKamar) {
            headKamar = baru;
        } else {
            KamarData* temp = headKamar;
            while(temp->next) temp = temp->next;
            temp->next = baru;
        }
        cout << "Kamar '" << baru->namaKamar << "' berhasil ditambahkan.\n";
    }
    cout << "============================================\n";

    int pilih;
    do {
        cout << "\n\n===== MENU MANAJEMEN PONDOK PESANTREN =====";
        cout << "\n--- Manajemen Pokok ---";
        cout << "\n1.  Tambah Ustadz Baru";
        cout << "\n2.  Tambah Santri Baru ";
        cout << "\n3.  Tampilkan Semua Santri";
        cout << "\n4.  Cari Santri Berdasarkan Nama";
        cout << "\n--- Manajemen Pelanggaran ---";
        cout << "\n5.  Catat Pelanggaran Santri";
        cout << "\n6.  Lihat Riwayat Pelanggaran Santri ";
        cout << "\n--- Manajemen Perizinan (Queue) ---";
        cout << "\n7.  Tambah Antrian Izin Keluar";
        cout << "\n8.  Proses Izin Keluar";
        cout << "\n9.  Tampilkan Semua Antrian Izin";
        cout << "\n--- Manajemen Nilai Kitab (BST) ---";
        cout << "\n10. Input Nilai Kitab Santri";
        cout << "\n11. Tampilkan Nilai Kitab";
        cout << "\n--- Tampilan Data  ---";
        cout << "\n12. Tampilkan Data Santri per Kamar (Hash Table)";
        cout << "\n13. Tampilkan Relasi Ustadz dan Santri Bimbingan";
        cout << "\n14. Tampilkan Semua Ustadz";
        cout << "\n15. Tampilkan Semua Kamar";
        cout << "\n16. Urutkan Santri Berdasarkan Kelas ";
        cout << "\n0.  Keluar ";
        cout << "\n======================================================================";
        cout << "\nPilih menu: ";
        cin >> pilih;
        cin.ignore(); 

        switch(pilih) {
            case 1: tambahUstadzBaru(); break;
            case 2: tambahSantri(); break;
            case 3: tampilSantri(); break;
            case 4: cariSantriMenu(); break;
            case 5: tambahPelanggaran(); break;
            case 6: lihatPelanggaranSantri(); break;
            case 7: antriIzin(); break;
            case 8: prosesIzin(); break;
            case 9: tampilAntrianIzin(); break;
            case 10: tambahNilaiKitab(); break;
            case 11: panggilTampilNilaiInOrder(); break;
            case 12: tampilKamarHash(); break;
            case 13: tampilRelasiUstadz(); break;
            case 14: tampilSemuaUstadz(); break;
            case 15: tampilSemuaKamar(); break;
            case 16: bubbleSortSantriByKelas(); break;
            case 0:
                cout << "Keluar ...\n";
                break;
            default: cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }

    } while (pilih != 0);

    return 0;
}