#include <iostream>
#include <utility> // Для std::move

template <typename T>
struct t_node {
    T data;
    t_node* prev;
    t_node* next;
    t_node(); // Конструктор за замовченням (створює sentinel)
    t_node(const T& data); // Конструктор з параметром
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
    /* Перевантаження оператору копіювання. Копіює кожен вузол правого списку 
    та додає його в лівий список. Повертає посилання на лівий список */
    Linked2List& operator=(const Linked2List& other);
    /* Перевантаження оператора переміщення. Передає ресурси з правого списку в лівий, 
    обнуляючи дані правого списку. Повертає посилання на лівий список.*/
    Linked2List& operator=(const Linked2List&& other) noexcept;
    /* Перевантаження оператора (==). Повертає true, якщо всі значення вузлів лівого списку
    дорівнюють відповідним значенням вузлів правого списку. */
    bool operator==(const Linked2List& other) const;
    /* Перевантаження оператору (не дорівнює). Повертає true, в разі, якщо хоча б одне 
    значення вузла лівого списку не дорівнює відповідному значенню вузла правого списку*/
    bool operator!=(const Linked2List& other) const;
    /* Перевантаження оператору (більше). Повертає true, в разі, якщо 
    розмір лівого списку більше розміру правого, і false в іншому випадку */
    bool operator>(const Linked2List& other) const;
    /* Перевантаження оператору (менше). Повертає true, в разі, якщо розмір 
    лівого списку менше розміру правого, і false в іншому випадку */
    bool operator<(const Linked2List& other) const;
    /* Перевантаження оператору (більше або дорівнює). Повертає true, в разі, якщо розмір 
    лівого списку більше або дорівнює розміру правого, і false в іншому випадку */
    bool operator>=(const Linked2List& other) const;
    /* Перевантаження оператору (менше або дорівнює). Повертає true, в разі, якщо розмір 
    лівого списку менше або дорівнює розміру правого, і false в іншому випадку */
    bool operator<=(const Linked2List& other)const;

    ///////////////////

    // Клас ітератор

    class iterator {
        t_node<T>* ptr;
      public:
        iterator();
        iterator(t_node<T>* ptr); 
        // Перевантаження оператору присвоювання (для значення)
        iterator operator=(const T& val);
        iterator operator ++ ();
        iterator operator -- ();
        bool operator != (const iterator& guest);
        bool operator == (const iterator& guest);
        T& operator * ();
        T* operator->();
        friend class Linked2List<T>;
    };

    // Клас реверсний ітератор
    class reverse_iterator {
        t_node<T>* ptr;
      public:
        reverse_iterator();
        reverse_iterator(t_node<T>* ptr); 
        // Перевантаження оператору присвоювання (для значення)
        reverse_iterator operator=(const T& val);
        reverse_iterator operator ++ ();
        reverse_iterator operator -- ();
        bool operator != (const reverse_iterator& guest);
        bool operator == (const reverse_iterator& guest);
        T& operator * ();
        T* operator -> ();

        friend class Linked2List<T>;
    };

    ////////////////////////////

    // Метод для вставлення вузла перед іншим вузлом у списку
    void insert_before(iterator it, const T& data);
    // Метод для вставлення вузла після іншого вузла у списку
    void insert_after(iterator it, const T& data);
    // Метод для видалення вибраного вузла зі списку
    iterator erase(iterator it);

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
    iterator begin() const;
    // Метод, що повертає посилання на ітератор останнього вузла списку
    iterator end() const;
    // Метод, що повертає посилання на реверс ітератор останнього вузла списку
    reverse_iterator rbegin() const;
    // Метод, що повертає посилання на реверс ітератор першого вузла списку
    reverse_iterator rend() const;
    // Метод, що повертає кількість вузлів у списку
    size_t size() const;

    // Метод для пошуку вузла за значенням
    iterator find(const T& value) const; 
    // Метод, що шукає вузол за допомогою унарного предикату
    iterator find(bool (*unary_predicate)(T&)) const;

