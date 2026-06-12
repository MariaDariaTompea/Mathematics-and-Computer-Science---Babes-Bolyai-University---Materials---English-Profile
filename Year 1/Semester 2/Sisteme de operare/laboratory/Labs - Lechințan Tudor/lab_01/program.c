#include <stdio.h>

/*
    argc - number of arguments.
    argv - an array of arguments.
    argv[0] - path used to invoke our program.
    argv[1..] - arguments passed to our program.
*/
int main(int argc, char* argv[]) {
    for (int i = 0; i < argc; ++i) {
        printf("%d: %s\n", i, argv[i]);
    }
    
    return 0;
}
