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
 } neurons_array;

void updateSecondaryMetrics();
void initialize(int inputNb);
void addNeuron();
double output(double x);
double derivative(double x);
double neuronOutput(size_t id);
double setInputs(size_t id, double inputs[]);
void adjustWeights(size_t id, size_t layerstartid, size_t outputstartid, size_t output_nb, double result);
void neuronLinking(size_t id);
void addLink(size_t id1, size_t id2);
void saveNetwork(char saveName[]);
void loadNetwork(char saveName[]);
int isInput(size_t id);
int isOutput(size_t id);
void setInputStat(size_t id, int param);
void setOutputStat(size_t id, int param);
int getInputsNb();
int getNeuronsNb();
#endif
