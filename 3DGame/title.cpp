//========================================================================================
//
// ��{[title.cpp]
//
// Author : masayasu wakita
// 07/13
//
//========================================================================================
#include "title.h"
#include "fade.h"
#include "game.h"
#include "meshField.h"
#include "camera.h"
#include "light.h"
#include "wall.h"
#include "shadow.h"
#include "gradation.h"
#include "input.h"
#include "controller.h"
#include "sound.h"

//========================================================================================
// �}�N����`
//========================================================================================
#define TEXTURE_TITLE_ADD "data/tex/Title.png"
#define TEXTURE_PRESS_ADD "data/tex/press enter.png"
#define TEXTURE_START_ADD "data/tex/game start.png"
#define TEXTURE_SELECT_ADD	"data/tex/select002.png"
#define TEXTURE_RANKING_ADD "data/tex/ranking.png"
#define RANKING_TIME 500
#define MAX_TITLE 4

//========================================================================================
// �O���[�o���ϐ�
//========================================================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TITLE] = {};						//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;							//���_�o�b�t�@�ւ̃|�C���^

D3DXVECTOR3 g_pos(640, 200, 0);											//�^�C�g���̃|�W�V����
D3DXCOLOR g_col(1.0f, 1.0f, 1.0f, 0.0f);
D3DXCOLOR g_logo;
int g_nRanking;
int g_nMode;
D3DXVECTOR3 g_Modepos;
bool g_bPressEnter;
bool g_bSelect;
float fMove_Title_Pos;

//========================================================================================
// �|���S���̏�����
//========================================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	g_nRanking = 0;

	g_Modepos = D3DXVECTOR3(640, 320, 0);
	g_nMode = 0;
	g_bSelect = false;
	g_bPressEnter = false;
	g_logo = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

	//�O���f�[�V�����̏���������
	InitGradation();

	//�e�̏���������
	InitShadow();

	//�t�B�[���h�̏���������
	InitMeshField();

	// �ǂ̏���������
	InitWall();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLE_ADD, &g_pTextureTitle[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PRESS_ADD, &g_pTextureTitle[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_START_ADD, &g_pTextureTitle[2]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_RANKING_ADD, &g_pTextureTitle[3]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TITLE + 1, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL);


	SetVertexTitle(0, D3DXVECTOR3(g_pos), g_col, 800, 200);

	SetVertexTitle(1, D3DXVECTOR3(640, 600, 0), g_logo, 400, 100);

	SetVertexTitle(2, D3DXVECTOR3(640, 600, 0), g_logo, 400, 100);

	SetVertexTitle(3, D3DXVECTOR3(640, 600, 0), g_logo, 400, 100);

	PlaySound(SOUND_LABEL_BGM001);
}

