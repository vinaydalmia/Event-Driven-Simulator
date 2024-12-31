#include <iostream>
#include <cmath>
#include <time.h>
#include <chrono>

using namespace std::chrono;
using namespace std;
using namespace std;

double swap_counter = 0;
double swap_counter_d = 0;

int dice(int n) // For generating a random number
{
    return rand() % n;
}

void swapi(int *A, int i, int j)
{
    swap_counter = swap_counter + 1;
    int dummy = A[i];
    A[i] = A[j];
    A[j] = dummy;
}

void swapd(int *A, int i, int j)
{
    swap_counter_d++;
    int dummy = A[i];
    A[i] = A[j];
    A[j] = dummy;
}

class Heap
{
    int A[1048576]; // 2^20
    int last = 0;
    int parent(int i) { return ceil(i / 2.0) - 1; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

public:
    int min()
    {
        return A[0];
    }

    void heapify()
    {
        int i = 0;
        while (i * 2 + 1 < last)
        {
            int val = A[i];
            int val1 = A[left(i)];
            int val2;
            if (right(i) == last)
                val2 = val;
            else
                val2 = A[2 * i + 2];
            if (val1 < val && val1 < val2)
            {
                swapd(A, i, left(i));
                i = 2 * i + 1;
            }
            else if (val2 < val && val2 < val1)
            {
                swapd(A, i, right(i));
                i = 2 * i + 2;
            }
            else
                break;
        }
    }

    int deletemin()
    {
        last--;
        swapd(A, 0, last);
        heapify();
        return A[last];
    }

    void insert(int i)
    {
        A[last] = i;
        int k = last;
        last++;
        while (parent(k) >= 0 && A[parent(k)] > A[k])
        {   
            swapi(A, k, parent(k));
            k = parent(k);
        }
    }
};

// int main()
// {
//     srand(time(0));
//     Heap H;
//     int N = 1000;
//     for (int i = 0; i < N; i++)
//     {
//         H.insert(dice(N));
//     }
//     swap_counter = 0;
//     swap_counter_d = 0;
//     double durationd = 0;
//     double durationi = 0;
//     double counterd = 0;
//     double counteri = 0;
//     for (int i = 0; i < N / 5; i++)
//     {
//         if (dice(2) == 0)
//         {
//             auto start = high_resolution_clock::now();
//             H.deletemin();
//             counterd++;
//             auto stop = high_resolution_clock::now();
//             auto duration = duration_cast<nanoseconds>(stop - start);
//             durationd = durationd + duration.count();
//         }
//         else
//         {
//             auto start = high_resolution_clock::now();
//             H.insert(dice(2*N));
//             counteri++;
//             auto stop = high_resolution_clock::now();
//             auto duration = duration_cast<nanoseconds>(stop - start);
//             durationi = durationi + duration.count();
//         }
//     }
//     cout << swap_counter/counteri << endl;
//     cout << swap_counter_d/counterd << endl;
//     cout << durationi/counteri << endl;
//     cout << durationd/counterd << endl;
// }

int main() {
    Heap H;
    int N = 10;
    int A[10] = {1,2,3,4,7,3,9,8,2,5};
    for(int i=0; i<10; i++){
        H.insert(A[i]);
    }
    for(int i=0; i<10; i++){
        cout << H.deletemin() << " ";
    }
    cout << endl;
}