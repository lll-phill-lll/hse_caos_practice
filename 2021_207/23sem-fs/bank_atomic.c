#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


typedef struct {
    int money;
} Account ;

void print_account(Account account) {
    printf("%d\n", account.money);
}

void add_money(Account* account, int amount) {
    account->money += amount;
}

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
