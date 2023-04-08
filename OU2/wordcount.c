#include <regex.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
    regex_t regex;
    int regCheck;

    /* Compile regular expression */
    regCheck = regcomp(&regex, "^a", 0);

    if (regCheck) {
        fprintf(stderr, "Could not compile regex.\n");
        exit(1);
    }

    /* Execute regular expression */
    regCheck = regexec(&regex, "b", 0, NULL, 0);
    if (!regCheck) {
        puts("Match");

    } else if ( regCheck == REG_NOMATCH) {
        puts("No match");
    }

    regfree(&regex);
}
