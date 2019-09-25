//=============================================================================
//
// �|���S������ [meshorbit.cpp]
// Author : masayasu wakita
//
//=============================================================================
#include "meshorbit.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_ORBIT	(1)
#define ORBIT_DEPTH	1
#define ORBIT_WIDE 10

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;										//�ʒu
	D3DXVECTOR3 rot;										//��]
	D3DXMATRIX	mtxWorld;									//���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffOrbit;					//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	pIdxBuffMeshOrbit;				//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	int nNumVertexMeshOrbit;								//�����_��
	int nNumPolygonMeshOrbit;								//���|���S����
	bool bUse;												//�g�p���Ă��邩�ǂ���
} ORBIT;

typedef struct
{
	D3DXVECTOR3 pos;										//�ʒu
	D3DXVECTOR3 rot;										//��]
	D3DXMATRIX	mtxWorld;									//���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffOrbit;					//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	pIdxBuffMeshOrbit;				//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	int nNumVertexMeshOrbit;								//�����_��
	int nNumPolygonMeshOrbit;								//���|���S����
	bool bUse;												//�g�p���Ă��邩�ǂ���
	int nLife;												//����
} ORBITMTX;


//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureOrbit = NULL;			//�e�N�X�`���ւ̃|�C���^
ORBIT					g_aOrbit[MAX_ORBIT];				//��
ORBITMTX				g_aMtxMeshOrbit;					
int g_nNumIndexOrbit;									//�C���f�b�N�X��

//������
D3DXMATRIX g_mtxWorldMeshOrbit;
D3DXMATRIX g_mtxWorldMeshOrbitOld[ORBIT_WIDE];
//����
D3DXMATRIX g_mtxWorldWeapon;
D3DXMATRIX g_mtxWorldWeaponOld[ORBIT_WIDE];


//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexOrbit(LPDIRECT3DDEVICE9 pDevice);


//=============================================================================
// ����������
//=============================================================================
void InitOrbit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

												// �ʒu�E��]�̏����ݒ�
	for (int nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++)
	{
		g_aOrbit[nCntOrbit].bUse = false;
		g_aOrbit[nCntOrbit].pVtxBuffOrbit = NULL;
		g_aOrbit[nCntOrbit].pIdxBuffMeshOrbit = NULL;
		g_aOrbit[nCntOrbit].pos = D3DXVECTOR3(0.0f,5.0f, 0.0f);
		g_aOrbit[nCntOrbit].rot = D3DXVECTOR3(133.0f, 3.0f, 3.0f);

		//�����_��
		g_aOrbit[nCntOrbit].nNumVertexMeshOrbit = (ORBIT_DEPTH + 1) * (ORBIT_DEPTH + 1);

		//�C���f�b�N�X��
		g_nNumIndexOrbit = ((ORBIT_DEPTH + 1) * 2) * ORBIT_DEPTH + ((ORBIT_WIDE - 1) * 2);

		//���|���S����
		g_aOrbit[nCntOrbit].nNumPolygonMeshOrbit = ORBIT_DEPTH * ORBIT_WIDE * 2 + 4 * (ORBIT_DEPTH - 1);

		// ���_���̍쐬
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (ORBIT_DEPTH + 1) * (ORBIT_WIDE + 1), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_aOrbit[nCntOrbit].pVtxBuffOrbit, NULL);

		//�C���f�b�N�X�o�b�t�@�𐶐�
		pDevice->CreateIndexBuffer(sizeof(WORD) * ORBIT_DEPTH * ORBIT_WIDE * (2 + 4), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_aOrbit[nCntOrbit].pIdxBuffMeshOrbit, NULL);
	}

	g_aMtxMeshOrbit.pos = D3DXVECTOR3(28.0f, 3.0f, 0.0f);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/tex/dam.jp", &g_pTextureOrbit);

	//MakeVertexOrbit(pDevice);

	SetOrbit(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0));
}

