# N-Queens Linkedin Solver with Brute Force Algoithm
## Penjelasan Singkat
Program ini adalah program yang menyelesaikan permasalahan *N-Queens*, yang mengikuti aturan standar dalam catur, yaitu tidak boleh ada Queen dalam baris, kolom yang sama dan tidak dapat diletakkan secara bersebelahan, termasuk secara diagonal. Lalu terdapat daerah warna di mana hanya ada satu Queen yang boleh menempati tiap satu daerah warna.

## Requirement & Instalasi
Sebelum menjalankan program, pastikan sudah terinstal compiler untuk C (gcc), library standar C ('stdio.h', 'stdlib.h', 'time.h', dan lain-lain). Lalu pastikan sudah terdapat folder bernama 'test' untuk menyimpan hasil test

## Cara Kompilasi
Buka terminal/command prompt, navigasikan sampai ke folder utama, lalu jalankan perintah :  
**Windows:**  
gcc -O3 src/main.c -o bin/queen

lalu jalankan perintah

./bin/queen 

untuk menjalankan program

## Cara menjalankan dan menggunakan program
1. Program akan meminta input nama file yang akan dieksekusi, jalankan "data/(nama file)" agar mndapatkan file dari folder data
2. program akan memvalidasi ukuran papan. Jika baris = kolom (persegi), maka program akan mencari semua solusi sampai mendapatkan solusi valid, atau mencoba semua susunan sampai akhir. Jika tidak persegi, maka program akan memberikan pesan error dan berhenti bekerja.
3. Program akan memberikan Live Update setiap 1000 kali percobaan, lalu memberikan solusi akhir dengan menampilkan papan yang berisi queen yang valid, waktu pencarian, dan banyak kasus yang ditinjau. 
4. Program akan meminta input dari pengguna apakah ingin menyimpan solusi atau tidak. Jika ingin menyimpan solusi, maka ketik "Ya" lalu masukkan "(nama file)" dan file akan otomatis tersimpan di folder test.

## Identitas Pembuat
Nama : Fauzan Mohamad Abdul Ghani
NIM : 13524113