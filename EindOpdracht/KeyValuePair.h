#pragma once
template <typename KEY, typename VALUE>
class KeyValuePair
{
	KEY key_;
	VALUE value_;
public:
	KeyValuePair(const KEY& key, const VALUE& value);
	KeyValuePair();
	~KeyValuePair();
	KeyValuePair(const KeyValuePair<KEY, VALUE>& other);
	KeyValuePair(KeyValuePair<KEY, VALUE>&& other) noexcept;
	KeyValuePair<KEY, VALUE>& operator=(KeyValuePair<KEY, VALUE> that);
	KeyValuePair<KEY, VALUE>& operator=(KeyValuePair<KEY, VALUE>&& that);
	const KEY& key() const;
	const VALUE& value() const;

	friend void swap(KeyValuePair<KEY, VALUE>& first, KeyValuePair<KEY, VALUE>& second) noexcept //nothrow
	{
		using std::swap;

		// by swapping the members of two objects,
		// the two objects are effectively swapped
		swap(first.key_, second.key_);
		swap(first.value_, second.value_);
	}
};

template <typename KEY, typename VALUE>
KeyValuePair<KEY, VALUE>::KeyValuePair(const KEY& key, const VALUE& value) : key_{key}, value_{value}
{
}

template <typename KEY, typename VALUE>
KeyValuePair<KEY, VALUE>::KeyValuePair() : KeyValuePair(KEY{}, VALUE{})
{
}

#pragma region Rule of five  
template <typename KEY, typename VALUE>
KeyValuePair<KEY, VALUE>::~KeyValuePair()
{
}

// Copy constructor
template <typename KEY, typename VALUE>
KeyValuePair<KEY, VALUE>::KeyValuePair(const KeyValuePair<KEY, VALUE>& other) : KeyValuePair(other.key_ , other.value_)
{
}

// Move constructor
template <typename KEY, typename VALUE>
KeyValuePair<KEY, VALUE>::KeyValuePair(KeyValuePair<KEY, VALUE>&& other) noexcept : KeyValuePair()
{
	swap(*this, other);
}

// Copy assignment
// This is NOT const refence so we can make use of optimized Elide copy
template <typename KEY, typename VALUE>
KeyValuePair<KEY, VALUE>& KeyValuePair<KEY, VALUE>::operator=(KeyValuePair<KEY, VALUE> that)
{
	swap(*this, that);
	return *this;
}

// Move assignment
template <typename KEY, typename VALUE>
KeyValuePair<KEY, VALUE>& KeyValuePair<KEY, VALUE>::operator=(KeyValuePair<KEY, VALUE>&& that)
{
	swap(*this, that);
	return *this;
}

#pragma endregion  Rule of five 

template <typename KEY, typename VALUE>
const KEY& KeyValuePair<KEY, VALUE>::key() const
{
	return key_;
}

template <typename KEY, typename VALUE>
const VALUE& KeyValuePair<KEY, VALUE>::value() const
{
	return value_;
}
