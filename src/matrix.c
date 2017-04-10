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

Matrix createMatrix(double* data, int nbL, int nbC) {
	Matrix init;
	init.nbL = nbL;
	init.nbC = nbC;
	init.data = data;
	return init;
}

double* elemMatrix(Matrix* matrix, int i, int j) {
	return (matrix->data + i + j);
}

Matrix multMatrix(Matrix* m1, Matrix* m2) {
	double* result = malloc(m1->nbL * m2->nbC * sizeof(double));
	Matrix m3 = createMatrix(result, m1->nbL, m2->nbC);
	for(int i = 0; i < m1->nbL; i++) {
		for(int j = 0; j < m2->nbC; j++) {
			double sum = 0;
			for(int k = 0; k < m1->nbL; k++) {
				sum += *elemMatrix(m1, i, j) * *elemMatrix(m2, i, j);
			}
			*elemMatrix(m3, i, j) = sum;
		}
	}
	return m3;
}
