#include  "unp.h"
#include  "msg.pb.h"
enum{
  PBVERSIONINDEX,
  PBTYPEINDEX,
  PBLENGTHINDEX
};
enum {
  RingActionCommandType = 5,
};
enum {
  PBVERSION = 1,
};
void
mydg_echo(int sfd, SA *pcliaddr, socklen_t clilen)
{
  int     n;
  socklen_t len;
  char    mesg[1000];
  char    mesg2[1000];
  msg::Actions actions;
  msg::ActionL4 actionl4; 

  char ipStr[20] = "192.168.178.252";
  int dstip  ;
  inet_pton(AF_INET, ipStr, &dstip);
  struct timeval tv, tv1;
  gettimeofday(&tv, 0);
  tv.tv_sec += 20;
  msg::ActionL4 *pL4 =  actions.add_actionl4s();
  pL4->set_ip(dstip);
  pL4->set_expire(tv.tv_sec+ 360);

  msg::ActionL7 *pL7 =  actions.add_actionl7s();
  pL7->set_ip(dstip);
  pL7->set_expire(tv.tv_sec+ 180);

  len = 4+ actions.ByteSize();
  actions.SerializeToArray(mesg+4, len -4);
  mesg[PBVERSIONINDEX] = PBVERSION;
  mesg[PBTYPEINDEX] = RingActionCommandType ;
  mesg[PBLENGTHINDEX] =htons( len -4 );



  int var = Fcntl(sfd, F_GETFL, 0);
  Fcntl(sfd, F_SETFL, var | O_NONBLOCK);

  for ( ; ; ) {
    n = recvfrom(sfd, mesg2, MAXLINE, 0, pcliaddr, &clilen);
    if (n == -1)
    {
      if (errno == EAGAIN)
      {
        /*err_msg( "EAGAIN");*/
      }
      else
      {

        /*err_msg( "recvfrom fail");*/
      }

    }
    if (n>0)
    {
      err_msg("Recv len: %d", n);
    }

    gettimeofday(&tv1, 0);

    if (tv.tv_sec != tv1.tv_sec)
    {
      n = sendto(sfd, mesg, len, 0, pcliaddr, clilen);
      if (n == -1)
      {
        if (errno == EAGAIN)
        {
          /*err_msg( "sendto EAGAIN");*/
        }
        else
        {
          /*err_msg( "sendto fail");*/
        }

      }
      else {

          /*err_msg( "sendto Success!***********");*/

      }
    }
  }
}
char * serverPath =   "/tmp/mockagent.sock";
char * clientPath = "/tmp/tpcore.sock";
int
main(int argc, char **argv)
{
  int         sockfd;
  struct sockaddr_un  servaddr, cliaddr;

  sockfd = Socket(AF_LOCAL, SOCK_DGRAM, 0);

  unlink(serverPath);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sun_family = AF_LOCAL;
  strcpy(servaddr.sun_path, serverPath);
  Bind(sockfd, (SA *) &servaddr, sizeof(servaddr));

  bzero(&cliaddr, sizeof(cliaddr));
  cliaddr.sun_family = AF_LOCAL;
  strcpy(cliaddr.sun_path, clientPath);
  /*
  *Bind(sockfd, (SA *) &cliaddr, sizeof(cliaddr));
  */

  mydg_echo(sockfd, (SA *) &cliaddr, sizeof(cliaddr));
}
