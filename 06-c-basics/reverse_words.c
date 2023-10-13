// https://leetcode.com/problems/reverse-words-in-a-string-iii/description/

#include "stdio.h"

void reverseWord(char *start, char *end) {
    char tmp;

    while (start < end) {
        tmp = *start;
        *start = *end;
        *end = tmp;

        start++;
        end--;
    }
}

void reverseWords(char *s) {
    char *start = s;
    char *current = s;

    while (*current != '\0') {
        if (*current == ' ') {
            reverseWord(start, current-1);
            start = current + 1;
        }
        ++current;
    }
    reverseWord(start, current-1);
}

int main() {
    char s[] = "Hello! I'm the string to be reversed!";
    printf("%s\n", s);
    reverseWords(s);
    printf("%s\n", s);
}
