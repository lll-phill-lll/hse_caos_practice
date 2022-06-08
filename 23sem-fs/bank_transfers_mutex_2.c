#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdatomic.h>

#define N 5
#define OPS 10

typedef struct {
    int balance;
    char name[20];

    pthread_mutex_t m; // положим mutex прям во внутрь структуры, значит для каждого аккаунта понадобиться отдельный mutex
} Account;

Account family_account;
Account mall_account;
Account gas_station_account;

void print_accounts() {
    printf("+---------------+\n");
    printf("|     BANK      |\n");
    printf("+---------------+\n");
    printf("| %s: %d\t|\n", family_account.name, family_account.balance);
    printf("| %s: %d\t|\n", mall_account.name, mall_account.balance);
    printf("| %s: %d\t|\n", gas_station_account.name, gas_station_account.balance);
    printf("+---------------+\n");
}

void add_money(Account* account, int amount) {
    atomic_fetch_add(&account->balance, amount);
}

void take_money(Account* account, int amount) {
    atomic_fetch_sub(&account->balance, amount);
}

void transfer(Account* from_account, Account* to_account, int amount) {
    // блокируем два mutex-а, откуда хотим снять деньги и куда хотим зачислить
    pthread_mutex_lock(&from_account->m);
    pthread_mutex_lock(&to_account->m);

    int allow_transaction = from_account->balance >= amount;
    sleep(1);
    if (allow_transaction) {
        printf("transfering %d from %s(%d) to %s(%d)\n", amount, from_account->name,from_account->balance, to_account->name, to_account->balance);

        take_money(from_account, amount);
        add_money(to_account, amount);
    } else {
        printf("cant transfer %d from %s(%d) to %s(%d)\n", amount, from_account->name,from_account->balance, to_account->name, to_account->balance);
    }

    pthread_mutex_unlock(&to_account->m);
    pthread_mutex_unlock(&from_account->m);
}

void* wife(void* smth) {
    for (int i = 0; i != OPS; ++i) {
        transfer(&family_account, &mall_account, 100);
    }

    return NULL;
}

void* husband(void* smth) {
    for (int i = 0; i != OPS; ++i) {
        transfer(&family_account, &gas_station_account, 50);
    }

    return NULL;
}

int main() {
    strcpy(mall_account.name, "MALL\0");
    strcpy(gas_station_account.name, "GAS\0");
    strcpy(family_account.name, "FAM\0");

    // закомитенная часть ниже позволяет заблокировать и разблокировать потоки рекурсивно
    // pthread_mutexattr_t attr;
    // pthread_mutexattr_init(attr);
    // pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

    // инициализируем mutex-ы для каждого аккаунта
    pthread_mutex_init(&mall_account.m, NULL);
    pthread_mutex_init(&family_account.m, NULL);
    pthread_mutex_init(&gas_station_account.m, NULL);

    // pthread_mutexattr_destroy(&attr);

    family_account.balance = 1000;

    print_accounts();

    pthread_t wife_pid, husband_pid;
    pthread_create(&wife_pid, NULL, wife, NULL);
    pthread_create(&husband_pid, NULL, husband, NULL);

    pthread_join(wife_pid, NULL);
    pthread_join(husband_pid, NULL);

    print_accounts();


    pthread_mutex_destroy(&mall_account.m);
    pthread_mutex_destroy(&family_account.m);
    pthread_mutex_destroy(&gas_station_account.m);
}
