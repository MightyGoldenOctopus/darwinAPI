/*
 * =====================================================================================
 *
 *       Filename:  neuralcore.c
 *
 *    Description:  Core file for Darwin API
 *
 *        Version:  1.0
 *        Created:  12/19/2016 08:09:33 AM
 *       Revision:  TBD
 *       Compiler:  gcc
 *
 *         Author:  J.A Ducastaing (ducast_j), jean-adrien.ducastaing@epita.fr
 *        Company:  none
 *
 * =====================================================================================
 */
#include "neuralcore.h"
//Don't forget the -lm at the end of cflags!

//Feed-Forward Network Neurons Array Architecture Convention:
//ADDRESS MAX
// ->Output Layer n
// ->Hidden Layer n-1
// -> ...
// ->Hidden Layer 2
// ->Layer 1 (Input Neurons)
//ADDRESS 0

void updateSecondaryMetrics(Network* neurons_array) {
	//Getting primary metrics
	int inputs = neurons_array->inputsPerNeuron;
	int neurons = neurons_array->neurons;
	//Updating secondary metrics
	neurons_array->inputs 		= (size_t) (inputs * neurons);
	neurons_array->weights 		= (size_t) (inputs * neurons);
	neurons_array->errors 		= (size_t) neurons;
	neurons_array->biasweights 	= (size_t) neurons;
}

//Neurons array initialization function
void initialize(int inputsNb, Network* neurons_array) {
	neurons_array->neurons = 0;
	//Initializing inputs array
	neurons_array->inputsList 	= malloc((size_t)inputsNb * sizeof(double));
	//Initializing weights and secondary properties
	neurons_array->weightsList 	= malloc((size_t)inputsNb * sizeof(double));
	neurons_array->linksList 	= malloc((size_t)inputNb * sizeof(size_t));
	neurons_array->errorsList 	= malloc(sizeof(double));
	neurons_array->biasweightsList 	= malloc(sizeof(double));
	neurons_array->isinput 		= malloc(sizeof(int));	
	neurons_array->isoutput 	= malloc(sizeof(int))
	for(int i = 0; i < inputsNb; i++) {
		*(neurons_array->weightsList + i) = (double)rand() / (double)RAND_MAX;
		*(neurons_array->linksList + i) = 9000;
		//This is an initialization value
	}
	*(neurons_array->errorsList) 		= 0.0;
	*(neurons_array->biasweightsList) 	= 0.0;
	*(neurons_array->isinput) 		= 0;
	*(neurons_array->isoutput) 		= 0;
	//Initializing neurons primary metrics
	neurons_array->inputsPerNeuron 	= inputsNb;
	neurons_array->inputsTypeCode 	= inputsType;
	(neurons_array->neurons)++;
	//Updating secondary metrics
	updateSecondaryMetrics();
}
//Neuron adding function
void addNeuron(Network* neurons_array) {
	//Updating neccessary metrics
	(neurons_array->neurons)++;
	updateSecondaryMetrics();
	//Getting primary metrics
	int neurons = neurons_array->neurons;
	int inputs = neurons_array->inputsPerNeuron;
	//Reallocating dynamic memory
	neurons_array->inputsList 	= realloc(neurons_array -> inputsList, (size_t) (neurons * inputs) * sizeof(double));
	neurons_array->weightsList 	= realloc(neurons_array -> weightsList, (size_t) (neurons * inputs) * sizeof(double));
	neurons_array->linksList 	= realloc(neurons_array -> linkList, (size_t) (neurons * inputs) * sizeof(size_t));
	neurons_array->errorsList	= realloc(neurons_array -> errorLists, (size_t) neurons * sizeof(double));
	neurons_array->biasweightsList	= realloc(neurons_array -> biasweightsList, (size_t) neurons * sizeof(double));
	neurons_array->isinput 		= realloc(neurons_array -> isinput, (size_t) neurons * sizeof(int));
	neurons_array->isoutput 	= realloc(neurons_array -> isoutput, (size_t) neurons * sizeof(int));
	//Initializing weigths and secondary properties
	for(int i = (neurons-1) * inputs; i < neurons * inputs; i++) { 
	//Starting adress (using correct pointers arithmetics) of last 
	//neuron's inputs list = (neurons-1) * inputs
		*(neurons_array->weightsList + i) 	= (double)rand() / (double)RAND_MAX;
		*(neurons_array->linksList + i) 	= (neurons_array -> inputsPerNeuron) + 1;
	}
	*(neurons_array->errorsList + neurons) 		= 0.0;
	*(neurons_array->biaswightsList + neurons) 	= 0.0;
	*(neurons_array->isinput + neurons) 		= 0;
	*(neurons_array->isoutput + neurons) 		= 0;
}

