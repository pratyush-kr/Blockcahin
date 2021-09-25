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
    //1st argv is port no and 2nd argv is number of clients
    int n;
    printf("Number of Clients: ");
    scanf(" %d", &n);
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
        recv(id[i%n], &h[i%n], sizeof(Hash), 0);
        printf("Hash Recieved\n");
        send(id[h[i%n].destination], &h, sizeof(h), 0);
        printf("Hash sent to client %d\n", h[i%n].destination);
        i++;
    }
    return 0;
}

void populateAddress(sockaddr_in &addr, const int pno)
{
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(pno);
}