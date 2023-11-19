#include <stdio.h>

int main()
{
    printf("Майя Введите 1 число\n");
    int x = 0;
    char number[10];
    fgets(number, 10, stdin);
    x = atoi(number);
    printf("Число 1 = %d\n", x);

    printf("Майя Введите 2 число\n");
    int y = 0;
    char number2[10];
    fgets(number2, 10, stdin);
    y = atoi(number2);
    printf("Число 2 = %d\n", y);
    printf("х * y = %d\n", x * y);
    printf("х/y = %d\n", x/y);

    printf("х%y = %d\n", x % y);
    return 0;
}
