//========================================================================================
//
// ��{[Ranking[.cpp]
//
// Author : masayasu wakita
// 07/13
//
//========================================================================================
#include "ranking.h"
#include "fade.h"
#include "time.h"
#include "wall.h"
#include "meshField.h"
#include "camera.h"
#include "light.h"
#include "shadow.h"
#include "gradation.h"
#include "input.h"
#include "controller.h"

//========================================================================================
// �}�N����`
//========================================================================================
#define TEXTURE_BG_ADD			"data/tex/nc40567.png"		//�w�i�̃e�N�X�`��
#define TEXTURE_RANKING_ADD		"data/tex/ranking.png"			//�uranking�v�̃e�N�X�`��
#define TEXTURE_NUMBER_ADD		"data/tex/number3D.png"			//�����̃e�N�X�`��
#define TEXTFILE_RANKING		"data/RANKING.txt"		//�����L���O�̃f�[�^�ǂݍ���
#define MAX_RANKINGTEX 3										//�����L���O�e�N�X�`���̍ő吔
#define MAX_DIGIT 8
#define MAX_RANK 6
#define MAX_PREFAB 45

//========================================================================================
// �O���[�o���ϐ�
//========================================================================================
LPDIRECT3DTEXTURE9 g_pTextureRanking[MAX_RANKINGTEX] = {};						//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;								//���_�o�b�t�@�ւ̃|�C���^
RANKING g_rank[5];
int g_nNum;
float fMove_Ranking_Pos;
bool g_bInit;
int g_nTitle;
D3DXCOLOR g_aColor[5] = { D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), D3DXCOLOR(0.0f,1.0f,0.0f,1.0f), 
	D3DXCOLOR(0.0f,0.0f,1.0f,1.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f) };

//========================================================================================
// �|���S���̏�����
//========================================================================================
void InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCount;
	g_nTitle = 0;
	
	// �t�B�[���h�̏���������
	InitMeshField();

	// �ǂ̏���������
	InitWall();
	
	// �e�̏���������
	InitShadow();

	//�O���f�[�V�����̏���������
	InitGradation();

	g_bInit = false;

	for (nCount = 0; nCount < 5; nCount++)
	{
		g_rank[nCount].pos = D3DXVECTOR3(0, 0, 0);
		g_rank[nCount].col = D3DXCOLOR(1, 1, 1, 1);
		g_rank[nCount].nScore = 0;
	}
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_BG_ADD, &g_pTextureRanking[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_RANKING_ADD, &g_pTextureRanking[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NUMBER_ADD, &g_pTextureRanking[2]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (MAX_RANKINGTEX + MAX_PREFAB), D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffRanking, NULL);

	//SetVertexRanking(0, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	SetVertexRanking(1, D3DXVECTOR3(640, 100, 0), 350, 100, 0);

	SetVertexRanking(2, D3DXVECTOR3(300, 220, 0), 120, 100, 1.09f);

	SetVertexRanking(3, D3DXVECTOR3(300, 320, 0), 120, 100, 2);

	SetVertexRanking(4, D3DXVECTOR3(300, 420, 0), 120, 100, 3);

	SetVertexRanking(5, D3DXVECTOR3(300, 530, 0), 120, 100, 4);

	SetVertexRanking(6, D3DXVECTOR3(300, 630, 0), 120, 100, 5);

	LoadRanking();

	ConvertRanking(g_nNum);

	SaveRanking();

	// ���_���̍쐬
	MakeVertexRanking(RANKINGSTATE_1, D3DXVECTOR3(400, 400, 0), D3DXCOLOR(1.0f, 0, 0, 1.0f));
}

//========================================================================================
// �|���S���̊J������
//========================================================================================
void UninitRanking(void)
{
	int nCntTex;

	// �t�B�[���h�̏I������
	UninitMeshField();

	// �ǂ̏I������
	UninitWall();

	// �e�̏I������
	UninitShadow();

	//�O���f�[�V�����̏I������
	UninitGradation();

	//�e�N�X�`���̊J��
	for (nCntTex = 0; nCntTex < MAX_RANKINGTEX; nCntTex++)
	{
		if (g_pTextureRanking[nCntTex] != NULL)
		{
			g_pTextureRanking[nCntTex]->Release();
			g_pTextureRanking[nCntTex] = NULL;
		}
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
}

//========================================================================================
// �|���S���̍X�V����
//========================================================================================
void UpdateRanking(void)
{
	VERTEX_2D *pVtx;										//���_���ւ̃|�C���^
	fMove_Ranking_Pos -= 0.01f;
	float fAlpha = 1.0;
	int nCount = 0;

	// �t�B�[���h�̍X�V����
	UpdateMeshField();

	// �ǂ̍X�V����
	UpdateWall();

	// �e�̍X�V����
	UpdateShadow();

	// �O���f�[�V�����̍X�V����
	UpdateGradation();

	g_nTitle++;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	if (g_nTitle > 1000)
	{
		if (GetFade() == FADE_NONE)
		{
			SetFade(MODE_TITLE);
		}
	}

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + fMove_Ranking_Pos);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + fMove_Ranking_Pos);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + fMove_Ranking_Pos);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f + fMove_Ranking_Pos);

	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffRanking->Unlock();

	if (GetTriggerKeyboard(DIK_RETURN) || GetControllerTrigger(0, JOYPADKEY_B))
	{
		if (GetFade() == FADE_NONE)
		{
			SetFade(MODE_TITLE);
		}
	}
}

