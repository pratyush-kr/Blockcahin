#include<iostream>
#include<ctime>
#include<vector>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<cstring>

using namespace std;

class Block
{
    private:
        string prevHash;
        string ownHash;
        string data;
        string timeStamp;
    protected:
        string generateHash(string);
    public:
        Block(string data)
        {
            time_t timestamp = time(0);
            timeStamp = ctime(&timestamp);
            prevHash = "";
            this->data = data;
            ownHash = generateHash(data + prevHash + timeStamp);
        }
        Block(string data, Block* block)
        {
            time_t timestamp = time(0);
            timeStamp = ctime(&timestamp);
            prevHash = block->ownHash;
            this->data = data;
            ownHash = generateHash(data + prevHash + timeStamp);
        }
        void putPrevHash(string hash){prevHash = hash;}
        string giveHash()
        {return ownHash;}
        void printBlock()
        {
            printf("{%s %s %s %s}\n", prevHash.c_str(), data.c_str(), timeStamp.c_str(), ownHash.c_str());
        }
        Block()
        {
            prevHash = "";
            ownHash = "";
            data = "";
            timeStamp = "";
        }
        void changeData(string prevHash)
        {
            //
        }
};

class Blockchain : public Block
{
    private:
        vector<Block*> blocks;
    public:
        void createChain(string data[], int n)
        {
            blocks.push_back(new Block(data[0]));
            for(int i=1; i<n; i++)
                blocks.push_back(new Block(data[i], blocks[i-1]));
            blocks[0]->putPrevHash(blocks[n-1]->giveHash());
        }
        void printChain()
        {
            for(int i=0; i<blocks.size(); i++)
                blocks[i]->printBlock();
        }
        void changeData(string prevHash)
        {
            //
        }
};


int main()
{
    Blockchain b1;
    int n = 5;
    string data[n] = {"hello", "world", "its", "circular", "blockchain"};
    b1.createChain(data, n);
    b1.printChain();
    return 0;
}

string Block::generateHash(string data)
{
    sockaddr_in saddr;
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(1025);
    saddr.sin_addr.s_addr = INADDR_ANY;
    char hash[255];
    char str[255];
    int len = sizeof(saddr);
    strcpy(str, data.c_str());
    sendto(fd, str, strlen(str), 0, (sockaddr*)&saddr, len);
    int n = recvfrom(fd, hash, sizeof(hash), 0, (sockaddr*)&saddr, (socklen_t*)&len);
    hash[n] = '\0';
    close(fd);
    return (string)hash;
}