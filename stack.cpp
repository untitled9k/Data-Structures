#include <iostream>
#include <stdexcept>
#include <cstdlib>

int const SIZE = 1000;

template <class T>
class Stack {
private:
    T* arr;
    int top;
    int capacity;
public:
    Stack(int size = SIZE) {
        arr = new T[size];
        capacity = size;
        top = -1;
    }

    ~Stack(){
        delete[] arr;
    }

    Stack(const Stack& other) {
        capacity = other.capacity;
        top = other.top;
        arr = new T[capacity];
        for (int i = 0; i <= top; i++) {
            arr[i] = other.arr[i];
        }
    }

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            capacity = other.capacity;
            top = other.top;
            arr = new T[capacity];
            for (int i = 0; i <= top; i++) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    void swap(Stack& other) noexcept {
        int i = 0;
        while (i < this->size() || i < other.size()) {
            std::swap(this->arr[i], other.arr[i]);
            ++i;
        }
        std::swap(top, other.top);
    }

    bool isEmpty() const {
        return top == -1;
    }

    void push(const T& element) {
        if (top == capacity - 1) {
            std::cout << "Stack overflow!" << std::endl;
            return;
        }
        arr[++top] = element;
    }

    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty.");
        }
        return arr[top--];
    }

    size_t size() const {
        return top + 1;
    }

    int topElement() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty.");
        }
        return arr[top];
    }
};


int main() {
    Stack<int> stack1; 

    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    std::cout << "Stack1 size: " << stack1.size() << std::endl;
    std::cout << "Stack1 top element: " << stack1.topElement() << std::endl;

    Stack<int> stack2(stack1); 
    std::cout << "Stack2 size: " << stack2.size() << std::endl;
    stack2.pop();
    std::cout << "Stack2 top element: " << stack2.topElement() << std::endl;

    Stack<int> stack3;
    stack3 = stack1; 
    stack3.push(5);
    std::cout << "Stack3 size: " << stack3.size() << std::endl;
    std::cout << "Stack3 top element: " << stack3.topElement() << std::endl;
}
