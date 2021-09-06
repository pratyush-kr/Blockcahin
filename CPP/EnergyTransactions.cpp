//run server.py using python

#include<iostream>
#include<ctime>
#include<vector>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<cstring>

using namespace std;

class Block //Each node(controller in this case is a Block in the Blockchain)
{
    private:
        string prevHash;
        string data;
        string timeStamp;
        string ownHash;
        vector<string> *pvHash;
    protected:
    /*
        I am hiding these function from the scope of user to be used only
        once in the scope of Blockchain class, i.e while creating the chain.
        This ensures that this function cannot be used by any one else
        except the admin when creating a Blockchain.
    */
        string generateHash(string);
        virtual void addPV();
    public:
        Block(string data) //this is used to create a genesis block
        {
            pvHash = NULL;
            time_t timestamp = time(0);
            timeStamp = ctime(&timestamp); //it creates a time stamp in 'day mmm dd hh:mm:ss yyyy'
            prevHash = "";
            this->data = data;
            ownHash = generateHash(prevHash + data + timeStamp);
        }
        Block(string data, Block* block) //any other block can be generated using this
        //the 2nd arg contain the previous block itself
        {
            pvHash = NULL;
            time_t timestamp = time(0);
            timeStamp = ctime(&timestamp);
            prevHash = block->ownHash;
            this->data = data;
            ownHash = generateHash(prevHash + data + timeStamp);
        }
        //this function is used to put the prev hash in genesis block
        //return Own Hash
        string giveHash(){return ownHash;}
        void printBlock()
        {
            printf("{%s %s %s %s}\n", prevHash.c_str(), data.c_str(), timeStamp.c_str(), ownHash.c_str());
        }
        //Defining a default constructor to define ghost genesis block
        Block()
        {
            time_t timestamp = time(0);
            timeStamp = ctime(&timestamp);
            prevHash = "";
            data = "Centeral Node";
            ownHash = generateHash(data + timeStamp);
            pvHash = new vector<string>;
        }
};

class Blockchain : public Block
{
    private:
        vector<Block*> blocks; //contains all the Block which we are gonna use to store data
        //in real world example this block does not exists
    public:
        void createChain(vector<string> data) //creates the whole chain using the data vector
        {
            int n = data.size();
            blocks.push_back(new Block(data[0]));
            for(int i=1; i<n; i++)
                blocks.push_back(new Block(data[i], blocks[i-1]));
        }
        void printChain()
        {
            for(int i=0; i<blocks.size(); i++)
                blocks[i]->printBlock();
        }
        void addPV();
};

int main()
{
    Blockchain *b1 = NULL;
    vector<string> *data = NULL; //this will store the data for different blocks acting as an array
    vector<vector<string>> transactions;
    string str;
    string command;
    return 0;
}

string Block::generateHash(string data) //It sends the string to the server.py and recieves
//a hash of the string
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

void Blockchain::addPV()
{
    string name;
    cout<<"Name: ";
    getline(cin, name);
    if(blocks.size() < 1)
        blocks.push_back(new Block(name));
}