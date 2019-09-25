//========================================================================================
//
// ��{[gradation.cpp]
//
// Author : masayasu wakita
// 07/13
//
//========================================================================================
#include "gradation.h"
#include "player.h"

//========================================================================================
// �}�N����`
//========================================================================================
#define TEXTURE_GRADATION_ADD		"data/tex/Gradation.png"
#define TEXTURE_BLACKOUT			"data/tex/blood.png"
#define	GRADATION_MAX				2

//========================================================================================
// �O���[�o���ϐ�
//========================================================================================
LPDIRECT3DTEXTURE9 g_apTextureGradation[GRADATION_MAX] = {};						//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGradation = NULL;				//���_�o�b�t�@�ւ̃|�C���^

//========================================================================================
// �|���S���̏�����
//========================================================================================
void InitGradation(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_GRADATION_ADD, &g_apTextureGradation[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BLACKOUT, &g_apTextureGradation[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * GRADATION_MAX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffGradation, NULL);

	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffGradation->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTex = 0; nCntTex < GRADATION_MAX; nCntTex++)
	{
		//���W�̈ʒu
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		//1.0�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		if (nCntTex == 0)
		{
			if (GetMode() == MODE_GAME)
			{
				//�J���[�`���[�g�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);
			}
			else
			{
				//�J���[�`���[�g�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
			}
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffGradation->Unlock();
}

//========================================================================================
// �|���S���̊J������
//========================================================================================
void UninitGradation(void)
{
		//�e�N�X�`���̊J��

	for (int nCntTex = 0; nCntTex < GRADATION_MAX; nCntTex++)
	{
		if (g_apTextureGradation[nCntTex] != NULL)
		{
			g_apTextureGradation[nCntTex]->Release();
			g_apTextureGradation[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffGradation != NULL)
	{
		g_pVtxBuffGradation->Release();
		g_pVtxBuffGradation = NULL;
	}
}

//========================================================================================
// �|���S���̍X�V����
//========================================================================================
void UpdateGradation(void)
{
	VERTEX_2D *pVtx;
	PLAYER *pPlayer = GetPlayer();

	if (GetMode() == MODE_GAME)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pVtxBuffGradation->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4;

		//�J���[�`���[�g�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f - 0.7f * (pPlayer->nLife / (float)PLAYER_LIFE));
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f - 0.7f * (pPlayer->nLife / (float)PLAYER_LIFE));
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f - 0.7f * (pPlayer->nLife / (float)PLAYER_LIFE));
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f - 0.7f * (pPlayer->nLife / (float)PLAYER_LIFE));

		//���_�f�[�^�̃A�����b�N
		g_pVtxBuffGradation->Unlock();
	}
}

//========================================================================================
// �|���S���̕`�揈��
//========================================================================================
void DrawGradation(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();
	for (int nCntTex = 0; nCntTex < GRADATION_MAX; nCntTex++)
	{
		//���_�o�b�t�@���f�o�C�X�̃f�[�^�Ƀo�C���h
		pDevice->SetStreamSource(0, g_pVtxBuffGradation, 0, sizeof(VERTEX_2D));

		//�e�N�X�`���̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetTexture(0, g_apTextureGradation[nCntTex]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTex, 2);
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void MakeVertexGradation(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	VERTEX_2D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffGradation->Lock(0, 0, (void**)&pVtx, 0);

	//���W�̈ʒu
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x, pos.y - size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x, pos.y - size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x, pos.y + size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);

	//1.0�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�J���[�`���[�g�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.5f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.5f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.5f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.5f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffGradation->Unlock();
}