#include  "unp.h"

void
dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen)
{
  int     n;
  socklen_t len;
  char    mesg[10];

  for ( ; ; ) {
    len = clilen;
    n = Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
    err_msg("Recv len: %d", n);

//    Sendto(sockfd, mesg, n, 0, pcliaddr, len);
  }
}
