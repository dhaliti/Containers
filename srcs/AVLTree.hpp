#pragma once
#include <iostream>
#include <memory>
#include <algorithm>
#include "pair.hpp"

namespace ft
{
    template <class T, class Compare = std::less<typename T::first_type>, class Alloc = std::allocator<T> >
    class AVLTree
    {
    public:

/***********************************TYPEDEFS***********************************/

        typedef Alloc allocator_type;
        typedef T value_type;
        typedef typename T::first_type key_type;
        typedef typename T::second_type mapped_type;
        typedef Compare key_compare;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef T &reference;
        typedef T *pointer;


/*************************************NODE*************************************/

        struct Node
        {
            value_type  pair;
            Node        *parent;
            Node        *left;
            Node        *right;
            int         height;

            Node *min()
            {
                Node *cur = this;
                while (cur->left != nullptr)
                    cur = cur->left;
                return cur;
            }

            Node *max()
            {
                Node *cur = this;
                while (cur->right != nullptr)
                    cur = cur->right;
                return cur;
            }
        };

        class value_compare
			{
				friend class AVLTree;
				protected:
					Compare comp;
					value_compare (key_compare c) : comp(c) {}
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const {
						return comp(x.first, y.first); }
		};

        value_compare	value_comp() const {
			return value_compare(this->_comp);
		}

/****************************CONSTRUCTOR/DESTRUCTOR****************************/

        AVLTree(const key_compare &comp = key_compare(),
             const allocator_type &alloc = allocator_type())
            : _allocValue(alloc), _comp(comp)
        {
            _root = NULL;
            _size = 0;
            _end_node = _allocNode.allocate(1);
            set_end_node();
        }

        AVLTree(const AVLTree &x)
            : _allocValue(x._allocValue), _allocNode(x._allocNode), _comp(x._comp)
        {
            _root = NULL;
            _size = 0;
            _end_node = _allocNode.allocate(1);
            set_end_node();
            *this = x;
        }

        ~AVLTree()
        {
            clear();
            _allocNode.deallocate(_end_node, 1);
        }


        Node*       _last(void) const { set_end_node(); return _end_node; }
        Node*       root(void) const { return _root; }

        size_type   size(void) const { return _size; }
        size_type   max_size() const { return _allocNode.max_size(); }


        void        insert(value_type v) { _root = insert(_root, v); }
        void        erase(key_type key) { _root = erase(_root, key); }

        void clear()
        {
            while(_root)
                _root = erase(_root, _root->pair.first);
            set_end_node();
        }

        void swap(AVLTree &other)
        {
			Node* tmp = this->_root;
			this->_root = other._root;
			other._root = tmp;
        }

        size_type count(const key_type &key) const
        {
            Node* cur = _root;
            while (cur != nullptr)
            {
                if (_comp(key, cur->pair.first))
                    cur = cur->left;
                else if (_comp(cur->pair.first, key))
                    cur = cur->right;
                else
                    return 1;
            }
            return 0;
        }

        Node*       find(key_type key) const{ return searching(key); }

        key_compare key_comp() const { return _comp; }

        Node*     maxValueNode(Node *node1, Node *node2) const
        {
            if (node1 == nullptr)
                return node2;
            if (node2 == nullptr)
                return node1;
            if (_comp(node1->pair.first, node2->pair.first))
                return node2;
            return node1;
        }

        Node*       minimum(void) const {
			return (_size ? minValueNode(_root) : NULL);
		}

        Node*       maximum(void) const {
			return (_size ? maxValueNode(_root) : NULL);
		}

        allocator_type get_allocator() const {
			return _allocValue;
		}

        Node*       maximum(Node* node1, Node* node2) const {
			return (_size ? maxValueNode(node1, node2) : NULL);
		}

        void        prettyPrint() const {
			print_tree(this->_root);
		}

        template<class I>
        const I& max(const I& a, const I& b) { return (a < b) ? b : a; }

    private:
        int height(Node *N) const
        {
            if (N == NULL)
                return 0;
            return N->height;
        }

        Node *newNode(value_type pair, Node* parent)
        {
            Node* node = _allocNode.allocate(1);
            _allocValue.construct(&node->pair, pair);
            node->left = NULL;
            node->right = NULL;
            node->height = 1;
            node->parent = parent;
            return (node);
        }

        Node *rightRotate(Node *y)
        {
            Node *x = y->left;
            Node *T2 = x->right;

            x->parent = y->parent;
            y->parent = x;
            if (T2 != NULL)
                T2->parent = y;

            x->right = y;
            y->left = T2;

            y->height = height(y->left) < height(y->right) ? height(y->right) + 1 : height(y->left) + 1;
            x->height = height(x->left) < height(x->right) ? height(x->right) + 1 : height(x->left) + 1;
            return x;
        }

        Node *leftRotate(Node *x)
        {
            Node *y = x->right;
            Node *T2 = y->left;

            y->parent = x->parent;
            x->parent = y;
            if (T2 != NULL)
                T2->parent = x;

            y->left = x;
            x->right = T2;

            x->height = height(x->left) < height(x->right) ? height(x->right) + 1 : height(x->left) + 1;
            y->height = height(y->left) < height(y->right) ? height(y->right) + 1 : height(y->left) + 1;

            return y;
        }

