#pragma once

template <typename T>
class Vector
{
	int used_;
	size_t capacity_;
	T* array_;
public:
	explicit Vector(const size_t& cap);
	~Vector();
	const size_t& capcity() const;
};

template <typename t>
Vector<t>::Vector(const size_t& cap) : used_{0}, capacity_{cap}, array_{ new t[cap] }
{
}

template <typename t>
Vector<t>::~Vector() {
	delete[] array_;
}

template <typename t>
const size_t& Vector<t>::capcity() const {
	return capacity_;
}
