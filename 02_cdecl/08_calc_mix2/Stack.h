#ifndef __HANDY_STACK_H__
#define __HANDY_STACK_H__

#include <stack>
template <typename Data>
class Stack {
    std::stack<Data> stack;
public:
    Stack() {}
    void push(const Data &data) {
        stack.push(data);
    }
    Data pop() {
        Data popValue = stack.top();
        stack.pop();
        return popValue;
    }
    Data top() const {
        return stack.top();
    }
    inline bool is_empty() const { return stack.empty(); }
    inline int count() const { return stack.size(); }
};

#endif