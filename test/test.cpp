#include <iostream>

#include "../googletest/googletest/include/gtest/gtest.h"

#include "../bitarray/bitarray.hpp"

TEST(BitArrayTest, DefaultConstructor) {
    BitArray bitarray;

    EXPECT_EQ(bitarray.size(), 0);
    EXPECT_TRUE(bitarray.empty());

    const BitArray cbitarray;
    EXPECT_EQ(bitarray.size(), 0);
    EXPECT_TRUE(bitarray.empty());
}

TEST(BitArrayTest, OverloadedConstructor) {
    BitArray bitarray(16,  32);
    
    EXPECT_EQ(bitarray.size(), 16);
    EXPECT_EQ(bitarray.toString(), "0000010000000000");

    const BitArray cbitarray(16,  32);

    EXPECT_EQ(cbitarray.size(), 16);
    EXPECT_EQ(cbitarray.toString(), "0000010000000000");

    try {
        BitArray tbitarray(-1,  -1);
    }

    catch (const char* string) {
        EXPECT_STREQ(string, "Out of range");
    }
}

TEST(BitArrayTest, CopyConstructor) {
    BitArray bitarray1(16, 32);
    BitArray bitarray2(bitarray1);

    EXPECT_EQ(bitarray2.size(), 16);
    EXPECT_EQ(bitarray2.toString(), "0000010000000000");

    const BitArray cbitarray1(16, 32);
    const BitArray cbitarray2(bitarray1);

    EXPECT_EQ(cbitarray2.size(), 16);
    EXPECT_EQ(cbitarray2.toString(), "0000010000000000");
}

TEST(BitArrayTest, Swap) {
    BitArray bitarray1(16, 32);
    BitArray bitarray2(8, 6);
    bitarray1.swap(bitarray2);

    EXPECT_EQ(bitarray1.size(), 8);
    EXPECT_EQ(bitarray1.toString(), "01100000");

    EXPECT_EQ(bitarray2.size(), 16);
    EXPECT_EQ(bitarray2.toString(), "0000010000000000");
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
    EXPECT_EQ(bitarray.toString(), "0110000000000000");

    bitarray.resize(4, false);
    EXPECT_EQ(bitarray.toString(), "0110");

    BitArray tbitarray(8, 6);

    try {
        tbitarray.resize(-1);
    }

    catch (const char* string) {
        EXPECT_STREQ(string, "Out of range");
    }
}

TEST(BitArrayTest, PushBack) {
    BitArray bitarray(8, 6);
    bitarray.pushBack(true);

    EXPECT_EQ(bitarray.size(), 9);
    EXPECT_EQ(bitarray.toString(), "011000001");

    bitarray.pushBack(false);

    EXPECT_EQ(bitarray.size(), 10);
    EXPECT_EQ(bitarray.toString(), "0110000010");
}

TEST(BitArrayTest, DefaultSet) {
    BitArray bitarray(8, 6);
    bitarray.set();

    EXPECT_EQ(bitarray.toString(), "11111111");
}

TEST(BitArrayTest, OverloadedSet) {
    BitArray bitarray(8, 6);
    bitarray.set(1, false);
    bitarray.set(6, true);

    EXPECT_EQ(bitarray.toString(), "00100010");

    BitArray tbitarray(8, 6);

    try {
        tbitarray.set(-1);
    }

    catch (const char* string) {
        EXPECT_STREQ(string, "Out of range");
    }
}

TEST(BitArrayTest, DefaultReset) {
    BitArray bitarray(8, 6);
    bitarray.reset();

    EXPECT_EQ(bitarray.toString(), "00000000");
}

TEST(BitArrayTest, OverloadedReset) {
    BitArray bitarray(8, 6);
    bitarray.reset(1);

    EXPECT_EQ(bitarray.toString(), "00100000");
}

