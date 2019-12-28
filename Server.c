#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  
  int socket_fd, cc, fsize;
  //address and port of server/client
  struct sockaddr_in  s_in, from;
  //sturct represting massge
  struct { char head; char body[256]; char tail;} msg;
  //open new socket with ipv3 and udp protocol
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);
 //reset the address and port of client
  bzero((char *) &s_in, sizeof(s_in));  /* They say you must do this    */
  //changes the type  ipv4/6 of server to ipv4 
  s_in.sin_family = (short)AF_INET;
  //init the server internet address and casting from regular address to network
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);
  //init the server port and casting from regular adrress ip to network address
  s_in.sin_port = htons((u_short)0x3331);
   bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));
 
  
  
 
  //bind connect address and port with socket
 
 //^^socket return,pointer to sockaddr , len of the sturct


    //the size of address and port of server
    fsize = sizeof(from);
    //recive massge from the client
    cc = recvfrom(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,&fsize);
    printf("Got data ::%c%s%c\n",msg.head, msg.body,msg.tail);
    
    //send to router back

  sendto(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,
                  sizeof(from));

   
  return 0;
}