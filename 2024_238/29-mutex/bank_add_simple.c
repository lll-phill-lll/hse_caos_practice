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
void add_money(Account* account, int amount) {
    int old_balance = account->balance;
    int new_balance = old_balance + amount;
    account->balance = new_balance;
}

// 1000 раз добавляем по одной монетке
void process(Account* account) {
    for (int i = 0; i != 1000; ++i) {
        add_money(account, 1);
    }
}

int main() {
    Account account = { 0 };
    print_account(account);

    process(&account);

    print_account(account);
}
