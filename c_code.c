//
// Created by bruce on 2025/12/21.
//
#include <stdio.h>

int main(int argc, const char * argv[]) {
    printf("Enter foot inch:");
    int inch;
    int foot;
    scanf("%d %d", &foot, &inch);
    float res = (foot + inch / 12.0) * 0.3048;
    printf("身高是: %.2f m\n", res);
}