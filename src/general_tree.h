#ifndef CLASS_GENERAL_TREE_H
#define CLASS_GENERAL_TREE_H

#include <initializer_list>
#include <iostream>
#include <ostream>
#include <functional>
#include <vector>

using std::cout;
using std::ostream;
using std::function;
using std::vector;

template <typename T>
class general_tree
{
	struct branch
	{
		T m_Value;

		branch* m_Son {};
		branch* m_Brother {};

		branch() = default;
		branch(T value) : m_Value(value) {}
	};
	
	branch* m_Root {};
	int m_Size {};

	void clear_branch(branch* br)
	{
		if (br == nullptr)
			return;
		
		clear_branch(br->m_Son);
		clear_branch(br->m_Brother);
		
		delete br;
		br = nullptr;
		m_Size--;
	}
		
	branch* find_branch_before_brother(branch* br, branch* element)
	{
		branch* local = nullptr;
		
		if (br == nullptr)
			return nullptr;
		
		if (br->m_Brother == element)
			return br;
		
		local = find_branch_before_brother(br->m_Son, element);
		
		if (local != nullptr)
			return local;
		
		local = find_branch_before_brother(br->m_Brother, element);
		
		if (local != nullptr)
			return local;
		
		return local;
	}
	
	branch* find_before_branch(branch* br, branch* searchable)
	{
		branch* local = nullptr;
		
		if (br == nullptr)
			return nullptr;
		
		if (br->m_Son == searchable)
			return br;
		
		local = find_before_branch(br->m_Son, searchable);
		
		if (local != nullptr)
			return local;
		
		local = find_before_branch(br->m_Brother, searchable);
		
		if (local != nullptr)
			return local;
		
		return local;
	}
	
	branch* find_branch_by_value(branch* br, T value)
	{
		branch* local = nullptr;
		
		if (br == nullptr)
			return nullptr;
		
		if (br->m_Value == value)
			return br;
		
		local = find_branch_by_value(br->m_Son, value);
		
		if (local != nullptr)
			return local;
		
		local = find_branch_by_value(br->m_Brother, value);
		
		if (local != nullptr)
			return local;
		
		if (local == nullptr && br == m_Root)
			throw std::runtime_error("Current value not found!");
		
		return local;
	}
	
	int path_to_need_branch(const branch* br, const branch* need) const
	{
		if (br == nullptr)
			return 0;
		
		int local = 0;
		
		if (br == need)
			return 1;
		
		if (local == 0)
			local = path_to_need_branch(br->m_Son, need);
		
		if (local != 0)
			return local + 1;
		
		if (local == 0)
			local = path_to_need_branch(br->m_Brother, need);
		
		if (local != 0)
			return local;
		
		if (local == 0 && br == m_Root)
			throw std::runtime_error("Current value not found!");
		
		return local;
	}

	int path_to_branch_value(branch* br, T value) {
		if (br == nullptr)
			return 0;
		
		int steps = 0;
		
		if (br->m_Value == value)
			return 1;
		
		if (steps == 0)
			steps = path_to_branch_value(br->m_Son, value);
		
		if (steps != 0)
			return steps + 1;
		
		if (steps == 0)
			steps = path_to_branch_value(br->m_Brother, value);
		
		if (steps != 0)
			return steps;
		
		if (steps == 0 && br == m_Root)
			throw std::underflow_error("Element is not found");
		
		return steps;
	}

public:
	general_tree() = default;
	
	~general_tree()
	{
		clear_branch(m_Root);
	}
	
	void push(T position, T value)
	{
		function<void(branch*, T, T)> add_to_branch = [&](branch* br, T pos, T val)
		{
			if (br == nullptr)
			{
				br = new branch(val);
				return;
			}

			br = find_branch_by_value(br, pos);

			if (br->m_Son == nullptr)
			{
				br->m_Son = new branch(val);
				return;
			}

			br = br->m_Son;

			while (br->m_Brother != nullptr)
				br = br->m_Brother;

			br->m_Brother = new branch(val);
		};
		
		add_to_branch(m_Root, position, value);
		m_Size++;
	}
	
