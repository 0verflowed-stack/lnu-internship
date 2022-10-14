#include<iostream>
#include<algorithm>
using namespace std;

class NaturalNumber {
	private:
		int number;
		int numSystem;
	public:
		NaturalNumber() : number(0), numSystem(10) {}
		NaturalNumber(int number, int numSystem): number(number), numSystem(numSystem) {}
		NaturalNumber(const NaturalNumber& naturalNumber) : number(naturalNumber.number), numSystem(naturalNumber.numSystem) {}

		NaturalNumber& operator=(const NaturalNumber& naturalNumber) {
			number = naturalNumber.number;
			numSystem = naturalNumber.numSystem;
			return *this;
		}

		NaturalNumber operator+(const NaturalNumber& naturalNumber) {
			if (number >= 0 && naturalNumber.number >= 0) {
				NaturalNumber res = NaturalNumber();
				res.number = 0;
				res.numSystem = numSystem;
				int nDigits = max(floor(log10(abs(number))) + 1, floor(log10(abs(naturalNumber.number))) + 1);
				int tempFirstNum = number;
				int tempSecondNum = naturalNumber.number;
				int remainder = 0;
				for (int i = 0; i < nDigits; ++i) {
					int firstDigit = tempFirstNum % 10;
					int secondDigit = tempSecondNum % 10;
					tempFirstNum /= 10;
					tempSecondNum /= 10;
					int sum = firstDigit + secondDigit + remainder;
					if (sum >= numSystem) {
						remainder = sum / numSystem;
						sum = sum % numSystem;
					} else {
						remainder = 0;
					}
					res.number += sum * pow(10, i);
				}
				res.number += remainder * pow(10, nDigits);
				return res;
			} else if (number < 0 && naturalNumber.number >= 0) {
				NaturalNumber temp = NaturalNumber(*this);
				temp.number *= -1;
				return NaturalNumber(naturalNumber) - temp;
			} else if (number >= 0 && naturalNumber.number < 0) {
				NaturalNumber temp = NaturalNumber(naturalNumber);
				temp.number *= -1;
				return *this - temp;
			}
			else if (number < 0 && naturalNumber.number < 0) {
				NaturalNumber tempFirst = NaturalNumber(*this);
				tempFirst.number *= -1;
				NaturalNumber tempSecond = NaturalNumber(*this);
				tempSecond.number *= -1;
				NaturalNumber res = tempFirst + tempSecond;
				res.number *= -1;
				return res;
			}
		}

		NaturalNumber operator-(const NaturalNumber& naturalNumber) {
			NaturalNumber res = NaturalNumber();
			res.number = 0;
			res.numSystem = numSystem;
			int nDigits = max(floor(log10(abs(number))) + 1, floor(log10(abs(naturalNumber.number))) + 1);
			if (number < naturalNumber.number) {
				res.number = -(NaturalNumber(naturalNumber) - *this).number;
				return res;
			}
			bool minusSign = false;
			int tempFirstNum = number;
			int tempSecondNum = naturalNumber.number;
			int remainder = 0;
			for (int i = 0; i < nDigits; ++i) {
				int firstDigit = tempFirstNum % 10;
				int secondDigit = tempSecondNum % 10;
				tempFirstNum /= 10;
				tempSecondNum /= 10;
				int nextFirstDigit = tempFirstNum % 10;
				int nextSecondDigit = tempSecondNum % 10;
				int difference = firstDigit - secondDigit - remainder;
				
				if (difference < 0) {
					remainder = 1;
					difference = numSystem + difference;
				}
				res.number += difference * pow(10, i);
			}
			res.number *= minusSign ? -1 : 1;
			return res;
		}

		NaturalNumber operator*(const NaturalNumber& naturalNumber) {
			NaturalNumber res = NaturalNumber();
			res.number = 0;
			res.numSystem = numSystem;
			int nDigitsFirst = floor(log10(abs(number))) + 1;
			int nDigitsSecond = floor(log10(abs(naturalNumber.number))) + 1;
			int tempSecondNum = abs(naturalNumber.number);
			for (int i = 0; i < nDigitsSecond; ++i) {
				int remainder = 0;
				int tempFirstNum = abs(number);
				int secondDigit = tempSecondNum % 10;
				tempSecondNum /= 10;
				NaturalNumber tempNum = NaturalNumber(0, numSystem);
				for (int j = 0; j < nDigitsFirst; ++j) {
					int firstDigit = tempFirstNum % 10;
					tempFirstNum /= 10;
					int product = firstDigit * secondDigit + remainder;
					if (product >= numSystem) {
						remainder = product / numSystem;
						product %= numSystem;
					} else {
						remainder = 0;
					}
					tempNum.number += product * pow(10, i + j);
				}
				tempNum.number += remainder * pow(10, i + nDigitsFirst);
				res = res + tempNum;
			}
			res.number *= (number < 0 ^ naturalNumber.number < 0) ? -1 : 1;
			return res;
		}

