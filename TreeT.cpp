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

    Node* currN = root;

    while(currN != nullptr)
    {
        if(value > currN->value) //move to the right
        {
            if(currN->right == nullptr)//insertion point
            {
                currN->right = newNode;
                return;
            }
            currN = currN->right;
        }
        else if(value < currN->value){ // move to the left
            if(currN->left == nullptr)
            {
                currN->left = newNode;
                return;
            }

            currN = currN->left;
        }
        else //duplicate value;
        {
            delete newNode;
            numNodes--;
            return;
        }
    }
}

template<class T>
TreeT<T>::TreeT() {

}

template<class T>
TreeT<T>::~TreeT() {

}

template<class T>
TreeT<T> &TreeT<T>::operator=(const TreeT &otherTree) {
    return *this;
}

template<class T>
void TreeT<T>::Remove(T value) {

}

template<class T>
bool TreeT<T>::Contains(T value) {

    Node* rootPtr = root;

    while(rootPtr != nullptr)
    {
        if(rootPtr < value)
            root = root->left;
        else if(rootPtr > value)
            root = root->right;
        else
            return true;
    }

    return false;
}

template<class T>
int TreeT<T>::Size() {
    return 0;
}

template<class T>
void TreeT<T>::ResetIterator(Order traverseOrder) {

}

template<class T>
T TreeT<T>::GetNextItem() {
    return nullptr;
}

template<class T>
void TreeT<T>::DestroyTree(TreeT::Node *node) {

}

template<class T>
void TreeT<T>::RemoveHelper(TreeT::Node *&subtree, T value) {

}

template<class T>
void TreeT<T>::DeleteNode(TreeT::Node *&subtree) {

}

template<class T>
void TreeT<T>::GetPredecessor(TreeT::Node *curr, T &value) {

}

template<class T>
void TreeT<T>::CopyHelper(TreeT::Node *&thisTree, TreeT::Node *otherTree) {

}

template<class T>
void TreeT<T>::PlacePreOrder(TreeT::Node *node) {

}

template<class T>
void TreeT<T>::PlacePostOrder(TreeT::Node *node) {

}

template<class T>
void TreeT<T>::PlaceInOrder(TreeT::Node *node) {

}