//=============================================================================
// �I������
//=============================================================================
void UninitOrbit(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureOrbit != NULL)
	{
		g_pTextureOrbit->Release();
		g_pTextureOrbit = NULL;
	}

	for (int nCntBuff = 0; nCntBuff < MAX_ORBIT; nCntBuff++)
	{
		//�C���f�b�N�X�o�b�t�@�̊J��
		if (g_aOrbit[nCntBuff].pIdxBuffMeshOrbit != NULL)
		{
			g_aOrbit[nCntBuff].pIdxBuffMeshOrbit->Release();
			g_aOrbit[nCntBuff].pIdxBuffMeshOrbit = NULL;
		}

		// ���_�o�b�t�@�̊J��
		if (g_aOrbit[nCntBuff].pVtxBuffOrbit != NULL)
		{
			g_aOrbit[nCntBuff].pVtxBuffOrbit->Release();
			g_aOrbit[nCntBuff].pVtxBuffOrbit = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateOrbit(void)
{
	VERTEX_3D *pVtx;
	PLAYER *pPlayer;

	pPlayer = GetPlayer();

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_aOrbit[0].pVtxBuffOrbit->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(g_mtxWorldWeapon._41, g_mtxWorldWeapon._42, g_mtxWorldWeapon._43);
	pVtx[ORBIT_WIDE + 1].pos = D3DXVECTOR3(pPlayer->aModel[14].mtxWorldPlayer._41, pPlayer->aModel[14].mtxWorldPlayer._42, pPlayer->aModel[14].mtxWorldPlayer._43);

	for (int nCntOrbit = 0; nCntOrbit < ORBIT_WIDE; nCntOrbit++)
	{
		pVtx[nCntOrbit + 1].pos = D3DXVECTOR3(
			g_mtxWorldWeaponOld[nCntOrbit]._41,
			g_mtxWorldWeaponOld[nCntOrbit]._42,
			g_mtxWorldWeaponOld[nCntOrbit]._43);

		pVtx[nCntOrbit + ORBIT_WIDE + 2].pos = D3DXVECTOR3(
			g_mtxWorldMeshOrbitOld[nCntOrbit]._41,
			g_mtxWorldMeshOrbitOld[nCntOrbit]._42,
			g_mtxWorldMeshOrbitOld[nCntOrbit]._43);
	}


	for (int nCntObit = ORBIT_WIDE - 1; nCntObit > 0; nCntObit--)
	{
		g_mtxWorldMeshOrbitOld[nCntObit] = g_mtxWorldMeshOrbitOld[nCntObit - 1];
		g_mtxWorldWeaponOld[nCntObit] = g_mtxWorldWeaponOld[nCntObit - 1];
	}

	g_mtxWorldMeshOrbitOld[0] = pPlayer->aModel[14].mtxWorldPlayer;
	g_mtxWorldWeaponOld[0] = g_mtxWorldWeapon;

	//���_�f�[�^�̃A�����b�N
	g_aOrbit[0].pVtxBuffOrbit->Unlock();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawOrbit(void)
{
	PLAYER *pPlayer = GetPlayer();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX	mtxRot, mtxTrans, mtxView, mtxMeshRot, mtxMeshTrans;				//�v�Z�p�}�g���b�N�X

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// ����(�����)���J�����O����


	//pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �����_�[�X�e�[�g(���Z��������)
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	// ���[���h�}�g���b�N�X�̏�����
	for (int nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++)
	{
		if (g_aOrbit[nCntOrbit].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldMeshOrbit);

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldWeapon);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aOrbit[nCntOrbit].rot.y, g_aOrbit[nCntOrbit].rot.x, g_aOrbit[nCntOrbit].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldMeshOrbit, &g_mtxWorldMeshOrbit, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aOrbit[nCntOrbit].pos.x, g_aOrbit[nCntOrbit].pos.y, g_aOrbit[nCntOrbit].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldMeshOrbit, &g_mtxWorldMeshOrbit, &mtxTrans);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxMeshRot, g_aMtxMeshOrbit.rot.y, g_aMtxMeshOrbit.rot.x, g_aMtxMeshOrbit.rot.z);
			D3DXMatrixMultiply(&g_mtxWorldWeapon, &g_mtxWorldWeapon, &mtxMeshRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxMeshTrans, g_aMtxMeshOrbit.pos.x, g_aMtxMeshOrbit.pos.y, g_aMtxMeshOrbit.pos.z);
			D3DXMatrixMultiply(&g_mtxWorldWeapon, &g_mtxWorldWeapon, &mtxMeshTrans);

			D3DXMatrixMultiply(&g_mtxWorldWeapon, &g_mtxWorldWeapon, &pPlayer->aModel[3].mtxWorldPlayer);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshOrbit);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_aOrbit[nCntOrbit].pVtxBuffOrbit, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_aOrbit[nCntOrbit].pIdxBuffMeshOrbit);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetTexture(0, g_pTextureOrbit);

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aOrbit[nCntOrbit].nNumVertexMeshOrbit, 0, g_aOrbit[nCntOrbit].nNumPolygonMeshOrbit);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetTexture(0, NULL);
		}
	}

	// �����_�[�X�e�[�g(�ʏ�u�����h����)
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ����(�����)���J�����O����
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexOrbit(LPDIRECT3DDEVICE9 pDevice)
{
	WORD *pIdx;									//�C���f�b�N�X�f�[�^�փ|�C���^

												// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	for (int nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++)
	{
		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_aOrbit[nCntOrbit].pVtxBuffOrbit->Lock(0, 0, (void**)&pVtx, 0);

		for (int nDepth = 0; nDepth < ORBIT_DEPTH + 1; nDepth++)
		{
			for (int nWide = 0; nWide < ORBIT_WIDE + 1; nWide++)
			{
				//���_���W�̐ݒ�
				pVtx[(ORBIT_WIDE + 1) * nDepth + nWide].pos = D3DXVECTOR3((-50.0f * ORBIT_WIDE) + 100.0f * nWide, (50.0f * ORBIT_DEPTH) - 50.0f * nDepth, 0.0f);
				//�@��
				pVtx[(ORBIT_WIDE + 1) * nDepth + nWide].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
				//���_�J���[
				pVtx[(ORBIT_WIDE + 1) * nDepth + nWide].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}

		//���_�f�[�^�̃A�����b�N
		g_aOrbit[nCntOrbit].pVtxBuffOrbit->Unlock();

		//�C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^
		g_aOrbit[nCntOrbit].pIdxBuffMeshOrbit->Lock(0, 0, (void**)&pIdx, 0);

		for (int nCntY = 0; nCntY < ORBIT_DEPTH; nCntY++)
		{
			if (nCntY != 0)
			{
				pIdx[1] = (ORBIT_WIDE + 1) + nCntY * (ORBIT_WIDE + 1);
				pIdx += 2;
			}

			for (int nCntX = 0; nCntX < ORBIT_WIDE + 1; nCntX++)
			{
				pIdx[0] = (ORBIT_WIDE + 1) + nCntX + nCntY * (ORBIT_WIDE + 1);
				pIdx[1] = nCntX + nCntY * (ORBIT_WIDE + 1);
				pIdx += 2;
			}

			if (ORBIT_DEPTH > nCntY)
			{
				pIdx[0] = ORBIT_WIDE + nCntY * (ORBIT_WIDE + 1);
			}
		}

		//�C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^
		g_aOrbit[nCntOrbit].pIdxBuffMeshOrbit->Unlock();
	}
}

//=============================================================================
// �ǂ̍쐬
//=============================================================================
void SetOrbit(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	WORD *pIdx;									//�C���f�b�N�X�f�[�^�փ|�C���^

	for (int nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++)
	{
		if (!g_aOrbit[nCntOrbit].bUse)
		{
			g_aOrbit[nCntOrbit].pos = pos;
			g_aOrbit[nCntOrbit].rot = rot;

			//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			g_aOrbit[nCntOrbit].pVtxBuffOrbit->Lock(0, 0, (void**)&pVtx, 0);

			for (int nDepth = 0; nDepth < ORBIT_DEPTH + 1; nDepth++)
			{
				for (int nWide = 0; nWide < ORBIT_WIDE + 1; nWide++)
				{
					//���_���W�̐ݒ�
					pVtx[0].pos = D3DXVECTOR3((-100.0f * ORBIT_WIDE) / 2 + 100 * nWide, (100.0f * ORBIT_DEPTH) - 100 * nDepth, 0.0f);

					//�@���x�N�g��
					pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

					//���_�J���[
					pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);

					//�e�N�X�`���`�ʂ̈ʒu
					pVtx[0].tex = D3DXVECTOR2(1.0f * nWide, 1.0f * nDepth);

					pVtx++;
				}
			}

			//���_�f�[�^�̃A�����b�N
			g_aOrbit[nCntOrbit].pVtxBuffOrbit->Unlock();

			//�C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^
			g_aOrbit[nCntOrbit].pIdxBuffMeshOrbit->Lock(0, 0, (void**)&pIdx, 0);

			for (int nCntY = 0; nCntY < ORBIT_DEPTH; nCntY++)
			{
				if (nCntY != 0)
				{
					pIdx[0] = (ORBIT_WIDE + 1) + nCntY * (ORBIT_WIDE + 1);
					pIdx++;
				}

				for (int nCntX = 0; nCntX < ORBIT_WIDE + 1; nCntX++)
				{
					pIdx[0] = (ORBIT_WIDE + 1) + nCntX + nCntY * (ORBIT_WIDE + 1);
					pIdx[1] = nCntX + nCntY * (ORBIT_WIDE + 1);
					pIdx += 2;
				}

				if (ORBIT_DEPTH > nCntY + 1)
				{
					pIdx[0] = ORBIT_WIDE + nCntY * (ORBIT_WIDE + 1);
					pIdx++;

				}
			}

			//�C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^
			g_aOrbit[nCntOrbit].pIdxBuffMeshOrbit->Unlock();

			g_aOrbit[nCntOrbit].bUse = true;
			break;
		}
	}
}

//=============================================================================
// �O�Ղ̎擾
//=============================================================================
D3DXMATRIX *GetOrbit(void)
{
	return &g_mtxWorldWeapon;
}

//=============================================================================
// �O�Ղ̎莝����
//=============================================================================
D3DXMATRIX *GetHand(void)
{
	return &g_mtxWorldMeshOrbit;
}