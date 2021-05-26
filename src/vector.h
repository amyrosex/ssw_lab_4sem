#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class MyVector{
int*arr; //arr - это целочисленный указатель, хранящий адрес вектора
int v_capacity; //вместительность вектора
int current_inv; //текущее кол-во эл-тов  в векторе
public:
    MyVector()
    {
        arr = new int[1];
        v_capacity=1; //задание начальной емкости 1 элемента
        current_inv=0; // выделение памяти
    }
    void push(int data) //вставка элемента в структуру в последний индекс
    {
        if (current_inv == v_capacity) { //если кол-во эл-тов равно емкости вектора (значит, места нет)
            int*temp = new int[2*v_capacity]; //удваиваем емкость
            for (int i = 0; i < v_capacity; i++) {   //копируем массив в новый
                temp[i] = arr[i];
            }
            delete[] arr; //удаление старого массива
            v_capacity *=2;
            arr = temp;
        }
        arr[current_inv] = data; //вставляем данные
        current_inv++;
    }
    void push(int data, int index) // добавление элемента в любой индекс
    {
        if (index = v_capacity) //если индекс=емкость, то это
            push(data); //функция, определенная выше
        else
            arr[index]=data; //иначе добавляем элемент
    }
    int get(int index) //извлечение элемента по любому индексу
    {
        if (index<current_inv) //если индекс меньше емкости вектора
            return arr[index]; //извлекаем
    }
    void pop() //удаление последнего элемента
    {
        current_inv--;
    }
    int size() //получение размера вектора
    {
        return current_inv;
    }
int get_capacity() //получение емкости вектора
{
    return v_capacity;
}
    void print() //печать элементов массива
    {
        for (int i = 0; i < current_inv; i++) {
            cout << arr[1] << " ";
        }
        cout << endl;
    }
};

int main()

{

    MyVector v;
    v.push(5);
    v.push(10);
    v.push(15);
    v.push(20);
    v.push(25);

    cout << "Vector size : "
         << v.size() << endl;
    cout << "Vector capacity : "
         << v.get_capacity() << endl;
    cout << "Vector elements : ";
    v.print();
    v.push(100, 1);
    cout << "\nAfter updating 1st index"
         << endl;
    cout << "Vector elements : ";
    v.print();
    cout << "Element at 1st index : "
         << v.get(1) << endl;
    v.pop();
    cout << "\nAfter deleting last element"
         << endl;
    cout << "Vector size : "
         << v.size() << endl;
    cout << "Vector capacity : "
         << v.get_capacity() << endl;
    cout << "Vector elements : ";
    v.print();
    return 0;

}
