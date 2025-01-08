#include<iostream>
#include "mylib.h"
#include<stdlib.h>
#include<string>
#include<sys/time.h>
using namespace std;
int main()
{
    int sensors[4];
    string labels[4];

    srand(time(NULL));

    labels[0] = "North";
    labels[1] = "West";
    labels[2] = "South";
    labels[3] = "East";
    for ( int i = 0 ; i < 5 ; i++) // simulate 5 moves by the robot
    {
        getSensors(sensors);
        printSensors(sensors, labels);
        cout<<"The index of the furthest sensor value is "<<furthest(sensors)<<endl;//the bigger the value, the further it is from the object
        cout<<"So, the robot is moving towards "<<labels[furthest(sensors)]<<" to avoid the object."<<endl; //go
        cout<<endl;
    }
}