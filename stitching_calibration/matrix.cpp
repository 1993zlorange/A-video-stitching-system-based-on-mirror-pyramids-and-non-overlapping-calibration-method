#include "matrix.h"
#include "math.h"
#include "stdlib.h"
#include <iostream>


void matrix_mul(float matrixA[3][3], float matrixB[3][3], float matrixC[3][3])
	{
		//两个矩阵相乘(l*m矩阵和m*n矩阵,结果为l*n矩阵)
		//其中前两个矩阵为乘数，得到的结果存放在第三个矩阵中
		int i,j,k;
		for(i=0;i<3;i++)
			for(j=0;j<3;j++)
				matrixC[i][j]=0.0f;//对matrixC初始化置零
		for(i=0;i<3;i++)
			for(j=0;j<3;j++)
				for(k=0;k<3;k++)
					matrixC[i][j]+=matrixA[i][k]*matrixB[k][j];
	}
void matrix_mul(float matrixA[3][1], float matrixB[1][3], float matrixC[3][3])
{
	//两个矩阵相乘(l*m矩阵和m*n矩阵,结果为l*n矩阵)
	//其中前两个矩阵为乘数，得到的结果存放在第三个矩阵中
	int i, j, k;
	for (i = 0; i<3; i++)
	for (j = 0; j<3; j++)
		matrixC[i][j] = 0;//对matrixC初始化置零
	for (i = 0; i<3; i++)
	for (j = 0; j<3; j++)
	for (k = 0; k<1; k++)
		matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
}
void matrix_mul(float matrixA[3][3], float matrixB[3][1], float matrixC[3])
{
	//两个矩阵相乘(l*m矩阵和m*n矩阵,结果为l*n矩阵)
	//其中前两个矩阵为乘数，得到的结果存放在第三个矩阵中
	int i, j, k;
	for (i = 0; i<3; i++)

		matrixC[i] = 0;//对matrixC初始化置零
	for (i = 0; i<3; i++)
	for (j = 0; j<1; j++)
	for (k = 0; k<3; k++)
		matrixC[i] += matrixA[i][k] * matrixB[k][j];
}
