#include<iostream>
#include<fstream>
#include<thread>
#include<unistd.h>

using namespace std;

volatile bool interrupt = false;

void foo(volatile float v, volatile float i, volatile float p);

int main()
 {
    volatile float voltage = 440, current, power = 21;
    cout<<"Initial Requirement:\n";
    printf("Power: %.2f KW\n", power);
    printf("Voltage: %.2f V\n", voltage);
    current = power*1000/voltage;
    printf("Current: %.2f A\n", current);
    thread th1(foo, voltage, current, power);
    while(true)
    {
        int br;
        sleep(15);
        cout<<"Interrupting\n";
        interrupt = true;
        cout<<"Break?: ";
        cin>>br;
        if(br == 1)
            break;
    }
    th1.join();
    return 0;
}

void foo(volatile float v, volatile float i, volatile float p)
{
    fstream file("NewData.csv", ios::out);
    file<<"Voltage, Current, Power\n";
    bool cont = true;
    while(cont)
    {
        float power, voltage, current;
        while(!interrupt)
        {
            file<<v<<','<<i<<','<<p<<'\n';
            usleep(100000);
        }
        cout<<"Continue: ";
        cin>>cont;
        if(cont == 1)
        {
            cout<<"Power: ";
            cin>>power;
            cout<<"Voltage: ";
            cin>>voltage;
            current = power*1000/voltage;
            v = voltage;
            p = power;
            i = current;
            interrupt = false;
        }
    }
    cout<<"Interupt = "<<true<<'\n';
    file.close();
}