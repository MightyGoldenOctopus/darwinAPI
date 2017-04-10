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

double** __forwardPropagation(FFNet* network, int layer, double** inputs) {
	//Calculating layer activity
	double** weightsMatrix = malloc(network->layersSize[layer-1] * sizeof(double*));
	for(int i = 0; i < network->layersSize[layer-1]; i++) {
		double* line = malloc(network->layersSize[layer]*sizeof(double));
		for(int j = 0; j < network->layersSize[layer]; j++) {
			line[j] = network->layers[layer][j].weights[i];
		}
		weightsMatrix[i] = line;
	}
	//layerActivity matrix and its dimensions
	int h;
	int l;
	double** layerActivity = matrixMult(inputs, weightsMatrix, &h, &l);

	//Calculating layer output (applying sigmoid)
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < l; j++) {
			layerActivity[i][j] = sigmoid(layerActivity[i][j]);
		}
	}
	return layerActivity;
}

double** forwardPropagation(FFNet* network, double** inputs) {
	for(int i = 1; i < sizeof(network->layersSize)/sizeof(int); i++) {
		inputs = __forwardPropagation(network, i, inputs);
	}
	return inputs;
}

//Basic Neural Functions:

Neuron createNeuron(int inputsNb) {
	Neuron init;
	init.inputs = 	malloc(inputsNb * sizeof(double));
	init.weights =	malloc(inputsNb * sizeof(double));
	for(int i = 0; i < inputsNb; i++) {
		init.weights[i] = (double)rand() / (double)RAND_MAX;
	}
	return init;
}

//Generics Maths Functions:

double sigmoid(double x) {
	return 1.0 / (1.0 + exp(-x));
}

double derivative(double x) {
	return x * (1.0 - x);
}
