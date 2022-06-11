#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


typedef struct {
    int balance;
} Account;

void print_account(Account account) {
    printf("%d\n", account.balance);
}

void add_balance(Account* account, int amount) {
    account->balance += amount;
}

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
