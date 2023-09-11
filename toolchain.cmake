# Название компилятора
SET(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
SET(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

# Префикс для исполнимых файлов (необязательно)
SET(CMAKE_CXX_COMPILER_PREFIX x86_64-w64-mingw32-)

# Архитектура и система
SET(CMAKE_SYSTEM_NAME Windows)
SET(CMAKE_SYSTEM_PROCESSOR x86_64)

# Настройка переменных окружения для поиска библиотек и заголовочных файлов
SET(CMAKE_FIND_ROOT_PATH    "/opt/local/bin/x86_64-w64-mingw32-g++"
                            "/opt/local/bin/x86_64-w64-mingw32-gcc")

# Параметры сборки
SET(CMAKE_CXX_FLAGS "-std=c++20") # Установите нужный стандарт C++
SET(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++") # Статические библиотеки

# Настройки для библиотеки SFML (пример)
SET(SFML_ROOT "/usr/local/lib/cmake/SFML")