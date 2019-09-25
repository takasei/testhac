//========================================================================================
//
// �̗͏��� [hitpoint.h]
// Author : Seiya Takahashi
//
//========================================================================================
#ifndef _HITPOINT_H_
#define _HITPOINT_H_

//========================================================================================
// �C���N���[�h�t�@�C��
//========================================================================================
#include "main.h"

//=============================================================================
// �\���̂̒�`
//=============================================================================
typedef struct
{
	float fMaxHp;									//HP�̍ő�l
	float fNowHp;									//���݂�HP
	float fWidth;									//�摜�̕��̍ő�l
	float fMaxHpEnemy;								//HP�̍ő�l
	float fNowHpEnemy;								//���݂�HP
	float fWidthEnemy;								//�摜�̕��̍ő�l
} HITPOINT;

//========================================================================================
// �v���g�^�C�v�錾
//========================================================================================
void InitHitPoint(void);
void UninitHitPoint(void);
void UpdateHitPoint(void);
void DrawHitPoint(void);
void SetVertexHitPoint(int index, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight);
void SetVertexHitPoint1(int index, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight);
HITPOINT *GetHitPoint(void);
#endif
