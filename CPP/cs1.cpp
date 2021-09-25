#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<cstring>

void sendFront(int id, char buffer[]);
char* recvFromBack(int id);
bool process(char sha256[]);
void response();
void populate(sockaddr_in &addr, int pno);

void bindfd(int fd, sockaddr_in *saddr, int len, int pno)
{
    if(bind(fd, (sockaddr*)saddr, len) < 0)
    {
        printf("Port Busy Trying another Port...\n");
        close(fd);
        exit(-1);
    }
}

void populate(sockaddr_in &addr, int pno)
{
    addr.sin_family = AF_INET;
    addr.sin_port = htons(pno);
    addr.sin_addr.s_addr = INADDR_ANY;
}

int main(int argc, char *argv[])
{
    char msg[255];
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in saddr, caddr;
    int Spno = std::stoi(argv[1]); //Server Port NO
    int Cpno = std::stoi(argv[2]); //Client Port No
    populate(saddr, Spno);
    populate(caddr, Cpno);
    int len = sizeof(saddr);
    bindfd(sfd, &saddr, len, Spno);
    listen(sfd, 2);
    int id = accept(cfd, (sockaddr*)&caddr,(socklen_t*)&len);
    sendFront(sfd, msg);
    char sha256[255];
    strcpy(sha256, recvFromBack(cfd));
    process(sha256);
    //response();
    close(sfd);
    close(cfd);
    return 0;
}

void sendFront(int id, char buffer[])
{
    send(id, buffer, strlen(buffer), 0);
}

char* recvFromBack(int id)
{
    char buffer[255];
    buffer[recv(id, buffer, sizeof(buffer), 0)] = '\0';
    return buffer;
}

bool process(char sha256[])
{
    //check(sha256)
    //return (sha256 == "prevHash")? true:false;
    return true;
}