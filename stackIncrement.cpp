#include <iostream>
#include <vector>

class Stack {
    std::vector<int> stack;
    int Size;
public:

    // constructor
    Stack(int size) {
        Size = size;
    }

    // push onto top of stack
    void push(int num) {
        if (stack.size() < Size) stack.push_back(num);
    }

    // removes top item and returns it
    int pop() {
        if (stack.size()) {
            int val = stack.back();
            stack.pop_back();
            return val;
        }
        return -1;
    }

    // Increments bottom i elements by k
    void increment(int i, int k) {
        for(int j = 0; j < std::min((int)k, i); j++){
            stack[j] += k;
        }
    }

    bool empty() {
        return !stack.size();
    }


};

int main(void) {

    Stack st(10);
    st.push(1), st.push(2), st.push(3);
    st.increment(2,3);

    while (!st.empty()) {
        std::cout << st.pop() << std::endl;
    }
    return 0;
}