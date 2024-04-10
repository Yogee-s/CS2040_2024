#ifndef TREE_H
#define TREE_H

#include <algorithm>
#include <cassert>
#include <functional>
#include <string>

using std::string;

template <typename T>
std::string my_to_string(const T& t) {
  return std::to_string(t);
}

template <>
std::string my_to_string(const std::string& t) {
  return "\"" + t + "\"";
}

template <typename T> struct Node {
  T element;
  int height;
  Node<T> *left;
  Node<T> *right;

  Node(T element)
      : element{element}, height{0}, left{nullptr}, right{nullptr} {}
  Node(T element, int height)
      : element{element}, height{height}, left{nullptr}, right{nullptr} {}
};

template <typename T> class Tree {
private:
  size_t m_size;
  Node<T> *m_root;

public:
  // Constructor
  Tree();

  // Rule of three:
  // If a class requires a user-defined destructor, a user-defined copy
  // constructor, or a user-defined copy assignment operator, it almost
  // certainly requires all three.

  // Destructor
  ~Tree();

  // Returns a pointer to the root
  Node<T> *root();

  // Checks whether the tree is empty
  bool empty() const;

  // Returns the number of elements
  size_t size() const;

  // Returns the height of the tree
  int height() const;

  // Inserts the specified element
  void insert(T element);

  // Checks whether the container contains the specified element
  bool contains(T element) const;

  // Returns the maximum element
  T max() const;

  // Returns the minimum element
  T min() const;

  // Returns the successor of the specified element
  T successor(T element);

  // Convert each element in the tree to string in pre-order.
  string pre_order();

  // Convert each element in the tree to string in order.
  string in_order();

  // Convert each element in the tree to string in post-order.
  string post_order();

  // Returns a string equivalent of the tree
  string to_string(bool with_height = true) const {
    return m_to_string(with_height, m_root, 0);
  }

private:
  string m_to_string(bool with_height, Node<T> *node, int ident) const {
    string res;
    if (node == nullptr) {
      return res;
    }
    if (node->right != nullptr) {
      res += m_to_string(with_height, node->right, ident + 2);
    }
    for (int i = 0; i < ident; i++) {
      res += " ";
    }
    res += my_to_string(node->element);
    if (with_height) {
      res += "(h=" + my_to_string(node->height) + ")";
    }
    res += "\n";
    if (node->left != nullptr) {
      res += m_to_string(with_height, node->left, ident + 2);
    }
    return res;
  }

  // Feel free to declare helper functions here, if necessary
 
  //helper function for destructor
  void deleteNodes(Node<T>* node) {
      if (node != nullptr) {
          deleteNodes(node->left);
          deleteNodes(node->right);
          delete(node);
      }
      m_size = 0;
      m_root = nullptr;
  }

  //updates node's height
  void update_height(Node<T>* node) {
      node->height = std::max(heightNode(node->left), heightNode(node->right)) + 1;
  }

  //return height of node
  int heightNode(Node<T>* node) {
      if (node == nullptr) {
          return -1;
      }
      return node->height;
  }

  //returns height difference
  int height_difference(Node<T>* node) {
      int left_side = node->left ? heightNode(node->left) : -1;
      int right_side = node->right ? heightNode(node->right) : -1;
      return (left_side - right_side);
  }

  Node<T>* left_rotate(Node<T>* node) {
      Node<T>* right_node = node->right;
      node->right = right_node->left;

      right_node->left = node;
      update_height(node);
      update_height(right_node);

      return right_node;
  }

  Node<T>* right_rotate(Node<T>* node) {
      Node<T>* left_node = node->left;
      node->left = left_node->right;

      left_node->right = node;
      update_height(node);
      update_height(left_node);

      return left_node;
  }

  Node<T>* insert_helper(Node<T>* node, T element) {
      if (element > node->element) {
          if (node->right) {
              node->right = insert_helper(node->right, element);
          }
          else {
              node->right = new Node<T>(element);
              m_size += 1;
          }
      }
      else if (element < node->element) {
          if (node->left) {
              node->left = insert_helper(node->left, element);
          }
          else {
              node->left = new Node<T>(element);
              m_size += 1;
          }
      }
      //else {
      //    return node;
      //}
      
      update_height(node);

      //Balancing
      //height diff = left_side - right_side
      //>1 equal left side heavy <-1 mean right side heavy
      if (height_difference(node) < -1) {
          //right heavy -> left rotate
          if (element > node->right->element) {
              node = left_rotate(node);     
          }
          else {
              node->right = right_rotate(node->right);
              node = left_rotate(node);
          }
      }
      else if (height_difference(node) > 1) {
          //left heavy -> right rotate
          if (element < node->left->element) {
              node = right_rotate(node);            
          }
          else {
              node->left = left_rotate(node->left);
              node = right_rotate(node);
          }
      }
      return node;
  }

  string in_order_helper(Node<T>* node) {
      Node<T>* current = node;
      return (node->left == nullptr ? "" : in_order_helper(node->left) + " ")
          + my_to_string(node->element)
          + (node->right == nullptr ? "" : " " + in_order_helper(node->right));
  }

  string post_order_helper(Node<T>* node) {
      Node<T>* current = node;
      return (node->left == nullptr ? "" : post_order_helper(node->left) + " ")
          + (node->right == nullptr ? "" : post_order_helper(node->right) + " ")
          + my_to_string(node->element);
  }

  };

