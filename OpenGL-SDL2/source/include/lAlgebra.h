#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//  create a v3, mat4x4, matrix translate

#ifndef LAGEBRA_H
#define LAGEBRA_H

//  mat4 create a matrix
//  1, 0, 0, 0,
//  0, 1, 0, 0,
//  0, 0, 1, 0,
//  0, 0, 0, 1

//  translate: sum or substract each value
float **algTranslate(float val, float v3[]);
void algTrans(float val, float v3[], float result[]);
void *algTransla(float val, float v3[], float *matrix);

#endif