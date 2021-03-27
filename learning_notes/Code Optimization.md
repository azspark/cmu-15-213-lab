# Code Optimization

**There is more to performance than asymptotic complexity!**

一些针对特定平台，硬件设计的程序优化没有普适性，本章首先介绍一些广泛有效的优化方法



## Generally Useful Optimizations

* Code Motion：减少循环中相同但是重复计算的模块。
* Sharing of common subexpression

## Optimization Blockers

### 编译器的限制

* 基本限制：不能改变程序行
* 对于程序员很明显的东西对于编译器并不
* 大多分析只局限于某个范围（整个程序的分析太昂贵）
* 分析智能基于静态信息
* 在有疑虑时，倾向于保守

```C
for (i = 0; i < strlen(s); i++)
	if (s[i] >= 'A' && s[i] <= 'Z') 
    	s[i] -= ('A' - 'a');
```

这个代码中调用了多次strlen，会随着string长度增加多项式时间增长，但编译器无法优化这部分，原因在于：

1. Procedure call对于编译器是黑盒
2. strlen会输入string作为参数，编译器可能认为其会改变string更加不敢优化

### Memory Alising

循环中可能涉及多次不必要的对数组的寻址，但编译器也不敢直接优化，怕影响程序行为，程序员应该养成设置局部变量的习惯进行优化。

## 指令并行优化

* 需要对现代编译器设计有一定理解
* 性能受限于数据间的依赖
* 简单的转换可以得到较大的提升

超标量处理器可以在一个时钟周期内执行多个指令，指令从序列指令流中提取并且通常可以动态规划。

## Branch Prediction

处理器做的事情

程序员或者编译器的优化：把条件语句转化成其他形式：

```C
//原始
if (data[c] >= 128)
    sum += data[c];
//优化
int t = (data[c] - 128) >> 31;
sum += ~t & data[c];
```

经典案例：

https://stackoverflow.com/questions/11227809/why-is-processing-a-sorted-array-faster-than-processing-an-unsorted-array

