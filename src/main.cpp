#include <iostream>
#include "vector.h"
#include "queue.h"
#include "Stack.h"
using namespace std;
void vector1() {

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

}
void queue1 () {
    cout << "Queue" << endl;
    cout << "====================================" << endl;
    Queue<int> queue1;
    queue1.print("queue1");

    queue1.push(1);
    queue1.print("queue1");

    queue1.push(2);
    queue1.push(3);
    queue1.push(4);
    queue1.print("queue1");

    int d;
    d = queue1.peek();
    cout << "d = " << d << endl;
    Queue<int> queue2 = queue1;
    queue2.print("queue2");
    Queue<int> queue3;
    queue3 = queue1 = queue2;
    queue1.push(975);
    queue2.push(53);
    queue1.print("queue1");
    queue2.pop();
    queue2.print("queue2");
    queue3.isMount("queue3");
    queue3.print("queue3");
    queue2.clear();
    cout << "Elements in queue = " << queue3.ElemCount() << endl;
}
void stack1 () {
	Stack<int> stack_1 { 2, 32, 52, 68, 131 };
	Stack<int> stack_2 { 3, 25, 15, 77, 10, 21 };

	cout << "Stack 1:\n\n" << stack_1 << "\n";
	cout << "Stack 2:\n\n" << stack_2 << "\n";

}
int main()
{
    cout << "Choose structure: " << endl;
    cout << "1. Vector" << endl;
    cout << "2. Queue" << endl;
    cout << "3. Stack" << endl;
    int ans = 0;
    cin >> ans;
    switch (ans) {
        case 1:
            vector1();
            break;
        case 2:
            queue1();
            break;
        case 3:
            stack1();
            break;
        default:
            cout << "Bad input!" << endl;

    }
    return 0;
}
