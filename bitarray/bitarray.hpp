#pragma once
#include <string>

class BitArray {
public:
	friend bool operator==(const BitArray& a, const BitArray& b);
	friend bool operator!=(const BitArray& a, const BitArray& b);
	friend BitArray operator&(const BitArray& a, const BitArray& b);
	friend BitArray operator|(const BitArray& a, const BitArray& b);
	friend BitArray operator^(const BitArray& a, const BitArray& b);

	BitArray();
	~BitArray();
	explicit BitArray(int num_bits, unsigned long value = 0);
	BitArray(const BitArray& bitarray);

	void swap(BitArray& bitarray);
	void clear();

	void resize(int num_bits, bool value = false);
	void pushBack(bool value);

	BitArray& set();
	BitArray& set(int n, bool value = true);
	BitArray& reset();
	BitArray& reset(int n);

	bool any() const;
	bool none() const;
	int count() const;
	int size() const;
	bool empty() const;

	bool operator[](int n) const;
	BitArray& operator~();
	BitArray& operator=(const BitArray& bitarray);
	BitArray& operator&=(const BitArray& bitarray);
	BitArray& operator|=(const BitArray& bitarray);
	BitArray& operator^=(const BitArray& bitarray);
	BitArray& operator>>=(int n);
	BitArray& operator<<=(int n);
	BitArray operator>>(int n) const;
	BitArray operator<<(int n) const;

	std::string toString() const;

private:
	char* bits;
	int num_bits;
	int capacity;
};

bool operator==(const BitArray& a, const BitArray& b);
bool operator!=(const BitArray& a, const BitArray& b);

BitArray operator&(const BitArray& a, const BitArray& b);
BitArray operator|(const BitArray& a, const BitArray& b);
BitArray operator^(const BitArray& a, const BitArray& b);