#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdatomic.h>

#define N 5

typedef struct {
    // добавляем атомарную переменную
    _Atomic int balance;
    // // int balance; так себе вариант, если не использовать функцию atomic_fetch_add
} Account ;

void print_account(Account account) {
    printf("%d\n", account.balance);
}

void add_money(Account* account, int amount) {
    // atomic_fetch_add(&account->balance, amount);

    account->balance += amount;
}

void* process(void* smth) {
    Account* account = (Account*)smth;
    for (int i = 0; i != 100000000; ++i) {
        add_money(account, 1);
    }

    return NULL;
}

int main() {
    Account account = { 0 };
    print_account(account);

    pthread_t tids[N];
    for (int i = 0; i != N; ++i) {
        // создаем потоки,
        pthread_create(&tids[i], NULL, process, (void *)&account);
    }

    // ждем каждый поток
    for (int i = 0; i != N; ++i) {
        pthread_join(tids[i], NULL);
    }

    print_account(account);
}
