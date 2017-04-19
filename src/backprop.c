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
#include "activ.h"

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

Matrix hiddenGradient(FFNet* net, int layer, Matrix* deltaSup) {
/* To be used with layer index comprised between first h layer+1
 * and last hidden layer.
 */
	Matrix weights = weights2Mat(net, layer);
	weights = transMatrix(&weights);
	Matrix activation = sigPrime2Mat(&(net->layersActivation[layer]));
	Matrix delta = multMatrix(deltaSup,&weights);
	delta = ewMultMatrix(&delta,&activation);
	Matrix dJdW = multMatrix(&(net->layersActivity[layer-1]),deltaSup);
	return dJdW;
}

Matrix* costPrime(FFNet* net, Matrix* output, Matrix* results) {
	//Gradient matrix for each hidden layers
	Matrix* gradients = malloc(((net->layersNb)-2) * sizeof(Matrix));
	//Output's layer delta
	Matrix negOut = coeffMatrix(output,-1);
	Matrix deltaOut = addMatrix(results,&negOut);
	deltaOut = coeffMatrix(&deltaOut,-1);
	Matrix activationOut = sigPrime2Mat(output);
	deltaOut = ewMultMatrix(&deltaOut,&activationOut);
	
	
}
