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
  protected:
    t_node<T>* sen;
    size_t list_size;
  public:
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

    // Клас ітератор

    class iterator {
        t_node<T>* ptr;
      public:
        iterator();
        iterator(t_node<T>* ptr); 
        iterator operator ++ ();
        iterator operator -- ();
        bool operator != (const iterator& guest);
        bool operator == (const iterator& guest);
        T& operator * ();

        friend class Linked2List<T>;
    };

    // Метод для вставлення вузла перед іншим вузлом у списку
    void insert_before(iterator it, const T& data);
    // Метод для вставлення вузла після іншого вузла у списку
    void insert_after(iterator it, const T& data);
    // Метод для видалення вибраного вузла зі списку
    void erase(iterator it);

    /*
    // Метод для видалення вузла перед іншим вузлом у списку
    void pop_before(iterator it);
    // Метод для видалення вузла після іншого вузла у списку
    void pop_after(iterator it);
    */

    // Метод для додавання нового вузла (ініціалізованого значенням) у кінець списку
    void push_back(const T data);
    // Метод для видалення останнього вузла у списку
    void pop_back();
    // Метод для додавання нового вузла (ініціалізованого значенням) на початок списку
    void push_front(const T data);
    // Метод для видалення першого вузла у списку
    void pop_front();
    // Метод для видалення всіх вузлів у списку
    void clear();
    // Метод, що перевіряє чи пустий список
    bool empty() const;

    // Метод, що повертає посилання на ітератор першого вузла списку
    iterator begin();
    // Метод, що повертає посилання на ітератор останнього вузла списку
    iterator end();
    // Метод, що повертає кількість вузлів у списку
    size_t size();
    // Метод для пошуку вузла за значенням
    iterator& search(const T value);


};


/////////////////// РЕАЛІЗАЦІЯ МЕТОДІВ /////////////////////////

// Конструктори вузла (t_node<T>)

template <typename T>
t_node<T>::t_node() : data(0), prev(this), next(this) {}

template <typename T>
t_node<T>::t_node(const T data) : data(data), prev(nullptr), next(nullptr) {}

/* *** РЕАЛІЗАЦІЯ КОНСТРУКТОРІВ ТА МЕТОДІВ ДЛЯ КЛАСУ ІТЕРАТОРА (Linked2List<T>::iterator) *** */

template <typename T>
Linked2List<T>::iterator::iterator() : ptr(nullptr) {}

template <typename T>
Linked2List<T>::iterator::iterator(t_node<T>* ptr) : ptr(ptr) {}

template <typename T>
typename Linked2List<T>::iterator Linked2List<T>::iterator::operator ++ () {
    ptr = ptr -> next;
    return *this;
}

template <typename T>
typename Linked2List<T>::iterator Linked2List<T>::iterator::operator -- () {
    ptr = ptr -> prev;
    return *this;
}

template <typename T>
bool Linked2List<T>::iterator::operator != (const iterator& guest) {
    return ptr != guest.ptr;
}

template <typename T>
bool Linked2List<T>::iterator::operator == (const iterator& guest) {
    return ptr == guest.ptr;
}

template <typename T>
T& Linked2List<T>::iterator::operator * () {
    return ptr -> data;
}

/////////////////////////////

/* *** КОНСТРУКТОРИ СПИСКУ (Linked2List<T>) *** */

// Конструктор за замовченням
template <typename T>
Linked2List<T>::Linked2List() : sen(new t_node<T>), list_size(0) {}
// Конструктор копіювання
template <typename T>
Linked2List<T>::Linked2List(const Linked2List& other) : sen(new t_node<T>){
    for (iterator it = other.begin(); it != other.end(); ++it)
        push_back(*it);
}
// Конструктор переміщення
template <typename T>
Linked2List<T>::Linked2List(Linked2List&& other) noexcept : sen(other.sen) {
    other.sen = nullptr;
}

/* *** ПЕРВАНТАЖЕННЯ ОПЕРАТОРІВ ****/

// Оператор копіювання
template <typename T>
Linked2List<T>& Linked2List<T>::operator=(const Linked2List<T>& other) {
    sen = new t_node<T>;
    for (iterator it = other.begin(); it != other.end(); ++it)
        push_back(*it);
    return *this;
}
// Оператор переміщення
template <typename T>
Linked2List<T>& Linked2List<T>::operator=(Linked2List<T>&& other) noexcept {
    sen = other.sen;
    other.sen = nullptr;
    return *this;
}

