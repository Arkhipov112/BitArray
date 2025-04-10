#include <algorithm>
#include <climits>
#include <cmath>
#include <cstring>

#include "bitarray.hpp"

BitArray::BitArray() : bits(nullptr), num_bits(0), capacity(0) {}

BitArray::~BitArray() {
	delete[] bits;
}

BitArray::BitArray(int num_bits, unsigned long value) : num_bits(num_bits), capacity((num_bits + (CHAR_BIT - 1)) / CHAR_BIT) {
	if (num_bits < 0) { throw "Out of range"; }

	bits = new char[capacity];
	std::memset(bits, false, capacity);

	if (num_bits < UL_BIT) {
		value %= static_cast<unsigned long>(std::pow(2, num_bits));
	}

	for (int i = 0; i < num_bits && i < UL_BIT; ++i) {
		if (value & (1UL << i)) {
			set(i);
		}
	}
}

BitArray::BitArray(const BitArray& bitarray) : bits(new char[bitarray.capacity]), num_bits(bitarray.num_bits), capacity(bitarray.capacity) {
	std::memcpy(bits, bitarray.bits, bitarray.capacity);
}

void BitArray::swap(BitArray& bitarray) {
	std::swap(bitarray.bits, bits);
	std::swap(bitarray.num_bits, num_bits);
	std::swap(bitarray.capacity, capacity);
}

void BitArray::clear() {
	delete[] bits;
	bits = nullptr;

	num_bits = 0;
	capacity = 0;
}

void BitArray::resize(int num_bits, bool value) {
	if (num_bits < 0) { throw "Out of range"; }

	if (num_bits >= (capacity * CHAR_BIT) - (CHAR_BIT - 1) && num_bits <= capacity * CHAR_BIT) {
		this->num_bits = num_bits;
		return;
	}

	int new_capacity = (num_bits + (CHAR_BIT - 1)) / CHAR_BIT;
	char* new_bits = new char[new_capacity];

	if (value) {
		std::memset(new_bits, 0xFF, new_capacity);
	}

	else {
		std::memset(new_bits, 0x00, new_capacity);
	}

	int num_copy = std::min(num_bits, this->num_bits);

	std::memcpy(new_bits, bits, num_copy / CHAR_BIT);

	num_copy %= CHAR_BIT;
	for (int i = 0; i < num_copy; ++i) {
		int n = (CHAR_BIT - 1) - i;
		bool bit = (operator[]((new_capacity - 1)* CHAR_BIT + i)) << n;

		bit ? (new_bits[new_capacity - 1] |= (1 << n)) : (new_bits[new_capacity - 1] &= ~(1 << n));
	}

	delete[] bits;
	bits = new_bits;
	this->num_bits = num_bits;
	this->capacity = new_capacity;
}

void BitArray::pushBack(bool value) {
	if (!(num_bits % CHAR_BIT)) {
		int old_num_bits = num_bits;
		resize(2 * num_bits);
		num_bits = old_num_bits;
	}

	++num_bits;

	set(num_bits - 1, value);
}

BitArray& BitArray::set() {
	std::memset(bits, 0xFF, capacity);
	return *this;
}

BitArray& BitArray::set(int n, bool value) {
	if (n < 0 || n >= num_bits) { throw "Out of range"; }

	int byte = n / CHAR_BIT;
	int bit = (CHAR_BIT - 1) - (n % CHAR_BIT);

	value ? bits[byte] |= (1 << bit) : bits[byte] &= ~(1 << bit);

	return *this;
}

BitArray& BitArray::reset() {
	std::memset(bits, 0x00, capacity);
	return *this;
}

BitArray& BitArray::reset(int n) {
	set(n, false);
	return *this;
}

bool BitArray::any() const {
	for (int i = 0; i < num_bits; ++i) {
		if (operator[](i)) { return true; }
	}

	return false;
}

bool BitArray::none() const {
	if (any()) { return false; }

	return true;
}

int BitArray::count() const {
	int result{ 0 };

	for (int i = 0; i < num_bits; ++i) {
		if (operator[](i)) { ++result; }
	}

	return result;
}

int BitArray::size() const {
	return num_bits;
}

bool BitArray::empty() const {
	if (!num_bits) { return true; }

	return false;
}

