#pragma once
#include <algorithm>
#include <iostream>

using size_type = size_t;

template <typename T>
class Vector
{
	/// https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
	/// https://stackoverflow.com/questions/5695548/public-friend-swap-member-function
	friend void swap(Vector<T>& first, Vector<T>& second) noexcept
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

protected:
	T* array_;
	size_type used_;
	size_type capacity_;
public:
	explicit Vector(const size_type& cap);
	Vector() noexcept;
	~Vector();
	Vector(const Vector<T>& other);
	Vector(Vector<T>&& other) noexcept;
	Vector<T>& operator=(Vector<T> that) noexcept;
	Vector<T>& operator=(Vector<T>&& that) noexcept;
	const int& capcity() const noexcept;
	const int& used() const noexcept;
	void push_back(const T& value);
	void clear();
	const T& operator[](const size_type& index) const;
	T& operator[](const size_type& index);
	void resize(const size_type& cap);
	void remove(const size_type& index);
};

template <typename T>
Vector<T>::Vector(const size_type& cap) : array_{new T[cap]}, used_{0}, capacity_{cap}
{
}

template <typename T>
Vector<T>::Vector() noexcept : Vector(0)
{
}

#pragma region Rule of five
template <typename T>
Vector<T>::~Vector()
{
	delete[] array_;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other) : array_{new T[other.capacity_]}, used_{other.used_},
                                            capacity_{other.capacity_}
{
	// Copy data
	// std::copy is marked as unsafe by vsc++
	//std::memcpy(array_, other.array_, other.used_);

	for (size_type i = 0; i < used_; ++i)
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
Vector<T>& Vector<T>::operator=(Vector<T> that) noexcept
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

#pragma endregion Rule of five

template <typename T>
const int& Vector<T>::capcity() const noexcept
{
	return capacity_;
}

template <typename T>
const int& Vector<T>::used() const noexcept
{
	return used_;
}

template <typename T>
void Vector<T>::push_back(const T& value)
{
	if (used_ >= capacity_)
	{
		// https://crntaylor.wordpress.com/2011/07/15/optimal-memory-reallocation-and-the-golden-ratio/
		const auto new_size = static_cast<size_t>(ceil(capacity_ * 1.5));
		resize(new_size);
	}

	array_[used_++] = value;
}

template <typename T>
void Vector<T>::clear()
{
	//std::fill_n(array_, capacity_, T{});
	for (int i = 0; i < used_; i++)
	{
		array_[i] = T{};
	}

	used_ = 0;
}

template <typename T>
const T& Vector<T>::operator[](const size_type& index) const
{
	return array_[index];
}

template <typename T>
T& Vector<T>::operator[](const size_type& index)
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

	if (used_ > capacity_)
	{
		used_ = capacity_;
	}

	T* temp = new T[capacity_];

	for (unsigned int i = 0; i < used_; i++)
	{
		temp[i] = array_[i];
	}

	delete[] array_;

	array_ = temp;
}

template <typename T>
void Vector<T>::remove(const size_type& index)
{
	/*for (int i = 0; i < used_; i++)
	{
		if (i == index)
		{
			*array_[i] = *array_[i + i];
		}
	}*/
}