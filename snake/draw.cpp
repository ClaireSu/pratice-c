#include<stdio.h>
#include<stdlib.h> 
#include<iostream>
using namespace std;

struct snake{	
	int i;
	int j;
	struct snake *next;
	};


//	ǽ�壬����
//   �ա�
void initMap(int **map, int height, int weight){

	// ������һ����Ҫ��ע�ĵط��� �Ǿ��Ǳ߽���ǽ����ô��ʱ�����ж���ʱ�� 
	// ����Ҫ��ǽ��Ĵ�С�����������ͼ��С�У�Ҳ����height�ǰ�����ǽ���˵� 
	for(int i = 0; i < height; i++){
		for(int j = 0; j < weight; j++){
			if(i == 0 || i == height - 1){
				map[i][j] = 1; 
			}else if(j == 0 || j == weight - 1){
				map[i][j] = 1; 
			}else{
				map[i][j] = 0; 
			}
		}
	} 
	return;
}
void draw(int **map, int *star, int height, int weight){
	// ������һ����Ҫ��ע�ĵط��� �Ǿ��Ǳ߽���ǽ����ô��ʱ�����ж���ʱ�� 
	// ����Ҫ��ǽ��Ĵ�С�����������ͼ��С�У�Ҳ����height�ǰ�����ǽ���˵� 

	/* �����Ļ */
	system("cls");
	for(int i = 0; i < height; i++){
		for(int j = 0; j < weight; j++){
			if(map[i][j] == 1){
				cout << "��";	// �����ǽ�� 
			}else if(map[i][j] == 2){
				cout << "��";	// ���� 
			}else if(i == star[0] && j == star[1]){
				cout << "��";	// ���� 
			}else{
				cout << "��"; 	// ���ƶ����� 
			}
		}
		cout << endl;
	} 
	return;
}

void drawSnake(int **map, struct snake snake){
	struct snake *p = snake.next;
	map[p->i][p->j] = 2;	// ��ͷ
	p = p->next;
	while(p){
		map[p->i][p->j] = 1;
		p = p->next;
	}
	return;
}
