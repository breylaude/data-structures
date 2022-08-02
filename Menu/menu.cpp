#include <iostream>
#include <conio.h>
#include "../List/listLogic.cpp"
#include "../Array/arrayLogic.cpp"
#include "../Heap/heapLogic.cpp"
#include "../RBTree/RBTreeLogic.cpp"
using namespace std;

//* Structures Declaration
LinkedList *list = new LinkedList();
Array *array = new Array();
Heap *heap = new Heap();
RBTree *tree = new RBTree();

// The default menu will be printed in every testing menu
void printDefaultMenu()
{
    cout << "[1] Add element\n";
    cout << "[2] Delete element\n";
    cout << "[3] Fill structure with random values\n";
    cout << "[4] Fill structure with values from the file\n";
    cout << "[5] Find element\n";
    cout << "[6] Print structure\n";
    cout << "[7] Clear structure\n";
    cout << "[8] Return\n";
    cout << "Press key with your choice\n";
}

// Gets the value if necessary for the function
int askForValue()
{
    int val;
    cout << "\nEnter value: ";
    cin >> val;
    return val;
}

// Testing menu for array
void arrayMenu()
{
    system("cls");
    do
    {
        cout << "------------- ARRAY MENU -------------" << endl;
        cout << "[a] Add element at the beginning\n";
        cout << "[b] Add element at the position\n";
        cout << "[c] Delete element from the beginning\n";
        cout << "[d] Delete element from the position\n";
        printDefaultMenu();
        cout << "\n";

        char choice = getch();
        int val;
        int pos;

        switch (choice)
        {
        case 'a':
            array->addElementAtTheBegenning(askForValue());
            system("cls");
            break;
        case 'b':
            system("cls");
            cout << "\nEnter position: ";
            cin >> pos;
            array->addElementOnPosition(askForValue(), pos);
            break;
        case 'c':
            system("cls");
            array->deleteFromTheBeginning();
            break;
        case 'd':
            system("cls");
            cout << "\nEnter position: ";
            cin >> pos;
            array->deleteElement(pos);
            break;
        case '1':
            system("cls");
            array->addElement(askForValue());
            break;
        case '2':
            system("cls");
            array->deleteElement(askForValue());
            break;
        case '3':
            system("cls");
            fillArrayWithRandomData(array);
            break;
        case '4':
            system("cls");
            fillArrayFromFile(array);
            break;
        case '5':
            system("cls");
            if (array->findElement(askForValue()))
                cout << "Found element!\n";
            else
                cout << "Element is not in the structure\n";
            break;
        case '6':
            system("cls");
            array->printArray();
            cout << "\n\n";
            break;
        case '7':
            system("cls");
            deleteArray(&array);
            break;
        case '8':
            system("cls");
            return;
            break;

        default:
            cout << "Invalid choice!\n";
            break;
        }
    } while (true);
}

// Testing menu for list
void listMenu()
{
    system("cls");
    do
    {
        cout << "------------- LINKED LIST MENU -------------" << endl;
        cout << "[a] Add element at the beginning\n";
        cout << "[b] Add element at the position\n";
        cout << "[c] Delete element from the beginning\n";
        cout << "[d] Delete element from the position\n";
        printDefaultMenu();

        char choice = getch();
        int val;
        int pos;

        switch (choice)
        {
        case 'a':
            system("cls");
            list->push_front(askForValue());
            break;
        case 'b':
            system("cls");
            cout << "\nEnter position: ";
            cin >> pos;
            list->insert(askForValue(), pos);
            break;
        case 'c':
            system("cls");
            list->pop_front();
            break;
        case 'd':
            system("cls");
            cout << "\nEnter position: ";
            cin >> pos;
            list->deleteFromPos(pos);
            break;
        case '1':
            system("cls");
            list->push_back(askForValue());
            break;
        case '2':
            system("cls");
            list->pop_back();
            break;
        case '3':
            system("cls");
            fillLinkedListWithRandomData(list);
            break;
        case '4':
            system("cls");
            fillLinkedListFromFile(list);
            break;
        case '5':
            system("cls");
            ListNode *elem;
            elem = list->findElement(askForValue());
            if (elem != nullptr)
                elem->printData();
            else
                cout << "Element is not in the list" << endl;
            break;
        case '6':
            system("cls");
            list->printList();
            cout << "\n";
            break;
        case '7':
            system("cls");
            deleteList(&list);
            cout << "Deleted!\n";
            break;
        case '8':
            return;
            break;
        default:
            break;
        }
    } while (true);
}

