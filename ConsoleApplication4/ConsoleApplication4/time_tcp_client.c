#include<netdb.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

int main(int argc, char* argv[]) {
	if (argc < 3) {
		perror("usage is: %s ip port", argv[0]);
		exit(1);
	}

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		perror("socket error");
	}

	struct sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(atoi(argv[2]));
	inet.pton(AF_INET, argv[1], &servAddr.sin_addr.s_addr);

	if (connect(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
		perror("connect error");
		exit(1);
	}

	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	size_t size;
	if (size = read(sockfd, buffer, sizeof(buffer)) < 0) {
		perror("read error");
		exit(1);
	}

	if (write(STDOUT_FILENO, buffer, size) != size) {
		perror("write error");
		exit(1);
	}

	close(sockfd);
}