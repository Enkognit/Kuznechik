#include "kuznyechik.h"

using namespace star::kuznyechik;

int main() {
    freopen("out", "w", stdout);
    uint8_t a[N];
    std::cerr<< 0xf00f;
    std::cout << "{\n";
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < (1 << 8); j++) {
            for (int i = 0; i < N; i++) {
                a[i] = 0;
            }
            a[i] = j;
            std::string s = VecToHex(L(a));
            auto prnt = [&](int i) {
                std::cout << "0x";
                for (int u = s.size() / 2 * i; u < s.size() / 2 * (i + 1); u++) {
                    std::cout << s[u];
                }
                std::cout << ", ";
            };
            prnt(1);
            prnt(0);
            if ((j + 1) % 32 == 0) {
                std::cout << "\n";
            }
        }
        std::cout << "\n";
    }
    std::cout << "}\n";
    return 0;
}
