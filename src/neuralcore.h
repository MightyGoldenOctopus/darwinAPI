/*
 * =====================================================================================
 *
 *       Filename:  neuralcore.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/27/2017 07:21:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.A Ducastaing (ducast_j), jean-adrien.ducastaing@epita.fr
 *        Company:  EPITA
 *
 * =====================================================================================
 */

#ifndef NEURALCORE_H_
#define NEURALCORE_H_

typedef struct {
	double*	inputs;
	double* 	weights;
	double 	activity;
	double	output;
} Neuron;

typedef struct {
	int			layersSize[];
	int			maxInputsNb;
	double*		inputLayer;
	Neuron** 	layers;
} FFNet;

//FFNet Ops Functions
FFNet createFFNet(int layersSize[]);
//FFNet Computation Functions:
double[][] __forwardPropagation(FFNet* network, int layer, double inputs[][]);
double[][] forwardPropagation(FFNet* network, double inputs[][]);
//Basics Neural Functions
Neuron createNeuron(int inputsNb);
//Generic Maths Functions
double sigmoid(double x);
double derivative(double x);
double[][] matrixMult(double m1[][], double m2[][]);

#endif
