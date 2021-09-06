#include<iostream>
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
    map<string, string> mapByHash;
    vector<string> *recvdDataHash = new vector<string>;
    vector<Node*> transactions;
    Node center(recvdDataHash);
    recvdDataHash->push_back("Hey");
    recvdDataHash->push_back("Yo");
    recvdDataHash->push_back("1323");
    center.print();
    return 0;
}