#ifndef QUICK_SORT_ARRAY_H
#define QUICK_SORT_ARRAY_H

#include <utility>
#include <stdexcept>

namespace lab
{
	template <typename T>
	void quick_sort_array(T* array, int size)
	{
		if (array == nullptr || size == 0)
			throw std::runtime_error("invalid one or two arguments!");

		T& center = array[size / 2];

		int i = 0;
		int j = size - 1;

		do
		{
			while (array[i] < center)
				i++;

			while (array[j] > center)
				j--;

			if (i <= j)
				std::swap(array[i++], array[j--]);
		} while (i <= j);

		if (j > 0)
			quick_sort_array(array, j + 1);

		if (i < size)
			quick_sort_array(&array[i], size - i);
	}
}

#endif