TEST(BitArrayTest, Any) {
    BitArray bitarray1(8, 6);
    BitArray bitarray2(8, 0);

    EXPECT_TRUE(bitarray1.any());
    EXPECT_FALSE(bitarray2.any());

    const BitArray cbitarray1(8, 6);
    const BitArray cbitarray2(8, 0);

    EXPECT_TRUE(cbitarray1.any());
    EXPECT_FALSE(cbitarray2.any());
}

TEST(BitArrayTest, None) {
    BitArray bitarray1(8, 6);
    BitArray bitarray2(8, 0);

    EXPECT_FALSE(bitarray1.none());
    EXPECT_TRUE(bitarray2.none());

    const BitArray cbitarray1(8, 6);
    const BitArray cbitarray2(8, 0);

    EXPECT_FALSE(cbitarray1.none());
    EXPECT_TRUE(cbitarray2.none());
}

TEST(BitArrayTest, Count) {
    BitArray bitarray1(8, 6);
    BitArray bitarray2(8, 0);

    EXPECT_EQ(bitarray1.count(), 2);
    EXPECT_EQ(bitarray2.count(), 0);

    const BitArray cbitarray1(8, 6);
    const BitArray cbitarray2(8, 0);

    EXPECT_EQ(cbitarray1.count(), 2);
    EXPECT_EQ(cbitarray2.count(), 0);
}

TEST(BitArrayTest, Size) {
    BitArray bitarray1(14, 6);
    BitArray bitarray2(8, 0);

    EXPECT_EQ(bitarray1.size(), 14);
    EXPECT_EQ(bitarray2.size(), 8);

    const BitArray cbitarray1(14, 6);
    const BitArray cbitarray2(8, 0);

    EXPECT_EQ(cbitarray1.size(), 14);
    EXPECT_EQ(cbitarray2.size(), 8);
}

TEST(BitArrayTest, Empty) {
    BitArray bitarray1;
    BitArray bitarray2(8, 0);

    EXPECT_TRUE(bitarray1.empty());
    EXPECT_FALSE(bitarray2.empty());

    const BitArray cbitarray1;
    const BitArray cbitarray2(8, 0);

    EXPECT_TRUE(cbitarray1.empty());
    EXPECT_FALSE(cbitarray2.empty());
}

TEST(BitArrayTest, OperatorGet) {
    BitArray bitarray(8, 6);

    EXPECT_EQ(bitarray[1], true);
    EXPECT_EQ(bitarray[6], false);

    const BitArray cbitarray(8, 6);

    EXPECT_EQ(cbitarray[1], true);
    EXPECT_EQ(cbitarray[6], false);

    BitArray tbitarray(8, 6);

    try {
        tbitarray[-1];
    }

    catch (const char* string) {
        EXPECT_STREQ(string, "Out of range");
    }
}

TEST(BitArrayTest, OperatorTilde) {
    BitArray bitarray(8, 6);

    ~bitarray;
    EXPECT_EQ(bitarray.toString(), "10011111");
}

TEST(BitArrayTest, OperatorAssign) {
    BitArray bitarray1(16, 32);
    BitArray bitarray2 = bitarray1;

    EXPECT_EQ(bitarray2.size(), 16);
    EXPECT_EQ(bitarray2.toString(), "0000010000000000");
}

TEST(BitArrayTest, OperatorAndAssign) {
    BitArray bitarray1(8, 6);
    BitArray bitarray2(16, 12);
    bitarray2 &= bitarray1;

    EXPECT_EQ(bitarray2.size(), 16);
    EXPECT_EQ(bitarray2.toString(), "0011000000000000");
}

TEST(BitArrayTest, OperatorOrAssign) {
    BitArray bitarray1(8, 6);
    BitArray bitarray2(16, 12);
    bitarray2 |= bitarray1;

    EXPECT_EQ(bitarray2.size(), 16);
    EXPECT_EQ(bitarray2.toString(), "0011000001100000");
}

