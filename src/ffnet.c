/*
 * =====================================================================================
 *
 *       Filename:  ffnet.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/27/2017 07:21:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.A Ducastaing (ducast_j), jean-adrien.ducastaing@epita.fr
 *        Company:  EPITA
 *
 * =====================================================================================
 */

#include	"ffnet.h"
#include "matrix.h"
#include "activFunc.h"
#include "neural.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h> //Don't forget -lm Cflag

//Feed-Forward Network Operations Functions:

FFNet createFFNet(int layersSize[]) {
	FFNet init;
	//Computing maxInputsNb
	int length = sizeof(layersSize)/sizeof(int);
	int max = 0;
	for(int i = 0; i < length && layersSize[i] > max; max = layersSize[i], i++);

	//Initializing metrics
	init.layersSize = layersSize;
	init.maxInputsNb = max;

	//Constructing Network
	init.inputLayer = malloc(layersSize[0] * sizeof(double));
	init.layers = 	malloc((length - 2) * sizeof(Neuron*));
	//layers[layerNb][neuronID] = neuron
	for(int i = 1; i < length; i++) {
		Neuron* layer = 	malloc(layersSize[i] * sizeof(Neuron));
		for(int j = 0; j < layersSize[i]; j++) {
			layer[j] = createNeuron(init.maxInputsNb);
		}
		init.layers[i] = layer;
	}

	return init;
}

//Feed-Forward Network Computation Functions:

Matrix __forwardPropagation(FFNet* network, int layer, Matrix inputs) {
	//Creating weights matrix
	int nbL = network->layersSize[layer-1];
	int nbC = network->layersSize[layer];
	double* weights = malloc(nbL * nbC * sizeof(double));
	for(int i = 0; i < nbL; i++) {
		for(int j = 0; j < nbC; j++) {
			*(weights + i + j) = network->layers[layer][j]->weights[i];
		}
	}
	Matrix weightsMat = createMatrix(weights, nbL, nbC);

	//Creating layer activity matrix
	Matrix layerActivity = multMatrix(&inputs, &weightsMat);

	//Return output matrix (applied sigmoid)
	return sig2Mat(layerActivity);
}

double** forwardPropagation(FFNet* network, double** inputs) {
	for(int i = 1; i < sizeof(network->layersSize)/sizeof(int); i++) {
		inputs = __forwardPropagation(network, i, inputs);
	}
	return inputs;
}
