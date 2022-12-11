#ifndef AVL_H
#define AVL_H

#include <iostream>

template <class K, class D>
class Node {
    public:
        // node constructor
        Node(K key, D data)
        :
        m_key(key),
        m_data(data),
        m_left(nullptr),
        m_right(nullptr),
        m_height(1)
        {}

        // Maximal int
        int maxInt(int a, int b) {
            return (a > b) ? a : b;
        }

        // Calculate height
        int heightGetter() {
            if (this == nullptr) {
                return 0;
            }
            return m_height;
        }

        // Calculate the balance value of a node
        int balanceFactor() {
            if (this == nullptr) {
                return 0;
            }
            return (m_left->heightGetter()-m_right->heightGetter());
        }

        // Rotate right
        Node<K,D> *rightRotate(Node<K,D> *originalRoot) {
            Node<K,D> *newRoot = originalRoot->m_left;
            Node<K,D> *subtree = newRoot->m_right;
            newRoot->m_right = originalRoot;
            originalRoot->m_left = subtree;
            originalRoot->m_height = maxInt(
                originalRoot->m_left->heightGetter(),
                originalRoot->m_right->heightGetter()) +1;
            newRoot->m_height = maxInt(newRoot->m_left->heightGetter(),
            newRoot->m_right->heightGetter()) +1;
            return newRoot;
        }

        // Rotate left
        Node<K,D> *leftRotate(Node<K,D> *originalRoot) {
            Node<K,D> *newRoot = originalRoot->m_right;
            Node<K,D> *subtree = newRoot->m_left;
            newRoot->m_left = originalRoot;
            originalRoot->m_right = subtree;
            originalRoot->m_height = maxInt(
                originalRoot->m_left->heightGetter(),
                originalRoot->m_right->heightGetter()) +1;
            newRoot->m_height = maxInt(newRoot->m_left->heightGetter(),
            newRoot->m_right->heightGetter()) +1;
            return newRoot;
        }

        // Insert a node
        Node<K,D> *insertNodeNode(Node<K,D> *root, Node<K,D> *node) {
            // Find the correct location and insert the node
            if (root == nullptr) {
                return new Node<K,D>(node->m_key, node->m_data);
            }
            if (node->m_key < root->m_key) {
                root->m_left = insertNodeNode(root->m_left, node);
            }
            else if (node->m_key > root->m_key) {
                root->m_right = insertNodeNode(root->m_right, node);
            }
            else { // if (node->m_key == root->m_key)
                return root;
            }
            // Update the balance factor of each node and balance the tree
            root->m_height = maxInt(root->m_left->heightGetter(),
            root->m_right->heightGetter()) +1;
            int balanceFactorValue = root->balanceFactor();
            if (balanceFactorValue >= 2) {
                if (node->m_key < root->m_left->m_key) {
                    return rightRotate(root);
                } else if (node->m_key > root->m_left->m_key) {
                    root->m_left = leftRotate(root->m_left);
                    return rightRotate(root);
                }
            }
            if (balanceFactorValue <= -2) {
                if (node->m_key > root->m_right->m_key) {
                    return leftRotate(root);
                } else if (node->m_key < root->m_right->m_key) {
                    root->m_right = rightRotate(root->m_right);
                    return leftRotate(root);
                }
            }
            return root;
        }

        // Node with minimum value
        Node<K,D> *leftmostNode(Node<K,D> *node) {
            Node<K,D> *current = node;
            while (current->m_left != nullptr)
                current = current->m_left;
            return current;
        }

