#include <iostream>
#include <stack>

template<typename T>
using FunctionType = void (*)(T&);

template<typename T>
class BinaryTree;


template<typename T>
class TreeNode
{
    public:
        TreeNode() {} ; 
        TreeNode (const T& nodeItem, TreeNode<T> *left = nullptr, 
                                     TreeNode<T> *right = nullptr): 
        item(nodeItem), leftChildPtr(left), rightChildPtr(right) {} 
        T item; 
        TreeNode<T> *leftChildPtr; 
        TreeNode<T> *rightChildPtr; 
        friend class BinaryTree<T>; 
};

template<typename T>
class BinaryTree
{
    public:
        BinaryTree();
        BinaryTree(const T& rootltem); 
        BinaryTree(const T& rootItem, 
                    const BinaryTree<T>& leftTree, 
                    const BinaryTree<T>& rightTree);
        BinaryTree(const BinaryTree<T>& tree);
        BinaryTree(BinaryTree<T>&& tree);
        BinaryTree<T>& BinaryTree<T>::operator=(BinaryTree<T>&& rhs);
        ~BinaryTree();
        bool isEmpty() const;
        T& getRootData() const;
        void setRootData(const T& newItem);
        void attachLeft(const T& newItem);     
        void attachRight(const T& newItem);  
        void attachLeftSubtree(const BinaryTree<T>& leftTree); 
        void attachRightSubtree(const BinaryTree<T>& rightTree);  
        void detachLeftSubtree(BinaryTree<T>& leftTree); 
        void detachRightSubtree(BinaryTree<T>& rightTree); 
        BinaryTree<T> getLeftSubtree() const; 
        BinaryTree<T> getRightSubtree() const;
        BinaryTree<T>& operator=(const BinaryTree<T>& rhs);
        TreeNode<T> *rootPtr() const; 
        void preorderTraverse(TreeNode<T> *treePtr, FunctionType<T> visit); 
        void inorderTraverse(TreeNode<T> *treePtr, FunctionType<T> visit); 
        void postorderTraverse(TreeNode<T> *treePtr, FunctionType<T> visit);
    protected: 
        BinaryTree(TreeNode<T> *nodePtr);
        void copyTree(TreeNode<T> *treePtr, 
        TreeNode<T>* &newTreePtr) const; 
        void destroyTree(TreeNode<T>* &treePtr); 
        void setRootPtr(TreeNode<T> *newRoot); 
        void getChildPtrs(TreeNode<T> *nodePtr, 
        TreeNode<T>* &leftChildPtr, 
        TreeNode<T>* &rightChildPtr) const; 
        void setChildPtrs(TreeNode<T> *nodePtr, 
        TreeNode<T>* leftChildPtr, 
        TreeNode<T>* rightChildPtr);

    private: 
        TreeNode<T> *root{nullptr};
    
};


template<typename T>
BinaryTree<T>::BinaryTree() : root(nullptr) {}

template<typename T>
BinaryTree<T>::BinaryTree(const T& rootItem) { 
    root = new TreeNode<T>(rootItem, nullptr, nullptr);
    if (root == nullptr) {
        throw std::bad_alloc();
    }
}

template<typename T>
BinaryTree<T>::BinaryTree (const T& rootItem, 
                        const BinaryTree<T>& leftTree, 
                        const BinaryTree<T>& rightTree) 
{ 
    root = new TreeNode<T>(rootItem, nullptr, nullptr); 
    if (root == nullptr) {
        throw std::bad_alloc();
    }
    
    attachLeftSubtree(leftTree); 
    attachRightSubtree(rightTree); 
}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& tree) { 
    copyTree(tree.root, root); 
}

template<typename T>
BinaryTree<T>::BinaryTree(TreeNode<T> *nodePtr): root(nodePtr) {}

template<typename T>
BinaryTree<T>::BinaryTree(BinaryTree<T>&& tree) : root(tree.root) {
    tree.root = nullptr;
}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(BinaryTree<T>&& rhs) {
    if (this != &rhs) {
        destroyTree(root);
        root = rhs.root;
        rhs.root = nullptr;
    }
    return *this;
}

template<typename T>
BinaryTree<T>::~BinaryTree(){
    destroyTree(root);
}

template<typename T>
bool BinaryTree<T>::isEmpty() const{ 
    return (this->root == nullptr); 
} 

template<typename T>
T& BinaryTree<T>::getRootData() const 
{ 
    if(this->root == nullptr)
        std::cerr << "Tree is empty" << std::endl;
    return this->root->item; 
}

