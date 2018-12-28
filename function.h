#pragma once
#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define random(x) (rand()%x)
#define CodeL 10
#define Size 500
typedef struct {
	int current_best;
	double fi;
}cb;
void init(int(*E)[2*CodeL], int size);
void decode(int(*E)[2*CodeL], double *fi, int size);
cb selectAndReproduct(int(*E)[2*CodeL], double *fi, int size);
void crossOver(int(*E)[2*CodeL], int size,int current_best);
void mutation(int(*E)[2*CodeL], int size,int current_best);
void sort(double f[Size], int index[Size], int size);
#endif