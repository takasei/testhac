//========================================================================================
//
// �X�L��[skill.h]
//
// Author : Ryouma Inoue
// 07/18
//
//========================================================================================
#ifndef _SKILL_H_
#define _SKILL_H_

//========================================================================================
// �C���N���[�h�t�@�C��
//========================================================================================
#include "main.h"

//========================================================================================
// �\����
//========================================================================================
typedef enum
{
	TEXTURETYPE_ASUKA = 0,
	TEXTURETYPE_ASUKA2,
	TEXTURETYPE_ASUKA3,
	TEXTURETYPE_MAX
} TEXTURETYPE;

typedef struct
{
	D3DXVECTOR3 pos;							//���݂̈ʒu
	D3DXVECTOR3 size;							//�T�C�Y
	D3DXVECTOR3 rot;							//��]���
	TEXTURETYPE type;
	float fAngle;
	float fLength;
	int nCounterAnim;							// �J�E���^�[
	int nPatternAnim;							// �p�^�[��No
	bool bUse;
} SKILL;

//========================================================================================
// �v���g�^�C�v�錾
//========================================================================================
void InitSkill(void);
void UninitSkill(void);
void UpdateSkill(void);
void DrawSkill(void);
void MakeVertexSkill(int nIndex, D3DXVECTOR3 pos, D3DXVECTOR3 size, TEXTURETYPE type);
SKILL *GetSkill(void);

#endif