        int getBalance(Node *x) const
        {
            if (x == NULL)
                return 0;
            return (height(x->left) - height(x->right));
        }

        Node* searching(key_type key) const
        {
            Node* cur = _root;
            while (cur != NULL)
            {
                if (_comp(key, cur->pair.first))
                    cur = cur->left;
                else if (_comp(cur->pair.first, key))
                    cur = cur->right;
                else
                    return cur;
            }
            return NULL;
        }
/*Reference: https://www.geeksforgeeks.org/avl-tree-set-1-insertion/?ref=gcse*/

        Node *insert(Node *node, value_type key, Node* parent = NULL)
        {
            if (node == NULL){
                _size++;
                return (newNode(key, parent));
            }

            if (_comp(key.first, node->pair.first))
                node->left = insert(node->left, key, node);
            else if (_comp(node->pair.first, key.first))
                node->right = insert(node->right, key, node);
            else
                return node;

            node->height = height(node->left) > height(node->right) ? height(node->left) : height(node->right);
            node->height++;
            int balance = getBalance(node);

            /* Left left case*/
            if (balance > 1 && _comp(key.first, node->left->pair.first))
                return rightRotate(node);

            /* Right right case*/
            if (balance < -1 && _comp(node->right->pair.first, key.first))
                return leftRotate(node);

            /* Left right case*/
            if (balance > 1 && _comp(node->left->pair.first, key.first))
            {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
            /* Right left case*/
            if (balance < -1 && _comp(key.first, node->right->pair.first))
            {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }

            set_end_node();
            return node;
        }

        Node *minValueNode(Node *node) const
        {
            if (!node)
                return node;
            Node *cur = node;
            while (cur->left != NULL)
                cur = cur->left;

            return cur;
        }

        Node *maxValueNode(Node *node) const
        {
            if (!node)
                return NULL;
            Node *cur = node;

            while (cur->right != NULL)
                cur = cur->right;

            return cur;
        }

/*Reference: https://www.geeksforgeeks.org/avl-tree-set-2-deletion/?ref=lbp*/
        Node *erase(Node *node, key_type key)
        {
            if (!node)
                return node;


            if (_comp(key, node->pair.first))
                node->left = erase(node->left, key);
            else if (_comp(node->pair.first, key))
                node->right = erase(node->right, key);

            else
            {
                if ((node->left == NULL) ||
                    (node->right == NULL))
                {
                    Node *temp = node->left ? node->left : node->right;
                    if (temp == NULL)
                    {
                        temp = node;
                        node = NULL;
                    }
                    else
                        *node = *temp;
                    if(node)
                        node->parent = temp->parent;
                    _allocValue.destroy(&temp->pair);
                    _allocNode.deallocate(temp, 1);
                    _size--;
                }
                else
                {
						Node *tmp = minValueNode(node->right);

						if (tmp != node->right)
						{
							tmp->right = node->right;
							node->right->parent = tmp;
						}
						if (tmp != node->left)
						{
							tmp->left = node->left;
							node->left->parent = tmp;
						}
						tmp->parent->left = 0;
						tmp->parent = node->parent;
						this->_allocValue.destroy(&node->pair);
						this->_allocNode.deallocate(node, 1);
                        _size--;
						node = tmp;
					}

            }

            if (node == NULL)
                return node;
            node->height = 1 + _comp(height(node->left), height(node->right));
            int balance = getBalance(node);

            /* Left left case*/
            if (balance > 1 && getBalance(node->left) >= 0)
                return rightRotate(node);

            /* Left right case*/
            if (balance > 1 && getBalance(node->left) < 0)
            {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }

            /* Right right case*/
            if (balance < -1 && getBalance(node->right) <= 0)
                return leftRotate(node);

            /* Right left case*/
            if (balance < -1 && getBalance(node->right) > 0)
            {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
            return node;
        }

        void set_end_node(void) const
        {
            if (_size)
                _end_node->parent = maxValueNode(_root);
            else
                _end_node->parent = nullptr;
            _end_node->left = _end_node->right = nullptr;
        }

/**********************************PRINT TREE**********************************/

        void preOrder(Node *_root)
        {
            if (_root != NULL)
            {
                std::cout << _root->key.first << " ";
                preOrder(_root->left);
                preOrder(_root->right);
            }
        }

        void padding(char c, int n) const
        {
            for (int i = 0; i < n; i++)
                std::cout << c;
        }

        void print_tree(Node *_root, int lvl = 0) const
        {
            if (_root == NULL)
            {
                padding('\t', lvl);
                std::cout << "~";
            }
            else
            {
                print_tree(_root->left, lvl + 1);
                padding('\t', lvl);
                std::cout << _root->pair.first << ":" << _root->pair.second << ";";

                if (_root->parent)
                    std::cout << _root->parent->pair.first;
                else
                    std::cout << "NULL";
                std::cout << std::endl;
                print_tree(_root->right, lvl + 1);
            }
            std::cout << std::endl;
        }

    private:
        Node*                   _root;
        Node*                   _end_node;
        allocator_type          _allocValue;
        std::allocator<Node>    _allocNode;
        size_type               _size;
        key_compare             _comp;
    };
}
