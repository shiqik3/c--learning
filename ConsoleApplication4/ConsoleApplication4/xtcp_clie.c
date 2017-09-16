/*����TCPЭ��Ķ��߳������ҿͻ��˿�*/
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
	signal(SIGINT, sig_handler);        //���ź�2ע��Ϊ�Զ��庯���������˳�  
	printf("��������...\n");
	printf("�����ɹ����������û���:");
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
	/*�ͻ��˳���Ҫ�����������������⣬��Ҫ���շ�����������
	�������������ǲ��еģ��������������߳���д�����ٵ��߳��ж�*/
	pthread_t pid;
	pthread_create(&pid, 0, task, 0);
	char msg[1024] = {};
	while (1) {
		scanf("%s", msg);
		write(sockfd, msg, strlen(msg));
		/*����ѻ��������*/
		memset(msg, 0, strlen(msg));
	}
}

void init() {
	/*����ͷ������˲��*/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("socket error");
		exit(-1);
	}
	/*����ͨ�ŵ�ַ*/
	struct sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(PORT);
	inet_pton(AF_INET, IP, &servAddr.sin_addr.s_addr);
	/*���ӷ�����*/
	if (connect(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
		perror("connect error");
		exit(1);
	}
	printf("���ӷ������ɹ���\n");
}

/*�̺߳��������ڶ����������͹���������*/
void* task(void* p) {
	while (1) {
		char buf[100] = {};
		if (read(sockfd, buf, sizeof(buf)) <= 0)
			return;
		printf("%s\n", buf);
		memset(buf, 0, sizeof(buf));
	}
}
