#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// структура, где хранится текущий баланс
typedef struct {
    int balance;
} Account;

// печатает баланс
void print_account(Account account) {
    printf("%d\n", account.balance);
}

// добавляем денюжку
void add_balance(Account* account, int amount) {
    account->balance += amount;
}

// 1000 раз добавляем по одной монетке
void process(Account* account) {
    for (int i = 0; i != 1000; ++i) {
        add_balance(account, 1);
    }
}

int main() {
    Account account = { 0 };
    print_account(account);

    process(&account);

    print_account(account);
}

// вроде бы все хорошо, но нужно предусмотреть, что у нас будет 100500 пользователей и еще больше операций с балансом
// и вспомним, что мы знаем про thread-ы
