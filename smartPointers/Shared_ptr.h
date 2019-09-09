#pragma once
#include "Counter.h"

template <class T>
class Shared_ptr {
public:
	// Constructor 
	/*explicit */Shared_ptr(T* ptr = nullptr)
	{
		m_ptr = ptr;
		m_counter = new Counter();
		if (ptr) {
			(*m_counter)++;
		}
	}

	// Copy constructor 
	Shared_ptr(const Shared_ptr<T>& sp)
	{
		m_ptr = sp.m_ptr;
		m_counter = sp.m_counter;
		(*m_counter)++;
	}

	Shared_ptr<T>& operator=(Shared_ptr<T>& rhs)
	{
		if (this->m_ptr != rhs.m_ptr)
		{
			if (m_counter != 0)
			{
				(*m_counter)--;
				if (m_counter->get() <= 0)
				{
					delete m_ptr;
					delete m_counter;
				}
			}
			m_ptr = rhs.m_ptr;
			m_counter = rhs.m_counter;
			(*m_counter)++;
		}
		return *this;
	}

	// Reference count 
	unsigned int use_count()
	{
		return m_counter->get();
	}

	// Get the pointer 
	T* operator->() { return m_ptr; }
	
	// Destructor 
	~Shared_ptr()
	{
		(*m_counter)--;
		if (m_counter->get() == 0) {
			delete m_counter;
			delete m_ptr;
		}
	}

	friend ostream& operator<<(ostream& os, Shared_ptr<T>& sp)
	{
		os << "Address pointed : "
			<< sp.get() << endl;
		cout << *(sp.m_counter) << endl;
	}

private:
	// Reference counter 
	Counter* m_counter;

	// Shared pointer 
	T* m_ptr;
};