TEST(BitArrayTest, OperatorXorAssign) {
    BitArray bitarray1(8, 6);
    BitArray bitarray2(16, 12);
    bitarray2 ^= bitarray1;

    EXPECT_EQ(bitarray2.size(), 16);
    EXPECT_EQ(bitarray2.toString(), "0011000001100000");
}

TEST(BitArrayTest, OperatorRightShiftAssign) {
    BitArray bitarray(16, 12);
    bitarray >>= 6;

    EXPECT_EQ(bitarray.toString(), "0000000011000000");

    BitArray tbitarray(16, 12);

    try {
        tbitarray >> -1;
    }

    catch (const char* string) {
        EXPECT_STREQ(string, "Out of range");
    }
}

TEST(BitArrayTest, OperatorLeftShiftAssign) {
    BitArray bitarray(16, 6);
    bitarray <<= 1;

    EXPECT_EQ(bitarray.toString(), "1100000000000000");

    BitArray tbitarray(16, 12);

    try {
        tbitarray << -1;
    }

    catch (const char* string) {
        EXPECT_STREQ(string, "Out of range");
    }
}

TEST(BitArrayTest, OperatorRightShift) {
    BitArray bitarray(16, 12);

    EXPECT_EQ((bitarray >> 6).toString(), "0000000011000000");

    const BitArray cbitarray(16, 12);

    EXPECT_EQ((cbitarray >> 6).toString(), "0000000011000000");
}

TEST(BitArrayTest, OperatorLeftShift) {
    BitArray bitarray(16, 6);

    EXPECT_EQ((bitarray << 1).toString(), "1100000000000000");

    const BitArray cbitarray(16, 6);

    EXPECT_EQ((cbitarray << 1).toString(), "1100000000000000");
}

TEST(BitArrayTest, OperatorEqual) {
    BitArray bitarray1(8, 6);
    BitArray bitarray2(16, 12);

    EXPECT_FALSE(bitarray1 == bitarray2);
}

TEST(BitArrayTest, OperatorNotEqual) {
    BitArray bitarray1(8, 6);
    BitArray bitarray2(16, 12);

    EXPECT_TRUE(bitarray1 != bitarray2);
}

TEST(BitArrayTest, OperatorAnd) {
    BitArray bitarray1(8, 6);
    BitArray bitarray2(16, 12);

    EXPECT_EQ((bitarray2 & bitarray1).size(), 16);
    EXPECT_EQ((bitarray2 & bitarray1).toString(), "0011000000000000");

    const BitArray cbitarray1(8, 6);
    const BitArray cbitarray2(16, 12);

    EXPECT_EQ((cbitarray2 & cbitarray1).size(), 16);
    EXPECT_EQ((cbitarray2 & cbitarray1).toString(), "0011000000000000");
}

TEST(BitArrayTest, OperatorOr) {
    BitArray bitarray1(8, 6);
    BitArray bitarray2(16, 12);

    EXPECT_EQ((bitarray2 | bitarray1).size(), 16);
    EXPECT_EQ((bitarray2 | bitarray1).toString(), "0011000001100000");

    const BitArray cbitarray1(8, 6);
    const BitArray cbitarray2(16, 12);

    EXPECT_EQ((cbitarray2 | cbitarray1).size(), 16);
    EXPECT_EQ((cbitarray2 | cbitarray1).toString(), "0011000001100000");
}

TEST(BitArrayTest, OperatorXor) {
    BitArray bitarray1(8, 6);
    BitArray bitarray2(16, 12);

    EXPECT_EQ((bitarray2 ^ bitarray1).size(), 16);
    EXPECT_EQ((bitarray2 ^ bitarray1).toString(), "0011000001100000");

    const BitArray cbitarray1(8, 6);
    const BitArray cbitarray2(16, 12);

    EXPECT_EQ((cbitarray2 ^ cbitarray1).size(), 16);
    EXPECT_EQ((cbitarray2 ^ cbitarray1).toString(), "0011000001100000");
}