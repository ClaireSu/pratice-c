#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <time.h>
#include <windows.h>//����̨�����Ҫͷ�ļ�
#include "block.h"
using namespace std;
void pos(int x,int y);//ȷ�����λ��
HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��׼������

/*������*/
int height = 0;
int width = 0;
int promptH = 8;
int promptW = 8; 
void drawInit(int h, int w){
	height = h;
	width = w;
}

//���ù��λ��
void pos(int x,int y){
    COORD posPoint = {x * 2, y}; //��������
    SetConsoleCursorPosition(hOut,posPoint);
}

//	ǽ�壬����
//   �ա�
void initMap(int **map){
	// ������һ����Ҫ��ע�ĵط��� �Ǿ��Ǳ߽���ǽ����ô��ʱ�����ж���ʱ�� 
	// ����Ҫ��ǽ��Ĵ�С�����������ͼ��С�У�Ҳ����height�ǰ�����ǽ���˵� 
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			if(i == height - 1){
				map[i][j] = 1; 
			}else if(j == 0 || j == width - 1){
				map[i][j] = 1; 
			}else{
				map[i][j] = 0; 
			}
		}
	} 
	return;
}

void drawMap(int **map){
	// ������һ����Ҫ��ע�ĵط��� �Ǿ��Ǳ߽���ǽ����ô��ʱ�����ж���ʱ�� 
	// ����Ҫ��ǽ��Ĵ�С�����������ͼ��С�У�Ҳ����height�ǰ�����ǽ���˵� 

	/* �����Ļ */
//	system("cls");
	pos(0, 0);
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			if(map[i][j] == 1){
				cout << "��";	// ǽ�� 
			}else{
				cout << "��"; 	// ���ƶ����� 
			}
		}
		cout << endl;
	} 
	return;
}

void drawBlock(Block block){
	int x = block.x;
	int y = block.y;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			pos(y + j, x + i);
			if(block.shape[i][j] == 1 && x + i >= 0 && x + i < height - 1 && y + j < width - 1 && y + j > 0){
				std::cout << "��";
			}
		}
	}
	pos(0,height);
}

void cleanBlock(Block block){
	int x = block.x;
	int y = block.y;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			pos(y + j, x + i);
			if(block.shape[i][j] == 1 && x + i >= 0 && x + i < height - 1 && y + j < width - 1 && y + j > 0){
				std::cout << "��";
			}
		}
	}
	pos(0,height);
} 

void addBlock(int **map, Block block){
	int x = block.x;
	int y = block.y;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(block.shape[i][j] == 1 && x + i >= 0 && x + i < height - 1 && y + j < width - 1 && y + j > 0){
				map[x+i][y+j] = block.shape[i][j];
			}
		}
	}
}

void cleanLine(int **map){
	drawMap(map);
	pos(0,height);
}

void drawPrompt(){
	/* ������ʾ����ʾ��һ���������״ */
	/**
		1. Ϊ�˷�����������������ʾ�Ĵ�Сֱ�ӹ̶������������Ҫ�޸ĵ�������һ���ֵĲ���Ҳ�Ǹ���չ��ϸ���ĵط��� 
		2. ��ʾ���ַ������Ͻ���� 
	**/ 
	int promptH = 8;
	int promptW = 8; 
	pos(width, 0);
	for(int i = 0; i < promptH; i++){
		for(int j = 0; j < promptW; j++){
			pos(width + j, i);
			if(i == promptH - 1 || i == 0){
				std::cout << "��";
			}else if(j == 0 || j == promptW - 1){
				std::cout << "��";
			}
		}
	} 
	pos(0,height);
} 

void _drawPrompt(Block block){
	/* ������ʾ����ʾ��һ���������״ */
	/**
		1. Ϊ�˷�����������������ʾ�Ĵ�Сֱ�ӹ̶������������Ҫ�޸ĵ�������һ���ֵĲ���Ҳ�Ǹ���չ��ϸ���ĵط��� 
		2. ��ʾ���ַ������Ͻ���� 
	**/ 
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			pos(width + 2 + j, 3 + i);
			if(block.shape[i][j] == 1){
				std::cout << "��";
			}else{
				std::cout << "  ";
			}
		}
	}
	pos(0,height);
} 

void _drawNumber(int points[5][3], int x, int y){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 3; j++){
		    COORD posPoint = {2 * y + j, x + i}; //��������
		    SetConsoleCursorPosition(hOut,posPoint);
			if(points[i][j] == 1){
				cout << "+";
			}else{
				cout << " ";
			} 

		}
	}
	pos(0, height);
}

void drawNumber(int number, int x, int y){
	if(number == 0){
		int points[5][3] = {
				{1, 1, 1},
				{1, 0, 1},
				{1, 0, 1},
				{1, 0, 1},
				{1, 1, 1}
			};
		_drawNumber(points, x, y);
	}else if(number == 1){
		int points[5][3] = {
				{0, 0, 1},
				{0, 0, 1},
				{0, 0, 1},
				{0, 0, 1},
				{0, 0, 1}
			};
		_drawNumber(points, x, y);
	}else if(number == 2){
		int points[5][3] = {
			{1, 1, 1},
			{0, 0, 1},
			{1, 1, 1},
			{1, 0, 0},
			{1, 1, 1}
		};
		_drawNumber(points, x, y);
	}else if(number == 3){
		int points[5][3] = {
			{1, 1, 1},
			{0, 0, 1},
			{1, 1, 1},
			{0, 0, 1},
			{1, 1, 1}
		};
		_drawNumber(points, x, y);
	}else if(number == 4){
		int points[5][3] = {
			{1, 0, 1},
			{1, 0, 1},
			{1, 1, 1},
			{0, 0, 1},
			{0, 0, 1}
		};
		_drawNumber(points, x, y);
	}else if(number == 5){
		int points[5][3] = {
			{1, 1, 1},
			{1, 0, 0},
			{1, 1, 1},
			{0, 0, 1},
			{1, 1, 1}
		};
		_drawNumber(points, x, y);
	}else if(number == 6){
		int points[5][3] = {
			{1, 1, 1},
			{1, 0, 0},
			{1, 1, 1},
			{1, 0, 1},
			{1, 1, 1}
		};
		_drawNumber(points, x, y);
	}else if(number == 7){
		int points[5][3] = {
			{1, 1, 1},
			{0, 0, 1},
			{0, 0, 1},
			{0, 0, 1},
			{0, 0, 1}
		};
		_drawNumber(points, x, y);
	}else if(number == 8){
		int points[5][3] = {
			{1, 1, 1},
			{1, 0, 1},
			{1, 1, 1},
			{1, 0, 1},
			{1, 1, 1}
		};
		_drawNumber(points, x, y);
	}else if(number == 9){
		int points[5][3] = {
			{1, 1, 1},
			{1, 0, 1},
			{1, 1, 1},
			{0, 0, 1},
			{1, 1, 1}
		};
		_drawNumber(points, x, y);
	}
	return;
}

void drawScore(int score){
	/* չʾ�ѻ�õķ��� */
	drawNumber(score % 10, promptH + 1, width + 6);
	score = score / 10;
	drawNumber(score % 10, promptH + 1, width + 3);
	score = score / 10;
	drawNumber(score % 10, promptH + 1, width + 0);

//	pos(width + 2, promptH + 2);
//	cout << score;
//	pos(0,height);
} 
