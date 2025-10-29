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

    // Метод, для отримання посилання на значення елементу списку
    T& at(const int index);
    T& operator[](const int index);

    ///////////////////
/*
    void push_back(const T data);
    void pop_back();
    void push_front(const T data);
    void pop_front(const T data);
    void add_before(const int index);
    void add_after(const int index);
    void pop(const int index);*/

    size_t size();
    t_node& sentinel();
    //////////////////

    struct iterator {
        T* data;
      //....
    };
    // Вкладений клас (ітератори)

    //
};

int main() {
    /*
    
    ...

    */
    return 0;
}