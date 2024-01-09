#include "NormalBasis.h"
#include <random>

NormalOperations::NormalOperations() : value(0) {}

NormalOperations::NormalOperations(const bitset<m>& value) : value(value) {}

NormalOperations::NormalOperations(const string& string) {
    if (string.size() == m) {
        *this = fromString(string);
    }
    else {
        *this = fromHex(string);
    }
}

int NormalOperations::CountLeadingZeros(uint32_t num) {
    int count = 0;
    while ((num & 0x80000000) == 0) { 
        ++count;
        num <<= 1;
    }
    if (num == 0) {
        return 32;
    }
    return count;
}

int NormalOperations::ModuloPowerOfTwo(int exp, int mod) {
    int result = 1;
    int base = 2 % mod; 

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    if (mod <= 0) {
        return -1;
    }

    if (exp == 0) {
        return 1;
    }

    return result;
}

void NormalOperations::GenerateMultiplicationMatrix() {
    for (int i = 0; i < m; ++i) { 
        for (int j = 0; j < m; ++j) { 
            int temp1 = ModuloPowerOfTwo(i, p);
            int temp2 = ModuloPowerOfTwo(j, p);

            if ((temp1 + temp2) % p == 1 || 
                (temp1 - temp2 + p) % p == 1 || 
                ((p - temp1) + temp2) % p == 1 ||
                ((p - temp1) - temp2 + p) % p == 1) { 
                Matrix[m - i - 1][m - j - 1] = 1;
            }
        }
    }
}

NormalOperations& NormalOperations::operator=(const NormalOperations& other) {
    if (this != &other) {
        this->value = other.value;
    }
    return *this;
}

NormalOperations NormalOperations::operator+(const NormalOperations& other) const {
    return this->Sum(other);
}

NormalOperations NormalOperations::operator*(const NormalOperations& other) const {
    return this->Mult(other);
}

bool NormalOperations::operator==(const NormalOperations& other) const {
    return value == other.value;
}

NormalOperations NormalOperations::Sum(const NormalOperations& other) const {
    return NormalOperations(value ^ other.value);
}

NormalOperations NormalOperations::Mult(const NormalOperations& other) const {
    bitset<m> z(0);
    for (int i = 0; i < m; ++i) {
        bitset<m> u = (value << i) | (value >> (m - i));
        bitset<m> v = (other.value << i) | (other.value >> (m - i));
        bitset<m> u_times_matrix(0);
        for (int j = 0; j < m; ++j) {
            if (u[j]) {
                u_times_matrix ^= Matrix[j];
            }
        }
        z <<= 1;
        if ((u_times_matrix & v).count() % 2 != 0) {
            z.set(0);
        }
    }
    return NormalOperations(z);
}

NormalOperations NormalOperations::Square() const {
    return NormalOperations((value >> 1) | (value << (m - 1)));
}

NormalOperations NormalOperations::Pow(const NormalOperations& exp) const {
    NormalOperations result("1" + string(358, '1'));
    NormalOperations base = *this;

    for (int i = 0; i < m; ++i) {
        if (exp.value.test(i)) {
            result = result.Mult(base);
        }
        base = base.Square();
    }
    return result;
}

NormalOperations NormalOperations::Invers() const {
    NormalOperations a = *this; 
    NormalOperations b = a; 
    NormalOperations temp; 
    int t = 31 - CountLeadingZeros(m - 1);
    int k = 1;

    for (int i = t - 1; i >= 0; --i) {
        temp = b; 
        for (int j = 0; j < k; j++) {
            b = b.Square();
        }
        b = b * temp; 
        k = 2 * k;

        if ((m - 1) & (1 << i)) {
            b = b.Square() * a;
            k = k + 1;
        }
    }

    b = b.Square();
    return b;
}

int NormalOperations::Trace() const {
    return value.count() % 2;
}

NormalOperations NormalOperations::fromString(const string& String) {
    string paddedString = String;
    if (String.size() < m) {
        paddedString = string(m - String.size(), '0') + String;
    }
    else if (String.size() > m) {
        paddedString = String.substr(String.size() - m);
    }
    return NormalOperations(bitset<m>(paddedString));
}

string NormalOperations::toHexString() const {
    string HexString;
    for (int i = 0; i < m; i += 4) {
        int HexValue = 0;
        for (int j = 0; j < 4 && (i + j) < m; ++j) {
            if (value.test(i + j)) {
                HexValue |= 1 << j;
            }
        }

        char HexChar;
        if (HexValue < 10) {
            HexChar = '0' + HexValue;
        }
        else {
            HexChar = 'A' + HexValue - 10;
        }
        HexString = HexChar + HexString;
    }
    size_t startPos = HexString.find_first_not_of('0');
    if (startPos != string::npos) {
        HexString = HexString.substr(startPos);
    }
    else {
        HexString = "0";
    }

    return HexString;
}

NormalOperations NormalOperations::fromHex(const string& HexString) {
    string BinString;
    for (char HexChar : HexString) {
        int HexValue;
        if (HexChar >= '0' && HexChar <= '9') { 
            HexValue = HexChar - '0'; 
        }
        else if (HexChar >= 'A' && HexChar <= 'F') {
            HexValue = HexChar - 'A' + 10; 
        }
        else if (HexChar >= 'a' && HexChar <= 'f') {
            HexValue = HexChar - 'a' + 10; 
        }
        else { 
            HexValue = -1; 
        }

        for (int i = 3; i >= 0; --i) {
            char bitChar;
            if ((HexValue >> i) & 1) {
                bitChar = '1';
            }
            else {
                bitChar = '0';
            }
            BinString.push_back(bitChar);
        } 
    }

    size_t firstNonZero = BinString.find_first_not_of('0'); 
    if (firstNonZero != string::npos) {
        BinString = BinString.substr(firstNonZero); 
    }
    else {
        BinString = "0"; 
    }

    size_t expectedSize;
    if (BinString.size() < m) {
        expectedSize = m;
    }
    else {
        expectedSize = BinString.size();
    }

    if (BinString.size() < m) {
        BinString = string(expectedSize - BinString.size(), '0') + BinString; 
    }
    else if (BinString.size() > m) {
        BinString = BinString.substr(BinString.size() - m); 
    }

    return NormalOperations(bitset<m>(BinString));
}

NormalOperations NormalOperations::generateRandomHex(const int size){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 15);

    string HexString;
    HexString.reserve(size);

    for (int i = 0; i < size; ++i) {
        int randomValue = distrib(gen);
        char HexChar;
        if (randomValue < 10) {
            HexChar = '0' + randomValue; 
        }
        else {
            HexChar = 'A' + randomValue - 10; 
        }
        HexString += HexChar;
    }

    return HexString;
}