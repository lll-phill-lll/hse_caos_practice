#include <iostream>
// #include "private_lib.h" // ❌ Это НЕ будет видно! include — PRIVATE
#include "public_lib.h"     // ✅ Видно, потому что include — PUBLIC
#include "interface_lib.h"  // ✅ Видно, потому что include — INTERFACE

int main() {
    // private_hello();     // ❌ Ошибка компиляции
    public_hello();         // ✅ Ок
    interface_hello();      // ✅ Ок (inline-заглушка)
}
