#include<iostream>
using namespace std;

class heaptree{
    public:
    int totalkeys;
    int value;
    int heap[10];

    void insert(){
        cout<<"Enter total number of keys: ";
        cin>>totalkeys;
        for(int loc=0;loc<totalkeys;loc++){
            cout<<"Enter key: ";
            cin>>value;
            built(loc,totalkeys,heap);
        }
    }

    void built(int loc,int totalkeys,int heap[]){
        int parent = loc/2;
        while (heap[parent] > heap[loc]){
            int temp = heap[parent];
            heap[parent] = heap[loc];
            heap[loc] = temp;
            loc = parent;
        }
    }

    void display(){
        cout<<"Heap Tree: ";
        for(int loc=0;loc<totalkeys;loc++){
            cout<<heap[loc]<<" ";
        }
        cout<<endl;
    }
}heapObject;

int main(){
    int choice;
    do{
        cout<<"1. Accept Data \t 2. Display Heap \t 0. Exit Program";
        cout<<"Enter the Choice : ";
        cin>>choice;
        switch(choice){
            case 1: heapObject.insert(); break;
            case 2: heapObject.display(); break;
            case 0: cout<<"Exiting program..."; break;
            default: cout<<"Invalid choice! Please try again."; break;
        }
    }while(choice != 0);
    return 0;
}