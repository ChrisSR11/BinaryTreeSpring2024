#include "TreeT.h"

template<class T>
void TreeT<T>::Add(T value)
{
    Node* newNode = new Node;
    newNode->value = value;
    numNodes++;
    if(root == nullptr)
    {
        root = newNode;
        return;
    }

    Node* nodePtr = root;
    while(nodePtr != nullptr)
    {
        if(value < nodePtr->value)
        {
            if(nodePtr->left == nullptr)
            {
                nodePtr->left = newNode;
                return;
            }
            nodePtr = nodePtr->left;
        }
        else if(nodePtr->value < value)
        {
            if(nodePtr->right == nullptr)
            {
                nodePtr->right = newNode;
                return;
            }

            nodePtr = nodePtr->right;
        }
        else {
            delete newNode;
            numNodes--;
            return;
        }
    }
}

template<class T>
TreeT<T>::TreeT() {
    root = nullptr;
    numNodes = 0;
}

template<class T>
TreeT<T>::~TreeT() {
    DestroyTree(root);
}

template<class T>
TreeT<T> &TreeT<T>::operator=(const TreeT &otherTree) {
    if(this != &otherTree)
    {
        DestroyTree(root);
        CopyHelper(root, otherTree.root);
    }

    return *this;
}

template<class T>
void TreeT<T>::Remove(T value) {
    RemoveHelper(root, value);
    numNodes--;
}

template<class T>
bool TreeT<T>::Contains(T value) {
    if(root == nullptr)
        return false;

    Node* nodePtr = root;
    while(nodePtr != nullptr)
    {
        if(value < nodePtr->value)
            nodePtr = nodePtr->left;
        else if(nodePtr->value < value)
            nodePtr = nodePtr->right;
        else
            return true;
    }

    return false;

}

template<class T>
int TreeT<T>::Size() {
    return numNodes;
}

template<class T>
void TreeT<T>::ResetIterator(Order traverseOrder) {
    if(traverseOrder == PRE_ORDER)
        PlacePreOrder(root);
    else if(traverseOrder == IN_ORDER)
        PlaceInOrder(root);
    else
        PlacePreOrder(root);
}

template<class T>
T TreeT<T>::GetNextItem() {
    if(iterArr.empty())
        throw "Queue is empty";
    T data = iterArr.front();
    iterArr.pop();
    return data;
}

template<class T>
void TreeT<T>::DestroyTree(TreeT::Node *node) {
    if(node != nullptr)
    {
        DestroyTree(node->left);
        DestroyTree(node->right);
        delete node;
    }
}

template<class T>
void TreeT<T>::RemoveHelper(TreeT::Node *&subtree, T value) {
    if(subtree == nullptr)
        return;

    if(value < subtree->value)
        RemoveHelper(subtree->left, value);
    else if(subtree->value < value)
        RemoveHelper(subtree->right, value);
    else
        DeleteNode(subtree);
}

template<class T>   //since we are deleting a branch subTree must be *&
void TreeT<T>::DeleteNode(TreeT::Node *&subtree) {
    Node* tmp = subtree;    //tmp will be node to destroy
    //case #1: no children
    if(subtree->left == nullptr && subtree->right == nullptr)
    {
        delete subtree;
        subtree = nullptr;

    }   //case 2: one child
    else if(subtree->left == nullptr)
    {
        subtree = subtree->right;   //go to the node where there is a value
        delete tmp; //delete node
    }
    else if(subtree->right == nullptr)
    {
        subtree = subtree->left;    //go to the node on the left where there is a value
        delete tmp;     //delete the tmp node
    }
    else    //case 3: two children;
    {
        int data;
        GetPredecessor(subtree->left, data); //data will hold max in left subtree
        subtree->value = data;
        RemoveHelper(subtree->left, data);  //remove the max value used from left subtree
    }

}

template<class T>   //store the max value of subtree to value
void TreeT<T>::GetPredecessor(TreeT::Node *curr, T &value) {
    while(curr->right != nullptr)   //loop until the final rightmost node
        curr = curr->right;     //traverse

    value = curr->value;        //store max to value
}

template<class T>   //since we are adding branches thisTree is *&
void TreeT<T>::CopyHelper(TreeT::Node *&thisTree, TreeT::Node *otherTree) {
    if(otherTree == nullptr)
    {
        thisTree = nullptr;
        return;
    }

    thisTree = new Node;
    thisTree->value = otherTree->value;
    CopyHelper(thisTree->left, otherTree->left);
    CopyHelper(thisTree->right, otherTree->right);
}

template<class T>
void TreeT<T>::PlacePreOrder(TreeT::Node *node) {
    if(root != nullptr)
    {
        iterArr.push(node->value);
        PlacePreOrder(node->left);
        PlacePreOrder(node->right);
    }
}

template<class T>
void TreeT<T>::PlacePostOrder(TreeT::Node *node) {
    if(root != nullptr)
    {
        PlacePostOrder(node->left);
        PlacePostOrder(node->right);
        iterArr.push(node->val);
    }
}

template<class T>
void TreeT<T>::PlaceInOrder(TreeT::Node *node) {
    if(node != nullptr)
    {
        PlaceInOrder(node->left);
        iterArr.push(node->value);
        PlaceInOrder(node->right);
    }
}