    // Метод Swap (для обміну вмістом)
    void swap(Linked2List& other) noexcept;

    // Метод, що видаляє вузли за значенням
    void remove(const T& value); 

    // Метод, що видаляє вузли, які підходять за умовою унарного предикату
    void remove(bool (*unary_predicate)(T&)); 

    // Метод, що виконує злиття двох відсортованих списків
    void merge(Linked2List& other);

    // Метод (сортування злиттям) з компаратором
    void sort(bool (*compare)(T&, T&));

    // Метод, що робить класичний список циклічним (аргумент true), або навпаки, робить циклічний список - класичним (аргумент false)
    void circular(const bool makeCirc); // РОБИТЬ СПИСОК ЦІИКЛІЧНИМ (ВІД'ЄДНУЄ SENTINEL)
};







/////////////////// РЕАЛІЗАЦІЯ МЕТОДІВ /////////////////////////

// Конструктори вузла (t_node<T>)

template <typename T>
t_node<T>::t_node() : data(), prev(this), next(this) {}

template <typename T>
t_node<T>::t_node(const T& data) : data(data), prev(nullptr), next(nullptr) {}

///////////////////////////////////////////////

/* *** РЕАЛІЗАЦІЯ КОНСТРУКТОРІВ ТА МЕТОДІВ ДЛЯ КЛАСУ ІТЕРАТОРА (Linked2List<T>::iterator) *** */

template <typename T>
Linked2List<T>::iterator::iterator() : ptr(nullptr) {}

template <typename T>
Linked2List<T>::iterator::iterator(t_node<T>* ptr) : ptr(ptr) {}

template <typename T>
typename Linked2List<T>::iterator Linked2List<T>::iterator::operator=(const T& val) {
    ptr -> data = val;
    return *this;
}

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

template <typename T>
T* Linked2List<T>::iterator::operator -> () {
    return &(ptr -> data);
}



/* *** РЕАЛІЗАЦІЯ КОНСТРУКТОРІВ ТА МЕТОДІВ ДЛЯ КЛАСУ !!!РЕВЕРС!!! ІТЕРАТОРА (Linked2List<T>::reverse_iterator) *** */

template <typename T>
Linked2List<T>::reverse_iterator::reverse_iterator() : ptr(nullptr) {}

template <typename T>
Linked2List<T>::reverse_iterator::reverse_iterator(t_node<T>* ptr) : ptr(ptr) {}

template <typename T>
typename Linked2List<T>::reverse_iterator Linked2List<T>::reverse_iterator::operator=(const T& val) {
    ptr -> data = val;
    return *this;
}

template <typename T>
typename Linked2List<T>::reverse_iterator Linked2List<T>::reverse_iterator::operator ++ () {
    ptr = ptr -> prev;
    return *this;
}

template <typename T>
typename Linked2List<T>::reverse_iterator Linked2List<T>::reverse_iterator::operator -- () {
    ptr = ptr -> next;
    return *this;
}

template <typename T>
bool Linked2List<T>::reverse_iterator::operator != (const reverse_iterator& guest) {
    return ptr != guest.ptr;
}

template <typename T>
bool Linked2List<T>::reverse_iterator::operator == (const reverse_iterator& guest) {
    return ptr == guest.ptr;
}

template <typename T>
T& Linked2List<T>::reverse_iterator::operator * () {
    return ptr -> data;
}

template <typename T>
T* Linked2List<T>::reverse_iterator::operator -> () {
    return &(ptr -> data);
}


/////////////////////////////

/* *** КОНСТРУКТОРИ СПИСКУ (Linked2List<T>) *** */

// Конструктор за замовченням
template <typename T>
Linked2List<T>::Linked2List() : sen(new t_node<T>), list_size(0) {}
// Конструктор копіювання
template <typename T>
Linked2List<T>::Linked2List(const Linked2List& other) : sen(new t_node<T>), list_size(0){
    for (auto it = other.begin(); it != other.end(); ++it)
        push_back(*it);
}
// Конструктор переміщення
template <typename T>
Linked2List<T>::Linked2List(Linked2List&& other) noexcept : sen(other.sen), list_size(other.list_size) {
    other.sen = nullptr;
    other.list_size = 0;
}

