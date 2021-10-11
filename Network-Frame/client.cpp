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
int validate(Block &A, const Block &B);

int main(int argc, char *argv[])
{
    int pno = stoi(argv[1]);
    sockaddr_in saddr;
    populate(saddr, pno);
    int len = sizeof(saddr);
    int fd = socket(AF_INET, SOCK_STREAM, 0); //creating a socket
    if(fd < 0) {perror("Socket Creation Failed\n");}
    //bind is handeled by OS
    if(connect(fd, (sockaddr*)&saddr, len) < 0) {perror("Connection Failed\n");}
    char ID;
    string prevHash, ownHash, data;
    cout<<"ID: ";
    cin>>ID;
    cout<<"PrevHash: ";
    cin>>prevHash;
    cout<<"OwnHash: ";
    cin>>ownHash;
    cout<<"Data: ";
    cin>>data;
    Block B(ID, prevHash, data, ownHash);
    B.ID = stoi(argv[1]);
    B.destination = stoi(argv[2]);
    Block R;
    while(1)
    {
        B.source = B.ID;
        B.destination = B.ID + 1;
        cout<<"Sending Own Hash:\n";
        send(fd, &B, sizeof(Block), 0);
        cout<<"Recieving Previous Hash:\n";
        recv(fd, &R, sizeof(Block), 0);
        cout<<"Validating Previous Hash:\n";
        validate(R, B);
        cout<<"Sending Previous Hash to server: ";
    }
    return 0;
}

void populate(sockaddr_in &addr, const int pno)
{
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(pno);
}