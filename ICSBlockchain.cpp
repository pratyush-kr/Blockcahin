/*
    Note Before running this cpp program please
    run server.py using python as hashes are created
    on the server side
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
        int id;
        string prevHash;
        string upperHash; //each node points to its upper nodes
        string sentData; //data sent to the center for center it is null
        vector<string> *recvdDataHashes; //data cent to central node
        string hash; //sent data hash for local reference
    public:
        Node(vector<string> *data = NULL, string hash = "\0")
        {recvdDataHashes = data; this->hash = hash;}
        void print()
        {
            for(auto data : *recvdDataHashes)
                cout<<data<<'\n';
        }
        void addTransaction(string);
        Node(const Node &center, string hash)
        {
            int n = center.recvdDataHashes->size();
            id = n;
            upperHash = center.hash;
            if(n == 0) prevHash = '\0';
            prevHash = (*center.recvdDataHashes)[n-1];
            center.recvdDataHashes->push_back(hash);
            sentData = "sent: 0 recv: 0";
            this->hash = hash;
        }
        string giveHash(){return hash;}
        Node(string upperHash, int id)
        {
            this->id = id;
            this->upperHash = upperHash;
        }
};

int main()
{
    //Client Side Socket UDP for hashes
    sockaddr_in saddr;
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(1025);
    saddr.sin_addr.s_addr = INADDR_ANY;
    char hash[255];
    char str[255];
    int len = sizeof(saddr);
    //Now Working on Incomplete Circular Cycle Scope Blockchain
    map<int, string> mapByPos; //pos to last hash
    strcpy(str, "Center\n"); //Blackhole Constant
    sendto(fd, str, strlen(str), 0, (sockaddr*)&saddr, len);
    int n = recvfrom(fd, hash, sizeof(hash), 0, (sockaddr*)&saddr, (socklen_t*)&len);
    hash[n] = '\0';
    cout<<"Black Hole Hash: "<<hash<<'\n';
    vector<string> *recvdDataHash = new vector<string>;
    recvdDataHash->push_back(hash);
    Node center(recvdDataHash, hash);
    string command, sent, recv;
    Node *ptr; //stores new node
    while(1)
    {
        cout<<"Command: ";
        getline(cin, command);
        if("add source" == command)
        {
            strcpy(hash, "");
            int id=recvdDataHash->size();
            string transaction = "sent:0 recv:0 ID:" + to_string(id); 
            strcpy(str, (char*)&transaction[0]);
            cout<<"Transaction: "<<str<<'\n';
            sendto(fd, str, strlen(str), 0, (sockaddr*)&saddr, len);
            int n = recvfrom(fd, hash, sizeof(hash), 0, (sockaddr*)&saddr, (socklen_t*)&len);
            hash[n] = '\0';
            ptr = new Node(center, hash);
            mapByPos[id] = ptr->giveHash();
        }
        else if(command == "add transation")
        {
            strcpy(hash, "");
            int id;
            cout<<"ID: ";
            cin>>id;
            cout<<"Data Sent: ";
            cin>>sent;
            cout<<"Data Recv: ";
            cin>>recv;
            string transaction = "sent:" + sent + " recv:" + recv + " ID:"+ to_string(id);
            strcpy(str, (char*)&transaction[0]);
            sendto(fd, str, strlen(str), 0, (sockaddr*)&saddr, len);
            int n = recvfrom(fd, hash, sizeof(hash), 0, (sockaddr*)&saddr, (socklen_t*)&len);
            hash[n] = '\0';
            ptr = new Node(mapByPos[id], id);
            mapByPos[id] = ptr->giveHash();
        }
        else if(command == "print")
        {
            center.print();
        }
        else if(command == "exit")
            break;
    }
    close(fd);
    return 0;
}