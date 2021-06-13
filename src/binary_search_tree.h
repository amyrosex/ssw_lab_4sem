#ifndef CLASS_BINARY_SEARCH_TREE_H
#define CLASS_BINARY_SEARCH_TREE_H

#include <initializer_list>
#include <iostream>
#include <ostream>
#include <functional>
#include <vector>

using std::cout;
using std::ostream;
using std::function;
using std::vector;

template <class T>
class binary_search_tree
{
	class branch
	{
		friend class binary_search_tree<T>;

		branch* m_Left {};
		branch* m_Right {};
		
		T m_Value;

	public:
		branch() = default;
		branch(T value) : m_Value(value) {}

		const T& get_value() const
		{
			return m_Value;
		}

		const branch* get_left() const
		{
			return m_Left;
		}

		const branch* get_right() const
		{
			return m_Right;
		}
	};

	branch* m_Root {};
	int m_Size {};

	void copy_from_branch(const branch* br)
	{
		if (br == nullptr)
			return;

		push(br->m_Value);
		copy_from_branch(br->m_Left);
		copy_from_branch(br->m_Right);
	}
	
	void clear_branch(branch*& br)
	{
		if (br == nullptr)
			return;

		clear_branch(br->m_Left);
		clear_branch(br->m_Right);

		delete br;
		br = nullptr;
		m_Size--;
	}

public:
	binary_search_tree() = default;
	
	binary_search_tree(const std::initializer_list<T>& list)
	{
		for (auto& value : list)
			push(value);
	}

	binary_search_tree(const binary_search_tree<T>& tree)
	{
		if (this != std::addressof(tree))
		{
			clear_branch(m_Root);
			copy_from_branch(tree.m_Root);
		}
	}

	~binary_search_tree()
	{
		clear_branch(m_Root);
	}
	
	void push(T value)
	{
		function<void(branch*&, T& val)> add_to_branch = [&](branch*& br, T& val)
		{
			if (br == nullptr)
			{
				br = new branch(val);
				m_Size++;
				return;
			}

			if (val < br->m_Value)
				add_to_branch(br->m_Left, val);
			else
				add_to_branch(br->m_Right, val);
		};

		add_to_branch(m_Root, value);
	}

	void pop(T value)
	{
		branch* br = m_Root;
		branch* parent = nullptr;

		while (br != nullptr && br->m_Value != value)
		{
			parent = br;

			if (value < br->m_Value)
				br = br->m_Left;
			else
				br = br->m_Right;
		}

		if (br == nullptr)
			return;

		bool can_delete = false;

		if (br->m_Left == nullptr)
		{
			if (parent != nullptr && parent->m_Left == br)
				parent->m_Left = br->m_Right;

			if (parent != nullptr && parent->m_Right == br)
				parent->m_Right = br->m_Right;

			can_delete = true;
		}
		else if (br->m_Right == nullptr)
		{
			if (parent != nullptr && parent->m_Left == br)
				parent->m_Left = br->m_Left;

			if (parent != nullptr && parent->m_Right == br)
				parent->m_Right = br->m_Left;

			can_delete = true;
		}

		if (can_delete)
		{
			delete br;
			m_Size--;
			return;
		}

		branch* replace = br->m_Right;

		while (replace->m_Left)
			replace = replace->m_Left;

		T replace_value = replace->m_Value;
		pop(replace_value);
		br->m_Value = replace_value;
	}

	const branch* find(T value) const
	{
		branch* br = m_Root;

		while (br != nullptr && br->m_Value != value)
		{
			if (value < br->m_Value)
				br = br->m_Left;
			else
				br = br->m_Right;
		}

		return br;
	}

	int count() const
	{
		return m_Size;
	}

	int height() const
	{
		function<int(const branch*)> branch_height = [&](const branch* br)
		{
			if (br == nullptr)
				return 0;

			int left_height = branch_height(br->m_Left);
			int right_height = branch_height(br->m_Right);

			if (left_height > right_height)
				return left_height + 1;

			return right_height + 1;
		};

		if (m_Root == nullptr)
			return 0;
		
		int left_height = branch_height(m_Root->m_Left);
		int right_height = branch_height(m_Root->m_Right);

		if (left_height > right_height)
			return left_height + 1;
		
		return right_height+ 1;
	}

	vector<int> path(T value) const
	{
		function<vector<int>(T&, branch*, int)> path_to = [&](T& val, branch* br, int current_dist)
		{
			vector<int> vc_paths;

			if (br == nullptr)
				return vc_paths;

			if (br->m_Value == val)
				vc_paths.push_back(current_dist);

			for (auto dist : path_to(val, br->m_Left, current_dist + 1))
				vc_paths.push_back(dist);

			for (auto dist : path_to(val, br->m_Right, current_dist + 1))
				vc_paths.push_back(dist);

			return vc_paths;
		};
		
		vector<int> vc_paths;

		if (m_Root == nullptr)
			return vc_paths;

		if (m_Root->m_Value == value)
			vc_paths.push_back(0);

		for (auto dist : path_to(value, m_Root->m_Left, 1))
			vc_paths.push_back(dist);

		for (auto dist : path_to(value, m_Root->m_Right, 1))
			vc_paths.push_back(dist);

		return vc_paths;
	}

	void print() const
	{
		function<void(const branch*)> print_branch = [&](const branch* br)
		{
			if (br == nullptr)
				return;

			cout << br->m_Value << "\n";
			print_branch(br->m_Left);
			print_branch(br->m_Right);
		};

		print_branch(m_Root);
	}

	const branch* begin() const
	{
		return m_Root;
	}

	const branch* end() const
	{
		return nullptr;
	}

	binary_search_tree<T>& operator=(const binary_search_tree<T>& tree)
	{
		if (this != std::addressof(tree))
		{
			clear_branch(m_Root);
			copy_from_branch(tree.m_Root);
		}

		return *this;
	}

	void swap(binary_search_tree<T>& tree) noexcept
	{
		std::swap(*this, tree);
	}

	void pop_all_by_value(T value)
	{
		while (find(value) != nullptr)
			pop(value);
	}
};

template <class T>
ostream& operator<<(ostream& out, const binary_search_tree<T>& tree)
{
	tree.print();
	return out;
}

#endif