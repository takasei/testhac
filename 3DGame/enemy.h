//=============================================================================
//
// �G���� [enemy.h]
// Author : masayasu wakita
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_MODEL	30

#define MAX_LIFE_EFFECT (1)

#define MAX_RANDOM (10)

#define MAX_RATE (20)

#define MAX_BASE (20)

//=============================================================================
// �\���̒�`
//=============================================================================
typedef enum
{
	MOTIONENEMY_NEUTRAL = 0,
	MOTIONENEMY_RUN,
	MOTIONENEMY_RUNATTACK,
	MOTIONENEMY_ATTACK_1,
	MOTIONENEMY_ATTACK_2,
	MOTIONENEMY_DAMAGE,
	MOTIONENEMY_MAX
} MOTIONENEMY;

typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;		//���_�o�b�t�@�ւ̃|�C���^
	LPD3DXMESH		pMeshEnemy = NULL;						//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	pBuffMatEnemy = NULL;					//�}�e���A�����ւ̃|�C���^
	DWORD			nNumMatEnemy = 0;						//�}�e���A�����̐�
} ENEMYPARTS;

typedef struct
{
	D3DXVECTOR3	pos;										//�ʒu
	D3DXVECTOR3 rot;										//��]
	int		nFrame;											//�t���[����
} ENEMYKEY;

typedef struct
{
	ENEMYKEY		aKey[10];										//�L�[�̍\����
	D3DXVECTOR3 CurrentPos;									//1�t���[��������̈ړ���
	D3DXVECTOR3 CurrentRot;									//1�t���[��������̉�]��
	int		nMaxKey;										//�L�[��
	int		nLoop;											//���[�v���邩�ǂ���
} ENEMYMOTION;

typedef struct
{
	ENEMYMOTION		aMotion[MOTIONENEMY_MAX];				//���[�V�����̍\����
	D3DXVECTOR3		originPos;								//�ʒu�̃v���Z�b�g
	D3DXVECTOR3		posEnemy;								//���f���̈ʒu
	D3DXVECTOR3		posOld;									//�v���C���[�̑O��̈ʒu
	D3DXVECTOR3		moveEnemy;								//���f���̈ړ���
	D3DXVECTOR3		originRot;								//��]�̃v���Z�b�g
	D3DXVECTOR3		rotEnemy;								//���f���̌���(��])
	D3DXMATRIX		mtxWorldEnemy;							//���f���̃��[���h�}�g���b�N�X
	int				nIdxShadow;								//�e��ID
	int				nIndex;									//���f���̃C���f�b�N�X
	int				nParent;								//���f���̐e�ԍ�
	char			sAdd[64];								//���f���̃A�h���X
} ENEMYMODEL;

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
	int			nWait;										//���̍s���Ɉڂ�����
	ENEMYMODEL	aModel[MAX_MODEL];							//���f���̏��
	bool bJump;												//�W�����v���Ă��邩�ǂ���
	bool bUse;												//�g���Ă��邩

	int CurrentEnemyFrame = 0;								//���݂̃t���[����
	int CurrentEnemyKey = 1;								//���݂̃L�[
	int nAnimationEnemy = 0;								//���݂̃A�j���[�V����
	float nValueH;											//�R���g���[���[
	float nValueV;											//�R���g���[���[
	int nCntAttack = 0;										//�A�^�b�N����܂ł̃J�E���^

} ENEMY;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

void SetEnemy(D3DXVECTOR3 pos, int nLife);
ENEMY *GetEnemy(void);
#endif