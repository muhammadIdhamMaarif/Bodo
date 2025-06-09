#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <queue>
#include "../PersonData/Patient.h"

using namespace std;

namespace AVLTree {
    class AVL {
        struct node {
            Data::Patient data;
            node* left;
            node* right;
            int height;
        };
        node* root = nullptr;

        std::string toLower(std::string s) {
            std::transform(s.begin(), s.end(), s.begin(), ::tolower);
            return s;
        }

        std::string trim(const std::string& str) {
            size_t first = str.find_first_not_of(' ');
            if (first == std::string::npos) {
                return ""; // String is all whitespace
            }
            size_t last = str.find_last_not_of(' ');
            return str.substr(first, (last - first + 1));
        }

        int height(node* n) {
            return n ? n->height : 0;
        }

        int getBalance(node* n) {
            return n ? height(n->left) - height(n->right) : 0;
        }

        node* rightRotation(node* y) {
            node* x = y->left;
            node* T2 = x->right;

            x->right = y;
            y->left = T2;

            y->height = 1 + max(height(y->left), height(y->right));
            x->height = 1 + max(height(x->left), height(x->right));

            return x;
        }

        node* leftRotation(node* x) {
            node* y = x->right;
            node* T2 = y->left;

            y->left = x;
            x->right = T2;

            x->height = 1 + max(height(x->left), height(x->right));
            y->height = 1 + max(height(y->left), height(y->right));

            return y;
        }

        Data::Patient maxUtility(node* current) {
            if (current->right == nullptr)
                return current->data;
            return maxUtility(current->right);
        }

        node* insertUtility(node* current, const Data::Patient& value) {
            if (!current) {
                node* newNode = new node{value, nullptr, nullptr, 1};
                return newNode;
            }

            if (value < current->data)
                current->left = insertUtility(current->left, value);
            else if (value > current->data)
                current->right = insertUtility(current->right, value);
            else
                return current; // Duplicate, ignore

            current->height = 1 + max(height(current->left), height(current->right));
            int balance = getBalance(current);

            // Left heavy
            if (balance > 1) {
                if (value > current->left->data)
                    current->left = leftRotation(current->left);
                return rightRotation(current);
            }

            // Right heavy
            if (balance < -1) {
                if (value < current->right->data)
                    current->right = rightRotation(current->right);
                return leftRotation(current);
            }

            return current;
        }

        node* removeUtility(node* current, const Data::Patient& value) {
            if (!current) return nullptr;

            if (value < current->data)
                current->left = removeUtility(current->left, value);
            else if (value > current->data)
                current->right = removeUtility(current->right, value);
            else {
                if (!current->left || !current->right) {
                    node* temp = current->left ? current->left : current->right;
                    delete current;
                    return temp;
                }

                Data::Patient maxVal = maxUtility(current->left);
                current->data = maxVal;
                current->left = removeUtility(current->left, maxVal);
            }

            current->height = 1 + max(height(current->left), height(current->right));
            int balance = getBalance(current);

            if (balance > 1) {
                if (getBalance(current->left) < 0)
                    current->left = leftRotation(current->left);
                return rightRotation(current);
            }

            if (balance < -1) {
                if (getBalance(current->right) > 0)
                    current->right = rightRotation(current->right);
                return leftRotation(current);
            }

            return current;
        }

        void inOrderUtility(node* current) {
            if (!current) return;
            inOrderUtility(current->left);
            cout << current->data.GetNama() << " ";
            inOrderUtility(current->right);
        }

        void preOrderUtility(node* current) {
            if (!current) return;
            cout << current->data.GetNama() << " ";
            preOrderUtility(current->left);
            preOrderUtility(current->right);
        }

        void postOrderUtility(node* current) {
            if (!current) return;
            postOrderUtility(current->left);
            postOrderUtility(current->right);
            cout << current->data.GetNama() << " ";
        }

        Data::Patient* searchByName(node* current, const std::string& name) {
            if (!current) return nullptr;
            if (name == toLower(current->data.GetNama())) return &(current->data);
            if (name < toLower(current->data.GetNama())) return searchByName(current->left, name);
            return searchByName(current->right, name);
        }

        void display_BFS() {
            if (!root) {
                cout << "Tree kosong" << endl;
                return;
            }
            queue<node*> q;
            q.push(root);
            while (!q.empty()) {
                node* current = q.front(); q.pop();
                cout << current->data.GetNama() << " ";
                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
            cout << endl;
        }

    public:
        void insert(const Data::Patient& value) {
            root = insertUtility(root, value);
        }

        void remove(const Data::Patient& value) {
            root = removeUtility(root, value);
        }

        void inorder() {
            inOrderUtility(root);
            cout << endl;
        }

        void preOrder() {
            preOrderUtility(root);
            cout << endl;
        }

        void postOrder() {
            postOrderUtility(root);
            cout << endl;
        }

        void levelOrder() {
            display_BFS();
        }

        Data::Patient* Search(const string& name) {
            return searchByName(root, trim(toLower(name)));
        }
    };
}

#endif // AVLTREE_H
