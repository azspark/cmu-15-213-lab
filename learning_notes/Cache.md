# Cache

**Cache memories** **are small, fast <u>SRAM-based</u> memories managed automatically in hardware**

<img src="/Users/zhuzheng/Notes/csapp/Pictures/Cache Structure.png" alt="Cache Structure" style="zoom:50%;" />

### 本章要点

* Cache在硬件中的位置
* Cache的存储结构(S E B)以及原始地址怎么对应到cache的block(Set index找到set，通过tag在set中找到对应的line，通过block offset确定这个block中第几位是要的byte)
* 多核CPU中cache的结构
* cache读写策略(read/write hit/miss)
* 如何写Cache Friendly code
* 理解通过Blocking策略减少Cache miss
* Memory Moutain那张图的解读
* cache处理的是物理地址不是虚拟地址

### 为什么用地址中间几位比特作为set index?

通过这种方式使得在内存中相邻的块会分到不同的cache set中，在访问连续较长的内存的时候使其分散到不同set中避免用完所有line导致不断替换。

### Write 写入几种策略

#### Write-hit

cache中有这段内容

* write-though 直接写入memory
* write-back 先写入cache，直到这个line被替换

#### Write-miss

cache中没有

* Write-allocate 先load进入cache，在cache中更新
* No-write-allocate 直接写入memory

### Cache结构

data cache， instruction cache

### Write Cache Friendly Code

* Focus on the inner loops of the core functions
* Repeted references to variables are good 
* Stride-1 reference patterns are good

### Memory Mountain

<img src="/Users/zhuzheng/Notes/csapp/Pictures/Memory Mountain.png" alt="Memory Mountain" style="zoom:50%;" />

这张图是作者设计了一个函数分析读取数据的速度随着数组的大小（size）和stride变化趋势。

从中主要可以看到三个点：

1. Ridges of temporal locality. 反映出随着数组大小变化在不同级别cache的存储。stride也很大的时候趋势更加明显，随着数组大小变大，当前的cache装不下只能用下一级cache存储速度一下子会掉很多。
2. Slopes of spatial locality. 当stride更小的时候，hit的几率更高速度更快。
3. Aggressive prefetching. 在stride很小的一段，当array size增大时仍然保持了L1 cache的速度，并没有第一点中的特征，这是由于硬件的prefetch机制，Core i7的存储系统自动识别出了stride-1的pattern并在一些区域访问前提前取到了cache中。



### 矩阵计算中通过Blocking技术减少cache miss

从食堂回来的路上想明白了大概为啥能优化