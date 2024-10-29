#include <stdio.h>

int foo(int a, int b)
{
    int c;

    asm volatile(
        "mul %0, %1, %1;"
        "mul %2, %3, %3;"
        "add %0, %0, %2;"
        : "=r"(c)
        : "r"(a), "r"(b), "r"(b)
    );

    return c;
}

int main(void)
{
    int a = 3;
    int b = 4;
    int c = foo(a, b);

    printf("c = %d\n", c);

    return 0;
}