//========================================================================================
//
// ��{[telop.cpp]
//
// Author : masayasu wakita
//
//========================================================================================
#include "telop.h"
#include "fade.h"
#include "pause.h"
#include "player.h"
#include "controller.h"
#include "enemy.h"
#include "model.h"
#include "input.h"
#include "tutorial.h"

//========================================================================================
// �}�N����`
//========================================================================================

//========================================================================================
// �O���[�o���ϐ�
//========================================================================================
LPDIRECT3DTEXTURE9 g_pTextureTelop[TELOPTEXTURE_MAX] = {};						//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTelop = NULL;					//���_�o�b�t�@�ւ̃|�C���^
D3DXCOLOR g_TelopWindowCol;										//�e���b�v�̃E�B���h�E�J���[
D3DXCOLOR g_TelopCol;											//�ʏ�e���b�v�̃J���[
TELOPMODE g_telop;
int g_nCntTelop;
int g_nCountTelopText;
int g_nCountTelopPage;
bool g_bDrowTelopText;
bool g_bDrowTelopStart;											//�ڕW�̎w�����������ǂ���
bool g_bDrowTelopDetails;										//�e���b�v�ɏڍ׃��[�h���g���Ă��鎞
float g_fLeftTelop;
float g_fRightTelop;
float fMove_Telop_Pos;
float g_fTelop;

//========================================================================================
// �|���S���̏�����
//========================================================================================
void InitTelop(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	PLAYER *pPlayer;
	pDevice = GetDevice();
	g_nCountTelopText = 0;
	g_nCountTelopPage = 0;
	bool g_bPlayerOperation = false;
	bool g_bBulletOperation = false;
	g_fLeftTelop = 0.33f;
	g_fRightTelop = 0.66f;
	g_nCntTelop = 0;

	g_bDrowTelopText = false;
	g_bDrowTelopStart = false;

	//�������擾
	pPlayer = GetPlayer();

	g_TelopCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_TelopWindowCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/tex/MessageWindow.png", &g_pTextureTelop[TELOPTEXTURE_MESSAGEWINDOW]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/tex/MessageWindow2.png", &g_pTextureTelop[TELOPTEXTURE_MESSAGEWIDE]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/tex/Message.png", &g_pTextureTelop[TELOPTEXTURE_MESSAGE]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TELOPTEXTURE_MAX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTelop, NULL);

}

//========================================================================================
// �|���S���̊J������
//========================================================================================
void UninitTelop(void)
{
	int nCntTex;

	//�e�N�X�`���̊J��
	for (nCntTex = 0; nCntTex < TELOPTEXTURE_MAX; nCntTex++)
	{
		if (g_pTextureTelop[nCntTex] != NULL)
		{
			g_pTextureTelop[nCntTex]->Release();
			g_pTextureTelop[nCntTex] = NULL;
		}
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTelop != NULL)
	{
		g_pVtxBuffTelop->Release();
		g_pVtxBuffTelop = NULL;
	}
}

//========================================================================================
// �|���S���̍X�V����
//========================================================================================
void UpdateTelop(void)
{
	VERTEX_2D *pVtx;										//���_���ւ̃|�C���^

	if (GetTriggerKeyboard(DIK_M))
	{
		if (g_bDrowTelopText == true)
		{
			g_bDrowTelopText = false;
		}
		else
		{
			g_bDrowTelopText = true;
		}
	}

	if (GetTriggerKeyboard(DIK_Z))
	{
		SetStageTelop(TELOPTYPE_MESSAGEWINDOW, TELOPPAGE_START);
	}

	if (GetFade() == FADE_NONE && IsFinish() && GetMode() == MODE_GAME)
	{
		if (!g_bDrowTelopStart)
		{
			SetStageTelop(TELOPTYPE_MESSAGEWINDOW, TELOPPAGE_START);
		}

		//�E�B���h�E����������
		if (g_bDrowTelopText)
		{
			if (!g_bDrowTelopDetails)
			{
				if (GetTriggerKeyboard(DIK_RETURN) || GetControllerTrigger(0, JOYPADKEY_B))
				{
					g_bDrowTelopText = false;
					g_TelopCol.a = 0.0f;

					if (!g_bDrowTelopStart)
					{
						g_bDrowTelopStart = true;
						SetStageTelop(TELOPTYPE_DETAILS, TELOPPAGE_PHASE1);
					}
				}
			}
			else
			{
				if (g_bDrowTelopDetails)
				{
					if (g_telop != TELOPMODE_NONE)
					{
						if (g_telop == TELOPMODE_IN)
						{
							g_TelopWindowCol.a -= 0.01f;
							if (g_TelopWindowCol.a <= 0.00f)
							{
								g_TelopWindowCol.a = 0.0f;
								g_bDrowTelopDetails = false;
								g_bDrowTelopText = false;
								g_telop = TELOPMODE_NONE;
							}
						}
						else if (g_telop == TELOPMODE_OUT)
						{
							g_TelopWindowCol.a += 0.01f;
							if (g_TelopWindowCol.a >= 1.0f)
							{
								g_TelopWindowCol.a = 1.0f;
								g_telop = TELOPMODE_IN;
							}
						}
					}
				}
			}
		}
	}

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffTelop->Lock(0, 0, (void**)&pVtx, 0);

	//�J���[�`���[�g�̐ݒ�
	pVtx[0].col = g_TelopWindowCol;
	pVtx[1].col = g_TelopWindowCol;
	pVtx[2].col = g_TelopWindowCol;
	pVtx[3].col = g_TelopWindowCol;

	pVtx += 4;

	//�J���[�`���[�g�̐ݒ�
	pVtx[0].col = g_TelopCol;
	pVtx[1].col = g_TelopCol;
	pVtx[2].col = g_TelopCol;
	pVtx[3].col = g_TelopCol;

	pVtx += 4;

	if (g_bDrowTelopDetails)
	{
		//�J���[�`���[�g�̐ݒ�
		pVtx[0].col = g_TelopWindowCol;
		pVtx[1].col = g_TelopWindowCol;
		pVtx[2].col = g_TelopWindowCol;
		pVtx[3].col = g_TelopWindowCol;
	}
	else
	{
		//�J���[�`���[�g�̐ݒ�
		pVtx[0].col = g_TelopCol;
		pVtx[1].col = g_TelopCol;
		pVtx[2].col = g_TelopCol;
		pVtx[3].col = g_TelopCol;
	}

	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffTelop->Unlock();
}

