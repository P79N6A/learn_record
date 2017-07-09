/*************************************************************************
  > File Name: server.cpp
  > Author: orientlu
  > Mail: lcdsdream@126.com
  > Created Time: Fri 07 Jul 2017 11:38:04 PM PDT
 ************************************************************************/

#include<iostream>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <errno.h>
#include"message.pb.h"

using namespace std;

static int set_fd_non_blocking(int sfd)
{
	int flag;
	flag = fcntl(sfd, F_GETFL, 0);
	if (flag < 0) {
		perror("fcntl get");
		return -1;
	}

	flag |= O_NONBLOCK;
	if (fcntl(sfd, F_SETFL, flag) < 0) {
		perror("fcntl set");
		return -1;
	}
	return 0;
}

static int create_socket(char *port)
{
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int sfd;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM; //TCP
	hints.ai_flags = AI_PASSIVE;

	int flag;
	flag = getaddrinfo(NULL, port, &hints, &result);
	if (flag < 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(flag));
		return -1;
	}
	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (-1 == sfd)
			continue;
		if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0) {
			break;
		}
		close(sfd);
	}
	if (rp == NULL) {
		fprintf (stderr, "Could not bind\n");
		return -1;
	}

	freeaddrinfo (result);
	return sfd;
}

static const int MAXEVENTS = 256;

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("usage : %s prot\n", argv[0]);
	}
	char *str_port = argv[1];
	printf("- Server port : %s\n", str_port);

	int sfd = -1;
	sfd = create_socket(str_port);
	if (-1 == sfd)
		abort();
	if (set_fd_non_blocking(sfd) == -1)
		abort();


	int efd;
	struct epoll_event event;
	struct epoll_event events[MAXEVENTS];
	efd = epoll_create1(0);
	if (-1 == efd) {
		perror("epoll create error");
		abort();
	}
	event.data.fd = sfd;
	event.events = EPOLLIN | EPOLLET;
	if (epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &event) == -1) {
		perror("epoll ctl add error");
		abort();
	}

	listen(sfd, 20);

	while (1) {
		int evenet_cnt;
		evenet_cnt = epoll_wait(efd, events, MAXEVENTS, -1);

		for (int i = 0; i < evenet_cnt; ++i) {
			/*if ((events[i].events & EPOLLERR)
			  || (events[i].events & EPOLLHUP)
			  || !(events[i].events & EPOLLIN)
			  || !(events[i].events & EPOLLOUT)) {
			  fprintf (stderr, "epoll error\n");
			  close(events[i].data.fd);
			  continue;
			  } else */if (sfd == events[i].data.fd) {
				  //new connection
				  while (1) {
					  struct sockaddr in_addr;
					  socklen_t in_len;
					  int infd;
					  char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
					  in_len = sizeof in_addr;
					  infd = accept(sfd, &in_addr, &in_len);
					  if (-1 == infd) {
						  // processed all request
						  if (errno != EAGAIN && errno != EWOULDBLOCK) {
							  perror("connection error");
						  }
						  break;
					  }
					  if (getnameinfo(&in_addr, in_len,
								  hbuf, sizeof hbuf,
								  sbuf, sizeof sbuf,
								  NI_NUMERICHOST | NI_NUMERICSERV) == 0) {
						  printf("Accepted connection on descriptor %d "
								  "(host=%s, port=%s)\n", infd, hbuf, sbuf);
					  }
					  if (set_fd_non_blocking(infd) == -1)
						  abort();

					  // add epoll
					  event.data.fd = infd;
					  event.events = EPOLLIN | EPOLLET;
					  if (epoll_ctl(efd, EPOLL_CTL_ADD, infd, &event) == -1) {
						  perror("epoll ctl add new connection error");
						  abort();
					  }
				  }
			  } else if (events[i].events & EPOLLIN) {
				  /* We have data on the fd waiting to be read. Read and
				     display it. We must read whatever data is available
				     completely, as we are running in edge-triggered mode
				     and won't get a notification again for the same
				     data.
				     */

				  int done = 0;
				  while (1) {
					  ssize_t count;
					  char buf[102400];
					  count = read(events[i].data.fd, buf, sizeof buf);
					  if (count == -1) {
						  if (errno != EAGAIN) {
							  perror("read error");
							  done = 1;
						  }
						  // read finish or error
						  break;
					  }
					  if (count == 0) {
						  // disconnection
						  done = 1;
						  break;
					  }

					  TestMessage message;
					  message.ParseFromArray(buf, count);
					  printf("ID = %ld, message = \"%s\"\n",
							  message.id(), message.message().c_str());

					  /*if (write(1, buf, count) == -1) {
						  perror("stdout write error");
						  abort();
					  }
					  printf("\n");*/
				  }
				  // 异步， 读取后设置该socket 为epoll
				  // write，在下一个循环处理发送
				  if (done) {
					  printf ("Closed connection on descriptor %d\n",
							  events[i].data.fd);

					  /* Closing the descriptor will make epoll remove it
					     from the set of descriptors which are monitored. */
					  close (events[i].data.fd);
				  }
			  } else if (events[i].events & EPOLLOUT) {
			  } else {
			  }
		}
	}
	close (sfd);
	return 0;
}
