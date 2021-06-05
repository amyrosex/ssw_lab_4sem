#ifndef CLASS_CIRCULAR_BUFFER_H
#define CLASS_CIRCULAR_BUFFER_H

#include "list.h"

namespace lab
{
	template <class T>
	class circular_buffer
	{
		list<T> m_Container;
		int m_maxSize;
		
		using self = circular_buffer;
		using self_ref = self&;

	public:
		using iterator = typename list<T>::iterator;

		circular_buffer(int size) : m_maxSize(size)
		{
			if (size == 0)
				throw std::runtime_error("size is zero!");
		}

		circular_buffer(const std::initializer_list<T> list) : m_Container(list), m_maxSize(list.size())
		{
			if (list.size() == 0)
				throw std::runtime_error("size is zero!");
		}

		void clear()
		{
			m_Container.clear();
		}
		
		void push(T data)
		{
			m_Container.push_back(data);

			if (m_Container.size() > m_maxSize)
				m_Container.pop_front();
		}

		void pop()
		{
			m_Container.pop_front();
		}

		void insert(iterator it, T data)
		{
			bool position_start = it == begin();
			m_Container.insert(it, data);

			if (m_Container.size() > m_maxSize)
			{
				if (position_start)
					m_Container.erase(begin() + 1);
				else
					m_Container.pop_front();
			}
		}

		void erase(iterator it)
		{
			m_Container.erase(it);
		}
		
		iterator begin() const
		{
			return m_Container.begin();
		}

		iterator end() const
		{
			return m_Container.end();
		}

		void resize(int new_size)
		{
			if (new_size < m_maxSize)
				for (int i = 0; i < m_maxSize - new_size; i++)
					pop();

			m_maxSize = new_size;
		}

		int size() const
		{
			return m_Container.size();
		}

		int max_size() const
		{
			return m_maxSize;
		}
		
		bool operator==(const self_ref buffer) const
		{
			return m_Container == buffer.m_Container;
		}

		bool operator!=(const self_ref buffer) const
		{
			return m_Container != buffer.m_Container;
		}

		bool operator<(const self_ref buffer) const
		{
			return m_Container < buffer.m_Container;
		}

		bool operator>(const self_ref buffer) const
		{
			return m_Container > buffer.m_Container;
		}

		bool operator<=(const self_ref buffer) const
		{
			return m_Container <= buffer.m_Container;
		}

		bool operator>=(const self_ref buffer) const
		{
			return m_Container >= buffer.m_Container;
		}

		void quick_sort()
		{
			m_Container.quick_sort();
		}

		void split_by_value(self_ref buffer_1, self_ref buffer_2, const T& value) const
		{
			int left_count = 0;
			int right_count = 0;

			for (auto it = begin(); it != end(); ++it)
				if (*it < value)
					left_count++;
				else
					right_count++;

			buffer_1.clear();
			buffer_2.clear();

			if (buffer_1.m_maxSize < left_count)
				buffer_1.resize(left_count);
			
			if (buffer_2.m_maxSize < right_count)
				buffer_2.resize(right_count);

			for (auto it = begin(); it != end(); ++it)
				if (*it < value)
					buffer_1.push(*it);
				else
					buffer_2.push(*it);
		}
	};

	template <class T>
	std::ostream& operator<<(std::ostream& stream, const circular_buffer<T>& buff)
	{
		for (auto it = buff.begin(); it != buff.end(); ++it)
			stream << *it << "\n";
		
		return stream;
	}
}

#endif