/*
 * =====================================================================================
 *
 *       Filename:  serialize.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/10/2017 04:14:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.A Ducastaing (ducast_j), jean-adrien.ducastaing@epita.fr
 *        Company:  EPITA
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "serialize.h"

void serialMatrix(Matrix* m, FILE* f){
	if(f == NULL){
		printf("Unable to write matrix in specified file.");
	}
	for(int i = 0; i < m->nbC * m->nbL; i++){
		fprintf(f, "%lf\n", m->data[i]);
	}
}

void serialFFNet(FFNet* network, char* savename){
	FILE* f = fopen(savename, "w");
	if(f == NULL){
		printf("Unable to write file.");
	}
	//Writing network metrics
	fprintf(f, "%d\n", network->layersNb);
	for(int i = 0; i < network->layersNb; i++){
		fprintf(f, "%d\n", network->layersSize[i]);
	}
	//Writing weights matrix
	for(int i = 0; i < network->layersNb - 1; i++){
		serialMatrix(&(network->layersWeights[i]), f);
	}
	fclose(f);
}

FFNet loadFFNet(char* savename){
	FILE* f = fopen(savename, "r");
	if(f == NULL){
		printf("Unable to find/read file.");
	}
	FFNet init;
	//Loading network metrics
	int metrics;
	fscanf(f, "%d", &metrics);	
	init.layersNb = metrics;
	init.layersSize = malloc(init.layersNb * sizeof(int));
	for(int i = 0; i < init.layersNb; i++){
		fscanf(f, "%d", &metrics);
		init.layersSize[i] = metrics;
	}
	//Allocating operations matrix arrays
	init.layersActivity = malloc(init.layersNb*sizeof(Matrix));
	init.layersActivation = malloc((init.layersNb-1)*sizeof(Matrix));
	//Loading network weights
	double weight;
	init.layersWeights = malloc((init.layersNb-1)*sizeof(Matrix));
	for(int i = 0; i < init.layersNb - 1; i++){
		double* data = malloc(init.layersSize[i]*init.layersSize[i+1]*sizeof(double));
		for(int j = 0; j < i*(i+1); j++){
			fscanf(f, "%lf", &weight);
			data[j] = weight;
		}
		Matrix weightsMatrix = createMatrix(data, init.layersSize[i], init.layersSize[i+1]);
		init.layersWeights[i] = weightsMatrix;
	}
	fclose(f);
	return init;
}
