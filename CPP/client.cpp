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
    int check; //-1 means check 0 means failed 1 means hash correct
};

void populateAddress(sockaddr_in &, const int);
bool process(char*);


int main(int argc, char *argv[])
{
    int clientCount = std::stoi(argv[1]);
    int client;
    printf("Client No: ");
    scanf(" %d", &client);
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in saddr;
    int pno;
    printf("Port No: ");
    scanf(" %d", &pno);
    populateAddress(saddr, pno);
    int len = sizeof(saddr);
    connect(fd, (sockaddr*)&saddr, len);
    Hash ownHash, prevHash;
    printf("Fill Hash:\n");
    printf("hash: ");
    scanf(" %s", ownHash.hash);
    ownHash.check = -1;
    if(client == clientCount-1) ownHash.destination = 0;
    else ownHash.destination = client+1;
    while(1)
    {
        if(client == 0)
        {
            send(fd, &ownHash, sizeof(Hash), 0);
            printf("Hash sent\n");
            recv(fd, &prevHash, sizeof(Hash), 0);
            prevHash.check = process(prevHash.hash);
            prevHash.destination = clientCount-1;
            send(fd, &prevHash, sizeof(Hash), 0);
        }
        else
        {
            recv(fd, &prevHash, sizeof(Hash), 0);
            printf("%s\n", prevHash.hash);
            send(fd, &ownHash, sizeof(Hash), 0);
            prevHash.check = process(prevHash.hash);
            prevHash.destination = client-1;
            send(fd, &prevHash, sizeof(Hash), 0);
        }
    }
    return 0;
}

void populateAddress(sockaddr_in &addr, const int pno)
{
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(pno);
}

bool process(char *hash)
{
    return true;
}