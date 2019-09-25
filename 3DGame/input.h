//=============================================================================
//
// ���͏��� [input.h]
// Author : masayasu wakita
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetTriggerKeyboard(int nKey);
bool GetUpKeyboard(int nKey);
bool GetKeyboardPress(int nKey);
#endif
