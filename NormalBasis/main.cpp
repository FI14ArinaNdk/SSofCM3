#include "NormalBasis.h"
#include <chrono> 

using namespace std;
using namespace std::chrono;

MultiplicativeMatrix NormalOperations::Matrix(m);
int main() {
    NormalOperations::GenerateMultiplicationMatrix();

    NormalOperations a("0AD49794C5B4CEB8F9FFE492A9DBF8512AA16E57B55C5F49F2E8B6971F12B7250494F6AF78CE0DE8213247F4C0");
    NormalOperations b("106C3182D26D28BA041EFAD3030E9C1B1B5C194E51D7ACF500D43B348A1FC657C7077DABB95E175FCCBCE87DB8");
    NormalOperations c("550C72D46E37BDCE5F488DAB50B69791BE6014917B59801686CB82813096E927C1BE76305B70F9F95F64A83957");

	cout << a.toHexString() << endl; 
	cout << b.toHexString() << endl;
	cout << c.toHexString() << endl; 

	NormalOperations result1 = a.Sum(b); 
    cout << "a+b =" << result1.toHexString() << endl; 

	NormalOperations result2 = a.Mult(b);
    cout << "a*b =" << result2.toHexString() << endl;

	NormalOperations result3 = a.Square();
    cout << "a^2 =" << result3.toHexString() << endl;

    cout << "trace(a) =" << a.Trace() << endl;

	NormalOperations result4 = a.Invers();
    cout << "a^-1 ="  << result4.toHexString() << endl;

	NormalOperations result5 = a.Pow(c);
    cout << "a^c =" << result5.toHexString() << endl; 

    cout << "\t" << endl;
    cout << "\t" << endl;

    cout << "Test time:" << endl;

    //Test 1
    NormalOperations left_side = (a.Sum(b)).Mult(c);
    NormalOperations right_side = (b.Mult(c)).Sum(c.Mult(a));
    cout << "Test 1: (a + b)* c = b * c + c * a - ";
    if (left_side.toHexString() == right_side.toHexString()) {
        cout << "Passed" << endl;
    }
    else { cout << "Failed" << endl; }

    NormalOperations k("1AFEFF01B7F70BF3E76A38C9E41709E2DEF18CC636B16A9E831FF9284CC7521B1AB570A24F26A8E9D05A066E83");
    NormalOperations l("7C057EC80E388CA19100954CAEFB65C55A8C1990060BA216DE7B7C848F318826FD8CFBE06357F179D76FFD74D4");
    NormalOperations h("119D7FA42D86FFB8D532F5A68444057A7BFE05F0D9819306D3050311765148BEB3620EA892F614BD7E1D6297D7");

    //Test 2
    NormalOperations expected("66FB81C9B9CF8752766AAD854AEC6C27847D955630BAC8885D6485ACC3F6DA3DE7398B422C7159900735FB1A57");
    NormalOperations sum_result = (k.Sum(l)).toHexString();
    if (sum_result == expected.toHexString()) {
        cout << "Test Sum - Passed\n";
    }
    else {
        cout << "Test Sum - Failed\n";
    }
    //Test 3
    NormalOperations expected1("1B67ACE4275C9B5F15EBEB464F5CFB6754881BAA7633398D56518CA0E69460E2DDD8D66E4F2F3A57F46CAAE97C");
    NormalOperations mult_result = (k.Mult(l)).toHexString();
    if (mult_result == expected1.toHexString()) {
        cout << "Test Mult - Passed\n";
    }
    else {
        cout << "Test Mult - Failed\n";
    }
    //Test4
    NormalOperations expected2("4D7F7F80DBFB85F9F3B51C64F20B84F16F78C6631B58B54F418FFC942663A90D8D5AB85127935474E82D033741");
    NormalOperations Sq_result = (k.Square()).toHexString();
    if (Sq_result == expected2.toHexString()) {
        cout << "Test Square - Passed\n";
    }
    else {
        cout << "Test Square - Failed\n";
    }
    
	/*
	const int iterations = 50;
	double totalSumDuration = 0.0;
	double totalMultiplicationDuration = 0.0;
	double totalTraceDuration = 0.0;
	double totalSquareDuration = 0.0;
	double totalInversDuration = 0.0;
	double totalPowerDuration = 0.0;


	for (int i = 0; i < iterations; ++i) {
		NormalOperations random_num1 = NormalOperations::generateRandomHex(359 / 4);
		NormalOperations random_num2 = NormalOperations::generateRandomHex(359 / 4);
		NormalOperations random_num3 = NormalOperations::generateRandomHex(359 / 4);


		auto startAddition = std::chrono::steady_clock::now();
		random_num1.Sum(random_num2).toHexString();
		auto endAddition = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::micro> additionDuration = endAddition - startAddition;
		totalSumDuration += additionDuration.count();

		auto startMultiplication = std::chrono::steady_clock::now();
		random_num1.Mult(random_num2).toHexString();
		auto endMultiplication = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::micro> multiplicationDuration = endMultiplication - startMultiplication;
		totalMultiplicationDuration += multiplicationDuration.count();

		auto startTrace = std::chrono::steady_clock::now();
		random_num1.Trace();
		auto endTrace = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::micro> TraceDuration = endTrace - startTrace;
		totalTraceDuration += TraceDuration.count();

		auto startSquare = std::chrono::steady_clock::now();
		random_num1.Square().toHexString();
		auto endSquare = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::micro> SquareDuration = endSquare - startSquare;
		totalSquareDuration += SquareDuration.count();

		auto startInvers = std::chrono::steady_clock::now();
		random_num1.Invers().toHexString();
		auto endInvers = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::micro> InversDuration = endInvers - startInvers;
		totalInversDuration += InversDuration.count();

		auto startPower = std::chrono::steady_clock::now();
		random_num1.Pow(random_num3).toHexString();
		auto endPower = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::micro> PowerDuration = endPower - startPower;
		totalPowerDuration += PowerDuration.count();
	}

	double averageSumTime = totalSumDuration / iterations;
	double averageMultiplicationTime = totalMultiplicationDuration / iterations;
	double averageTraceTime = totalTraceDuration / iterations;
	double averageSquareTime = totalSquareDuration / iterations;
	double averageInversTime = totalInversDuration / iterations;
	double averagePowerTime = totalPowerDuration / iterations;

	cout << "Average time for polynomial addition: " << averageSumTime << " microsec\n";
	cout << "Average time for polynomial multiplication: " << averageMultiplicationTime << " microsec\n";
	cout << "Average time for polynomial trace: " << averageTraceTime << " microsec\n";
	cout << "Average time for polynomial squareT: " << averageSquareTime << " microsec\n";
	cout << "Average time for polynomial invers: " << averageInversTime << " microsec\n";
	cout << "Average time for polynomial power: " << averagePowerTime << " microsec\n";
	*/

    return 0;
}