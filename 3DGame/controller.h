//=============================================================================
//
// DirectX �R���g���[���[�����@[controller.h]
// Author : YUUJI AIDA
//
//=============================================================================
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �L�[�̎��
//=============================================================================
typedef enum
{
	JOYPADKEY_X = 0,				//[0]�@X�{�^��
	JOYPADKEY_Y,					//[1]�@Y�{�^��
	JOYPADKEY_A,					//[2]�@A�{�^��
	JOYPADKEY_B,					//[3]�@B�{�^��
	JOYPADKEY_LEFT_SHOULDER,		//[4]�@����O�{�^��
	JOYPADKEY_RIGHT_SHOULDER,		//[5]�@�E��O�{�^��
	JOYPADKEY_LEFT_TRIGGER,			//[6]�@���{�^��
	JOYPADKEY_RIGHT_TRIGGER,		//[7]�@�E�{�^��
	JOYPADKEY_LEFT_THUMB,			//[8]�@�E�X�e�B�b�N�{�^��
	JOYPADKEY_RIGHT_THUMB,			//[9]�@���X�e�B�b�N�{�^��
	JOYPADKEY_BACK,					//[10]�@�o�b�N�{�^��
	JOYPADKEY_START,				//[11]�@�X�^�[�g�{�^��

	JOYPADKEY_LEFT,					//[12]�@�����L�[[��]
	JOYPADKEY_RIGHT,				//[13]�@�����L�[[�E]
	JOYPADKEY_UP,					//[14]�@�����L�[[��]
	JOYPADKEY_DOWN,					//[15]�@�����L�[[��]
	JOYPADKEY_MAX					
}JOYPADKEY;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT InitController(HINSTANCE hInstance, HWND hWnd);
void UninitController(void);
void UpdateController(void);

bool GetControllerPress(int nIDPad, JOYPADKEY nKey);
bool GetControllerTrigger(int nIDPad, JOYPADKEY nKey);
bool GetControllerRelease(int nIDPad, JOYPADKEY nKey);
bool GetControllerRepeat(int nIDPad, JOYPADKEY nKey);

int GetJoypadTriggerLeft(int nIDPad);
int GetJoypadTriggerRight(int nIDPad);

void GetJoypadStickLeft(int nIDPad, float *pValueH, float *pValueV);
void GetJoypadStickRight(int nIDPad, float *pValueH, float *pValueV);

static BOOL CALLBACK EnumJoyCallbackJoypad(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);
static BOOL CALLBACK EnumAxesCallbackJoypad(const LPCDIDEVICEOBJECTINSTANCE lpddi, LPVOID pvRef);
void SetKeyStateJoypad(int nIDPad);

#endif
