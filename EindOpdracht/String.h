#pragma once
#include "Vector.h"

class String : public Vector<char>
{
public:
	String() noexcept;
	// Implicit
	String(const char* input);

	explicit operator char*() const;
	bool operator==(const char* value) const;
	bool operator==(const String value) const;
	bool operator!=(const char* value) const;
	bool operator!=(const String value) const;
	const int& length() const;
	String substr(int begin, int end) const;
	void remove_spaces() const;
	void erase(int begin, int end);
	size_t find(char* s, size_t pos) const;
	String& operator=(const String& move) = default;

	static const size_t npos = -1;
	static const char nul = '\0';
	static inline int String::stoi(String value);
};


inline std::ostream& operator<<(std::ostream& str, String const& v)
{
	for (int i = 0; i < v.used(); i++)
	{
		str << v[i];
	}

	return str;
}

inline String::String() noexcept
{
}

inline String::String(const char* input)
{
	const int length = strlen(input) + 1;
	clear();

	for (int i = 0; i < length; i++)
	{
		push_back(input[i]);
	}
}

inline String::operator char*() const
{
	return array_;
}

inline bool String::operator==(const char* value) const
{
	for (int i = 0; i < used_; i++)
	{
		if (array_[i] != value[i])
			return false;
	}

	return true;
}

inline bool String::operator==(const String value) const
{
	const auto* a = static_cast<char*>(value);
	return strncmp(array_, a, used_) == 0;
}

inline bool String::operator!=(const char* value) const
{
	for (int i = 0; i < used_; i++)
	{
		if (array_[i] != value[i])
			return true;
	}

	return false;
}

inline bool String::operator!=(const String value) const
{
	return array_ != static_cast<char*>(value);
}

inline const int& String::length() const
{
	// minus nul char
	return used_ - 1;
}

inline String String::substr(int begin, int end) const
{
	String n;
	for (int i = begin; i < end; i++)
	{
		n.push_back(array_[i]);
	}
	n.push_back(nul);

	return n;
}

inline void String::remove_spaces() const
{
	// an alias to iterate through s without moving s
	char* cpy = array_;
	char* temp = array_;

	while (*cpy)
	{
		if (*cpy != ' ')
			*temp++ = *cpy;
		cpy++;
	}
	*temp = 0;
}

inline void String::erase(int begin, int end)
{
	for (int i = 0; i < used_; i++)
	{
		array_[begin + i] = array_[begin + end + i];
	}

	used_ -= end - begin;
}

inline size_t String::find(char* s, size_t pos = 0) const
{
	size_t result = npos;
	for (size_t i = 0; i < used_; i++)
	{
		if (array_[i] == *s)
		{
			result = i;
			break;
		}
	}

	return result;
}

inline int String::stoi(String value)
{
	int i;
	sscanf_s(static_cast<char*>(value), "%d", &i);

	return i;
}
