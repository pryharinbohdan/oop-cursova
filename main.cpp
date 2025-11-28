#include <iostream>
#include <utility>
#include "Linked2List/Linked2List.hpp"

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
    std::cout << "-1  - Надіслати прелік команд знову\n";
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
    
    print_menu(); // Перед початком сесії знайомимо користувача з інтерфейсом роботи з прогрмою

    while (running) {
        std::cout << "====================================\n";
        std::cout << "Ваш вибір: ";
        std::cin >> choice; // читаємо з вхідного потоку у змінну код наступної дії програми
        std::cin.ignore(); //для ігнорування \n у вхідному потоці (для нормалізації відображення)
        std::cout << std::endl << std::endl;
        
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
            case -1: {
                print_menu();
                break;
            }
            // Для інших випадків
            default:
                std::cout << "Невірний вибір!\n";
        }
    }
    return 0;
}