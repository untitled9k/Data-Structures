#include <iostream>
#include <stdexcept>

int const SIZE = 1000;

template <class T>
class CircularQueue {
private:
    T* arr;
    int front;
    int rear;
    int capacity;
    int count;
public:
    CircularQueue(int size = SIZE) : arr(new T[size]), front(0), rear(-1), capacity(size), count(0) {}

    CircularQueue(const CircularQueue& other)
        : arr(new T[other.capacity]), front(other.front), rear(other.rear),
          capacity(other.capacity), count(other.count) {
        for (int i = 0; i < capacity; i++) {
            arr[i] = other.arr[i];
        }
    }

    CircularQueue& operator=(const CircularQueue& other) {
        if (this != &other) {
            delete[] arr;
            arr = new T[other.capacity];
            front = other.front;
            rear = other.rear;
            capacity = other.capacity;
            count = other.count;
            for (int i = 0; i < capacity; i++) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    ~CircularQueue(){
        delete[] arr;
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == capacity;
    }

    void enqueue(const T& element) {
        if (isFull()) {
            std::cout << "Queue overflow!" << std::endl;
            return;
        }
        rear = (rear + 1) % capacity;
        arr[rear] = element;
        count++;
    }

    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty.");
        }
        T element = arr[front];
        front = (front + 1) % capacity;
        count--;
        return element;
    }

    size_t size() const {
        return count;
    }

    T frontElement() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty.");
        }
        return arr[front];
    }
};

int main() {
    CircularQueue<int> queue;

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    std::cout << "Queue size: " << queue.size() << std::endl;
    std::cout << "Front element: " << queue.frontElement() << std::endl;

    queue.dequeue();
    std::cout << "Queue size after dequeue: " << queue.size() << std::endl;
    std::cout << "Front element after dequeue: " << queue.frontElement() << std::endl;

    queue.enqueue(4);
    std::cout << "Queue size after enqueue: " << queue.size() << std::endl;
    std::cout << "Front element after enqueue: " << queue.frontElement() << std::endl;

    return 0;
}