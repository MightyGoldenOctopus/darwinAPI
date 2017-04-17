/*
 * =====================================================================================
 *
 *       Filename:  activ.c
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
#include <math.h>
#include "activ.h"
#include "matrix.h"

double sigmoid(double x) {
	return 1.0 / (1.0 + exp(-x));
}

double sigmoidDerivative(double x) {
	return x * (1.0 - x);
}

Matrix sig2Mat(Matrix* m) {
	double* results = malloc(m->nbL * m->nbC * sizeof(double));
	Matrix m3 = createMatrix(results, m->nbL, m->nbC);
	for(int i = 0; i < m->nbL; ++i) {
		for(int j = 0; j < m->nbC; ++j) {
			*elemMat(m3, i, j) = sigmoid(*elemMat(*m, i, j));
		}
	}
	return m3;
}

Matrix sigPrime2Mat(Matrix* m) {
	double* results = malloc(m->nbL * m->nbC * sizeof(double));
	Matrix m3 = createMatrix(results, m->nbL, m->nbC);
	for(int i = 0; i < m->nbL; ++i) {
		for(int j = 0; j < m->nbC; ++j) {
			*elemMat(m3, i, j) = sigmoidDerivative(*elemMat(*m, i, j));
		}
	}
	return m3;
}

double softMax(double x) {
	//FIXME
	return 0.0;
}
