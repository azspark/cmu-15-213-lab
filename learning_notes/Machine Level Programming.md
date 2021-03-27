# Machine Level Programming

<img src="/Users/zhuzheng/Notes/csapp/Pictures/1.png" alt="1" style="zoom:67%;" />

上图是基本硬件中对程序员可见的部分，经过编译器的机器码通过这些部分操控硬件，更底层的实现主要通过硬件本身。

PC：Program counter 记录下一个指令的地址

Registers: 寄存器，大量被使用

Condition codes：记录状态信息，用于条件分支等

<img src="/Users/zhuzheng/Notes/csapp/Pictures/2 Memory Componet.png" alt="2 Memory Componet" style="zoom:50%;" />

内存主要是以下部分组成:

- **Stack：**用于函数调用，及**局部变量**的存储，这样随着函数的运行，栈顶就能向低地址不断扩展。常用系统中栈的大小是8MB，可通过命令`limit`查看,相同程序的栈的分配是固定的。
- **Shared Libraries：**类似于`printf`和`malloc`的这类**库函数**平时是被存储在磁盘上的，当我们程序需要使用库函数时，就会在程序开始执行时，将它们加载到你的程序中，这称为**动态加载（Dynamic Linking**）。
- **Heap：**用来存放通过**`malloc`、`callc`或`new`**等申请的变量，这些变量在程序运行时会动态变化。当你不断通过`malloc`申请空间又没释放时，堆顶的指针就不会断向高地址增加，使得占用的内存不断变多。堆在分配时是具有随机性的。
- **Data：**该数据区用来存放程序开始时分配的数据，你声明的**全局变量、静态变量或字符常量等**都在这个数据段中。
- **Text：**根据可执行目标文件的内容进行初始化，是放置你的**可执行程序**的位置。这部分区域是只读的。

## 主要知识点

* 寄存器概念，寄存器的操作，记住一些重要寄存器如：
  * %rip：记录指令地址
  * %rsp：记录栈顶位置
* 寻址方法
* Branch Prediction. cpu在执行指令时，永远是一条直线执行是最快的，但程序中往往有分支（if else）要求执行地址的跳转，为了优化，在分支计算不复杂的情况下，会同时执行不同分支的指令，根据运行时的情况决定使用哪个。
  * Conditonal control transfer
  * Conditional move transfer

* 循环的执行：Do while, while, for 等

* 特别的Switch语句会维护一个<u>Jump table</u>的结构进行实现。BTW：使用switch是一种Bad code style。

* ABI（Application Binary Interface）

* Stack的概念：是实现程序Procedure call/return最合适的数据结构

* Calling conventions

  * 函数调用方法：%rip改变，%rsp变化，<u>Stack存储Return Address</u>
  * 传参：一些寄存器：%rdi, %rsi,....Stack
  * Managing Local Data
  * Stack Frame存储函数局部信息
  * Register Saving Conventions：防止在calling一个新的函数时对寄存器的操作影响了上一个函数要记录的信息，解决方法：push到栈里，调用结束pop回寄存器
    * Caller saved
    * Callee saved

* 递归实现时对上述结构的使用

* Array：1-d 2-d， Nested Array vs Multi-level Array

  * N * N Matrix code
  * 结构体的array，进行了两次内存访问

* Structures 在内存中是连续的空间进行存储，但由于内存是以4或8bytes的chunk为单位被访问的，编译器会插入一些间隔使得每个元素的起始地址是4或8的倍数，可以通过更好的元素排列顺序节省空间。

* 浮点数的操作需要用到特殊的寄存器（XMM）和更加复杂的实现

* Memory Layout：如第一部分的图。另外要知道的一点是64位机器寻址往往不会用到全部64位，而是47位

  #### Buffer Overflow

  C语言没有自动的数组越界检查，通过一些没有检查边界的函数如gets()，可以修改stack一些位置的信息，而代码中每次call一个function，会先在stack中push当前汇编代码下一行的地址，如果gets()输入的字符串过长涉及到了这个Return Address，则会造成Stack Smashing Attacks，一些早期的攻击主要针对这种漏洞。另外可以在输入的字符串中包含注入的代码信息，攻击者可以使得程序在执行ret时先执行这些注入的代码再根据攻击者的意图继续，这种攻击叫做Code Injection Attacks。

  ##### 避免方法

  1. 减少代码中overflow的可能性（使用更安全的函数）
  2. System-Level Protections. 在程序开始前在栈中插入随机大小的空间，改程序所有的栈中地址会变化，使得攻击者难以预测哪里插入代码
  3. 使一些片段不可执行代码
  4. Stack Canaries 插入一些特殊值在缓冲区内，在退出前检查缓冲区是否遭到更改

  #### Return Oriented Programming Attacks

