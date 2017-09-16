#include<netdb.h>
#include<sys/socket.h>
#include<unist.h>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<time.h>
#include<signal.h>

int sockfd;
int bStop = 0;

void sig_handler(int signo) {
	if (signo == SIGINT) {
		bStop = 1;
		printf("service close");

		exit(1);
	}
}

void out_addr(struct sockaddr_in* addr) {
	int port = ntohs(addr->sin_port);
	char ip[16] = { 0 };
	inet.ntop(AF_INET, &addr.sin_addr.s_addr, ip, sizeof(ip));
	printf("Clinet: %s(%d) connected", ip, port);
}

void do_service(int fd) {
	long t = time(0);
	char* s = ctime(&t);
	size_t size = strlen(s) * sizeof(char);

	if (write(fd, s, size) != size) {
		perror("write error");
	}

}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("usage: %s is port", argv[0]);
		exit(1);
	}

	if (signal(SIGINT, sig_handler) == SIG_ERR) {
		perror("signal sigint error");

		exit(1);
	}

	//����1:����socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in servAddr;
	memset(servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = argv[1];
	servAddr.sin_addr.s_addr = INADDR_ANY;

	//����2:��socket�͵�ַ����bind��
	if (bind(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
		perror("bind error");
		exit(1);
	}

	//����3:����listen���ü���
	if (listen(sockfd, 10) < 0) {
		perror("listen error");
		exit(1);
	}

	//����4:����accept����������������л�ȡһ�����ӣ������µ�socket��ʶ��
	struct sockaddr_in* clientAddr;
	socklen_t clientAddr_len = sizeof(clientAddr);
	while (!bStop) {
		//���û�пͻ������ӣ����ô˺������������ֱ�����һ���ͻ�������
		int fd = accept(sockfd, (struct sockaddr*)&clientAddr, &clientAddr_len);
		if (fd < 0) {
			perror("accept error");
			continue;
		}

		//����ͻ�����Ϣ
		out_addr(&clientAddr);

		//����5������I/O�����Ϳͻ��˽���˫��ͨ��
		do_service(fd);

		//�ر�
		close(fd);
	}

	close(sockfd);

	return 0;
}