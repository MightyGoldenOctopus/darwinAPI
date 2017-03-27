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
	int length = sizeof(layerSize)/sizeof(int);
	int max = 0;
	for(int i = 0; i < length && layersSize[i] > max; max = layersSize[i], i++);

	//Initializing metrics
	init.layersSize = layersSize;
	init.maxInputsNb = max;

	//Constructing Network
	init.inputLayer = 	malloc(layersSize[0] * sizeof(double));
	init.layers = 	malloc((length - 2) * sizeof(Neuron*));
	//layers[layerNb][neuronID] = neuron
	for(int i = 1; i < length; i++) {
		Neuron* layer = 	malloc(layersSize[i] * sizeof(Neuron));
		for(int j = 0; j < layersSize[i]; j++) {
			layer[j] = createNeuron(int inputsNb);
		}
		init.layers[i] = layer;
	}

	return init;
}

//Feed-Forward Network Computation Functions:

double[][] __forwardPropagation(FFNet* network, int layer, double inputs[][]) {
	//Calculating layer activity
	double weightsMatrix[network.layersSize[layer-1]][network.layersSize[layer]];
	for(int i = 0; i < network.layersSize[layer-1]; i++) {
		for(int j = 0; j < network.layersSize[layer]; j++) {
			weightsMatrix[i][j] = network->layers[layer][j]->weights[i];
		}
	}
	int length = network.layersSize[layer];
	int height = sizeof(inputs[]);
	double layerActivity[height][length] = matrixMult(inputs, weightsMatrix);

	//Calculating layer output
	double layerOutput[height][length];
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < length; j++) {
			layerOutput[i][j] = sigmoid(layerActivity[i][j]);
		}
	}
	return layerOutput;
}

double[][] forwardPropagation(FFNet* network, double inputs[][]) {
	for(int i = 1; i < sizeof(network.layersSize)/sizeof(int); i++) {
		feed = __forwardPropagation(network, i, feed);
	}
	return feed;
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

double[][] matrixMult(double m1[][], double m2[][]) {
	//Calculating matrix sizes
	int h1 = sizeof(m1) / sizeof(m1[0]);
	int l1 = sizeof(m1[0]) / sizeof(double);
	int h2 = sizeof(m2) / sizeof(m2[0]);
	int l2 = sizeof(m2[0]) / sizeof(double);
	if(l1 != h2 || h1 != l2) {
		printf("WARNING: Invalid matrix sizes for multiplication!");
	}
	//Calculating product
	double m3[l1][h2];
	for(int i = 0; i < l1; i++) {
		for(int j = 0; j < h2; j++) {
			double sum = 0;
			for(int k = 0; k < h1; k++) {
				sum += m1[k][i] * m2[j][k];
			}
			m3[j][i] = sum;
		}
	}
	return m3;
}
