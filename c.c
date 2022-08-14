#include <stdio.h>

void bubble(int m[3][3], int x, int y){
	int aux;
	for (int i = 0; i<x; i++){
		for(int j = 0; j<y; ++j){
			for (int k = 0; k<y; ++k){
				if (m[i][j] < m[i][k]){
					aux = m[i][j];
					m[i][j] = m[i][k];
					m[i][k] = aux;
				}
			}
		}
	}
}

int main(){
int ma[3][3] = {
	{3, 2, 1},
	{1, 3, 2},
	{3, 1, 2}
	};
	bubble(ma, 3, 3);
	for (int i = 0; i<3; ++i){
		for (int j=0; j<3; ++j){
			printf("%d ", ma[i][j]);
		}
		printf("\n");
	}

}
