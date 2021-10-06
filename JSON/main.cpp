#include<iostream>
#include<fstream>
#include<jsoncpp/json/json.h>
#include<unistd.h>

using namespace std;

int main()
{
    json j;
    ifstream ifs("profile.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj);
    cout<<obj["1"]<<endl;
    cout<<obj["2"]<<endl;
    ifs.close();
    return 0;
}