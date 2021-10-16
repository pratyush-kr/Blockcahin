#include<iostream>
#include<fstream>
#include<thread>
#include<unistd.h>

using namespace std;

volatile bool interupt = false;

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
    sleep(30);
    cout<<"Interupting\n";
    interupt = true;
    th1.join();
    return 0;
}

void foo(volatile float v, volatile float i, volatile float p)
{
    fstream file("NewData.csv");
    file<<"Voltage, Current, Power\n";
    while(!interupt)
    {
        file<<v<<','<<i<<','<<p<<'\n';
        usleep(100000);
    }
    cout<<"Interupt = "<<true<<'\n';
}