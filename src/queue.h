#include <iostream>
#include <new>
using namespace std;
// Реализация очереди
template <class T>
class Queue
{
private:
    T* p; // динамический массив
    int count; // кол-во элементов

public:
    Queue()
    {
        count = 0; // в конструкторе по умолчанию очередь пустая
    }

    // конструктор копирования
    Queue(const Queue& other)
    {
        count = other.count;

        try {
            // выделяем память для T
            p = new T[count];
            // и заполняем значениями
            for (int i = 0; i < count; i++)
                p[i] = other.p[i];
        }
        catch (bad_alloc e)
        {
            // ловим ошибку, если память не выделилась
            cout << e.what() << endl;
            count = 0; // создаем пустую очередь
        }
    }

    // вставка элемента в структуру
    void push(T item)
    {
        T* p2; // доп. указатель
        p2 = p; // перенаправляем доп. указатель

        try {
            // новый фрагмент памяти для T (но +1)
            p = new T[count + 1];

            // присваиваем данные с указателя на p2 в p
            for (int i = 0; i < count; i++)
                p[i] = p2[i];

            // скопировать последний элемент и инкрементировать count
            p[count] = item;
            count++;

            if (count > 1)
                delete[] p2;
        }
        catch (bad_alloc e)
        {
            // если память не выделена
            cout << e.what() << endl; // вывести сообщение об ошибке

            // вернуть старый указатель на p
            p = p2;
        }
    }

    // выталкивание элемента из структуры
    T pop()
    {
        if (count == 0)
            return 0;

        // заполнить элемент, который вытягивается из очереди
        T item;

        item = p[0];

        // новый участок памяти, который меньше на 1
        try {
            T* p2;

            p2 = new T[count - 1];

            count--; // декрементируем count

            for (int i = 0; i < count; i++)
                p2[i] = p[i + 1]; // копируются все кроме первого элемента

            if (count > 0)
                delete[] p;

            // перенаправляем p на p2
            p = p2;

            // возвращаем item
            return item;
        }
        catch (bad_alloc e)
        {
            // если память не выделилась, то вернуть 0
            cout << e.what() << endl;
            return 0;
        }
    }

    // перегрузка оператора равенства
    Queue& operator= (const Queue& other)
    {
        T* p2; // указатель на дополнительную память

        try {
            // попытка выделить новый участок памяти для p2
            p2 = new T[other.count];

            // если память выделена успешно, освобождаем выделенную память
            if (count > 0)
                delete[] p;

            // копируем other в текущий объект
            p = p2;
            count = other.count;

            // заполняем значениями
            for (int i = 0; i < count; i++)
                p[i] = other.p[i];
        }
        catch (bad_alloc e)
        {
            // если память не выделилась, то выводим ошибку
            cout << e.what() << endl;
        }
        return *this;
    }

    ~Queue()
    {
        if (count > 0)
            delete[] p;
    }

    // возврат первого элемента структуры
    T peek()
    {
        if (count > 0)
            return p[0];
        else
            return 0;
    }

    // очистка очереди
    void clear()
    {
        if (count > 0)
        {
            delete[] p;
            count = 0;
        }
    }

    // проверка существования элементов в очереди
    bool IsEmpty()
    {
        return count == 0;
    }

    // количество элементов в очереди
    int ElemCount()
    {
        return count;
    }

    // вывод метода на экран
    void print(const char* objName)
    {
        cout << "Object: " << objName << endl;
        for (int i = 0; i < count; i++)
            cout << p[i] << "\t";
            cout << endl;
        cout << "---------------------" << endl;
    }
    // проверка горной последовательности
    void isMount (const char* objName) {
        cout << "Object: " << objName << endl;
        bool mount;
        if (count >= 3) {

            for (int i = 0; i < count; i++) {
                if (p[i] < p[i + 1]) {
                    mount = true;
                } else {
                    mount = false;
                }
            }
            if (mount) {
                cout << "Mount-like sequence check = True" << endl;
            } else {
                cout << "Mount-like sequence check = False" << endl;
            }

        } else {
            cout << "Less than 3 elements!" << endl;
        }
    }
};