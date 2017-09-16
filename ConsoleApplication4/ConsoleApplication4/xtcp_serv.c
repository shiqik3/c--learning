#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<signal.h>
#include<pthread.h>

int sockfd;
int PORT = 8888;          //ͨ�Ŷ˿ں�
int bStop = 0;
typedef struct client1 {
	char name[20];
	int sock;
} Client;
Client client[100];         //��ͬʱ����100���ͻ�����  
int size = 0;               //��ŵ�ǰ���߿ͻ�����Ŀ  

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
	printf("��������ʼ����ϣ�\n");
}

void start() {
	printf("��������������...\n");
	printf("�����������ɹ�!\n");
	printf("��������....\n");
	while (!bStop) {
		/*�������������Ŀͻ���ͨ�ŵ�ַ*/
		struct sockaddr_in client_Addr;
		socklen_t client_len = sizeof(client_Addr);
		int fd = accept(sockfd, (struct sockaddr*)&client_Addr, &client_len);
		if (fd < 0) {
			perror("accept error");
			continue;
		}
		/*Ϊ���������Ŀͻ��˿����µ��߳�*/
		client[size].sock = fd;
		pthread_t p_id;
		pthread_create(&p_id, 0, task, &fd);
	}
}
void closeServe() {
	printf("���������ڹر�...\n");
	close(sockfd);
	printf("�������رճɹ�!\n");
	exit(0);
}

void* task(void* p) {
	int socktemp = *(int*)p;
	char name[20] = {};      //���ڽ����û���  
	char buf[1024] = {};
	int i, temp;
	if (read(client[size].sock, name, sizeof(name))>0)
		strcpy(client[size].name, name);
	temp = size;
	size++;
	/*�״ν��������Ҵ�ӡ������ʾ*/
	char remind[100] = {};
	sprintf(remind, "��ӭ%s���뱾������..", client[size - 1].name);
	sendMsgToAll(remind);
	while (1) {
		if (read(socktemp, buf, sizeof(buf)) <= 0) {
			char remind1[100] = {};
			sprintf(remind1, "%s�˳�������", client[temp].name);
			sendMsgToAll(remind1);
			for (i = 0; i<size; i++)
				if (client[i].sock == socktemp) {
					client[i].sock = 0;
				}
			return;//�����߳�  
		}
		/*����Ϣ���͸��������Լ��������������ߵĿͻ���*/
		char msg[100] = {};
		sprintf(msg, "%s:%s", client[temp].name, buf);
		sendMsgToAll(msg);
		memset(buf, 0, strlen(buf));
	}
}



int main(int argc,char* argv[]) {
	//��ctrl-cʱ��ֹ����˳���
	signal(SIGINT, sig_handler);
	init();
	start();
	closeServe();
	return 0;
}


