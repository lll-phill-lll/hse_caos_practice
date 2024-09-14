// https://leetcode.com/problems/reverse-words-in-a-string-iii/description/

#include "stdio.h"

void reverseWord(char *start, char *end) {
    char tmp;

    // Пока указатель на начало слова меньше, чем указатель на конец,
    // будем менять значения под этими указателями и сдвигато оба к середине
    while (start < end) {
        tmp = *start;
        *start = *end;
        *end = tmp;

        start++;
        end--;
    }
}

void reverseWords(char *s) {
    // Указатель на начало очередного найденного слова (которое мы развернем)
    char *start = s;
    // Указатель на текущий символ
    char *current = s;

    // Пока текущий символ не конец строки
    // берем очередное слово и переворачиваем
    while (*current != '\0') {
        // Если текущий символ - пробел, значит мы нашли слово 
        // и можем развернуть все символы от start до current-1
        // Можем просто вычитать из указателей, получая указатель на предыдущий элемент
        if (*current == ' ') {
            reverseWord(start, current-1);
            // следующее слово начинаем с символа за пробелом
            start = current + 1;
        }
        // Передвигаем указатель к следующему символу в строке
        ++current;
    }
    // Не забываем перевернуть последнее оставшееся слово
    reverseWord(start, current-1);
}

int main() {
    char s[] = "Hello! I'm the string to be reversed!";
    printf("%s\n", s);
    reverseWords(s);
    printf("%s\n", s);
}