/* *** ПЕРВАНТАЖЕННЯ ОПЕРАТОРІВ ****/

// Оператор копіювання
template <typename T>
Linked2List<T>& Linked2List<T>::operator=(const Linked2List<T>& other) {
    sen = new t_node<T>;
    for (auto it = other.begin(); it != other.end(); ++it)
        push_back(*it);
    return *this;
}
// Оператор переміщення
template <typename T>
Linked2List<T>& Linked2List<T>::operator=(const Linked2List<T>&& other) noexcept {
    sen = other.sen;
    list_size = other.list_size;
    other.sen = nullptr;
    other.list_size = 0;
    return *this;
}

// Перевантаження оператору (дорівнює)
template <typename T>
bool Linked2List<T>::operator==(const Linked2List<T>& other) const {
    if (list_size != other.list_size) return false;
    auto it1 = begin();
    auto it2 = other.begin();
    for (; it1 != end(); ++it1, ++it2) {
        if (*it1 != *it2) return false;
    }
    return true;
}


// Перевантаження оператору (не дорівнює)
template <typename T>
bool Linked2List<T>::operator!=(const Linked2List& other) const{
    return !(*this == other);
}

//Перевантаження оператору (більше)
template <typename T>
bool Linked2List<T>::operator>(const Linked2List& other) const {
    return list_size > other.list_size;
}

//Перевантаження оператору (менше)
template <typename T>
bool Linked2List<T>::operator<(const Linked2List& other) const {
    return list_size < other.list_size;
}

//Перевантаження оператору (більше або дорівнює)
template <typename T>
bool Linked2List<T>::operator>=(const Linked2List& other) const {
    return (this > other) || (this == other);
}

