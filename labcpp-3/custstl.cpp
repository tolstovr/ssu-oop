#include <iostream>

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;

        Node(T value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    List() : head(nullptr), tail(nullptr) {}

    ~List() {
        clear();
    }

    void add(T value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void remove(T value) {
        Node* current = head;
        Node* previous = nullptr;

        while (current != nullptr) {
            if (current->data == value) {
                if (previous == nullptr) {
                    head = current->next;
                    if (head == nullptr) {
                        tail = nullptr;
                    }
                } else {
                    previous->next = current->next;
                    if (current == tail) {
                        tail = previous;
                    }
                }
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }
    }

    void insert(int index, T value) {
        if (index < 0) return;

        Node* newNode = new Node(value);
        if (index == 0) {
            newNode->next = head;
            head = newNode;
            if (tail == nullptr) {
                tail = newNode;
            }
            return;
        }

        Node* current = head;
        for (int i = 0; i < index - 1 && current != nullptr; ++i) {
            current = current->next;
        }

        if (current == nullptr) {
            add(value);
        } else {
            newNode->next = current->next;
            current->next = newNode;
            if (newNode->next == nullptr) {
                tail = newNode;
            }
        }
    }

    bool find(T value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value)
                return true;
            current = current->next;
        }
        return false;
    }

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    void print(std::ostream& out) const {
        Node* current = head;
        while (current != nullptr) {
            out << current->data << " -> ";
            current = current->next;
        }
        out << "nullptr" << std::endl;
    }
};