#include <chrono>
#include <iostream>

#define ARR 100000000

int arr[ARR];

int main(){
    for(int i = 0; i < ARR; ++i){
        arr[i] = i;
    }
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - end;

    int x = 0;
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < ARR; ++i){
        x += arr[i];
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Normal for loop: \n" << (end - start).count() << " ms. sum:" << x;

    x=0;
    start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i <= ARR; i+=2){
        x += arr[i] + arr[ARR-i];
    }
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "\nTwosided for loop: \n" << (end - start).count() << " ms. sum:" << x;
}