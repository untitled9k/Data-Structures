#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <initializer_list>


template<typename T>
class List {
public:
    List();
    List(std::initializer_list<T> init);
    List(const List& other);
    List& operator=(const List& other);
    ~List();
    void push_back(const T& data);
    void pop_front();
    void push_front(const T& data);
    void insert(const T& value, int index);
    void removeAt(int index); 
    void pop_back();
    void clear() noexcept;
    int GetSize() const noexcept { return Size; }
    T& operator[](const int index);

private:
    template<typename T>
    class Node {
    public:
        Node *pNext;
        Node *pPrev; 
        T data;
        Node(const T& data = T(), Node* pNext = nullptr, Node* pPrev = nullptr)
            : data(data), pNext(pNext), pPrev(pPrev) {}
    };
    int Size;
    Node<T>* head;
};

template<typename T>
List<T>::List()
    : Size(0), head(nullptr) {}

template<typename T>
List<T>::List(std::initializer_list<T> init): Size(0), head(nullptr)
{
    for(const T& value : init ){
        push_back(value);    
    }
}

template<typename T>
List<T>::List(const List& other)
    : Size(other.Size), head(nullptr) {
    Node<T>* current = other.head;
    while (current != nullptr) {
        push_back(current->data);
        current = current->pNext;
    }
}

template<typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this == &other) {
        return *this;
    }
    clear();
    Size = other.Size;
    Node<T>* current = other.head;
    while (current != nullptr) {
        push_back(current->data);
        current = current->pNext;
    }
    return *this;
}

template<typename T>
List<T>::~List() {
    clear();
}

template<typename T>
void List<T>::push_back(const T& data) {
    if (head == nullptr) {
        head = new Node<T>(data);
    }
    else {
        Node<T> *current = this->head;
        while (current->pNext != nullptr) {
            current = current->pNext;
        }
        Node<T> *newNode = new Node<T>(data, nullptr, current);
        current->pNext = newNode;
    }
    Size++;
}

template <typename T>
void List<T>::pop_front() {
    if (head == nullptr) {
        return;
    }
    Node<T> *temp = head;
    head = head->pNext;
    if (head != nullptr) {
        head->pPrev = nullptr;
    }
    delete temp;
    --Size;
}

template <typename T>
void List<T>::insert(const T& value, int index) {
    if (index == 0) {
        push_front(value);
    }
    else {
        Node<T> *previous = this->head;
        for (int i = 0; i < index - 1; ++i) {
            previous = previous->pNext;
        }
        Node<T> *newNode = new Node<T>(value, previous->pNext, previous);
        if (previous->pNext != nullptr) {
            previous->pNext->pPrev = newNode;
        }
        previous->pNext = newNode;
    }
    Size++;
}

template <typename T>
void List<T>::removeAt(int index) {
    if (index < 0 || index >= Size) {
        throw std::out_of_range("Index out of range");
    } 
    if (index == 0) {
        pop_front();
    }
    else {
        Node<T> *previous = this->head;
        for (int i = 0; i < index - 1; ++i) {
            previous = previous->pNext;
        }
        Node<T> *toDelete = previous->pNext;
        previous->pNext = toDelete->pNext;
        if (toDelete->pNext != nullptr) {
            toDelete->pNext->pPrev = previous;
        }
        delete toDelete;
        Size--;
    }
}

template <typename T>
void List<T>::pop_back() {
    if (Size == 1) {
        pop_front();
    }
    else {
        removeAt(Size - 1);
    }
}

template<typename T>
void List<T>::clear() noexcept{
    while (Size) {
        pop_front();
    }
}

template<typename T>
T& List<T>::operator[](const int index) {
    if (index < 0 || index >= Size) {
        throw std::out_of_range("Index out of range");
    }
    int counter = 0;
    Node<T> *current = this->head;
    while (current != nullptr) {
        if (counter == index) {
            return current->data;
        }
        current = current->pNext;
        ++counter;
    }
}

template <typename T>
void List<T>::push_front(const T& data) {
    head = new Node<T>(data, head, nullptr);
    if (head->pNext != nullptr) {
        head->pNext->pPrev = head;
    }
    ++Size;
}

int main() {
    List<int> lst;
    int numbersCount;
    std::cin >> numbersCount;
    for (int i = 0; i < numbersCount; ++i) {
        lst.push_back(rand() % 10);
    }
    for (int i = 0; i < lst.GetSize(); ++i) {
        std::cout << lst[i] << std::endl;
    }
    std::cout << "Size: " << lst.GetSize() << "! Next step push_front and insert 99." << std::endl;
    lst.push_front(9);
    lst.push_front(11);
    lst.insert(99, 1);
    for (int i = 0; i < lst.GetSize(); ++i) {
        std::cout << lst[i] << std::endl;
    }
    std::cout << "Size: " << lst.GetSize() << "! Next step clear." << std::endl;

    lst.clear();
    std::cout << "Size: " << lst.GetSize() << std::endl;
}