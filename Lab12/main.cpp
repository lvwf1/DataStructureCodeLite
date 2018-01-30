#include <iostream>
#include "priority_queue.h"

using namespace std;

int main()
{
    priority_queue<int> pq;
    pq.push(23);
    pq.push(45);
    pq.push(35);
    pq.push(4);
    pq.push(21);
    pq.push(22);
    pq.push(19);
    pq.push(27);
    pq.push(42);
    pq.print();
    pq.pop();
    pq.print();
    pq.pop();
    pq.print();
    return 0;
}