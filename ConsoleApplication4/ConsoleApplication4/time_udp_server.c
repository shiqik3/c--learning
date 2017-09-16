#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<time.h>
#include<memory.h>

int sockfd;

void sig_handler(int signo) {
	if (signo == SIGINT) {
		printf("server close\n");
		close(sockfd);
		exit(1);
	}
}

//输出客户端的信息
void out_addr(struct sockaddr_in* addr){
	char ip[16];
	int port = 0;
	memset(ip, 0, sizeof(ip));
	inet_ntop(AF_INET, &addr->sin_addr.s_addr, ip, sizeof(ip));
	port = ntohs(addr->sin_port);
	printf("client: %s(%d)\n", ip, port);
}

//与客户端尽心通信
void do_service() {
	struct  sockaddr_in cliAddr;
	socklen_t len = sizeof(cliAddr);
	char buff[1024];
	memset(buff, 0, sizeof(buff));

	//接受客户端的数据报文
	//使用recvfrom而不适用recv函数的主要目的是为了获取客户端信息
	if (recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&cliAddr, &len) < 0) {
		perror("recvfrom error");
	}
	else {
		out_addr(&cliAddr);
		printf("client send info: %s\n", buff);

		//向客户端发送数据报文
		long int t = time(0);
		char* ptr = ctime(&t);
		size_t size = strlen(ptr) * sizeof(char);
		if (sendto(sockfd, ptr, size, 0, (struct sockaddr*)&cliAddr, len) < 0) {
			perror("sendto error");
		}
	}
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("usage: %s port\n", argv[0]);
		exit(1);
	}

	//注册ctrl+c 信号处理函数
	if (signal(SIGINT,sig_handler) == SIG_ERR) {
		perror("signal sigint error");
		exit(1);
	}

	//步骤1：创建socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);    //SOCK_DGRAM为UDP协议
	if (sockfd < 0) {
		perror("socket error");
		exit(1);
	}

	//设置socket的相关选项
	int ret;
	int opt = 1;    //1表示启动该选项
	//设置为可重新使用端口，每次启动该端口时，原来对该端口使用将失效
	if ((ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) < 0) {
		perror("setsockopt error");
		exit(1);
	}

	//步骤2: 调用bind函数将socket和地址进行绑定
	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;    //ipv4
	servAddr.sin_port = htons(atoi(argv[1]));    //port
	servAddr.sin_addr.s_addr = INADDR_ANY;    //ip
	if (bind(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
		perror("bind error");
		exit(1);
	}

	//步骤3:与客户端进行双向的数据通信；
	while (1) {
		do_service();
	}

	return 0;
}
