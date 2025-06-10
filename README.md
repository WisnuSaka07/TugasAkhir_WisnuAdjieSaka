# QUICK STARTUP GUIDE
Judul : Perancangan dan Implementasi Alat Tracking Mahasiswa Berbasis BLE untuk Penggunaan Absensi dan Validator Posisi Mahasiswa dengan Analisis Konsumsi Energi pada JDY-33 dan Esp32

Ada 3 Implementasi :
- Implementasi Alat 
- Implementasi Server
- Implementasi Receiver

## Implementasi Alat 

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

### 3. Upload program ke perangkat esp 32
- 

Setelah selesai setup PlatformIO masuk ke halaman "Home"  dari PlatformIO, lalu :
- Click New Project
- adasdasd
- asdasdasd

Masuk ke Alat Pertama yaitu JDY-33, jadi karena JDY merupakan modul bluetooth, untuk memprogram dia kita harus menggunakan mcu juga, disini saya menggunakan esp32. 

Untuk melakukan programing nya di src/main.cpp

Masukan program ke main.cpp (Buat beberapa Project)




## Implementasi Receiver














