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
#include "matrix.h"
#include "activ.h"
#include "neural.h"
#include "ffnet.h"
#include "backprop.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h> //Don't forget -lm Cflag

//Feed-Forward Network Operations Functions:

FFNet createFFNet(int layersSize[], int layersNb) {
	FFNet init;
	int length = layersNb;
	int max = 0;
	for(int i = 0; i < length && layersSize[i] > max; max = layersSize[i], i++);

	//Initializing metrics
	init.layersNb = layersNb;
	init.layersSize = layersSize;
	init.maxInputsNb = max;
	init.layersActivity = malloc((layersNb-1)*sizeof(Matrix));
	init.layersActivation = malloc((layersNb-1)*sizeof(Matrix));

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

Matrix weights2Mat(FFNet* net, int layer) {
	int nbL = net->layersSize[layer-1];
	int nbC = net->layersSize[layer];
	double* weights = malloc(nbL * nbC * sizeof(double));
	for(int i = 0; i < nbL; ++i) {
		for(int j = 0; j < nbC; ++j) {
			*(weights+i+j) = net->layers[layer][j].weights[i];
		}
	}
	return createMatrix(weights, nbL, nbC);
}

Matrix __forwardProp(FFNet* net,int layer,Matrix inputs,Matrix* activLayer){
	//Creating weights matrix
	Matrix weightsMat = weights2Mat(net, layer);

	//Creating layer activity matrix
	Matrix layerActivity = multMatrix(&inputs, &weightsMat);
	//Saving layer activity into network
	*activLayer = layerActivity;
	//Return output matrix (applied sigmoid)
	return sig2Mat(&layerActivity);
}

Matrix forwardPropagation(FFNet* net, Matrix inputs) {
	for(int i = 1; i < net->layersNb; i++) {
		inputs= __forwardProp(net,i,inputs,&net->layersActivity[i-1]);
		net->layersActivation[i-1] = inputs;
	}
	return inputs;
}

//Test zone
int main() {
	int layers[3] = {2,3,1};
	FFNet network = createFFNet(layers, 3);
	double inputs[8] = {0,0,0,1,1,0,1,1};
	Matrix inputsMat = createMatrix(inputs, 4, 2);
	double results[4] = {0,1,1,0};
	Matrix resultsMat = createMatrix(results, 4, 1);

	printf("\nInputs Matrix:\n");
	printMatrix(inputsMat);
	Matrix output = forwardPropagation(&network, inputsMat);
	printf("\nResults Matrix:\n");
	printMatrix(output);
	printf("\nOverall Cost: %f \n", cost(output, resultsMat));
	return 0;
}
