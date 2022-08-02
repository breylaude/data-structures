class Heap
{
private:
    int size;
    int *heap;

    int parent(int i) { return i >> 1; };           // i/2
    int leftChild(int i) { return i << 1; };        // i*2
    int rightChild(int i) { return (i << 1) + 1; }; // i*2+1

public:
    Heap();
    bool isEmpty();
    int getMax();
    void insert(int);
    void printHeap();
    void shiftUp(int i);
    void shiftDown(int i);
    void heapify(int i);
    void deleteElement(int);
    bool findElement(int);
};