/* *** МЕТОДИ СПИСКУ (Linked2List<T>) *** */

// Метод для вставлення вузла перед іншим вузлом у списку
template <typename T>
void Linked2List<T>::insert_before(typename Linked2List<T>::iterator it, const T& data) {
    t_node<T>* new_node = new t_node<T>(data);
    new_node -> next = it.ptr;
    new_node -> prev = it.ptr -> prev;
    it.ptr -> prev -> next = new_node;
    it.ptr -> prev = new_node;
    ++list_size;
}
// Метод для вставлення вузла після іншого вузла у списку
template <typename T>
void Linked2List<T>::insert_after(typename Linked2List<T>::iterator it, const T& data) {
    t_node<T>* new_node = new t_node<T>(data);
    new_node -> next = it.ptr -> next;
    new_node -> prev = it.ptr;
    it.ptr -> next -> prev= new_node;
    it.ptr -> next = new_node;
    ++list_size;
}

/*
// Метод для видалення вузла перед іншим вузлом у списку
template <typename T>
void Linked2List<T>::pop_before(typename Linked2List<T>::iterator it) {
    t_node<T>* for_delete = it.ptr -> prev;
    for_delete -> prev -> next = it.ptr;
    it.ptr -> prev = for_delete -> prev;
    delete for_delete;
}
// Метод для видалення вузла після іншого вузла у списку
template <typename T>
void Linked2List<T>::pop_after(typename Linked2List<T>::iterator it) {
    t_node<T>* for_delete = it.ptr -> next;
    for_delete -> next -> prev = it.ptr;
    it.ptr -> next = for_delete -> next;
    delete for_delete;
}
*/

template <typename T>
void Linked2List<T>::erase(typename Linked2List<T>::iterator it) {
    t_node<T>* for_delete = it.ptr;
    it.ptr -> prev -> next = it.ptr -> next;
    it.ptr -> next -> prev = it.ptr -> prev;
    --it;
    --list_size;
    delete for_delete;
}

// Метод для додавання нового вузла (ініціалізованого значенням) у кінець списку
template <typename T>
void Linked2List<T>::push_back(const T data) {
    insert_before(end(), data);
}
// Метод для видалення останнього вузла у списку
template <typename T>
void Linked2List<T>::pop_back() {
    erase(--end());
}
// Метод для додавання нового вузла (ініціалізованого значенням) на початок списку
template <typename T>
void Linked2List<T>::push_front(const T data) {
    insert_after(end(), data);
}
// Метод для видалення першого вузла у списку
template <typename T>
void Linked2List<T>::pop_front() {
    erase(begin());
}
// Метод для видалення всіх вузлів у списку
template <typename T>
void Linked2List<T>::clear() {
    while (begin() != end()) {
        pop_back();
    }
}
// Метод, що перевіряє чи пустий список
template <typename T>
bool Linked2List<T>::empty() const {
    return begin() == end();
}

// Метод, що повертає посилання на ітератор першого вузла списку
template <typename T>
typename Linked2List<T>::iterator Linked2List<T>::begin() {
    return iterator(sen -> next);
}

// Метод, що повертає посилання на ітератор останнього вузла списку
template <typename T>
typename Linked2List<T>::iterator Linked2List<T>::end() {
    return iterator(sen);
}

// Метод, що повертає кількість вузлів у списку
template <typename T>
size_t Linked2List<T>::size() {
    return list_size;
}

/* *** ДЕСТРУКТОР СПИСКУ (Linked2List<T>) *** */

template <typename T>
Linked2List<T>::~Linked2List() {
    clear();
    delete sen;
}

/////////////////////////// ОСНОВНА ПРОГРАМА ///////////////////////////////

int main() {
    // створюємо об'єкт типу Linked2List

    Linked2List < int > ls;

    
    for (int i = 0; i < 10; ++i) {
        ls.push_back(i);
    }

    for (Linked2List < int > :: iterator it = ls.begin(); it != ls.end(); ++it) {
        if (*it % 2 == 0) {
            ls.erase(it);
        }
    }

    //цикл ітератор
    for (Linked2List < int > :: iterator it = ls.begin(); it != ls.end(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << std::endl;

    return 0;
}