//Перевантаження оператору (менше або дорівнює)
template <typename T>
bool Linked2List<T>::operator<=(const Linked2List& other) const{
    return (this < other) || (this == other);
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

// Метод, що видаляє обраний вузол списку
template <typename T>
typename Linked2List<T>::iterator Linked2List<T>::erase(typename Linked2List<T>::iterator it) {
    t_node<T>* next_elem = it.ptr -> next;
    if (it.ptr == sen -> prev && sen -> prev -> next != sen) {
        sen -> prev = it.ptr -> prev;
    } else if (it.ptr == sen -> next && sen -> next -> prev != sen) {
        sen -> next = it.ptr -> next;
    }
    it.ptr -> prev -> next = it.ptr -> next;
    it.ptr -> next -> prev = it.ptr -> prev;
    delete it.ptr;
    --list_size;
    return iterator(next_elem);
}
// Метод для додавання нового вузла (ініціалізованого значенням) у кінець списку
template <typename T>
void Linked2List<T>::push_back(const T data) {
    insert_before(end(), data);
}
// Метод для видалення останнього вузла у списку
template <typename T>
void Linked2List<T>::pop_back() {
    if (empty()) return;
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
    if (empty()) return;
    erase(begin());
}
// Метод, що перевіряє чи пустий список
template <typename T>
bool Linked2List<T>::empty() const {
    return begin() == end();
}
// Метод для видалення всіх вузлів у списку
template <typename T>
void Linked2List<T>::clear() {
    while (!empty()) {
        pop_back();
    }
}
// Метод, що повертає посилання на ітератор першого вузла списку
template <typename T>
typename Linked2List<T>::iterator Linked2List<T>::begin() const{
    return iterator(sen -> next);
}
// Метод, що повертає посилання на ітератор останнього вузла списку
template <typename T>
typename Linked2List<T>::iterator Linked2List<T>::end() const{
    return iterator(sen);
}
// Метод, що повертає посилання на реверс ітератор останнього вузла списку
template <typename T>
typename Linked2List<T>::reverse_iterator Linked2List<T>::rbegin() const{
    return reverse_iterator(sen -> prev);
}
// Метод, що повертає посилання на реверс ітератор першого вузла списку
template <typename T>
typename Linked2List<T>::reverse_iterator Linked2List<T>::rend() const{
    return reverse_iterator(sen);
}
// Метод, що повертає кількість вузлів у списку
template <typename T>
size_t Linked2List<T>::size() const{
    return list_size;
}

// Метод, що шукає вузол за значенням у списку
template <typename T>
typename Linked2List<T>::iterator Linked2List<T>::find(const T& value) const{
    for (auto it = begin(); it != end(); ++it) 
        if (*it == value)
            return it;
    return end();
}

// Метод, що шукає вузол за допомогою унарного предикату
template <typename T>
typename Linked2List<T>::iterator Linked2List<T>::find(bool (*unary_predicate)(T&)) const {
    for (auto it = begin(); it != end(); ++it)
        if (unary_predicate(*it)) return it;
    return end();
}


// Метод Swap (для обміну вмістом)
template <typename T>
void Linked2List<T>::swap(Linked2List& other) noexcept {
    std::swap(sen, other.sen);
    std::swap(list_size, other.list_size);
}

// Метод, що видаляє вузли за значенням
template <typename T>
void Linked2List<T>::remove(const T& value) {
    auto it = begin();
    while (it != end()) {
        if (*it == value) {
            it = erase(it);
        } else {
            ++it;
        }
    }
}
// Метод, що видаляє вузли, які підходять за умовою унарного предикату !!!!
template <typename T>
void Linked2List<T>::remove(bool (*unary_predicate)(T&)) {
    for (auto it = begin(); it != end(); ) {
        if (unary_predicate(*it))
            it = erase(it);
        else
            ++it;
    }
}

// Метод, що зливає відсортований поточний список і відсортований переданий список в поточний список
template <typename T>
void Linked2List<T>::merge(Linked2List& other) {
    auto it = begin();
    auto jt = other.begin();
    
    while (jt != other.end()) {
        if (it == end() || *jt < *it) {
            insert_before(it, *jt);
            ++jt;
        } else {
            ++it;
        }
    }
    
    other.clear();  
   
}

// Метод (сортування вставкою) за неспаданням з компаратором
template <typename T>
void Linked2List<T>::sort(bool (*compare)(T&, T&)) {
    if (size() <= 1) return;
    auto it = begin();
    ++it;
    
    while (it != end()) {
        T key = *it;
        auto pos = begin();
        
        while (pos != it && compare(*pos, key)) {
            ++pos;
        }
        
        if (pos != it) {
            auto temp = it;
            ++it;
            insert_before(pos, key);
            erase(temp);
        } else {
            ++it;
        }
    }
}

/* Метод, що робить зв'язний список циклічним, приймає як аргумент bool значення:
    true, якщо треба зробити із класичного списку зациклений список
    false, якщо з циклічного треба перетворити у класичний */
template <typename T>
void Linked2List<T>::circular(const bool makeCirc) {
    if (makeCirc && sen -> prev -> next == sen) {
        sen -> prev -> next = sen -> next;
        sen -> next -> prev = sen -> prev;
    } else if (!makeCirc && sen -> prev -> next != sen) {
        sen -> prev -> next = sen;
        sen -> next -> prev = sen;
    }
}

/* *** ДЕСТРУКТОР СПИСКУ (Linked2List<T>) *** */

template <typename T>
Linked2List<T>::~Linked2List() {
    // ЯКЩО КОРИСТУВАЧ ЗАЦИКЛИВ НАШ СПИСОК, ПРИВОДИМО ЙОГО ДО КЛАСИЧНОГО ВИГЛЯДУ, ЩОБ ОЧИСТИТИ ПАМ'ЯТЬ
    if (sen -> prev -> next != sen) {
        circular(false);
    }
    clear();
    delete sen;
}








/////////////////////////// ДОПОМІЖНІ ФУНКЦІЇ ///////////////////////////////

/* Функція перевірки двох рядків (const char* a, const char* b) 
на рівність (повертає true, якщо рівні та false, якщо ні) */
bool strcmp_equal(const char* a, const char* b) {
    size_t i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        ++i;
    }
    return a[i] == b[i];
}

