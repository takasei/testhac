//=============================================================================
//
// ���f������ [player.h]
// Author : 
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_PLAYER	30
#define PLAYER_LIFE		30

//=============================================================================
// �\���̒�`
//=============================================================================
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,
	MOTIONTYPE_RUN,
	MOTIONTYPE_ATTACK_1,
	MOTIONTYPE_ATTACK_2,
	MOTIONTYPE_DAMAGE,
	MOTIONTYPE_MAX
} MOTIONTYPE;

typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;		//���_�o�b�t�@�ւ̃|�C���^
	LPD3DXMESH		pMeshPlayer = NULL;						//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	pBuffMatPlayer = NULL;					//�}�e���A�����ւ̃|�C���^
} PLAYERPARTS;

typedef struct
{
	D3DXVECTOR3	pos;										//�ʒu
	D3DXVECTOR3 rot;										//��]
	int		nFrame;											//�t���[����
} KEY;

typedef struct
{
	KEY		aKey[10];										//�L�[�̍\����
	D3DXVECTOR3 CurrentPos;									//1�t���[��������̈ړ���
	D3DXVECTOR3 CurrentRot;									//1�t���[��������̉�]��
	int		nMaxKey;										//�L�[��
	int		nLoop;											//���[�v���邩�ǂ���
} MOTION;

typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;		//���_�o�b�t�@�ւ̃|�C���^
	LPD3DXMESH		pMeshPlayer = NULL;						//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	pBuffMatPlayer = NULL;					//�}�e���A�����ւ̃|�C���^

	MOTION	aMotion[MOTIONTYPE_MAX];						//���[�V�����̍\����
	DWORD			nNumMatPlayer = 0;						//�}�e���A�����̐�
	D3DXVECTOR3		originPos;								//�ʒu�̃v���Z�b�g
	D3DXVECTOR3		posPlayer;								//���f���̈ʒu
	D3DXVECTOR3		posOld;									//�v���C���[�̑O��̈ʒu
	D3DXVECTOR3		movePlayer;								//���f���̈ړ���
	D3DXVECTOR3		originRot;								//��]�̃v���Z�b�g
	D3DXVECTOR3		rotPlayer;								//���f���̌���(��])
	D3DXMATRIX		mtxWorldPlayer;							//���f���̃��[���h�}�g���b�N�X
	int nIdxShadow;											//�e��ID
	int nIndex;												//���f���̃C���f�b�N�X
	int nParent;											//���f���̐e�ԍ�
	char sAdd[64];											//���f���̃A�h���X
} MODEL;

typedef struct
{
	D3DXMATRIX	mtxWorld;									//���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;										//�ʒu
	D3DXVECTOR3 posOld;										//�O�̈ʒu
	D3DXVECTOR3 move;										//�ړ���
	D3DXVECTOR3 rot;										//��]
	D3DXVECTOR3	dest;										//���f���̍ŏI���B�_
	D3DXVECTOR3	Difference;									//���f���̍ő��]
	int			nIdxShadow;									//�e��ID
	int			nLife;										//�̗�
	MODEL		aModel[MAX_PLAYER];							//���f���̏��
	bool bJump;												//�W�����v���Ă��邩�ǂ���
	int CurrentFrame;									//���݂̃t���[����
	int CurrentKey;									//���݂̃L�[
	int nAnimationType;								//���݂̃A�j���[�V����
	float nValueH;									//�R���g���[���[
	float nValueV;									//�R���g���[���[
} PLAYER;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER *GetPlayer(void);
#endif