	void pop(T value)
	{
		function<void(branch*, T)> remove_value = [&](branch* br, T val)
		{
			if (br == nullptr)
				return;
			
			branch* local;

			branch* need_br = find_branch_by_value(br, val);
			branch* before_br = find_before_branch(br, need_br);

			if (before_br == nullptr)
			{
				before_br = find_branch_before_brother(br, need_br);

				if (before_br == nullptr && need_br == br)
				{
					m_Root = br->m_Son;
					delete need_br;
				}
				else
				{
					if (need_br->m_Son != nullptr)
					{
						if (before_br->m_Son != nullptr)
						{
							local = before_br->m_Son;

							while (local->m_Brother != nullptr)
								local = local->m_Brother;

							local->m_Brother = need_br->m_Son;
						}
						else
							before_br->m_Son = need_br->m_Son;
					}

					if (need_br->m_Brother != nullptr)
						before_br->m_Brother = need_br->m_Brother;
					else
						before_br->m_Brother = nullptr;

					need_br->m_Son = nullptr;
					need_br->m_Brother = nullptr;

					delete need_br;
				}
			}
			else
			{
				if (need_br->m_Brother != nullptr)
				{
					if (need_br->m_Son != nullptr)
					{
						local = need_br->m_Brother;

						if (local->m_Son != nullptr)
						{
							local = local->m_Son;

							while (local->m_Brother != nullptr)
								local = local->m_Brother;

							local->m_Brother = need_br->m_Son;
						}
						else
							local->m_Son = need_br->m_Son;
					}
					before_br->m_Son = need_br->m_Brother;
				}
				else
				{
					if (need_br->m_Son != nullptr)
						before_br->m_Son = need_br->m_Son;
					else
						before_br->m_Son = nullptr;
				}

				need_br->m_Son = nullptr;
				need_br->m_Brother = nullptr;

				delete need_br;
			}
		};
		
		remove_value(m_Root, value);
		m_Size--;
	}

	const branch* find(T value) 
	{
		return find_branch_by_value(m_Root, value);
	}
	
	int count() const
	{
		return m_Size;
	}

	int height() const
	{
		function<int(branch*)> branch_height = [&](branch* br)
		{
			if (br == nullptr)
				return 0;

			int height_max = 0;

			for (branch* current_br = br->m_Son; current_br != nullptr; current_br = current_br->m_Brother)
			{
				int current_height = branch_height(current_br);

				if (current_height > height_max)
					height_max = current_height;
			}

			return height_max + 1;
		};

		return branch_height(m_Root);
	}

	vector<int> path(T position) const
	{
		function<vector<int>(vector<int>&, const branch*, T)> path_to = [&](vector<int>& paths_vc, const branch* br, T pos)
		{
			if (br == nullptr)
				return paths_vc;
			
			if (br->m_Value == pos)
				paths_vc.push_back(path_to_need_branch(m_Root, br) - 1);

			if (br->m_Son != nullptr)
				path_to(paths_vc, br->m_Son, pos);

			if (br->m_Brother != nullptr)
				path_to(paths_vc, br->m_Brother, pos);

			return paths_vc;
		};

		vector<int> paths_vc;
		return path_to(paths_vc, m_Root, position);
	}
	
	void print() const
	{
		function<void(branch*, int)> print_br = [&](branch* br, int ret)
		{
			if (br == nullptr)
				return;

			for (int i = 0; i < ret; i++)
				cout << " ";

			cout << br->m_Value << "\n";

			if (br->m_Son != nullptr)
				print_br(br->m_Son, ret + 1);

			if (br->m_Brother != nullptr)
				print_br(br->m_Brother, ret);
		};
		
		print_br(m_Root, 0);
	}
};

template <class T>
ostream& operator<<(ostream& out, const general_tree<T>& tree)
{
	tree.print();
	return out;
}

#endif
