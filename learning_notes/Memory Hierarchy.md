# Memory Hierarchy

存储结构是按金字塔形状层次划分的，约上层容量越小，读写速度越快，对存储结构的理解可以帮助我们写出更好的利用上层存储的代码，也就是更高效的代码。

<img src="/Users/zhuzheng/Notes/csapp/Pictures/Memory Hierarchy.png" alt="Memory Hierarchy" style="zoom:50%;" />

## Memory Read/Write Transaction



## RAM (Random Access Memory)

* SRAM(Static) **cache**

* DRAM(Dynamic) **Main Memories, frame buffers**

### 差异

1. 速度 SRAM更快
2. 组成结构 DRAM 1transistors/bit SRAM 6 transistors/bit
3. 刷新需求 DRAM（需要周期性刷新）SRAM （不需要）
4. 发展趋势 都接近极限 DRAM（受限于需要的最少电容） SRAM（取决于半导体技术）

Nonvolatile memories

### DRAM

<img src="/Users/zhuzheng/Notes/csapp/Pictures/DRAM布局.png" alt="DRAM布局" style="zoom:50%;" />

上图是一个对64M内存数据存取的示意图，一块64M的内存可以分为8个chips，每个数据都是二维索引的，每个单元可以存8个bit，收到行信息后每个chip会将整行存到缓冲，接着收到列信息后每个chip提取出特定的8个bit，8个chip合起来就得到了需要的64bit数据。

## Locality of reference

### **<u>Principle of Locality</u>:**

Programs tend to use data and instructions with addresses near or equal to those they have used recently

* Spatial locality
* Temporal locality

### Why

<u>To bridging the speed gap between cpu and memory</u>



## The Memory hierarchy

L0-L6,不同层级间数据一直在流动，越往低层流动的数据单位大小越大（因为更慢，）。

## Storage technologies and trends

* Disk
* SSD(Solid State Disks) flash memory