//========================================================================================
// �|���S���̕`�揈��
//========================================================================================
void DrawTelop(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCount;

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffTelop, 0, sizeof(VERTEX_2D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (GetGameState() == GAMESTATE_NORMAL || GetPauseMode() == GAMESTATE_NORMAL)
	{
		if (g_bDrowTelopText == true)
		{
			for (nCount = 0; nCount < TELOPTEXTURE_MAX; nCount++)
			{
				pDevice->SetTexture(0, g_pTextureTelop[nCount]);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
			}
		}
	}
}

//=============================================================================
// ���_�̐ݒ�
//=============================================================================
void SetVertexTelop(TELOPTEXTURE index, TELOPPAGE pgae, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight)
{
	VERTEX_2D *pVtx;										//���_���ւ̃|�C���^

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffTelop->Lock(0, 0, (void**)&pVtx, 0);

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

	if (index == TELOPTEXTURE_MESSAGE)
	{
		//�e�N�X�`���`�ʂ̈ʒu
		pVtx[0].tex = D3DXVECTOR2(0.0f + 0.5f * (pgae / 6), 0.0f + 0.167f * (pgae % 6));
		pVtx[1].tex = D3DXVECTOR2(0.5f + 0.5f * (pgae / 6), 0.0f + 0.167f * (pgae % 6));
		pVtx[2].tex = D3DXVECTOR2(0.0f + 0.5f * (pgae / 6), 0.167f + 0.167f * (pgae % 6));
		pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5f * (pgae / 6), 0.167f + 0.167f * (pgae % 6));
	}
	else
	{
		//�e�N�X�`���`�ʂ̈ʒu
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffTelop->Unlock();
}

//=============================================================================
// �Z�b�g�e���b�v
//=============================================================================
void SetStageTelop(TELOPTYPE index, TELOPPAGE page)
{
	//���̕��Ƀ��b�Z�[�W�E�B���h�E��\��������
	if (index == TELOPTYPE_MESSAGEWINDOW)
	{
		SetVertexTelop(TELOPTEXTURE_MESSAGEWIDE, page, D3DXVECTOR3(640.0f, 630.0f, 0.0f), g_TelopCol, 1200, 170);

		SetVertexTelop(TELOPTEXTURE_MESSAGE, page, D3DXVECTOR3(650.0f, 630.0f, 0.0f), g_TelopCol, 1200, 100);

		g_TelopCol.a = 1.0f;
	}

	//�傫����ʂɏڍו\��
	else if(index == TELOPTYPE_DETAILS)
	{
		g_telop = TELOPMODE_OUT;

		SetVertexTelop(TELOPTEXTURE_MESSAGEWINDOW, page, D3DXVECTOR3(640.0f, SCREEN_HEIGHT / 2, 0.0f), g_TelopWindowCol, SCREEN_WIDTH, 500);

		SetVertexTelop(TELOPTEXTURE_MESSAGE, page, D3DXVECTOR3(650.0f, SCREEN_HEIGHT / 2, 0.0f), g_TelopWindowCol, 1200, 100);

		g_TelopWindowCol.a = 0.0f;
		g_bDrowTelopDetails = true;
	}

	//�`��J�n
	g_bDrowTelopText = true;
}

//=============================================================================
// �e���b�v�̕\��������Ă��邩�ǂ���
//=============================================================================
bool GetTelopState(void)
{
	return g_bDrowTelopText;
}