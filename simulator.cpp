#include <iostream>
#include <unistd.h>
#include <cmath>

using namespace std;

#define STEP_TIME 1

int N;       // Global variables for number of nodes and total time
int T;

int dice(int n) // For generating a random number
{
    return rand() % n;
}

struct Packet {
    int time;       // size in bytes
    int transmittor;     // Index of the transmittor
    int reciever;        // index of the reciever
    bool error = true;
    Packet(int t, int trans, int rec){
        time = t;
        transmittor = trans;
        reciever = rec;
    }
    Packet(){}
};

void swap(Packet *A, int i, int j)       // Swaps two packets in an array of packets
{
    Packet dummy = A[i];
    A[i] = A[j];
    A[j] = dummy;
}

class Packet_Heap
{
    Packet A[10485]; // 2^20
    int last = 0;
    int parent(int i) { return ceil(i / 2.0) - 1; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

public:
    int min()
    {
        if(last==0) return -1;
        return A[0].time;
    }

    void heapify()
    {
        int i = 0;
        while (i * 2 + 1 < last)
        {
            int val = A[i].time;
            int val1 = A[left(i)].time;
            int val2;
            if (right(i) == last)
                val2 = val;
            else
                val2 = A[2 * i + 2].time;
            if (val1 < val && val1 < val2)
            {
                swap(A, i, left(i));
                i = 2 * i + 1;
            }
            else if (val2 < val && val2 < val1)
            {
                swap(A, i, right(i));
                i = 2 * i + 2;
            }
            else
                break;
        }
    }

    Packet deletemin()
    {
        last--;
        swap(A, 0, last);
        heapify();
        return A[last];
    }

    void insert(Packet i)
    {
        if(last==1) A[0].error = true;
        A[last] = i;
        int k = last;
        last++;
        while (parent(k) >= 0 && A[parent(k)].time > A[k].time)
        {   
            swap(A, k, parent(k));
            k = parent(k);
        }
        if(last == 1) A[0].error == false;
    }

    void timedecrease(){
        for(int i=0; i<last; i++){
            // cout << "yes" << endl;
            A[i].time = A[i].time - STEP_TIME;
        }
        while(min()==0){
            Packet d = deletemin();
            if(dice(10)) cout << "Packet from " << d.transmittor << " unsuccessfully recieved at " << d.reciever << endl;
            else cout << "Packet from " << d.transmittor << " successfully recieved at " << d.reciever << endl;
        }
    }
};

struct node{
    int period;
    int startingtime;
    node(){
        period = dice(T);
        startingtime = dice(T);
    }
    bool generate(int currTime, Packet& P){
        if(currTime<startingtime) return false;
        if((currTime-startingtime)%period==0){
            // cout << "yes" << endl;
            P.time = 50+dice(950);
            P.reciever = dice(N);
            if(P.reciever == P.transmittor) P.reciever = (P.reciever+1)%N;
            return true;
        }
        else return false;
    }
};

class Scheduler
{
    Packet A[10485]; // 2^20
    int last = 0;
    int parent(int i) { return ceil(i / 2.0) - 1; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

public:
    int min()
    {
        return A[0].time;
    }

    void heapify()
    {
        int i = 0;
        while (i * 2 + 1 < last)
        {
            int val = A[i].time;
            int val1 = A[left(i)].time;
            int val2;
            if (right(i) == last)
                val2 = val;
            else
                val2 = A[2 * i + 2].time;
            if (val1 < val && val1 < val2)
            {
                swap(A, i, left(i));
                i = 2 * i + 1;
            }
            else if (val2 < val && val2 < val1)
            {
                swap(A, i, right(i));
                i = 2 * i + 2;
            }
            else
                break;
        }
    }

    void deletemin(Packet& P)
    {   
        if(last==0) return;
        last--;
        swap(A, 0, last);
        heapify();
        P = (A[last]);
    }

    void insert(Packet i)
    {
        A[last] = i;
        int k = last;
        last++;
        while (parent(k) >= 0 && A[parent(k)].time > A[k].time)
        {   
            swap(A, k, parent(k));
            k = parent(k);
        }
    }
};

int main()
{
    int stepCount = 0;
    float stepTime = STEP_TIME;
    float runTime; // sec; -ve means infinite
    float currTime = 0;
    cout << "Enter the number of nodes: - ";
    cin >> N;
    cout << "Enter the total runtime: - ";
    cin >> T;
    runTime = T*1000;
    node Node[N];
    Scheduler S;
    Packet_Heap H;
    for (;;)
    {   
        for(int i=0; i<N; i++){
            //cout << i << " ";
            Packet P;
            P.transmittor = i;
            bool result = Node[i].generate(currTime, P);
            //cout << result << endl;
            if(result){
                S.insert(P);
            }
        }
        Packet P(-1,0,0);
        S.deletemin(P);
        if(P.time!=-1) H.insert(P);
        if((runTime > 0) && (currTime > runTime)) { break; }
        stepCount++;
        currTime += stepTime;
        unsigned int millisecond = 100;
        usleep(stepTime * millisecond); //sleeps for 1 millisecond
        H.timedecrease();
    }
}