//=============================================================================
//
// ���f������ [model.cpp]
// Author : 
//
//=============================================================================
#include "model.h"
#include "input.h"
#include "camera.h"
#include "game.h"
#include "shadow.h"
#include "result.h"
#include "effect.h"
#include "tutorial.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_ITEM 128						//�A�C�e���̍ő吔

//�ʏ�̔z�u���
#define	NORMAL_WEDTH	6					//�ʏ�z�u�̍ő吔
#define	NORMAL_DEPTH	4					//�ʏ�z�u�̍ő吔

//�E�H�[���̔z�u���
#define WALL_WEDTH		12					//�E�H�[���̍ő吔
#define WALL_DEPTH		4					//�E�H�[���̍���

//�T�[�N���̔z�u���
#define CIRCLE_MAX		4					//�T�[�N���̍ő吔
//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{
	LPDIRECT3DTEXTURE9		pTextureModel = NULL;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffModel = NULL;		//���_�o�b�t�@�ւ̃|�C���^
	LPD3DXMESH		pMeshModel = NULL;				//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	pBuffMatModel = NULL;				//�}�e���A�����ւ̃|�C���^
	DWORD			nNumMatModel = 0;					//�}�e���A�����̐�
	D3DXVECTOR3		vtxMinModel;						//�ŏ�
	D3DXVECTOR3		vtxMaxModel;						//�ő�
} MODEL;

typedef struct
{
	D3DXVECTOR3		posModel;							//���f���̈ʒu
	D3DXVECTOR3		moveModel;							//���f���̈ړ���
	D3DXVECTOR3		rotModel;							//���f���̌���(��])
	D3DXVECTOR3		rotDestModel;						//���f���̍ő��]
	D3DXMATRIX		mtxWorldModel;						//���f���̃��[���h�}�g���b�N�X
	int nIdx;											//�e��ID
	int nCntMax;
	ITEMTYPE type;											//�A�C�e���̃^�C�v
	bool bUse;											//�g�p����Ă��邩�ǂ���
} ITEM;

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
MODEL g_aModel[ITEMTYPE_MAX];
ITEM g_aItem[MAX_ITEM];

int g_nLayout;

//=============================================================================
// ����������
//=============================================================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//======== ������ ========//
	bool bFlip = false;
	g_nLayout = 0;

	for (int nCntReset = 0; nCntReset < MAX_ITEM; nCntReset++)
	{
		// �ʒu�E�����̏����ݒ�
		g_aItem[nCntReset].posModel = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
		g_aItem[nCntReset].moveModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntReset].rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	
	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/model/���ݑ�.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[ITEMTYPE_CLOUD_1].pBuffMatModel,
		NULL,
		&g_aModel[ITEMTYPE_CLOUD_1].nNumMatModel,
		&g_aModel[ITEMTYPE_CLOUD_1].pMeshModel);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/model/���ݑ�.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[ITEMTYPE_CLOUD_2].pBuffMatModel,
		NULL,
		&g_aModel[ITEMTYPE_CLOUD_2].nNumMatModel,
		&g_aModel[ITEMTYPE_CLOUD_2].pMeshModel);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/model/���ݑ�.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aModel[ITEMTYPE_CLOUD_3].pBuffMatModel,
		NULL,
		&g_aModel[ITEMTYPE_CLOUD_3].nNumMatModel,
		&g_aModel[ITEMTYPE_CLOUD_3].pMeshModel);

	//���f���̒��_���W�̍ő�E�ŏ��̐ݒ�
	int nNumVertices;			//���_��
	DWORD sizeFVF;				//���_�t�H�[�}�b�g
	BYTE	*pVertexBuffer;		//���_�o�b�t�@�ւ̃|�C���^

	for (int nCntType = 0; nCntType < ITEMTYPE_MAX; nCntType++)
	{
		//�ŏ��E�ő�̃��Z�b�g
		g_aModel[nCntType].vtxMinModel = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
		g_aModel[nCntType].vtxMaxModel = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);

		//���_�����擾
		nNumVertices = g_aModel[nCntType].pMeshModel->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_aModel[nCntType].pMeshModel->GetFVF());

		//���_�o�b�t�@�����b�N
		g_aModel[nCntType].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

		for (int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++)
		{
			D3DXVECTOR3	vtx = *(D3DXVECTOR3*)pVertexBuffer;

			//���ׂĂ̒��_�����r���čŏ��ő�𔲂��o��
			if (g_aModel[nCntType].vtxMinModel.x > vtx.x)
			{
				g_aModel[nCntType].vtxMinModel.x = vtx.x;
			}
			if (g_aModel[nCntType].vtxMinModel.y > vtx.y)
			{
				g_aModel[nCntType].vtxMinModel.y = vtx.y;
			}
			if (g_aModel[nCntType].vtxMinModel.z > vtx.z)
			{
				g_aModel[nCntType].vtxMinModel.z = vtx.z;
			}

			//�ŏ��l�����߂�
			if (g_aModel[nCntType].vtxMaxModel.x < vtx.x)
			{
				g_aModel[nCntType].vtxMaxModel.x = vtx.x;
			}
			if (g_aModel[nCntType].vtxMaxModel.y < vtx.y)
			{
				g_aModel[nCntType].vtxMaxModel.y = vtx.y;
			}
			if (g_aModel[nCntType].vtxMaxModel.z < vtx.z)
			{
				g_aModel[nCntType].vtxMaxModel.z = vtx.z;
			}

			pVertexBuffer += sizeFVF;			//�T�C�Y���̃|�C���^��i�߂�
		}

		//���_�o�b�t�@���A�����b�N
		g_aModel[nCntType].pMeshModel->UnlockVertexBuffer();
	}
	SetStage(0);
}

