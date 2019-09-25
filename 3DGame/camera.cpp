//=============================================================================
//
// �J�������� [camera.cpp]
// Author : masayasu wakita
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "player.h"
#include "controller.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define DISTANCE -400						//����

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
#ifdef _DEBUG
void DrawCameraData(void);
#endif

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CAMERA	g_camera;			//�J�������

D3DXVECTOR3	g_originPos;

D3DXVECTOR3 g_resultPos;
#ifdef _DEBUG
LPD3DXFONT			g_pCameraFont = NULL;			// �t�H���g�ւ̃|�C���^
#endif

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3		originPos;

#ifdef _DEBUG
	// �f�o�b�O�\���p�t�H���g��ݒ�
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "�l�r �S�V�b�N", &g_pCameraFont);
#endif

	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//���_
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, DISTANCE);					//�����_
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	originPos = g_camera.posR - g_camera.posV;

	//g_originPos = D3DXVECTOR3(710.0f, 80.0f, -250.0f);
	g_resultPos = D3DXVECTOR3(0.0f, 80.0f, 0.0f);
	g_camera.fDistonce = sqrtf(originPos.y * originPos.y + originPos.z * originPos.z);
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	PLAYER *pPlayer;

	float	fValueH = 0;
	float	fValueV = 0;

	pPlayer = GetPlayer();
	D3DXVECTOR3 Calculation;			//�v�Z�p

	g_camera.rotDest.y = pPlayer->rot.y + D3DX_PI;

	Calculation.y = g_camera.rotDest.y - g_camera.rot.y;

	if (GetMode() == MODE_TITLE)
	{
		g_camera.rotDest.y = 0.0f + D3DX_PI;

		g_camera.posR.x = g_originPos.x + sinf(D3DX_PI + 1.25f);
		g_camera.posR.y = g_originPos.y;
		g_camera.posR.z = g_originPos.z + cosf(D3DX_PI + 1.25f);
		g_camera.posV.x = g_originPos.x + sinf(D3DX_PI + 1.25f) * g_camera.fDistonce;
		g_camera.posV.y = g_originPos.y + 40.0f;
		g_camera.posV.z = g_originPos.z + cosf(D3DX_PI + 1.25f) * g_camera.fDistonce;

		g_originPos.z += 0.1f;
	}

	//�Q�[�����[�h�������ꍇ
	else if (GetMode() == MODE_GAME)
	{
		g_camera.nCount++;

		if (Calculation.y > D3DX_PI)
		{
			g_camera.rotDest.y -= D3DX_PI * 2;
		}
		else if (Calculation.y < -D3DX_PI)
		{
			g_camera.rotDest.y += D3DX_PI * 2;
		}

		if (fabsf(Calculation.y) < 0.0f)
		{
			Calculation.y = g_camera.rotDest.y;
		}

		//if (g_camera.nCount > 60 && GetKeyboardPress(DIK_L) != 1)
		//{
		//	g_camera.rot.y += (g_camera.rotDest.y - g_camera.rot.y) * 0.02f;
		//}

		//g_camera.rot.y += (g_camera.rotDest.y - g_camera.rot.y) * 0.02f;

		//g_camera.posRDest.x =sinf(D3DX_PI + pPlayer->rot.y);
		g_camera.posRDest.y = 50;
		//g_camera.posRDest.z =cosf(D3DX_PI + pPlayer->rot.y);

		g_camera.posVDest.x =sinf(D3DX_PI + g_camera.rot.y) * g_camera.fDistonce;
		g_camera.posVDest.y = 150;
		g_camera.posVDest.z =cosf(D3DX_PI + g_camera.rot.y) * g_camera.fDistonce;

		g_camera.posV += (g_camera.posVDest - g_camera.posV) * 0.2f;

		g_camera.posR += (g_camera.posRDest - g_camera.posR) * 0.2f;
	}

	//���[�h���U���g�������ꍇ
	else if (GetMode() == MODE_RESULT)
	{
		g_camera.rotDest.y = 0.0f + D3DX_PI;

		g_camera.posR.x = 425.0f + sinf(D3DX_PI + 0.5f);
		g_camera.posR.y = 70;
		g_camera.posR.z = -250.0f + cosf(D3DX_PI + 0.5f);
		g_camera.posV.x = 425.0f + sinf(D3DX_PI + 0.5f) * 50;
		g_camera.posV.y = 70 + 30.0f;
		g_camera.posV.z = -250.0f + cosf(D3DX_PI + 0.5f) * 50;
	}

	//���[�h�����L���O�������ꍇ
	else if (GetMode() == MODE_RANKING)
	{
		g_camera.rotDest.y = 0.0f + D3DX_PI;

		g_camera.posR.x = g_resultPos.x + sinf(D3DX_PI + 3.14f);
		g_camera.posR.y = g_resultPos.y;
		g_camera.posR.z = g_resultPos.z + cosf(D3DX_PI + 3.14f);
		g_camera.posV.x = g_resultPos.x + sinf(D3DX_PI + 3.14f) * g_camera.fDistonce;
		g_camera.posV.y = g_resultPos.y + 70.0f;
		g_camera.posV.z = g_resultPos.z + cosf(D3DX_PI + 3.14f) * g_camera.fDistonce;

		g_resultPos.z += -0.5f;
	}

	//g_camera.rot -= D3DXVECTOR3(sinf(D3DX_PI * 1.0f) * (1.5f * g_player.nValueV), 0, cosf(D3DX_PI * 1.0f) * (1.5f * g_player.nValueV));

	GetJoypadStickRight(0, &fValueH, &fValueV);

	g_camera.rot.y +=  fValueH * 0.1f;

	//��]
	if (GetKeyboardPress(DIK_E))
	{
		g_camera.rot.y += 0.01f;
	}
	if (GetKeyboardPress(DIK_Q))
	{
		g_camera.rot.y -= 0.01f;
	}

	//��]���̃��Z�b�g
	if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y += D3DX_PI * 2;
	}
	else if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y -= D3DX_PI * 2;
	}

}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(
		&g_camera.mtxProjection,
		D3DXToRadian(45.0f),								//����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,			//�A�X�y�N�g��
		10.0f,												//NearZ�l
		10000.0f);											//FarZ�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(
		&g_camera.mtxView,
		&g_camera.posV,			//�J�����̎��_
		&g_camera.posR,			//�J�����̒����_
		&g_camera.vecU);		//�J�����̏�����x�N�g��

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
#ifdef _DEBUG
	DrawCameraData();
