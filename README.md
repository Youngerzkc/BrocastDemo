# BrocastDemo
       单播用于两个主机之间的端对端通信，广播用于一个主机对整个局域网上所有主机上的数据通信。单播和广播是两个极端，要么对一个主机进行通信，要么对整个局域网上的主机进行通信。实际情况下，经常需要对一组特定的主机进行通信，而不是整个局域网上的所有主机，这就是多播的用途。

       多播，也称为“组播”，将局域网中同一业务类型主机进行了逻辑上的分组，进行数据收发的时候其数据仅仅在同一分组中进行，其他的主机没有加入此分组不能收发对应的数据。

       多播的地址是特定的，D类地址用于多播。D类IP地址就是多播IP地址，即224.0.0.0至239.255.255.255之间的IP地址，并被划分为局部连接多播地址、预留多播地址和管理权限多播地址3类：

 局部多播地址：在224.0.0.0～224.0.0.255之间，这是为路由协议和其他用途保留的地址，路由器并不转发属于此范围的IP包。

 预留多播地址：在224.0.1.0～238.255.255.255之间，可用于全球范围（如Internet）或网络协议。

管理权限多播地址：在239.0.0.0～239.255.255.255之间，可供组织内部使用，类似于私有IP地址，不能用于Internet，可限制多播范围。

linux多播编程步骤：

        1>建立一个socket;

        2>设置多播的参数，例如超时时间TTL，本地回环许可LOOP等

        3>加入多播组

        4>发送和接收数据

        5>从多播组离开
 多播程序设计使用setsockopt()函数和getsockopt()函数来实现，组播的选项是IP层的。
 
 1．选项IP_MULTICASE_TTL

选项IP_MULTICAST_TTL允许设置超时TTL，范围为0～255之间的任何值，例如：
unsigned char ttl=255;

setsockopt(s,IPPROTO_IP,IP_MULTICAST_TTL,&ttl,sizeof(ttl)); 
2．选项IP_MULTICAST_IF

选项IP_MULTICAST_IF用于设置组播的默认默认网络接口，会从给定的网络接口发送，另一个网络接口会忽略此数据。例如：

struct in_addr addr;

setsockopt(s,IPPROTO_IP,IP_MULTICAST_IF,&addr,sizeof(addr));

参数addr是希望多播输出接口的IP地址，使用INADDR_ANY地址回送到默认接口。

默认情况下，当本机发送组播数据到某个网络接口时，在IP层，数据会回送到本地的回环接口，选项IP_MULTICAST_LOOP用于控制数据是否回送到本地的回环接口。例如：
unsigned char loop;

setsockopt(s,IPPROTO_IP,IP_MULTICAST_LOOP,&loop,sizeof(loop));参数loop设置为0禁止回送，设置为1允许回送。

 
3．选项IP_ADD_MEMBERSHIP和IP_DROP_MEMBERSHIP

加入或者退出一个多播组，通过选项IP_ADD_MEMBERSHIP和IP_DROP_MEMBER- SHIP，对一个结构struct ip_mreq类型的变量进行控制，struct ip_mreq原型如下：
struct ip_mreq          
{ 
    struct in_addr imn_multiaddr;      /*加入或者退出的广播组IP地址*/ 

  struct in_addr imr_interface;      /*加入或者退出的网络接口IP地址*/

};
 

选项IP_ADD_MEMBERSHIP用于加入某个多播组，之后就可以向这个多播组发送数据或者从多播组接收数据。此选项的值为mreq结构，成员imn_multiaddr是需要加入的多播组IP地址，成员imr_interface是本机需要加入广播组的网络接口IP地址。例如：

struct ip_mreq mreq;

setsockopt(s,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));

多播服务器的程序设计很简单，建立一个数据包套接字，选定多播的IP地址和端口，直接向此多播地址发送数据就可以了。多播服务器的程序设计，不需要服务器加入多播组，可以直接向某个多播组发送数据。
客户端只有在加入多播组后才能接受多播组的数据，因此多播客户端在接收多播组的数据之前需要先加入多播组，当接收完毕后要退出多播组。







