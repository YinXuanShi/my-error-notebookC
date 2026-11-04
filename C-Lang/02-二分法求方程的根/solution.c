/*
 * PTA 7-5: 二分法求方程的根
 * 日期: 2026-11-04
 *
 * 题目: f(x) = cos(2x) * sqrt(x) - c, 给定 c, x1, x2 (x2>x1),
 *       f(x1) 与 f(x2) 异号, 用二分法求 f(x)=0 在 [x1,x2] 内的根。
 * 输出: 根, 保留 4 位小数。
 * 样例: 输入 1.0 2.0 3.0 → 输出 2.6844
 *
 * 【我的错误记录】
 *
 * 错误1: return 语句漏分号
 *   错误写法:  return sqrt(x)*cos(2.0*x)-c
 *   正确写法:  return sqrt(x)*cos(2.0*x)-c;
 *   原因: C 语言每条语句必须以分号结尾
 *
 * 错误2: 用未初始化的变量去初始化别的变量（致命）
 *   错误写法:
 *     double r = x1;    // 此时 x1 还没被 scanf 赋值, 是垃圾值
 *     double l = x2;    // 同上
 *     scanf(...);       // 现在才读入, 但 r/l 已经固定成垃圾了
 *   正确写法:
 *     scanf(...);       // 先读入
 *     r = x1;           // 再赋值
 *     l = x2;
 *   规则: scanf 之前不要用还没读入的变量初始化别的变量
 *         顺序永远是: 声明 → scanf → 用读入的值
 *
 * 错误3: 二分循环里有冗余代码（不影响结果但多余）
 *   错误写法:
 *     if (q < 0) {
 *         mid = (mid + r) / 2.0;   // 没用, 下一轮被覆盖
 *         l = mid;
 *     }
 *   正确写法:
 *     if (q < 0) {
 *         l = mid;                 // 直接赋值就够了
 *     }
 *   原因: mid 下一轮循环开头会被重新计算 mid=(r+l)/2.0, 这里改 mid 没意义
 */

#include <stdio.h>
#include <math.h>

/* f(x) = cos(2x) * sqrt(x) - c */
double f(double x, double c) {
    return sqrt(x) * cos(2.0 * x) - c;    /* 错误1: 原来漏了分号 */
}

int main(void) {
    double c, x1, x2, x, q, mid;
    double r, l;

    scanf("%lf %lf %lf", &c, &x1, &x2);

    r = x1;    /* 错误2: 原来在 scanf 之前赋值, x1/x2 是垃圾值 */
    l = x2;

    for (int i = 0; i < 111; i++) {
        mid = (r + l) / 2.0;
        q = f(r, c) * f(mid, c);
        if (q < 0) {
            l = mid;    /* 错误3: 原来还有一行 mid=(mid+r)/2.0, 多余 */
        } else {
            r = mid;    /* 同上, 原来还有一行 mid=(mid+l)/2.0 */
        }
    }

    x = mid;
    printf("%.4f", x);
    return 0;
}
