//========================================================================================
//
// ��{[result.cpp]
//
// Author : masayasu wakita
// 07/13
//
//========================================================================================
#include "input.h"
#include "fade.h"
#include "result.h"
#include "camera.h"
#include "light.h"
#include "meshField.h"
#include "shadow.h"
#include "controller.h"
#include "sound.h"
#include "tutorial.h"

//========================================================================================
// �}�N����`
//========================================================================================
#define TEXTURE_ADD "data/tex/bg003.png"
#define TEXTURE_BG	"data/tex/gameover_bg.png"
#define TEXTURE_CLEAR "data/tex/gameclear.png"
#define TEXTURE_FAILD "data/tex/gameover.png"
#define MAX_RESULT 2

//========================================================================================
// �O���[�o���ϐ�
//========================================================================================
LPDIRECT3DTEXTURE9 g_pTextureResult[5] = {};						//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;				//���_�o�b�t�@�ւ̃|�C���^

RESULTSTATE g_resultState;
float g_fMoveResultPos;
//========================================================================================
// �|���S���̏�����
//========================================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	SetTutorial();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ADD, &g_pTextureResult[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BG, &g_pTextureResult[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_CLEAR, &g_pTextureResult[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FAILD, &g_pTextureResult[3]);
	D3DXCreateTextureFromFile(pDevice, "data/tex/bg003", &g_pTextureResult[4]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RESULT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffResult, NULL);

	SetVertexResult(4, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), SCREEN_WIDTH, SCREEN_HEIGHT);

	SetVertexResult(1, D3DXVECTOR3(640, 200, 0), 600, 200);

	// �e�̏���������
	InitShadow();

	// �t�B�[���h�̏���������
	InitMeshField();

	PlaySound(SOUND_LABEL_SE_GAMEOVER);
}

//========================================================================================
// �|���S���̊J������
//========================================================================================
void UninitResult(void)
{
	int nCntTex;

	//�t�B�[���h�̏I������
	UninitMeshField();

	// �e�̏I������
	UninitShadow();

	//�e�N�X�`���̊J��
	for (nCntTex = 0; nCntTex < 5; nCntTex++)
	{
		if (g_pTextureResult[nCntTex] != NULL)
		{
			g_pTextureResult[nCntTex]->Release();
			g_pTextureResult[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}

//========================================================================================
// �|���S���̍X�V����
//========================================================================================
void UpdateResult(void)
{
	VERTEX_2D *pVtx;										//���_���ւ̃|�C���^

	//�t�B�[���h�̍X�V����
	UpdateMeshField();

	//�e�̍X�V����
	UpdateShadow();

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + g_fMoveResultPos);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + g_fMoveResultPos);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + g_fMoveResultPos);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f + g_fMoveResultPos);

	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffResult->Unlock();

	// ��ʑJ��
	if (GetTriggerKeyboard(DIK_RETURN) || GetControllerTrigger(0, JOYPADKEY_START))
	{
		if (GetFade() == FADE_NONE)
		{
			SetFade(MODE_RANKING);
		}
	}
}

//========================================================================================
// �|���S���̕`�揈��
//========================================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCount;

	////�t�B�[���h�̕`�揈��
	//DrawMeshField();

	// �e�̕`�揈��
	DrawShadow();

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCount = 0; nCount < MAX_RESULT; nCount++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResult[nCount * 2 + (g_resultState == RESULTSTATE_CLEAR ? 0 : 1)]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}

//=============================================================================
// ���_�̐ݒ�
//=============================================================================
void SetVertexResult(int index, D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	VERTEX_2D *pVtx;										//���_���ւ̃|�C���^

															//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += index * 4;

	// ���_���̐ݒ�
	//���_���W�̐ݒ�(���x���W + �Ԋu * nCntScore (+ ��), ���y���W)
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth / 2, pos.y - fHeight / 2, 0);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth / 2, pos.y - fHeight / 2, 0);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth / 2, pos.y + fHeight / 2, 0);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth / 2, pos.y + fHeight / 2, 0);

	//1.0�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	if (index == 4)
	{
		//�J���[�`���[�g�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	}
	else
	{
		//�J���[�`���[�g�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//�e�N�X�`���`�ʂ̈ʒu
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffResult->Unlock();
}

//=============================================================================
// ���ʂ̐ݒ�
//=============================================================================
void SetResultState(RESULTSTATE state)
{
	g_resultState = state;
}