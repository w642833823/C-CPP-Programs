#include<stdio.h>
#include<graphics.h>	//ͼ�ο�ͷ�ļ�
#include<mmsystem.h>	//��������ͷ�ļ�
#include<math.h>

#pragma comment(lib, "winmm.lib")	//�������ֿ��ļ�

int flag = 0;	//��ʾ�������
int board[20][20] = { 0 };	//0��ʾ����û������״̬

void initGame();
int judge(int a, int b);
void playChess();

int main() {

	initGame();
	playChess();

	getchar();
	return 0;
}

//1.��������
void initGame() {		//��ʼ����Ϸ

	//1.1 ��ͼ���� �⺯��
	//Ĭ�ϵ���ϵͳ�Ĵ���
	initgraph(600, 500);	//�����Զ��崰��
	//setbkcolor(BLUE);		//���ô��ڱ�����ɫ
	//cleardevice();			//ˢ��

	//1.2 ��ͼ
	loadimage(NULL, "./src/bg.jpg");

	//1.3 ��������	mci ��ý����ƽ��
	mciSendString("open ./src/skyCity.mp3", 0, 0, 0);
	//mciSendString("play ./src/skyCity.mp3", 0, 0, 0);

	//setlinecolor(BLACK);
	//1.4 ��������
	//���� 20 20 25 25 500 500
	for (int i = 0; i <= 500; i += 25) {
		line(0, i, 500, i);
		line(i, 0, i, 500);
	}
	line(501, 0, 501, 500);

	//1.5 print out
	outtextxy(510, 100, "���1������");
	outtextxy(510, 200, "���2������");
}

//2.����
void playChess() {
	//���
	MOUSEMSG m;	//���������Ϣ
	int x=0, y=0;	//����
	int a=0, b=0;	//����

	//��������
	while (1) {
		m = GetMouseMsg();	//��ȡһ�������Ϣ

		//��ȡ���������ĵ��������Ϣ
		for (int i = 1; i < 20; i++) {
			for (int j = 1; j < 20; j++) {
				if (abs(m.x - i * 25) < 12 && abs(m.y - j * 25) < 12) {
					x = i * 25;
					y = j * 25;
					a = i;
					b = j;
				}
			}
		}


		if (m.uMsg == WM_LBUTTONDOWN) {
			//�����ظ�����һ��λ����
			if (board[a][b] != 0) {
				MessageBox(NULL, "�����Ѿ��������ˣ�������ѡ��", "��ʾ", MB_OK);	//����һ����ʾ��
				continue;	//������һѭ��
			}

			//�жϺڰ���
			if (flag % 2 == 0) {	//	ż���� ����
				setfillcolor(BLACK);
				solidcircle(x, y, 10);
				board[a][b] = 1;
			}
			else {	//������
				setfillcolor(WHITE);
				solidcircle(x, y, 10);
				board[a][b] = 2;
			}
			flag++;
		}

		if (judge(a, b)) {
			if (flag % 2 == 0) {
				MessageBox(NULL, "���2ʤ����", "��Ϸ����", MB_OK);	//����һ����ʾ��
				exit(0);
			}
			else {
				MessageBox(NULL, "���1ʤ����", "��Ϸ����", MB_OK);	//����һ����ʾ��
				exit(0);
			}
		}
	}
}


//3.�ж���Ӯ
int judge(int a, int b) {
	int i, j;
	int t = 2 - flag % 2;	//1 �жϺ����Ƿ�Ӯ	2 �жϰ����Ƿ�Ӯ

	//����
	for (i = a - 4, j = b; i <= a; i++) {
		if (i > 0 && i < 16 && t == board[i][j] && t == board[i + 1][j] && t == board[i + 2][j] && t == board[i + 3][j] && t == board[i + 4][j]) {
			return 1;
		}
	}

	//����
	for (i = a, j = b - 4; j <= b; j++) {
		if (j > 0 && j < 16 && t == board[i][j] && t == board[i][j + 1] && t == board[i][j + 2] && t == board[i][j + 3] && t == board[i][j + 4]) {
			return 1;
		}
	}

	//����
	for (i = a - 4, j = b - 4; i <= a, j <= b; i++, j++) {
		if (i > 0 && i < 16 && j > 0 && j < 16 && t == board[i][j] && t == board[i + 1][j + 1] && t == board[i + 2][j + 2] && t == board[i + 3][j + 3] && t == board[i + 4][j + 4]) {
			return 1;
		}
	}

	//����
	for (i = a - 4, j = b + 4; i <= a, j >= b; i++, j--) {
		if (i > 0 && i < 16 && j > 0 && j < 16 && t == board[i][j] && t == board[i + 1][j - 1] && t == board[i + 2][j - 2] && t == board[i + 3][j - 3] && t == board[i + 4][j - 4]) {
			return 1;
		}
	}

	return 0;
}