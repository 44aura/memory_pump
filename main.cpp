#include <chrono>
#include <thread>
#include <iostream>

volatile char glob_char = 0;
int main(int argc, char* argv[]){
    if(*argv[1] != '1' && *argv[1] != '2'){
        std::cout << "Такого режима нет, попробуйте снова\n";
        return 1;
    }
    constexpr size_t page_size = 4 * (1 << 10);
    constexpr size_t arr_size = 16UL * (1 << 30);
    char* arr = new char[arr_size];
    int delay_ms = 5;

    size_t i = 0;
    while(i < arr_size){
        if (*argv[1] == '1'){
             glob_char = arr[i];
        } 
        else if(*argv[1] == '2'){
            arr[i] = 0;
        }
        i += page_size;
        if (i / page_size % 2000 == 0){
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        }
    }

    delete[] arr;
    return 0;
}

/*
Результаты:
В режиме чтения память не изменяется. (ОС - Linux)
В режиме записи скорость потребления памяти примерно 1 ГБ/сек и ОС "становится тыквой" за 10-12 секунд. 
*/