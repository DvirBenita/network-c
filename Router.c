#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
 

void printsin(struct sockaddr_in *s, char *str1, char *str2) {
  printf("%s\n", str1);
  printf("%s: ", str2);
  printf("%s= %s, %s= %d", "ip", inet_ntoa(s->sin_addr), "port", s->sin_port);
  printf("\n");
}

 double r2()
{
    return (double)rand() / (double)RAND_MAX ;
}
int main(int argc, char *argv[])
{
  double b  = 0.3;
  int socket_fd, socket_fd1; //fd- client , fd1-client_a
  struct sockaddr_in  s_in, from, s_in1,from1;//s_in- clientc,s_in1-client_a
  struct { char head; char body[256]; char tail;} msg;
   struct hostent *hostptr;
   hostptr = gethostbyname("localhost");
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
  bzero((char *) &s_in, sizeof(s_in));
  s_in.sin_family = (short)AF_INET;
bcopy(hostptr->h_addr, (char *)&s_in.sin_addr,hostptr->h_length);
  s_in.sin_port = htons((u_short)0x3333); // same port like client_c
//init client a socket
 socket_fd1 = socket (AF_INET, SOCK_DGRAM, 0);
  bzero((char *) &s_in1, sizeof(s_in1));
  s_in1.sin_family = (short)AF_INET;
  bcopy(hostptr->h_addr, (char *)&s_in1.sin_addr,hostptr->h_length);
  s_in1.sin_port = htons((u_short)0x3332); // same port like client_a
  fflush(stdout);//clean standart input
  bind(socket_fd,(struct sockaddr *)&s_in, sizeof(s_in));
  bind(socket_fd1,(struct sockaddr *)&s_in1, sizeof(s_in1));

    int fsize = sizeof(from);
    //recive massge from the client
    int cc = recvfrom(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,&fsize);
    printf("%s%c%s%c","got: ",msg.head,msg.body,msg.tail);
    printsin((struct sockaddr*) &from, "recv_udp: ", "Packet from:");
     //send to client a the message same code from client_c
    int socket_fd2  ;
  struct sockaddr_in  dest;
  struct hostent *hostptr1;
  struct { char head; char body[256]; char tail; } msgbuf;//change body to char[100]

  socket_fd2 = socket (AF_INET, SOCK_DGRAM, 0);
  bzero((char *) &dest, sizeof(dest)); /* They say you must do this */
  hostptr1 = gethostbyname("localhost");
  dest.sin_family = (short) AF_INET;
  bcopy(hostptr1->h_addr, (char *)&dest.sin_addr,hostptr1->h_length);
  dest.sin_port = htons((u_short)0x3331);//port that client a connected
sendto(socket_fd2,&msg,sizeof(msg),0,(struct sockaddr *)&dest,
                  sizeof(dest));
    printf("message sent wait for response \n");
    //recive massge from the client
    int c1 = recvfrom(socket_fd2,&msg,sizeof(msg),0,(struct sockaddr *)&from1,&fsize);
    printf("%s%c%s%c","got: ",msg.head,msg.body,msg.tail);
    printsin((struct sockaddr*) &from1, "recv_udp: ", "Packet from:");
    double num = r2();
    printf("Random number %f",num);
    if(num>b)
    {
        //change dest port
        printf("send %s \n ",msg.body);
        sendto(socket_fd,&msg.body,sizeof(msg.body),0,(struct sockaddr *)&from,
                  sizeof(from));
    }
    else
    {
      printf("message dropped");
    }
    


}