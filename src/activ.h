/*
 * =====================================================================================
 *
 *       Filename:  activ.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/10/2017 10:30:22 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.A Ducastaing (ducast_j), jean-adrien.ducastaing@epita.fr
 *        Company:  EPITA
 *
 * =====================================================================================
 */

#ifndef ACTIV_H_
#define ACTIV_H_

#include "matrix.h"

double sigmoid(double x);
double sigmoidDerivative(double x);
Matrix sig2Mat(Matrix* m);
Matrix sigPrime2Mat(Matrix* m);

double softMax(double x);
#endif
