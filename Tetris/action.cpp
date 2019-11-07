#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "block.h"
/* draw */
extern void cleanBlock(Block block);
extern void drawBlock(Block block);
extern void addBlock(int **map, Block block);
/* check */
extern int checkCrash(int **map, Block *block);

int ch = 0;
int t = 50;

void getAction(){
    clock_t start, now;
    start = clock();
    

	while(1){
		if(_kbhit()){
			ch = _getch();
			break;
		}
		now = clock();
		int duration = (double)(now - start);
		if(duration > t)
			break;
	}
}

int _move(int **map, Block *block, int x, int y, int sign){
	// sign�� 1��ʾ�����ƶ��� 0��ʾ�����ƶ� 
	/* ������������block�Ŀ� */
	/* ���¶�λblock��λ�ã������µ�block */
	cleanBlock(*block);
	block->set(block->x + x, block->y + y, -1);
	if(checkCrash(map, block) == 1){
		block->set(block->x - x, block->y - y, -1);
		drawBlock(*block);
		if(sign == 1)
			addBlock(map, *block);
		return 1;
	}
	drawBlock(*block);
	return 0;
}

/* ������ת90�� */
void rotation(Block *block, int director){
	// ����ֻ��ת���Ͻ�3*3�ľ��󣬲�����director��ת90��

	/* ������ת */
	if(director == 0){
		/* ��ת�� */ 
		int value = block->shape[0][0];
		block->shape[0][0] = block->shape[0][2];
		block->shape[0][2] = block->shape[2][2];
		block->shape[2][2] = block->shape[2][0];
		block->shape[2][0] = value;
		/* ʮ��ת�� */
		value = block->shape[0][1];
		block->shape[0][1] = block->shape[1][2];
		block->shape[1][2] = block->shape[2][1];
		block->shape[2][1] = block->shape[1][0];
		block->shape[1][0] = value;
	}else if(director == 1){
		/* ��ת�� */ 
		int value = block->shape[0][0];
		block->shape[0][0] = block->shape[2][0]; 
		block->shape[2][0] = block->shape[2][2];
		block->shape[2][2] = block->shape[0][2];
		block->shape[0][2] = value;
		/* ʮ��ת�� */
		value = block->shape[0][1];
		block->shape[0][1] = block->shape[1][0];
		block->shape[1][0] = block->shape[2][1];
		block->shape[2][1] = block->shape[1][2];
		block->shape[1][2] = value;
	}

	/* ������ӵ�������� */
	if(block->type == 1){
		if(block->shape[1][3] == 1){
			block->shape[1][3] = 0;
			block->shape[3][1] = 1;
		}else{
			block->shape[1][3] = 1;
			block->shape[3][1] = 0;
		}
	}
}
void _transfer(int **map, Block *block, int sign){
	int director = block->director;
	cleanBlock(*block);	 // ������תǰ��block 
	switch(sign){
		case 0:
			rotation(block, director);
			// ��ת�������ײ���
			if(checkCrash(map, block) == 1){
				rotation(block, director^1);
			}
			break;
		case 1:
			rotation(block, director);
			block->director = block->director ^ 1;
			// ��ת�������ײ���
			if(checkCrash(map, block) == 1){
				rotation(block, director ^ 1);
				block->director = block->director ^ 1;
			}
			break;
	}
	
	drawBlock(*block);  // ���»�����ת���block 
}
/* ��ת */
void transfer(int **map, Block *block){

	int sign = block->type;
	/*
	sign�� ʲô���͵ķ��飬 ��ͬ���͵ķ������ת���Բ�ͬ 
	*/
	if(sign == 2 || sign == 3 || sign == 4){ // �����Ͻǵ���������ת 
		_transfer(map, block, 0);
	}else if(sign == 1 || sign == 6 || sign == 7){	// �������,Z
		_transfer(map, block, 1);
	}else if(sign == 0 || sign == 5){	// ����Ҫ����� 
//		_transfer(block, 2);
		return;
	}


}

int _action(int **map, Block *block, int c){
	int isButtom = 0;
	ch = c;
	if(ch == -1){
		getAction();
	}
	switch(ch){
		case 119:
			/* ��ת */
			transfer(map, block);
			break;
		case 115:
			/* ������ */ 
			isButtom = _move(map, block, 1, 0, 1); // ����Ƿ�Ӵ����˵ײ� 
			break;
		case 97:
			/* ������ */
			_move(map, block, 0, -1, 0);
			break;
		case 100:
			/* ������ */
			_move(map, block, 0, 1, 0);
			break;
	    case 224:                    //���������ASCII��
			switch(getch()){
		        case 72:
					/* ��ת */
					transfer(map, block);
		           break;
		        case 80:
					/* ������ */ 
					isButtom = _move(map, block, 1, 0, 1); // ����Ƿ�Ӵ����˵ײ� 
		            break;
		        case 75:    
					/* ������ */
					_move(map, block, 0, -1, 0);
		           break;
		         case 77:
					/* ������ */
					_move(map, block, 0, 1, 0);
		           break;   
		    }   
	}
	if(isButtom == 1){
		return 1;
	}
	return 0;
}
