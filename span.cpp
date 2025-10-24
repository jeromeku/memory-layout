#include <cstddef>
#include <span>
#include <stdio.h>
#include <iostream>
#include <iomanip>

struct Base {
  Base(int b = 0) : b_data(b) {}

  virtual void f() {};
  int b_data;
};

struct Derived : Base {
  Derived(int b = 0, int d = 0)
    : Base(b), d_data(d) {}

  int d_data;
};

template<typename T>
void print_span(T t){
    auto bytes = std::as_bytes(std::span{&t, 1});
    for(std::byte b : bytes){
        std::cout << std::hex << std::setw(2) << std::setfill('0')
        << std::to_integer<unsigned>(b) << ' ';
    }
    std::cout << "\n";
}
void print_bytes(unsigned char *t, size_t num_bytes, const char *label = ""){
    printf("%s\n", label);
    printf("%p %zu\n", (void * ) t, size_t(t));
    for(int i = 0; i < num_bytes; i++){
        printf("%02x ", t[i]);
    }
    printf("\n");
}

int main(){
    Base b{1};
    Derived d{2, 3};

    print_bytes(reinterpret_cast<unsigned char *>(&b), sizeof(b), "Base");
    print_bytes(reinterpret_cast<unsigned char *>(&d), sizeof(d), "Derived");
    print_span(b);
    // auto s = std::span{&b, 1};

    // auto b_bytes = { std::as_bytes(span<Type, Extent> sp)
    // std::span<std::byte, sizeof(b)> b_bytes  = reinterpret_cast<std::span<std::byte, sizeof(b)>(&b);


}

// https://chatgpt.com/c/68fb97e9-cae8-832e-8c05-ee8ffc12702e
// echo "" | clang++ -std=c++20 -stdlib=libc++ -E -x c++ -v -
// clang++ -print-resource-dir
// clang++ -print-search-dirs
// clang++ -### -std=c++20 test.cc
