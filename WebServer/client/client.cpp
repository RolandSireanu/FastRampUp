#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <fstream>
// #include <netinet/in.h>

const int SERVER_PORT = 28000;
const int MAXLINE = 4096;

class Payload
{
    public:
        void addBytesToData(char* arg_data, uint32_t nrOfBytes)
        {
            data.append(arg_data, nrOfBytes);
        }

        void showMe()
        {
            // for(auto& ch : data)
            // {   
            //     printf("%hhx\t", ch);
            // }  

            // printf("%hhx\t", data[0]);
        }

        void showNrOfBytes()
        {
            printf("\nNumber of bytes in payload %d\n", data.size());
        }

        void dumpInFile(std::string path)
        {
            std::ofstream output(path, std::ios::out | std::ios::binary | std::ios::ate);
            output << data;
            output.close();
        }

    private:
        std::string data;

};

Payload payload;

int main(int argc, char *argv[])
{
    struct sockaddr_in serverAddr;
    int sockfd = 0;
    char sendline[MAXLINE];
    char receiveline [MAXLINE];

    
    bzero(&serverAddr, sizeof(serverAddr));
    
    // AF_INET = internet socket (Address family)
    // SOCK_STREAM = stream socket (stream sockets or datagram sockets)
    // 0 = Use tcp
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(sockfd < 0)
        printf("Error at socket creating ! \n");
    else
        printf("Socket has been created !\n");

    //AF_INET = this is an internet address
    serverAddr.sin_family = AF_INET;
    //Abstraction over byte order. If two computers use different byte order they are still
    //able to communicate
    serverAddr.sin_port = htons(SERVER_PORT);

    if(inet_pton(AF_INET, argv[1], &serverAddr.sin_addr) < 0)
        printf("Error at address translation ! \n");

    if(connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
        printf("Error at connecting !");

    // ========== Send the init message ===============
    sprintf(sendline, "%s", "/tmp/file**");
    printf("I will send req : %s of size : %d \n",sendline, strlen(sendline));
    if(write(sockfd, sendline, strlen(sendline)) != strlen(sendline))
        printf("Error at send request ! \n");
    else
        printf("Request has been send ! \n");

    int n=1;
    int totalNrOfBytes = 0;
    char byte[MAXLINE];
    memset(byte, 0, MAXLINE-1);

    while(n > 0)
    {
        n = read(sockfd, &byte, MAXLINE);
        if(n > 0)
        {
            payload.addBytesToData(byte, n);
        }
        totalNrOfBytes += n;
    }

    printf("I have read %d bytes \n", totalNrOfBytes);

    // payload.showMe();
    // payload.showNrOfBytes();
    payload.dumpInFile(std::string(argv[2]));
    close(sockfd);

    return 0;
}