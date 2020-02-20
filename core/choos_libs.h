#include <vector>
#include "Library.h"
using namespace std;


vector < Library > get_lib_order(int D, vector < Library > libs, double t_coef = 1, double b_coef = 0);


vector < Library > get_lib_order_D(int D, vector < Library > libs_, int seed=123);