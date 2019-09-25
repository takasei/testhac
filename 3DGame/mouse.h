//=============================================================================
//
// �}�E�X���� [mouse.h]
// Author : Kanan Naganawa
//
//=============================================================================
#ifndef _MOUSE_H_
#define _MOUSE_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	DIMOUSESTATE2 mouseState;
	float posX;
	float posY;
} MOUSE;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);
void UpdateMouse(void);
void UninitMouse(void);
bool GetMousePress(int nButton);
bool GetMousePressTrigger(int nButton);
LONG GetMouseX(void);
LONG GetMouseY(void);

#endif
