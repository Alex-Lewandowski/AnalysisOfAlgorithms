// huffcode.cpp  UNFINISHED
// Glenn G. Chappell
// 29 Nov 2015
//
// For CS 411/611 Fall 2015
// Assignment 6, Exercise A
// Source for class HuffCode
//
// Modified 11/22/17
// Chris Hartman
// For CS 411 Fall 2017


//Hints: You will need to write a Node class for the nodes of your Huffman tree. If you use C++
//        smart pointers, this will be nearly trivial, and probably doesn't even need a destructor.
//        You will also need to use an appropriate data structure to enable the step in the algorithm
//        that says "take the two smallest weight trees." C++ STL has an implementation of the obvious
//        choice, so you can use that, but there is also some explanation in the exercises at the end of
//        the chapter that leads to a faster algorithm (linear, rather than log-linear in alphabet size.)
//
//For your smart pointer, the obvious choice would be unique_ptr, but there are some issues that make that
//difficult in that the front() method of STL containers returns *by value* the front element, which is
//impossible for unique_ptrs because that makes a copy. You may therefore use shared_ptr, or figure out
//the method alluded to above so you can use std::move.
//
//Keep in mind that the instructions say "be efficient." In particular, you should not need to traverse
//the whole tree every time you want to encode a letter.

#include "huffcode.hpp"  // for class HuffCode declaration
#include <string>
using std::string;
#include <unordered_map>
using std::unordered_map;
#include <memory>
using std::shared_ptr;
using std::make_shared;
#include <utility>
using std::pair;
using std::make_pair;

void HuffCode::setWeights(const unordered_map<char, int> & theweights)
{
    // fill priority queue with Nodes containing char/weight pairs, sorted by weight
    for (auto a : theweights) {
        auto n = Node(make_pair(a.second, a.first));
        this->_queue.push(n);
    }
    if (size(_queue) == 0) {
        return;
    }

    // Create binary tree with char Nodes as leaves
    // After loop, _queue contains root
    while (size(_queue) > 1 ) {
        auto one = _queue.top();
        _queue.pop();
        auto two = _queue.top();
        _queue.pop();
        auto weight = one.get_data().first + two.get_data().first;
        auto node = Node(make_pair(weight, NULL),
                         make_shared<Node>(one),
                                 make_shared<Node>(two));
        this->_queue.push(node);
    }
    auto root = make_shared<Node>(_queue.top());
    auto code = write_huff_dict(root, "");
}


string HuffCode::write_huff_dict(shared_ptr<Node> node, const string & code) {
    if (node->get_left() == nullptr) {
        if (code == "") {
            _code_dict[node->get_data().second] = "0";
        } else {
            _code_dict[node->get_data().second] = code;
        }
        return code.substr(0, size(code) - 1);
    }
    auto cd = code;
    // cout << node->get_data().first << node->get_data().second << endl;
    cd = write_huff_dict(node->get_left(), cd + '0');
    cd = write_huff_dict(node->get_right(), cd + '1');
    return cd.substr(0, size(cd) - 1);
}

string HuffCode::lookup(char c) const {
    auto ans = _code_dict.find(c);
    return ans->second;
}

string HuffCode::encode(const string & text) const
{
    string code;
    for (auto c : text) {
        code.append(this->lookup(tolower(c)));
    }
    return code;
}


string HuffCode::decode(const string & codestr) const
{
    string ovaltine;
    if (this->_queue.empty()) {
        return "";
    }
    auto curr_node = make_shared<Node>(this->_queue.top());
    for (auto c : codestr) {
        if (c == '0'){
            curr_node = curr_node->get_left();
        }
        else {
            curr_node = curr_node->get_right();
        }
        if (curr_node->get_left() == nullptr) {
            auto chh = curr_node->get_data().second;
            ovaltine = ovaltine + chh;
//            ovaltine.append(reinterpret_cast<const char *>(curr_node->get_data().second));
            curr_node = make_shared<Node>(this->_queue.top());
        }

    }
    return ovaltine;  // DUMMY RETURN
}

std::shared_ptr<Node> Node::get_left() {
    return this->_left;
}

std::shared_ptr<Node> Node::get_right() {
    return this->_right;
}


