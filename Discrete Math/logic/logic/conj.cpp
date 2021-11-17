/*
* @author Nickel_Angel (1239004072@qq.com)
* @copyright Copyright (c)
*/

#include "conj.hpp"

bool condition(bool P, bool Q)
{
	return Q & !P;
}

bool bicondition(bool P, bool Q)
{
	return (P & Q) | (!P & !Q);
}