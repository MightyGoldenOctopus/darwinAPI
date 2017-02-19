/*
 * =====================================================================================
 *
 *       Filename:  neuralcore.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/19/2017 08:56:36 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.A Ducastaing (ducast_j), jean-adrien.ducastaing@epita.fr
 *        Company:  EPITA
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

#ifndef NEURALCORE_H
#define NEURALCORE_H

typedef struct
{
	 int inputsPerNeuron;
         int neurons;
         size_t inputs;
         size_t weights;
         size_t errors;
         size_t biasweights;
         double* inputsList;
         double* weightsList;
         size_t* linksList;
         double* errorsList;
         double* biasweightsList;
         int* isinput;
         int* isoutput;
 } Network;

void updateSecondaryMetrics(Network* neurons_array);
void initialize(int inputNb, Network* neurons_array);
void addNeuron(Network* neurons_array);
double output(double x);
double derivative(double x);
double neuronOutput(size_t id, Network* neurons_array);
void setInputs(size_t id, double inputs[], Network* neurons_array);
void adjustWeights(size_t id, size_t layerstartid, size_t outputstartid, size_t output_nb, double result, Network* neurons_array);
void neuronLinking(size_t id, Network* neurons_array);
void addLink(size_t id1, size_t id2, Network* neurons_array);
void saveNetwork(char saveName[], Network* neurons_array);
void loadNetwork(char saveName[], Network* neurons_array);
int isInput(size_t id, Network* neurons_array);
int isOutput(size_t id, Network* neurons_array);
void setInputStat(size_t id, int param, Network* neurons_array);
void setOutputStat(size_t id, int param, Network* neurons_array);
int getInputsNb(Network* neurons_array);
int getNeuronsNb(Network* neurons_array);
#endif
