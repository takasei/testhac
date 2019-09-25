//=============================================================================
//
// �|���S������ [MeshField.h]
// Author : masayasu wakita
//
//=============================================================================
#ifndef _TRAJECTORY_H_
#define _TRAJECTORY_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitTrajectory(void);
void UninitTrajectory(void);
void UpdateTrajectory(void);
void DrawTrajectory(void);

void SetTrajectory(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
#endif