template<typename T>
void BinaryTree<T>::setRootData(const T& newItem) 
{ 
    if (!isEmpty()) 
        root->item = newItem; 
    else { 
        root = new TreeNode<T>(newItem, nullptr, nullptr);
        try{
            if(root == nullptr){
                throw std::bad_alloc();
            } 
        }
        catch(const std::bad_alloc& e){
            std::cerr << "Error: bad_alloc" << e.what() << std::endl;
        }
    } 
}

template<typename T>
void BinaryTree<T>::attachLeft(const T& newItem) 
{ 
    if(this->root == nullptr)
        std::cerr << "Tree is empty" << std::endl;
    else if (this->root->leftChildPtr != nullptr){
        std::cerr << "Overwriting the left subtree is not possible" << std::endl;
    }
    else{
        root->leftChildPtr = new TreeNode<T>(newItem, nullptr, nullptr);
        if (root->leftChildPtr == nullptr)
            std::cerr << "Unable to allocate memory" << std::endl;
    }
}

template<typename T>
void BinaryTree<T>::attachRight(const T& newItem) 
{ 
    if(this->root == nullptr)
        std::cerr << "Tree is empty" << std::endl;
    else if (root->rightChildPtr != nullptr)     
        std::cerr << "Overwriting the left subtree is not possible " << std::endl;
    else
        root->rightChildPtr = new TreeNode<T>(newItem, nullptr, nullptr); 
            if (root->rightChildPtr == nullptr) 
                std::cerr << "Unable to allocate memory" << std::endl;
}

template<typename T>
void BinaryTree<T>::attachLeftSubtree(const BinaryTree<T>& leftTree) 
{ 
    if(this->root == nullptr)
        std::cerr << "Tree is empty" << std::endl; 
    else if (root->leftChildPtr != nullptr) 
        std::cerr << "Overwriting the left subtree is not possible " << std::endl;
    else { 
        root->leftChildPtr = leftTree.root; 
        leftTree.root = nullptr; 
    } 
}

template<typename T>
void BinaryTree<T>::attachRightSubtree(const BinaryTree<T>& rightTree) 
{ 
    if(this->root == nullptr)
        std::cerr << "Tree is empty" << std::endl;  
    else if (root->rightChildPtr != nullptr) 
        std::cerr << "Overwriting the left subtree is not possible " << std::endl;
    else { 
        root->rightChildPtr = rightTree.root; 
        rightTree.root = nullptr;
    }
}

template<typename T>
void BinaryTree<T>::detachLeftSubtree(BinaryTree<T>& leftTree) 
{ 
    if(this->root == nullptr)
        std::cerr << "Tree is empty" << std::endl;
    else { 
        leftTree = BinaryTree(root->leftChildPtr); 
        root->leftChildPtr = nullptr; 
    } 
}

template<typename T>
void BinaryTree<T>::detachRightSubtree(BinaryTree<T>& rightTree) 
{ 
    if(this->root == nullptr)
        std::cerr << "Tree is empty" << std::endl; 
    else { 
        rightTree = BinaryTree(root->rightChildPtr); 
        root->rightChildPtr = nullptr; 
    } 
}

template<typename T>
BinaryTree<T> BinaryTree<T>::getLeftSubtree() const 
{ 
    TreeNode<T> *subTreePtr; 
    if(this->root == nullptr) 
        return BinaryTree(); 
    else 
    { 
        copyTree(root->leftChildPtr, subTreePtr); 
        return BinaryTree(subTreePtr); 
    } 
} 

template<typename T>
BinaryTree<T> BinaryTree<T>::getRightSubtree() const 
{ 
    TreeNode<T> *subTreePtr; 
    if(this->root == nullptr) 
        return BinaryTree(); 
    else { 
        copyTree(root->rightChildPtr, subTreePtr); 
        return BinaryTree(subTreePtr); 
    } 
}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& rhs) 
{ 
    if (this != &rhs) { 
        destroyTree(root); 
        copyTree(rhs.root, root); 
    } 
    return *this; 
} 

template<typename T>
void BinaryTree<T>::copyTree(TreeNode<T> *treePtr, 
TreeNode<T> *& newTreePtr) const 
{ 
    if (treePtr != nullptr) 
    { 
        newTreePtr = new TreeNode<T>(treePtr->item, nullptr, nullptr); 
        if (newTreePtr == nullptr) 
            std::cerr << "Error: bad_alloc" << std::endl;
        copyTree(treePtr->leftChildPtr, newTreePtr->leftChildPtr); 
        copyTree(treePtr->rightChildPtr, newTreePtr->rightChildPtr); 
    } 
    else 
        newTreePtr = nullptr;
} 

