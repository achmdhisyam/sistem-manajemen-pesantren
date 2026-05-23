# Sistem Manajemen Pondok Pesantren

## Deskripsi Program
Program ini adalah aplikasi berbasis bahasa C++ untuk membantu pengelolaan data pondok pesantren.
Project ini bertujuan untuk memenuhi Final Project struktur data

Sistem menggunakan berbagai struktur data seperti:

- Linked List
- Stack
- Queue
- Binary Search Tree (BST)
- Hash Table
- Graph sederhana
- Bubble Sort

Program dibuat untuk mengelola data:

- Santri
- Ustadz
- Kamar
- Pelanggaran
- Perizinan
- Nilai kitab

---

# Fitur Program

## 1. Manajemen Ustadz
Fitur untuk menambahkan dan menampilkan data ustadz pembimbing.

### Menu:
- Tambah Ustadz Baru
- Tampilkan Semua Ustadz

### Struktur Data:
- Singly Linked List

---

## 2. Manajemen Santri
Fitur untuk menambahkan, mencari, menampilkan, dan mengurutkan data santri.

### Data Santri:
- ID
- Nama
- Kamar
- Kelas

### Menu:
- Tambah Santri Baru
- Tampilkan Semua Santri
- Cari Santri Berdasarkan Nama
- Urutkan Santri Berdasarkan Kelas

### Struktur Data:
- Linked List
- Bubble Sort

---

## 3. Manajemen Pelanggaran
Setiap santri dapat memiliki riwayat pelanggaran.

### Menu:
- Catat Pelanggaran Santri
- Lihat Riwayat Pelanggaran

### Struktur Data:
- Stack (LIFO)

Pelanggaran terbaru akan tampil paling atas.

---

## 4. Manajemen Perizinan
Digunakan untuk antrean izin keluar santri.

### Menu:
- Tambah Antrian Izin
- Proses Izin
- Tampilkan Semua Antrian Izin

### Struktur Data:
- Queue (FIFO)

Izin diproses sesuai urutan masuk.

---

## 5. Manajemen Nilai Kitab
Digunakan untuk menyimpan nilai baca kitab santri.

### Menu:
- Input Nilai Kitab
- Tampilkan Nilai Kitab

### Struktur Data:
- Binary Search Tree (BST)

Data nilai ditampilkan secara urut menggunakan traversal inorder.

---

## 6. Manajemen Kamar
Menampilkan daftar santri berdasarkan kamar.

### Struktur Data:
- Hash Table

---

## 7. Relasi Ustadz dan Santri
Menampilkan hubungan ustadz dengan santri bimbingannya.

### Struktur Data:
- Graph sederhana (Adjacency List)

---

# Struktur Data yang Digunakan

| Struktur Data | Fungsi |
|---|---|
| Linked List | Menyimpan data santri, ustadz, kamar |
| Stack | Menyimpan riwayat pelanggaran |
| Queue | Menyimpan antrean izin |
| BST | Menyimpan nilai kitab |
| Hash Table | Menyimpan data kamar |
| Graph | Relasi ustadz dan santri |
| Bubble Sort | Mengurutkan santri berdasarkan kelas |

---


# Tampilan Menu Program

```text
===== MENU MANAJEMEN PONDOK PESANTREN =====

1.  Tambah Ustadz Baru
2.  Tambah Santri Baru
3.  Tampilkan Semua Santri
4.  Cari Santri Berdasarkan Nama

--- Manajemen Pelanggaran ---
5.  Catat Pelanggaran Santri
6.  Lihat Riwayat Pelanggaran Santri

--- Manajemen Perizinan ---
7.  Tambah Antrian Izin Keluar
8.  Proses Izin Keluar
9.  Tampilkan Semua Antrian Izin

--- Manajemen Nilai Kitab ---
10. Input Nilai Kitab Santri
11. Tampilkan Nilai Kitab

--- Tampilan Data ---
12. Tampilkan Data Santri per Kamar
13. Tampilkan Relasi Ustadz dan Santri
14. Tampilkan Semua Ustadz
15. Tampilkan Semua Kamar
16. Urutkan Santri Berdasarkan Kelas

0. Keluar
```

---

# Contoh Alur Penggunaan

## 1. Tambah Kamar
Saat program dijalankan, user diminta memasukkan daftar kamar.

## 2. Tambah Ustadz
Masukkan nama ustadz pembimbing.

## 3. Tambah Santri
Input:
- ID
- Nama
- Pilih kamar
- Kelas
- Pilih ustadz pembimbing

## 4. Input Pelanggaran
Masukkan nama santri dan jenis pelanggaran.

## 5. Input Nilai Kitab
Masukkan nama santri dan nilai baca kitab.

---

# Identitas

### Nama
Achmad Hisyammuddin
### NIM
24051204165
### Kelas
TI 2024 E

### Mata Kuliah
Struktur Data

### Bahasa Pemrograman
C++

### Tema Program
Sistem Manajemen Pondok Pesantren
