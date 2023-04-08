#include <regex.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
    regex_t regex;
    int regCheck;
    regmatch_t matches[50];

    /* Compile regular expression */
    regCheck = regcomp(&regex, "^a", 0);

    if (regCheck) {
        fprintf(stderr, "Could not compile regex.\n");
        exit(1);
    }

    /* Execute regular expression */
    regCheck = regexec(&regex, "a", 0, NULL, 0);
    if (!regCheck) {
        printf("Match\n");
        printf("", );
    } else if ( regCheck == REG_NOMATCH) {
        printf("No match\n");
    }

    regfree(&regex);
}
