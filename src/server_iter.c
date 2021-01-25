#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys.types.h>
#include <netinet/in.h>

void error_handling(char* message)

int main()
{
	int serv_sock;
	int clnt_sock;
	char port[10] = "9190";
	char msg[] = "From Server\n";

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1)
		error_handling("Socket errror");

	memset(&serv_sock, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INARRY_ANY);
	serv_addr.sin_port = htons(atoi(port));

	if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("Bind error");

	if (listen(serv_sock, 5) == -1)
		error_handling("Listen error");

	clnt_addr_size = sizeof(clnt_addr);

	while (1)
	{
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
		if (clnt_sock == -1)
		{
			error_handling("Accept error");
			break;
		}
		sleep(7000);
		write(clnt_sock, msg, sizeof(msg));
		printf("%d\n", ntohl(clnt_addr.sin.s_addr));
		close(clnt_sock);
	}

	close(serv_sock);

	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}