//Output functions
double output(double x) {
	return 1.0 / (1.0 + exp(-x));
}

double derivative(double x) {
	return x * (1.0 - x);
}

//Neuron linking procedure now built-in in output function (enjoy!)
double neuronOutput(size_t id, Network* neurons_array) { 
	//First neuron id's 0, the second's 1 and so on...
	//Getting neuron's metrics
	int inputs = neurons_array->inputsPerNeuron;
	//Computing neurons linking
	if((neurons_array->isInput + id) == 0) {
	//If this neuron is not part of input layer so its linked
		neuronLinking(id);
	}
	//Generating output formula
	double sum = *(neurons_array->biasweightsList + id);
	for(int i = (id - 1) * inputs; i < id * inputs; i++) { 
	//CHECK THIS FORMULA IF SOMETHING WENT WRONG
		sum += ((double) *(neurons_array->inputsList + i)) * ((double) *(neurons_array->weightsList + i)); 
		//CHECK THIS IF THE OUTPUT IS A REAL WTF BULLSHIT
	} 
	return output(sum);
}

//Input function
void setInputs(size_t id, double inputs[], Network* neurons_array) { 
	//Getting neuron's metrics
	int inputsNb = neurons_array->inputsPerNeuron;
	//Filling the neuron's inputs with values contained in the array
	int array_size = sizeof(inputs)/sizeof(double);
	int j = 0;
	for(int i = (id-1) * inputsNb; i < id * inputsMb; i++, j++) {
		//The numbers of inputs per neurons may vary, the 
		//"inputsPerNeuron" variable describe the maximum 
		//number of inputs per neurons
		//Thus if you need less inputs in a neuron, 
		//the remainings inputs slots will be filled with 
		//the null element of the corresponding datatype
		if(i < array_size) {
			*(neurons_array->inputsList + i) = inputs[j];
		}
		else {
			*(neurons_array->inputsList + i) = 0.0;
		}
	}
}

//Backpropagation function
//layerstartid is the starting id of the present layer
//outputstartid is the first id of the output neurons array (see Neural Array Architecture Convention)
//output_nb is the numbers of output neurons in the structure
//The output array can also represent the superior hidden layer in case of multiple hidden layers
void adjustWeights(size_t id, size_t layerstartid, size_t outputstartid, size_t output_nb, double result, Network* neurons_array) {
	int inputs = neurons_array->inputsPerNeurons;
	if(*(neurons_array->isOutput + id) == 1) {
		*(neurons_array->errorList + id) = derivative(neuronOutput(id)) * (result - neuronOutput(id));
	}
	else if(*(neurons_array->isInput + id) == 0) {
		double product = derivative(neuronOutput(id));
		for(int i = outputstartid; i < outputstartid + output_nb; i++) 	{
				product *= (*(neurons_array->errorList + i) * *(neurons_array->weightsList + i + id - layerstartid));
		}
		*(neurons_array->error + id) = product;
	}
	for(int i = (id-1) * inputs; i < id * inputs; i++) {
		*(neurons_array->weightsList + i) = *(neurons_array->errorList + id) * *(neurons_array->inputsList +i);
	}
}

//Neurons linking functions
void neuronLinking(size_t id, Network* neurons_array) {
	size_t link;
	int array;
	int j = 0;
	for(int i = (id-1) * inputs; i++, j++) {
		link = *(neurons_array->linksList + i);
		if(link != 9000) { 
		//Checking if its not bullshit initialization value
			*(neurons_array->inputsList + i) = neuronOutput(link);
		}
		else {
			*(neurons_array->inputsList + i) = 0.0;	
		}
	}
}

void addLink(size_t id1, size_t id2, Network* neurons_array) { 
	//Links neuron 1 output to neuron 2 input
	//Looking for an available link slot
	int i = 0;
	while(*(neurons_array->linksList + id2 + i) != 9000) { 
	//See linksList property initialization process
		i++;
	}
	if(i > inputsPerNeurons) {
		printf("NEURAL LINKING ERROR: NO LINK SLOT AVAILABLE");
	}
	else {
		*(neurons_array->linksList + id2 + i) = neuronOutput(id1);
	}
}

