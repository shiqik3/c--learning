/*基于TCP协议的多线程聊天室客户端口*/
#include <stdio.h>  
#include <stdlib.h>  
#include <sys/socket.h>  
#include <netdb.h>
#include <unistd.h>  
#include <signal.h>  
#include <pthread.h>  
#include <string.h>

int sockfd;
char name[20];
char *IP = "127.0.0.1";
short PORT = 8888;

void sig_handler(int signo);
void start();
void init();
void* task(void* p);

int main() {
	signal(SIGINT, sig_handler);        //将信号2注册为自定义函数，用于退出  
	printf("正在启动...\n");
	printf("启动成功，请输入用户名:");
	scanf("%s", name);
	init();
	write(sockfd, name, strlen(name));
	start();
}

void sig_handler(int signo) {
	if (signo == SIGINT) {
		printf("service close");
		exit(1);
	}
}

void start() {
	/*客户端除了要给服务器发送数据外，还要接收服务器的数据
	而这两个步骤是并行的，所以我们在主线程中写，开辟的线程中读*/
	pthread_t pid;
	pthread_create(&pid, 0, task, 0);
	char msg[1024] = {};
	while (1) {
		scanf("%s", msg);
		write(sockfd, msg, strlen(msg));
		/*必须把缓冲区清空*/
		memset(msg, 0, strlen(msg));
	}
}

void init() {
	/*步骤和服务器端差不多*/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("socket error");
		exit(-1);
	}
	/*创建通信地址*/
	struct sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(PORT);
	inet_pton(AF_INET, IP, &servAddr.sin_addr.s_addr);
	/*连接服务器*/
	if (connect(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
		perror("connect error");
		exit(1);
	}
	printf("连接服务器成功！\n");
}

/*线程函数，用于读服务器发送过来的数据*/
void* task(void* p) {
	while (1) {
		char buf[100] = {};
		if (read(sockfd, buf, sizeof(buf)) <= 0)
			return;
		printf("%s\n", buf);
		memset(buf, 0, sizeof(buf));
	}
}
