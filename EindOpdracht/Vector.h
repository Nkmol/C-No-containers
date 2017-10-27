#pragma once
#include <algorithm>
#include <iostream>

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
	Vector(Vector<T>& other);
	Vector(Vector<T>&& other) noexcept;
	Vector<T>& operator=(Vector<T> that);
	Vector<T>& operator=(Vector<T>&& that) noexcept;
	const int& capcity() const;
	const int& used() const;
	void push_back(T& value);
	void clear();
	T& operator[](size_type index) const;
	void resize(const size_type& cap);

	/// https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
	/// https://stackoverflow.com/questions/5695548/public-friend-swap-member-function
	friend void swap(Vector<T>& first, Vector<T>& second) noexcept //nothrow
	{
		// enable ADL (not necessary in our case, but good practice)
		/// https://stackoverflow.com/questions/28130671/how-does-using-stdswap-enable-adl
		using std::swap;

		// by swapping the members of two objects,
		// the two objects are effectively swapped
		swap(first.capacity_, second.capacity_);
		swap(first.used_, second.used_);
		swap(first.array_, second.array_);
	}
};

template <typename T>
Vector<T>::Vector(const size_type& cap) : used_{0}, capacity_{cap}, array_{new T[cap]}
{
}

template <typename T>
Vector<T>::Vector() : Vector(0)
{
}

template <typename T>
Vector<T>::~Vector()
{
	delete[] array_;
}

// Copy constructor
template <typename T>
Vector<T>::Vector(Vector<T>& other) : used_{other.used_}, capacity_{other.capacity_}, array_{new T[other.capacity_]}
{
	// Copy data
	// std::copy is marked as unsafe by vsc++
	//std::memcpy(array_, other.array_, other.used_);

	for (int i = 0; i < used_; ++i)
	{
		array_[i] = other.array_[i];
	}
}

// Move constructor
template <typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept : Vector()
{
	swap(*this, other);
}

// Copy assignment
// This is NOT const refence so we can make use of optimized Elide copy
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> that)
{
	swap(*this, that);
	return *this;
}

// Move assignment
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& that) noexcept
{
	swap(*this, that);
	return *this;
}


template <typename T>
const int& Vector<T>::capcity() const
{
	return capacity_;
}

template <typename T>
const int& Vector<T>::used() const
{
	return used_;
}

template <typename T>
void Vector<T>::push_back(T& value)
{
	if (used_ >= capacity_)
	{
		// https://crntaylor.wordpress.com/2011/07/15/optimal-memory-reallocation-and-the-golden-ratio/
		resize(ceil(capacity_ * 1.5));
	}

	array_[used_++] = value;
}

template <typename T>
void Vector<T>::clear()
{
	std::fill_n(array_, capacity_, T{});
}

template <typename T>
T& Vector<T>::operator[](size_type index) const
{
	return array_[index];
}

template <typename T>
void Vector<T>::resize(const size_type& cap)
{
	capacity_ = cap;

	if (capacity_ <= 0)
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