//========================================================================================
// �|���S���̊J������
//========================================================================================
void UninitTitle(void)
{
	int nCntTex;

	//�O���f�[�V�����̏I������
	UninitGradation();

	//�t�B�[���h�̏I������
	UninitMeshField();

	//�e�̏I������
	UninitShadow();

	//�e�N�X�`���̊J��
	for (nCntTex = 0; nCntTex < MAX_TITLE; nCntTex++)
	{
		if (g_pTextureTitle[nCntTex] != NULL)
		{
			g_pTextureTitle[nCntTex]->Release();
			g_pTextureTitle[nCntTex] = NULL;
		}
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//========================================================================================
// �|���S���̍X�V����
//========================================================================================
void UpdateTitle(void)
{
	float fAlpha = 1.0;
	int nCount = 0;

	//�t�B�[���h�̍X�V����
	UpdateMeshField();

	// �ǂ̍X�V����
	UpdateWall();

	g_nRanking++;

	//�^�C�g�����烉���L���O�ւ̎����J��
	if (g_bPressEnter == false)
	{
		if (g_nRanking >= RANKING_TIME)
		{
			if (GetFade() == FADE_NONE)
			{
				SetFade(MODE_RANKING);
			}
		}
	}

	//�^�C�g�������S�ɕ\�����ꂽ�Ƃ���press�G���^�[�̏���
	if (g_col.a > 1.0f && g_bPressEnter == false)
	{
		g_logo.a += 0.1f;

		SetVertexTitle(0, D3DXVECTOR3(g_pos), g_col, 800, 200);
		SetVertexTitle(1, D3DXVECTOR3(640, 600, 0), g_logo, 400, 100);
	}
	else
	{
		g_col.a += 0.01f;
		SetVertexTitle(0, D3DXVECTOR3(g_pos), g_col, 800, 200);
	}

	//pressenter�̍폜
	if (g_pos.y >= 200 && g_bPressEnter == true)
	{
		SetVertexTitle(1, D3DXVECTOR3(640, 600, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 400, 100);

		SetVertexTitle(2, D3DXVECTOR3(640, 450, 0), D3DXCOLOR(1.0f,1.0f,1.0f,1.0f), 250, 50);

		SetVertexTitle(3, D3DXVECTOR3(640, 600, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 50);
	}

	//�ǂ̃��[�h�ɂ��邩�����߂鏈��
	if (g_bPressEnter == true)
	{
		//�I��������
		if (GetTriggerKeyboard(DIK_UPARROW) || GetControllerTrigger(0, JOYPADKEY_UP))
		{
			g_nMode -= 1;
		}
		if (GetTriggerKeyboard(DIK_DOWNARROW) || GetControllerTrigger(0, JOYPADKEY_DOWN))
		{
			g_nMode += 1;
		}

		//�I�����̌J��Ԃ�����
		if (g_nMode > 1)
		{
			g_nMode = 0;
		}
		else if (g_nMode < 0)
		{
			g_nMode = 1;
		}

		//�I�����̕\������
		if (g_nMode == 0)
		{
			//�Q�[���J�n
			g_Modepos.y = 470;
			SetVertexTitle(2, g_Modepos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500, 100);
		}
		else if (g_nMode == 1)
		{
			//�����L���O
			g_Modepos.y = 620;
			SetVertexTitle(3, g_Modepos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500, 100);
		}
	}

	if (GetTriggerKeyboard(DIK_RETURN) || GetControllerTrigger(0, JOYPADKEY_B))
	{
		if (g_col.a > 1.0f && g_bPressEnter == true)
		{
			//PlaySound(SOUND_LABEL_SE_SELECT);
			if (GetFade() == FADE_NONE)
			{
				if (g_nMode == 0)
				{
					g_bSelect = true;
					SetFade(MODE_GAME);
				}
				else if (g_nMode == 1)
				{
					SetFade(MODE_RANKING);
				}
			}
		}
		//�^�C�g�����w�肵���ꏊ�ɂ����ꍇ
		else if (g_col.a >= 1.0f)
		{
			g_bPressEnter = true;
		}
		else
		{
			g_col.a = 1.0f;
		}
	}
}

//========================================================================================
// �|���S���̕`�揈��
//========================================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCount;

	//�@�t�B�[���h�̕`�揈��
	DrawMeshField();

	// �ǂ̕`�揈��
	DrawWall();

	//�e�̕`�揈��
	DrawShadow();

	//�O���f�[�V�����̕`�揈��
	DrawGradation();

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCount = 0; nCount < MAX_TITLE; nCount++)
	{
		pDevice->SetTexture(0, g_pTextureTitle[nCount]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}

//=============================================================================
// ���_�̐ݒ�
//=============================================================================
void SetVertexTitle(int index, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight)
{
	VERTEX_2D *pVtx;										//���_���ւ̃|�C���^

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += index * 4;

	// ���_���̐ݒ�
	//���_���W�̐ݒ�(���x���W + �Ԋu * nCntScore (+ ��), ���y���W)
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth / 2, pos.y - fHeight / 2, 0);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth / 2, pos.y - fHeight / 2, 0);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth / 2, pos.y + fHeight / 2, 0);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth / 2, pos.y + fHeight / 2, 0);

	//1.0�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�J���[�`���[�g�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//�e�N�X�`���`�ʂ̈ʒu
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffTitle->Unlock();
}

//=============================================================================
// �Q�[���J�n(�`���[�g���A���J�b�g��)
//=============================================================================
bool GetState(void)
{
	return g_bSelect;
}