#include "function.h"
//种群初始化
void init(int(*E)[2*CodeL], int size) {
	srand((int)time(NULL));
	int i, j;
	for (i = 0; i < size; i++)
		for (j = 0; j < 2*CodeL; j++)
			*(*(E + i) + j) = random(2);
}
//二进制编码解码
void decode(int(*E)[2*CodeL], double*fi, int size) {
	double umax = 2.048;
	double umin = -2.048;
	for (int i = 0; i < size; i++) {
		double x1 = 0, x2 = 0;
		for (int j = 0; j < CodeL; j++) {
			x1 += *(*(E + i) + j)*pow(2, j);
			x2 += *(*(E + i) + 10 + j)*pow(2, j);
		}
		x1 = (umax - umin)*x1 / 1023 + umin;
		x2 = (umax - umin)*x2 / 1023 + umin;
		*(fi + i) = 100 * pow(pow(x1, 2) - x2, 2) + pow(1 - x1, 2);
	}
}
//选择算子
cb selectAndReproduct(int(*E)[2*CodeL],double *fi,int size){
	int r=size;
	int fi_size[Size] = { 0 };
	double fi_sum = 0, rest[Size] = { 0 };
	int index_fi[Size] = { 0 }, index_rest[Size] = { 0 };
	for (int i = 0; i < Size; i++) {
		index_fi[i] = i;
		index_rest[i] = i;
	}
	sort(fi, index_fi, size);
	for(int i=0;i<size;i++){
		fi_sum+=fi[i];
	}
	for(int i=0;i<size;i++){
		*(fi_size+i)=(int)(*(fi+i)/fi_sum*Size);
		r -= *(fi_size+i);
		*(rest + i) = *(fi + i) / fi_sum*Size - *(fi_size + i);
	}
	sort(rest, index_rest, size);
	for (int i = Size-1; i > Size - r -1; i--) {
		fi_size[index_rest[i]] += 1;
	}
	int tempE[Size][2 * CodeL],kk=0;
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < fi_size[i]; j++) {
			for (int k = 0; k < 2 * CodeL; k++) {
				*(*(tempE + kk) + k) = *(*(E + index_fi[i]) + k);
			}
			kk++;
		}
	}
	for (int i = 0; i < Size; i++)
		for (int j = 0; j < 2 * CodeL; j++)
			*(*(E + i) + j) = *(*(tempE + i) + j);
	cb current_best = { *(fi_size + size - 1) ,fi[Size - 1] };
	return current_best;
}
//交叉算子
void crossOver(int(*E)[2 * CodeL], int size,int current_best) {
	double pc = 0.8;
	for (int i = 0; i < size- current_best; i += 2)
		if (pc > random(10) / 10.0 + 0.05) {
			for (int j = random(2 * CodeL); j < 2 * CodeL; j++) {
				int temp = 0;
				temp = *(*(E + i) + j);
				*(*(E + i) + j) = *(*(E + i + 1) + j);
				*(*(E + i + 1) + j) = temp;
			}
		}
}
//变异算子
void mutation(int(*E)[2 * CodeL], int size,int current_best) {
	double pc = 0.05;
	for (int i = 0; i < size- current_best; i++)
		for (int j = 0; j < 2 * CodeL; j++) {
			if (pc > random(1024) / 1024.0) {
				if (*(*(E + i) + j) == 1)
					*(*(E + i) + j) = 0;
				else
					*(*(E + i) + j) = 1;
			}
		}
}
//对适应度进行排序，适应度高的排在前面
void sort(double *f,int *index, int size) {
	for (int i=0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			double tempF = 0;
			int tempI = 0;
			if (f[j] > f[j + 1]) {
				tempF = f[j];
				f[j] = f[j + 1];
				f[j + 1] = tempF;
				tempI = index[j];
				index[j] = index[j + 1];
				index[j + 1] = tempI;
			}
		}
	}
}