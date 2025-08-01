# QUICK STARTUP GUIDE
Judul : Perancangan dan Implementasi Alat Tracking Mahasiswa Berbasis BLE untuk Penggunaan Absensi dan Validator Posisi Mahasiswa dengan Analisis Konsumsi Energi pada JDY-33 dan Esp32


Ada 3 Implementasi :
- Implementasi Alat 
- Implementasi Server


## Implementasi Alat (Beacon dan Receiver)

Ada 2 alat yang digunakan yaitu ESP 32 DevKit V1 dan JDY-33. Untuk pemrograman alat saya menggunakan ekstensi platformIO di VsCode. Berikut langkah-langkah implementasinya :


### 1. Instal driver microcontroller pada komputer
- Pertama kalian bisa cek chip pada esp 32 kalian apa, biasanya CH9102/CP2102, karena pada implementasi ini menggunakan ESP 32 DevKit V1, jadi chipnya CH9102

![Image](https://github.com/user-attachments/assets/e8b23da9-5fc1-4b90-8a00-79e875326035)

- Lalu download drivernya, kalian bisa liat dari video ini https://youtu.be/JmDxP4O4Trk?si=LEQVhztODxG_LDDF
- Jika sudah, pada saat kalian menyambungkan perangkat esp 32 ke komputer kalian, maka akan terlihat seperti gambar dibawah

![Image](https://github.com/user-attachments/assets/d543da58-5879-495d-93c1-1245a99688c9)

### 2. Tutorial Install PlatformIO
- Oke selanjutnya untuk memprogram alatnya kita menggunakan PlatformIo melalui Visual Studio Code
- Pertama kalian bisa install Vscode, kalian bisa liat dari video ini https://youtu.be/cu_ykIfBprI?si=zf6j9igDM7ElvqMv
- Setelah itu kalian bisa Install Extensions PlatformIo

![Image](https://github.com/user-attachments/assets/445eaa3f-3105-4677-86b4-41146e7c8187)

- Setelah berhasil install PlaformIo, masuk ke home PlatformIO dan pilih New Project

![Image](https://github.com/user-attachments/assets/d4757ff1-9002-4a7f-b7af-a8b5af24cdd9)

- Masukan konfigurasi sesuai alat yang dipakai lalu pilih finish

![Image](https://github.com/user-attachments/assets/c9932855-716b-4b38-b413-5cec5897f2a9)

- Untuk tombol build, upload, serial monitor, dan lain-lain ada di bagian bawah VsCode

![Image](https://github.com/user-attachments/assets/b269f83f-5bb4-4c73-a095-80a31cf82d26)

- Untuk tutorial lebih lengkap dari PlatformIO kalian bisa cek pada video ini https://youtu.be/tc3Qnf79Ny8?si=eTluzbBJOMf1335Y


### 3. Upload program Beacon ke perangkat esp 32
Pilih dan upload satu dari empat skenario program berikut, sesuai dengan pengujian yang ingin dilakukan. Ada 2 jenis program untuk beacon esp32 :
- Program burst langsung sleep
- Prgram delay sebelum sleep

Program untuk burst :
- esp32_burst5.cpp → Program dengan sleep selama 5 menit.
- esp32_burst8.cpp → Program dengan sleep selama 8 menit.

Program untuk delay :
- esp32_delay5.cpp → Program dengan delay 1 menit lalu sleep selama 5 menit.
- Esp32_delay8.cpp → Program dengan delay 1 menit lalu sleep selama 8 menit.

Pastikan hanya satu program dijalankan pada tiap ESP32 sesuai skenario uji konsumsi energi.


### 4. Upload program Receiver ke perangkat esp 32
Upload program receiver.cpp ke ESP32 yang akan dijadikan receiver di titik-titik deteksi lokasi. Lalu pada bagian ini bisa diganti sesuai nama ruangan
```
const char* LOCATION_NAME = "Lokasi B";
```
Dan kalian juga bisa ubah jangkauan deteksi sesuai luas ruangan (ganti angka "-85")
```
if (rssi > -85 && advertisedDevice.haveName()) { 
```
Untuk koneksi internet pada alat receiver ini, kita menggunakan wifi manager dari esp32, berikut cara menggunakannya:
- Setelah kamu upload program kamu pada esp32 nya, kamu bisa nyalakan esp32 supaya programnya bisa berjalan
- Setelah itu kamu buka hp atau komputer mu lalu koneksikan ke jaringan "ESP32-Receiver" dengan password "admin123"

![Image](https://github.com/user-attachments/assets/828a74a6-f3ed-4ed8-bc97-d6c5fd222236)

- Setelah koneksi dengan jaringannya, buka browser ke "192.168.4.1"

![Image](https://github.com/user-attachments/assets/6764ac6d-11ca-45ac-ab62-227949b620d6)

- Lalu masuk ke "Configur WIFI", pilih wifi lokal mana yang mau kamu gunakan, masukan ssid dan passwordnya

![Image](https://github.com/user-attachments/assets/850ed2c9-fd0e-41b7-82f7-2c6e4c4c0762)

- ESP-32 sudah terhubung dengan internet, dengan menggunakan WIFI manager ini, jadi tidak perlu mengganti code jika ingin mengganti jaringan WIFI




## Implementasi Server 
Untuk implementasi server ini akan dijalankan di ip "10.4.90.28", ini merupakan salah satu ip ITS, berikut langkah-langkah implementasinya : 

### 1. Persiapan VPN ITS
Langkah ini dilakukan jika ingin menjalankan dari perangkat diluar jaringan ITS
- masuk myITS Portal Lalu pilih "myITS VPN"

![Image](https://github.com/user-attachments/assets/59e06cbb-8c21-45b4-946c-54151f485744)

- ikuti petunjuk yang ada website tersebut, kalian akan diminta menginstall open VPN dan profil myITS VPN

![Image](https://github.com/user-attachments/assets/b714802f-6afa-48c0-9e77-fa0fdd30f06c)

- Jika sudah maka kalian sudah berada di jaringan ITS menggunakan VPN

![Image](https://github.com/user-attachments/assets/735d227b-2c69-4640-b115-38064ee8749a)


### 2. Jalankan Server
Untuk menjalankan server nya yang pertama dilakukan masuk ke ssh 10.4.90.28. Pertama pada terminal perangkat mu (bebas lokasinya dimana) masukan command ini untuk mengakses ssh nya
```
ssh root@10.4.90.28
```
setelah itu masukan passwordnya 

![Image](https://github.com/user-attachments/assets/94ec8590-777b-4b5d-aa16-1dc83b4ad7bb)

setelah masuk kedalam ssh nya, lakukan instalasi dan setup awal dengan langkah berikut 
```
sudo apt update && sudo apt upgrade -y
```
Lalu kita install python dan pip
```
sudo apt install python3 python3-pip -y
```
Lalu kita install flask 
```
pip install flask
```
Setelah semua dependensi terpasang, buat file Python untuk menjalankan server
```
nano server.py
```
Lalu copy file "server.py" ke dalam editor tersebut. Setelah selesai, tekan CTRL + X, lalu Y, dan tekan Enter untuk menyimpan. Terakhir, jalankan server dengan perintah
```
python3 server.py
``` 

### 3. Fungsi Server
- Saat server berhasil dijalankan, pada terminal akan muncul informasi ini

![Image](https://github.com/user-attachments/assets/02fe8b3b-b972-4478-ab9e-e849ead122eb)

- server sudah aktif dan bisa diakses melalui browser menggunakan alamat ip dan port yang tertera
- Setelah masuk, berikut tampilan dashboard yang muncul pada browser kalian

![Image](https://github.com/user-attachments/assets/d14e8ca7-dd9a-4af3-839d-3402048c5991)

- Receiver ESP32 akan mengirimkan data beacon yang terdeteksi ke server ini
- Dashboard akan menampilkan lokasi beacon secara real-time dan log waktu deteksinya


Catatan : 
- Pastikan receiver telah terkoneksi ke jaringan Wi-Fi ITS
- Jangan tutup terminal selama pengujian karena akan mematikan program server yang berjalan pada jaringan ITS



