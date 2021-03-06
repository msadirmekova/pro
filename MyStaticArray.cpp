#include<iostream>
using namespace std;
#include<cstdlib>
#include<cctype>
#include<cassert>
#include "StaticArray.h"

const bool Placed = true;
int main()
{
    cout<<"Programmer: Madina Sadirmekova \n";
    cout<<"Programmer's ID: 1736270 \n";
    cout<<"file: "<<__FILE__<<"\n\n";
    
    StaticArray<double, 100> a;
    StaticArray<bool, 100> storeStatus;
    int count = 0;
    char ch[15], chi[15];
    double value;
    int index = 0;
    while(chi[0] != 'Q' || chi[0] != 'q')
    {
        cout<<"Input an index and a value [Q to quit]: ";
        cin>>chi;
        if(chi[0] == 'Q' || chi[0] == 'q')
            break;
        cin>>ch;
        value = atof(ch);
        if(isalpha(chi[0]))
            index = 0;
        else
            index = atoi(chi);
        
        a[index] = value;
        storeStatus[index] = Placed;
    }
    
    for(int i = 0; i < 100; i++)
    {
        if(storeStatus[i] == Placed)
            count++;
    }
    cout<<"You stored this many values: "<<count<<endl;
    
    cout<<"The index-value pairs are:"<<endl;
    for(int i = 0; i < 100; i++)
    {
        if(storeStatus[i] != 0)
            cout<<i<<" -> "<<a[i]<<endl;
    }
    
    while(chi[0] != 'Q' || chi[0] != 'q')
    {
        cout<<"Input an index for me to look up [Q to quit]: ";
        cin>>chi;
        if(chi[0] == 'Q' || chi[0] == 'q')
            break;
        index = atof(chi);
        if(a[index] != 0 && (index >=0 && index < 100))
            cout<<"Found it -- the value stored at "<<index<<" is "<<a[index]<<endl;
        else
            cout<<"I didn't find it \n";
    }
    return 0;
}

