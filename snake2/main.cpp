#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<windows.h>
#define random(x) (rand()%x)

using namespace std;

struct snake{	
	int i;
	int j;
	struct snake *next;
	};
	
/* draw */
extern void initMap(int **map, int height, int weight);
extern void draw(int **map, int *star, int height, int weight);
extern void drawSnake(int **map, struct snake snake);
extern void update(int x, int y, int sign);
extern void pos(int x,int y);
/* action */
extern void getAction();
extern int move(struct snake *s, int *star);
extern void initAction(int x, int y, int h, int w, int c, int s); 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct snake generateSnake(){
	cout << "��ʼ����" << endl; 
	struct snake *s;
	s = (struct snake*)malloc(sizeof(struct snake));
	struct snake *p = s;
	int x[6] = {2, 3, 4, 5, 5, 5};
	int y[6] = {2, 2, 2, 2, 3, 4};
	for(int i = 0; i < 6; i++){
		struct snake *node;
		node = (struct snake*)malloc(sizeof(struct snake));
		p->next = node;		
		p = p->next;
		p->i = x[i];
		p->j = y[i];
	}
	p->next = NULL;
	cout << "���ɳɹ�" << endl; 
	return *s;
}

/* �������� */
void generateStar(int **map, int *star, int height, int weight){
	int sum = 0;
	int index = 0;
	// �����ж��ٿո� 
	for(int i = 0; i < height; i++)
		for(int j = 0; j < weight; j++)
			if(map[i][j] == 0)
				sum += 1;
	// ������ɿո��±� 
	index = random(sum) + 1;
	// ѡ��index���ո���Ϊ���ǵ�����λ�� 
	for(int i = 0; i < height; i++)
		for(int j = 0; j < weight; j++){
			if(map[i][j] == 0)
				index -= 1;
				
			if(index == 0){
				star[0] = i;
				star[1] = j;
				return;
			}
		}
	return;
}

int _move(struct snake *s, int *star){
	int result = move(s, star);
	return result; 
} 

int main(int argc, char** argv) {

	/* ������ */
	int height = 15;
	int weight = 15;
	int speed = 200;	// �˶��ٶȣ�ԽСԽ�죨��ʵ����ʱʱ���� 
	/* ���Ƴ�ʼ��ͼ */
	int **map;
	map = (int**) new int*[height];
	/* ��ʼ����ͼ */
	for(int i = 0; i < height; i++){
		*(map + i) = new int[weight];
	}
	
	while(1){
		/* ������ */
		struct snake s = generateSnake();
		initMap(map, height, weight);
		drawSnake(map, s);
		/* �������� */ 
		int star[2] = {0, 0};
		generateStar(map, star, height, weight);
		/* ���Ƶ�ͼ */
		draw(map, star, height, weight);
		/* ��ʼ���˶����������᷽�򣬺��᷽�򣬵�ͼ�߶ȣ���ͼ���, ���򰴼�ֵ, �˶��ٶȣ�ԽСԽ�죩 */
		initAction(0, 0, height, weight, 0, speed);
		while(1){
			getAction();
			int result = _move(&s, star);
			
			if(result == 0) //������ˣ��Ǿ����н��� 
				break;
			
			// ��Ҫ���µ�����֮ǰ�Ƚ����߻��Ƶ���ͼ��ȥ����Ȼ�ᵼ���ڸճ������ǵ�λ���������� 
			initMap(map, height, weight);	
			drawSnake(map, s);
			
			if(result == 2) {// ���Ǳ��Ե��ˣ� ���������µ����� 
				generateStar(map, star, height, weight);
				update(star[1], star[0], 2); 
			}
		}
		pos(0, height);
		printf("������\n");
		system("pause");
	}

	return 0;
}
