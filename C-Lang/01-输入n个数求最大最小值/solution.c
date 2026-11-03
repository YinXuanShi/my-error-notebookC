/*
 * PTA 7-1: 输入 n 个数求最大最小值
 * 日期: 2026-11-03
 *
 * 【我的错误记录】
 *
 * 错误1: 参数没写类型
 *   错误写法:  int MIN(*p, *n);
 *   正确写法:  int MIN(int *p, int n);
 *   原因: 参数必须写完整类型, *p 前面要有 int
 *
 * 错误2: 调用函数时多写了类型
 *   错误写法:  int a = MIN(p, int n);   // 多了 int
 *             int b = MAX(p, *n);      // 多了 *
 *   正确写法:  int a = MIN(p, n);
 *   规则: 声明/定义时写类型, 调用时只写变量名, 不写类型不加 *
 *
 * 错误3: 函数体内比较对象选错
 *   错误写法:  if (p[0] > p[j]) { min = p[j]; }   // 每次都跟 p[0] 比
 *   正确写法:  if (p[j] < min) { min = p[j]; }    // 跟当前 min 比
 *   原因: p[0] 是固定值, 应该跟不断更新的 min/max 比
 */

#include <stdio.h>
#include <stdlib.h>

/* 前置声明: 参数必须写完整类型 int *p, int n */
int MIN(int *p, int n);
int MAX(int *p, int n);

int main(void) {
    int n;
    scanf("%d", &n);

    int *p = malloc(n * sizeof(int));
    if (p == NULL) {        /* malloc 之后必须判空 */
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    /* 调用时只写变量名, 不写类型, 不加 * */
    int a = MIN(p, n);      /* 不是 MIN(p, int n) */
    int b = MAX(p, n);      /* 不是 MAX(p, *n) */
    printf("%d %d", a, b);

    free(p);                /* 用完释放 */
    p = NULL;               /* 置空好习惯 */
    return 0;
}

int MIN(int *p, int n) {
    int min = p[0];
    for (int j = 1; j < n; j++) {
        if (p[j] < min) {   /* 跟 min 比, 不是跟 p[0] 比 */
            min = p[j];
        }
    }
    return min;
}

int MAX(int *p, int n) {
    int max = p[0];
    for (int j = 1; j < n; j++) {
        if (p[j] > max) {   /* 跟 max 比, 不是跟 p[0] 比 */
            max = p[j];
        }
    }
    return max;
}
