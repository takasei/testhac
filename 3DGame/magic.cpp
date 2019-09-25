//=============================================================================
//
// ���@���� [magic.cpp]
// Author : Seiya Takahashi
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "magic.h"
#include "fade.h"
#include "input.h"
#include "mouse.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_ADD_MagicBar	"data/tex/HP�o�[��.png"		//�ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_ADD_MagicFrame "data/tex/HP�o�[��.png"		//�ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_ADD_MP			"data/tex/MP.png"			//�ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_MAGIC (3)											//�e�N�X�`������
#define MAX_WIDTH (500.0f)										//�摜�̕��̍ő�l
#define MAX_HEIGHT (27.0f)										//�摜�̍����̍ő�l

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureMagic[MAX_MAGIC] = {};				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMagic = NULL;

MAGIC g_Magic;
//=============================================================================
// ����������
//=============================================================================
void InitMagic(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	g_Magic.fMaxMagic = 100.0f;
	g_Magic.fNowMagic = g_Magic.fMaxMagic;
	g_Magic.fWidth = MAX_WIDTH;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ADD_MagicBar, &g_pTextureMagic[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ADD_MagicFrame, &g_pTextureMagic[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_ADD_MP, &g_pTextureMagic[2]);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_MAGIC,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMagic,
		NULL);

	//�e�N�X�`���ݒ�
	//SetVertexMagic(0, D3DXVECTOR3(55, 55, 0), D3DXCOLOR(0.059f, 0.32f, 0.73f, 1.0f), MAX_WIDTH, MAX_HEIGHT);

	//SetVertexMagic(1, D3DXVECTOR3(50, 50, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), MAX_WIDTH + 10.0f, 35.0f);

	//SetVertexMagic(2, D3DXVECTOR3(20, 50, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 40, 30);

}
//=============================================================================
// �I������
//=============================================================================
void UninitMagic(void)
{
	int nCntTex;

	for (nCntTex = 0; nCntTex < MAX_MAGIC; nCntTex++)
	{
		//�e�N�X�`���̊J��
		if (g_pTextureMagic[nCntTex] != NULL)
		{
			g_pTextureMagic[nCntTex]->Release();
			g_pTextureMagic[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffMagic != NULL)
	{
		g_pVtxBuffMagic->Release();
		g_pVtxBuffMagic = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateMagic(void)
{
	float NowMagic;
	float fWidth;																	//���݂̉摜�̕�

	if (GetMousePressTrigger(0))
	{
		g_Magic.fNowMagic -= 10.0f;
	}
	else
	{
		g_Magic.fNowMagic += 0.75f;

		if (g_Magic.fNowMagic >= g_Magic.fMaxMagic)
		{
			g_Magic.fNowMagic = g_Magic.fMaxMagic;
		}
	}

	NowMagic = g_Magic.fNowMagic / g_Magic.fMaxMagic;									//���͂̔䗦�v�Z
	fWidth = NowMagic * g_Magic.fWidth;													//�`�悷�ׂ��摜����������Ȃ̂�

	//SetVertexMagic(0, D3DXVECTOR3(55, 55, 0), D3DXCOLOR(0.059f, 0.32f, 0.73f, 1.0f), fWidth, MAX_HEIGHT);
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawMagic(void)
{
	int nCntTex;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffMagic, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntTex = 0; nCntTex < MAX_MAGIC; nCntTex++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMagic[nCntTex]);

		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTex * 4, 2);

	}

}

//=============================================================================
// ���_�̐ݒ�
//=============================================================================
void SetVertexMagic(int index, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight)
{
	VERTEX_2D *pVtx;										//���_���ւ̃|�C���^

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffMagic->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffMagic->Unlock();

}

//=============================================================================
// �̗͂̎擾
//=============================================================================
MAGIC *GetMagic(void)
{
	return &g_Magic;
}
