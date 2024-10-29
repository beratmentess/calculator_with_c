cmake_minimum_required(VERSION 3.10)
project(untitled7)

set(CMAKE_C_STANDARD 11)

# GTK Kütüphanesini bulmak için pkg-config kullan
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Proje dosyasını ekle
add_executable(untitled7 gelismis_hesapmakinesi.c)

# GTK ve Matematik Kütüphanelerini bağla
target_link_libraries(untitled7 ${GTK3_LIBRARIES} m)
target_include_directories(untitled7 PRIVATE ${GTK3_INCLUDE_DIRS})
