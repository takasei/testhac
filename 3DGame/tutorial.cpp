//========================================================================================
//
// ��{[Tutorial.cpp]
//
// Author : masayasu wakita
//
//========================================================================================
#include "tutorial.h"
#include "fade.h"
#include "pause.h"
#include "player.h"
#include "controller.h"
#include "enemy.h"
#include "model.h"

//========================================================================================
// �}�N����`
//========================================================================================
#define TEXTURE_BG_ADD "data/tex/School_library.jpg"
#define TEXTURE_TUTORIAL_ADD "data/tex/MessageWindow2.png"
#define TEXTURE_MESSAGE_ADD "data/tex/�e���b�v�R�����g�`���[�g���A��.png"
#define MAX_TUTORIAL 2

//========================================================================================
// �O���[�o���ϐ�
//========================================================================================
LPDIRECT3DTEXTURE9 g_pTextureTutorial[2] = {};						//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;					//���_�o�b�t�@�ւ̃|�C���^
D3DXCOLOR g_tutorialCol;
bool g_aPressButton[8];
bool g_bIsFinish = false;
bool g_bDrowText;
int g_nCnt_tutorial;
bool g_bPlayerOperation;
bool g_bBulletOperation;
int g_nCountText;
int g_nCountPage;
float g_fLeftTutorial;
float g_fRightTutorial;
float fMove_Tutorial_Pos;
float g_fTutorial;

//========================================================================================
// �|���S���̏�����
//========================================================================================
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	PLAYER *pPlayer;
	pDevice = GetDevice();
	g_nCountText = 0;
	g_nCountPage = 0;
	g_bDrowText = true;
	g_fLeftTutorial = 0.33f;
	g_fRightTutorial = 0.66f;
	g_nCnt_tutorial = 0;

	for (int nCount = 0; nCount < 8; nCount++)
	{
		g_aPressButton[nCount] = false;
	}

	//�������擾
	pPlayer = GetPlayer();

	g_tutorialCol = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_TUTORIAL_ADD, &g_pTextureTutorial[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MESSAGE_ADD, &g_pTextureTutorial[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TUTORIAL, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTutorial, NULL);

	//���_���̍쐬
	SetVertexTutorial(0, D3DXVECTOR3(640.0f, 650.0f, 0.0f), g_tutorialCol, SCREEN_WIDTH, 170);

	SetVertexTutorial(1, D3DXVECTOR3(640.0f, 640.0f, 0.0f), g_tutorialCol,1200, 100);
}

//========================================================================================
// �|���S���̊J������
//========================================================================================
void UninitTutorial(void)
{
	int nCntTex;

	//�e�N�X�`���̊J��
	for (nCntTex = 0; nCntTex < MAX_TUTORIAL; nCntTex++)
	{
		if (g_pTextureTutorial[nCntTex] != NULL)
		{
			g_pTextureTutorial[nCntTex]->Release();
			g_pTextureTutorial[nCntTex] = NULL;
		}
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
}

//========================================================================================
// �|���S���̍X�V����
//========================================================================================
void UpdateTutorial(void)
{
	SetVertexTutorial(0, D3DXVECTOR3(640.0f, 630.0f, 0.0f), g_tutorialCol, SCREEN_WIDTH, 170);

	SetVertexTutorial(1, D3DXVECTOR3(650.0f, 630.0f, 0.0f), g_tutorialCol, 1200, 100);

	if (GetTriggerKeyboard(DIK_RETURN) || GetControllerTrigger(0, JOYPADKEY_B) && g_bDrowText == true)
	{
		g_nCountPage++;
		g_nCountText = 0;

		if (g_nCountPage == 4)
		{
			//SetLayout(LAYOUTTYPE_NONE);
			//SetEnemy(D3DXVECTOR3(100.0f, 0.0f, 100.0f), 999);
		}

		if (g_nCountPage == 5)
		{
			if (GetFade() == FADE_NONE)
			{
				g_bIsFinish = true;
				SetFade(MODE_GAME);
				SetGameState(GAMESTATE_TUTORIALEND);
			}
		}
	}
}

//========================================================================================
// �|���S���̕`�揈��
//========================================================================================
void DrawTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCount;

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_bDrowText == true)
	{
		if (GetGameState() == GAMESTATE_TUTORIAL || GetPauseMode() == GAMESTATE_TUTORIAL)
		{
			for (nCount = 0; nCount < MAX_TUTORIAL; nCount++)
			{
				pDevice->SetTexture(0, g_pTextureTutorial[nCount]);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
			}
		}
	}
}

//=============================================================================
// ���_�̐ݒ�
//=============================================================================
void SetVertexTutorial(int index, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight)
{
	VERTEX_2D *pVtx;										//���_���ւ̃|�C���^

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

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

	//�J���[�`���[�g�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	if (index == 1)
	{
		//�e�N�X�`���`�ʂ̈ʒu
		pVtx[0].tex = D3DXVECTOR2(0.0f + 0.5f * (g_nCountPage / 6), 0.0f + 0.167f * (g_nCountPage % 6));
		pVtx[1].tex = D3DXVECTOR2(0.5f + 0.5f * (g_nCountPage / 6), 0.0f + 0.167f * (g_nCountPage % 6));
		pVtx[2].tex = D3DXVECTOR2(0.0f + 0.5f * (g_nCountPage / 6), 0.167f + 0.167f * (g_nCountPage % 6));
		pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5f * (g_nCountPage / 6), 0.167f + 0.167f * (g_nCountPage % 6));
	}
	else
	{
		//�e�N�X�`���`�ʂ̈ʒu
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffTutorial->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
bool IsFinish(void)
{
	return g_bIsFinish;
}

//=============================================================================
// ����������
//=============================================================================
void SetTutorial(void)
{
	g_bIsFinish = false;
}
