#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


int setup(char *serverip,int port){
    int fd;
    if((fd=socket(AF_INET,SOCK_DGRAM,0))<0){
        printf("%s %d\n",strerror(errno),__LINE__);
        exit(1);
    }
    struct sockaddr_in client_adress;
    client_adress.sin_port=htons(5200);
    client_adress.sin_addr.s_addr=inet_addr(INADDR_ANY);
    if(bind(fd,(struct sockaddr*)&client_adress,sizeof(client_adress))<0){
        printf("%s %d\n",strerror(errno),__LINE__);
        exit(1);
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_port=htons(port);
    serv_addr.sin_addr.s_addr=inet_addr(serverip);
    char buffer[255]={0,1,5};
    socklen_t serv_addr_size = sizeof(serv_addr);
    sendto(fd, buffer, 3, 0,(struct sockaddr*)&serv_addr,serv_addr_size);
    recvfrom(fd,buffer,2,0,(struct sockaddr*)&serv_addr,&serv_addr_size);
    buffer[255]=0;
    printf("%s \n",buffer);
    

    return 0;


}