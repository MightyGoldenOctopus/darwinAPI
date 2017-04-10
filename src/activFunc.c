/*
 * =====================================================================================
 *
 *       Filename:  activFunc.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/10/2017 10:35:20 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.A Ducastaing (ducast_j), jean-adrien.ducastaing@epita.fr
 *        Company:  EPITA
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "activFunc.h"

double sigmoid(double x) {
	return 1.0 / (1.0 + exp(-x);
}

double sigmoidDerivative(double x) {
	return x * (1.0 - x);
}

double softMax(double x) {
	//FIXME
	return 0.0;
}