//========================================================================================
//
// ��{[skill.cpp]
//
// Author : Ryouma Inoue
// 07/13
//
//========================================================================================
#include "skill.h"
#include "player.h"
#include "input.h"

//========================================================================================
// �}�N����`
//========================================================================================
#define TEXTURE_ASUKA			"data/tex/������.jpg"

//========================================================================================
// �O���[�o���ϐ�
//========================================================================================
LPDIRECT3DTEXTURE9 g_apTextureUI[TEXTURETYPE_MAX] = {};									//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUI = NULL;											//���_�o�b�t�@�ւ̃|�C���^
SKILL	g_aSkill[TEXTURETYPE_MAX];
int		g_nCntSkill_1;
int		g_nCntSkill_2;
int		g_nCntSkill_3;

//========================================================================================
// �|���S���̏�����
//========================================================================================
void InitSkill(void)
{
	g_nCntSkill_1 = 0;
	g_nCntSkill_2 = 0;
	g_nCntSkill_3 = 0;
	for (int nCntUI = 0; nCntUI < TEXTURETYPE_MAX; nCntUI++)
	{
		g_aSkill[nCntUI].nCounterAnim = 0;
		g_aSkill[nCntUI].nPatternAnim = 0;
		g_aSkill[nCntUI].bUse = false;
	}

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ASUKA, &g_apTextureUI[TEXTURETYPE_ASUKA]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ASUKA, &g_apTextureUI[TEXTURETYPE_ASUKA2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ASUKA, &g_apTextureUI[TEXTURETYPE_ASUKA3]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 
	TEXTURETYPE_MAX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D,
		D3DPOOL_MANAGED, &g_pVtxBuffUI, NULL);

	MakeVertexSkill(0, D3DXVECTOR3(70, 650, 0.0f), D3DXVECTOR3(100, 100, 0.0f), TEXTURETYPE_ASUKA);
	MakeVertexSkill(1, D3DXVECTOR3(170, 650, 0.0f), D3DXVECTOR3(100, 100, 0.0f), TEXTURETYPE_ASUKA2);
	MakeVertexSkill(2, D3DXVECTOR3(120, 550, 0.0f), D3DXVECTOR3(100, 100, 0.0f), TEXTURETYPE_ASUKA3);
}

//========================================================================================
// �|���S���̊J������
//========================================================================================
void UninitSkill(void)
{
	for (int nCntTex = 0; nCntTex < TEXTURETYPE_MAX; nCntTex++)
	{
		//�e�N�X�`���̊J��
		if (g_apTextureUI[nCntTex] != NULL)
		{
			g_apTextureUI[nCntTex]->Release();
			g_apTextureUI[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffUI != NULL)
	{
		g_pVtxBuffUI->Release();
		g_pVtxBuffUI = NULL;
	}
}

//========================================================================================
// �|���S���̍X�V����
//========================================================================================
void UpdateSkill(void)
{
	g_nCntSkill_1++;
	g_nCntSkill_2++;
	g_nCntSkill_3++;

	if (GetTriggerKeyboard(DIK_1))
	{
		g_aSkill[TEXTURETYPE_ASUKA].bUse = true;
		g_nCntSkill_1 = 0;
	}
	if (GetTriggerKeyboard(DIK_2))
	{
		g_aSkill[TEXTURETYPE_ASUKA2].bUse = true;
		g_nCntSkill_2 = 0;
	}
	if (GetTriggerKeyboard(DIK_3))
	{
		g_aSkill[TEXTURETYPE_ASUKA3].bUse = true;
		g_nCntSkill_3 = 0;
	}

	if (g_nCntSkill_1 >= 100)
	{
		g_aSkill[TEXTURETYPE_ASUKA].bUse = false;
	}
	if (g_nCntSkill_2 >= 100)
	{
		g_aSkill[TEXTURETYPE_ASUKA2].bUse = false;
	}
	if (g_nCntSkill_3 >= 100)
	{
		g_aSkill[TEXTURETYPE_ASUKA3].bUse = false;
	}
}

//========================================================================================
// �|���S���̕`�揈��
//========================================================================================
void DrawSkill(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	for (int nCnt = 0; nCnt < TEXTURETYPE_MAX; nCnt++)
	{
		if (g_aSkill[nCnt].bUse == false)
		{
			//�f�o�C�X���擾����
			pDevice = GetDevice();

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�Ƀo�C���h
			pDevice->SetStreamSource(0, g_pVtxBuffUI, 0, sizeof(VERTEX_2D));

			//�e�N�X�`���̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetTexture(0, g_apTextureUI[nCnt]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void MakeVertexSkill(int nIndex, D3DXVECTOR3 pos, D3DXVECTOR3 size, TEXTURETYPE type)
{
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nIndex;

	g_aSkill[nIndex].size = size;						//�T�C�Y�̒l���i�[
	g_aSkill[nIndex].pos = pos;							//�ʒu�̒l���i�[
	g_aSkill[nIndex].type = type;

	g_aSkill[nIndex].fAngle = atan2f(g_aSkill[nIndex].size.x, g_aSkill[nIndex].size.y);
	g_aSkill[nIndex].fLength = (float)sqrt(g_aSkill[nIndex].size.x * g_aSkill[nIndex].size.x + g_aSkill[nIndex].size.y * g_aSkill[nIndex].size.y) / 2;

	//���W�̈ʒu
	pVtx[0].pos.x = g_aSkill[nIndex].pos.x + sinf(-D3DX_PI + g_aSkill[nIndex].fAngle + g_aSkill[nIndex].rot.z) * g_aSkill[nIndex].fLength;
	pVtx[0].pos.y = g_aSkill[nIndex].pos.y + cosf(-D3DX_PI + g_aSkill[nIndex].fAngle + g_aSkill[nIndex].rot.z) * g_aSkill[nIndex].fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_aSkill[nIndex].pos.x + sinf(D3DX_PI - g_aSkill[nIndex].fAngle + g_aSkill[nIndex].rot.z) * g_aSkill[nIndex].fLength;
	pVtx[1].pos.y = g_aSkill[nIndex].pos.y + cosf(D3DX_PI - g_aSkill[nIndex].fAngle + g_aSkill[nIndex].rot.z) * g_aSkill[nIndex].fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_aSkill[nIndex].pos.x + sinf(-g_aSkill[nIndex].fAngle + g_aSkill[nIndex].rot.z) * g_aSkill[nIndex].fLength;
	pVtx[2].pos.y = g_aSkill[nIndex].pos.y + cosf(-g_aSkill[nIndex].fAngle + g_aSkill[nIndex].rot.z) * g_aSkill[nIndex].fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_aSkill[nIndex].pos.x + sinf(g_aSkill[nIndex].fAngle + g_aSkill[nIndex].rot.z) * g_aSkill[nIndex].fLength;
	pVtx[3].pos.y = g_aSkill[nIndex].pos.y + cosf(g_aSkill[nIndex].fAngle + g_aSkill[nIndex].rot.z) * g_aSkill[nIndex].fLength;
	pVtx[3].pos.z = 0.0f;

	//1.0�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�J���[�`���[�g�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffUI->Unlock();
}

//=============================================================================
// UI�擾
//=============================================================================
SKILL *GetSkill(void)
{
	return &g_aSkill[0];
}