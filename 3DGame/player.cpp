//=============================================================================
//
// ���f������ [player.cpp]
// Author : masayasu wakita
//
//=============================================================================
#include "player.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "load.h"
#include "trajectory.h"
#include "model.h"
#include "bullet.h"
#include "controller.h"
#include "tutorial.h"
#include "sound.h"
#include "telop.h"
#include "pointer.h"
#include "mouse.h"
#include "magic.h"
#include "magician.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_GRAVITY	0.5

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void AnimationPlayer(void);
void AnimationSwitch(MOTIONTYPE nType);
void BulletPos(void);
float g_fVelocity = 10;

#ifdef _DEBUG
void DrawPlayerData(void);
#endif

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTexturePlayer = NULL;		//�e�N�X�`���ւ̃|�C���^
PLAYER g_player;										//�v���C���[�̍\����
int g_nMaxPlayer = 15;									//�p�[�c�̍ő吔
int g_bAnimationPlayer = true;							//�A�j���[�V�����̃v���C

int g_nCntAttacCombo = 0;								//�A�^�b�N���[�V�����̔h��

#ifdef _DEBUG
LPD3DXFONT			g_pPlayerFont = NULL;				// �t�H���g�ւ̃|�C���^
#endif

//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_player.bJump = false;
	g_player.CurrentFrame = 0;									//���݂̃t���[����
	g_player.CurrentKey = 1;									//���݂̃L�[
	g_player.nAnimationType = MOTIONTYPE_NEUTRAL;				//���݂̃A�j���[�V����
	g_player.nValueH = 0;										//�R���g���[���[
	g_player.nValueV = 0;										//�R���g���[���[

	// �ʒu�E�����̏����ݒ�
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		g_player.aModel[nCntPlayer].posPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.aModel[nCntPlayer].movePlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.aModel[nCntPlayer].rotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.aModel[nCntPlayer].originPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.aModel[nCntPlayer].originRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

#ifdef _DEBUG
	// �f�o�b�O�\���p�t�H���g��ݒ�
	D3DXCreateFont(pDevice, 13, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "�l�r �S�V�b�N", &g_pPlayerFont);
#endif

	//�X�N���v�g�̓ǂݍ���
	g_nMaxPlayer = LoadModel();

	// �ʒu�E�����̏����ݒ�
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		g_player.aModel[nCntPlayer].posPlayer = g_player.aModel[nCntPlayer].originPos;
		g_player.aModel[nCntPlayer].rotPlayer = g_player.aModel[nCntPlayer].originRot;
	}
	//LoadMaya();

	for (int nCntPlayer = 0; nCntPlayer < g_nMaxPlayer; nCntPlayer++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(g_player.aModel[nCntPlayer].sAdd, D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[nCntPlayer].pBuffMatPlayer, NULL, &g_player.aModel[nCntPlayer].nNumMatPlayer, &g_player.aModel[nCntPlayer].pMeshPlayer);
	}

	g_player.pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);

	if (IsFinish())
	{
		g_player.nLife = PLAYER_LIFE;
	}
	else
	{
		g_player.nLife = 999;
	}

	//�e�̍쐬
	g_player.nIdxShadow = SetShadow(D3DXVECTOR3(1.0f,0.0f,10.0f), g_player.rot, D3DXVECTOR3(30.0f, 10.0f, 30.0f));
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
#ifdef _DEBUG
	if (g_pPlayerFont != NULL)
	{// �f�o�b�O�\���p�t�H���g�̊J��
		g_pPlayerFont->Release();
		g_pPlayerFont = NULL;
	}