#endif // _DEBUG
}

#ifdef _DEBUG
//=============================================================================
// �J�����̏��
//=============================================================================
void DrawCameraData(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	RECT rect = { 800, 300, SCREEN_WIDTH, SCREEN_HEIGHT };

	char sCamera[500];
	char sPosV[128];
	char sPosR[128];
	char sRot[128];

	// �e�L�X�g�`��(pos)
	sprintf(&sPosV[0], "g_camera.posV X : %.2f Y : %.2f Z : %.2f\n", g_camera.posV.x, g_camera.posV.y, g_camera.posV.z);
	sprintf(&sPosR[0], "g_camera.posR X : %.2f Y : %.2f Z : %.2f\n", g_camera.posR.x, g_camera.posR.y, g_camera.posR.z);
	sprintf(&sRot[0], "g_camera.rot X : %.2f Y : %.2f Z : %.2f\n", g_camera.rot.x, g_camera.rot.y, g_camera.rot.z);

	strcpy(&sCamera[0], "==============�J����===============\n");

	strcat(&sCamera[0], &sPosV[0]);

	strcat(&sCamera[0], &sPosR[0]);

	strcat(&sCamera[0], &sRot[0]);

	// �e�L�X�g�`��
	g_pCameraFont->DrawText(NULL, &sCamera[0], -1, &rect, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}
#endif // _DEBUG

//=============================================================================
// �J�����̏��
//=============================================================================
CAMERA *GetCamera(void)
{
	return &g_camera;
}