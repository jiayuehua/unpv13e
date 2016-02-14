#include  "unp.h"

void
str_echo(int sockfd)
{
  ssize_t   n;
  char    buf[MAXLINE+1];

again:
  while ( (n = read(sockfd, buf, MAXLINE)) > 0)
  {

    Writen(sockfd, buf, n);
    buf[n+1] = 0;
    printf ("%d: buf: %s", n , buf);

  }

  if (n < 0 && errno == EINTR)
    goto again;
  else if (n < 0)
    err_sys("str_echo: read error");
}
