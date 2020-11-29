// huffcode.hpp  UNFINISHED
// Glenn G. Chappell
// 29 Nov 2015
//
// For CS 411/611 Fall 2015
// Assignment 6, Exercise A
// Header for class HuffCode
//
// Modified 11/22/17
// Chris Hartman
// For CS 411 Fall 2017


#ifndef FILE_HUFFCODE_H_INCLUDED
#define FILE_HUFFCODE_H_INCLUDED

#include <string>
#include <unordered_map>
#include <queue>
#include <utility>
#include <memory>
#include <functional>

//template <typename T>
//class  Node
//{
//public:
//    Node() : _data(T()) {}
//    explicit Node(const T & value) : _data(value) {}
//
//    void setLeft(const Node & left);
//    void setRight(const Node & right);
//
//    [[nodiscard]] T get_data() const {
//        return this->_data;
//    }
//    std::shared_ptr<Node<T>> get_left();
//    std::shared_ptr<Node<T>> get_right();
//
//    bool operator >(const Node<std::pair<int, char>> & other) {
//        return this->_data.first > other.get_data().first;
//    }
//
//
//private:
//    T _data;
//    std::shared_ptr<Node<T>> _left;
//    std::shared_ptr<Node<T>> _right;
//};

class  Node
{
public:
    Node() : _data(std::pair<int, char>()) {}
    explicit Node(std::pair<int, char> value) : _data(std::move(value)), _left(nullptr), _right(nullptr){}
    explicit Node(std::pair<int, char> value,
                  std::shared_ptr<Node> left,
                  std::shared_ptr<Node> right) :
                  _data(std::move(value)), _left(left), _right(right) {}


    void setLeft(const Node & left);
    void setRight(const Node & right);

    [[nodiscard]] std::pair<int, char> get_data() const {
        return this->_data;
    }
    std::shared_ptr<Node> get_left();
    std::shared_ptr<Node> get_right();

    bool operator >(const Node & other) const {
        return this->_data.first > other.get_data().first;
    }

private:
    std::pair<int, char> _data;
    std::shared_ptr<Node> _left;
    std::shared_ptr<Node> _right;
};


// Class HuffCode
// Encoding & decoding using a Huffman code
class HuffCode {

// ***** HuffCode: ctors, dctor, op= *****
public:

    // Compiler-generated default ctor, copy ctor, copy =, dctor used

// ***** HuffCode: general public functions *****
public:

    void setWeights(const std::unordered_map<char, int> & theweights);

    std::string write_huff_dict(std::shared_ptr<Node> node,const std::string & code);

    std::string lookup(char c) const;

    std::string encode(const std::string & text) const;

    std::string decode(const std::string & codestr) const;

// ***** HuffCode: data members *****
private:
    std::priority_queue<Node, std::vector<Node>, std::greater<>> _queue;
    std::unordered_map<char, std::string> _code_dict;

};  // End class HuffCode



#endif //#ifndef FILE_HUFFCODE_H_INCLUDED

