#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#define INFO 1
int handshake(char *serverip,int port);
void get_client_request_packet(char*buffer,struct sockaddr*addr);

int handshake(char *serverip,int port){
    int fd;
    if((fd=socket(AF_INET,SOCK_STREAM,0))<0){
        printf("%s %d\n",strerror(errno),__LINE__);
        exit(1);
    }

    int yes = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    struct sockaddr_in proxy_adress;
    proxy_adress.sin_family=AF_INET;
    proxy_adress.sin_port=htons(4145);
    proxy_adress.sin_addr.s_addr=inet_addr("199.187.210.54");
    

    struct sockaddr_in serv_addr;
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(port);
    serv_addr.sin_addr.s_addr=inet_addr(serverip);
    char buffer[255]={5,1,0};
    buffer[3]=0;
    if(connect(fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
        printf("%s %d\n",strerror(errno),__LINE__);
        exit(1);
    }
    printf("%d \n",(int)buffer[1]);
    
    socklen_t serv_addr_size = sizeof(serv_addr);
    sendto(fd, &buffer[0], 3, 0,(struct sockaddr*)&serv_addr,serv_addr_size);
    
    
    //sleep(2);
    recvfrom(fd,&buffer[0],3,0,(struct sockaddr*)&serv_addr,&serv_addr_size);
    //printf("%d\n",buffer[1]);
    get_client_request_packet(buffer,(struct sockaddr*)&proxy_adress);
    sendto(fd, &buffer[0], 10, 0,(struct sockaddr*)&serv_addr,serv_addr_size);
    recvfrom(fd,&buffer[0],10,0,(struct sockaddr*)&serv_addr,&serv_addr_size);
    printf("\n  %d",buffer[3]);
    
    memcpy(&serv_addr.sin_addr,&buffer[4],4);
    memcpy(&serv_addr.sin_port,&buffer[8],2);
    printf("\n %d \n",ntohs(serv_addr.sin_port));
    printf("%s",inet_ntoa(serv_addr.sin_addr));
    const char *http_get = "GET / HTTP/1.1\r\nHost: google.com\r\n\r\n";
    send(fd, http_get, strlen(http_get), 0);

    char response[4096];
    int n = recv(fd, response, sizeof(response) - 1, 0);
    if (n > 0) {
        response[n] = '\0';
        printf("Received:\n%s\n", response);
    }
        close(fd);
    exit(1);
    
    buffer[255]=0;
    printf("1 \n");
    printf("%d \n",(int)buffer[0]);
    exit(-1);

    return 0;


}

void get_client_request_packet(char*buffer,struct sockaddr*addr){
    struct sockaddr_in *addr_in=(struct sockaddr_in*)addr;
    buffer[0]=5;
    buffer[1]=1;
    buffer[2]=0;
    buffer[3]=1;
    // Target IP and port (for example)
    inet_pton(AF_INET, "142.250.201.206", &buffer[4]);
    uint16_t target_port = htons(80);
    memcpy(&buffer[8], &target_port, 2);
    
    //for(int i=0;i<10;i++)
    //printf("%d",(unsigned char)buffer[i]);
    return;
}
