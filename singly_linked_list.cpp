#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <initializer_list>

template<typename T>
class List{
public:
    List() ;
    List(std::initializer_list<T> init);
    List(const List& other);
    List<T>& operator=(const List& other);
    ~List();
    void push_back(const T& data);
    void pop_front();
    void push_front(const T& data);
    void insert(const T& value, int index);
    void removeAt(int index);
    void pop_back();
    void clear() noexcept;
    int GetSize() const noexcept {return Size;}
    T&operator[](const int index);
private:
    template<typename T>
    class Node{
        public:
            Node *pNext;
            T data;
            Node (T data = T(), Node *pNext = nullptr) noexcept{
                this->data = data;
                this->pNext = pNext;
            }
    };
    int Size;
    Node<T>*head;
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
List<T>::List(const List& other) {
    Size = other.Size;
    if (other.head) {
        head = new Node<T>(other.head->data);
        Node<T>* current = head;
        Node<T>* otherCurrent = other.head->pNext;
        while (otherCurrent) {
            current->pNext = new Node<T>(otherCurrent->data);
            current = current->pNext;
            otherCurrent = otherCurrent->pNext;
        }
    }
}

template<typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this == &other) {
        return *this;
    }
    Size = other.Size;
    if (other.head) {
        head = new Node<T>(other.head->data);
        Node<T>* current = head;
        Node<T>* otherCurrent = other.head->pNext;
        while (otherCurrent) {
            current->pNext = new Node<T>(otherCurrent->data);
            current = current->pNext;
            otherCurrent = otherCurrent->pNext;
        }
    }
    return *this;
}

template<typename T>
List<T>::~List(){
    clear();
}

template<typename T>
void List<T>::push_back(const T& data){
    if(head == nullptr){
        head = new Node<T>(data);    
    }
    else{
        Node<T> * current = this->head;
        while(current->pNext != nullptr){
            current = current->pNext;
        }
        current->pNext = new Node<T>(data);
    }
    Size++;
}

template <typename T>
void List <T>::pop_front(){
    Node<T> *temp = head;
    head = head->pNext;
    delete temp;
    --Size;  
}

template <typename T>
void List<T>::insert(const T& value, int index)
{
    if(index == 0){
        push_front(value);
    }  
    else{
        Node<T> *previous = this->head;
        for(int i = 0; i < index-1; ++i)
        {
            previous = previous->pNext;
        }
        Node<T> *newNode = new Node<T>(value, previous->pNext);
        previous->pNext = newNode;
    } 
}

template <typename T>
void List<T>::removeAt(int index)
{
    if (index < 0 || index >= Size) {
        throw std::out_of_range("Index out of range");
    }

    if(index == 0){
        pop_front();
    }
    else{
        Node<T> *previous = this->head;   
        for(int i=0; i<index-1;++i){
            previous = previous->pNext;
        }
        Node<T> *toDelete = previous->pNext;
        previous->pNext = toDelete->pNext;
        delete toDelete;
        Size--;
    }
}

template <typename T>
void List<T>::pop_back(){
    removeAt(Size-1);    
}

template <typename T>
void List<T>::clear()noexcept{
    while(Size){
        pop_front();
    }
}

template<typename T>
T& List<T>::operator[](const int index){
    if (index < 0 || index >= Size) {
        throw std::out_of_range("Index out of range");
    }

    int counter = 0;
    Node<T> *current = this->head;
    while(current != nullptr)
    {
        if(counter == index){
            return current->data;
        }
        current = current->pNext;
        ++counter;
    }
}


template <typename T>
void List<T>::push_front(const T& data){
    head = new Node<T>(data, head);
    ++Size;
}

int main(){
    List<int> lst;
    
    int numbersCount;
    std::cin >> numbersCount;

    for(int i = 0; i < numbersCount; ++i){
        lst.push_back(rand()%10);
    }
    
    for(int i = 0; i < lst.GetSize(); ++i){
        std::cout << lst[i] << std::endl;
    }

    std::cout << "Size: " << lst.GetSize() << "! Next step push_front." << std::endl;
    lst.push_front(9);
    lst.push_front(11);

    for(int i = 0; i < lst.GetSize(); ++i){
        std::cout << lst[i] << std::endl;
    }

    lst.insert(99, 1);
    std::cout << "Size: " << lst.GetSize() << "! Next step clear." << std::endl;
    lst.clear();
    std::cout << "Size: " << lst.GetSize() << std::endl;
}



