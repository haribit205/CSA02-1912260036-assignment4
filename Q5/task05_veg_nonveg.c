#include <stdio.h>

/* Task 5.2: Independent Veg and Non-Veg Counters */
int next_veg_static(void) {
    static int veg_token = 1000;
    return ++veg_token;
}

int next_nonveg_static(void) {
    static int nonveg_token = 2000;
    return ++nonveg_token;
}

/* Alternative Concept: Caller-owned counter passed by pointer */
int next_token_ptr(int *counter) {
    if (counter == NULL) return -1;
    return ++(*counter);
}

int main(void) {
    int v1 = next_veg_static(), v2 = next_veg_static();
    int nv1 = next_nonveg_static(), nv2 = next_nonveg_static();
    printf("Static Separate Counters:\n");
    printf("  Veg    : %d, %d\n", v1, v2);
    printf("  Non-Veg: %d, %d\n", nv1, nv2);

    int veg_cnt = 1000, nonveg_cnt = 2000;
    int pv1 = next_token_ptr(&veg_cnt), pv2 = next_token_ptr(&veg_cnt);
    int pnv1 = next_token_ptr(&nonveg_cnt), pnv2 = next_token_ptr(&nonveg_cnt);
    printf("\nPointer-Based Counters (Alternative Concept):\n");
    printf("  Veg    : %d, %d\n", pv1, pv2);
    printf("  Non-Veg: %d, %d\n", pnv1, pnv2);
    return 0;
}
