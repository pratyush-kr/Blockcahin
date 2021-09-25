#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

void send();
void recv();
void process();
void response();

int main()
{
    recv();
    send();
    process();
    response();
    return 0;
}