template<typename T>
void BinaryTree<T>::destroyTree(TreeNode<T> *& treePtr) 
{ 
    if (treePtr != nullptr) 
    { 
        destroyTree(treePtr->leftChildPtr); 
        destroyTree(treePtr->rightChildPtr); 
        delete treePtr; 
        treePtr = nullptr; 
    }   
} 

template<typename T>
TreeNode<T> *BinaryTree<T>::rootPtr() const 
{ 
    return root; 
} 

template<typename T>
void BinaryTree<T>::setRootPtr(TreeNode<T> *newRoot) { 
    root = newRoot; 
} 

template<typename T>
void BinaryTree<T>::getChildPtrs(TreeNode<T> *nodePtr, 
        TreeNode<T> *& leftPtr, TreeNode<T> *& rightPtr) const 
{ 
    leftPtr = nodePtr->leftChildPtr; 
    rightPtr = nodePtr->rightChildPtr; 
} 

template<typename T>
void BinaryTree<T>::setChildPtrs(TreeNode<T> *nodePtr, 
                              TreeNode<T> *leftPtr, 
                              TreeNode<T> *rightPtr) 
{ 
    nodePtr->leftChildPtr = leftPtr; 
    nodePtr->rightChildPtr = rightPtr; 
} 

template<typename T>
void BinaryTree<T>::preorderTraverse(TreeNode<T> *treePtr, 
                            FunctionType<T> visit) 
{ 
    //рекурсивно
    if (treePtr != nullptr) 
    { 
        visit(treePtr->item); 
        preorderTraverse(treePtr->leftChildPtr, visit); 
        preorderTraverse(treePtr->rightChildPtr, visit); 
    } 
    //используя стек

    /*std::stack<TreeNode<T>*> nodeStack;
    if (treePtr != nullptr)
        nodeStack.push(treePtr);

    while (!nodeStack.empty())
    {
        TreeNode<T>* node = nodeStack.top();
        nodeStack.pop();
        visit(node->item);

        if (node->rightChildPtr != nullptr)
            nodeStack.push(node->rightChildPtr);

        if (node->leftChildPtr != nullptr)
            nodeStack.push(node->leftChildPtr);
    }
    */
}

template<typename T>
void BinaryTree<T>::inorderTraverse(TreeNode<T> *treePtr, FunctionType<T> visit) 
{ /*
    //рекурсивно
    if (treePtr != nullptr) {
        inorderTraverse(treePtr->leftChildPtr, visit); 
        visit(treePtr->item); 
        inorderTraverse(treePtr->rightChildPtr, visit); 
    } 
    //используя стек
*/
    std::stack<TreeNode<T>*> nodeStack;
    TreeNode<T>* current = treePtr;

    while (current != nullptr || !nodeStack.empty())
    {
        while (current != nullptr)
        {
            nodeStack.push(current);
            current = current->leftChildPtr;
        }

        current = nodeStack.top();
        nodeStack.pop();
        visit(current->item);
        current = current->rightChildPtr;
    }
    
} 

template<typename T>
void BinaryTree<T>::postorderTraverse(TreeNode<T> *treePtr, FunctionType<T> visit) 
{ 
    /*рекурсивно
    if (treePtr != nullptr) 
    { 
        postorderTraverse(treePtr->leftChildPtr, visit); 
        postorderTraverse(treePtr->rightChildPtr, visit);
        visit(treePtr->item); 
    } 
     */

    std::stack<TreeNode<T>*> nodeStack;
    TreeNode<T>* current = treePtr;
    TreeNode<T>* lastVisitedNode = nullptr;

    while (current != nullptr || !nodeStack.empty())
    {
        if (current != nullptr)
        {
            nodeStack.push(current);
            current = current->leftChildPtr;
        }
        else
        {
            TreeNode<T>* temp = nodeStack.top();

            if (temp->rightChildPtr != nullptr && temp->rightChildPtr != lastVisitedNode)
            {
                current = temp->rightChildPtr;  
            }
            else
            {
                visit(temp->item);
                lastVisitedNode = temp;
                nodeStack.pop();
            }
        }
    }
} 

template<typename T>
void display(T& anItem){
    std::cout << anItem << std::endl;
}


int main() 
{
    BinaryTree<int> myTree{911};
    myTree.attachLeft(9);
    myTree.attachRight(11);
    myTree.inorderTraverse(myTree.rootPtr(),display);
}




