#include  "str_cli.h"

enum{
  MAXLINE = 128
};

  void
str_cli(FILE *fp, int sockfd)
{
  int     maxfdp1;
  fd_set    rset;
  fd_set    wset;
  char    sendline[MAXLINE] = "nihao";
  char     recvline[MAXLINE];

  printf ("1\n");
  FD_ZERO(&rset);
  FD_ZERO(&wset);
  for ( ; ; ) {
    FD_SET(sockfd, &rset);
    FD_SET(sockfd, &wset);
    maxfdp1 =  sockfd + 1;
    printf ("1.1\n");
    select(maxfdp1, &rset, &wset, NULL, NULL);

    printf ("2\n");
    if (FD_ISSET(sockfd, &rset)) {  /* socket is readable */
      printf ("3\n");
      if (read(sockfd, recvline, MAXLINE) == 0)
        printf("str_cli: server terminated prematurely");
      fputs(recvline, stdout);
      printf ("4");
    }

    if (FD_ISSET(sockfd, &wset)) {  /* input is readable */
      printf ("7\n");
      write(sockfd, sendline, strlen(sendline));
    }
  }
}
