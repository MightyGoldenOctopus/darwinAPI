/*
 * =====================================================================================
 *
 *       Filename:  matrix.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/10/2017 09:52:44 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.A Ducastaing (ducast_j), jean-adrien.ducastaing@epita.fr
 *        Company:  EPITA
 *
 * =====================================================================================
 */

#ifndef MATRIX_H_
#define MATRIX_H_

typedef struct {
	int nbL;
	int nbC;
	double* data;
} Matrix;

Matrix createMatrix(double* data, int nbL, int nbC);
double* elemMat(Matrix m, int i, int j);
Matrix multMatrix(Matrix* m1, Matrix* m2);
Matrix ewMultMatrix(Matrix* m1, Matrix* m2);
Matrix addMatrix(Matrix* m1, Matrix* m2);
Matrix coeffMatrix(Matrix* m1, double coeff);
Matrix transMatrix(Matrix* m);
Matrix absMatrix(Matrix* m);
void printMatrix(Matrix m);
void freeMatrix(Matrix* m);

#endif
