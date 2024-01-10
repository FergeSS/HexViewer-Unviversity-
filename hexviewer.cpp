#include <iostream>
#include <fstream>
#include <cstring>

void to_16(int digit, char* res, int index) {
	while (digit > 0) {
		res[index] = static_cast<char>(digit % 16 + (digit % 16 > 9 ? 55 : 48));
		--index;
		digit /= 16;
	}
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		std::cout << "Error, not enough arguments" << std::endl;
		return 1;
	}
	std::ifstream inp(argv[1], std::ios::binary);
	std::ofstream otp(argv[2], std::ios::binary);

    if (!inp) {
        std::cout << "Error Input file!\n";
        return 1;
    }

	int shift = 0;
	char symbol[16];
	memset(symbol, '\0', 16);
	char hex[11];
	hex[10] = '\0';
	char hex_2[3];
	hex_2[2] = '\0';
	int k = 0;
	bool flag = true;

	while (inp.peek() != EOF) {
		memset(hex, '0', 10);	
		memset(hex_2, '0', 2);
		to_16(shift, hex, 9);
		otp << hex << ": ";
		shift += 16;

		for (int j = 0; j < 16; ++j) {
            if (j == 8) otp << "| "; 
			if (inp.peek() != EOF) {
				inp.get(symbol[j]);
				to_16(symbol[j], hex_2, 1);
				otp << hex_2 << " ";
				memset(hex_2, '0', 2);
				++k;
			}
			else {
				otp << "   ";
				flag = false;
		    }
        }

		otp << " ";
		for (int m = 0; m < k; ++m) {			
			if (static_cast<char>(symbol[m]) < 32 && static_cast<char>(symbol[m]) >= 0) {
				otp << '.';
			}
			else {
				otp << static_cast<char>(symbol[m]);
			}		
		}
		if (flag) otp << '\n';
		k = 0;
	}

	inp.close();
	otp.close();

	return 0;
}
