//=============================================================================
//
// �̗͏��� [hitpoint.cpp]
// Author : Seiya Takahashi
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "hitpoint.h"
#include "fade.h"
#include "player.h"
#include "enemy.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_ADD_HPbar	"data/tex/HP�o�[��.png"			//�ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_ADD_HPframe "data/tex/HP�o�[��.png"			//�ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_ADD_HP		"data/tex/HP.png"				//�ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_HITPOINT (6)									//�e�N�X�`������
#define MAX_WIDTH (465.0f)									//�摜�̕��̍ő�l
#define MAX_HEIGHT (27.0f)									//�摜�̍����̍ő�l
#define PLAYER_POS D3DXVECTOR3(70, 20, 0)					//Player�o�[�̈ʒu
#define ENEMY_POS D3DXVECTOR3(1185, 20, 0)					//Enemy�o�[�̈ʒu
#define NORMAL_COLOR D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)		//���ʂ̐F

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureHITPOINT[MAX_HITPOINT] = {};				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHITPOINT = NULL;

HITPOINT g_HitPoint;
//=============================================================================
// ����������
//=============================================================================
void InitHitPoint(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *pPlayer = GetPlayer();
	ENEMY *pEnemy = GetEnemy();
	
	g_HitPoint.fMaxHp = (float)pPlayer->nLife;
	g_HitPoint.fNowHp = g_HitPoint.fMaxHp;
	g_HitPoint.fWidth = MAX_WIDTH;
	g_HitPoint.fMaxHpEnemy = (float)pEnemy->nLife;
	g_HitPoint.fNowHpEnemy = g_HitPoint.fMaxHpEnemy;
	g_HitPoint.fWidthEnemy = MAX_WIDTH;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ADD_HPbar, &g_pTextureHITPOINT[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ADD_HPframe, &g_pTextureHITPOINT[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ADD_HP, &g_pTextureHITPOINT[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ADD_HPbar, &g_pTextureHITPOINT[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ADD_HPframe, &g_pTextureHITPOINT[4]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ADD_HP, &g_pTextureHITPOINT[5]);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_HITPOINT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHITPOINT,
		NULL);

	//�e�N�X�`���ݒ�
	//Player1�̗̑�
	SetVertexHitPoint(0, PLAYER_POS, D3DXCOLOR(0.0f, 1.0f, 0.25f, 1.0f), MAX_WIDTH, MAX_HEIGHT);
	SetVertexHitPoint(1, D3DXVECTOR3(50, 15, 0), NORMAL_COLOR, 505.0f, MAX_HEIGHT + 8.0f);
	SetVertexHitPoint(2, D3DXVECTOR3(20, 15, 0), NORMAL_COLOR, 40, 30);

	//Player2�̗̑�
	SetVertexHitPoint1(3, ENEMY_POS, D3DXCOLOR(0.0f, 1.0f, 0.25f, 1.0f), MAX_WIDTH, MAX_HEIGHT);
	SetVertexHitPoint1(4, D3DXVECTOR3(1200, 15, 0), NORMAL_COLOR, 505.0f, MAX_HEIGHT + 8.0f);
	SetVertexHitPoint(5, D3DXVECTOR3(1180, 15, 0), NORMAL_COLOR, 40, 30);
}
//=============================================================================
// �I������
//=============================================================================
void UninitHitPoint(void)
{
	int nCntTex;

	for (nCntTex = 0; nCntTex < MAX_HITPOINT; nCntTex++)
	{
		//�e�N�X�`���̊J��
		if (g_pTextureHITPOINT[nCntTex] != NULL)
		{
			g_pTextureHITPOINT[nCntTex]->Release();
			g_pTextureHITPOINT[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffHITPOINT != NULL)
	{
		g_pVtxBuffHITPOINT->Release();
		g_pVtxBuffHITPOINT = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateHitPoint(void)
{
	PLAYER *pPlayer = GetPlayer();
	ENEMY *pEnemy = GetEnemy();
	float NowHP;
	float fWidth;																						//���݂̉摜�̕�
	float fResidue;																						//�摜�̎c��̒���
	float NowHpEnemy;																					//�G�̍��̗̑�
	float fWidthEnemy;																					//���݂̉摜�̕�
	float fResidueEnemy;																				//�摜�̎c��̒���

	//Player�̌v�Z
	g_HitPoint.fNowHp = (float)pPlayer->nLife;															//���݂�HP
	NowHP = g_HitPoint.fNowHp / g_HitPoint.fMaxHp;														//HP�̔䗦�v�Z
	fWidth = NowHP * g_HitPoint.fWidth;																	//�`�悷�ׂ��摜����������Ȃ̂�
	fResidue = (g_HitPoint.fMaxHp - g_HitPoint.fNowHp) / g_HitPoint.fMaxHp;								//HP�̎c��̔䗦�v�Z

	//Enemy�̌v�Z
	g_HitPoint.fNowHpEnemy = (float)pEnemy->nLife;														//���݂�HP
	NowHpEnemy = g_HitPoint.fNowHpEnemy / g_HitPoint.fMaxHpEnemy;										//HP�̔䗦�v�Z
	fWidthEnemy = NowHpEnemy * g_HitPoint.fWidthEnemy;													//�`�悷�ׂ��摜����������Ȃ̂�
	fResidueEnemy = (g_HitPoint.fMaxHpEnemy - g_HitPoint.fNowHpEnemy) / g_HitPoint.fMaxHpEnemy;			//HP�̎c��̔䗦�v�Z

	//Player�̗͔̑����ȏ�
	if (NowHP > 0.5f)
	{
		SetVertexHitPoint(0, PLAYER_POS, D3DXCOLOR(0.0f + fResidue * 2, 1.0f, 0.25f - (fResidue / 2), 1.0f), fWidth, MAX_HEIGHT);
	}
	else
	{
		SetVertexHitPoint(0, PLAYER_POS, D3DXCOLOR(1.0f, NowHP * 2, 0.0f, 1.0f), fWidth, MAX_HEIGHT);
	}

	//Enemy�̗͔̑����ȏ�
	if (NowHpEnemy > 0.5f)
	{
		SetVertexHitPoint1(3, ENEMY_POS, D3DXCOLOR(0.0f + fResidueEnemy * 2, 1.0f, 0.25f - (fResidueEnemy / 2), 1.0f), fWidthEnemy, MAX_HEIGHT);
	}
	else
	{
		SetVertexHitPoint1(3, ENEMY_POS, D3DXCOLOR(1.0f, NowHpEnemy * 2, 0.0f, 1.0f), fWidthEnemy, MAX_HEIGHT);
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawHitPoint(void)
{
	int nCntTex;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffHITPOINT, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntTex = 0; nCntTex < MAX_HITPOINT; nCntTex++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureHITPOINT[nCntTex]);

		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTex * 4, 2);
	}
}

//=============================================================================
// ���_�̐ݒ�
//=============================================================================
void SetVertexHitPoint(int index, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight)
{
	VERTEX_2D *pVtx;										//���_���ւ̃|�C���^

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffHITPOINT->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += index * 4;					//���_��4�����Z

	// ���_���̐ݒ�
	//���_���W�̐ݒ�(���x���W + �Ԋu * nCntScore (+ ��), ���y���W)
	pVtx[0].pos = D3DXVECTOR3(pos.x, pos.y, 0);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y, 0);
	pVtx[2].pos = D3DXVECTOR3(pos.x, pos.y + fHeight, 0);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHeight, 0);

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

	//�e�N�X�`���`�ʂ̈ʒu
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffHITPOINT->Unlock();
}

//=============================================================================
// ���_�̐ݒ�
//=============================================================================
void SetVertexHitPoint1(int index, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight)
{
	VERTEX_2D *pVtx;										//���_���ւ̃|�C���^

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffHITPOINT->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += index * 4;					//���_��4�����Z

	// ���_���̐ݒ�
	//���_���W�̐ݒ�(���x���W + �Ԋu * nCntScore (+ ��), ���y���W)
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y, 0);
	pVtx[1].pos = D3DXVECTOR3(pos.x, pos.y, 0);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHeight, 0);
	pVtx[3].pos = D3DXVECTOR3(pos.x, pos.y + fHeight, 0);

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

	//�e�N�X�`���`�ʂ̈ʒu
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffHITPOINT->Unlock();
}

//=============================================================================
// �̗͂̎擾
//=============================================================================
HITPOINT *GetHitPoint(void)
{
	return &g_HitPoint;
}
