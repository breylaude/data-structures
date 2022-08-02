enum Color
{
    RED,
    BLACK
};

struct RBNode
{
    int data;
    Color color;
    RBNode *leftChild;
    RBNode *rightChild;
    RBNode *parent;

    RBNode(int data)
    {
        this->data = data;
        this->leftChild = nullptr;
        this->rightChild = nullptr;
        this->parent = nullptr;
        this->color = RED;
    }
};

class RBTree
{
private:
    RBNode *root;
    string cr, cl, cp;

public:
    RBTree();
    void inorder();
    bool isEmpty();
    RBNode *find(int k);
    RBNode *findMin(RBNode *node);
    RBNode *findSuccessor(RBNode *node);
    RBNode *getRoot();
    // Rotations
    void leftRotation(RBNode *node);
    void rightRotation(RBNode *node);
    // Inserting
    void insertElement(int value);
    RBNode *insertElementNormalBST(RBNode *root, RBNode *node);
    void restoreRBTreeProperties(RBNode *&node);
    // Deleting
    void deleteElement(RBNode *);
    RBNode *getSibling(RBNode *);
    void fixDoubleBlack(RBNode *);
    void deleteTree(RBNode *node);
    // Printing
    void inorderH(string, string, RBNode *);
    void print();
};