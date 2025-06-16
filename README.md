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
- Setelah berhasil install PlaformIo, kalian bisa cek tutorial untuk memulai PlatformIo dari video ini https://youtu.be/tc3Qnf79Ny8?si=eTluzbBJOMf1335Y


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
setelah itu masukan passwordnya setelah masuk kedalam ssh nya, kita lanjut ke tahap instalasi dan setup, pertama kita update dulu 

![Image](https://github.com/user-attachments/assets/94ec8590-777b-4b5d-aa16-1dc83b4ad7bb)

setelah masuk kedalam ssh nya, kita lanjut ke tahap instalasi dan setup, pertama kita update dulu 
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
Setelah menginstall semua yang dibutuhkan, kita masukan akan membuat file untuk program server nya
```
nano server.py
```
Lalu copy file "server.py" ke nano tersebut, jika sudah klik save, dan jalankan prgramnya
```
python3 server.py
``` 

### 3. Fungsi Server
- Saat server berhasil dijalankan, pada terminal akan muncul informasi ini
![Image](https://github.com/user-attachments/assets/02fe8b3b-b972-4478-ab9e-e849ead122eb)

- Masuk pada web browser sesuai ip dan port yang tertera
- Setelah masuk, berikut tampilan dashboard yang muncul pada browser kalian
![Image](https://github.com/user-attachments/assets/d14e8ca7-dd9a-4af3-839d-3402048c5991)
- Receiver ESP32 akan  mengirimkan data beacon yang terdeteksi ke server ini
- Dashboard akan menampilkan lokasi beacon secara real-time dan log waktu deteksinya


Catatan : 
- Pastikan receiver telah terkoneksi ke jaringan Wi-Fi ITS
- Jangan tutup terminal selama pengujian karena akan mematikan server pada jaringan ITS