        // Delete a node
        Node<K,D> *deleteNodeNode(Node<K,D> *root, K key) {
            // Find node
            if (root == nullptr) {
                return root;
            }
            if (key < root->m_key) {
                root->m_left = deleteNodeNode(root->m_left, key);
            }
            else if (key > root->m_key) {
                root->m_right = deleteNodeNode(root->m_right, key);
            }
            else { // delete node
                if ((root->m_left == nullptr) ||
                (root->m_right == nullptr)) {
                    Node<K,D> *temp;
                    if (root->m_left == nullptr) {
                        if (root->m_right == nullptr) { // both false
                            temp = root;
                            root = nullptr;
                        } else { // right=true
                            temp = root->m_right;
                            *root = *temp;
                        }
                    } else { // left=true
                        temp = root->m_left;
                        *root = *temp;
                    }
                    free(temp);
                } else { // both true
                    Node<K,D> *temp = // next value in inorder
                    leftmostNode(root->m_right);
                    root->m_key = temp->m_key;
                    root->m_data = temp->m_data;
                    root->m_right = deleteNodeNode(root->m_right, temp->m_key);
                }
            }

            // After the deletion
            if (root == nullptr) {
                return root;
            }

            // Update balance factor for all nodes and balance the tree
            root->m_height = maxInt(root->m_left->heightGetter(),
            root->m_right->heightGetter()) + 1;
            if (root->balanceFactor() >= 2) {
                if (root->m_left->balanceFactor() >= 0) {
                    root->m_left = leftRotate(root->m_left); //LL rotation
                    return leftRotate(root);
                } else { // if (root->m_left->balanceFactor() <= -1)
                    root->m_left = leftRotate(root->m_left); //LR rotation
                    return rightRotate(root);
                }
            }
            if (root->balanceFactor() <= -2) {
                if (root->m_right->balanceFactor() <= 0) {
                    root->m_right = // RR rotation
                    rightRotate(root->m_right);
                    return rightRotate(root);
                } else { // if (root->m_right->balanceFactor() >= 1)
                    root->m_right =
                    rightRotate(root->m_right); // RL rotation
                    return leftRotate(root);
                }
            }
            return root;
        }

        // Print tree
        void printTreeNode(Node<K,D> *root, bool lastChild = true,
        std::string indent = "") {
            if (root != nullptr) {
                std::cout << indent;
                if (lastChild) {
                    std::cout << "R--------";
                    indent += "       ";
                } else {
                    std::cout << "L--------";
                    indent += "|      ";
                }
                std::cout << "(" << root->m_key << "," << root->m_data <<
                ")" << std::endl;
                this->printTreeNode(root->m_left, false, indent);
                this->printTreeNode(root->m_right, true, indent);
            }
        }

        // Find a node
        Node<K,D> *findNodeNode(Node<K,D> *root, K key) {
            // Find the node
            Node<K,D> *res = nullptr;
            if (root == nullptr) {
                return res;
            }
            else if (key < root->m_key) {
                res = findNodeNode(root->m_left, key);
            }
            else if (key > root->m_key) {
                res = findNodeNode(root->m_right, key);
            }
            else { // if (key == root->m_key)
                res = root;
            }
            return res;
        }

        void deleteAVLNode(Node<K,D>* root) {
            if (root == nullptr) {
                return;
            }
            deleteAVLNode(root->m_left);
            deleteAVLNode(root->m_right);
            delete root;
        }


        K m_key;
        D m_data;
        Node<K,D> *m_left;
        Node<K,D> *m_right;
        int m_height;
};

template <class K, class D>
class AVL {
    public:
        // AVL constructor
        AVL(Node<K,D>* root = nullptr)
        :
        m_root(root)
        {}

        // Call node insertion
        void insertNode(Node<K,D>* node) {
            m_root = m_root->insertNodeNode(m_root, node);
        }

        // Call node deletion
        void deleteNode(K key) {
            m_root = m_root->deleteNodeNode(m_root, key);
        }

        // Call function of tree's printing
        void printTreeAVL() {
            m_root->printTreeNode(m_root);
        }

        // Call node finding
        Node<K,D> *findNode(K key) {
            return m_root->findNodeNode(m_root, key);
        }

        // Return tree's root
        Node<K,D> *getRoot() {
            return m_root;
        }

        // delete AVL
        void deleteAVL() {
            m_root->deleteAVLNode(m_root);
            m_root = nullptr;
        }

        // Node with minimum value
        Node<K,D> *smallestNode() {
            Node<K,D> *current = m_root;
            while (current->m_left != nullptr) {
                current = current->m_left;
            }
            return current;
        }

        // Node with maximum value
        Node<K,D> *biggestNode() {
            Node<K,D> *current = m_root;
            while (current->m_right != nullptr) {
                current = current->m_left;
            }
            return current;
        }

    private:
        Node<K,D> *m_root;
};

#endif /* AVL_H */
