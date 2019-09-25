//=============================================================================
//
// �|���S������ [wall.cpp]
// Author : masayasu wakita
//
//=============================================================================
#include "wall.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_WALL	(130)
#define WALL_DEPTH	7
#define WALL_WIDE 20

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;										//�ʒu
	D3DXVECTOR3 rot;										//��]
	D3DXMATRIX	mtxWorld;									//���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffWall;					//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	pIdxBuffMeshField;				//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	int nNumVertexMeshField;								//�����_��
	int nNumPolygonMeshField;								//���|���S����
	bool bUse;												//�g�p���Ă��邩�ǂ���
} WALL;

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureWall = NULL;			//�e�N�X�`���ւ̃|�C���^
WALL					g_aWall[MAX_WALL];				//��
int g_nNumIndexWall;									//�C���f�b�N�X��

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice);


//=============================================================================
// ����������
//=============================================================================
void InitWall (void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �ʒu�E��]�̏����ݒ�
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].bUse = false;
		g_aWall[nCntWall].pVtxBuffWall = NULL;
		g_aWall[nCntWall].pIdxBuffMeshField = NULL;
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�����_��
		g_aWall[nCntWall].nNumVertexMeshField = (WALL_DEPTH + 1) * (WALL_WIDE + 1);

		//�C���f�b�N�X��
		g_nNumIndexWall = ((WALL_DEPTH + 1) * 2) * WALL_DEPTH + ((WALL_WIDE - 1) * 2);

		//���|���S����
		g_aWall[nCntWall].nNumPolygonMeshField = WALL_DEPTH * WALL_WIDE * 2 + 4 * (WALL_DEPTH - 1);

		// ���_���̍쐬
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (WALL_DEPTH + 1) * (WALL_WIDE + 1), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_aWall[nCntWall].pVtxBuffWall, NULL);

		//�C���f�b�N�X�o�b�t�@�𐶐�
		pDevice->CreateIndexBuffer(sizeof(WORD) * WALL_DEPTH * WALL_WIDE * (2 + 4), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_aWall[nCntWall].pIdxBuffMeshField, NULL);
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/tex/FOG.png", &g_pTextureWall);

	//MakeVertexWall(pDevice);

	//SetWall(D3DXVECTOR3(-500.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0));
	//SetWall(D3DXVECTOR3(500.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));
	//SetWall(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	//SetWall(D3DXVECTOR3(500.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//=============================================================================
// �I������
//=============================================================================
void UninitWall(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	for (int nCntBuff = 0; nCntBuff < MAX_WALL; nCntBuff++)
	{
		//�C���f�b�N�X�o�b�t�@�̊J��
		if (g_aWall[nCntBuff].pIdxBuffMeshField != NULL)
		{
			g_aWall[nCntBuff].pIdxBuffMeshField->Release();
			g_aWall[nCntBuff].pIdxBuffMeshField = NULL;
		}

		// ���_�o�b�t�@�̊J��
		if (g_aWall[nCntBuff].pVtxBuffWall != NULL)
		{
			g_aWall[nCntBuff].pVtxBuffWall->Release();
			g_aWall[nCntBuff].pVtxBuffWall = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateWall(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX	mtxRot, mtxTrans, mtxView;				//�v�Z�p�}�g���b�N�X


	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_aWall[nCntWall].pVtxBuffWall, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_aWall[nCntWall].pIdxBuffMeshField);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall);

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aWall[nCntWall].nNumVertexMeshField, 0, g_aWall[nCntWall].nNumPolygonMeshField);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetTexture(0, NULL);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice)
{
	WORD *pIdx;									//�C���f�b�N�X�f�[�^�փ|�C���^

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_aWall[nCntWall].pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

		for (int nDepth = 0; nDepth < WALL_DEPTH + 1; nDepth++)
		{
			for (int nWide = 0; nWide < WALL_WIDE + 1; nWide++)
			{
				//���_���W�̐ݒ�
				pVtx[(WALL_WIDE + 1) * nDepth + nWide].pos = D3DXVECTOR3((-50.0f * WALL_WIDE) + 100.0f * nWide, (50.0f * WALL_DEPTH) - 50.0f * nDepth, 0.0f);
				//�@��
				pVtx[(WALL_WIDE + 1) * nDepth + nWide].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
				//���_�J���[
				pVtx[(WALL_WIDE + 1) * nDepth + nWide].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}

		//���_�f�[�^�̃A�����b�N
		g_aWall[nCntWall].pVtxBuffWall->Unlock();

		//�C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^
		g_aWall[nCntWall].pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

		for (int nCntY = 0; nCntY < WALL_DEPTH; nCntY++)
		{
			if (nCntY != 0)
			{
				pIdx[1] = (WALL_WIDE + 1) + nCntY * (WALL_WIDE + 1);
				pIdx += 2;
			}

			for (int nCntX = 0; nCntX < WALL_WIDE + 1; nCntX++)
			{
				pIdx[0] = (WALL_WIDE + 1) + nCntX + nCntY * (WALL_WIDE + 1);
				pIdx[1] = nCntX + nCntY * (WALL_WIDE + 1);
				pIdx += 2;
			}

			if (WALL_DEPTH > nCntY)
			{
				pIdx[0] = WALL_WIDE + nCntY * (WALL_WIDE + 1);
			}
		}

		//�C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^
		g_aWall[nCntWall].pIdxBuffMeshField->Unlock();
	}
}

//=============================================================================
// �ǂ̍쐬
//=============================================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	WORD *pIdx;									//�C���f�b�N�X�f�[�^�փ|�C���^

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (!g_aWall[nCntWall].bUse)
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;

			//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			g_aWall[nCntWall].pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

			for (int nDepth = 0; nDepth < WALL_DEPTH + 1; nDepth++)
			{
				for (int nWide = 0; nWide < WALL_WIDE + 1; nWide++)
				{
					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3((-100.0f * WALL_WIDE) / 2 + 100 * nWide, (100.0f * WALL_DEPTH) - 100 * nDepth, 0.0f);

					//�@���x�N�g��
					pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

					//���_�J���[
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					//�e�N�X�`���`�ʂ̈ʒu
					pVtx[0].tex = D3DXVECTOR2(1.0f * nWide, 1.0f * nDepth);

					pVtx++;
				}
			}

			//���_�f�[�^�̃A�����b�N
			g_aWall[nCntWall].pVtxBuffWall->Unlock();

			//�C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^
			g_aWall[nCntWall].pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

			for (int nCntY = 0; nCntY < WALL_DEPTH; nCntY++)
			{
				if (nCntY != 0)
				{
					pIdx[0] = (WALL_WIDE + 1) + nCntY * (WALL_WIDE + 1);
					pIdx++;
				}

				for (int nCntX = 0; nCntX < WALL_WIDE + 1; nCntX++)
				{
					pIdx[0] = (WALL_WIDE + 1) + nCntX + nCntY * (WALL_WIDE + 1);
					pIdx[1] = nCntX + nCntY * (WALL_WIDE + 1);
					pIdx += 2;
				}

				if (WALL_DEPTH > nCntY + 1)
				{
					pIdx[0] = WALL_WIDE + nCntY * (WALL_WIDE + 1);
					pIdx++;

				}
			}

			//�C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^
			g_aWall[nCntWall].pIdxBuffMeshField->Unlock();

			g_aWall[nCntWall].bUse = true;
			break;
		}
	}
}