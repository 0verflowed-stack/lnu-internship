#include<iostream>
#include<algorithm>
using namespace std;

int main() {
	const string input = "dad   my hi  add  a nodd   my hi  dd   no   ";
	char vowels[] = { 'a', 'e', 'i', 'o', 'u' };
	char consonants[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 't', 'v', 'w' };
	bool isVowel = false;
	bool isValid = true;
	int wordStartIndex = 0;
	int wordEndIndex = 0;
	for (int i = 0; i < input.length(); ++i) {
		if (input[i] == ' ' && input[i - 1] != ' ') {
			wordEndIndex = i - 1;
			if (isValid) {
				for (int j = wordStartIndex; j <= wordEndIndex; ++j) {
					cout << input[j];
				}
				cout << " ";
			}
		} else {
			if (i > 0 && input[i - 1] == ' ' && input[i] != ' ') {
				wordStartIndex = i;
				isValid = true;
			}
			if (wordEndIndex <= wordStartIndex && input[i] != ' ') {
				bool present = find(begin(vowels), end(vowels), input[i]) != end(vowels);
				if (i != wordStartIndex && isVowel == present) {
					isValid = false;
					for (int j = i + 1; j < input.length(); ++j) {
						if (input[j] == ' ') {
							i = j - 1;
							break;
						}
					}
				}
				isVowel = present;
			}
		}
	}

	return 0;
}