#include <fstream>
#include <time.h>
#include "RBTree.cpp"

// Delete the old tree and create new one
void deleteTree(RBTree **tree)
{
    delete *tree;
    *tree = new RBTree();
}

void fillTreeFromFile(RBTree *tree)
{
    // Open file and check if it opened with success
    fstream file;
    file.open("./data.txt", ios::in);

    if (!tree->isEmpty())
    {
        cout << "Red-Black Tree is not empty!\n";
        return;
    }

    if (!file.is_open())
    {
        cout << "[Red-Black Tree] Cannot open data.txt\n";
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
        tree->insertElement(data);
    }
    cout << "Filled with success!\n";
    file.close();
}

// Fill tree with random values fot testing
void fillTreeWithRandomData(RBTree *tree)
{
    srand(time(NULL));

    if (!tree->isEmpty())
    {
        cout << "Red-Black Tree is not empty!\n";
        return;
    }

    int size;
    cout << "Enter the size of the tree: " << flush;
    cin >> size;

    // Fill tree with random values
    for (int i = 0; i < size; i++)
    {
        int value = rand();
        tree->insertElement(value);
    }
}

void fillTreeForExperiment(RBTree **tree, int size, int range)
{
    int value;
    deleteTree(tree);

    for (int i = 0; i < size; i++)
    {
        value = rand() % range;
        (*tree)->insertElement(value);
    }
}

// Perform experiment on tree
void treeExperiment(RBTree *&tree)
{
    srand(time(NULL));
    int size, value, testNumber, range;
    float time;

    cout << "Please enter the size of the red-black tree: " << flush;
    cin >> size;

    cout << "Please enter number of tests: " << flush;
    cin >> testNumber;

    cout << "Please enter maximum size of the arguments in structure: " << flush;
    cin >> range;

    //! Insert element
    time = 0;
    for (int i = 0; i < testNumber; i++)
    {
        fillTreeForExperiment(&tree, size, range);
        value = rand() % range;
        Timer timer;
        tree->insertElement(value);
        time += timer.getTime().count() * 1000000000.0f;
    }
    cout << "Inserting element to the red-black tree took on average: " << time / testNumber << " ns\n";

    //! Delete element
    time = 0;
    RBNode *node;
    for (int i = 0; i < testNumber; i++)
    {
        fillTreeForExperiment(&tree, size, range);
        value = rand() % range;
        Timer timer;
        node = tree->find(value);
        if (node == nullptr)
            continue;
        tree->deleteElement(node);
        time += timer.getTime().count() * 1000000000.0f;
    }
    cout << "Deleting element form the red-black tree took on average: " << time / testNumber << " ns\n";

    //! Find element
    time = 0;
    for (int i = 0; i < testNumber; i++)
    {
        fillTreeForExperiment(&tree, size, range);
        value = rand() % range;
        Timer timer;
        tree->find(value);
        time += timer.getTime().count() * 1000000000.0f;
    }
    cout << "Finding element in the red-black tree took on average: " << time / testNumber << " ns\n";
}