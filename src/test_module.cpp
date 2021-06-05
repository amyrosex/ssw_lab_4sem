#include <iostream>
#include <string>
#include <forward_list>
#include <list>

using std::cout;
using std::string;

#include "test_module.h"
#include "simple_timer.h"
#include "forward_list.h"
#include "list.h"
#include "circular_buffer.h"

static const std::string LINE = "************************************************\n\n";
static const int CALLS_COUNT = 5000000;

void lab::run_test_forward_list()
{
	cout << "Tests for std::forward_list & lab::forward_list...\n\n";

	std::forward_list<int> std_list;
	lab::forward_list<int> lab_list;
	lab::simple_timer timer;
	
	for (int i = 0; i < CALLS_COUNT; i++)
		std_list.push_front(i);

	cout << "Test std::forward_list push_front: " << timer.get_elapsed_ms() << " ms\n";

	timer.reset();

	for (int i = 0; i < CALLS_COUNT; i++)
		lab_list.push_front(i);

	cout << "Test lab::forward_list push_front: " << timer.get_elapsed_ms() << " ms\n\n";

	timer.reset();

	for (int i = 0; i < CALLS_COUNT; i++)
		std_list.insert_after(++std_list.begin(), i);

	cout << "Test std::forward_list insert_after: " << timer.get_elapsed_ms() << " ms\n";

	timer.reset();

	for (int i = 0; i < CALLS_COUNT; i++)
		lab_list.insert(++lab_list.begin(), i);

	cout << "Test lab::forward_list insert: " << timer.get_elapsed_ms() << " ms\n\n";

	timer.reset();

	for (int i = 0; i < CALLS_COUNT / 2; i++)
		std_list.erase_after(++std_list.begin());

	cout << "Test std::forward_list erase_after: " << timer.get_elapsed_ms() << " ms\n";

	timer.reset();

	for (int i = 0; i < CALLS_COUNT / 2; i++)
		lab_list.erase(++lab_list.begin());

	cout << "Test lab::forward_list erase: " << timer.get_elapsed_ms() << " ms\n\n";

	timer.reset();

	while (!std_list.empty())
		std_list.pop_front();

	cout << "Test std::forward_list pop_front: " << timer.get_elapsed_ms() << " ms\n";

	timer.reset();

	while (lab_list.size() != 0)
		lab_list.pop_front();

	cout << "Test lab::forward_list pop_front: " << timer.get_elapsed_ms() << " ms\n\n";
	cout << LINE;
}

void lab::run_test_list()
{
	cout << "Tests for std::list & lab::list...\n\n";

	std::list<int> std_list;
	lab::list<int> lab_list;
	lab::simple_timer timer;

	for (int i = 0; i < CALLS_COUNT; i++)
		std_list.push_front(i);

	cout << "Test std::list push_front: " << timer.get_elapsed_ms() << " ms\n";

	timer.reset();

	for (int i = 0; i < CALLS_COUNT; i++)
		lab_list.push_front(i);

	cout << "Test lab::list push_front: " << timer.get_elapsed_ms() << " ms\n\n";

	timer.reset();

	for (int i = 0; i < CALLS_COUNT; i++)
		std_list.push_back(i);

	cout << "Test std::list push_back: " << timer.get_elapsed_ms() << " ms\n";

	timer.reset();

	for (int i = 0; i < CALLS_COUNT; i++)
		lab_list.push_back(i);

	cout << "Test lab::list push_back: " << timer.get_elapsed_ms() << " ms\n\n";

	timer.reset();

	for (int i = 0; i < CALLS_COUNT; i++)
		std_list.pop_back();

	cout << "Test std::list pop_back: " << timer.get_elapsed_ms() << " ms\n";

	timer.reset();

	for (int i = 0; i < CALLS_COUNT; i++)
		lab_list.pop_back();

	cout << "Test lab::list pop_back: " << timer.get_elapsed_ms() << " ms\n\n";

	timer.reset();

	for (int i = 0; i < CALLS_COUNT; i++)
		std_list.insert(++std_list.begin(), i);

	cout << "Test std::list insert: " << timer.get_elapsed_ms() << " ms\n";

	timer.reset();

	for (int i = 0; i < CALLS_COUNT; i++)
		lab_list.insert(++lab_list.begin(), i);

	cout << "Test lab::list insert: " << timer.get_elapsed_ms() << " ms\n\n";

	timer.reset();

	for (int i = 0; i < CALLS_COUNT / 2; i++)
		std_list.erase(++std_list.begin());

	cout << "Test std::list erase: " << timer.get_elapsed_ms() << " ms\n";

	timer.reset();

	for (int i = 0; i < CALLS_COUNT / 2; i++)
		lab_list.erase(++lab_list.begin());

	cout << "Test lab::list erase: " << timer.get_elapsed_ms() << " ms\n\n";

	timer.reset();

	while (!std_list.empty())
		std_list.pop_front();

	cout << "Test std::list pop_front: " << timer.get_elapsed_ms() << " ms\n";

	timer.reset();

	while (lab_list.size() != 0)
		lab_list.pop_front();

	cout << "Test lab::list pop_front: " << timer.get_elapsed_ms() << " ms\n\n";
	cout << LINE;
}

void lab::run_test_circular_buffer()
{
	cout << "Tests for lab::circular_buffer...\n\n";

	lab::circular_buffer<int> buffer(CALLS_COUNT / 2);
	lab::simple_timer timer;

	for (int i = 0; i < CALLS_COUNT; i++)
		buffer.push(i);

	cout << "Test push: " << timer.get_elapsed_ms() << " ms\n";

	timer.reset();

	for (int i = 0; i < CALLS_COUNT; i++)
		buffer.insert(buffer.begin() + 5, i);
	
	cout << "Test insert: " << timer.get_elapsed_ms() << " ms\n\n";

	timer.reset();

	for (int i = 0; i < CALLS_COUNT / 4; i++)
		buffer.erase(buffer.begin() + 2);

	cout << "Test erase: " << timer.get_elapsed_ms() << " ms\n";

	timer.reset();

	while (buffer.size() != 0)
		buffer.pop();
	
	cout << "Test pop: " << timer.get_elapsed_ms() << " ms\n\n";
	cout << LINE;
}

void lab::run_all_tests()
{
	run_test_forward_list();
	run_test_list();
	run_test_circular_buffer();
}