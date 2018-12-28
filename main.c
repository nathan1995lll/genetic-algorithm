#include"function.h"
int main() {
	const int G = 300;
	FILE *fp;
	int err = fopen_s(&fp, "result.csv", "w");
	if (err == 1){
		printf("ERROR!\a");
		return 1;
	}
	int E[Size][2 * CodeL] = { 0 };
	init(E, Size);
	double fi[Size] = { 0 };
	cb current_best = { 0 };
	double test[20] = { 0 };
	for (int generation = 0; generation < G; generation++) {
		decode(E, fi, Size);
		current_best=selectAndReproduct(E, fi, Size);
		fprintf(fp, "%d,%f\n", generation + 1, current_best.fi);
		if (generation < 20)
			test[generation] = current_best.fi;
		else {
			for (int i = 0; i < 18; i++)
				test[i] = test[i + 1];
			test[19] = current_best.fi;
		}
		if (generation >= 20 && fabs(test[19] - test[0]) < 10e-6)
			break;
		crossOver(E, Size, current_best.current_best);
		mutation(E, Size, current_best.current_best);
	}
	return 0;
}