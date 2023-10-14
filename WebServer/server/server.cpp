#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <pthread.h>
#include <sys/syscall.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

const int SERVER_PORT = 28000;
const int MAXLINE = 65536;
char* bufferToSend;
std::string readBuffer("");
char receiveline[MAXLINE];
int socket_OK=0;

void sigpipe_handler(int a)
{
    printf("SIGPIPE caught\n");
    socket_OK=0;
}

int accept_new_connection(int arg_listenSocket)
{
    struct sockaddr clientAddr;
    socklen_t clientAddrLen = MAXLINE;
    return accept(arg_listenSocket, &clientAddr, &clientAddrLen);
}

bool stopCondition(const std::string& strArg)
{
    const std::string stopSign = "**";
    if(strArg[strArg.size()-1] == stopSign[0] && strArg[strArg.size()-2] == stopSign[1])
    {
        return true;
    }
    else
    {
        return false;
    }
}

void handle_new_connection(int arg_fd)
{
    int nrOfBytesRead = 0;
    unsigned char buffer[10];
    FILE *ptr;

    while((nrOfBytesRead=read(arg_fd, receiveline, MAXLINE)) > 0)
    {
        readBuffer.append(receiveline, nrOfBytesRead);
        if(stopCondition(readBuffer))
        {
            readBuffer.erase(readBuffer.size()-2, 2);
            break;
        }
    }
    
    ptr = fopen(readBuffer.c_str(),"rb");  // r for read, b for binary

    if(ptr != NULL)
    {
        uint32_t size = 0;
        fseek(ptr, 0 , SEEK_END);
        size=ftell(ptr);
        fseek(ptr, 0, SEEK_SET);
        char* bufferToSend = new char[size];
        fread(bufferToSend, size, 1, ptr);                        
        fclose(ptr);

        std::cout << "File " << readBuffer << " has been read ! " << std::endl;
        readBuffer.clear();
        std::cout << "bufferToSend size : " << strlen(bufferToSend) << std::endl;
        
        int retCode = 0;
        int bytesSendSoFar = 0;
        while(bytesSendSoFar < size)
        {
            retCode = write(arg_fd, bufferToSend+bytesSendSoFar, size-bytesSendSoFar);
            if(retCode == -1)
            {
                std::cout << "[ERROR] Error at data transmission !" << std::endl;
                break;
            }
            bytesSendSoFar += retCode;
        }
        
        delete []bufferToSend;
    }
    else
    {
        std::cout<< "[ERROR] File " << readBuffer.c_str() << " is not opened ! " << std::endl;                        
    }
    
    close(arg_fd);

}

int main(int argc, char *argv[])
{
    int listenfd = 0;
    int receivefd = 0;
    int connfd = 0;
    struct sockaddr_in serveraddr;
    fd_set readfs;
    fd_set referenceSet;

    signal(SIGPIPE,sigpipe_handler);
    FD_ZERO(&readfs);
    FD_ZERO(&referenceSet);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd < 0)
        printf("Error at socket creating ! \n");

    

     bzero(&serveraddr , sizeof(serveraddr));
     serveraddr.sin_family = AF_INET;
     serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
     serveraddr.sin_port = htons(SERVER_PORT);

    if(bind(listenfd, (struct sockaddr*) &serveraddr, sizeof(serveraddr)) < 0)
        printf("Binding error !\n"); 

    if (listen(listenfd, 500) < 0)
        printf("Listen error ! \n");

    FD_SET(listenfd, &referenceSet);

    while(1)
    {   
        readfs = referenceSet;

        if(select(FD_SETSIZE, &readfs, NULL, NULL, NULL) < 0 )
        {
            perror("Select error \n");
        }

        printf("Message arrived \n");

        for(int i=0; i<FD_SETSIZE; i++)
        {
            if(FD_ISSET(i, &readfs))
            {
                printf("Socket %d found \n", i);
                if( i==listenfd)
                {
                    //Accept new connection
                    printf("Accept new connection \n");
                    int connfd = accept_new_connection(i);
                    printf("Adding new socket to set %d\n", connfd);
                    FD_SET(connfd, &referenceSet);
                }
                else
                {
                    handle_new_connection(i);
                    FD_CLR(i, &referenceSet);
                }
            }
        }
    }
        
}
