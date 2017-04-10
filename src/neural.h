/*
 * =====================================================================================
 *
 *       Filename:  neural.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/10/2017 10:43:25 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.A Ducastaing (ducast_j), jean-adrien.ducastaing@epita.fr
 *        Company:  EPITA
 *
 * =====================================================================================
 */

#ifndef NEURAL_H_
#define NEURAL_H_

typedef struct {
	double* weights;
} Neuron;

Neuron createNeuron(int nbInput);

#endif