bool BitArray::operator[](int n) const {
	if (n < 0 || n >= num_bits) { throw "Out of range"; }

	int byte = n / CHAR_BIT;
	int bit = (CHAR_BIT - 1) - (n % CHAR_BIT);

	return bits[byte] & (1 << bit);
}

BitArray& BitArray::operator~() {
	for (int i = 0; i < capacity; ++i) {
		bits[i] = ~bits[i];
	}

	return *this;
}

BitArray& BitArray::operator=(const BitArray& bitarray) {
	bits = new char[bitarray.capacity];
	std::memcpy(bits, bitarray.bits, bitarray.capacity);

	num_bits = bitarray.num_bits;
	capacity = bitarray.capacity;

	return *this;
}

BitArray& BitArray::operator&=(const BitArray& bitarray) {
	int num_min = std::min(bitarray.num_bits, num_bits);

	int last_this = (capacity - 1) * CHAR_BIT + (CHAR_BIT - 1) - (num_bits % CHAR_BIT);
	int last_bitarray = (bitarray.capacity - 1) * CHAR_BIT + (CHAR_BIT - 1) - (bitarray.num_bits % CHAR_BIT);

	for (int i = 0; i < num_min; ++i) {
		set(last_this - i, bitarray[last_bitarray - i] && operator[](last_this - i));
	}

	return *this;
}

BitArray& BitArray::operator|=(const BitArray& bitarray) {
	int num_min = std::min(bitarray.num_bits, num_bits);

	int last_this = (capacity - 1) * CHAR_BIT + (CHAR_BIT - 1) - (num_bits % CHAR_BIT);
	int last_bitarray = (bitarray.capacity - 1) * CHAR_BIT + (CHAR_BIT - 1) - (bitarray.num_bits % CHAR_BIT);

	for (int i = 0; i < num_min; ++i) {
		set(last_this - i, bitarray[last_bitarray - i] || operator[](last_this - i));
	}

	return *this;
}

BitArray& BitArray::operator^=(const BitArray& bitarray) {
	int num_min = std::min(bitarray.num_bits, num_bits);

	int last_this = (capacity - 1) * CHAR_BIT + (CHAR_BIT - 1) - (num_bits % CHAR_BIT);
	int last_bitarray = (bitarray.capacity - 1) * CHAR_BIT + (CHAR_BIT - 1) - (bitarray.num_bits % CHAR_BIT);

	for (int i = 0; i < num_min; ++i) {
		set(last_this - i, bitarray[last_bitarray - i] ^ operator[](last_this - i));
	}

	return *this;
}

BitArray& BitArray::operator>>=(int n) {
	if (n < 0) { throw "Out of range"; }

	if (n >= num_bits) {
		reset();
		return *this;
	}

	for (int i = num_bits - 1; i >= n; --i) {
		set(i, operator[](i - n));
	}

	for (int i = 0; i < n; ++i) {
		reset(i);
	}

	return *this;
}

BitArray& BitArray::operator<<=(int n) {
	if (n < 0) { throw "Out of range"; }

	if (n >= num_bits) {
		reset();
		return *this;
	}

	for (int i = 0; i < num_bits - n; ++i) {
		set(i, operator[](i + n));
	}

	for (int i = num_bits - n; i < num_bits; ++i) {
		reset(i);
	}

	return *this;
}

BitArray BitArray::operator>>(int n) const {
	BitArray result(*this);
	result >>= n;
	return result;
}

BitArray BitArray::operator<<(int n) const {
	BitArray result(*this);
	result <<= n;
	return result;
}

std::string BitArray::toString() const {
	std::string result;

	for (int i = 0; i < num_bits; ++i) {
		result += operator[](i) ? "1" : "0";
	}

	return result;
}

bool operator==(const BitArray& a, const BitArray& b) {
	if (a.num_bits != b.num_bits) {
		return false;
	}

	for (int i = 0; i < a.capacity; ++i) {
		if (a.bits[i] != b.bits[i]) { return false; }
	}

	return true;
}

bool operator!=(const BitArray& a, const BitArray& b) {
	if (a == b) { return false; }

	return true;
}

BitArray operator&(const BitArray& a, const BitArray& b) {
	BitArray result(a);
	result &= b;
	return result;
}

BitArray operator|(const BitArray& a, const BitArray& b) {
	BitArray result(a);
	result |= b;
	return result;
}

BitArray operator^(const BitArray& a, const BitArray& b) {
	BitArray result(a);
	result ^= b;
	return result;
}
