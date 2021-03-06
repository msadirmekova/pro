//
//  main.cpp
//  Assignment7
//
//  Created by Madina Sadirmekova on 10/18/19.
//  Copyright © 2019 Madina Sadirmekova. All rights reserved.
//

//idle-free
#include<iostream>
#include<string>
using namespace std;
#include "Queue.h"
#include "DynamicArray.h"
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
#include<cmath>


struct Customer
{
    char id;
    int ArrivalTime;
    int endTime;
};

int getRandomNumberOfArrivals(double averageArrivalRate)
{
    int arrivals = 0;
    double probOfnArrivals = exp(-averageArrivalRate);
    for(double randomValue = (double)rand( ) / RAND_MAX; (randomValue -= probOfnArrivals) > 0.0; probOfnArrivals *= averageArrivalRate / static_cast<double>(++arrivals));
    return arrivals;
}

char getLetter(char &letter)
{
    letter++;
    if(letter  > 'Z')
        letter = 'A';
    return letter;
}

int main() {

    cout<<"Programmer: Madina Sadirmekova \n";
    cout<<"Programmer's ID: 1736270 \n";
    cout<<"file: "<<__FILE__<<"\n\n";

    srand(time(0));
    rand();
    
    Queue<Customer> waitLine;
    DynamicArray<Customer> serving;
    DynamicArray<bool> serverStatus;
    Customer client;

    fstream file;

    string sservers, srate, stime, slength, smax_time, smin_time,sserver;
    int servers, totalTime, length, max_time, min_time;
    double rate;
    char letter = 'Z';
    
    file.open("simulation.txt");
    if(!file.good())
        cout<<"I/O error \n";
    file>>sservers;
    while(file.good())
    {
        getline(file,sserver, '\n');
        getline(file,srate, '\n');
        getline(file,slength, '\n');
        getline(file,smin_time, '\n');
        getline(file,smax_time, '\n');
        getline(file,stime, '\n');

    }
    servers = stoi(sservers);
    rate = stof(srate);
    totalTime = stoi(stime);
    length = stoi(slength);
    min_time = stoi(smin_time);
    max_time = stoi(smax_time);
    int service_time = rand()%(max_time-min_time) + min_time;

    cout<<"Number of servers: "<<servers<<endl;
    cout<<"Customer arrival rate "<<rate<<" per minute, for "<<totalTime<<" minutes \n";
    cout<<"Maximum queue length: "<<length<<endl;
    cout<<"Minimum service time: "<<min_time<<" minutes"<<endl;
    cout<<"Maximum service time: "<<max_time<<" minutes"<<endl;

    for(int time = 0; ; time++)
    {

        for(int i = 0; i < servers; i++)
        {
            if(!serverStatus[i])
            {
                if(serving[i].endTime == time)
                {
                    serverStatus[i] = true;
                serving[i].id = ' ';
                }
            }
        }

        if(time < totalTime)
        {
            int arrivalNum = getRandomNumberOfArrivals(rate);
            for(int j = 0; j < arrivalNum; j++)
            {
                if(waitLine.size() < length)
                {
                    client.id = getLetter(letter);
                    client.ArrivalTime = time;
                    waitLine.push(client);
                }
            }
        }

        for(int i = 0; i < servers; i++)
        {
            if(serverStatus[i] && !waitLine.empty())
            {
                serving[i].id = waitLine.front().id;
                waitLine.pop();
                serving[i].endTime = time + service_time;
                serverStatus[i] = false;
            }
        }


        cout << "Time: " << time << endl;
        cout << "--------------------------------------\n";
        cout << "server"<<setw(16)<< "now serving"<< setw(16) << "wait line \n";
        cout << "--------------------------------------- \n";
        Queue<Customer> copy = waitLine;
        for(int i = 0; i < servers; i++)
        {
            cout << i << setw(16) << serving[i].id<<"         ";
            
            while(!copy.empty()){
                cout << copy.front().id;
                copy.pop();
            }
            cout << endl;
        }
        
        if(time == totalTime)
            break;
    }
    
    return 0;
}
