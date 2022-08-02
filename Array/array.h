class Array
{
private:
    int *array;
    int size;

public:
    Array();
    ~Array();
    void addElement(int);
    void addElementOnPosition(int, int);
    void addElementAtTheBegenning(int);
    void deleteElement(int);
    void deleteFromTheEnd();
    void deleteFromTheBeginning();
    bool findElement(int);
    void printArray();
    int getSize();
    bool isEmpty();
};