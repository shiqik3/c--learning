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

	//����1:����socket
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("socket error");
		exit(1);
	}

	//����2:����recvfrom��sendto�Ⱥ����ͷ����˫��ͨ��
	struct sockaddr_in servAddr;	//��װ�������ĵ�ַ��Ϣ
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;	//ipv4
	servAddr.sin_port = htons(atoi(argv[2]));	//�˿�
	inet_pton(AF_INET, argv[1], &servAddr.sin_addr.s_addr);

	//��UDP�ܷ����connect������������ӣ�
	//TCP�еذ�����connect������������֣�������˫��������
	//��UDP�е�����connect���Ժ����ֱ��ʹ��send������ֻ��sendto��������Ϣ���Է���
	//���⣬����һ���ô�������Ϊsock��¼�˿ͻ��˵�ip��ʹ�ø�sockfd����ֻ����ָ����������������Ϣ��������
	//���ܷ��������������ط���������Ϣ��
	if (connect(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
		perror("connect error");
		exit(1);
	}

	char buff[1024] = "hello world";
	//��������������ݱ���
	if ((sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr*)&servAddr, sizeof(servAddr))) < 0) {
		perror("sendto error");
		exit(1);
	}
	else {
		//���ܷ������˵����ݱ���
		memset(buff, 0, sizeof(buff));
		size_t size;

		//1.Ϊʲôrecv��û��ָ����������ַ��ȴ���Է��ͳɹ���
		//��Ϊ���֮ǰ��sendto���ͳɹ�����sockfd�ｫ����ͨѶ˫������Ϣ������Ϳ���ֱ��ʹ�����sockfd��ͨ��
		//2.Ϊʲô����Ҫ�ж�recv�ķ���ֵΪ0����0��ʾ�Է��Ѿ��ر����ӣ�
		//��ΪUDP�������ӵ�ͨ�ţ�ͨ��˫����û�н������ӵģ����ݱ�������·���Ժ��ͷ��Ϳ��Թرգ�������ﲻ���ж��Ƿ�Ϊ0
		if ((size = recv(sockfd, buff, sizeof(buff), 0)) < 0) {
			perror("recv error");
			exit(1);
		}
		else {
			printf("%s", buff);
		}
	}
}
