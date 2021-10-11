#include<iostream>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>

using namespace std;

struct Block
{
    int source;
    int destination;
    int ID;
    string prevHash;
    string data;
    int validate; // -1 => validate this hash 0 => validate failed 1 => validated
    string ownHash;
    Block(char ID, string prevHash, string data, string ownHash)
    {
        this->ID = ID;
        this->prevHash = prevHash;
        this->ownHash = ownHash;
        this->data = data;
    }
    Block(){}
};

void populate(sockaddr_in &, const int);

int main(int argc, char *argv[])
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0) {perror("Socket Creation Failed\n");}
    sockaddr_in saddr, caddr;
    int pno = stoi(argv[1]);
    populate(saddr, pno);
    return 0;
}

void populate(sockaddr_in &addr, const int pno)
{
    addr.sin_family = AF_INET;
    addr.sin_port = htons(pno);
    addr.sin_addr.s_addr = INADDR_ANY;
}