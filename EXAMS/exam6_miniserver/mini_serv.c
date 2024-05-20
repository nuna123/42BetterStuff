#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/select.h>
#include <stdio.h>


typedef struct client_s
{
	int id;
	char msg[200000];
} client_t;

t_clients clients[1024];
int serverfd = -1;
fd_set	  fds, active_fds;


void err(char *str)
{
	if (str)
		write(STDERR_FILENO, str, strlen(str));
	else
		write(STDERR_FILENO, "Fatal error", 11);
	write(STDERR_FILENO, "\n", 1);
	if (serverfd != -1)
		close (serverfd);
	exit (1);

}
void send_to_all (char *msg, int clients[128], int besides)
{
	for (int fd = 0; fd < 1024; fd++)
	{
		if (FD_ISSET(fd, &active_fds) && fd != besides)
			send(fd, msg, strlen(msg), 0);
	}
}


int main(int argc, char **argv)
{
	int connfd, len;
	struct sockaddr_in servaddr, cli;

	//get port
	if (argc == 1)
		err ("Wrong number of arguments");
	int port = atoi(argv[1]);


	//socket setup
	serverfd = socket(AF_INET, SOCK_STREAM, 0);
	if (serverfd == -1)
		err ("1");

	bzero(&servaddr, sizeof(servaddr));
	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(port);

	// Binding newly created socket to given IP and verification
	if ((bind(serverfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
		err ("2");
	if (listen(serverfd, 10) != 0)
		err ("3");

	//SET UP FDS
	FD_ZERO(&fds);
	FD_SET(serverfd, &fds);
	FD_ZERO(&active_fds);
	FD_SET(serverfd, &active_fds);

	int max_listen = serverfd + 1;
	int new_fd;
	char buf[120000];
	int recv_stat;

	char tmp_buf[5000];

	int next_id = 0;
	while (1)
	{
		fds = active_fds;
		if (select(max_listen, &fds, NULL, NULL, NULL) == -1)
			err ("OHNO");
		// at this point, the only fds set in the array are the ones that called an action
		for (int i = serverfd; i < max_listen; i++)
		{
			if (!FD_ISSET(i, &fds))
				continue;
			if (i == serverfd)	//new connection
			{
				new_fd = accept(serverfd, NULL, NULL);
				if (new_fd == -1)
					err ("ACCEPT ERR");
				FD_SET(new_fd, &active_fds);
				max_listen++;
				sprintf(tmp_buf, "server: client %d just arrived\n", next_id);
				send_to_all(tmp_buf, clients, -1);
				clients[new_fd].id = next_id++;
				clients[new_fd].msg[0] = 0;
			}
			else //action from client
			{
				recv_stat = recv (i, buf,sizeof (buf), 0);
				if (recv_stat <= 0)
				{
					sprintf(tmp_buf, "server: client %d just left\n", clients[i]);
					send_to_all(tmp_buf, clients, -1);
					close(i);
					FD_CLR(i, &active_fds);
					// clients[i] = -1;
				}
				else
				{

					buf[recv_stat] = 0;
					sprintf(tmp_buf, "client %d: %s", clients[i], buf);
					send_to_all(tmp_buf, clients, i);
					for (int i = 0, j = strlen (clients[fd].msg); i < recv_stat; i++, j++)
					{
						clients[fd].msg[j] = recv_buffer[i];
						if (clients[fd].msg[j] == '\n')
							{
								clients[fd].msg[j] = '\0';
								sprintf(send_buffer, "client %d: %s\n", clients[fd].id, clients[fd].msg);
								send_to_all(fd);
								bzero(clients[fd].msg, strlen(clients[fd].msg));
								j = -1;
							}
					}
				}
			}
		}

	}
	close (serverfd);
}