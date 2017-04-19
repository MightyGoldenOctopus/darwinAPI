/*
 * =====================================================================================
 *
 *       Filename:  neural.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/10/2017 10:45:56 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.A Ducastaing (ducast_j), jean-adrien.ducastaing@epita.fr
 *        Company:  EPITA
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "neural.h"

Neuron createNeuron(int inputsNb) {
	srand((int)time(NULL));
	Neuron init;
	init.weights = malloc(inputsNb * sizeof(double));
	init.bias =	0;
	for(int i = 0; i < inputsNb; i++) {
		init.weights[i] = (double)rand() / (double)RAND_MAX;
	}
	return init;
}
