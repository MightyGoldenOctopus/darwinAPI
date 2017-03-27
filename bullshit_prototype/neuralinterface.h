/*
 * =====================================================================================
 *
 *       Filename:  neuralinterface.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/23/2017 04:30:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.A Ducastaing (ducast_j), jean-adrien.ducastaing@epita.fr
 *        Company:  EPITA
 *
 * =====================================================================================
 */

#ifndef NEURALINTERFACE_H
#define NEURALINTERFACE_H

void createFFB(char name[], int neurons_Layer[], int inputs);
void trainFFB((char name[], int neuronsLayer[], double inputs[][], double results[]));
double* computeFFB(char name[], size_t outputLayerStart, int outputs);

#endif
