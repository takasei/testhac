//=============================================================================
//
// �|���S������ [polygon.h]
// Author : masayasu wakita
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef enum
{
	BULLETTYPE_NONE = -1,
	BULLETTYPE_ENEMY,
	BULLETTYPE_PLAYER,
	BULLETTYPE_MAX
} BULLETTYPE;
typedef struct
{
	D3DXVECTOR3 pos;										//�ʒu
	D3DXVECTOR3 move;										//�ړ���
	D3DXVECTOR3 rot;										//��]
	D3DXMATRIX	mtxWorld;									//���[���h�}�g���b�N�X
	BULLETTYPE	type;										//�o���b�g�̃^�C�v
	bool bUse;												//�g�p���Ă��邩�ǂ���
	int nLife;												//�ʂ̑ϋv�l
	int nIndexShadow;										//�e�̃C���f�b�N�X
} BULLET;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, BULLETTYPE type);
BULLET *GetBullet(void);
#endif