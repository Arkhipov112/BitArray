#include <iostream>

#include "../googletest/googletest/include/gtest/gtest.h"

#include "../bitarray/bitarray.hpp"

TEST(BitArrayTest, DefaultConstructor) {
    BitArray bitarray;

    EXPECT_EQ(bitarray.size(), 0);
    EXPECT_TRUE(bitarray.empty());
}

TEST(BitArrayTest, OverloadedConstructor) {
    BitArray bitarray(16, 32);
    
    EXPECT_EQ(bitarray.size(), 16);
    EXPECT_EQ(bitarray.toString(), "0000000000100000");
}

TEST(BitArrayTest, CopyConstructor) {
    BitArray bitarray1(16, 32);
    BitArray bitarray2(bitarray1);

    EXPECT_EQ(bitarray2.size(), 16);
    EXPECT_EQ(bitarray2.toString(), "0000000000100000");
}

TEST(BitArrayTest, Swap) {
    BitArray bitarray1(16, 32);
    BitArray bitarray2(8, 6);
    bitarray1.swap(bitarray2);

    EXPECT_EQ(bitarray1.size(), 8);
    EXPECT_EQ(bitarray1.toString(), "00000110");

    EXPECT_EQ(bitarray2.size(), 16);
    EXPECT_EQ(bitarray2.toString(), "0000000000100000");
}

TEST(BitArrayTest, Clear) {
    BitArray bitarray(16, 32);
    bitarray.clear();

    EXPECT_EQ(bitarray.size(), 0);
    EXPECT_TRUE(bitarray.empty());
}

TEST(BitArrayTest, Resize) {
    BitArray bitarray(8, 6);
    bitarray.resize(16, false);

    EXPECT_EQ(bitarray.size(), 16);
    EXPECT_EQ(bitarray.toString(), "0000011000000000");

    bitarray.resize(20, true);

    EXPECT_EQ(bitarray.size(), 20);
    EXPECT_EQ(bitarray.toString(), "00000110000000001111");
}

TEST(BitArrayTest, PushBack) {
    BitArray bitarray(8, 6);
    bitarray.pushBack(true);

    EXPECT_EQ(bitarray.size(), 9);
    EXPECT_EQ(bitarray.toString(), "000001101");

    bitarray.pushBack(false);

    EXPECT_EQ(bitarray.size(), 10);
    EXPECT_EQ(bitarray.toString(), "0000011010");
}

TEST(BitArrayTest, DefaultSet) {
    BitArray bitarray(8, 6);
    bitarray.set();

    EXPECT_EQ(bitarray.toString(), "11111111");
}

TEST(BitArrayTest, OverloadedSet) {
    BitArray bitarray(8, 6);
    bitarray.set(0, true);
    bitarray.set(6, false);

    EXPECT_EQ(bitarray.toString(), "10000100");
}

TEST(BitArrayTest, DefaultReset) {
    BitArray bitarray(8, 6);
    bitarray.reset();

    EXPECT_EQ(bitarray.toString(), "00000000");
}

TEST(BitArrayTest, OverloadedReset) {
    BitArray bitarray(8, 6);
    bitarray.reset(6);

    EXPECT_EQ(bitarray.toString(), "00000100");
}

TEST(BitArrayTest, Any) {
    BitArray bitarray1(8, 6);
    BitArray bitarray2(8, 0);

    EXPECT_TRUE(bitarray1.any());
    EXPECT_FALSE(bitarray2.any());
}

TEST(BitArrayTest, None) {
    BitArray bitarray1(8, 6);
    BitArray bitarray2(8, 0);

    EXPECT_FALSE(bitarray1.none());
    EXPECT_TRUE(bitarray2.none());
}

TEST(BitArrayTest, Count) {
    BitArray bitarray1(8, 6);
    BitArray bitarray2(8, 0);

    EXPECT_EQ(bitarray1.count(), 2);
    EXPECT_EQ(bitarray2.count(), 0);
}

TEST(BitArrayTest, Size) {
    BitArray bitarray1(14, 6);
    BitArray bitarray2(8, 0);

    EXPECT_EQ(bitarray1.size(), 14);
    EXPECT_EQ(bitarray2.size(), 8);
}

TEST(BitArrayTest, Empty) {
    BitArray bitarray1;
    BitArray bitarray2(8, 0);

    EXPECT_TRUE(bitarray1.empty());
    EXPECT_FALSE(bitarray2.empty());
}

TEST(BitArrayTest, OperatorGet) {
    BitArray bitarray(8, 6);

    EXPECT_EQ(bitarray[0], false);
    EXPECT_EQ(bitarray[6], true);
}

TEST(BitArrayTest, OperatorTilde) {
    BitArray bitarray(8, 6);

    ~bitarray;
    EXPECT_EQ(bitarray.toString(), "11111001");
}

TEST(BitArrayTest, OperatorEqual) {
    BitArray bitarray1(16, 32);
    BitArray bitarray2 = bitarray1;

    EXPECT_EQ(bitarray2.size(), 16);
    EXPECT_EQ(bitarray2.toString(), "0000000000100000");
}

TEST(BitArrayTest, OperatorAndEqual) {
    BitArray bitarray1(8, 6);
    BitArray bitarray2(16, 12);
    bitarray2 &= bitarray1;

    EXPECT_EQ(bitarray2.size(), 16);
    EXPECT_EQ(bitarray2.toString(), "0000000000000100");
}

TEST(BitArrayTest, OperatorOrEqual) {
    BitArray bitarray1(8, 6);
    BitArray bitarray2(16, 12);
    bitarray2 |= bitarray1;

    EXPECT_EQ(bitarray2.size(), 16);
    EXPECT_EQ(bitarray2.toString(), "0000000000001110");
}

TEST(BitArrayTest, OperatorXorEqual) {
    BitArray bitarray1(8, 6);
    BitArray bitarray2(16, 12);
    bitarray2 ^= bitarray1;

    EXPECT_EQ(bitarray2.size(), 16);
    EXPECT_EQ(bitarray2.toString(), "0000000000001010");
}

TEST(BitArrayTest, OperatorRightShift) {
    BitArray bitarray(12, 128);
    bitarray >>= 6;

    EXPECT_EQ(bitarray.toString(), "000000000010");
}

TEST(BitArrayTest, OperatorLeftShift) {
    BitArray bitarray(12, 6);
    bitarray <<= 6;

    EXPECT_EQ(bitarray.toString(), "000110000000");
}
