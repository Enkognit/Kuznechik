#include "kuznyechik.h"

using namespace star::kuznyechik;

int main() {
    auto obj = Kuznyechik::CreateWithHexKey("8899aabbccddeeff0011223344556677fedcba98765432100123456789abcdef");
    uint8_t a[N];
    VecFromHex(a, "db31485315694343228d6aef8cc78c44");
    auto time = clock();
    for (int i = 0; i < 10000000; i++) {
        obj.EncodeFast(a);
    }
    std::cout << "Total time: " << (clock() - time) * 1.0 / CLOCKS_PER_SEC << "\n";
    return 0;
}
