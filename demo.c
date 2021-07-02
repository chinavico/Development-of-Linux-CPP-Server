#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <poll.h>
#include <sys/epoll.h>

int play_select()
{
	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(STDIN_FILENO, &rfds);
 
	fd_set wfds;
	FD_ZERO(&wfds);
	FD_SET(STDOUT_FILENO, &wfds);
	
	struct timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	int retval = select(STDOUT_FILENO + 1, &rfds, &wfds, NULL, &tv);
	if (retval < 0)
	{
		printf("select error\n");
		return -1;
	}
 
	if (retval == 0)
	{
		printf("time out\n");
		return -1;
	}
  
	// 需要对所有句柄进行轮询遍历
	if(FD_ISSET(STDIN_FILENO, &rfds))
	{
		printf("can read\n");
	}
 
	if(FD_ISSET(STDOUT_FILENO, &wfds))
	{
		printf("can write\n");
	}
 
	return 0;	   
}
 
 
int play_poll()
{
	pollfd pfd[2];
	int nfds = 2;
	
	pfd[0].fd = STDIN_FILENO;
	pfd[0].events = POLLIN;
 
	pfd[1].fd = STDOUT_FILENO;
	pfd[1].events = POLLOUT;
 
	int timeout_ms = 5000; // 5000毫秒
	int retval = poll(pfd, nfds, timeout_ms);
	if (retval < 0)
	{
		printf("poll error\n");
		return -1;
	}
 
	if (retval == 0)
	{
		printf("time out\n");
		return -1;
	}
  
	// 需要对所有句柄进行轮询遍历
	if(pfd[0].revents & POLLIN)
	{
		printf("can read\n");
	}
 
	if(pfd[1].revents & POLLOUT)
	{
		printf("can write\n");
	}
 
	return 0;
}
 
 
 
int play_epoll()
{
	epoll_event evReq[10];
	epoll_event evRsp[10];
 
	evReq[0].data.fd = STDIN_FILENO;
	evReq[0].events = EPOLLIN;
 
	evReq[1].data.fd = STDOUT_FILENO;
	evReq[1].events = EPOLLOUT;
 
	// 创建管理句柄
	int epollFd = epoll_create(10);
 
	// 添加以便于管理
	epoll_ctl(epollFd, EPOLL_CTL_ADD, evReq[0].data.fd, evReq);
	epoll_ctl(epollFd, EPOLL_CTL_ADD, evReq[1].data.fd, evReq + 1);
 
	int timeout_ms = 5000; // 5000毫秒
	int retval = epoll_wait(epollFd, evRsp, 10, timeout_ms);
	if (retval < 0)
	{
		printf("epoll error\n");
		close(epollFd);
		return -1;
	}
 
	if (retval == 0)
	{
		printf("time out\n");
		close(epollFd);
		return -1;
	}
 
	// 无需遍历所有句柄，只需直接取结果就行，如下evRsp[i]对应的句柄一定是"就绪的(active)"
	for (int i = 0; i < retval; ++i) 
	{
		printf("active fd is %d\n", evRsp[i].data.fd);
	}
	
	close(epollFd);
	return 0;
}
 
 
int main()
{
	play_select();
	play_poll();
	play_epoll();
 
	return 0;
}