/* Use standard echo server; baseline measurements for nonblocking version */
#include  "str_cli.h"

int
main(int argc, char **argv)
{
  int         sockfd;
  struct sockaddr_in  servaddr;

  printf ("first\n");
  printf ("first\n");
  printf ("first %d\n", argc);
  if (argc != 2)
  {

    printf("usage: tcpcli <IPaddress>\n");
    exit(1);

  }


  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(9877);
  inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

  connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

  str_cli(stdin, sockfd);   /* do it all */

  exit(0);
}
