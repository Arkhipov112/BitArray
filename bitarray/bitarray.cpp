#include <algorithm>
#include <climits>
#include <cmath>
#include <stdexcept>
#include <cstring>

#include "bitarray.hpp"

namespace {
	const int UL_BIT = 32;
}

namespace {
	inline int getCapacityByNumBits(int num_bits) {
		return (num_bits + (CHAR_BIT - 1)) / CHAR_BIT;
	}

	inline int getByteInCapacity(int n) {
		return n / CHAR_BIT;
	}

	inline int getBitInByte(int n) {
		return (CHAR_BIT - 1) - (n % CHAR_BIT);
	}
}

BitArray::BitArray() : num_bits(0), capacity(0), bits(nullptr) {}

BitArray::~BitArray() {
	delete[] bits;
}

BitArray::BitArray(int num_bits, unsigned long value) : num_bits(num_bits), capacity(getCapacityByNumBits(num_bits)), bits(new char[capacity]) {
	if (num_bits < 0) { throw std::out_of_range("The number of bits cannot be negative"); }

	std::memset(bits, false, capacity);

	if (num_bits < UL_BIT) {
		value %= static_cast<unsigned long>(std::pow(2, num_bits));
	}

	for (int i = 0; i < std::min(num_bits, UL_BIT); ++i) {
		if (value & (1UL << i)) {
			set(i);
		}
	}
}

BitArray::BitArray(const BitArray& bitarray) : num_bits(bitarray.num_bits), capacity(getCapacityByNumBits(bitarray.num_bits)), bits(new char[capacity]) {
	std::memcpy(bits, bitarray.bits, capacity);
}

void BitArray::swap(BitArray& bitarray) {
	std::swap(bitarray.bits, bits);
	std::swap(bitarray.num_bits, num_bits);
	std::swap(bitarray.capacity, capacity);
}

void BitArray::clear() {
	num_bits = 0;
}

void BitArray::resize(int num_bits, bool value) {
	if (num_bits < 0) { throw std::out_of_range("The number of bits cannot be negative"); }

	if (num_bits <= this->num_bits) { this->num_bits = num_bits; return; }

	int old_num_bits = this->num_bits;
	this->num_bits = num_bits;

	int new_capacity = getCapacityByNumBits(num_bits);
	if (new_capacity > capacity) {
		char* new_bits = new char[new_capacity];

		int bit_value = value ? 0xFF : 0x00;
		std::memset(new_bits, bit_value, new_capacity);

		std::memcpy(new_bits, bits, getCapacityByNumBits(old_num_bits));

		delete[] bits;
		bits = new_bits;

		capacity = new_capacity;
	}

	else {
		for (int i = 0; i < num_bits - old_num_bits; ++i) {
			set((num_bits - 1) + i, value);
		}
	}
}

void BitArray::pushBack(bool value) {
	resize(num_bits + 1, value);
}

BitArray& BitArray::set() {
	std::memset(bits, 0xFF, getCapacityByNumBits(num_bits));
	return *this;
}

BitArray& BitArray::set(int n, bool value) {
	if (n < 0 || n >= num_bits) { throw std::out_of_range("Out of range"); }

	value ? bits[getByteInCapacity(n)] |= (1 << getBitInByte(n)) : bits[getByteInCapacity(n)] &= ~(1 << getBitInByte(n));

	return *this;
}

BitArray& BitArray::reset() {
	std::memset(bits, 0x00, getCapacityByNumBits(num_bits));
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
	return !any();
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
	return !num_bits;
}

bool BitArray::operator[](int n) const {
	if (n < 0 || n >= num_bits) { throw std::out_of_range("Out of range"); }

	return bits[getByteInCapacity(n)] & (1 << getBitInByte(n));
}

BitArray& BitArray::operator~() {
	for (int i = 0; i < capacity; ++i) {
		bits[i] = ~bits[i];
	}

	return *this;
}

BitArray& BitArray::operator=(const BitArray& bitarray) {
	if (&bitarray == this) {
		return *this;
	}

	resize(bitarray.num_bits);
	memcpy(bits, bitarray.bits, num_bits);
  
	return *this;
}

BitArray& BitArray::operator&=(const BitArray& bitarray) {
	int capacity_min = std::min(getCapacityByNumBits(bitarray.num_bits), getCapacityByNumBits(num_bits));

	for (int i = 0; i < capacity_min; ++i) {
		bits[(getCapacityByNumBits(num_bits) - 1) - i] &= bitarray.bits[(getCapacityByNumBits(bitarray.num_bits) - 1) - i];
	}

	return *this;
}

BitArray& BitArray::operator|=(const BitArray& bitarray) {
	int capacity_min = std::min(getCapacityByNumBits(bitarray.num_bits), getCapacityByNumBits(num_bits));

	for (int i = 0; i < capacity_min; ++i) {
		bits[(getCapacityByNumBits(num_bits) - 1) - i] |= bitarray.bits[(getCapacityByNumBits(bitarray.num_bits) - 1) - i];
	}

	return *this;
}

BitArray& BitArray::operator^=(const BitArray& bitarray) {
	int capacity_min = std::min(getCapacityByNumBits(bitarray.num_bits), getCapacityByNumBits(num_bits));

	for (int i = 0; i < capacity_min; ++i) {
		bits[(getCapacityByNumBits(num_bits) - 1) - i] ^= bitarray.bits[(getCapacityByNumBits(bitarray.num_bits) - 1) - i];
	}

	return *this;
}

BitArray& BitArray::operator>>=(int n) {
	if (n < 0) { throw std::out_of_range("Out of range"); }

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
	if (n < 0) { throw std::out_of_range("Out of range"); }

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
	return !(a == b);
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