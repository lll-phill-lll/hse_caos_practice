#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdatomic.h>

#define N 5

typedef struct {
    _Atomic int balance;
} Account ;

void print_account(Account account) {
    printf("%d\n", account.balance);
}

// добавляем денюжку
void add_money(Account* account, int amount) {
    int old_balance = atomic_fetch_sub(&account->balance, amount);
    old_balance += amount;
    // save old balance
}

void* child_action(void* smth) {
    Account* account = (Account*)smth;
    for (int i = 0; i != 1000000; ++i) {
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
        pthread_create(&tids[i], NULL, child_action, (void *)&account);
    }

    // ждем каждый поток
    for (int i = 0; i != N; ++i) {
        pthread_join(tids[i], NULL);
    }

    print_account(account);
}
