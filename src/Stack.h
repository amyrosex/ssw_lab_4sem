#ifndef STACK_INCLUDED_H
#define STACK_INCLUDED_H

#include <stdexcept>
#include <initializer_list>

template <class T>
class Stack
{
private:
	T* data {nullptr};
	int size {0};
	int capacity {0};
	static constexpr int size_additive {4096};

public:
	Stack() = default;

	Stack(const std::initializer_list<T>& list)
	{
		for (auto& element : list)
			push(element);
	}

	Stack(const Stack& stack)
	{
		*this = stack;
	}

	Stack(Stack&& stack)
	{
		*this = std::move(stack);
	}

	~Stack()
	{
		clear();
	}

	void push(T value)
	{
		if (size % size_additive == 0)
		{
			capacity += size_additive;
			T* new_data = new T[capacity];

			for (int i = 0; i < size; i++)
				new_data[i] = data[i];

			delete[] data;
			data = new_data;
		}

		data[size++] = value;
	}

	void pop()
	{
		if (size == 0)
			throw std::runtime_error("Stack is empty!");

		if (--size % size_additive == 0)
		{
			capacity -= size_additive;
			T* new_data = new T[capacity];

			for (int i = 0; i < size; i++)
				new_data[i] = data[i];

			delete[] data;
			data = new_data;
		}
	}

	T& peek()
	{
		if (size == 0)
			throw std::runtime_error("Stack is empty!");

		return data[size - 1];
	}

	int count() const
	{
		return size;
	}

	int max_count() const
	{
		return capacity;
	}

	void clear()
	{
		if (data)
		{
			delete[] data;
			size = 0;
			capacity = 0;
		}
	}

	Stack<T>& operator=(const Stack<T>& stack)
	{
		if (this == &stack)
			return *this;

		clear();

		size = stack.size;
		capacity = stack.capacity;
		data = new T[capacity];

		for (int i = 0; i < size; i++)
			data[i] = stack.data[i];

		return *this;
	}

	Stack<T>& operator=(Stack<T>&& stack)
	{
		if (this == &stack)
			return *this;

		clear();

		size = stack.size;
		capacity = stack.capacity;
		data = stack.data;

		stack.size = 0;
		stack.capacity = 0;
		stack.data = nullptr;

		return *this;
	}

	bool operator==(const Stack<T>& stack) const
	{
		if (this == &stack)
			return true;

		if (size != stack.size)
			return false;

		for (int i = 0; i < size; i++)
			if (data[i] != stack.data[i])
				return false;

		return true;
	}

	bool operator!=(const Stack<T>& stack) const
	{
		return !(*this == stack);
	}

	bool operator<(const Stack<T>& stack) const
	{
		if (this == &stack)
			return false;

		int result_size = (size < stack.size) ? size : stack.size;

		for (int i = 0; i < result_size; i++)
			if (data[i] != stack.data[i])
				return data[i] < stack.data[i];

		return size < stack.size;
	}

	bool operator>(const Stack<T>& stack) const
	{
		return !(*this < stack) && (*this != stack);
	}

	bool operator<=(const Stack<T>& stack) const
	{
		return (*this < stack) || (*this == stack);
	}

	bool operator>=(const Stack<T>& stack) const
	{
		return (*this > stack) || (*this == stack);
	}

	friend std::ostream& operator<<(std::ostream& stream, const Stack<T>& stack)
	{
		for (int i = stack.size - 1; i >= 0; i--)
			stream << stack.data[i] << "\n";

		return stream;
	}
};

#endif