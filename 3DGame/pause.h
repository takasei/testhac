//========================================================================================
//
// polygon��b[bg.h]
//
// Author : masayasu wakita
// 07/18
//
//========================================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_
//========================================================================================
// �C���N���[�h�t�@�C��
//========================================================================================
#include "game.h"

//========================================================================================
// �\���̒�`
//========================================================================================
typedef enum
{
	PAUSESTATE_CONTINUE = 0,
	PAUSESTATE_TITLE,
	PAUSESTATE_MAX
} PAUSESTATE;

//========================================================================================
// �v���g�^�C�v�錾
//========================================================================================
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
void SetPause(bool bPause);
void SetPauseMode(GAMESTATE mode);
GAMESTATE GetPauseMode(void);
void SetVertexPause(int index, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight);
#endif