#endif
	for (int nCntPlayer = 0; nCntPlayer < g_nMaxPlayer; nCntPlayer++)
	{
		// ���b�V���̊J��
		if (g_player.aModel[nCntPlayer].pMeshPlayer != NULL)
		{
			g_player.aModel[nCntPlayer].pMeshPlayer->Release();
			g_player.aModel[nCntPlayer].pMeshPlayer = NULL;
		}

		// �}�e���A���̊J��
		if (g_player.aModel[nCntPlayer].pBuffMatPlayer != NULL)
		{
			g_player.aModel[nCntPlayer].pBuffMatPlayer->Release();
			g_player.aModel[nCntPlayer].pBuffMatPlayer = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	CAMERA *pCamera = GetCamera();
	MAGIC *pMagic = GetMagic();

	if (g_bAnimationPlayer)
	{
		AnimationPlayer();
	}

	if (GetTriggerKeyboard(DIK_8))
	{
		g_player.nLife += 1;
	}
	if (GetTriggerKeyboard(DIK_I))
	{
		g_player.nLife += -1;
	}

	g_player.posOld = g_player.pos;

	if (GetTelopState() == false)
	{
		if (g_player.nAnimationType != MOTIONTYPE_ATTACK_1 && g_player.nAnimationType != MOTIONTYPE_ATTACK_2)
		{
			//================�R���g���[���[===================//
			GetJoypadStickLeft(0, &g_player.nValueH, &g_player.nValueV);

			//�p�x
			g_player.dest.y = atan2f(-g_player.move.x, -g_player.move.z);

			//�ړ�
			g_player.move -= D3DXVECTOR3(sinf(D3DX_PI * 1.0f + pCamera->rot.y) * (1.5f * g_player.nValueV), 0, cosf(D3DX_PI * 1.0f + pCamera->rot.y) * (1.5f * g_player.nValueV));
			g_player.move += D3DXVECTOR3(sinf(D3DX_PI * 0.5f + pCamera->rot.y) * (1.5f * g_player.nValueH), 0, cosf(D3DX_PI * 0.5f + pCamera->rot.y) * (1.5f * g_player.nValueH));

			if (fabs(g_player.move.x) > 1 || fabs(g_player.move.z) > 1)
			{
				if (g_player.nAnimationType != MOTIONTYPE_RUN)
				{
					AnimationSwitch(MOTIONTYPE_RUN);
				}
			}

			//���E����
			if (GetKeyboardPress(DIK_LEFT))
			{
				if (g_player.nAnimationType != MOTIONTYPE_RUN)
				{
					AnimationSwitch(MOTIONTYPE_RUN);
				}
				g_player.move.x += sinf(-D3DX_PI * 0.5f + pCamera->rot.y) * 1.0f;
				g_player.move.z += cosf(-D3DX_PI * 0.5f + pCamera->rot.y) * 1.0f;
				g_player.dest.y = D3DX_PI * 0.5f + pCamera->rot.y;
				pCamera->nCount = 0;
			}

			if (GetTriggerKeyboard(DIK_RSHIFT) || GetControllerTrigger(0, JOYPADKEY_X))
			{
				if (g_player.nAnimationType != MOTIONTYPE_ATTACK_1 && g_player.nAnimationType != MOTIONTYPE_ATTACK_2)
				{
					g_player.nAnimationType = MOTIONTYPE_ATTACK_1;
					g_player.CurrentKey = 0;
					g_player.CurrentFrame = 0;
				}
			}

			else if (GetKeyboardPress(DIK_RIGHT))
			{
				if (g_player.nAnimationType != MOTIONTYPE_RUN)
				{
					AnimationSwitch(MOTIONTYPE_RUN);
				}
				g_player.move.x += sinf(D3DX_PI * 0.5f + pCamera->rot.y) * 1.0f;
				g_player.move.z += cosf(D3DX_PI * 0.5f + pCamera->rot.y) * 1.0f;
				g_player.dest.y = -D3DX_PI * 0.5f + pCamera->rot.y;
				pCamera->nCount = 0;
			}
		}

		if (GetTriggerKeyboard(DIK_UP) || GetControllerPress(0, JOYPADKEY_A))
		{
			if (g_player.bJump == false)
			{
				g_player.bJump = true;
				g_player.move.y += g_fVelocity;
			}
		}
		//���͂�����Ƃ�
		if (pMagic->fNowMagic > 0)
		{
			if (GetMousePressTrigger(0))
			{
				BulletPos();
			}
		}
		//if (g_player.pos.x >= pPointer->pos.x)
		//{
		//	g_player.dest.y = D3DX_PI * 0.5f + pCamera->rot.y;
		//}
		//else if (g_player.pos.x <= pPointer->pos.x)
		//{
		//	g_player.dest.y = -D3DX_PI * 0.5f + pCamera->rot.y;
		//}

		g_player.aModel[2].originRot.z = 1.57f;
	}

	//���W�̈ړ�
	g_player.pos += g_player.move;

	g_player.move.x += (0 - g_player.move.x) * 0.2f;
	g_player.move.z += (0 - g_player.move.z) * 0.2f;

	//�L�����N�^�[�̐U�����
	g_player.Difference.y = g_player.rot.y - g_player.dest.y;

	if (g_player.Difference.y > D3DX_PI)
	{
		g_player.Difference.y -= D3DX_PI * 2;
	}
	else if (g_player.Difference.y < -D3DX_PI)
	{
		g_player.Difference.y += D3DX_PI * 2;
	}

	g_player.rot.y -= g_player.Difference.y * 0.1f;

	if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2;
	}
	else if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2;
	}

	if (GetTriggerKeyboard(DIK_F5))
	{
		if (g_bAnimationPlayer)
		{
			g_bAnimationPlayer = false;
		}
		else if (!g_bAnimationPlayer)
		{
			g_bAnimationPlayer = true;
		}
	}

	//�d��
	g_player.move.y -= PLAYER_GRAVITY;

	//���f���̏�ɂ��鎞
	if (CollisionModel(&g_player.pos, &g_player.posOld, &g_player.move) == true)
	{
		g_player.bJump = false;
		g_player.move.y = 0.0f;
	}
	else
	{
		g_player.bJump = true;
	}

	//�v���C���[�����ɒ�������
	if (g_player.pos.y <= 0)
	{
		g_player.pos.y = 0.0f;
		g_player.move.y = 0.0f;
		g_player.bJump = false;
	}

	//�e�̈ʒu��ݒ�
	SetPositionShadow(g_player.nIdxShadow, g_player.pos);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX		mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DXMATERIAL	*pMat;							//���݂̃}�e���A���ۑ��p
	D3DMATERIAL9	matDef;							//�}�e���A���f�[�^�ւ̃|�C���^


	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	for (int nCntPlayer = 0; nCntPlayer < g_nMaxPlayer; nCntPlayer++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player.aModel[nCntPlayer].mtxWorldPlayer);

		// �X�P�[���𔽉f


		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.aModel[nCntPlayer].rotPlayer.y, g_player.aModel[nCntPlayer].rotPlayer.x, g_player.aModel[nCntPlayer].rotPlayer.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntPlayer].mtxWorldPlayer, &g_player.aModel[nCntPlayer].mtxWorldPlayer, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_player.aModel[nCntPlayer].posPlayer.x,g_player.aModel[nCntPlayer].posPlayer.y, g_player.aModel[nCntPlayer].posPlayer.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntPlayer].mtxWorldPlayer, &g_player.aModel[nCntPlayer].mtxWorldPlayer, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);					//���ׂẴf�[�^���^

		//�e�q�֌W���������Ă���ꍇ
		if (g_player.aModel[nCntPlayer].nParent == -1)
		{
			//�}�g���b�N�X�̍���
			D3DXMatrixMultiply(&g_player.aModel[nCntPlayer].mtxWorldPlayer, &g_player.aModel[nCntPlayer].mtxWorldPlayer, &g_player.mtxWorld);
		}
		else
		{
			//�}�g���b�N�X�̍���
			D3DXMatrixMultiply(&g_player.aModel[nCntPlayer].mtxWorldPlayer, &g_player.aModel[nCntPlayer].mtxWorldPlayer, &g_player.aModel[g_player.aModel[nCntPlayer].nParent].mtxWorldPlayer);
		}

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCntPlayer].mtxWorldPlayer);					//���ׂẴf�[�^���^

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntPlayer].pBuffMatPlayer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntPlayer].nNumMatPlayer; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �`��
			g_player.aModel[nCntPlayer].pMeshPlayer->DrawSubset(nCntMat);
		}
	}
#ifdef _DEBUG
	// FPS�\��
	DrawPlayerData();
#endif

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �v���C���[�A�j���[�V����
//=============================================================================
void AnimationPlayer(void)
{
	//���[�V�����̍ő�l����
	if (g_player.nAnimationType < 0)
	{
		g_player.nAnimationType = MOTIONTYPE_MAX;
	}
	else if (g_player.nAnimationType > MOTIONTYPE_MAX)
	{
		g_player.nAnimationType = 0;
	}

	//�ŏ��̃t���[���̎�
	if (g_player.CurrentFrame == 0)
	{
		for (int nCntMotion = 0; nCntMotion < g_nMaxPlayer; nCntMotion++)
		{
			//// �ʒu�E�����̏����ݒ�
			//g_player.aModel[nCntMotion].posPlayer = g_player.aModel[nCntMotion].originPos;
			//g_player.aModel[nCntMotion].rotPlayer = g_player.aModel[nCntMotion].originRot;

			//pos�̌v�Z((�ڕW��key + �v���Z�b�g�̔z�u) - ���݂̃L�[)
			g_player.aModel[nCntMotion].aMotion[g_player.nAnimationType].CurrentPos.x = ((g_player.aModel[nCntMotion].aMotion[g_player.nAnimationType].aKey[g_player.CurrentKey].pos.x + g_player.aModel[nCntMotion].originPos.x) - g_player.aModel[nCntMotion].posPlayer.x) / g_player.aModel[0].aMotion[g_player.nAnimationType].aKey[g_player.CurrentKey].nFrame;
			g_player.aModel[nCntMotion].aMotion[g_player.nAnimationType].CurrentPos.y = ((g_player.aModel[nCntMotion].aMotion[g_player.nAnimationType].aKey[g_player.CurrentKey].pos.y + g_player.aModel[nCntMotion].originPos.y) - g_player.aModel[nCntMotion].posPlayer.y) / g_player.aModel[0].aMotion[g_player.nAnimationType].aKey[g_player.CurrentKey].nFrame;
			g_player.aModel[nCntMotion].aMotion[g_player.nAnimationType].CurrentPos.z = ((g_player.aModel[nCntMotion].aMotion[g_player.nAnimationType].aKey[g_player.CurrentKey].pos.z + g_player.aModel[nCntMotion].originPos.z) - g_player.aModel[nCntMotion].posPlayer.z) / g_player.aModel[0].aMotion[g_player.nAnimationType].aKey[g_player.CurrentKey].nFrame;

			//rot�̌v�Z((�ڕW��key + �v���Z�b�g�̔z�u) - ���݂̃L�[)
			g_player.aModel[nCntMotion].aMotion[g_player.nAnimationType].CurrentRot.x = ((g_player.aModel[nCntMotion].aMotion[g_player.nAnimationType].aKey[g_player.CurrentKey].rot.x + g_player.aModel[nCntMotion].originRot.x) - g_player.aModel[nCntMotion].rotPlayer.x) / g_player.aModel[0].aMotion[g_player.nAnimationType].aKey[g_player.CurrentKey].nFrame;
			g_player.aModel[nCntMotion].aMotion[g_player.nAnimationType].CurrentRot.y = ((g_player.aModel[nCntMotion].aMotion[g_player.nAnimationType].aKey[g_player.CurrentKey].rot.y + g_player.aModel[nCntMotion].originRot.y) - g_player.aModel[nCntMotion].rotPlayer.y) / g_player.aModel[0].aMotion[g_player.nAnimationType].aKey[g_player.CurrentKey].nFrame;
			g_player.aModel[nCntMotion].aMotion[g_player.nAnimationType].CurrentRot.z = ((g_player.aModel[nCntMotion].aMotion[g_player.nAnimationType].aKey[g_player.CurrentKey].rot.z + g_player.aModel[nCntMotion].originRot.z) - g_player.aModel[nCntMotion].rotPlayer.z) / g_player.aModel[0].aMotion[g_player.nAnimationType].aKey[g_player.CurrentKey].nFrame;
		}
	}

	//����ȊO�̃t���[��
	if (g_player.aModel[0].aMotion[g_player.nAnimationType].nMaxKey > g_player.CurrentKey)
	{
		for (int nCntMotion = 0; nCntMotion < g_nMaxPlayer; nCntMotion++)
		{
			if (nCntMotion != 2)
			{
				//rot�̈ړ�
				g_player.aModel[nCntMotion].rotPlayer += g_player.aModel[nCntMotion].aMotion[g_player.nAnimationType].CurrentRot;

				//pos�̈ړ�
				g_player.aModel[nCntMotion].posPlayer += g_player.aModel[nCntMotion].aMotion[g_player.nAnimationType].CurrentPos;
			}
		}
	}

	//�t���[���̍ő吔�ɖ����Ȃ��ꍇ
	if (g_player.CurrentFrame < g_player.aModel[0].aMotion[g_player.nAnimationType].aKey[g_player.CurrentKey].nFrame)
	{
		g_player.CurrentFrame++;
	}

	//�t���[�����̍ő�l�ɒB�����ꍇ
	if (g_player.aModel[0].aMotion[g_player.nAnimationType].aKey[g_player.CurrentKey].nFrame <= g_player.CurrentFrame)
	{
		g_player.CurrentKey++;
		g_player.CurrentFrame = 0;
	}

	//�L�[���̍ő�l�ɒB�����ꍇ
	if (g_player.CurrentKey >= g_player.aModel[0].aMotion[g_player.nAnimationType].nMaxKey)
	{
		//�U���̔h��
		if (g_player.nAnimationType == MOTIONTYPE_ATTACK_1)
		{
			g_nCntAttacCombo++;

			if (GetTriggerKeyboard(DIK_RSHIFT) || GetControllerTrigger(0, JOYPADKEY_X))
			{
				g_player.nAnimationType = MOTIONTYPE_ATTACK_2;
				g_player.CurrentKey = 0;
				g_player.CurrentFrame = 0;
				g_nCntAttacCombo = 0;
			}
			else if (g_nCntAttacCombo > 15)
			{
				g_player.nAnimationType = MOTIONTYPE_NEUTRAL;
				g_player.CurrentFrame = 0;
				g_nCntAttacCombo = 0;

				//�L�[�̃��Z�b�g
				g_player.CurrentKey = 0;
			}
		}
		else
		{
			//���[�v���邩�ǂ���
			if (g_player.aModel[0].aMotion[g_player.nAnimationType].nLoop)
			{
				//�L�[�̃��Z�b�g
				g_player.CurrentKey = 0;
				g_player.CurrentFrame = 0;
			}
			//�܂������Ă���ꍇ
			else if (fabs(g_player.move.x) > 2 || fabs(g_player.move.z) > 2)
			{
				//�L�[�̃��Z�b�g
				g_player.CurrentKey = 0;
				g_player.CurrentFrame = 0;
			}
			else
			{
				//�j���[�g�������[�V����
				AnimationSwitch(MOTIONTYPE_NEUTRAL);
				g_player.CurrentFrame = 0;

				//�L�[�̃��Z�b�g
				g_player.CurrentKey = 0;
			}
		}
	}
}

//=============================================================================
// �A�j���[�V�����̐؂�ւ�
//=============================================================================
void AnimationSwitch(MOTIONTYPE nType)
{
	g_player.nAnimationType = nType;
	g_player.CurrentKey = 0;
	g_player.CurrentFrame = 0;

	//switch (nType)
	//{
	//case MOTIONTYPE_NEUTRAL:
	//	g_nAnimationType = MOTIONTYPE_NEUTRAL;
	//	g_CurrentKey = 0;
	//	g_CurrentFrame = 0;
	//	break;
	//case MOTIONTYPE_ATTACK:
	//	break;
	//case MOTIONTYPE_RUN:
	//	break;
	//}
}


//=============================================================================
// �v���C���[���̎擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_player;
}

#ifdef _DEBUG
//=============================================================================
// �f�[�^�\��
//=============================================================================
void DrawPlayerData(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	char sAnimation[2000];
	char sData[128];

	strcpy(&sAnimation[0], "==============�p�[�c���===============\n");

	sprintf(&sData[0], "�A�j���[�V�����̎�� : %d\n", g_player.nAnimationType);
	strcat(&sAnimation[0], &sData[0]);

	sprintf(&sData[0], "�p�[�c�� : %d\n", g_nMaxPlayer);
	strcat(&sAnimation[0], &sData[0]);

	sprintf(&sData[0], "�v���C���[�̗� : %d\n", g_player.nLife);
	strcat(&sAnimation[0], &sData[0]);

	for (int nCntAnimation = 0; nCntAnimation < g_nMaxPlayer; nCntAnimation++)
	{
		//���f�����(pos)
		sprintf(&sData[0], "[%d] : (%.6f, %.6f, %.6f)\n", nCntAnimation, g_player.aModel[nCntAnimation].posPlayer.x, g_player.aModel[nCntAnimation].posPlayer.y, g_player.aModel[nCntAnimation].posPlayer.z);
		strcat(&sAnimation[0], &sData[0]);

		//���f�����(rot)
		sprintf(&sData[0], "rot : (%.6f, %.6f, %.6f)\n\n", g_player.aModel[nCntAnimation].rotPlayer.x, g_player.aModel[nCntAnimation].rotPlayer.y, g_player.aModel[nCntAnimation].rotPlayer.z);
		strcat(&sAnimation[0], &sData[0]);
	}

	sprintf(&sData[0], "�t���[���� : %d\n", g_player.CurrentFrame);
	strcat(&sAnimation[0], &sData[0]);
	sprintf(&sData[0], "�L�[�� : %d\n", g_player.CurrentKey);
	strcat(&sAnimation[0], &sData[0]);


	strcat(&sAnimation[0], "==============�e���===============\n");
	sprintf(&sData[0], "[%d] : (%.6f, %.6f, %.6f)\n", 0, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	strcat(&sAnimation[0], &sData[0]);


	// �e�L�X�g�`��
	g_pPlayerFont->DrawText(NULL, &sAnimation[0], -1, &rect, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}
#endif

//=============================================================================
// �e�̈ʒu
//=============================================================================
void BulletPos(void)
{
	CAMERA *pCamera = GetCamera();

	POINTER *pPointer;

	pPointer = GetPointer();

	float fX_Difference;
	float fY_Difference;
	float fDifference;


	// �J�[�\���ƃv���C���[�̇]���W����
	fX_Difference = g_player.pos.x - pPointer->pos.x;

	// �J�[�\���ƃv���C���[�̂x���W����
	fY_Difference = g_player.pos.y - pPointer->pos.y + 25;

	// �J�[�\���ƃv���C���[�̈�苗��
	fDifference = sqrtf(fX_Difference * fX_Difference + fY_Difference * fY_Difference);

	// �J�[�\���̕�����������
	g_player.rot.y = (float)atan2(fX_Difference, fY_Difference);

	//g_player.rot.y -= pCamera->rot.y;

	PlaySound(SOUND_LABEL_SE_AIM);
	SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 25, g_player.pos.z),
			D3DXVECTOR3(sinf(g_player.rot.y + D3DX_PI) * 10.0f, cosf(g_player.rot.y + D3DX_PI) * 10.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),BULLETTYPE_PLAYER);

	SetMagician(g_player.pos);

}
