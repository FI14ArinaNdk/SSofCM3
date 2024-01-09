#include <iostream>
#include <bitset>
#include <vector>
#include <string>

using namespace std; 

const int m = 359;
const int p = 2 * m + 1;

using MultiplicativeMatrix = vector<bitset<m>>;

class NormalOperations {
private:
    bitset<m> value;
    static MultiplicativeMatrix Matrix;

public:
    NormalOperations();
    NormalOperations(const bitset<m>& value);
    NormalOperations(const string& string);

    static void GenerateMultiplicationMatrix();
    static int CountLeadingZeros(uint32_t num);
    static int ModuloPowerOfTwo(int exp, int mod);

    NormalOperations& operator=(const NormalOperations& other);
    NormalOperations operator+(const NormalOperations& other) const;
    NormalOperations operator*(const NormalOperations& other) const;

    bool operator==(const NormalOperations& other) const;

    NormalOperations Sum(const NormalOperations& other) const;
    NormalOperations Mult(const NormalOperations& other) const;
    NormalOperations Square() const;
    int Trace() const;
    NormalOperations Invers() const;
    NormalOperations Pow(const NormalOperations& exp) const;

    static NormalOperations fromString(const string& String); 
    string toHexString() const;
    static NormalOperations fromHex(const string& HexString); 

    static  NormalOperations generateRandomHex(const int size);
};