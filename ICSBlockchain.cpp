/*
    Note Before running this cpp program please
    run server.py using python as hashes are created
    in the server side
*/

#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<cstring>
#include<vector>
#include<map>

using namespace std;

class Node
{
    private:
        string nodeID;
        string prevHash; //stores previous Data hash for center it is null
        string sentData; //data sent to the center for center it is null
        vector<string> *recvdDataHashes; //data cent to central node
        string hash; //sent data hash for local reference
    public:
        Node(vector<string> *data = NULL){recvdDataHashes = data;}
        void print()
        {
            for(auto data : *recvdDataHashes)
                cout<<data<<'\n';
        }
};

int main()
{
    //Client Side Socket
    sockaddr_in saddr;
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(1025);
    saddr.sin_addr.s_addr = INADDR_ANY;
    char hash[255];
    char str[255];

    //Now Working on Incomplete Circular Cycle Scope Blockchain
    map<string, string> mapByHash;
    vector<string> *recvdDataHash = new vector<string>;
    vector<Node*> transactions;
    Node center(recvdDataHash);
    int len = sizeof(saddr);
    while(1)
    {
        printf("String: ");
        cin.getline(str, 255);
        sendto(fd, &str, strlen(str), 0, (sockaddr*)&saddr, len);
        int n = recvfrom(fd, &hash, sizeof(hash), 0, (sockaddr*)&saddr, (socklen_t*)&len);
        hash[n] = '\0';
        recvdDataHash->push_back(hash);
        
        center.print();
    }
    return 0;
}