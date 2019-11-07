#include <stdio.h>
#include <iostream>

	
class Block // class declaration
{

	
	public:
		int x; // �����꣬�����Ͻ�Ϊ��־λ 
		int y; // �����꣬�����Ͻ�Ϊ��־λ 
		int type; // �������� 
		int director; // ��ת���� 0:����1���� 
		int shape[4][4]; // ���Ӵ�С 
		int shapes[8][4][4]; 
	public:
		/* ���÷������� */ 
		void set(int _x, int _y, int _shape){
			x = _x;
			y = _y;
			if(_shape != -1){
				for(int i = 0; i < 4; i++)
					for(int j = 0; j < 4; j++)
						shape[i][j] = shapes[_shape][i][j];	
				type = _shape;
				director = 0;
			}
	
		}
		void generate(){
			for(int i = 0; i < 8; i++)
				for(int j = 0; j < 4; j++)
					for(int k = 0; k < 4; k++)
						shapes[i][j][k] = 0;
						
			/* ʯͷ */
			shapes[0][1][1] = 1;
			/* ���� */
			shapes[1][1][0] = shapes[1][1][1] = shapes[1][1][2] = shapes[1][1][3] = 1;
			/* �� (��*/
			shapes[2][0][0] = shapes[2][0][1] = shapes[2][1][1] = shapes[2][2][1] = 1;
			/* �� (��) */
			shapes[3][0][1] = shapes[3][0][2] = shapes[3][1][1] = shapes[3][2][1] = 1;
			/* ͹ */ 
			shapes[4][0][1] = shapes[4][1][0] = shapes[4][1][1] = shapes[4][2][1] = 1;
			/* �� */
			shapes[5][1][1] = shapes[5][1][2] = shapes[5][2][1] = shapes[5][2][2] = 1;
			/* Z(��) */
			shapes[6][0][0] = shapes[6][0][1] = shapes[6][1][1] = shapes[6][1][2] = 1;
			/* Z(��)*/
			shapes[7][0][2] = shapes[7][0][1] = shapes[7][1][1] = shapes[7][1][0] = 1;
			
		}
 }; 
