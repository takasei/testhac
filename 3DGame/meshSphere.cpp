//=============================================================================
//
// �|���S������ [polygon.cpp]
// Author : masayasu wakita
//
//=============================================================================
#include "meshSphere.h"
#include "input.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define RADIUS	120										//���a
#define DIVISION 20										//����
#define DEPTH 	20										//��

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexMeshSphere(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureMeshSphere = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshSphere = NULL;			//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9	g_pIdxBuffMeshSphere = NULL;			//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^

D3DXVECTOR3				g_posMeshSphere;						//�|���S���̈ʒu
D3DXVECTOR3				g_rotMeshSphere;						//�|���S���̌���(��])
D3DXMATRIX				g_mtxWorldMeshSphere;				//���[���h�}�g���b�N�X

int g_nNumVertexMeshSphere;									//�����_��
int g_nNumIndexMeshSphere;									//�C���f�b�N�X��
int g_nNumPolygonMeshSphere;									//���|���S����

//=============================================================================
// ����������
//=============================================================================
void InitMeshSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	WORD *pIdx;									//�C���f�b�N�X�f�[�^�փ|�C���^

												// �ʒu�E��]�̏����ݒ�
	g_posMeshSphere = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	g_rotMeshSphere = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�����_��
	g_nNumVertexMeshSphere = (DIVISION + 1) + (DEPTH + 1) * (DIVISION + 1);

	//�C���f�b�N�X��
	g_nNumIndexMeshSphere = (DIVISION + 1) + ((DEPTH + 1) * 2) * DEPTH + ((DIVISION - 1) * 2);

	//���|���S����
	g_nNumPolygonMeshSphere = (DIVISION - 1) + (DEPTH * DIVISION * 2 + 4 * (DEPTH - 1));

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/tex/wood_Seamless.jg", &g_pTextureMeshSphere);

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nNumVertexMeshSphere, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffMeshSphere, NULL);

	//�C���f�b�N�X�o�b�t�@�𐶐�
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_nNumIndexMeshSphere, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffMeshSphere, NULL);

	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffMeshSphere->Lock(0, 0, (void**)&pVtx, 0);

	//================= �~�̒��S ===================//
	pVtx[0].pos = g_posMeshSphere;

	//�@���x�N�g��
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���`�ʂ̈ʒu
	pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);

	//pVtx[1].pos = D3DXVECTOR3(40.0f, 25.0f, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(0.0f, 25.0f, 40.0f);
	//pVtx[3].pos = D3DXVECTOR3(-40.0f, 25.0f, 0.0f);
	//pVtx[4].pos = D3DXVECTOR3(0.0f, 25.0f, -40.0f);
	//pVtx[5].pos = D3DXVECTOR3(40.0f, 25.0f, 0.0f);
	pVtx++;

	//================= �~���`�� ===================//
	for (int nDepth = 0; nDepth < DIVISION; nDepth++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(sinf(D3DX_PI + 6.28f + ((6.28f / (DIVISION - 1)) * nDepth)) * RADIUS, 5.0f, cosf(D3DX_PI + 6.28f + ((6.28f / (DIVISION - 1)) * nDepth)) * RADIUS);

		//�@���x�N�g��
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���`�ʂ̈ʒu
		pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f * nDepth);

		pVtx++;
	}

	//for (int nDepth = 0; nDepth < 2; nDepth++)
	//{
	//	for (int nWide = 0; nWide < DIVISION; nWide++)
	//	{
	//		//���_���W�̐ݒ�
	//		pVtx[0].pos = D3DXVECTOR3((-100.0f * DIVISION) / 2 + 100 * nWide, (100.0f * DIVISION) - 100 * nDepth, 0.0f);

	//		//�@���x�N�g��
	//		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//		//���_�J���[
	//		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//		//�e�N�X�`���`�ʂ̈ʒu
	//		pVtx[0].tex = D3DXVECTOR2(1.0f * nWide, 1.0f * nDepth);

	//		pVtx++;
	//	}
	//}

	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffMeshSphere->Unlock();

	//�C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^
	g_pIdxBuffMeshSphere->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntY = 0; nCntY < g_nNumVertexMeshSphere; nCntY++)
	{
		pIdx[0] = nCntY;
		pIdx++;
	}


	//for (int nCntY = 0; nCntY < 2; nCntY++)
	//{
	//	if (nCntY != 0)
	//	{
	//		pIdx[0] = (DIVISION + 1) + nCntY * (DIVISION + 1);
	//		pIdx++;
	//	}

	//	for (int nCntX = 0; nCntX < DIVISION + 1; nCntX++)
	//	{
	//		pIdx[0] = (DIVISION + 1) + nCntX + nCntY * (DIVISION + 1);
	//		pIdx[1] = nCntX + nCntY * (DIVISION + 1);
	//		pIdx += 2;
	//	}

	//	if (DEPTH > nCntY + 1)
	//	{
	//		pIdx[0] = DIVISION + nCntY * (DIVISION + 1);
	//		pIdx++;

	//	}
	//}

	//�C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^
	g_pIdxBuffMeshSphere->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshSphere(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureMeshSphere != NULL)
	{
		g_pTextureMeshSphere->Release();
		g_pTextureMeshSphere = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshSphere != NULL)
	{
		g_pIdxBuffMeshSphere->Release();
		g_pIdxBuffMeshSphere = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshSphere != NULL)
	{
		g_pVtxBuffMeshSphere->Release();
		g_pVtxBuffMeshSphere = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshSphere(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX	mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

												// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshSphere);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshSphere.y, g_rotMeshSphere.x, g_rotMeshSphere.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshSphere, &g_mtxWorldMeshSphere, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshSphere.x, g_posMeshSphere.y, g_posMeshSphere.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshSphere, &g_mtxWorldMeshSphere, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshSphere);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshSphere, 0, sizeof(VERTEX_3D));

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshSphere);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshSphere);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN, 0, 0, (DIVISION + 1), 0, (DIVISION + 1));

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN, (DIVISION + 1), (DIVISION + 1), (DIVISION + 1), 0, (DIVISION + 1));

	//// �|���S���̕`��
	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, (DIVISION + 1), (DIVISION + 1), g_nNumVertexMeshSphere, (DIVISION + 1) + 1, g_nNumPolygonMeshSphere);

	// //�|���S���̕`��
	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN, 0, 0, g_nNumVertexMeshSphere, 0, g_nNumPolygonMeshSphere);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMeshSphere(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffMeshSphere, NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffMeshSphere->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffMeshSphere->Unlock();
}