//Network Import/Export functions
void saveNetwork(char saveName[], Network* neurons_array) {
	//Defining save files names
	char nameMetrics[strlen(saveName) + 15];
	strcpy(nameMetrics, saveName);
	strcat(nameMetrics, "Metrics.dat");
	char nameStructure[strlen(saveName) + 15];
	strcpy(nameStructure, saveName);
	strcat(nameStructure, "Structure.dat");
	char nameWeights[strlen(saveNam) + 15];
	strcpy(nameWeights, saveName);
	strcat(nameWeights, "Weights.dat");
	//Metrics save file proccessing
	FILE *metrics = fopen(nameMetrics, "w+");
	fprintf(metrics, "%d\n", neurons_array->inputsPerNeuron);
	fprintf(metrics, "%d\n", neurons_array->neurons);
	fclose(metrics);
	//Structure save file processing
	FILE *structure = fopen(nameStructure, "w+");
	for(int i = 0; i < neurons_array->neurons; i++) {
		for(int j = 0; j < neurons_array->inputsPerNeuron, j++) {
			fprintf(structure, "%u\n", *(neurons_array->linksList + (i*neurons_array->inputsPerNeuron)+j));
		}
		fprintf(structure, "%d\n", *(neurons_array->isInput + i));
		fprintf(structure, "%d\n", *(neurons_array->isOutput + i));
	}
	fclose(structure);
	//Weights save file processing
	FILE *weights = fopen(nameWeights, "w+");
	for(int i = 0; i < neurons_array->neurons; i++) {
		for(int j = i * (neurons_array->inputsPerNeuron); j < neurons_array->inputsPerNeuron; j++) {
			fprintf(weights, "%1f\n", *(neurons_array->weightsList + j));
		}
		fprintf(weights, "%lf\n", *(neurons_array->biasweightsList + i));
		fprintf(weights, "%lf\n", *(neurons_array->errorsList + i));
	}
	fclose(weights);
}

void loadNetwork(char saveName[], Network* neurons_array) {
	//Defining save files names
	char nameMetrics[strlen(saveName) + 15];
	strcpy(nameMetrics, saveName);
	strcat(nameMetrics, "Metrics.dat");
	char nameStructure[strlen(saveName) + 15];
	strcpy(nameStructure, saveName);
	strcat(nameStructure, "Structure.dat");
	char nameWeights[strlen(saveName) + 15];
	strcpy(nameWeights, saveName);
	strcat(nameWeights, "Weights.dat");
	//Metrics loading
	int inputsPerNeuron;
	int neurons;
	FILE *metrics = fopen(nameMetrics, "r");
	if(metrics == NULL) {
		printf("Unable to read metrics file");
	}
	fscanf(metrics, "%d", &inputsPerNeuron);
	fscanf(metrics, "%d", &neurons);
	//Network initialization
	initialize(inputsPerNeuron);
	for(int i = 0; i < neurons - 1; i++) {
		addNeuron();
	}
	//Loading structure
	FILE *structure(nameStructure, "r");
	if(metrics == NULL) {
		printf("Unable to read structure file");
	}
	for(int j = 0; j < neurons; j++) {
		for(int k = 0; k < inputsPerNeuron; k++) {
			 fscanf(structure, "%u", (neurons_array->linksList+(j*inputsPerNeuron)+k));
		}
		fscanf(structure, "%d", (neurons_array->isInput + j));
		fscanf(structure, "%d", (neurons_array->isOutput + j));
	}
	//Loading weights
	FILE *weights = fopen(nameWeights, "r");
	if(weights == NULL) {
		printf("Unable to read weights file");
	}
	for(int l = 0; l < neurons; l++) {
		for(int m = 0; m < inputsPerNeuron; m++) {
			fscanf(weights, "%lf", (neurons_array->weightsList+(l*inputsPerNeuron)+m));
		}
		fscanf(weights, "%lf", (neurons_array->biasweightList+l));
		fscanf(weights, "%lf", (neurons_array->errorsList+l));
	}	 
}

//Getters/Setters
int isInput(size_t id, Network* neurons_array) {
	return *(neurons_array->isInput + id);
}

int isOutput(size_t id, Network* neurons_array) {
	return *(neurons_array->isOutput + id);
}

void setInputStat(size_t id, int param, Network* neurons_array) {
	if(param == 0 || param == 1) {
		*(neurons_array->isInput + id) = param;
	}
	else{
		printf("ERROR: Invalid argument");
	}
}

void setOutputStat(size_t id, int param, Network* neurons_array) {
	if(param == 0 || param == 1) {
		*(neurons_array->isOutput + id) = param;
	}
	else {
		printf("ERROR: Invalid argument");
	}
}

int getInputsNb(Network* neurons_array) {
	return neurons_array->inputsPerNeuron
}

int getNeuronsNb(Network* neurons_array) {
	return neurons_array->neurons;
}

int main(void) {
	//Intializing pseudo-random seed
	srand(time(NULL));
	return 0;
}