// Процедура копіювання рядка (const char* src) у масив (char* dest)
void strcpy_custom(char* dest, const char* src) {
    size_t i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }
    dest[i] = '\0';
}

/* Функція для визначення довжини рядка (const char* str)
Повертає довжину типу size_t */
size_t strlen_custom(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') ++len;
    return len;
}

/////////////////////////// СТРУКТУРА ПІСНІ ///////////////////////////////

struct Song {
    char* name; // Назва пісні
    char* author; // Ім'я автора
    int duration; // Довжина пісні в секундах
    // Конструктор за замовчуванням
    Song() : name(nullptr), author(nullptr), duration(0) {
        // Створюємо масиви типу char розмірності 1
        name = new char[1];
        name[0] = '\0';
        author = new char[1];
        author[0] = '\0';
    }
    // Конструктор з параметром
    Song(const char* n, const char* a, int d) : duration(d) {
        // визначаємо довжину рядка
        size_t len = strlen_custom(n) + 1;
        // виділяємо пам'ять під масиви та заповнюємо їх значеннями
        name = new char[len];
        strcpy_custom(name, n);
        // так само для другого рядка
        len = strlen_custom(a) + 1;
        author = new char[len];
        strcpy_custom(author, a);
    }
    
    // Конструктор копіювання
    Song(const Song& other) : duration(other.duration) {
        // визначаємо довжину рядка
        size_t len = strlen_custom(other.name) + 1;
        // виділяємо пам'ять під масиви та заповнюємо їх значеннями
        name = new char[len];
        strcpy_custom(name, other.name);
        // так само для другого рядка
        len = strlen_custom(other.author) + 1;
        author = new char[len];
        strcpy_custom(author, other.author);
    }
    // Перевантаження оператору присвоєння, повертає посилання (Song&) на поточний об'єкт
    Song& operator=(const Song& other) {
        if (this != &other) {
            delete[] name;
            delete[] author;
            // визначаємо довжину рядка
            size_t len = strlen_custom(other.name) + 1;
            // виділяємо пам'ять під масиви та заповнюємо їх значеннями
            name = new char[len];
            strcpy_custom(name, other.name);
            // так само для другого рядка
            len = strlen_custom(other.author) + 1;
            author = new char[len];
            strcpy_custom(author, other.author);
            duration = other.duration;
        }
        return *this;
    }
    /* Перевантаження оператору == (порівняння на рівність всіх полів двох об'єктів типу Song), 
    повертає true, в разі рівності і false, в разі нерівності */
    bool operator==(const Song& other) const {
        return strcmp_equal(name, other.name) && strcmp_equal(author, other.author) && duration == other.duration;
    }
    /* Перевантаження оператору != (порівняння на нерівність полів двох об'єктів типу Song), 
    повертає true, в разі нерівності хоч одного поля, false в разі повної рівності */
    bool operator!=(const Song& other) const {
        return !(*this == other);
    }
    /* Перевантаження оператору < (порівняння часу), в разі якщо в полі значення duration поточного об'єкту
    менше, ніж у переданого, повертає true, в протилежному випадку - false*/
    bool operator<(const Song& other) const {
        return duration < other.duration;
    }
    /* Перевантаження оператору > (порівняння часу), в разі якщо в полі значення duration поточного об'єкту
    більше, ніж у переданого, повертає true, в протилежному випадку - false*/
    bool operator>(const Song& other) const {
        return duration > other.duration;
    }
    // Перевантаження оператору <= (менше за часом або рівні) логічне об'єднання вже реалізованих (== та <)
    bool operator<=(const Song& other) const {
        return (*this < other) || (*this == other);
    }
    // Перевантаження оператору >= (більше за часом або рівні) логічне об'єднання вже реалізованих (== та >)
    bool operator>=(const Song& other) const {
        return (*this > other) || (*this == other);
    }
    // Деструктор
    ~Song() {
        delete[] name;
        delete[] author;
    }
};

