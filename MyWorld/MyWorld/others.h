#ifndef OTHERS_H
#define OTHERS_H
#include"chrono"
using namespace std::chrono;
long long  gettime();
///////////////////////////////
struct Random {
	void SetSeed(int seed);
	int rand(int begin,int end);
};
///////////////////////////////
int Get_2_N_POW(int num);
#endif // OTHERS_H
