#pragma once
template<typename KEY, typename VALUE>
class KeyValuePair
{
	KEY key_;
	VALUE value_;
public:
	KeyValuePair(const KEY& key, const VALUE& value);
	KeyValuePair();
	const KEY& key() const;
	const VALUE& value() const;
};

template <typename KEY, typename VALUE>
KeyValuePair<KEY, VALUE>::KeyValuePair(const KEY& key, const VALUE& value) : key_{key}, value_{value}
{
}

template <typename KEY, typename VALUE>
KeyValuePair<KEY, VALUE>::KeyValuePair()
{
	
}

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
