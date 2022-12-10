#include "AVL.h"
#include <iostream>
using std::cout;
using std::endl;

int main() {

    cout << endl;

    cout << "AVL verification:" << endl;
    Node<int, int> node1(1,2);
    AVL<int, int> avl1(&node1);
    avl1.printTreeAVL();
    cout << endl;

    cout << "Insertion's verification:" << endl;
    Node<int, int> node11(1,2);
    Node<int, int> node12(2,4);
    Node<int, int> node13(3,6);
    Node<int, int> node14(4,8);
    Node<int, int> node15(5,10);
    Node<int, int> node16(6,12);
    Node<int, int> node17(7,14);
    AVL<int, int> avl11(&node11);
    avl11.insertNode(&node12);
    avl11.insertNode(&node13);
    avl11.insertNode(&node14);
    avl11.insertNode(&node15);
    avl11.insertNode(&node16);
    avl11.insertNode(&node17);
    avl11.printTreeAVL();
    cout << endl;

    cout << "Deletion's verification:" << endl;
    avl11.deleteNode(&node12);
    avl11.printTreeAVL();
    cout << endl;

    cout << "Node finding's verification:" << endl;
    cout << "The node found is: (" << avl11.findNode(3)->m_key << "," <<
    avl11.findNode(3)->m_data << ")" << endl;
    if (avl11.findNode(2) == nullptr) {
        cout << "It's a nullptr. Node does not exist." << endl;
    }
    cout << endl;

    cout << "Root's getter verification:" << endl;
    cout << "The root is: (" << avl11.getRoot()->m_key << "," <<
    avl11.getRoot()->m_data << ")" << endl;
    cout << endl;

    cout << "Null AVL verification:" << endl;
    AVL<int, int> avl21(nullptr);
    if (avl21.getRoot() == nullptr) {
        cout << "The AVL is empty" << endl;
    } else {
        avl21.printTreeAVL();
    }
    Node<int, int> node21(1,2);
    avl21.insertNode(&node21);
    avl21.printTreeAVL();
    cout << endl;

    return 0;
}
