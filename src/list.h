#ifndef CLASS_LIST_H
#define CLASS_LIST_H

#include <ostream>
#include <stdexcept>
#include "quick_sort_array.h"

namespace lab
{
	template <class T>
	class list
	{
		struct node
		{
			node* m_Next {};
			node* m_Prev {};
			
			T m_Data;
			node(T data) : m_Data(data) {}
		};

		using pnode = node*;
		using self = list<T>;
		using self_ref = self&;
		
		pnode m_Head {};
		pnode m_Tail {};
		int m_Size {};

	public:
		class iterator
		{
			friend class self;
			
			pnode m_currentNode;
			const pnode* m_prevNode;
			
			iterator(pnode node, const pnode* prev_node = nullptr) : m_currentNode(node), m_prevNode(prev_node) {}

		public:
			iterator& operator++()
			{
				m_currentNode = m_currentNode->m_Next;
				return *this;
			}

			iterator operator++(int)
			{
				iterator it(*this);
				m_currentNode = m_currentNode->m_Next;
				return it;
			}

			iterator operator+(int step)
			{
				iterator it(*this);

				for (int i = 0; i < step; i++)
					++it;
				
				return it;
			}

			iterator& operator--()
			{
				if (m_currentNode == nullptr)
				{
					m_currentNode = *m_prevNode;
					return *this;
				}
				
				m_currentNode = m_currentNode->m_Prev;
				return *this;
			}

			iterator operator--(int)
			{
				iterator it(*this);
				m_currentNode = m_currentNode->m_Prev;
				return it;
			}

			iterator operator-(int step)
			{
				iterator it(*this);

				for (int i = 0; i < step; i++)
					--it;

				return it;
			}

			T& operator*() const
			{
				return m_currentNode->m_Data;
			}

			bool operator==(const iterator& it) const
			{
				return m_currentNode == it.m_currentNode;
			}

			bool operator!=(const iterator& it) const
			{
				return m_currentNode != it.m_currentNode;
			}
		};

		list() {}

		list(const std::initializer_list<T> list)
		{
			for (auto& data : list)
				push_back(data);
		}

		~list()
		{
			clear();
		}

		void clear()
		{
			while (m_Size != 0)
				pop_front();
		}

		void push_front(T data)
		{
			pnode new_node = new node(data);
			pnode old_head = m_Head;

			m_Head = new_node;
			m_Head->m_Next = old_head;

			if (old_head != nullptr)
				old_head->m_Prev = m_Head;
			
			if (m_Size++ == 0)
				m_Tail = m_Head;
		}

		void push_back(T data)
		{
			if (m_Size == 0)
			{
				push_front(data);
				return;
			}

			pnode new_node = new node(data);
			pnode old_tail = m_Tail;

			m_Tail = new_node;
			m_Tail->m_Prev = old_tail;
			old_tail->m_Next = m_Tail;
			
			m_Size++;
		}

		void pop_front()
		{
			if (m_Size == 0)
				throw std::runtime_error("container is empty!");

			pnode old_head = m_Head;
			
			m_Head = m_Head->m_Next;

			if (m_Head != nullptr)
				m_Head->m_Prev = nullptr;
			
			delete old_head;
			m_Size--;
		}

		void pop_back()
		{
			if (m_Size == 0)
				throw std::runtime_error("container is empty!");

			if (m_Size == 1)
			{
				pop_front();
				return;
			}

			pnode old_tail = m_Tail;

			m_Tail = m_Tail->m_Prev;
			m_Tail->m_Next = nullptr;

			delete old_tail;
			m_Size--;
		}

		void insert(iterator it, T data)
		{
			if (it == begin())
			{
				push_front(data);
				return;
			}

			if (it == end())
			{
				push_back(data);
				return;
			}

			pnode new_node = new node(data);
			pnode prev_node = it.m_currentNode->m_Prev;

			prev_node->m_Next = new_node;
			new_node->m_Prev = prev_node;

			it.m_currentNode->m_Prev = new_node;
			new_node->m_Next = it.m_currentNode;
			
			m_Size++;
		}

		void erase(iterator it)
		{
			if (it == begin())
			{
				pop_front();
				return;
			}

			if (it == end() - 1)
			{
				pop_back();
				return;
			}

			pnode prev_node = it.m_currentNode->m_Prev;
			pnode next_node = it.m_currentNode->m_Next;

			prev_node->m_Next = next_node;
			next_node->m_Prev = prev_node;

			delete it.m_currentNode;		
			m_Size--;
		}

		iterator begin() const
		{
			return iterator(m_Head, nullptr);
		}

		iterator end() const
		{
			return iterator(nullptr, &m_Tail);
		}

		int size() const
		{
			return m_Size;
		}

		bool operator==(const self_ref list) const
		{
			if (this == &list)
				return true;

			if (m_Size == list.m_Size)
			{
				iterator it_1 = begin();
				iterator it_2 = list.begin();

				while (it_1 != end())
					if (*it_1++ != *it_2++)
						return false;

				return true;
			}

			return false;
		}

		bool operator!=(const self_ref list) const
		{
			return !(*this == list);
		}

		bool operator<(const self_ref list) const
		{
			if (this == &list)
				return false;

			iterator it_1 = begin();
			iterator it_2 = list.begin();

			while (it_1 != end() && it_2 != list.end())
			{
				T& data_1 = *it_1++;
				T& data_2 = *it_2++;

				if (data_1 != data_2)
					return data_1 < data_2;
			}

			return m_Size < list.m_Size;
		}

		bool operator>(const self_ref list) const
		{
			return !(*this < list) && *this != list;
		}

		bool operator<=(const self_ref list) const
		{
			return *this < list || *this == list;
		}

		bool operator>=(const self_ref list) const
		{
			return *this > list || *this == list;
		}

		void quick_sort()
		{
			int size = m_Size;
			T* temp_array = new T[size];
			int k = 0;

			for (auto it = begin(); it != end(); ++it)
				temp_array[k++] = *it;

			quick_sort_array<T>(temp_array, size);
			clear();

			for (int i = size - 1; i >= 0; i--)
				push_front(temp_array[i]);

			delete[] temp_array;
		}

		void split_by_value(self_ref list_1, self_ref list_2, const T& value) const
		{
			if (this == &list_1 || this == &list_2)
				throw std::runtime_error("you can't use yourself as a parameter!");

			if (&list_1 == &list_2)
				throw std::runtime_error("you need to pass two different lists!");

			list_1.clear();
			list_2.clear();

			for (auto it = begin(); it != end(); ++it)
				if (*it < value)
					list_1.push_back(*it);
				else
					list_2.push_back(*it);
		}
	};

	template <class T>
	std::ostream& operator<<(std::ostream& stream, const list<T>& list)
	{
		for (auto it = list.begin(); it != list.end(); ++it)
			stream << *it << "\n";

		return stream;
	}
}

#endif