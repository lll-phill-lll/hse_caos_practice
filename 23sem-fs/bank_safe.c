#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdatomic.h>

#define N 5
#define OPS 10

typedef struct {
    int balance;
} Account ;

void print_account(Account account) {
    printf("%d\n", account.balance);
}

void add_money(Account* account, int amount) {
    int prev = atomic_fetch_add(&account->balance, amount);
    printf("%d\n", prev);
}

void take_money(Account* account, int amount) { // снимаем деньги
    int prev = atomic_fetch_sub(&account->balance, amount);
    printf("%d\n", prev);
}

// process Dad
void* process_add(void* smth) {
    Account* account = (Account*)smth;
    for (int i = 0; i != OPS; ++i) {
        add_money(account, 1);
    }

    return NULL;
}

// process son
void* process_take(void* smth) {
    Account* account = (Account*)smth;
    for (int i = 0; i != OPS; ++i) {
        take_money(account, 1);
    }

    return NULL;
}

int main() {
    Account account = {0};
    print_account(account);

    pthread_t tids_add[N];
    pthread_t tids_take[N];
    for (int i = 0; i != N; ++i) { // создаем 5 dads и 5 sons, у них общий счет
        pthread_create(&tids_add[i], NULL, process_add, (void *) &account);
        pthread_create(&tids_take[i], NULL, process_take, (void *) &account);
    }

    for (int i = 0; i != N; ++i) {
        pthread_join(tids_add[i], NULL);
        pthread_join(tids_take[i], NULL);
    }

    print_account(account);

}
