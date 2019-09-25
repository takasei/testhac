//=============================================================================
//
// ���͏��� [mouse.cpp]
// Author : wakita masayasu
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "mouse.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	NUM_KEY_MAX				(256)	// �L�[�̍ő吔
#define	NUM_BUTTON_MAX			(8)		// �{�^��(�}�E�X)�̍ő吔

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECTINPUT8			g_pMouseput = NULL;						// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8	g_pDevMouse = NULL;						// ���̓f�o�C�X(�}�E�X)�ւ̃|�C���^

MOUSE					g_mouse;								// �}�E�X�̏��

BYTE					g_aButtonState[NUM_BUTTON_MAX];			// �}�E�X�̓��͏�񃏁[�N
BYTE					g_aButtonStateTrigger[NUM_BUTTON_MAX];	// �}�E�X�̃g���K�[

HWND					g_hWnd;									// �E�B���h�E�n���h��

//=============================================================================
// �}�E�X�̏���������
//=============================================================================
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̍쐬
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)& g_pMouseput, NULL)))
	{
		return E_FAIL;
	}

	g_pMouseput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL);
	g_pDevMouse->SetDataFormat(&c_dfDIMouse2); // �}�E�X�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�

	g_pDevMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL; // ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j
	g_pDevMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);

	// ���͐���J�n
	g_pDevMouse->Acquire();

	// ���
	g_hWnd = hWnd;

	return S_OK;
}

//=============================================================================
// �}�E�X�̍X�V����
//=============================================================================
void UpdateMouse(void)
{
	// �ϐ��錾
	int nCntButton;
	POINT point;

	// �l�̏�����
	g_mouse.mouseState.rgbButtons[0] = 0;

	GetCursorPos(&point);
	ScreenToClient(g_hWnd, &point);
	g_mouse.posX = (float)point.x;
	g_mouse.posY = (float)point.y;

	// �l�̍X�V
	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &g_mouse.mouseState)))
	{
		for (nCntButton = 0; nCntButton < NUM_BUTTON_MAX; nCntButton++)
		{
			// �r���I�_���a���ǂ������f
			g_aButtonStateTrigger[nCntButton] = (g_aButtonState[nCntButton] ^ g_mouse.mouseState.rgbButtons[nCntButton]) & g_mouse.mouseState.rgbButtons[nCntButton];
			g_aButtonState[nCntButton] = g_mouse.mouseState.rgbButtons[nCntButton];	// �L�[�v���X���ۑ�
		}
	}
	else
	{
		g_pDevMouse->Acquire(); // �P���ڂ�Q���ڂɃG���[���o�邪�������Ă悢�B
	}
}

//=============================================================================
// �}�E�X�̏I������
//=============================================================================
void UninitMouse(void)
{
	// ���̓f�o�C�X(�}�E�X)�̊J��
	if (g_pDevMouse != NULL)
	{
		g_pDevMouse->Unacquire();	// �}�E�X�ւ̃A�N�Z�X�����J��
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}
	// DirectInput�I�u�W�F�N�g�̊J��
	if (g_pMouseput != NULL)
	{
		g_pMouseput->Release();
		g_pMouseput = NULL;
	}
}


//=============================================================================
// �}�E�X�̃v���X��Ԃ��擾
//=============================================================================
bool GetMousePress(int nButton)
{
	return (g_mouse.mouseState.rgbButtons[nButton] & 0x80) ? true : false;
}

//=============================================================================
// �}�E�X�̃g���K�[����
//=============================================================================
bool GetMousePressTrigger(int nButton)
{
	return (g_aButtonStateTrigger[nButton] & 0x80) ? true : false;
}

//=============================================================================
// �}�E�X��X���W�̎擾
//=============================================================================
LONG GetMouseX(void)
{
	return (LONG)g_mouse.posX - SCREEN_WIDTH / 2;
}

//=============================================================================
// �}�E�X��Y���W�̎擾
//=============================================================================
LONG GetMouseY(void)
{
	return ((LONG)g_mouse.posY - SCREEN_HEIGHT / 2) * -1;
}