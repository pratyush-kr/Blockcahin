/*
    TCP Server for exchanging hash keys
    around clients
*/

#include<iostream>
#include<cstring>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

struct Hash
{
    int destination;
    char hash[255];
    int check; //-1 means check 0 means failed 1 means hash checked
};

void populateAddress(sockaddr_in &addr, const int);

int main(int argc, char *argv[])
{
    int n;
    printf("Number of Clients: ");
    n = argc-1;
    printf("%d\n", n);
    int id[n];
    char buffer[255];
    sockaddr_in saddr, caddr;
    int pno;
    printf("Port No: ");
    scanf(" %d", &pno);
    populateAddress(saddr, pno);
    populateAddress(caddr, pno);
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int len = sizeof(saddr);
    if(bind(fd, (sockaddr*)&saddr, (socklen_t)len) < 0)
    {
        printf("Bind Failed\n");
        close(fd);
        exit(-1);
    }
    listen(fd, n);
    for(int i=0; i<n; i++)
    {
        id[i] = accept(fd, (sockaddr*)&caddr, (socklen_t*)&len);
        printf("Client %d accepted\n", i+1);
    }
    int i=0;
    Hash h[n];
    while(1)
    {
        for(int j=0; j<n; j++)
            recv(id[j], &h[j], sizeof(Hash), 0);
        printf("Hashes Recieved\n");
        for(int j=0; j<n; j++)
            send(id[h[j].destination], &h[j], sizeof(Hash), 0);
    }
    return 0;
}

void populateAddress(sockaddr_in &addr, const int pno)
{
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(pno);
}