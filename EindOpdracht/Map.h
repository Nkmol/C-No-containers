#pragma once
#include "Vector.h"

template<typename KEY, typename VALUE>
class Map
{
	Vector<KEY> keys_;
	Vector<VALUE> values_;

public:
	void insert(const KEY& key, const VALUE& value);
	Vector<VALUE> find(const KEY& key);
};

template <typename KEY, typename VALUE>
void Map<KEY, VALUE>::insert(const KEY& key, const VALUE& value)
{
	// TODO [HIGH]: Improved by not having double keys
	keys_.push_back(key);
	values_.push_back(value);
}

template <typename KEY, typename VALUE>
Vector<VALUE> Map<KEY, VALUE>::find(const KEY& key)
{
	Vector<VALUE> found;
	for(int i = 0; i < keys_.used(); i++)
	{
		if(keys_[i] == key)
		{
			found.push_back(values_[i]);
		}
	}

	return found;
}
