# Exceptional Control Flow

课参考链接：https://wdxtub.com/csapp/thin-csapp-5/2016/04/16/



## 本章要点

* 理解系统调用是通过异常中Trap的机制实现的
* Concurrent(并发)的概念与对写Signal Handler的影响
* Block Signal(Sigprocmask)的使用方法与**原因**
* Sigsuspend怎么用
* Nonlocal jump的概念与应用

## 异常

异常是异常控制流的一种形式，被硬件和操作系统共同控制。进一步的可以定义为：为应对进程状态改变突然的控制流变化。异常由Exception handler来处理。

在exception handler处理完成后有几种可能：

1. 返回到原来的指令
2. 返回到原来指令的下一个指令
3. 不返回（无法恢复的系统错误）

系统会维护一个Exception table，记录每个exception handler程序在内存中的位置，exception table的起始位置由cpu上exception table stage register，在执行exception handler时处于内核态即可以调用所有系统资源。

### 四种异常类型

* Interrupt 进程外的I/O信号
* Trap 用来做System call 如read, exit, fork
  * 对于用户来说调用这种system call就像调用普通函数，但是其具体实现非常不同，常规态优先级低很多事无法做无法像在内核态时调用资源比如系统栈
* Fault（可能恢复的error，如page fault
* Abort 无法恢复的错误

## 进程

进程是计算机科学中最为重要的思想之一，进程才是程序（指令和数据）的真正运行实例。之所以重要，是因为进程给每个应用提供了两个非常关键的抽象：一是逻辑控制流，二是私有地址空间。逻辑控制流通过称为上下文切换(context switching)的内核机制让每个程序都感觉自己在独占处理器。私有地址空间则是通过称为虚拟内存(virtual memory)的机制让每个程序都感觉自己在独占内存。这样的抽象使得具体的进程不需要操心处理器和内存的相关适宜，也保证了在不同情况下运行同样的程序能得到相同的结果。

### Fork的进程的特点

* fork函数调用一次返回两次
* 与原进程并发（concurrent）执行
* 拥有与原进程内容重复但是相互独立的地址空间
* 与原进程共享文件

### 进程切换



## 系统调用

### 必要的调用失败处理

当系统调用函数失败时，一般会返回-1，在调用系统函数时，最好要进行检查，一种方式是写一个wrapper：

```c
pid_t Fork(void) 2{
		pid_t pid;
  	if ((pid = fork()) < 0)
    		unix_error("Fork error");
  	return pid;
}
void unix_error(char *msg) /* Unix-style error */ 2{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}
```

## 信号

信号使得内核或者一个进程得以影响其他进程的运行。对于每个进程，系统会维护一个pending bit vector和blocked bit vector来。系统定义了31种不同的信号，信号发出的原因各不相同，但是默认的对接收到的进程的影响只有四种，可以自行定义handler来改变进程对于接收信号后的行为，但是**SIGSTOP**和**SIGKILL**的默认反应不可改变：

### 进程的一生



**一个要注意的点是一种handler的执行可能被另一种信号打断然后执行另一种handler**

1. The process terminates.
2. The process terminates and dumps core.
3. .The process stops (suspends) until restarted by a SIGCONT signal.
4. The process ignores the signal.（SIGCONT）

### 信号的Blocking和Unblocking

对于信号的blocking有直接和间接两种方式

* 间接：一个进程在处理一种信号的时候会使得其他到来的该种信号处理pending状态
* 直接：调用sigpromask，**对该函数的使用是理解本章的重点**

### 安全的信号处理

一些指导建议：

1. G0：使得handlers尽可能简单
2. G1：在handler内只调用*async-signal-safe*的函数。*async-signal-safe* function的定义为：
   * 该函数只访问局部变量
   * 该函数不会被singal handler打断
3. G2：许多linux async-signal-safe函数会设定errno当其执行遇到错误，这可能会影响其他函数。在执行前保存erron执行后恢复errno（如果执行完直接exit就不用）
4. G3：通过blocking所有信号来保护全局的数据结构
5. G4：通过volatile申明全局变量
6. G5：用sig_atomic_t申明flag

### 信号处理不当的场景1：race

在有job控制的shell程序中，如果fork了一个子进程且在原进程addjob前就结束发出了SIGCHLD并且handler处理时deletejob了，原进程会继续addjob，那么在job列表中这个进程永远不会被删除。