//========================================================================================
// �|���S���̕`�揈��
//========================================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCount;

	// �t�B�[���h�̕`�揈��
	DrawMeshField();

	// �ǂ̕`�揈��
	DrawWall();

	// �e�̕`�揈��
	DrawShadow();

	//�O���f�[�V�����̕`�揈��
	DrawGradation();

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	//�e�N�X�`���̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCount = 0; nCount < (MAX_RANKINGTEX + MAX_PREFAB); nCount++)
	{
		if (nCount < MAX_RANKINGTEX)
		{
			pDevice->SetTexture(0, g_pTextureRanking[nCount]);
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}

//=============================================================================
// ���_�̐ݒ�
//=============================================================================
void SetVertexRanking(int index, D3DXVECTOR3 pos, float fWidth, float fHeight, float nNumber)
{
	VERTEX_2D *pVtx;										//���_���ւ̃|�C���^

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	if (index < 2)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	else
	{
		//�e�N�X�`���`�ʂ̈ʒu
		pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);

	}

	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffRanking->Unlock();
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void MakeVertexRanking(RANKINGSTATE rank, D3DXVECTOR3 pos, D3DXCOLOR col)
{
	VERTEX_2D *pVtx;
	int nCntScore;
	int nCntRank;
	int nNumber;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	g_rank[rank].pos = pos;
	g_rank[rank].col = col;

	pVtx += (4 * 7);

	// ���_���̐ݒ�
	for (nCntRank = 0; nCntRank < 5; nCntRank++)
	{
		for (nCntScore = 0; nCntScore < MAX_DIGIT; nCntScore++)
		{
			//���_���W�̐ݒ�(���x���W + �Ԋu * nCntScore (+ ��), ���y���W)
			pVtx[0].pos = D3DXVECTOR3(400.0f + 85 * nCntScore, 155.0f + nCntRank * 100, 0);
			pVtx[1].pos = D3DXVECTOR3(400.0f + 85 * nCntScore + 70.0f, 155.0f + nCntRank * 100, 0);
			pVtx[2].pos = D3DXVECTOR3(400.0f + 85 * nCntScore, (155.0f + 110.0f) + nCntRank * 100, 0);
			pVtx[3].pos = D3DXVECTOR3(400.0f + 85 * nCntScore + 70.0f, (155.0f + 110.0f) + nCntRank * 100, 0);

			//1.0�ŌŒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//�J���[�`���[�g�̐ݒ�
			pVtx[0].col = g_aColor[nCntRank];
			pVtx[1].col = g_aColor[nCntRank];
			pVtx[2].col = g_aColor[nCntRank];
			pVtx[3].col = g_aColor[nCntRank];

			nNumber = (int)g_rank[nCntRank].nScore % (int)pow(10, 8 - nCntScore) / (int)pow(10, 8 - 1 - nCntScore);

			pVtx[0].tex = D3DXVECTOR2(nNumber * 0.1f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(nNumber * 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(nNumber * 0.1f + 0.1f, 1.0f);

			pVtx += 4;
		}
	}
	// ���_�f�[�^���A�����b�N����
	g_pVtxBuffRanking->Unlock();
}
//=============================================================================
// ���ʂ̐���
//============================================================================
void ConvertRanking(int nNumber)
{
	int nCount, nCountA;
	int nNum01;
	g_rank[RANKINGSTATE_6].nScore = nNumber;

	//�f�[�^�̃\�[�g�����s
	for (nCount = 0; nCount < MAX_RANK; nCount++)
	{
		for (nCountA = 0; nCountA < MAX_RANK - nCount; nCountA++)
		{
			if (g_rank[nCountA].nScore < g_rank[nCountA + 1].nScore)
			{
				nNum01 = g_rank[nCountA].nScore;				//�������������������ւ���
				g_rank[nCountA].nScore = g_rank[nCountA + 1].nScore;	//�傫�������������i�[
				g_rank[nCountA + 1].nScore = nNum01;			//����������������
			}
		}
	}
}

//=============================================================================
// ���ʂ̕ۑ�
//=============================================================================
void SaveRanking(void)
{
	FILE *pFile;
	int nCount;

	pFile = fopen(TEXTFILE_RANKING, "w");
	if (pFile != NULL)
	{
		for (nCount = 0; nCount < 5; nCount++)
		{
			//�f�[�^�̕ۑ�
			fprintf(pFile, "��%d��\n", nCount + 1);
			fprintf(pFile, "%d\n", g_rank[nCount].nScore);
		}
		fclose(pFile);
	}
}

//=============================================================================
// ���ʂ̃��[�h
//=============================================================================
void LoadRanking(void)
{
	FILE *pFile;
	int nCount;
	char x[128];

	pFile = fopen(TEXTFILE_RANKING, "r");
	if (pFile != NULL)
	{
		for (nCount = 0; nCount < 5; nCount++)
		{
			//�f�[�^�̃��[�h
			fscanf(pFile, "%s", &x[0]);
			fscanf(pFile, "%d", &g_rank[nCount].nScore);
		}
		fclose(pFile);
	}
}


//=============================================================================
// ���ʂ̐ݒ�
//=============================================================================
void SetResultIndex(int nScore)
{
	g_nNum = nScore;
}