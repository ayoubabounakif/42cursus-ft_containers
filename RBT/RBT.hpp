/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabounak <aabounak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:19:07 by aabounak          #+#    #+#             */
/*   Updated: 2021/11/11 20:09:07 by aabounak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "../utility/pair.hpp"
# include "../utility/make_pair.hpp"
# include "../containers/vector.hpp"
# include <errno.h>

# define RED 1
# define BLACK 0
# define DOUBLE_BLACK 007

namespace ft {
    
    /* --       Description:
        RBT is a self-balancing BST in which each node contains \
        an extra bit for denoting the color of the node, either RED or BLACK */
    
    /* --       RBT Properties:
        1 - R/B Property: Every node is colored, either RED or BLACK.
        2 - Root Property: The ROOT is always BLACK.
        3 - Leaf Property: Every LEAF (NIL) is BLACK.
        4 - Red Property: If a RED node has CHILDREN, they will always be BLACK.
        5 - Depth Property: For each NODE, any SIMPLE PATH from this node to any \
        of its DESCENDANT LEAF has the same BLACK-DEPTH (The number of BLACK nodes) */

    /* --       How the RBT maintains SELF-BALANCING property:
        1 - The R/B color is meant for balancing the tree.
        2 - The limitations put on the NODE COLORS ensure that any SIMPLE PATH \
        from the ROOT to a LEAF is not more than twice as long as any other such PATH. \
        It helps in maintaining the self-balancing property of the RBT. */

    template < class T, class Compare = std::less<T> , class Alloc = std::allocator<T> >
    class RBT
    {
        public:
        
            typedef             T                  value_type;
            typedef             Compare            key_compare;
            typedef             Alloc              allocator_type;
            
            struct Node {
                value_type  * data;
                Node        * parent;
                Node        * left;
                Node        * right;
                short         color;      
            };           

            typedef typename    Alloc::template rebind<Node>::other   rebind_allocator;
             
            // Constructor
            RBT( void ) {
                this->_root = nullptr;
            }

            /* void    preOrder( Node * root ) {
                if (root == nullptr) { return ; }
                std::cout << *root->data << " ";
                preOrder(root->left);
                preOrder(root->right);
            }

            void    inOrder( Node * root ) {
                if (root == nullptr) { return ; }
                inOrder(root->left);
                std::cout << *root->data << " ";
                inOrder(root->right);
            }

            void    postOrder( Node * root ) {
                if (root == nullptr) { return ; }
                postOrder(root->left);
                postOrder(root->right);
                std::cout << *root->data << " ";
            } */

            Node *  getRoot( void ) {
                return this->_root;
            }

            /* --   Insertion of an element into a RBT:
                While inserting a new node, the ney node is always inserted as a RED node.
                After insertion of a new node, if the tree is violating the properties of the RBT
                we do the following operations:
                    1 - Recolor
                    2 - Rotation */
            void    insert( value_type key ) {
                Node * tmpNode = newNode(key);
                this->_root = this->BST_insert(this->_root, tmpNode);
                if (tmpNode->parent == nullptr)
                {
                    tmpNode->parent->color = BLACK;
                    return ;
                }
                if (tmpNode->parent->parent == nullptr)
                    return ;
                fixInsertionViolation(this->_root, tmpNode);
                return ;
            }

            void    deleteNode( value_type key ) {
                BST_delete(this->_root, key);
                return ;
            }

            void    printTree() {
                if (_root) {
                    printHelper(this->_root, nullptr, false);
                }
            }

            /* Node *  minimum( Node * node ) {
                while (getRoot()->left != nullptr) { node = node->left; }
                return node;
            }

            Node *  maximum( Node * node ) {
                while (getRoot()->right != nullptr) { node = node->right; }
                return node;
            } */
            

        private:
            Node    *           _root;
            key_compare         _comp;
            allocator_type      _alloc;
            rebind_allocator    _nodeAlloc;

            /* --   Why newly inserted nodes are always RED in a RBT?
                This is because insertion a RED node does not vioolate the depth property of a RBT.
                If you attack a RED node to another RED node, then the rule is violated \
                but it is easier to fix this problem than the problem introduced by violating the DEPTH property. */
            Node *  newNode( value_type key ) {
                Node  * nouveauNode;
                nouveauNode = _nodeAlloc.allocate(1);
                nouveauNode->data = _alloc.allocate(1);
                *(nouveauNode->data) = key;
                nouveauNode->parent = nouveauNode->left = nouveauNode->right = nullptr;
                nouveauNode->color = RED;
                return nouveauNode;
            }

            
            Node *  BST_insert( Node *root, Node *z ) {
                if (root == nullptr) { return z; }
                if (*root->data < *z->data) {
                    root->right = BST_insert(root->right, z);
                    root->right->parent = root;
                }
                else if (*root->data > *z->data) {
                    root->left = BST_insert(root->left, z);
                    root->left->parent = root;
                }
                return root;
            }


            /* // Util method for deletion
            Node * minValueNode( Node * node ) {
                Node * current = node;

                while (current && current->left)
                    current = current->left;
                return current;
            }

            // Deletion of a node
            Node *  BST_delete( Node *root, value_type key ) {
                // Base case
                if (root == nullptr) { return root; }

                // If the key to be deleted is smaller
                // than the root's key, then it lies in left subtree
                if (key < *root->data) {
                    root->left = BST_delete(root->left, key);
                    return root;
                }
                else if (key > *root->data)
                {
                    root->right = BST_delete(root->right, key);
                    return root;
                }
                if (root->left == nullptr) {
                    Node * temp = root->right;
                    _nodeAlloc.deallocate(root, 1);
                    return temp;
                }
                else if (root->right == nullptr) {
                    Node * temp = root->left;
                    _nodeAlloc.deallocate(root, 1);
                    return temp;
                }

                else {
                    
                    Node * successorParent = root;
                    Node * successor = root->right;
                    while (successor->left != nullptr) {
                        successorParent = successor;
                        successor = successor->left;
                    }

                    if (successorParent != root)
                        successorParent->left = successor->right;
                    else
                        successorParent->right = successor->right;
                    *root->data = *successor->data;
                    _nodeAlloc.deallocate(successor, 1);
                    return root;
                }        
            } */


            /* ---------------------- Operations ---------------------- */
                /* --- Subtrees rotations // */
            
            /* -- Left Rotation:
                The arrangement of the nodes on the right is transformed into the arrangements on the left node
                -- Algorithm:
                    1 - If Y has a left subtree, assign X as the parent of the left substree of Y.
                    2 - If the parent of X is NULL, make Y as the root of the tree. 
                    3 - Else if X is the left child of its parent P, make Y as the left child of P. 
                    4 - Else assign Y as the right child of P. 
                    5 - Make Y as the parent of X. */
            void    rotateLeft( Node *& root, Node *& x ) {
                Node * y = x->right; x->right = y->left;
                if (y->left != nullptr) y->left->parent = x;
                y->parent = x->parent;
                if (x->parent == nullptr) root = y;
                else if (x == x->parent->left) x->parent->left = y;
                else x->parent->right = y;
                y->left = x; x->parent = y;
            }

            /* -- Right Rotation:
                The arrangement of the nodes on the left is transformed into the arrangements on the right node
                -- Algorithm:
                    1 - If X has a right subtree, assign Y as the parent of the right subtree of X. 
                    2 - If the parent of Y is NULL, make  as the root of the tree. 
                    3 - Else if Y is the right child of its parent P, make X as the right child of P. 
                    4 - Else assign X as the left cchild of P. 
                    5 - Make X as the parent of Y. */
            void    rotateRight( Node *&root, Node *&x )
            {
                Node * y = x->left; x->left = y->right;
                if (y->right != nullptr) y->right->parent = x;
                y->parent = x->parent;
                if (x->parent == nullptr) root = y;
                else if (x == x->parent->right) x->parent->right = y;
                else x->parent->left = y;
                y->right = x; x->parent = y;
            }

            /* -- Insertion Violation Fix:
                This function is used for maintaining the property of a RBT \ 
                if the insertion of a newNode violates this property. 
                -- Alorithm:
                    1 - Do the following suite of instructions while the parent of a newNode <pt> is RED.
                    2 - If <pt> is the left child of grandParent. */

            void    fixInsertionViolation( Node *&root, Node *&pt ) {
                Node * parent = nullptr;
                Node * grandParent = nullptr;
            }
            // void    fixInsertionViolation(Node *&root, Node *&pt)
            // {
            //     Node *parent_pt = nullptr;
            //     Node *grand_parent_pt = nullptr;
            
            //     while ((pt != root) && (pt->color != BLACK) &&
            //         (pt->parent->color == RED))
            //     {
            
            //         parent_pt = pt->parent;
            //         grand_parent_pt = pt->parent->parent;
            
            //         /*  Case : A
            //             Parent of pt is left child
            //             of Grand-parent of pt */
            //         if (parent_pt == grand_parent_pt->left)
            //         {
            //             Node *uncle_pt = grand_parent_pt->right;
            
            //             /* Case : 1
            //             The uncle of pt is also red
            //             Only Recoloring required */
            //             if (uncle_pt != nullptr && uncle_pt->color ==
            //                                                 RED)
            //             {
            //                 grand_parent_pt->color = RED;
            //                 parent_pt->color = BLACK;
            //                 uncle_pt->color = BLACK;
            //                 pt = grand_parent_pt;
            //             }
            
            //             else
            //             {
            //                 /* Case : 2
            //                 pt is right child of its parent
            //                 Left-rotation required */
            //                 if (pt == parent_pt->right)
            //                 {
            //                     rotateLeft(root, parent_pt);
            //                     pt = parent_pt;
            //                     parent_pt = pt->parent;
            //                 }
            
            //                 /* Case : 3
            //                 pt is left child of its parent
            //                 Right-rotation required */
            //                 rotateRight(root, grand_parent_pt);
            //                 std::swap(parent_pt->color,
            //                         grand_parent_pt->color);
            //                 pt = parent_pt;
            //             }
            //         }
            
            //         /* Case : B
            //         Parent of pt is right child
            //         of Grand-parent of pt */
            //         else
            //         {
            //             Node *uncle_pt = grand_parent_pt->left;
            
            //             /*  Case : 1
            //                 The uncle of pt is also red
            //                 Only Recoloring required */
            //             if ((uncle_pt != nullptr) && (uncle_pt->color ==
            //                                                     RED))
            //             {
            //                 grand_parent_pt->color = RED;
            //                 parent_pt->color = BLACK;
            //                 uncle_pt->color = BLACK;
            //                 pt = grand_parent_pt;
            //             }
            //             else
            //             {
            //                 /* Case : 2
            //                 pt is left child of its parent
            //                 Right-rotation required */
            //                 if (pt == parent_pt->left)
            //                 {
            //                     rotateRight(root, parent_pt);
            //                     pt = parent_pt;
            //                     parent_pt = pt->parent;
            //                 }
            
            //                 /* Case : 3
            //                 pt is right child of its parent
            //                 Left-rotation required */
            //                 rotateLeft(root, grand_parent_pt);
            //                 std::swap(parent_pt->color,
            //                         grand_parent_pt->color);
            //                 pt = parent_pt;
            //             }
            //         }
            //     }
            //     root->color = BLACK;
            // }


                    /* ---------- | Recursive print of a "RBT" | ---------- */

            struct Trunk {
                Trunk *prev;
                std::string str;
                Trunk( Trunk *prev, std::string str ) { this->prev = prev; this->str = str; }
            };

            // Helper function to print branches of the binary tree
            void showTrunks(Trunk *p) {
                if (p == nullptr) { return ; }
                showTrunks(p->prev);
                std::cout << p->str;
            }
            
            void printHelper( Node* root, Trunk *prev, bool isLeft ) {
                if (root == nullptr) { return; }
                std::string prev_str = "    ";
                Trunk *trunk = new Trunk(prev, prev_str);
                printHelper(root->right, trunk, true);
                if (!prev) { trunk->str = "——— "; }
                else if (isLeft) { trunk->str = " .——— "; prev_str = "   |"; }
                else { trunk->str = " `——— "; prev->str = prev_str; }
                showTrunks(trunk);
                std::string sColor = root->color ? "R" : "B";
                std::cout << *root->data << "(" << sColor <<  ")" << std::endl;
                if (prev) { prev->str = prev_str; }
                trunk->str = "   |";
                printHelper(root->left, trunk, false);
            }
    }; 
}
