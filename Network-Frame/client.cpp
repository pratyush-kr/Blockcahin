#include<iostream>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>

using namespace std;

void populate(sockaddr_in &, const int);

int main(int argc, char *argv[])
{
    int pno = stoi(argv[1]);
    sockaddr_in saddr;
    populate(saddr, pno);
    int len = sizeof(saddr);
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0) {printf("Socket Creation Failed\n");}
    if(bind(fd, (sockaddr*)&saddr, len) < 0) {perror("Bind Failed\n");} 
    return 0;
}

void populate(sockaddr_in &addr, const int pno)
{
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(pno);
}