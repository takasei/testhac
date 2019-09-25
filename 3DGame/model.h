//========================================================================================
//
// polygon��b[bg.h]
//
// Author : masayasu wakita
// 07/18
//
//========================================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#define	STAGE_FILE		"data/stage.txt"				// �ǂݍ��ރX�e�[�W�t�@�C����

//========================================================================================
// �C���N���[�h�t�@�C��
//========================================================================================
#define _CRT_SECURE_NO_WARNINGS

#include "main.h"

//========================================================================================
// �\����
//========================================================================================
typedef enum
{
	COLLISIONTYPE_NORMAL = 0,
	COLLISIONTYPE_WEAPON,
	COLLISIONTYPE_MAX
} COLLISIONTYPE;

typedef enum
{
	LAYOUTTYPE_NONE = -1,
	LAYOUTTYPE_NORMAL,
	LAYOUTTYPE_WALL,
	LAYOUTTYPE_CIRCLE,
	LAYOUTTYPE_GROUP,
	LAYOUTTYPE_MAX
} LAYOUTTYPE;

typedef enum
{
	ITEMTYPE_NONE = -1,
	ITEMTYPE_CLOUD_1,
	ITEMTYPE_CLOUD_2,
	ITEMTYPE_CLOUD_3,
	ITEMTYPE_MAX
} ITEMTYPE;

//========================================================================================
// �v���g�^�C�v�錾
//========================================================================================
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);

void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, ITEMTYPE nType, int nCntMax);
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
bool SphereModel(COLLISIONTYPE  nType,D3DXVECTOR3 *C1, D3DXVECTOR3 *C2, D3DXVECTOR3 *M1, D3DXVECTOR3 *M2, float R1, float R2);

//void SetLayout(LAYOUTTYPE nType);
//void ChangeModel(void);

bool SetStage(int nStageNo);

#endif