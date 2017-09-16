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

//����ͻ��˵���Ϣ
void out_addr(struct sockaddr_in* addr){
	char ip[16];
	int port = 0;
	memset(ip, 0, sizeof(ip));
	inet_ntop(AF_INET, &addr->sin_addr.s_addr, ip, sizeof(ip));
	port = ntohs(addr->sin_port);
	printf("client: %s(%d)\n", ip, port);
}

//��ͻ��˾���ͨ��
void do_service() {
	struct  sockaddr_in cliAddr;
	socklen_t len = sizeof(cliAddr);
	char buff[1024];
	memset(buff, 0, sizeof(buff));

	//���ܿͻ��˵����ݱ���
	//ʹ��recvfrom��������recv��������ҪĿ����Ϊ�˻�ȡ�ͻ�����Ϣ
	if (recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&cliAddr, &len) < 0) {
		perror("recvfrom error");
	}
	else {
		out_addr(&cliAddr);
		printf("client send info: %s\n", buff);

		//��ͻ��˷������ݱ���
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

	//ע��ctrl+c �źŴ�����
	if (signal(SIGINT,sig_handler) == SIG_ERR) {
		perror("signal sigint error");
		exit(1);
	}

	//����1������socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);    //SOCK_DGRAMΪUDPЭ��
	if (sockfd < 0) {
		perror("socket error");
		exit(1);
	}

	//����socket�����ѡ��
	int ret;
	int opt = 1;    //1��ʾ������ѡ��
	//����Ϊ������ʹ�ö˿ڣ�ÿ�������ö˿�ʱ��ԭ���Ըö˿�ʹ�ý�ʧЧ
	if ((ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) < 0) {
		perror("setsockopt error");
		exit(1);
	}

	//����2: ����bind������socket�͵�ַ���а�
	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;    //ipv4
	servAddr.sin_port = htons(atoi(argv[1]));    //port
	servAddr.sin_addr.s_addr = INADDR_ANY;    //ip
	if (bind(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
		perror("bind error");
		exit(1);
	}

	//����3:��ͻ��˽���˫�������ͨ�ţ�
	while (1) {
		do_service();
	}

	return 0;
}
