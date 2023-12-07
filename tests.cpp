//
// Created by enkognit on 2.12.23.
//
#include <gtest/gtest.h>
#include "kuznyechik.h"

using namespace star::kuznyechik;

bool AreVecEq(uint8_t* a, uint8_t* b, int len = N) {
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

void test_S(uint8_t* arr, std::string const& str1, std::string const& str2) {
    VecFromHex(arr, str1, N);
    ASSERT_EQ(VecToHex(S(arr)), str2);
}

TEST(Components, STest) {
    uint8_t a[N];
    test_S(a, "ffeeddccbbaa99881122334455667700", "b66cd8887d38e8d77765aeea0c9a7efc");
    test_S(a, "b66cd8887d38e8d77765aeea0c9a7efc", "559d8dd7bd06cbfe7e7b262523280d39");
    test_S(a, "559d8dd7bd06cbfe7e7b262523280d39", "0c3322fed531e4630d80ef5c5a81c50b");
    test_S(a, "0c3322fed531e4630d80ef5c5a81c50b", "23ae65633f842d29c5df529c13f5acda");
}

void test_SInv(uint8_t* arr, std::string const& str2, std::string const& str1) {
    VecFromHex(arr, str1, N);
    ASSERT_EQ(VecToHex(S_Inv(arr)), str2);
}

TEST(Components, SInvTest) {
    uint8_t a[N];
    test_SInv(a, "ffeeddccbbaa99881122334455667700", "b66cd8887d38e8d77765aeea0c9a7efc");
    test_SInv(a, "b66cd8887d38e8d77765aeea0c9a7efc", "559d8dd7bd06cbfe7e7b262523280d39");
    test_SInv(a, "559d8dd7bd06cbfe7e7b262523280d39", "0c3322fed531e4630d80ef5c5a81c50b");
    test_SInv(a, "0c3322fed531e4630d80ef5c5a81c50b", "23ae65633f842d29c5df529c13f5acda");
}

void test_L(uint8_t* arr, std::string const& str1, std::string const& str2) {
    VecFromHex(arr, str1, N);
    ASSERT_EQ(VecToHex(L(arr)), str2);
}

TEST(Components, LTest) {
    uint8_t a[N];
    test_L(a, "64a59400000000000000000000000000", "d456584dd0e3e84cc3166e4b7fa2890d");
    test_L(a, "d456584dd0e3e84cc3166e4b7fa2890d", "79d26221b87b584cd42fbc4ffea5de9a");
    test_L(a, "79d26221b87b584cd42fbc4ffea5de9a", "0e93691a0cfc60408b7b68f66b513c13");
    test_L(a, "0e93691a0cfc60408b7b68f66b513c13", "e6a8094fee0aa204fd97bcb0b44b8580");
}

void test_FastL(uint8_t* arr, std::string const& str1, std::string const& str2) {
    VecFromHex(arr, str1, N);
    ASSERT_EQ(VecToHex(FastL(arr)), str2);
}

TEST(Components, FastLTest) {
    uint8_t a[N];
    test_FastL(a, "64a59400000000000000000000000000", "d456584dd0e3e84cc3166e4b7fa2890d");
    test_FastL(a, "d456584dd0e3e84cc3166e4b7fa2890d", "79d26221b87b584cd42fbc4ffea5de9a");
    test_FastL(a, "79d26221b87b584cd42fbc4ffea5de9a", "0e93691a0cfc60408b7b68f66b513c13");
    test_FastL(a, "0e93691a0cfc60408b7b68f66b513c13", "e6a8094fee0aa204fd97bcb0b44b8580");
}

void test_LInv(uint8_t* arr, std::string const& str2, std::string const& str1) {
    VecFromHex(arr, str1);
    ASSERT_EQ(VecToHex(L_Inv(arr)), str2);
}

TEST(Components, LInvTest) {
    uint8_t a[N];
    test_L(a, "64a59400000000000000000000000000", "d456584dd0e3e84cc3166e4b7fa2890d");
    test_L(a, "d456584dd0e3e84cc3166e4b7fa2890d", "79d26221b87b584cd42fbc4ffea5de9a");
    test_L(a, "79d26221b87b584cd42fbc4ffea5de9a", "0e93691a0cfc60408b7b68f66b513c13");
    test_L(a, "0e93691a0cfc60408b7b68f66b513c13", "e6a8094fee0aa204fd97bcb0b44b8580");
}

void test_FastLSX(uint8_t* arr1, uint8_t* arr2, std::string const& str1, std::string const& str2) {
    VecFromHex(arr1, str1);
    VecFromHex(arr2, str2);
    auto s1 = VecToHex(FastLSX(arr1, arr2));
    VecFromHex(arr1, str1);
    auto s2 = VecToHex(L(S(X(arr2, arr1))));
    ASSERT_EQ(s1, s2);
}

TEST(Components, FastLSX) {
    uint8_t a[N];
    uint8_t b[N];
    test_FastLSX(a, b, "d456584dd0e3e84cc3166e4b7fa2890d", "fedcba98765432100123456789abcdef");
}

TEST(Kuznyechik, GenKeysTest) {
    auto obj = Kuznyechik::CreateWithHexKey("8899aabbccddeeff0011223344556677fedcba98765432100123456789abcdef");
    ASSERT_EQ(VecToHex(obj.getGenKey(0)), "8899aabbccddeeff0011223344556677");
    ASSERT_EQ(VecToHex(obj.getGenKey(1)), "fedcba98765432100123456789abcdef");
    ASSERT_EQ(VecToHex(obj.getGenKey(2)), "db31485315694343228d6aef8cc78c44");
    ASSERT_EQ(VecToHex(obj.getGenKey(3)), "3d4553d8e9cfec6815ebadc40a9ffd04");
    ASSERT_EQ(VecToHex(obj.getGenKey(4)), "57646468c44a5e28d3e59246f429f1ac");
    ASSERT_EQ(VecToHex(obj.getGenKey(5)), "bd079435165c6432b532e82834da581b");
    ASSERT_EQ(VecToHex(obj.getGenKey(6)), "51e640757e8745de705727265a0098b1");
    ASSERT_EQ(VecToHex(obj.getGenKey(7)), "5a7925017b9fdd3ed72a91a22286f984");
    ASSERT_EQ(VecToHex(obj.getGenKey(8)), "bb44e25378c73123a5f32f73cdb6e517");
    ASSERT_EQ(VecToHex(obj.getGenKey(9)), "72e9dd7416bcf45b755dbaa88e4a4043");
}

TEST(Kuznyechik, Encode) {
    auto obj = Kuznyechik::CreateWithHexKey("8899aabbccddeeff0011223344556677fedcba98765432100123456789abcdef");
    uint8_t a[N];
    VecFromHex(a, "1122334455667700ffeeddccbbaa9988");
    ASSERT_EQ(VecToHex(obj.Encode(a)), "7f679d90bebc24305a468d42b9d4edcd");
}

TEST(Kuznyechik, EncodeFast) {
    auto obj = Kuznyechik::CreateWithHexKey("8899aabbccddeeff0011223344556677fedcba98765432100123456789abcdef");
    uint8_t a[N];
    VecFromHex(a, "1122334455667700ffeeddccbbaa9988");
    ASSERT_EQ(VecToHex(obj.EncodeFast(a)), "7f679d90bebc24305a468d42b9d4edcd");
}

TEST(Kuznyechik, Decode) {
    auto obj = Kuznyechik::CreateWithHexKey("8899aabbccddeeff0011223344556677fedcba98765432100123456789abcdef");
    uint8_t a[N];
    VecFromHex(a, "7f679d90bebc24305a468d42b9d4edcd");
    ASSERT_EQ(VecToHex(obj.Decode(a)), "1122334455667700ffeeddccbbaa9988");
}