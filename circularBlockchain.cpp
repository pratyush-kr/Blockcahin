//run server.py using python

#include<iostream>
#include<ctime>
#include<vector>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<cstring>

/*
    The basic Idea here is to make even the last Block safe,
    So that if any one starts an at attack at any Block other blocks can
    recognise that and override the system thereby failing the attack
    this is achived using circular Blockchain as the hash of last is stored
    in the prev hash of genesis block so even if someone try to change the data of
    last block they just can't. I have used OOPS in such a way so that certain functions are
    hidden from the scope of user and the Blockchain can use certain function only once there by
    making it more secure.
*/

using namespace std;

class Block //Each node(controller in this case is a Block in the Blockchain)
{
    private:
        string prevHash;
        string ownHash;
        string data;
        string timeStamp;
    protected:
    /*
        I am hiding this function from the scope of user to be used only
        once in the scope of all the program, i.e while creating the chain.
        This ensures that this function by any one else except the admin when creating a block.
    */
        string generateHash(string);
    public:
        Block(string data) //this is used to create a genesis block
        {
            time_t timestamp = time(0);
            timeStamp = ctime(&timestamp);
            prevHash = "";
            this->data = data;
            ownHash = generateHash(data + prevHash + timeStamp);
        }
        Block(string data, Block* block) //any other block can be generated using this
        //the 2nd arg contain the previous block itself
        {
            time_t timestamp = time(0);
            timeStamp = ctime(&timestamp);
            prevHash = block->ownHash;
            this->data = data;
            ownHash = generateHash(data + prevHash + timeStamp);
        }
        //this function is used to put the prev hash in genesis block
        void putPrevHash(string hash){prevHash = hash;}
        //return Own Hash
        string giveHash()
        {return ownHash;}
        void printBlock()
        {
            printf("{%s %s %s %s}\n", prevHash.c_str(), data.c_str(), timeStamp.c_str(), ownHash.c_str());
        }
        //Defining a default constructor to define ghost genesis block
        Block()
        {
            prevHash = "";
            ownHash = "";
            data = "";
            timeStamp = "";
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
            blocks[0]->putPrevHash(blocks[n-1]->giveHash());
        }
        void printChain()
        {
            for(int i=0; i<blocks.size(); i++)
                blocks[i]->printBlock();
        }
};

int main()
{
    Blockchain *b1 = NULL; //Taking a pointer because i dont think
    //I can change any data once created
    vector<string> *data = NULL; //this will store the data for different blocks
    string str;
    string command;
    while(1)
    {
        cout<<"command: ";
        getline(cin, command);
        if(command == "exit")
            break;
        else if(command == "new")
        {
            if(data != NULL) delete data;
            data = new vector<string>;
            int n;
            cout<<"n: ";
            cin>>n;
            cin.ignore();
            for(int i=0; i<n; i++)
            {
                cout<<"Data: ";
                getline(cin, str);
                data->push_back(str);
            }
            b1 = new Blockchain();
            b1->createChain(*data);
        }
        else if(command == "print chain")
        {
            if(b1 != NULL)
                b1->printChain();
            else
                printf("No Blockchain to print\n");
        }
    }
    return 0;
}

string Block::generateHash(string data) //It send the string to the server.py and recieves
//a hash of the data
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