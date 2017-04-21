/*
 * =====================================================================================
 *
 *       Filename:  ffnet.h
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

#ifndef FFNET_H_
#define FFNET_H_

#include "neural.h"
#include "matrix.h"

typedef struct {
	int*			layersSize;
	int			layersNb;
	Matrix*		layersWeights;
	Matrix*		layersActivity;
	Matrix*		layersActivation;
} FFNet;

//FFNet Ops Functions
FFNet createFFNet(int layersSize[], int layersNb);
//FFNet Computation Functions:
Matrix weightsMat(FFNet* net, int layer);
Matrix __forwardPropagation(FFNet* net, int layer, Matrix inputs);
Matrix forwardPropagation(FFNet* net, Matrix inputs);
#endif
