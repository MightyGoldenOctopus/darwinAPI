/*
 * =====================================================================================
 *
 *       Filename:  serialize.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/11/2017 09:51:03 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  J.A Ducastaing (ducast_j), jean-adrien.ducastaing@epita.fr
 *        Company:  EPITA
 *
 * =====================================================================================
 */

#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "matrix.h"
#include "ffnet.h"
#include <string.h>
#include <stdio.h>

void serialMatrix(Matrix* m, FILE* f);
void serialFFNet(FFNet* network, char* savename);
FFNet loadFFNet(char* savename);

#endif
