/*
 * =====================================================================================
 *
 *       Filename:  matrix.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/10/2017 09:55:12 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.A Ducastaing (ducast_j), jean-adrien.ducastaing@epita.fr
 *        Company:  EPITA
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "matrix.h"

Matrix createMatrix(double* data, int nbL, int nbC) {
	Matrix init;
	init.nbL = nbL;
	init.nbC = nbC;
	init.data = data;
	return init;
}

Matrix multMatrix(Matrix* m1, Matrix* m2) {
	double* result = malloc(m1->nbL * m2->nbC * sizeof(double));
	Matrix m3 = createMatrix(result, m1->nbL, m2->nbC);
	for(int i = 0; i < m1->nbL; i++) {
		for(int j = 0; j < m2->nbC; j++) {
			double sum = 0;
			for(int k = 0; k < m1->nbL; k++) {
				sum += m1->data[i+k] * m2->data[k+j];
			}
			m3.data[i+j] = sum;
		}
	}
	return m3;
}
