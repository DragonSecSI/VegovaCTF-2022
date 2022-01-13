#include <stdio.h>

int main() {
    char name[16];
    printf("Enter your name:\n");
    scanf("%15s", name);
    printf("Greetings, %s!}\n", name);
    return 0;
}
