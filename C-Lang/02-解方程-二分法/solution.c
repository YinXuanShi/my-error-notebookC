/*
 * PTA 7-6: 解方程 (二分法)
 * 日期: 2026-11-04
 *
 * 题目: 已知函数 f(x) = cos(2x) * sqrt(x) - c (其中 c 为常数),
 *       在 [x1,x2] 单调递增或递减, 求方程 f(x)=0 在该区间内的解。
 * 输出: 保留小数点后四位数字。
 * 样例: 输入 1.0 2.0 3.0 → 输出 2.6844
 *
 * 【我的错误记录】
 *
 * 错误1: return 语句漏分号
 *   错误写法:  return sqrt(x)*cos(2.0*x)-c
 *   正确写法:  return sqrt(x)*cos(2.0*x)-c;
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
 *
 * 错误3: 二分循环里改 mid 导致区间收缩到错误位置
 *   错误写法:
 *     if (q < 0) {
 *         mid = (mid + r) / 2.0;   // 先偏移了 mid
 *         l = mid;                // 再把偏移后的 mid 给 l → 落点不对
 *     }
 *   正确写法:
 *     if (q < 0) {
 *         l = mid;                // 直接用本轮中点更新 l
 *     }
 *   原因: mid 下一轮开头会被重新计算 mid=(r+l)/2.0, 手动偏移它只会错
 *         二分只需改 l 或 r, 不要动 mid
 *
 * 错误4: 只用 f(r)*f(mid) 判断，端点为根时会丢掉解（隐蔽）
 *   问题: q = f(r)*f(mid), 若 f(r) 恰为 0, 则 q=0, q<0 为假,
 *         走 else 分支把 r 推到 mid, 根被丢弃, 最后输出 x2
 *   正确写法: 分别判断 mid 与两端的符号关系, 并用 <= 0 覆盖端点情况
 *
 * 错误5: r / l 命名与实际左右边界相反（不影响结果但易混）
 *   我的写法里 r 是左边界(x1)、l 是右边界(x2), 与直觉相反, 容易写错判断
 *   修正: 统一用 l=左边界, r=右边界
 */

#include <stdio.h>
#include <math.h>

/* f(x) = cos(2x) * sqrt(x) - c */
double f(double x, double c) {
    return sqrt(x) * cos(2.0 * x) - c;   /* 错误1: 原来漏了分号 */
}

int main(void) {
    double c, x1, x2, x, mid;
    scanf("%lf %lf %lf", &c, &x1, &x2);

    /* 错误5: 统一 l=左边界, r=右边界; 顺手处理 x1>x2 的情况 */
    if (x1 > x2) { double t = x1; x1 = x2; x2 = t; }
    double l = x1, r = x2;

    /* 记录 |f| 最小的点作为兜底答案 */
    double best_x = x1;
    double best_abs = fabs(f(x1, c));
    double f2_abs = fabs(f(x2, c));
    if (f2_abs < best_abs) { best_abs = f2_abs; best_x = x2; }

    for (int i = 0; i < 200; i++) {
        mid = (l + r) / 2.0;

        double fm = f(mid, c);
        if (fabs(fm) < best_abs) {
            best_abs = fabs(fm);
            best_x = mid;
        }

        double fl = f(l, c);
        double fr = f(r, c);

        /* 错误4: 用 <= 0 而不是 < 0, 并分别判断两个半区间 */
        if (fl * fm <= 0) {        /* 根在 [l, mid] */
            r = mid;
        } else if (fm * fr <= 0) { /* 根在 [mid, r] */
            l = mid;
        } else {                   /* 端点情况: 保留 |f| 小的一侧 */
            if (fabs(fl) <= fabs(fr)) { l = mid; }
            else                      { r = mid; }
        }
        if (r - l < 1e-14) break;
    }

    x = best_x;
    printf("%.4f", x);
    return 0;
}
