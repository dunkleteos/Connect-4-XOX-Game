cmake_minimum_required(VERSION 3.28)
project(242_p2)

set(CMAKE_CXX_STANDARD 17)

# 1. Raylib Kütüphanesini İndirme Ayarları
include(FetchContent)
FetchContent_Declare(raylib URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz)
FetchContent_MakeAvailable(raylib)

# 2. Çalıştırılabilir Dosyayı ve TÜM KOD DOSYALARINI Tanımlama (Sorunu çözen kısım burası)
add_executable(242_p2
        main.cpp
        Board.cpp
        Board.h
        Connect_Board.cpp
        Connect_Board.h
        Connect_Ultimate.cpp
        Connect_Ultimate.h
        Game.cpp
        Game.h
)

# 3. Raylib'i Projeye Bağlama
target_link_libraries(242_p2 raylib)

# 4. DLL Hatalarını Çözen Statik Paketleme Ayarı
target_link_options(242_p2 PRIVATE "-static-libgcc" "-static-libstdc++" "-static")