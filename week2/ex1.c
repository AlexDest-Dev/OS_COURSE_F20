#include <stdio.h>
#include <float.h>
#include <limits.h>

int main() {
    int _integer;
    float _float;
    double _double;
    _integer = INT_MAX;
    _float = FLT_MAX;
    _double = DBL_MAX;
    printf("Integer = %d; Size of Integer = %d\n", _integer, sizeof(_integer));
    printf("Float = %f; Size of Float = %d\n", _float, sizeof(_float));
    printf("Double = %f; Size of Double = %d", _double, sizeof(_double));
    return 0;
}