// Constructor
template <typename T> Tree<T>::Tree() : m_root(nullptr) {
  // TODO: Implement this method
    m_size = 0;
}

// Destructor
template <typename T> Tree<T>::~Tree() {
  // TODO: Implement this method
    deleteNodes(m_root);
}

// Returns a pointer to the root
template <typename T> Node<T> *Tree<T>::root() {
  // TODO: Implement this method
  return m_root;
}

// Checks whether the tree is empty
template <typename T> bool Tree<T>::empty() const {
  // TODO: Implement this method
    if (m_size == 0 && m_root == nullptr) {
        return true;
    }
  return false;
}

// Returns the number of elements
template <typename T> size_t Tree<T>::size() const {
  // TODO: Implement this method
  return m_size;
}

// Returns the height of the tree
template <typename T> int Tree<T>::height() const {
  // TODO: Implement this method
    if (m_root == nullptr) {
        return -1;
    }
  return m_root->height;
}

// Inserts an element
template <typename T> void Tree<T>::insert(T element) {
  // TODO: Implement this method
    if (m_root != nullptr) {
        m_root = insert_helper(m_root, element);
    }
    else {
        m_size += 1;
        m_root = new Node<T>(element);
        update_height(m_root);
    }
}

// Checks whether the container contains the specified element
template <typename T> bool Tree<T>::contains(T element) const {
  // TODO: Implement this method
    Node<T>* current = m_root;
    while (current != nullptr) {
        if (element == current->element) {
            return true;
        }
        else if (element < current->element && current->left != nullptr) {
            current = current->left;
        }
        else if (element > current->element && current->right != nullptr) {
            current = current->right;
        }
        else {
            return false;
        }
    }
    return false;
}

// Returns the maximum element
template <typename T> T Tree<T>::max() const {
  // TODO: Implement this method
 /* throw std::runtime_error("not implemented");*/
    Node <T>* current = m_root;
    if (current == nullptr) {
        throw std::out_of_range("Tree is empty!");
    }
    while (current->right != nullptr) {
        current = current->right;
    }
    return current->element;
}

// Returns the minimum element
template <typename T> T Tree<T>::min() const {
  // TODO: Implement this method
  /*throw std::runtime_error("not implemented");*/
    Node <T>* current = m_root;
    if (current == nullptr) {
        throw std::out_of_range("Tree is empty!");
    }
    while (current->left != nullptr) {
        current = current->left;
    }
    return current->element;
}

// Returns the successor of the specified element
template <typename T> T Tree<T>::successor(T element) {
    // TODO: Implement this method
    /*throw std::runtime_error("not implemented");*/
    Node<T>* current = m_root;
    Node<T>* successor = nullptr;

    if (m_root == nullptr) {
        throw std::out_of_range("Tree is empty!");
    }

    if (element == this->max()) {
        throw std::out_of_range("Max element does not have a successor!");
    }

    while (current != nullptr) {
        if (element == current->element) {
            break;
        }
        else if (element > current->element) {
            current = current->right;
        }
        else if (element < current->element) {
            successor = current;
            current = current->left;
        }
    }

    if (current == nullptr) {
        return successor->element;
    }

    //element exist and it has a right child
    if (current->right != nullptr) {
        current = current->right;
        while (current->left != nullptr) {
            successor = current;
            current = current->left;
        }
        successor = current;
    }
    return successor->element;
}

template <typename T>
string _pre_order(Node<T> *node) {
  return my_to_string(node->element)
    + (node->left == nullptr ? "" : " " + _pre_order(node->left))
    + (node->right == nullptr ? "" : " " + _pre_order(node->right));
}

template <typename T>
string Tree<T>::pre_order() {
  if (m_root == nullptr) {
    return "";
  }
  return _pre_order(m_root);
}

template <typename T>
string Tree<T>::in_order() {
  // TODO: Implement this method
    if (m_root == nullptr) {
        return "";
    }
    return in_order_helper(m_root);

}

template <typename T>
string Tree<T>::post_order() {
  // TODO: Implement this method
    if (m_root == nullptr) {
        return "";
    }
    return post_order_helper(m_root);
}

#endif
