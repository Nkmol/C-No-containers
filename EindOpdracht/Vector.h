#pragma once
#include <algorithm>

using size_type = size_t;

template <typename T>
class Vector
{
	unsigned int used_;
	unsigned int capacity_;
	T* array_;
public:
	explicit Vector(const size_type& cap);
	explicit Vector();
	~Vector();
	const int& capcity() const;
	const int& used() const;
	void push_back(const T& value);
	void clear();
	const T& operator[](size_type index) const;
	void resize(const size_type& cap);
};

template <typename T>
Vector<T>::Vector(const size_type& cap) : used_{0}, capacity_{cap}, array_{ new T[cap] }
{
}

template <typename T>
Vector<T>::Vector() : Vector(0)
{
}

template <typename T>
Vector<T>::~Vector() {
	delete[] array_;
}

template <typename T>
const int& Vector<T>::capcity() const {
	return capacity_;
}

template <typename T>
const int& Vector<T>::used() const {
	return used_;
}

template <typename T>
void Vector<T>::push_back(const T& value)
{
	if(used_ >= capacity_)
	{
		// https://crntaylor.wordpress.com/2011/07/15/optimal-memory-reallocation-and-the-golden-ratio/
		resize(ceil(capacity_*1.5));
	}

	array_[used_++] = value;
}

template <typename T>
void Vector<T>::clear()
{
	std::fill_n(array_, capacity_, T{});
}

template <typename T>
const T& Vector<T>::operator[](size_type index) const
{
	return array_[index];
}

template <typename T>
void Vector<T>::resize(const size_type& cap)
{
	capacity_ = cap;

	if(capacity_ <= 0)
	{
		capacity_ = 1;
	}

	T* temp = new T[capacity_];

	for (unsigned int i = 0; i < used_; i++)
	{
		temp[i] = array_[i];
	}

	delete[] array_;

	array_ = temp;
}
