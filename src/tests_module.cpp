#include "tests_module.h"
#include "binary_search_tree.h"
#include "general_tree.h"

#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

class simple_timer
{
	steady_clock::time_point start;

public:
	simple_timer()
	{
		reset();
	}

	void reset()
	{
		start = steady_clock::now();
	}

	long long get_elapsed_ms() const
	{
		return duration_cast<milliseconds>(steady_clock::now() - start).count();
	}
};

void test_binary_search_tree()
{
	srand(time(0));
	
	binary_search_tree<int> tree;
	simple_timer timer;

	cout << "Test binary search tree...\n\n";
	
	for (int i = 0; i < 200000; i++)
		tree.push(rand() % 5001);

	tree.push(6000);
	tree.push(6423);
	tree.push(74574);
	tree.push(43242);
	tree.push(85241);
	tree.push(7777777);

	cout << "Push 200000 elements time: " << timer.get_elapsed_ms() << " ms\n\n";
	
	timer.reset();
	cout << "Path to 85241: " << *tree.path(85241).begin() << "\n";
	cout << "Calc path to 85241 time: " << timer.get_elapsed_ms() << " ms\n\n";
	
	timer.reset();
	cout << "Height: " << tree.height() << "\n";
	cout << "Calculate height time: " << timer.get_elapsed_ms() << " ms\n\n";

	timer.reset();
	tree.pop(6000);
	tree.pop(6423);
	tree.pop(74574);
	tree.pop(43242);
	tree.pop(85241);
	cout << "Pop 5 elements time: " << timer.get_elapsed_ms() << " ms\n";
	
	timer.reset();
	tree.find(7777777);
	cout << "Find value 7777777 time: " << timer.get_elapsed_ms() << " ms\n\n";

	binary_search_tree<int> tree2 { 25, 51, 15, 835, 414, 4156, 511, 62 };
	cout << "Binary search tree created with init list:\n\n" << tree2 << "\n";
	
	cout << "###################################\n\n";
}

void test_general_tree()
{
	srand(time(0));

	general_tree<int> tree;
	simple_timer timer;

	cout << "Test general tree...\n\n";
	
	for (int i = 0; i < 200000; i++)
		tree.push(i, i + rand() % 5001);

	tree.push(200001, 6000);
	tree.push(200002, 6423);
	tree.push(200003, 74574);
	tree.push(200004, 43242);
	tree.push(200005, 85241);
	tree.push(200006, 7777777);
	
	cout << "Push 200000 elements time: " << timer.get_elapsed_ms() << " ms\n";

	timer.reset();
	tree.pop(6000);
	tree.pop(6423);
	tree.pop(74574);
	tree.pop(43242);
	tree.pop(85241);

	cout << "Pop 5 elements time: " << timer.get_elapsed_ms() << " ms\n";

	timer.reset();
	tree.find(7777777);
	cout << "Find value 7777777 time: " << timer.get_elapsed_ms() << " ms\n\n";
}