//=============================================================================
// �I������
//=============================================================================
void UninitModel(void)
{
	for (int nCntModel = 0; nCntModel < ITEMTYPE_MAX; nCntModel++)
	{
		// ���b�V���̊J��
		if (g_aModel[nCntModel].pMeshModel != NULL)
		{
			g_aModel[nCntModel].pMeshModel->Release();
			g_aModel[nCntModel].pMeshModel = NULL;
		}

		// �}�e���A���̊J��
		if (g_aModel[nCntModel].pBuffMatModel != NULL)
		{
			g_aModel[nCntModel].pBuffMatModel->Release();
			g_aModel[nCntModel].pBuffMatModel = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModel(void)
{
	//if (GetMode() == MODE_GAME)
	//{
	//	for (int nCntModel = 0; nCntModel < MAX_ITEM; nCntModel++)
	//	{
	//		if (g_aItem[nCntModel].bUse)
	//		{
	//			switch (g_aItem[nCntModel].type)
	//			{
	//			case ITEMTYPE_CLOUD_3:
	//				SetEffect(g_aItem[nCntModel].posModel, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), g_aItem[nCntModel].rotModel, true);
	//				break;
	//			}
	//		}
	//	}
	//}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX		mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DXMATERIAL	*pMat;							//���݂̃}�e���A���ۑ��p
	D3DMATERIAL9	matDef;							//�}�e���A���f�[�^�ւ̃|�C���^
	
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aItem[nCntItem].mtxWorldModel);

			// �X�P�[���𔽉f


			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aItem[nCntItem].rotModel.y, g_aItem[nCntItem].rotModel.x, g_aItem[nCntItem].rotModel.z);
			D3DXMatrixMultiply(&g_aItem[nCntItem].mtxWorldModel, &g_aItem[nCntItem].mtxWorldModel, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aItem[nCntItem].posModel.x, g_aItem[nCntItem].posModel.y, g_aItem[nCntItem].posModel.z);
			D3DXMatrixMultiply(&g_aItem[nCntItem].mtxWorldModel, &g_aItem[nCntItem].mtxWorldModel, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aItem[nCntItem].mtxWorldModel);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aModel[g_aItem[nCntItem].type].pBuffMatModel->GetBufferPointer();


			for (int nCntMat = 0; nCntMat < (int)g_aModel[g_aItem[nCntItem].type].nNumMatModel; nCntMat++)
			{
				
				//// �}�e���A���̐ݒ�
				//pDevice->SetMaterial(&pMat[nCntMat].pTextureFilename);

				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �`��
				g_aModel[g_aItem[nCntItem].type].pMeshModel->DrawSubset(nCntMat);
			}

			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=============================================================================
// ���f���̓����蔻��
//=============================================================================
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	bool bRand = false;

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse)
		{
			//�㉺����
			if ((pPosOld->y >= g_aModel[g_aItem[nCntItem].type].vtxMinModel.y + g_aItem[nCntItem].posModel.y) &&
				(pPosOld->y <= g_aModel[g_aItem[nCntItem].type].vtxMaxModel.y + g_aItem[nCntItem].posModel.y))
			{
				//���E����
				if ((pPosOld->x >= g_aModel[g_aItem[nCntItem].type].vtxMinModel.x + g_aItem[nCntItem].posModel.x) &&
					(pPosOld->x <= g_aModel[g_aItem[nCntItem].type].vtxMaxModel.x + g_aItem[nCntItem].posModel.x))
				{
					//�v���C���[����
					if ((pPos->z >= g_aModel[g_aItem[nCntItem].type].vtxMinModel.z + g_aItem[nCntItem].posModel.z) &&
						(pPosOld->z <= g_aModel[g_aItem[nCntItem].type].vtxMinModel.z + g_aItem[nCntItem].posModel.z))
					{
						pPos->z = g_aModel[g_aItem[nCntItem].type].vtxMinModel.z + g_aItem[nCntItem].posModel.z;
						pMove->z = 0.0f;
						////�A�C�e���̓����蔻��
						//if (g_aItem[nCntItem].type == ITEMTYPE_CLOUD_3)
						//{
						//	g_aItem[nCntItem].bUse = false;
						//	//DeleteShadow(g_aItem[nCntItem].nIdx);
						//	SetResultState(RESULTSTATE_CLEAR);
						//	SetGameState(GAMESTATE_END);
						//}
					}
					else if ((pPos->z <= g_aModel[g_aItem[nCntItem].type].vtxMaxModel.z + g_aItem[nCntItem].posModel.z) &&
						(pPosOld->z >= g_aModel[g_aItem[nCntItem].type].vtxMaxModel.z + g_aItem[nCntItem].posModel.z))
					{
						pPos->z = g_aModel[g_aItem[nCntItem].type].vtxMaxModel.z + g_aItem[nCntItem].posModel.z;
						pMove->z = 0.0f;

						////�A�C�e���̓����蔻��
						//if (g_aItem[nCntItem].type == ITEMTYPE_CLOUD_3)
						//{
						//	g_aItem[nCntItem].bUse = false;
						//	//DeleteShadow(g_aItem[nCntItem].nIdx);
						//	SetResultState(RESULTSTATE_CLEAR);
						//	SetGameState(GAMESTATE_END);
						//}
					}
				}
			}
			//���E����
			if ((pPosOld->x >= g_aModel[g_aItem[nCntItem].type].vtxMinModel.x + g_aItem[nCntItem].posModel.x) &&
				(pPosOld->x <= g_aModel[g_aItem[nCntItem].type].vtxMaxModel.x + g_aItem[nCntItem].posModel.x))
			{
				//���E����
				if ((pPosOld->z >= g_aModel[g_aItem[nCntItem].type].vtxMinModel.z + g_aItem[nCntItem].posModel.z) &&
					(pPosOld->z <= g_aModel[g_aItem[nCntItem].type].vtxMaxModel.z + g_aItem[nCntItem].posModel.z))
				{
					//�v���C���[�̔���
					if ((pPos->y >= g_aModel[g_aItem[nCntItem].type].vtxMinModel.y + g_aItem[nCntItem].posModel.y) &&
						(pPosOld->y <= g_aModel[g_aItem[nCntItem].type].vtxMinModel.y + g_aItem[nCntItem].posModel.y))
					{
						pPos->y = g_aModel[g_aItem[nCntItem].type].vtxMinModel.y + g_aItem[nCntItem].posModel.y;
					}
					else if (pPos->y <= g_aModel[g_aItem[nCntItem].type].vtxMaxModel.y + g_aItem[nCntItem].posModel.y &&
						(pPosOld->y >= g_aModel[g_aItem[nCntItem].type].vtxMaxModel.y + g_aItem[nCntItem].posModel.y))
					{
						pPos->y = g_aModel[g_aItem[nCntItem].type].vtxMaxModel.y + g_aItem[nCntItem].posModel.y;
						pMove->y = 0.0f;
						bRand = true;
					}
				}
			}
			//�㉺����
			if ((pPosOld->y >= g_aModel[g_aItem[nCntItem].type].vtxMinModel.y + g_aItem[nCntItem].posModel.y) &&
				(pPosOld->y <= g_aModel[g_aItem[nCntItem].type].vtxMaxModel.y + g_aItem[nCntItem].posModel.y))
			{
				//���E����
				if ((pPosOld->z >= g_aModel[g_aItem[nCntItem].type].vtxMinModel.z + g_aItem[nCntItem].posModel.z) &&
					(pPosOld->z <= g_aModel[g_aItem[nCntItem].type].vtxMaxModel.z + g_aItem[nCntItem].posModel.z))
				{
					if (pPos->x >= g_aModel[g_aItem[nCntItem].type].vtxMinModel.x + g_aItem[nCntItem].posModel.x &&
						(pPosOld->x <= g_aModel[g_aItem[nCntItem].type].vtxMinModel.x + g_aItem[nCntItem].posModel.x))
					{
						pPos->x = g_aModel[g_aItem[nCntItem].type].vtxMinModel.x + g_aItem[nCntItem].posModel.x;
						pMove->x = 0.0f;

						/*if (g_aItem[nCntItem].type == ITEMTYPE_CLOUD_3)
						{
							g_aItem[nCntItem].bUse = false;
							DeleteShadow(g_aItem[nCntItem].nIdx);
							SetResultState(RESULTSTATE_CLEAR);
							SetGameState(GAMESTATE_END);
						}*/
					}
					else if (pPos->x <= g_aModel[g_aItem[nCntItem].type].vtxMaxModel.x + g_aItem[nCntItem].posModel.x &&
						(pPosOld->x >= g_aModel[g_aItem[nCntItem].type].vtxMaxModel.x + g_aItem[nCntItem].posModel.x))
					{
						pPos->x = g_aModel[g_aItem[nCntItem].type].vtxMaxModel.x + g_aItem[nCntItem].posModel.x;
						pMove->x = 0.0f;

					/*	if (g_aItem[nCntItem].type == ITEMTYPE_CLOUD_3)
						{
							g_aItem[nCntItem].bUse = false;
							DeleteShadow(g_aItem[nCntItem].nIdx);
							SetResultState(RESULTSTATE_CLEAR);
							SetGameState(GAMESTATE_END);
						}*/
					}
				}
			}

			if (pPos->y < 0)
			{
				pPos->y = 0.0f;
				pPosOld->y = 0.0f;
				pMove->y = 0.0f;
				bRand = true;
			}
		}
	}
	return bRand;
}

//=============================================================================
// ���f���̏o��
//=============================================================================
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 move, ITEMTYPE type,int nCntMax)
{
	//���̎g���Ă��Ȃ��ꏊ����������
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (!g_aItem[nCntItem].bUse)
		{
			//���̊i�[�y�юg�p���ɐݒ�
			g_aItem[nCntItem].posModel = pos;
			g_aItem[nCntItem].moveModel = move;
			g_aItem[nCntItem].rotModel = rot;
			g_aItem[nCntItem].nCntMax = nCntMax;
			g_aItem[nCntItem].type = type;
			g_aItem[nCntItem].bUse = true;

			//==========================�e=========================//
			////���̃A�C�e�������������Ƃ�
			//if (g_aItem[nCntItem].type == ITEMTYPE_CLOUD_1)
			//{
			//	//�e�̍쐬
			//	g_aItem[nCntItem].nIdx = SetShadow(g_aItem[nCntItem].posModel, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(65.0f, 65.0f, 65.0f));
			//}

			////���̃A�C�e�����֎q�������Ƃ�
			//else if (g_aItem[nCntItem].type == ITEMTYPE_CLOUD_2)
			//{
			//	//�e�̍쐬
			//	g_aItem[nCntItem].nIdx = SetShadow(g_aItem[nCntItem].posModel, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 50.0f));
			//}

			////���̃A�C�e�����Ԃ�������
			//else if (g_aItem[nCntItem].type == ITEMTYPE_CLOUD_3)
			//{
			//	g_aItem[nCntItem].nIdx = SetShadow(D3DXVECTOR3(430.0f, 75.5f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(15.0f, 10.0f, 15.0f));

			//}
			break;
		}
	}
}

////=============================================================================
//// ���f���z�u�̎��
////=============================================================================
//void SetLayout(LAYOUTTYPE nType)
//{
//	//���̎g���Ă��Ȃ��ꏊ����������
//	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
//	{
//		if (g_aItem[nCntItem].bUse)
//		{
//			//���̊i�[�y�юg�p���ɐݒ�
//			g_aItem[nCntItem].posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			g_aItem[nCntItem].rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//			g_aItem[nCntItem].nType = ITEMTYPE_NONE;
//			g_aItem[nCntItem].bUse = false;
//			DeleteShadow(g_aItem[nCntItem].nIdx);
//		}
//	}
//
//	//���Ԋu�̊��֎q�z�u
//	if (nType == LAYOUTTYPE_NORMAL)
//	{
//		//���ƈ֎q
//		for (int nCntDepth = 0; nCntDepth < NORMAL_DEPTH; nCntDepth++)
//		{
//			for (int nCntWidth = 0; nCntWidth < NORMAL_WEDTH; nCntWidth++)
//			{
//				SetModel(ITEMTYPE_CLOUD_1, D3DXVECTOR3(430.0f - (170 * nCntWidth), 0.0f, -250.0f + (170 * nCntDepth)), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
//				SetModel(ITEMTYPE_CLOUD_2, D3DXVECTOR3(430.0f - (170 * nCntWidth), 0.0f, -230.0f + (170 * nCntDepth)), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
//			}
//		}
//
//		//���̉�ʂ��^�C�g����ʂ������Ƃ�
//		if (GetMode() == MODE_TITLE)
//		{
//			SetModel(ITEMTYPE_CLOUD_3, D3DXVECTOR3(430.0f, 80.0f, -250.0f), D3DXVECTOR3(-1.0f, 1.0f, 0.0f));
//
//			//�e�̍쐬
//			SetShadow(D3DXVECTOR3(430.0f, 75.5f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(15.0f, 10.0f, 15.0f));
//		}
//
//		//���݂̃��C�A�E�g�^�C�v�̕ύX
//		g_nLayout = LAYOUTTYPE_NORMAL;
//	}
//	else if (nType == LAYOUTTYPE_WALL)
//	{
//		//���E�H�[��
//		for (int nCntWidth = 0; nCntWidth < WALL_WEDTH; nCntWidth++)
//		{
//			for (int nCntWall = 0; nCntWall < WALL_DEPTH; nCntWall++)
//			{
//				//����
//				if (nCntWall == 0)
//				{
//					//���f���̔z�u(�ǂ̔z�u�ʒu�y���[�z - (���Ɗ��̊Ԋu * ��), 0.0f, 0.0f)
//					SetModel(ITEMTYPE_CLOUD_1, D3DXVECTOR3(450.0f - (78 * nCntWidth), 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
//				}
//				//���ڈȍ~
//				else
//				{
//					//���f���̔z�u(�ǂ̔z�u�ʒu�y���[�z - (���Ɗ��̊Ԋu * ��), 0.0f, 0.0f)
//					SetModel(ITEMTYPE_CLOUD_1, D3DXVECTOR3(450.0f - (78 * nCntWidth), 150.0f + (75 * (nCntWall - 1)), 0.0f), D3DXVECTOR3(3.14f, 0.0f, 0.0f));
//				}
//			}
//		}
//
//		//���݂̃��C�A�E�g�^�C�v�̕ύX
//		g_nLayout = LAYOUTTYPE_WALL;
//	}
//	else if (nType == LAYOUTTYPE_CIRCLE)
//	{
//		//�~
//		for (int nCntDepth = 0; nCntDepth < CIRCLE_MAX; nCntDepth++)
//		{
//			//���ڋy�эŌ�̗�
//			if (nCntDepth % CIRCLE_MAX == 0 || nCntDepth == CIRCLE_MAX - 1)
//			{
//				for (int nCntWidth = 0; nCntWidth < CIRCLE_MAX; nCntWidth++)
//				{
//					SetModel(ITEMTYPE_CLOUD_1, D3DXVECTOR3(430.0f - (170 * (nCntWidth + 1)), -0.5f, -250.0f + (170 * nCntDepth)), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
//				}
//			}
//			else
//			{
//				for (int nCount = 0; nCount < 2; nCount++)
//				{
//					SetModel(ITEMTYPE_CLOUD_1, D3DXVECTOR3(260.0f - 170 * (CIRCLE_MAX - 1) * nCount, 0.0f, -250.0f + 170 * nCntDepth), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
//				}
//			}
//		}
//
//		//���݂̃��C�A�E�g�^�C�v�̕ύX
//		g_nLayout = LAYOUTTYPE_CIRCLE;
//	}
//	else if (nType == LAYOUTTYPE_GROUP)
//	{
//		SetModel(ITEMTYPE_CLOUD_1, D3DXVECTOR3(200.0f, 0.0f, -220.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
//		SetModel(ITEMTYPE_CLOUD_1, D3DXVECTOR3(148.0f, 0.0f, -220.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
//		SetModel(ITEMTYPE_CLOUD_1, D3DXVECTOR3(200.0f, 0.0f, -145.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
//		SetModel(ITEMTYPE_CLOUD_1, D3DXVECTOR3(148.0f, 0.0f, -145.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
//
//		//���݂̃��C�A�E�g�^�C�v�̕ύX
//		g_nLayout = LAYOUTTYPE_GROUP;
//	}
//}

//=============================================================================
// ���f���z�u�̎��
//=============================================================================
bool SphereModel(COLLISIONTYPE  nType, D3DXVECTOR3 *C1, D3DXVECTOR3 *C2, D3DXVECTOR3 *M1, D3DXVECTOR3 *M2, float R1, float R2)
{
	bool bDetection = false;
	//D3DXVECTOR3 C3;							//�v�Z�p
	D3DXVECTOR3 save = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//�ۑ��p
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if ((C1->x - C2->x) * (C1->x - C2->x) + (C1->z - C2->z) * (C1->z - C2->z) <= (R1 + R2) * (R1 + R2))
	{
		save = *C1 - *C2;
		D3DXVec3Normalize(&vec, &save);			//���K������b

		if (nType == COLLISIONTYPE_NORMAL)
		{
			C1->z += vec.z * ((R1 + R2) - fabsf(save.z));
			C1->x += vec.x * ((R1 + R2) - fabsf(save.x));

			M1->x = 0.0f;
			M1->z = 0.0f;
			M2->x = 0.0f;
			M2->z = 0.0f;
		}
		else if (nType == COLLISIONTYPE_WEAPON)
		{
			bDetection = true;
		}
	}
	return bDetection;
}

////=============================================================================
//// ���f���z�u�̃`�F���W
////=============================================================================
//void ChangeModel(void)
//{
//	//============================ ���f���̔z�u ============================//
//	if (GetMode() == MODE_RESULT)
//	{
//		//���Z�b�g�̃��f��
//		SetModel(ITEMTYPE_CLOUD_1, D3DXVECTOR3(430.0f, 0.0f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
//		SetModel(ITEMTYPE_CLOUD_2, D3DXVECTOR3(430.0f, 0.0f, -230.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
//
//		//�t�����[
//		SetModel(ITEMTYPE_CLOUD_3, D3DXVECTOR3(430.0f, 80.0f, -250.0f), D3DXVECTOR3(-1.0f, 1.0f, 0.0f));
//	}
//	else if (GetMode() == MODE_TITLE)
//	{
//		//���C�A�E�g�u���ʂ̋����v
//		SetLayout(LAYOUTTYPE_NORMAL);
//	}
//	else if (GetMode() == MODE_GAME)
//	{
//		if (IsFinish())
//		{
//			//���C�A�E�g�u���ʂ̋����v
//			SetLayout(LAYOUTTYPE_CIRCLE);
//		}
//		else
//		{
//			//���C�A�E�g�u���ʂ̋����v
//			SetLayout(LAYOUTTYPE_NONE);
//		}
//	}
//	else
//	{
//		//���C�A�E�g�u���ʂ̋����v
//		SetLayout(LAYOUTTYPE_CIRCLE);
//	}
//}

// ----------------------------------------------------------------------------
// �X�e�[�W�ǂݍ���
// ----------------------------------------------------------------------------
bool SetStage(int nStageNo)
{
	FILE *pFile;
	char aTextBuff[128];
	int nCntObject = 0;
	pFile = 0;

	// �u���b�N�̏��̏�����
	for (nCntObject = 0; nCntObject < MAX_ITEM; nCntObject++)
	{
		g_aItem[nCntObject].bUse = false;
	}

	nCntObject = 0;

	if (nStageNo == 0)
	{
		pFile = fopen(STAGE_FILE, "r");
	}


	if (pFile != NULL)
	{
		while (1)
		{
			fscanf(pFile, "%s", &aTextBuff[0]);
			// �t�@�C���͈�
			if (strcmp(&aTextBuff[0], "SCRIPT") == 0)
			{
				while (strcmp(&aTextBuff[0], "END_SCRIPT") != 0)
				{
					fscanf(pFile, "%s", &aTextBuff[0]);
					// �u���b�N�t�@�C���ǂݍ���
					if (strcmp(&aTextBuff[0], "BLOCKSET") == 0)
					{
						while (strcmp(&aTextBuff[0], "END_BLOCKSET") != 0)
						{
							fscanf(pFile, "%s", &aTextBuff[0]);
							if (strcmp(&aTextBuff[0], "pos") == 0)
							{
								fscanf(pFile, " = %f,%f,%f", &g_aItem[nCntObject].posModel.x, &g_aItem[nCntObject].posModel.y, &g_aItem[nCntObject].posModel.z);
							}
							else if (strcmp(&aTextBuff[0], "move") == 0)
							{
								fscanf(pFile, " = %f,%f,%f", &g_aItem[nCntObject].moveModel.x, &g_aItem[nCntObject].moveModel.y, &g_aItem[nCntObject].moveModel.z);
							}
							else if (strcmp(&aTextBuff[0], "rot") == 0)
							{
								fscanf(pFile, " = %f,%f,%f", &g_aItem[nCntObject].rotModel.x, &g_aItem[nCntObject].rotModel.y, &g_aItem[nCntObject].rotModel.z);
							}
							else if (strcmp(&aTextBuff[0], "CountMax") == 0)
							{
								fscanf(pFile, " = %d", &g_aItem[nCntObject].nCntMax);
							}
							else if (strcmp(&aTextBuff[0], "type") == 0)
							{
								fscanf(pFile, " = %d", &g_aItem[nCntObject].type);
							}
						}
						// �u���b�N������
						SetModel(g_aItem[nCntObject].posModel, g_aItem[nCntObject].rotModel, g_aItem[nCntObject].moveModel, g_aItem[nCntObject].type, g_aItem[nCntObject].nCntMax);
						nCntObject++;
					}
				}
				break;
			}

		}
		fclose(pFile);
		return true;
	}
	return false;
}
