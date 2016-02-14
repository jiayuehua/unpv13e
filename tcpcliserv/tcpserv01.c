#include  "unp.h"
enum {
  LEN = 10
};
int
main(int argc, char **argv)
{
  int         listenfd, connfd;
  pid_t       childpid;
  socklen_t     clilen;
  struct sockaddr_in  cliaddr, servaddr;

  listenfd = Socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family      = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port        = htons(SERV_PORT);

  Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

  Listen(listenfd, LISTENQ);

  for ( ; ; ) {
    clilen = sizeof(cliaddr);
Again2:
    connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);

    printf ("Accept\n");
  ssize_t   n = 0;
  char    buf[MAXLINE+1];

again:
  while ( (n = read(connfd, buf, LEN)) > 0)
  {

    Writen(connfd, buf, n);
    buf[n+1] = 0;
    printf ("%d: buf: %s\n", n , buf);
    Close(connfd);      /* parent closes connected socket */
    printf ("close connfd\n");
    goto Again2;

  }

  if (n < 0 && errno == EINTR)
    goto again;
  else if (n < 0)
    err_sys("str_echo: read error");

    printf ("close connfd");
    Close(connfd);      /* parent closes connected socket */
    //Close(listenfd);      /* parent closes connected socket */
  }
}
