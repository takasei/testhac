//=============================================================================
//
// �|���S������ [polygon.cpp]
// Author : masayasu wakita
//
//=============================================================================
#include "magician.h"
#include "meshorbit.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_MAGICIAN	(128)

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;										//�ʒu
	D3DXCOLOR	col;										
	D3DXVECTOR3 move;										//�ړ���
	D3DXVECTOR3 rot;										//��]
	D3DXMATRIX	mtxWorld;									//���[���h�}�g���b�N�X
	int nCounterAnim;										//�A�j���[�V�����J�E���^�[
	int nPatternAnim;										//�A�j���[�V����No
	bool bUse;												//�g�p���Ă��邩�ǂ���
} MAGICIAN;

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureMagician = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMagician = NULL;			//���_�o�b�t�@�ւ̃|�C���^
MAGICIAN				g_aMagician[MAX_MAGICIAN];			//����

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexMagician(LPDIRECT3DDEVICE9 pDevice);


//=============================================================================
// ����������
//=============================================================================
void InitMagician(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

												// �ʒu�E��]�̏����ݒ�
	for (int nCntMagician = 0; nCntMagician < MAX_MAGICIAN; nCntMagician++)
	{
		g_aMagician[nCntMagician].bUse = false;
		g_aMagician[nCntMagician].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMagician[nCntMagician].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aMagician[nCntMagician].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMagician[nCntMagician].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/tex/Magician.png", &g_pTextureMagician);

	MakeVertexMagician(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitMagician(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureMagician != NULL)
	{
		g_pTextureMagician->Release();
		g_pTextureMagician = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMagician != NULL)
	{
		g_pVtxBuffMagician->Release();
		g_pVtxBuffMagician = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMagician(void)
{
	VERTEX_3D *pVtx;										//���_���ւ̃|�C���^
	D3DXMATRIX *pHand = GetOrbit();
	PLAYER *pPlayer = GetPlayer();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffMagician->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMagician = 0; nCntMagician < MAX_MAGICIAN; nCntMagician++)
	{
		//�J�E���^�[�̉��Z
		g_aMagician[nCntMagician].nCounterAnim++;

		//�������g���Ă���ꍇ
		if (g_aMagician[nCntMagician].bUse == true)
		{
			g_aMagician[nCntMagician].rot.y = pPlayer->rot.y + 0.5f;

			g_aMagician[nCntMagician].pos = D3DXVECTOR3(pHand->_41, pHand->_42, pHand->_43);

			
			g_aMagician[nCntMagician].col.a -= 0.1;

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, g_aMagician[nCntMagician].col.a);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, g_aMagician[nCntMagician].col.a);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, g_aMagician[nCntMagician].col.a);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, g_aMagician[nCntMagician].col.a);
		}
		pVtx += 4;										//���_�f�[�^�̃|�C���g��4���i�߂�	
	}
	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffMagician->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMagician(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX	mtxRot, mtxTrans, mtxView;				//�v�Z�p�}�g���b�N�X

	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// ����(�����)���J�����O����

	for (int nCntMagician = 0; nCntMagician < MAX_MAGICIAN; nCntMagician++)
	{
		if (g_aMagician[nCntMagician].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aMagician[nCntMagician].mtxWorld);

			//pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//g_aMagician[nCntMagician].mtxWorld._11 = mtxView._11;
			//g_aMagician[nCntMagician].mtxWorld._12 = mtxView._21;
			//g_aMagician[nCntMagician].mtxWorld._13 = mtxView._31;
			//g_aMagician[nCntMagician].mtxWorld._21 = mtxView._12;
			//g_aMagician[nCntMagician].mtxWorld._22 = mtxView._22;
			//g_aMagician[nCntMagician].mtxWorld._23 = mtxView._32;
			//g_aMagician[nCntMagician].mtxWorld._31 = mtxView._13;
			//g_aMagician[nCntMagician].mtxWorld._32 = mtxView._23;
			//g_aMagician[nCntMagician].mtxWorld._33 = mtxView._33;

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMagician[nCntMagician].rot.y, g_aMagician[nCntMagician].rot.x, g_aMagician[nCntMagician].rot.z);
			D3DXMatrixMultiply(&g_aMagician[nCntMagician].mtxWorld, &g_aMagician[nCntMagician].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aMagician[nCntMagician].pos.x, g_aMagician[nCntMagician].pos.y, g_aMagician[nCntMagician].pos.z);
			D3DXMatrixMultiply(&g_aMagician[nCntMagician].mtxWorld, &g_aMagician[nCntMagician].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aMagician[nCntMagician].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMagician, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetTexture(0, g_pTextureMagician);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntMagician, 2);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetTexture(0, NULL);

		}
	}

	//�ʏ�u�����h�ɖ߂�
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ����(�����)���J�����O����
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMagician(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_MAGICIAN, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffMagician, NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffMagician->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMagician = 0; nCntMagician < MAX_MAGICIAN; nCntMagician++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-30.0f, 30.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(30.0f, 30.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-30.0f, -30.0f, -0.0f);
		pVtx[3].pos = D3DXVECTOR3(30.0f, -30.0f, -0.0f);

		//�@���x�N�g��
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//�e�N�X�`���`�ʂ̈ʒu
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffMagician->Unlock();
}

//=============================================================================
// �����̍쐬
//=============================================================================
void SetMagician(D3DXVECTOR3 pos)
{
	for (int nCntExplosion = 0; nCntExplosion < MAX_MAGICIAN; nCntExplosion++)
	{
		if (!g_aMagician[nCntExplosion].bUse)
		{
			g_aMagician[nCntExplosion].pos = pos;
			g_aMagician[nCntExplosion].bUse = true;
			break;
		}
	}
}