/////////////////////////// УНАРНІ ПРЕДИКАТИ ТА КОМПАРАТОРИ ///////////////////////////////

// Компаратор, аргументами є два посилання(Song&) на об'єкти а та b
// Повертає true, якщо довжина пісні a менша або дорівнює довжині пісні b 
// false в протилежному випадку
bool compare_by_duration(Song& a, Song& b) {
    return a.duration <= b.duration;
}
// Унарний предикат, аргументом є посилання(Song&) на об'єкт а
// Повертає true, в разі якщо довжина пісні більша за 5 хв (300 с), false в протилежному випадку
bool is_long_song(Song& s) {
    return s.duration > 300; // більше 5 хвилин
}
// Унарний предикат, аргументом є посилання(Song&) на об'єкт а
// Повертає true, в разі якщо довжина пісні менша за 3 хв (180 с), false в протилежному випадку
bool is_short_song(Song& s) {
    return s.duration < 180; // менше 3 хвилин
}

/////////////////////////// ОСНОВНА ПРОГРАМА ///////////////////////////////

// Процедура для виводу у вихідний потік інструкції для користувача
void print_menu() {
    std::cout << "\n========== МЕНЮ ПЛЕЙЛИСТА ==========\n";
    std::cout << "1  - Додати пісню в кінець\n";
    std::cout << "2  - Додати пісню на початок\n";
    std::cout << "3  - Показати всі пісні\n";
    std::cout << "4  - Показати в зворотному порядку\n";
    std::cout << "5  - Видалити останню пісню\n";
    std::cout << "6  - Видалити першу пісню\n";
    std::cout << "7  - Знайти пісню за назвою\n";
    std::cout << "8  - Видалити довгі пісні (>5хв)\n";
    std::cout << "9  - Сортувати за тривалістю\n";
    std::cout << "10 - Розмір плейлиста\n";
    std::cout << "11 - Очистити плейлист\n";
    std::cout << "12 - Обміняти з іншим плейлистом\n";
    std::cout << "13 - Злити з іншим плейлистом\n";
    std::cout << "0  - Вихід\n";
    std::cout << "====================================\n";
    std::cout << "Ваш вибір: ";
}
// Процедура для виводу у вихідний потік пісні, приймає першим аргументом константне посилання
// на об'єкт (const Song& s) та int num (номер треку)
void print_song(const Song& s, int num) {
    std::cout << num << ". " << s.name << " - " << s.author << " (" << s.duration / 60 << ":";
    if (s.duration % 60 < 10) {
        std::cout << "0";
    }
    std::cout << s.duration % 60 << ")\n";
}

/////////////////////////// ГОЛОВНА ПРОГРАМА ///////////////////////////////

