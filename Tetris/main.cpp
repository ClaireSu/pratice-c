#include <bits/stdc++.h>//C++����ͷ
#include <windows.h>//����̨�����Ҫͷ�ļ�
#include <conio.h>//getch()����
#include <stdlib.h>//system()����
#include <time.h>
#include "block.h"
#define random(x) (rand()%x)

/* draw */
extern void drawInit(int h, int w);
extern void initMap(int **map);
extern void drawMap(int **map);
extern void drawBlock(Block block);
extern void pos(int x, int y);
extern void cleanLine(int **map); 
extern void drawPrompt();
extern void _drawPrompt(Block block);
extern void drawScore(int score);

/* action */
extern int _action(int **map, Block *block, int c);

/* check */
extern int checkLine(int **map, int height, int width);
extern int checkCrash(int **map, Block *block);

int main()
{
	/* ������ */
	int height = 24;
	int width = 15;
	int speed = 750;
	int score = 0;
	/* ���Ƴ�ʼ��ͼ */
	int **map;
	map = (int**) new int*[height];
	/* ��ʼ����ͼ */
	for(int i = 0; i < height; i++){
		*(map + i) = new int[width];
	}
	
	drawInit(height, width);
	initMap(map);
	drawMap(map);
	drawPrompt();

	/* ���Ʒ��� */
	int index = random(8);
	Block block;
	block.generate();
	block.set(2, 2, index);
	drawBlock(block);
	drawScore(score);
	
	/* ��һ������ */
	index = random(8);
	Block nextBlock;
	nextBlock.generate();
	nextBlock.set(2, 2, index);
	_drawPrompt(nextBlock);
	
	clock_t start, end;
	while(1){
	    start = clock();
	    end = clock();
	    
	    while(end - start < speed){
			if(_action(map, &block, -1) == 1){
				while(checkLine(map, height, width) == 1){
					cleanLine(map);
					score += random(10);
					drawScore(score);
				}

				index = random(8);
				block.set(2, 2, nextBlock.type);
				drawBlock(block);
				nextBlock.set(2, 2, index);
				_drawPrompt(nextBlock);

				// �������
				if(checkCrash(map, &block) == 1){
					break;
				} 
			}
			end = clock();
		}
		// �������
		if(checkCrash(map, &block) == 1){
			break;
		} 
		if(_action(map, &block, 115) == 1){
			while(checkLine(map, height, width) == 1){
				cleanLine(map);
				score += random(10);
				drawScore(score);
			}
			index = random(8);
			block.set(2, 2, nextBlock.type);
			drawBlock(block);
			nextBlock.set(2, 2, index);
			_drawPrompt(nextBlock);

			// �������
			if(checkCrash(map, &block) == 1){
				break;
			} 
		}
//		std::cout << score << std::endl;
	}
	while(1){
		
	}
//	std::cout << "������" << std::endl;
	 
}

