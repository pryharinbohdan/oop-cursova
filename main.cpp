#include <iostream>
#include <utility> // Для std::move

template <typename T>
struct t_node {
    T data;
    t_node* prev;
    t_node* next;
    t_node(); // Конструктор за замовченням (створює sentinel)
    t_node(const T data); // Конструктор з параметром
};

template <typename T>
class Linked2List {
    // Конструктор за замовченням
    Linked2List();
    // Конструктор копіювання
    Linked2List(const Linked2List& other);
    // Конструктор переміщення
    Linked2List(Linked2List&& other) noexcept;
    // Деструктор
    ~Linked2List();
    // Оператор копіювання
    Linked2List& operator=(const Linked2List& other);
    // Оператор переміщення
    Linked2List& operator=(Linked2List&& other) noexcept;

    ///////////////////
    void push_back(const T data);
    void pop_back();
    void push_front(const T data);
    void pop_front(const T data);
    void insert_before(t_node<T>* node, const T& data);
    void insert_after(t_node<T>* node, const T& data);
    void clear() const;
    bool empty() const;

    class iterator {
        t_node* ptr;
      public:
        iterator() : ptr(nullptr) {}
        iterator(t_node* ptr) : ptr(ptr) {}

        iterator operator ++ () {
            return iterator(ptr = ptr -> next);
        }
        iterator operator -- () {
            return iterator(ptr = ptr -> prev);
        }
        bool operator != (const iterator& guest) {
            return ptr != guest.ptr;
        }

        T& operator * () {
            return ptr -> data;
        }
    };

    iterator& begin();
    iterator& end();

    size_t size();
    //t_node& sentinel();
};


/// РЕАЛІЗАЦІЯ МЕТОДІВ ///


/////////////////////////////


int main() {
    // створюємо об'єкт типу Linked2List

    Linked2List < int > ls;

    /*
    
    ...

    */


    //цикл ітератор
    for (Linked2List < int > :: iterator it = ls.begin(); it != --ls.end(); ++it) {
        std::cout << *it << " ";
    }

    return 0;
}