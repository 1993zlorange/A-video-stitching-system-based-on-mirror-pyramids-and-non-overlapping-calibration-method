#include "matrix.h"
#include "math.h"
#include "stdlib.h"
#include <iostream>


void matrix_mul(float matrixA[3][3], float matrixB[3][3], float matrixC[3][3])
	{
		//�����������(l*m�����m*n����,���Ϊl*n����)
		//����ǰ��������Ϊ�������õ��Ľ������ڵ�����������
		int i,j,k;
		for(i=0;i<3;i++)
			for(j=0;j<3;j++)
				matrixC[i][j]=0.0f;//��matrixC��ʼ������
		for(i=0;i<3;i++)
			for(j=0;j<3;j++)
				for(k=0;k<3;k++)
					matrixC[i][j]+=matrixA[i][k]*matrixB[k][j];
	}
void matrix_mul(float matrixA[3][1], float matrixB[1][3], float matrixC[3][3])
{
	//�����������(l*m�����m*n����,���Ϊl*n����)
	//����ǰ��������Ϊ�������õ��Ľ������ڵ�����������
	int i, j, k;
	for (i = 0; i<3; i++)
	for (j = 0; j<3; j++)
		matrixC[i][j] = 0;//��matrixC��ʼ������
	for (i = 0; i<3; i++)
	for (j = 0; j<3; j++)
	for (k = 0; k<1; k++)
		matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
}
void matrix_mul(float matrixA[3][3], float matrixB[3][1], float matrixC[3])
{
	//�����������(l*m�����m*n����,���Ϊl*n����)
	//����ǰ��������Ϊ�������õ��Ľ������ڵ�����������
	int i, j, k;
	for (i = 0; i<3; i++)

		matrixC[i] = 0;//��matrixC��ʼ������
	for (i = 0; i<3; i++)
	for (j = 0; j<1; j++)
	for (k = 0; k<3; k++)
		matrixC[i] += matrixA[i][k] * matrixB[k][j];
}