		NaturalNumber operator/(const NaturalNumber& naturalNumber) {
			NaturalNumber res = NaturalNumber();
			res.number = 0;
			res.numSystem = numSystem;
			int nDigitsFirst = floor(log10(abs(number))) + 1;
			int nDigitsSecond = floor(log10(abs(naturalNumber.number))) + 1;
			int tempFirstNum = abs(number);
			int tempSecondNum = abs(naturalNumber.number);
			NaturalNumber tempFirst(0, numSystem);
			NaturalNumber tempSecond(0, numSystem);
			for (int i = 0; i < nDigitsSecond; ++i) {
				if (nDigitsFirst >= nDigitsSecond) {
					if (tempFirstNum / pow(10, nDigitsFirst - nDigitsSecond) < tempSecondNum) {
						int j = 1;
						while (true) {
							tempFirst.number = tempSecondNum;
							tempSecond.number = j;
							NaturalNumber prod = tempFirst * tempSecond;
							if (*this <= prod) {
								res.number += res.number * 10 + (j - 1);
								NaturalNumber rem = *this - prod;
								return NaturalNumber(j - 1, numSystem);
							}
							j++;
						}
					}
				}
				return NaturalNumber(0, numSystem);
			}
			res.number *= (number < 0 ^ naturalNumber.number < 0) ? -1 : 1;
			return res;
		}
		bool operator==(const NaturalNumber& num) {
			return number == num.number && numSystem == num.numSystem;
		}
		bool operator!=(const NaturalNumber& num) {// maybe add numSystem conversion
			return !(*this == num);
		}
		bool operator<(const NaturalNumber& num) {
			return number < num.number;
		}
		bool operator<=(const NaturalNumber& num) {
			return number <= num.number;
		}
		bool operator>(const NaturalNumber& num) {
			return number > num.number;
		}
		bool operator>=(const NaturalNumber& num) {
			return number >= num.number;
		}

		/*NaturalNumber to(int system) {

		}*/

		int getNumber() {
			int res = number;
			
			return res;
		}

		void setNumber(int num, int p) {
			number = num;
			numSystem = p;
		}

		int to10() {
			int res = 0;
			int digits = floor(log10(abs(number))) + 1;
			int tempNum = number;
			for (int i = 0; i < digits; ++i) {
				res += (tempNum % 10) * pow(numSystem, i);
				tempNum /= 10;
			}
			return res;
		}

		NaturalNumber convert10ToP(int p) {
			int res = 0;
			int n = floor(log10(abs(number))) + 1;
			int i = 0;
			while (true) {
				if (number < pow(p, i)) {
					--i;
					break;
				}
				i++;
			}
			int rem = number;
			for (int j = i; j >= 0; --j) {
				res += rem / (int)pow(7, j) * (int)pow(10, j);
				rem = rem % (int)pow(7, j);
			}
			number = res;
			numSystem = 10;
			return *this;
		}
};

int main() {
	//NaturalNumber firstNaturalNumber(3321, 7);
	//NaturalNumber secondNaturalNumber(456, 7);
	//cout << (firstNaturalNumber / secondNaturalNumber).getNumber() << endl;
	//cout << NaturalNumber(4509, 10).convert10ToP(7).getNumber() << endl;

	int p, n;
	cin >> p >> n;
	NaturalNumber* nums = new NaturalNumber[n];
	int a = nums->getNumber();
	for (int i = 0; i < n; ++i) {
		int temp;
		cin >> temp;
		nums[i].setNumber(temp, p);
	}

	NaturalNumber sumOfAllElementsInP = NaturalNumber(0, p);
	for (int i = 0; i < n; ++i) {
		sumOfAllElementsInP = sumOfAllElementsInP + nums[i];
	}
	NaturalNumber avarageValueInP = sumOfAllElementsInP / NaturalNumber(n, 10).convert10ToP(p);
	int avarageValueIn10 = avarageValueInP.to10();
	NaturalNumber minValue = NaturalNumber(nums[0]);
	NaturalNumber maxValue = NaturalNumber(nums[0]);
	for (int i = 0; i < n; ++i) {
		if (minValue > nums[i]) {
			minValue.setNumber(nums[i].getNumber(), p);
		}
		if (maxValue < nums[i]) {
			maxValue.setNumber(nums[i].getNumber(), p);
		}
	}
	NaturalNumber rangeInP = maxValue - minValue;
	int rangeIn10 = rangeInP.to10();
	NaturalNumber productOfFirst5ElementsInP = NaturalNumber(1, p);
	for (int i = 0; i < n; ++i) {
		productOfFirst5ElementsInP = productOfFirst5ElementsInP * nums[i];
	}
	int productOfFirst5ElementsIn10 = productOfFirst5ElementsInP.to10();
	cout << avarageValueInP.getNumber() << " ";
	cout << avarageValueIn10 << " ";
	cout << rangeInP.getNumber() << " ";
	cout << rangeIn10 << " ";
	cout << productOfFirst5ElementsInP.getNumber() << " ";
	cout << productOfFirst5ElementsIn10;

	return 0;
}

