# System I/O

## Unix I/O

Linux中文件是一堆byte序列，所有I/O设备用文件表示，<u>内核本身也是用文件来表示</u>

### 要点

打开、关闭、读、写文件背后的知识

### 文件类型

* Regular File
* Directory 对文件夹内文件的索引，至少包含两个entry（. 和 ..）
* Socket
* Name pipes(FIFO)
* Symbolic links
* Character and block devices

### 打开文件

每个通过shell打开的进程会有三个文件被维护

* Standard input
* standard output
* standard error

## Metadata, sharing and rediction



Discriptor table: 每个进程一个

Open file table：每个文件一个

v-node table：每个文件一个

Dup2?

## Standard I/O

**Standard I/O models open files as** **streams**

Short count?

## 选择I/O的库

- **When to use standard I/O**
  -  When working with disk or terminal files
- When to use raw Unix I/O
  * inside signal handlers, because Unix I/O is async-signal-safe。 In rare cases when you need absolute highest performance

* When to use RIO
  * When you are reading and writing network sockets. Avoid using standard I/O on sockets