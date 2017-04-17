/*
 * =====================================================================================
 *
 *       Filename:  backprop.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/17/2017 01:16:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.A Ducastaing (ducast_j), jean-adrien.ducastaing@epita.fr
 *        Company:  EPITA
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "ffnet.h"

double cost(Matrix output, Matrix results) {
	double sum = 0;
	double product;
	for(int i = 0; i < output.nbL; ++i) {
		for(int j = 0; j < output.nbC; ++j) {
			product = (*elemMat(results,i,j) - *elemMat(output,i,j));
			product *= product;
			sum += product;
		}
	}
	sum /= 2;
	return sum;
}

double costPrime()
