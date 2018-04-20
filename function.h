#pragma once
#include <DxLib.h>
#include <math.h>
#include "define.h"

#define PI 3.141592653589793


//�펞

void DrawBrush() {
	DrawGraph(mX - 10, mY - 110, brush, TRUE);
}

void Draw() {
	DrawBox(0, 0, 1280, 720, 0xffffff, TRUE); //���w�i
}

void Error() {
	DrawBox(460, 320, 840, 400, 0xff0000, TRUE);
	DrawFormatStringToHandle(464, 328, 0xffffff, Cica32, "�G���[���������܂����B\n�������Ă�ł��������B");
}


//OP,Pause,ED

void OP() {
	DrawFormatStringToHandle(544, 344, 0x000000, azukiLB32, "���[�Ղɂ�");
	DrawFormatStringToHandle(440, 400, 0x000000, azukiLB24, "SPACE�L�[�������ăX�^�[�g");
	if (key[KEY_INPUT_SPACE] == 1)	gamemode = 1;

}

void Pause() {
	DrawFormatStringToHandle(544, 344, 0x000000, azukiLB32, "�ہ[�����߂�");
	if (key[KEY_INPUT_SPACE] == 1)	gamemode = 1;
	if (key[KEY_INPUT_RETURN] == 1)	gamemode = 0;
}

void ED() {

}


//Game


void Control() {
	if (!moveFlag) {
		if (key[KEY_INPUT_A] == 1)		course--;
		else if (key[KEY_INPUT_D] == 1)	course++;

		else if (key[KEY_INPUT_S] == 1) power--;
		else if (key[KEY_INPUT_W] == 1) power++;
	}

	switch (course) {
	case 4:
		course = 3;
		break;
	case -4:
		course = -3;
		break;
	}
	switch (power) {
	case 6:
		power = 5;
		break;
	case 0:
		power = 1;
		break;
	}
}

void DrawControl() {

}

void DrawStone() {
	for (int i = 0; i < 4; i++)	DrawGraph((int)yellowStone[i].x - 31, (int)yellowStone[i].y - 32, stone_yellow, TRUE);
	for (int i = 0; i < 4; i++)	DrawGraph((int)redStone[i].x - 31, (int)redStone[i].y - 32, stone_red, TRUE);
}

void Game() {
	switch (course) {
	case -3:
		sX = 60;
		sY = 520;
		xBevel = -3;
		yBevel = 10.5;
		break;
	case -2:
		sX = 100;
		sY = 530;
		xBevel = -2;
		yBevel = 10.75;
		break;
	case -1:
		sX = 140;
		sY = 540;
		xBevel = -1;
		yBevel = 11;
		break;
	case 0:
		sX = 180;
		sY = 540;
		xBevel = 0;
		yBevel = 8;
		break;
	case 1:
		sX = 220;
		sY = 540;
		xBevel = 1;
		yBevel = 11;
		break;
	case 2:
		sX = 260;
		sY = 530;
		xBevel = 2;
		yBevel = 10.75;
		break;
	case 3:
		sX = 300;
		sY = 520;
		xBevel = 3;
		yBevel = 10.5;
		break;

	}
	sX += 480;
	if (key[KEY_INPUT_ESCAPE] == 1)	gamemode = 2;
}

void DrawGame() {
	DrawGraph(481, 0, sheet, FALSE);
}

void MoveOverStone() {
	for (int i = 0; i < 4; i++) {
		if (yellowStone[i].y > 740) {
			yellowStone[i].x = yellowStoneDefault[i].x;
			yellowStone[i].y = yellowStoneDefault[i].y;
			setFlag = false;
			moveFlag = false;
			nowStonePos = 0;
		}
	}
}


//Debug

void DrawInfo() {
	DrawFormatStringToHandle(0, 20, 0x000000, Cica16, "course:%d,power:%d\nspeed:%f,nowStonePos:%f\nsetFlag:%s,moveFlag:%s", course, power, speed, nowStonePos, setFlag?"true":"false", moveFlag?"true":"false");
}

void DrawMousePos() {
	DrawFormatStringToHandle(0, 0, 0x000000, Cica16, "X: %d Y: %d", mX, mY);
}

void DrawShootLine() {
	DrawLineAA((float)660, (float)100, (float)sX, (float)sY, 0x000000, (float)4);
}

void DrawShootLineRad() {
	DrawLineAA((float)660, (float)100, (float)660 + (float)sin(Rad(course * 5)) * (float)300, (float)100 + (float)cos(Rad(course * 5)) * (float)300, 0xff0000, 4);
}

void MoveStoneD() {
	if (key[KEY_INPUT_Y] == 1) {
		yellowStone[0].x = 660;
		yellowStone[0].y = 100;
		setFlag = true;
	}
	if (key[KEY_INPUT_U] == 1 && setFlag) {
		moveFlag = true;
		speed = (double)power / 1.25;
		stoneMoveTime = cnt;
	}
	
	if (moveFlag) {
		nowStonePos += speed;
		yellowStone[0].x = 660 + sin(Rad(course * 5)) * nowStonePos;
		yellowStone[0].y = 100 + cos(Rad(course * 5)) * nowStonePos;
	}
	
	if (cnt % 20 == 0 && moveFlag) {
		speed *= 0.9;
	}

	if (speed < 0.2 && cnt - stoneMoveTime > 60) {
		moveFlag = false;
		nowStonePos = 0;
		speed = 0;
	}
}

double Rad(int deg) {
	return (double)deg * PI / 180;
}