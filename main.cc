#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <random>
#include <chrono>
#include "string.h"
#include "controller.h"

using namespace std;

int main(int argc, char * argv[]) {
    Controller c{}; 
    vector<string> arg_vec;
    for (int i = 1; i < argc; i++) {
        arg_vec.emplace_back(argv[i]); 
	}
    return c.general(arg_vec);
}
