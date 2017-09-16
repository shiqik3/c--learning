#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<signal.h>
#include<pthread.h>

int sockfd;
int PORT = 8888;          //通信端口号
int bStop = 0;
typedef struct client1 {
	char name[20];
	int sock;
} Client;
Client client[100];         //能同时容纳100个客户上线  
int size = 0;               //存放当前在线客户端数目  

void* task(void* p);

void sig_handler(int signo) {
	if (signo == SIGINT) {
		bStop = 1;
		printf("service close");
		exit(1);
	}
}

void sendMsgToAll(char* msg) {
	int i;
	for (i = 0; i < size; i++) {
		if (client[i].sock != 0) {
			printf("sendto%d\n", client[i].sock);
			send(client[i].sock, msg, strlen(msg), 0);
		}
	}
}

void init() {
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("scoket error");
		exit(1);
	}
	struct sockaddr_in sockAddr;
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(PORT);
	sockAddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sockfd, (struct sockaddr*)&sockAddr, sizeof(sockAddr)) < 0) {
		perror("bind error");
		exit(1);
	}

	if (listen(sockfd, 100) < 0) {
		perror("listen error");
		exit(1);
	}
	printf("服务器初始化完毕！\n");
}

void start() {
	printf("服务器正在启动...\n");
	printf("服务器启动成功!\n");
	printf("靠靠靠靠....\n");
	while (!bStop) {
		/*创建连接上来的客户端通信地址*/
		struct sockaddr_in client_Addr;
		socklen_t client_len = sizeof(client_Addr);
		int fd = accept(sockfd, (struct sockaddr*)&client_Addr, &client_len);
		if (fd < 0) {
			perror("accept error");
			continue;
		}
		/*为连接上来的客户端开辟新的线程*/
		client[size].sock = fd;
		pthread_t p_id;
		pthread_create(&p_id, 0, task, &fd);
	}
}
void closeServe() {
	printf("服务器正在关闭...\n");
	close(sockfd);
	printf("服务器关闭成功!\n");
	exit(0);
}

void* task(void* p) {
	int socktemp = *(int*)p;
	char name[20] = {};      //用于接收用户名  
	char buf[1024] = {};
	int i, temp;
	if (read(client[size].sock, name, sizeof(name))>0)
		strcpy(client[size].name, name);
	temp = size;
	size++;
	/*首次进入聊天室打印如下提示*/
	char remind[100] = {};
	sprintf(remind, "欢迎%s进入本聊天室..", client[size - 1].name);
	sendMsgToAll(remind);
	while (1) {
		if (read(socktemp, buf, sizeof(buf)) <= 0) {
			char remind1[100] = {};
			sprintf(remind1, "%s退出聊天室", client[temp].name);
			sendMsgToAll(remind1);
			for (i = 0; i<size; i++)
				if (client[i].sock == socktemp) {
					client[i].sock = 0;
				}
			return;//结束线程  
		}
		/*把消息发送给除了他自己的其他所有在线的客户端*/
		char msg[100] = {};
		sprintf(msg, "%s:%s", client[temp].name, buf);
		sendMsgToAll(msg);
		memset(buf, 0, strlen(buf));
	}
}



int main(int argc,char* argv[]) {
	//按ctrl-c时中止服务端程序
	signal(SIGINT, sig_handler);
	init();
	start();
	closeServe();
	return 0;
}


