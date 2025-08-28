
#include <locale.h>
#include <wchar.h>

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    wchar_t letters[] = L"Привет мир!";

    wprintf(L"%ls\n", letters);

    return 0;
}

