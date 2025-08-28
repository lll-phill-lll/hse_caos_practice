#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdatomic.h>

#define INIT_BALANCE 2000
#define OPS 50

typedef struct {
    _Atomic int balance;
    char name[20];
} Account;

void add_money(Account* account, int amount) {
    atomic_fetch_add(&account->balance, amount);
}

void take_money(Account* account, int amount) {
    atomic_fetch_sub(&account->balance, amount);
}

Account family_account;       // банковский аккаунт семьи, из которого идет вывод средств
Account mall_account;         // аккаунт магазина
Account gas_station_account;  // аккаунт заправки

void print_accounts() {
    printf("+---------------+\n");
    printf("|     BANK      |\n");
    printf("+---------------+\n");
    printf("| %s: %d\t|\n", family_account.name, family_account.balance);
    printf("| %s: %d\t|\n", mall_account.name, mall_account.balance);
    printf("| %s: %d\t|\n", gas_station_account.name, gas_station_account.balance);
    printf("+---------------+\n");
}


void transfer(Account* from_account, Account* to_account, int amount) {
    int allow_transaction = from_account->balance >= amount;
    // проверяем, хватает ли денег на покупку
    if (allow_transaction) {
        printf("transfering %d from %s(%d) to %s(%d)\n",
                amount, from_account->name,from_account->balance, to_account->name, to_account->balance);

        add_money(to_account, amount);
        take_money(from_account, amount);
        return;
    }

    printf("cant transfer %d from %s(%d) to %s(%d)\n",
            amount, from_account->name,from_account->balance, to_account->name, to_account->balance);
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
    family_account.balance = INIT_BALANCE;

    print_accounts();

    pthread_t wife_pid, husband_pid; // два потока
    pthread_create(&husband_pid, NULL, husband, NULL);
    pthread_create(&wife_pid, NULL, wife, NULL);

    pthread_join(wife_pid, NULL);
    pthread_join(husband_pid, NULL);

    print_accounts();
}
