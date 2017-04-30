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
#include "ffnet.h"
#include "backprop.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h> //Don't forget -lm Cflag

//Feed-Forward Network Operations Functions:

FFNet createFFNet(int layersSize[], int layersNb) {
	FFNet init;
	//Initializing metrics
	init.layersNb = layersNb;
	init.layersSize = layersSize;
	//Creating operation matrixs
	init.layersActivity = malloc((layersNb)*sizeof(Matrix));
	init.layersActivation = malloc((layersNb-1)*sizeof(Matrix));
	init.layersWeights = malloc((layersNb-1)*sizeof(Matrix));
	//Creating weights matrixs
	srand(time(NULL));
	for(int i = 0; i < init.layersNb - 1; i++) {
		init.layersWeights[i] = weightsMat(&init, i+1);
	}
	return init;
}

//Feed-Forward Network Computation Functions:

Matrix weightsMat(FFNet* net, int layer) {
	int nbL = net->layersSize[layer-1];
	int nbC = net->layersSize[layer];
	double* weights = malloc(nbL * nbC * sizeof(double));
	Matrix res = createMatrix(weights, nbL, nbC);
	for(int i = 0; i < nbL; ++i) {
		for(int j = 0; j < nbC; ++j) {
			*(elemMat(res,i,j)) = (double)rand()/(double)RAND_MAX;
		}
	}
	return res;
}

Matrix __forwardProp(FFNet* net,int layer,Matrix inputs,Matrix* activLayer){
	//Creating layer activation matrix
	*activLayer = multMatrix(&inputs, &net->layersWeights[layer-1]);
	//Returns layer activity matrix
	return sig2Mat(activLayer);
}

Matrix forwardPropagation(FFNet* net, Matrix inputs) {
	net->layersActivity[0] = inputs;
	for(int i = 1; i < net->layersNb; i++) {
		inputs = __forwardProp(net,i,inputs,&net->layersActivation[i-1]);
		net->layersActivity[i] = inputs;
	}
	return inputs;
}

void trainFFNet(FFNet* net, int epoch, Matrix* inputs, Matrix* results){
	Matrix output;
	double lr = 0.1 / inputs->nbL;
	int i = 0;
	while(i < epoch) {
		i++;
		output = forwardPropagation(net, *inputs);
		//Calculating gradients for each layers
		Matrix* gradients = costPrime(net,&output,results);
		//Updating the weights
		int j = 0;
		for(int k = net->layersNb-2; k >= 0; --k, ++j){
			Matrix updateMat = coeffMatrix(&gradients[j],-lr);
			net->layersWeights[k] = addMatrix(&net->layersWeights[k],&updateMat);
			//Freeing used matrix
			freeMatrix(&updateMat);
			freeMatrix(&gradients[j]);
			freeMatrix(&(net->layersActivation[k]));
		}
		free(gradients);
		freeMatrix(&output);
		for(int l = net->layersNb-2; l > 0; --l){
			freeMatrix(&(net->layersActivity[l]));
		}
	}
}

void freeFFNet(FFNet* net) {
	int n = net->layersNb;
	for(int i = 0; i < n-1; ++i) {
		freeMatrix(&(net->layersWeights[i]));
		freeMatrix(&(net->layersActivation[i]));
	}
	for(int j = 1; j < n; ++j) {
		freeMatrix(&(net->layersActivity[j]));
	}
	free(net->layersActivity);
	free(net->layersActivation);
	free(net->layersWeights);
	net = NULL;
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
	
	printf("\nTRAINING NETWORK... (epochs: 250000)\n");
	trainFFNet(&network, 250000, &inputsMat, &resultsMat);

	output = forwardPropagation(&network,inputsMat);
	printf("\nNew Results Matrix:\n");
	printMatrix(output);
	printf("\nNew Overall Cost: %f\n", cost(output, resultsMat));
	freeFFNet(&network);
	return 0;
}
