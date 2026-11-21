#include <stdio.h>

/* Global variable defined in this file, shared via extern in task05_extern_helper.c */
int global_token = 1000;

int next_token_auto(void) {
    auto int token = 1000;
    return ++token;
}

int next_token_static(void) {
    static int token = 1000;
    return ++token;
}

int next_token_global(void) {
    return ++global_token;
}

/* Declared in task05_extern_helper.c */
int helper_issue_global_token(void);

int main(void) {
    register int i;

    printf("(a) Auto local tokens    : ");
    for (i = 0; i < 3; i++) printf("%d ", next_token_auto());
    printf("\n");

    printf("(b) Static local tokens  : ");
    for (i = 0; i < 3; i++) printf("%d ", next_token_static());
    printf("\n");

    printf("(c) Global/extern tokens : ");
    printf("%d ", next_token_global());          /* From main file: 1001 */
    printf("%d ", helper_issue_global_token());  /* From helper file via extern: 1002 */
    printf("%d\n", next_token_global());         /* From main file: 1003 */

    printf("(d) Register loop variable used for 3 iterations successfully.\n");
    return 0;
}
