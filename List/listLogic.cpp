#include <iostream>
#include <time.h>
#include <fstream>
#include "linkedList.cpp"

// Delete old list and create new one
void deleteList(LinkedList **list)
{
    delete *list;
    *list = new LinkedList();
}

void fillLinkedListFromFile(LinkedList *list)
{
    // Open file and check if it opened with success
    fstream file;
    file.open("./data.txt", ios::in);

    if (!list->isEmpty())
    {
        cout << "List is not empty!\n";
        return;
    }

    if (!file.is_open())
    {
        cout << "[LinkedList] Cannot open data.txt\n";
        return;
    }

    int size;
    int data;
    // First data is the size
    file >> size;

    // All the next values are elements
    for (int i = 0; i < size; i++)
    {
        file >> data;
        list->push_back(data);
    }
    cout << "Filled with success!\n";
    file.close();
}

// Fill list with random values for testing
void fillLinkedListWithRandomData(LinkedList *list)
{
    if (!list->isEmpty())
    {
        cout << "List is not empty!\n";
        return;
    }

    int size;
    cout << "Enter the size of the list: " << flush;
    cin >> size;

    // Fill list with random values
    for (int i = 0; i < size; i++)
    {
        int value = rand();
        list->push_back(value);
    }
}

void fillListForExperiment(LinkedList **list, int size, int range)
{

    deleteList(list);

    for (int i = 0; i < size; i++)
    {
        int value = rand() % range;
        (*list)->push_back(value);
    }
}

// Perform experiment on list
void linkedListExperiment(LinkedList *&list)
{
    srand(time(NULL));
    int size, value, testNumber, range;
    float time;

    cout << "Please enter the size of the list: " << flush;
    cin >> size;

    cout << "Please enter number of tests: " << flush;
    cin >> testNumber;

    cout << "Please enter maximum size of the arguments in structure: " << flush;
    cin >> range;

    //! Insert at the end
    time = 0;
    for (int i = 0; i < testNumber; i++)
    {
        fillListForExperiment(&list, size, range);
        value = rand() % range;
        Timer timer;
        list->push_back(value);
        time += timer.getTime().count() * 1000000000.0f;
    }
    cout << "Inserting element at the end of the double linked list took on average: " << time / testNumber << " ns\n";

    //! Insert at the beginning
    time = 0;
    for (int i = 0; i < testNumber; i++)
    {
        fillListForExperiment(&list, size, range);
        value = rand() % range;
        Timer timer;
        list->push_front(value);
        time += timer.getTime().count() * 1000000000.0f;
    }
    cout << "Inserting element at the beginning of the double linked list took on average: " << time / testNumber << " ns\n";

    //! Insert at random position
    time = 0;
    int position;
    for (int i = 0; i < testNumber; i++)
    {
        fillListForExperiment(&list, size, range);
        value = rand() % range;
        position = rand() % (size - 1);
        Timer timer;
        list->insert(value, position);
        time += timer.getTime().count() * 1000000000.0f;
    }
    cout << "Inserting element at the random position of the double linked list took on average: " << time / testNumber << " ns\n";

    //! Delete element form the end
    time = 0;
    for (int i = 0; i < testNumber; i++)
    {
        fillListForExperiment(&list, size, range);
        Timer timer;
        list->pop_back();
        time += timer.getTime().count() * 1000000000.0f;
    }
    cout << "Deleting element from the end of the double linked list took on average: " << time / testNumber << " ns\n";

    //! Delete element fotm the position
    time = 0;
    for (int i = 0; i < testNumber; i++)
    {
        fillListForExperiment(&list, size, range);
        position = rand() % (size - 1);
        Timer timer;
        list->deleteFromPos(position);
        time += timer.getTime().count() * 1000000000.0f;
    }
    cout << "Deleting element from the random position of the doule linked list took on average: " << time / testNumber << " ns\n";

    //! Delete element form the beginning
    time = 0;
    for (int i = 0; i < testNumber; i++)
    {
        fillListForExperiment(&list, size, range);
        Timer timer;
        list->pop_front();
        time += timer.getTime().count() * 1000000000.0f;
    }
    cout << "Deleting element from the beginning of the double linked list took on average: " << time / testNumber << " ns\n";

    //! Finding element in the list
    time = 0;
    for (int i = 0; i < testNumber; i++)
    {
        fillListForExperiment(&list, size, range);
        value = rand() % range;
        Timer timer;
        list->findElement(value);
        time += timer.getTime().count() * 1000000000.0f;
    }
    cout << "Finding element in the double linked list took on average: " << time / testNumber << " ns\n";
}