int main() {
    Linked2List<Song> playlist1;
    Linked2List<Song> playlist2;
    // Додамо тестові пісні
    playlist1.push_back(Song("Bohemian Rhapsody", "Queen", 354));
    playlist1.push_back(Song("Imagine", "John Lennon", 183));
    playlist1.push_back(Song("Stairway to Heaven", "Led Zeppelin", 482));
    
    int choice; // Змінна, де зберігається вибір наступної дії користувача
    bool running = true; // Змінна, що використовується в якості прапорця, 
    //в разі значення false, програма завершить свою роботу
    
    while (running) {
        print_menu();
        std::cin >> choice; // читаємо з вхідного потоку у змінну код наступної дії програми
        std::cin.ignore(); //для ігнорування \n у вхідному потоці (для нормалізації відображення)
        
        // Умова switch / case для зручності обробки випадків різних значень choise 
        switch (choice) {
            case 1: { // push_back
                char name[256], author[256];
                int dur;
                std::cout << "Назва: ";
                std::cin.getline(name, 256);
                std::cout << "Автор: ";
                std::cin.getline(author, 256);
                std::cout << "Тривалість (сек): ";
                std::cin >> dur;
                playlist1.push_back(Song(name, author, dur));
                std::cout << "Пісню додано!\n";
                break;
            }
            case 2: { // push_front
                char name[256], author[256];
                int dur;
                std::cout << "Назва: ";
                std::cin.getline(name, 256);
                std::cout << "Автор: ";
                std::cin.getline(author, 256);
                std::cout << "Тривалість (сек): ";
                std::cin >> dur;
                playlist1.push_front(Song(name, author, dur));
                std::cout << "Пісню додано на початок!\n";
                break;
            }
            case 3: { // Показати всі (використання iterator)
                if (playlist1.empty()) {
                    std::cout << "Плейлист порожній!\n";
                } else {
                    std::cout << "\n--- ПЛЕЙЛИСТ ---\n";
                    int i = 1;
                    for (auto it = playlist1.begin(); it != playlist1.end(); ++it) {
                        print_song(*it, i++);
                    }
                }
                break;
            }
            case 4: { // Показати в зворотному порядку (reverse_iterator)
                if (playlist1.empty()) {
                    std::cout << "Плейлист порожній!\n";
                } else {
                    std::cout << "\n--- ЗВОРОТНИЙ ПОРЯДОК ---\n";
                    int i = 1;
                    for (auto it = playlist1.rbegin(); it != playlist1.rend(); ++it) {
                        print_song(*it, i++);
                    }
                }
                break;
            }
            case 5: { // pop_back
                if (!playlist1.empty()) {
                    playlist1.pop_back();
                    std::cout << "Останню пісню видалено!\n";
                } else {
                    std::cout << "Плейлист порожній!\n";
                }
                break;
            }
            case 6: { // pop_front
                if (!playlist1.empty()) {
                    playlist1.pop_front();
                    std::cout << "Першу пісню видалено!\n";
                } else {
                    std::cout << "Плейлист порожній!\n";
                }
                break;
            }
            case 7: { // find
                char name[256];
                std::cout << "Введіть назву пісні: ";
                std::cin.getline(name, 256);
                
                bool found = false;
                int pos = 1;
                for (auto it = playlist1.begin(); it != playlist1.end(); ++it, ++pos) {
                    if (strcmp_equal(it->name, name)) {
                        std::cout << "Знайдено!\n";
                        print_song(*it, pos);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << "Пісню не знайдено!\n";
                }
                break;
            }
            case 8: { // remove за предикатом
                playlist1.remove(is_long_song);
                std::cout << "Довгі пісні видалено!\n";
                break;
            }
            case 9: { // sort
                playlist1.sort(compare_by_duration);
                std::cout << "Плейлист відсортовано!\n";
                break;
            }
            case 10: { // size
                std::cout << "Кількість пісень: " << playlist1.size() << "\n";
                break;
            }
            case 11: { // clear
                playlist1.clear();
                std::cout << "Плейлист очищено!\n";
                break;
            }
            case 12: { // swap
                std::cout << "Обмін з другим плейлистом...\n";
                playlist1.swap(playlist2);
                std::cout << "Плейлисти обмінено!\n";
                break;
            }
            case 13: { // merge
                if (playlist2.empty()) {
                    std::cout << "Другий плейлист порожній!\n";
                } else {
                    playlist1.sort(compare_by_duration);
                    playlist2.sort(compare_by_duration);
                    playlist1.merge(playlist2);
                    std::cout << "Плейлисти злито!\n";
                }
                break;
            }
            case 0: { // для завершення користування програмою
                running = false;
                std::cout << "До побачення!\n";
                break;
            }
            // Для інших випадків
            default:
                std::cout << "Невірний вибір!\n";
        }
    }
    return 0;
}