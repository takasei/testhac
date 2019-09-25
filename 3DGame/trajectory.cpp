//=============================================================================
//
// �|���S������ [polygon.cpp]
// Author : masayasu wakita
//
//=============================================================================
#include "polygon.h"
#include "input.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define DEPTH 	50											//���s��
#define WIDE 50												//��

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexTrajectory(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureTrajectory = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTrajectory = NULL;			//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffTrajectory = NULL;			//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

D3DXVECTOR3				g_posTrajectory;						//�|���S���̈ʒu
D3DXVECTOR3				g_rotTrajectory;						//�|���S���̌���(��])
D3DXMATRIX				g_mtxWorldTrajectory;				//���[���h�}�g���b�N�X

int g_nNumVertexTrajectory;									//�����_��
int g_nNumIndexTrajectory;									//�C���f�b�N�X��
int g_nNumPolygonTrajectory;									//���|���S����

int g_nCount;		//���

//=============================================================================
// ����������
//=============================================================================
void InitTrajectory(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	WORD *pIdx;									//�C���f�b�N�X�f�[�^�փ|�C���^

												// �ʒu�E��]�̏����ݒ�
	g_posTrajectory = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotTrajectory = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�����_��
	g_nNumVertexTrajectory = (DEPTH + 1) * (WIDE + 1);

	//�C���f�b�N�X��
	g_nNumIndexTrajectory = ((DEPTH + 1) * 2) * DEPTH + ((WIDE - 1) * 2);

	//���|���S����
	g_nNumPolygonTrajectory = DEPTH * 2 + WIDE * 2;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/tex/stone.pn", &g_pTextureTrajectory);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (DEPTH + 1) * (WIDE + 1), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffTrajectory, NULL);

	//�C���f�b�N�X�o�b�t�@�𐶐�
	pDevice->CreateIndexBuffer(sizeof(WORD) * DEPTH * WIDE * (2 + 4), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffTrajectory, NULL);

	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffTrajectory->Lock(0, 0, (void**)&pVtx, 0);

	for (int nDepth = 0; nDepth < DEPTH + 1; nDepth++)
	{
		for (int nWide = 0; nWide < WIDE + 1; nWide++)
		{
			//���_���W�̐ݒ�
			pVtx[(WIDE + 1) * nDepth + nWide].pos = D3DXVECTOR3((-50.0f * WIDE) + 100 * nWide, 0.0f, (50.0f * DEPTH) - 100 * nDepth);
			//�@���x�N�g��
			pVtx[(WIDE + 1) * nDepth + nWide].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//���_�J���[
			pVtx[(WIDE + 1) * nDepth + nWide].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			//�e�N�X�`���`�ʂ̈ʒu
			pVtx[(WIDE + 1) * nDepth + nWide].tex = D3DXVECTOR2(1.0f * nWide, 1.0f * nDepth);

		}
	}

	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffTrajectory->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^
	g_pIdxBuffTrajectory->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntZ = 0; nCntZ < DEPTH; nCntZ++)
	{
		if (nCntZ != 0)
		{
			pIdx[1] = (DEPTH + 1) + nCntZ * (DEPTH + 1);
			pIdx += 2;
		}

		for (int nCntX = 0; nCntX < WIDE + 1; nCntX++)
		{
			pIdx[0] = (DEPTH + 1) + nCntX + nCntZ * (DEPTH + 1);
			pIdx[1] = 0 + nCntX + nCntZ * (DEPTH + 1);
			pIdx += 2;
		}

		if (DEPTH > 0 && DEPTH > nCntZ)
		{
			pIdx[0] = DEPTH + nCntZ * (DEPTH + 1);
		}
	}

	//�C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^
	g_pIdxBuffTrajectory->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitTrajectory(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureTrajectory != NULL)
	{
		g_pTextureTrajectory->Release();
		g_pTextureTrajectory = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffTrajectory != NULL)
	{
		g_pIdxBuffTrajectory->Release();
		g_pIdxBuffTrajectory = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTrajectory != NULL)
	{
		g_pVtxBuffTrajectory->Release();
		g_pVtxBuffTrajectory = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTrajectory(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTrajectory(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX	mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

												// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldTrajectory);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotTrajectory.y, g_rotTrajectory.x, g_rotTrajectory.z);
	D3DXMatrixMultiply(&g_mtxWorldTrajectory, &g_mtxWorldTrajectory, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posTrajectory.x, g_posTrajectory.y, g_posTrajectory.z);
	D3DXMatrixMultiply(&g_mtxWorldTrajectory, &g_mtxWorldTrajectory, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldTrajectory);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTrajectory, 0, sizeof(VERTEX_3D));

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffTrajectory);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureTrajectory);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_nNumVertexTrajectory, 0, g_nNumIndexTrajectory);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTrajectory(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffTrajectory, NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffTrajectory->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	pVtx[1].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	pVtx[2].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	pVtx[3].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);

	//�@���x�N�g��
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffTrajectory->Unlock();
}

//=============================================================================
// �Z�b�g����
//=============================================================================
void SetTrajectory(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	WORD *pIdx;									//�C���f�b�N�X�f�[�^�փ|�C���^

	PLAYER *pPlayer = GetPlayer();

	////���_���W�̐ݒ�
	//pVtx[(WIDE + 1) * nDepth + nWide].pos = pos;
	////�@���x�N�g��
	//pVtx[(WIDE + 1) * nDepth + nWide].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	////���_�J���[
	//pVtx[(WIDE + 1) * nDepth + nWide].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	////�e�N�X�`���`�ʂ̈ʒu
	//pVtx[(WIDE + 1) * nDepth + nWide].tex = D3DXVECTOR2(1.0f * nWide, 1.0f * nDepth);

	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffTrajectory->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^
	g_pIdxBuffTrajectory->Lock(0, 0, (void**)&pIdx, 0);

	pIdx[0] = g_nCount;
	pIdx[1] = g_nCount + 1;
	pIdx += 2;
	g_nCount += 2;

	//�C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^
	g_pIdxBuffTrajectory->Unlock();
}