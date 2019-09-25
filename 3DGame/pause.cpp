//========================================================================================
//
// ��{[game_bg.cpp]
//
// Author : masayasu wakita
// 07/13
//
//========================================================================================
#include "pause.h"
#include "input.h"
#include "game.h"

//========================================================================================
// �}�N����`
//========================================================================================
#define TEXTURE_PAUSE_ADD	"data/tex/bg003"
#define TEXTURE_CONTINUE	"data/tex/continu.png"
#define TEXTURE_TITLE		"data/tex/title_go.png"
#define TEXTURE_PAUSE		"data/tex/pause.png"
#define MAX_PAUSE 4

//========================================================================================
// �O���[�o���ϐ�
//========================================================================================
LPDIRECT3DTEXTURE9 g_pTexturePause[MAX_PAUSE] = {};						//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;				//���_�o�b�t�@�ւ̃|�C���^

bool g_bPause;
int g_nSelect;
GAMESTATE g_pauseMode;
D3DXVECTOR3 g_Selectpos;
//float fMove_Pos;

//========================================================================================
// �|���S���̏�����
//========================================================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	g_bPause = false;
	g_Selectpos = D3DXVECTOR3(640, 320, 0);
	g_nSelect = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSE_ADD, &g_pTexturePause[0]);

	D3DXCreateTextureFromFile(pDevice, TEXTURE_PAUSE, &g_pTexturePause[1]);

	D3DXCreateTextureFromFile(pDevice, TEXTURE_CONTINUE, &g_pTexturePause[2]);

	D3DXCreateTextureFromFile(pDevice, TEXTURE_TITLE, &g_pTexturePause[3]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PAUSE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPause, NULL);

	SetVertexPause(0, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0),D3DXCOLOR(0.0f,0.0f,0.0f,0.5f), SCREEN_WIDTH, SCREEN_HEIGHT);

	SetVertexPause(1, D3DXVECTOR3(640, 150, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500, 100);

	SetVertexPause(2, D3DXVECTOR3(640, 290, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 100);

	SetVertexPause(3, D3DXVECTOR3(640, 450, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 100);
}

//========================================================================================
// �|���S���̊J������
//========================================================================================
void UninitPause(void)
{
	int nCntTex;

	//�e�N�X�`���̊J��
	for (nCntTex = 0; nCntTex < MAX_PAUSE; nCntTex++)
	{
		if (g_pTexturePause[nCntTex] != NULL)
		{
			g_pTexturePause[nCntTex]->Release();
			g_pTexturePause[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//========================================================================================
// �|���S���̍X�V����
//========================================================================================
void UpdatePause(void)
{
	//�I��������
	if (GetTriggerKeyboard(DIK_UPARROW))
	{
		g_nSelect -= 1;
	}
	if (GetTriggerKeyboard(DIK_DOWNARROW))
	{
		g_nSelect += 1;
	}

	//�I�����̌J��Ԃ�����
	if (g_nSelect > 1)
	{
		g_nSelect = 0;
	}
	else if (g_nSelect < 0)
	{
		g_nSelect = 1;
	}

	SetVertexPause(2, D3DXVECTOR3(640, 320, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 50);
	SetVertexPause(3, D3DXVECTOR3(640, 470, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 250, 50);

	//�I�����̕\������
	if (g_nSelect == 0)
	{
		g_Selectpos.y = 320;
		SetVertexPause(2, g_Selectpos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500, 100);
	}
	else if (g_nSelect == 1)
	{
		g_Selectpos.y = 470;
		SetVertexPause(3, g_Selectpos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500, 100);
	}

	if (GetTriggerKeyboard(DIK_RETURN))
	{
		if (g_nSelect == 0)
		{
			SetPause(false);
			SetGameState(GetPauseMode());
		}
		else if (g_nSelect == 1)
		{
			SetGameState(GAMESTATE_BREAK);
		}
	}
}

//========================================================================================
// �|���S���̕`�揈��
//========================================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCount;

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_bPause == true)
	{
		for (nCount = 0; nCount < MAX_PAUSE; nCount++)
		{
			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetTexture(0, g_pTexturePause[nCount]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		}
	}
}

//========================================================================================
// �|�[�Y����
//========================================================================================
void SetPause(bool bPause)
{
	g_bPause = bPause;
}

//========================================================================================
// �|�[�Y�O�̃��[�h�擾
//========================================================================================
void SetPauseMode(GAMESTATE mode)
{
	g_pauseMode = mode;
}

//========================================================================================
// �|�[�Y�O�̃��[�h�擾
//========================================================================================
GAMESTATE GetPauseMode(void)
{
	return g_pauseMode;
}

//=============================================================================
// ���_�̐ݒ�
//=============================================================================
void SetVertexPause(int index, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight)
{
	VERTEX_2D *pVtx;										//���_���ւ̃|�C���^

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffPause->Unlock();
}