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

### 2. Tutorial Install PlatformIO :
- Oke selanjutnya untuk memprogram alatnya kita menggunakan PlatformIo melalui Visual Studio Code
- Pertama kalian bisa install Vscode, kalian bisa liat dari video ini https://youtu.be/cu_ykIfBprI?si=zf6j9igDM7ElvqMv
- Setelah itu kalian bisa Install Extensions PlatformIo
![Image](https://github.com/user-attachments/assets/445eaa3f-3105-4677-86b4-41146e7c8187)
- Setelah berhasil install PlaformIo, kalian bisa cek tutorial untuk memulai PlatformIo dari video ini https://youtu.be/tc3Qnf79Ny8?si=eTluzbBJOMf1335Y

### 3. Upload program Beacon ke perangkat esp 32
- Pilih dan upload satu dari empat skenario program berikut, sesuai dengan pengujian yang ingin dilakukan
- esp32_burst5.cpp → Program dengan sleep selama 5 menit.
- esp32_burst8.cpp → Program dengan sleep selama 8 menit.
- esp32_delay5.cpp → Program dengan delay 1 menit lalu sleep selama 5 menit.
- Esp32_delay8.cpp → Program dengan delay 1 menit lalu sleep selama 8 menit.
- Pastikan hanya satu program dijalankan pada tiap ESP32 sesuai skenario uji konsumsi energi.

### 4. Upload program Receiver ke perangkat esp 32
- Upload program receiver.cpp ke ESP32 yang akan dijadikan receiver di titik-titik deteksi lokasi
- wifi dan ip


## Implementasi Server 

.....