// Testing menu for heap
void heapMenu()
{
    system("cls");
    do
    {
        cout << "------------- BINARY HEAP MENU -------------" << endl;
        printDefaultMenu();

        char choice = getch();
        int val;

        switch (choice)
        {
        case '1':
            system("cls");
            heap->insert(askForValue());
            cout << "Inserted!\n";
            break;
        case '2':
            system("cls");
            heap->deleteElement(askForValue());
            cout << "Deleted!\n";
            break;
        case '3':
            system("cls");
            fillHeapWithRandomData(heap);
            break;
        case '4':
            system("cls");
            fillHeapFromFile(heap);
            break;
        case '5':
            system("cls");
            if (heap->findElement(askForValue()))
                cout << "Found element!\n";
            else
                cout << "Element is not in the structure\n";
            break;
        case '6':
            system("cls");
            heap->printHeap();
            cout << "\n";
            break;
        case '7':
            system("cls");
            deleteHeap(&heap);
            cout << "Deleted!\n";
            break;
        case '8':
            return;
            break;

        default:
            break;
        }
    } while (true);
}

// Testing menu for RB tree
void treeMenu()
{
    char choice;
    int val;
    system("cls");
    do
    {
        cout << "------------- RED-BLACK TREE MENU -------------" << endl;
        printDefaultMenu();

        choice = getch();

        switch (choice)
        {
        case '1':
            system("cls");
            tree->insertElement(askForValue());
            cout << "Inserted!\n";
            break;
        case '2':
            system("cls");
            tree->deleteElement(tree->find(askForValue()));
            break;
        case '3':
            system("cls");
            fillTreeWithRandomData(tree);
            break;
        case '4':
            system("cls");
            fillTreeFromFile(tree);
            break;
        case '5':
            system("cls");
            RBNode *temp;
            temp = tree->find(askForValue());
            if (temp != nullptr)
                cout << "Found element!\n";
            else
                cout << "Element is not in the structure\n";
            break;
        case '6':
            system("cls");
            tree->inorder();
            cout << "\n";
            break;
        case '7':
            deleteTree(&tree);
            system("cls");
            cout << "Deleted!\n";
            break;
        case '8':
            return;

        default:
            break;
        }
    } while (true);
}

void printExperimentMenu()
{
    char choice;
    system("cls");

    do
    {
        cout << "------------- EXPERIMENT MENU -------------" << endl;
        cout << "[1] Experiment on a Array" << endl;
        cout << "[2] Experiment on a Linked list" << endl;
        cout << "[3] Experiment on a Binary heap" << endl;
        cout << "[4] Experiment on a Red-black tree" << endl;
        cout << "[5] Experiment on all structures" << endl;
        cout << "[6] Exit" << endl;

        choice = getch();
        switch (choice)
        {
        case '1':
            system("cls");
            arrayExperiment(array);
            break;
        case '2':
            system("cls");
            linkedListExperiment(list);

            break;
        case '3':
            system("cls");
            heapExperiment(heap);

            break;
        case '4':
            system("cls");
            treeExperiment(tree);

            break;
        case '5':
            system("cls");
            cout << "ARRAY:\n";
            arrayExperiment(array);
            cout << "\nLIST:\n";
            linkedListExperiment(list);
            cout << "\nHEAP:\n";
            heapExperiment(heap);
            cout << "\nTREE:\n";
            treeExperiment(tree);

            break;
        case '6':
            return;
            break;
        default:
            break;
        }
    } while (true);
}

void printTestingMenu()
{
    char choice;
    do
    {
        system("cls");

        cout << "------------- TESTING MENU -------------" << endl;
        cout << "[1] Array" << endl;
        cout << "[2] Linked list" << endl;
        cout << "[3] Binary heap" << endl;
        cout << "[4] Red-black tree" << endl;
        cout << "[5] Exit" << endl;

        choice = getch();
        switch (choice)
        {
        case '1':
            arrayMenu();
            break;
        case '2':
            listMenu();
            break;
        case '3':
            heapMenu();
            break;
        case '4':
            treeMenu();
            break;
        case '5':
            return;
            break;
        default:
            return;
            break;
        }
    } while (true);
}

// Menu for selecting program mode
void selectMode()
{
    char choice;
    system("cls");
    do
    {
        cout << "-------------- START ----------------\n";
        cout << "[1] Experiment mode\n";
        cout << "[2] Testing mode\n";
        cout << "[3] Exit program\n";
        cout << "Press key with your choice\n";

        choice = getch();
        switch (choice)
        {
        case '1':
            printExperimentMenu();
            system("cls");
            break;
        case '2':
            printTestingMenu();
            system("cls");
            break;
        default:
            return;
            break;
        }
    } while (true);
}