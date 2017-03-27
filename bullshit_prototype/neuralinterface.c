/*
 * =====================================================================================
 *
 *       Filename:  neuralinterface.c
 *
 *    Description:  Primary interface file for Darwin API
 *
 *        Version:  1.0
 *        Created:  02/02/2017 01:06:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.A Ducastaing (ducast_j), jean-adrien.ducastaing@epita.fr
 *        Company:  EPITA (becoming property of ZaphTech S.A.S on summer 2017)
 *
 * =====================================================================================
 */

#include "neuralcore.h"
#include "neuralinterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Direct use of this interface for advanced users only
//Please use a more idiot-proof interface instead

//Create a Feed-Forward network using backpropagation
//neuronsLayer[] : nb of neurons for each layers
//For n elements, layer 0 is input and layer n is output
//inputs : nb of inputs per neurons
//CAUTION: Except output layer, for layer n neuronsLayer[n] < inputs
void createFFB(char name[], int neuronsLayer[], int inputs) {
	int layers = sizeof(neuronsLayer)/sizeof(int);
	//Generating input layer
	//NOTE: The first neuron is created in initialization
	Network neurons_array;
	initialize(inputs, neurons_array);
	setInputStat(0, 1, neurons_array);
	for(int i = 1; i < neuronsLayer[0], i++) {
		addNeuron(neurons_array);
		setInputStat(i, 1, neurons_array);
	}
	//Generating hidden layers
	size_t currentid = (size_t) (neuronsLayer[0] - 1); //OK
	size_t lowerLayer = 0;
	for(int j == 1; j < layers - 2; j++) {
		for(int k = 0; k < neuronsLayer[j]; k++) {
			currentid++;
			addNeuron(neurons_array);
			//Generating neuron linking
			for(int l = lowerLayer; l < lowerLayer + neuronsLayer[j-1]; l++) {
				addLink(l , currentid, neurons_array);
			}
		}
		lowerLayer += neuronsLayer[j];	
	}
	//Generating output layer
	for(int m = 0; m < neuronsLayer[layers-1]) {
		addNeuron(neurons_array);
		setOutputStat(currentid+m+1, 1, neurons_array);
		for(int n = 0; n < neuronsLayer[layers-2]; n++) {
			addLink(n, currentid+m+1, neurons_array);
		}
	}
	//Saving network
	saveNetwork(name, neurons_array);
	printf("Network successfully created!");
}

//inputs must be a matrix of size inputsPerNeuron*neuronsLayer[0]
void trainFFB(char name[], int neuronsLayer[], double inputs[][], double results[]) { //FIXME
	//Loading network
	Network neurons_array;
	loadNetwork(name, neurons_array);
	int epoch = 0;
	//Getting network's metrics
	int inputsPerNeuron = getInputsNb(neurons_array);
	int layers = sizeof(neuronsLayer)/sizeof(int);
	//Calculating output layer start id
	size_t outputstartid = 0
	for(int i = 0; i < layers - 1; i++) {
		outputstartid += neuronsLayer[i];
	}
	//epoch must be comprised between 10K & 100K to be effective
	while(epoch < 50000) {
		epoch++;
		//Set input layer inputs
		for(int i = 0; i < neuronsLayer[0] - i) {
			setInputs(i, inputs[i][], neurons_array);
		}
		//Neuron output function got a built-in linking function
		//Thus when you plot a neuron's output, all preceding neurons
		//linked directly or inderectly to this neuron are plotted as well
		//So because the neuralcore's functions are badass, there's no
		//need of making calculations for hiddens layers

		//SO HERE WE ADJUST WEIGHTS FOR OUTPUT LAYER
		//Note that neuron's output are inplicitly calculated
		//in the adjustweight function, enjoy the ride.
		//Parameters sets to 0 are irrelevant in present cases
		for(int i = 0; i < neuronsLayer[layers-1]; i++) {
			adjustWeights(outputstartid+i, 0, 0, result[i], neurons_array); //OK
		}
		//Adjusting weights for hiddens layers
		size_t layerStartId = neuronsLayer[0]; //OK
		for(int i = 1, i < layers-2; i++) {
			for(int j = 0; j < neuronsLayer[i]-1; j++) {
				adjustWeights(layerStartId+j, layerStartId, outputstartid, 0.0, neurons_array);
			}
			layerStartId += neuronsLayer[i];
		}
	}
	//Saving network with weights balance changes
	saveNetwork(name);
	printf("Network successfully trained");
}

double* computeFFB(char name[], size_t outputLayerStart, int outputs) {
	Network neurons_array;
	loadNetwork(name, neurons_array);
	double* results = malloc(sizeof(double) * outputs);
	for(int i = outputLayerStart; i < outputs - 1; i++) {
		results + i = neuronOutput(i, neurons_array);
	}
	return results;
}

//TO-DO List:
//->BUY COFFEE
//->Feed-Forward Network with forward propagation
//->Competitive Network (Hemming Net & Maxnet)
//->Hopfield Network
//->Adaptive Resonance Theory Network
//->Kohonen Self-Organizing Maps
//->BUY MORE COFFEE
//->READ MORE STANDFORD PAPERS
