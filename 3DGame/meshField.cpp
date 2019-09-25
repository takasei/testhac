//=============================================================================
//
// �|���S������ [polygon.cpp]
// Author : masayasu wakita
//
//=============================================================================
#include "polygon.h"
#include "input.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define DEPTH 	50											//���s��
#define WIDE 50												//��

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureMeshField = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;			//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffMeshField = NULL;			//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

D3DXVECTOR2				g_tex;

D3DXVECTOR3				g_posMeshField;						//�|���S���̈ʒu
D3DXVECTOR3				g_rotMeshField;						//�|���S���̌���(��])
D3DXMATRIX				g_mtxWorldMeshField;				//���[���h�}�g���b�N�X

int g_nNumVertexMeshField;									//�����_��
int g_nNumIndexMeshField;									//�C���f�b�N�X��
int g_nNumPolygonMeshField;									//���|���S����

//=============================================================================
// ����������
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	WORD *pIdx;									//�C���f�b�N�X�f�[�^�փ|�C���^

	g_tex = D3DXVECTOR2(1.0f, 1.0f);

												// �ʒu�E��]�̏����ݒ�
	g_posMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�����_��
	g_nNumVertexMeshField = (DEPTH + 1) * (WIDE + 1);

	//�C���f�b�N�X��
	g_nNumIndexMeshField = ((DEPTH + 1) *  2) * DEPTH + ((WIDE - 1) * 2);

	//���|���S����
	g_nNumPolygonMeshField = DEPTH * WIDE * 2 + 4 * (DEPTH - 1);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/tex/FOG.png", &g_pTextureMeshField);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (DEPTH + 1) * (WIDE + 1), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffMeshField, NULL);

	//�C���f�b�N�X�o�b�t�@�𐶐�
	pDevice->CreateIndexBuffer(sizeof(WORD) * DEPTH * WIDE * (2 + 4), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffMeshField, NULL);

	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	for (int nDepth = 0; nDepth < DEPTH + 1; nDepth++)
	{
		for (int nWide = 0; nWide < WIDE + 1; nWide++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3((-100.0f * WIDE) / 2 + 100 * nWide, 0.0f, (50.0f * DEPTH) - 100 * nDepth);

			//�@���x�N�g��
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`���`�ʂ̈ʒu
			pVtx[0].tex = D3DXVECTOR2(1.0f * nWide, 1.0f * nDepth);

			pVtx++;
		}
	}

	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffMeshField->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntY = 0; nCntY < DEPTH; nCntY++)
	{
		if (nCntY != 0)
		{
			pIdx[0] = (WIDE + 1) + nCntY * (WIDE + 1);
			pIdx++;
		}

		for (int nCntX = 0; nCntX < WIDE + 1; nCntX++)
		{
			pIdx[0] = (WIDE + 1) + nCntX + nCntY * (WIDE + 1);
			pIdx[1] = nCntX + nCntY * (WIDE + 1);
			pIdx += 2;
		}

		if (DEPTH > nCntY + 1)
		{
			pIdx[0] = WIDE + nCntY * (WIDE + 1);
			pIdx++;

		}
	}

	//�C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^
	g_pIdxBuffMeshField->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshField(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshField(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX	mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

												// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshField);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshField.x, g_posMeshField.y, g_posMeshField.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshField, &g_mtxWorldMeshField, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshField);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshField);

	//// �|���S���̕`��
	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_nNumVertexMeshField, 0, g_nNumPolygonMeshField);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffMeshField, NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffMeshField->Unlock();
}

