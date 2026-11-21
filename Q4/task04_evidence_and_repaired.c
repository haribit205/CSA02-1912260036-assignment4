#include <stdio.h>

struct account {
    int number;
    float balance;
};

/* Task 4.2: Proof that pass-by-value copies to a different stack address */
void addInterestByValue(struct account a, float rate) {
    printf("  [Inside addInterestByValue] Address of copy 'a'      : %p\n", (void *)&a);
    a.balance = a.balance + a.balance * rate / 100.0f;
}

/* Task 4.3: Repaired function using structure pointer and arrow operator */
void addInterest(struct account *a, float rate) {
    if (a == NULL) return;
    printf("  [Inside addInterest]        Pointer 'a' points to    : %p\n", (void *)a);
    a->balance = a->balance + a->balance * rate / 100.0f;
}

void printAccounts(const struct account *list, int n) {
    for (int i = 0; i < n; i++) {
        printf("Account %d -> Balance: %.2f\n", (list + i)->number, (list + i)->balance);
    }
}

int main(void) {
    struct account list[3] = {{101, 5000.0f}, {102, 12000.0f}, {103, 800.0f}};
    struct account *p = list;

    printf("--- Address Evidence (Pass-by-Value vs Pass-by-Pointer) ---\n");
    printf("Address of list[0] in main(): %p\n", (void *)&list[0]);
    addInterestByValue(list[0], 4.0f);
    printf("Balance of list[0] after pass-by-value: %.2f (Unchanged)\n\n", list[0].balance);

    printf("--- Applying 4%% Interest via Structure Pointers ---\n");
    for (int i = 0; i < 3; i++) {
        addInterest(&list[i], 4.0f);
    }

    printf("\nFirst account via pointer 'p': %d %.2f\n", p->number, p->balance);
    printf("\nUpdated Account Balances:\n");
    printAccounts(list, 3);
    return 0;
}
