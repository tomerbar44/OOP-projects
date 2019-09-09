#pragma once
#include <iostream> 
using namespace std;

// Class representing a reference counter class 
class Counter {
public:
	// Constructor 
	Counter()
		: m_counter(0) {};

	Counter(const Counter&) = delete;
	Counter& operator=(const Counter&) = delete;

	// Destructor 
	~Counter()
	{
	}

	void reset()
	{
		m_counter = 0;
	}

	unsigned int get()
	{
		return m_counter;
	}

	// Overload post/pre increment 
	void operator++()
	{
		m_counter++;
	}

	void operator++(int)
	{
		m_counter++;
	}

	// Overload post/pre decrement 
	void operator--()
	{
		m_counter--;
	}
	void operator--(int)
	{
		m_counter--;
	}

	// Overloading << operator 
	friend ostream& operator<<(ostream& os, const Counter& counter)
	{
		os << "Counter Value : "
			<< counter.m_counter << endl;
	}

private:
	unsigned int m_counter{};
};