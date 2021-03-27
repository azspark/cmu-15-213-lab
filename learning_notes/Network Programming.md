# Network Programming

## Network Structure

根据网络的应用范围和架构可以分为

- SAN - System Area Network
  - Switched Ethernet, Quadrics QSW, …
- LAN - Local Area Network
  - Ethernet, ..
- WAN - Wide Area Network
  - High speed point-to-point phone lines

### 最基本的单位：Ethernet Segment

* 由若干主机(hosts)通过交换机(hub)连接，通常范围是房间或一层楼
* 每个 Ethernet 适配器有一个唯一的 48 位的地址（也就是 MAC 地址），例如 `00:16:ea:e3:54:e6`
* 不同主机间发送的数据称为帧(frame) - a chuck of bits
* Hub 会把每个端口发来的所有数据复制到其他的端口
  - 所有的主机都可以看到所有的数据（注意安全问题）

### 下一层 - Bridged Ethernet Segment

* a set of wires and small boxes

* 通常范围是一层楼，通过不同的 bridge 来连接不同的 ethernet segment。Bridge 知道从某端口出发可达的主机，并有选择的在端口间复制数据。
* 自动学习与选择性的传输数据以达到最好的bandwith利用

### 下一层 - internets

* 不同的（也许不兼容）的 LAN 可以通过 router 来进行物理上的连接，这样连接起来的网络称为 internet（注意是小写，大写的 Internet 可以认为是最著名的 internet）

**目的：使得每个host可以看做是与其他所有host在一个总线上相连接**

### 重要概念

#### Router

* 连接不同类型的网络

#### Protocal

* 命名策略：给每个host唯一的标识
* 传递机制：

## 从程序员来说网络的三个核心概念

1. Hosts are mapped to a set of 32-bit <u>**IP addresses**</u> 

   ▪ 127.0.0.1 (always *localhost*)

2. The set of IP addresses is mapped to a set of identifiers called Internet **<u>Domain Names</u>**

   ▪ 128.2.217.3 is mapped to www.cs.cmu.edu

3. Connection的概念，一个host上的进程可以通过connection与Internet上另一个host交流

## Global IP Internet

### 主要协议

IP (Internet Protocol)

* Provides *basic naming scheme* and unreliable *delivery capability* of packets (datagrams) from *host-to-host*

UDP (Unreliable Datagram Protocol)

* Uses IP to provide *unreliable* datagram delivery from process-to-process

TCP (Transmission Control Protocol)

* Uses IP to provide *reliable* byte streams from process-to-process over connections
  

### IP地址

TCP/IP设置了统一的 *network byte order* (big-endian byte order) 

### DNS(Domain Name System)

* distributed worldwide database

## Socket Interface

* 用于和Unix I/O函数一起来构建网络应用
* 在所有现代操作系统中都有

### Socket的概念

* 对于内核，socket是communication的终点
* 对于应用，socket是文件描述符用于从网络中读/写
* client和server通过向socket descriptor读/写来进行通信
* socket I/O与普通I/O的区别在于如何“打开”socket descriptor

对于Linux内核来说，socket是连接的终点，而对于Linux应用来说socket是打开的文件(with correspoding descriptor)

## Web servers

### HTTP

**HyperText Transfer Protocol**

* The content returned in HTTP responses can be either static or dynamic

#### **HTTP Requests**

- **Request line:** \<method> \<uri> \<version>
  ▪ \<method> is one of **GET**, **POST**, **OPTIONS**, **HEAD**, **PUT**,

  **DELETE**, or **TRACE**

   ▪ \<uri> is typically URL for proxies, URL suffix for servers

  ▪ A URL is a type of URI (Uniform Resource Identifier)

  ▪ See http://www.ietf.org/rfc/rfc2396.txt
   ▪ \<version> is HTTP version of request (**HTTP/1.0** or **HTTP/1.1**)

**HTTP Responses**

- HTTP response is a response line followed by zero or more response headers, possibly followed by content, with blank line (“\r\n”) separating headers from content.

### Proxy

A intermediary between a client and an origin server

* To the client the proxy acts like a server
* To the sever, the proxy ascts like a client
* **Can perform useful functions as requests and responses pass by**
  * Caching, logging, anonymization, filtering, transcoding