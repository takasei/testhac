// ----------------------------------------------------------------------------//
// �G�t�F�N�g�̏��� [effect.h]
// Author : Ryouma Inoue
//
// ----------------------------------------------------------------------------
#ifndef _EFFECT_H_
#define _EFFECT_H_

#define _CRT_SECURE_NO_WARNINGS

// ----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
// ----------------------------------------------------------------------------
#include "main.h"

//=============================================================================
// �G�t�F�N�g�̎��
//=============================================================================
typedef enum
{
	EFFECTTYPE_NORMAL = 0,
	EFFECTTYPE_LIFE,
	EFFECTTYPE_HIBANA,
	EFFECTTYPE_MAX
} EFFECTTYPE;


// ----------------------------------------------------------------------------
// �\���̒�`
// ----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 move;
	D3DXCOLOR col;			// �F
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	EFFECTTYPE type;
	float fRadius;			// ���a
	int nLife;				// ���C�t
	bool bUse;				// �g�p���Ă��邩�ǂ���
} EFFECT;


// ----------------------------------------------------------------------------
// �v���g�^�C�v�錾
// ----------------------------------------------------------------------------
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, float fRadius, int nLife, EFFECTTYPE type);

#endif
