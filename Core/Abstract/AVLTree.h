//
// Created by Idham on 06/06/2025.
//

#ifndef AVLTREE_H
#define AVLTREE_H

#include<iostream>
#include<queue>

#include "../../Data/PatientData.h"
using namespace std;

namespace AVLTree {
    template <typename T>
    class AVL {
        class node {
        public:
            T data;         // menyimpan data di AVL
            node* left;     // menunjuk ke node kiri
            node* right;    // menunjuk ke node kanan
            int height;     // jalur maksimum dari node tertentu ke daun
        };
        node* root = NULL;  // node belum ada (kosong)

        // fungsi untuk menghitung nilai maksimum dari node tertentu
        int maxUtility(node* current)
        {
            if (current->right == NULL) return current->data;
            else return maxUtility(current->right);
        }

        // mengembalikan tinggi node
        int height(node* current) {
            if (current == NULL) return 0;
            return current->height;
        }

        // rotasi kanan jika tidak seimbang di kiri
        node* rightRotation(node* current) {
            node* new_node = current->left;
            current->left = new_node->right;
            new_node->right = current;
            current->height = 1 + max(height(current->left), height(current->right));
            new_node->height = 1 + max(height(new_node->left), height(new_node->right));
            return new_node;
        }

        // rotasi kiri jika tidak seimbang di kanan
        node* leftRotation(node* current) {
            node* new_node = current->right;
            current->right = new_node->left;
            new_node->left = current;
            current->height = 1 + max(height(current->left), height(current->right));
            new_node->height = 1 + max(height(new_node->left), height(new_node->right));
            return new_node;
        }

        // menampilkan nilai dengan metode In Order .. kiri - node - kanan
        void inOrderUtility(node* current) {
            if (current == NULL) {
                return;
            }
            inOrderUtility(current->left);
            cout << current->data << " ";
            inOrderUtility(current->right);
        }

        // menampilkan nilai dengan metode Pre Order .. node - kiri - kanan
        void preOrderUtility(node* current) {
            if (current == NULL) {
                return;
            }
            cout << current->data << " ";
            preOrderUtility(current->left);
            preOrderUtility(current->right);
        }

        // menampilkan nilai dengan metode Post Order .. kiri - kanan - node
        void postOrderUtility(node* current) {
            if (current == NULL) {
                return;
            }
            postOrderUtility(current->left);
            postOrderUtility(current->right);
            cout << current->data << " ";
        }

        // menambahkan node ke AVL Tree dengan hasil yang seimbang
        node* insertUtility(node* current, T value) {
            // jika AVL Tree kosong
            if (current == NULL) {
                node* new_node = new node;
                new_node->data = value;
                new_node->right = NULL;
                new_node->left = NULL;
                new_node->height = 1;
                current = new_node;
                return new_node;
            }

            // jika AVL Tree tidak kosong
            if (value < current->data) current->left = insertUtility(current->left, value);         // ke kiri paling bawah
            else if (value > current->data) current->right = insertUtility(current->right, value);  // ke kanan paling bawah
            current->height = 1 + max(height(current->left), height(current->right));          // hitung ulang tinggi node
            int balance = height(current->left) - height(current->right);                           // hitung keseimbangan dengan selisih sisi kiri dan kanan

            // jika tidak seimbang di kiri
            if (balance > 1) {
                // Kasus Kiri Kanan
                /*
                         5
                        /
                       3
                        \
                         4
                */
                if (value > current->left->data) {
                    current->left = leftRotation(current->left);
                    return rightRotation(current);
                }

                // Kasus Kiri Kiri
                /*
                         5
                        /
                       3
                      /
                     2
                */
                else {
                    return rightRotation(current);
                }
            }

            // jika tidak seimbang di kanan
            else if (balance < -1) {
                // Kasus Kanan Kiri
                /*
                      5
                       \
                        7
                       /
                      6
                */
                if (value < current->right->data) {
                    current->right = rightRotation(current->right);
                    return leftRotation(current);
                }

                // Kasus Kanan Kanan
                /*
                       5
                        \
                         6
                          \
                           7
                */
                else {
                    return leftRotation(current);
                }
            }
            return current;
        }

        // menghapus node dari AVL Tree dengan hasil yang seimbang
        node* removeUtility(node* current, T value) {
            // jika AVL Tree kosong
            if (current == NULL) {
                cout << "Tree kosong" << endl;
                return NULL;
            }

            // jika AVL Tree tidak kosong
            if (value < current->data) current->left = removeUtility(current->left, value);         // ke kiri paling bawah
            else if (value > current->data) current->right = removeUtility(current->right, value);  // ke kanan paling bawah

            // setelah menemukan nilai
            else {
                // jika node adalah daun
                if (current->left == NULL && current->right == NULL) {
                    delete current;
                    current = NULL;
                }

                // jika node memiliki 2 anak
                else if (current->left != NULL && current->right != NULL) {
                    int max = maxUtility(current->left);
                    current->data = max;
                    removeUtility(current->left,max);
                }

                // jika node hanya memiliki 1 anak
                else {
                    node* child=current;
                    if (current->right != NULL) {
                        current = current->right;
                    }
                    else {
                        current = current->left;
                    }
                    child->left = NULL;
                    child->right = NULL;
                    delete child;
                    child = NULL;
                }
            }

            current->height = 1 + max(height(current->left), height(current->right));   // hitung ulang tinggi node
            int balance = height(current->left) - height(current->right);                    // hitung keseimbangan dengan selisih sisi kiri dan kanan

            // jika tidak seimbang di kiri
            if (balance > 1) {
                // Kasus Kiri Kiri
                if (height(current->left) >= height(current->right)) {
                    return rightRotation(current);
                }

                // Kasus Kiri Kanan
                else {
                    current->left = leftRotation(current->left);
                    return rightRotation(current);
                }
            }

            // jika tidak seimbang di kanan
            else if (balance < -1) {
                // Kasus Kanan Kanan
                if (height(current->right) >= height(current->left)) {
                    return leftRotation(current);
                }

                // Kasus Kanan Kiri
                else {
                    current->right = rightRotation(current->right);
                    return leftRotation(current);
                }
            }
            return current;
        }

        // menampilkan tree dengan level order .. level per level
        void display_BFS()
        {
            if (root == NULL) cout << "Tree kosong" << endl;
            else {
                queue<node*> q;
                q.push(root);
                node* current;
                while (!q.empty()) {
                    current = q.front();
                    q.pop();
                    cout << current->data << " ";
                    if (current->left != NULL) q.push(current->left);
                    if (current->right != NULL)q.push(current->right);
                }
                cout << endl;
            }
        }

    public:
        // fungsi-fungsi ini akan muncul di main saat menggunakan objek
        void insert(T value) {
            root = insertUtility(root, value);
            Database::PatientLinear.push_back(value);
        }
        void remove(T value) {
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
    };

}

#endif //AVLTREE_H
