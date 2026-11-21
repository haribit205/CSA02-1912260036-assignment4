extern int global_token;

int helper_issue_global_token(void) {
    return ++global_token;
}
