class MyCircularQueue {
public:
    vector<int> arr;
    int front;
    int size;
    int capacity;

    MyCircularQueue(int k) {
        capacity = k;
        arr.resize(k);
        front = 0;
        size = 0;
    }

    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }

        int rear = (front + size) % capacity;

        arr[rear] = value;
        size++;

        return true;
    }

    bool deQueue() {
        if (isEmpty()) {
            return false;
        }

        front = (front + 1) % capacity;
        size--;

        return true;
    }

    int Front() {
        if (isEmpty()) {
            return -1;
        }

        return arr[front];
    }

    int Rear() {
        if (isEmpty()) {
            return -1;
        }

        int rear = (front + size - 1) % capacity;

        return arr[rear];
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == capacity;
    }
};