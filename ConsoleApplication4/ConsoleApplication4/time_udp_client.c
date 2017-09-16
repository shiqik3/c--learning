#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("usage: %s ip port\n", argv[0]);
		exit(1);
	}

	//步骤1:创建socket
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("socket error");
		exit(1);
	}

	//步骤2:调用recvfrom和sendto等函数和服务端双向通信
	struct sockaddr_in servAddr;	//封装服务器的地址信息
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;	//ipv4
	servAddr.sin_port = htons(atoi(argv[2]));	//端口
	inet_pton(AF_INET, argv[1], &servAddr.sin_addr.s_addr);

	//在UDP能否调用connect来与服务器链接？
	//TCP中地啊调用connect会进过三次握手，建立起双方的链接
	//单UDP中调用了connect后，以后可以直接使用send而不必只有sendto来发送消息给对方。
	//此外，还有一个好处就是因为sock记录了客户端的ip，使用该sockfd可以只接受指定服务器发来的消息，而不会
	//接受服务器意外其他地方发来的消息。
	if (connect(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
		perror("connect error");
		exit(1);
	}

	char buff[1024] = "hello world";
	//向服务器发送数据报文
	if ((sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&servAddr, sizeof(servAddr))) < 0) {
		perror("sendto error");
		exit(1);
	}
	else {
		//接受服务器端的数据报文
		memset(buff, 0, sizeof(buff));
		size_t size;

		//1.为什么recv里没有指定服务器地址，却可以发送成功？
		//因为如果之前的sendto发送成功，则sockfd里将保存通讯双方的信息，这里就可以直接使用这个sockfd来通信
		//2.为什么不需要判断recv的返回值为0？（0表示对方已经关闭链接）
		//因为UDP是无连接的通信，通信双方是没有建立连接的，数据被传到链路层以后发送方就可以关闭，因此这里不需判断是否为0
		if ((size = recv(sockfd, buff, sizeof(buff), 0)) < 0) {
			perror("recv error");
			exit(1);
		}
		else {
			printf("%s", buff);
		}
	}
}
