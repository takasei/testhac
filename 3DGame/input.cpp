//=============================================================================
//
// ���͏��� [input.cpp]
// Author : masayasu wakita
//
//=============================================================================
#include "input.h"
//#include <atlstr.h> 

//=============================================================================
// �}�N����`
//=============================================================================
#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECTINPUT8 g_pInput = NULL;				//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;	//���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];				//�L�[�{�[�h�̓��͏�񃏁[�N
BYTE g_akeyStateTrigger[NUM_KEY_MAX];		//�e��1������
BYTE g_akeyStateUp[NUM_KEY_MAX];		//�e��1������(������)
//BYTE g_aXInputTrigger[NUM_KEY_MAX];			//�R���g���[���[��1������
BYTE g_akeyStateRelese[NUM_KEY_MAX];		//�e�̗��߂���
BYTE g_akeyStateRepeat[NUM_KEY_MAX];		//�e�̍ĘA��
//XINPUT_STATE g_pState;						//XInput�R���g���[���[
//XINPUT_KEYSTROKE g_pKeystroke;

//=============================================================================
// �L�[�{�[�h�̏�����
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̍쐬
	if (FAILED(DirectInput8Create(hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&g_pInput,NULL)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X�i�L�[�{�[�h�j�̍쐬
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void UninitKeyboard(void)
{
	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();			//�L�[�{�[�h�ւ̃A�N�Z�X�����J��
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}
	
	// DirectInput�I�u�W�F�N�g�̊J��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];				//�L�[�{�[�h�̓��͏��
	int nCntKey;

	// �f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_akeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] & aKeyState[nCntKey]) ^ aKeyState[nCntKey];
			g_akeyStateUp[nCntKey] = g_aKeyState[nCntKey] ^ (g_aKeyState[nCntKey] & aKeyState[nCntKey]);

			g_aKeyState[nCntKey] = aKeyState[nCntKey];	//�L�[�v���X���ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();				//�L�[�{�[�h�ւ̃A�N�Z�X�����擾
	}
}

//=============================================================================
// �L�[�{�[�h�̃g���K�[��Ԃ��擾
//=============================================================================
bool GetTriggerKeyboard(int nKey)
{
	return(g_akeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̃g���K�[��Ԃ��擾
//=============================================================================
bool GetUpKeyboard(int nKey)
{
	return(g_akeyStateUp[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̃v���X��Ԃ��擾
//=============================================================================
bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) ? true : false;
}
