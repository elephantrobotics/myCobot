#include <vector>
#include <cstdio>
#include <algorithm>

int main()
{
	// output on Uart0, see common/uart.cpp
	puts("AVR libstdc++ vector test\n");

	std::vector<uint8_t> test{10, 1, 2, 42, 3};
	test.push_back(4);
	test.erase(test.begin());

	if(auto it = std::find(test.begin(), test.end(), 42); it != test.end()) {
		test.erase(it);
	}

	for(auto i : test) {
		printf("%i ", i);
	}
 	puts("\n");
}
