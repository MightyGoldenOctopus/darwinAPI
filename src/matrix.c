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
#include <stdio.h>
#include "matrix.h"

Matrix createMatrix(double* data, int nbL, int nbC) {
	Matrix init;
	init.nbL = nbL;
	init.nbC = nbC;
	init.data = data;
	return init;
}

double* elemMat(Matrix m, int i, int j){
	return &(m.data[i * m.nbC + j]);
}

Matrix multMatrix(Matrix* m1, Matrix* m2) {
	double* result = malloc(m1->nbL * m2->nbC * sizeof(double));
	Matrix m3 = createMatrix(result, m1->nbL, m2->nbC);
	for(int i = 0; i < m1->nbL; ++i) {
		for(int j = 0; j < m2->nbC; ++j) {
			double sum = 0;
			for(int k = 0; k < m1->nbL; ++k) {
				sum += *elemMat(*m1, i, k) * *elemMat(*m2, k, j);
			}
			*elemMat(m3, i, j) = sum;
		}
	}
	return m3;
}

Matrix addMatrix(Matrix* m1, Matrix* m2) {
	double* result = malloc(m1->nbL * m1->nbC * sizeof(double));
	Matrix m3 = createMatrix(result, m1->nbL, m2->nbC);
	for(int i = 0; i < m1->nbL; ++i) {
		for(int j = 0; j < m1->nbC; ++j) {
			*elemMat(m3, i, j) = *elemMat(*m1,i,j) + *elemMat(*m2,i,j);
		}
	}
	return m3;
}

Matrix coeffMatrix(Matrix* m1, double coeff) {
	double* result = malloc(m1->nbL * m1->nbC * sizeof(double));
	Matrix m3 = createMatrix(result, m1->nbL, m1->nbC);
	for(int i = 0; i < m1-> nbL; ++i) {
		for(int j = 0; j < m1->nbC; ++j) {
			*elemMat(m3,i,j) = *elemMat(*m1,i,j) * coeff;
		}
	}
	return m3;
}

void printMatrix(Matrix m) {
	for(int i = 0; i < m.nbL; ++i) {
		for(int j = 0; j < m.nbC; ++j) {
			printf("%f ", *elemMat(m, i, j));
		}
		printf("\n");
	}
}
