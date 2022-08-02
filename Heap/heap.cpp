#include <iostream>
#include "heap.h"
using namespace std;

Heap::Heap()
{
    this->size = 0;
    this->heap = nullptr;
}

// Print linear heap
void Heap::printHeap()
{
    cout << "Heap :";
    for (int i = 0; i < size; i++)
    {
        cout << heap[i] << " ";
    }
}

bool Heap::isEmpty()
{
    if (size <= 0)
        return true;
    return false;
}

bool Heap::findElement(int value)
{
    for (int i = 0; i < size; i++)
    {
        if (heap[i] == value)
        {
            return true;
        }
    }
    return false;
}

// Add element to the heap
void Heap::insert(int value)
{
    int temp, temp2;
    temp = size++;
    heap = (int *)realloc(heap, size * sizeof(int));
    temp2 = (temp - 1) / 2;

    while (temp > 0 && heap[temp2] < value)
    {
        heap[temp] = heap[temp2];
        temp = temp2;
        temp2 = (temp - 1) / 2;
    }
    heap[temp] = value;
}

// Delete element from the heap
void Heap::deleteElement(int value)
{
    if (size == 0)
        return;
    int i;
    for (i = 0; i < size; i++)
    {
        if (value == heap[i])
            break;
    }

    swap(heap[i], heap[size - 1]);
    size--;
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        heapify(i);
    }

    heap = (int *)realloc(heap, size * sizeof(int));
}

// Restore the heap properties
void Heap::heapify(int i)
{
    if (size == 1)
    {
        return;
    }
    else
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < size && heap[left] > heap[largest])
            largest = left;
        if (right < size && heap[right] > heap[largest])
            largest = right;
        if (largest != i)
        {
            swap(heap[i], heap[largest]);
            heapify(largest);
        }
    }
}
