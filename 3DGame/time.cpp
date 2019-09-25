//================================================================================================
//
// �X�R�A���� [time.cpp]
// Author : Seiya takahashi
//
//================================================================================================
#include "time.h"
#include "fade.h"

//================================================================================================
// �}�N����`
//================================================================================================
#define	TEXTURE_TIME		"data/tex/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_TIME (2)


//================================================================================================
// �v���g�^�C�v�錾
//================================================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//================================================================================================
// �O���[�o���ϐ��錾
//================================================================================================
LPDIRECT3DTEXTURE9		g_pTextureTime = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
DWORD					g_dStartTime;
int g_nTime;
int g_nSeconds;
int g_nMaxSeconds;

//================================================================================================
// �^�C���̏���������
//================================================================================================
void InitTime(void)
{
	g_nSeconds = 0;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_dStartTime = 0;
	SetSeconds(99);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TIME,								// �t�@�C���̖��O
		&g_pTextureTime);							// �ǂݍ��ރ������[
						
	// ���_���̍쐬
	MakeVertexTime(pDevice);
}

//================================================================================================
// �^�C���I������
//================================================================================================
void UninitTime(void)
{
	// �e�N�X�`�����
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}
	// ���_�o�b�t�@�̉��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//================================================================================================
// �^�C���̍X�V����
//================================================================================================
void UpdateTime(void)
{
	g_dStartTime--;
	if (g_dStartTime >= 0)
	{
		SetTime(g_dStartTime);
	}
	if (g_dStartTime == 0)
	{
		// ��ʑJ��
		SetFade(MODE_RESULT);
	}

}

//================================================================================================
// �^�C���̕`�揈��
//================================================================================================
void DrawTime(void)
{
	int nCount;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTime);

	// �|���S���̕`��
	for (nCount = 0; nCount < MAX_TIME; nCount++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}

//================================================================================================
// �^�C���̍쐬
//================================================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
{
	int nCount;
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	for (nCount = 0; nCount < 2; nCount++)
	{
		// ���_���W
		//���_���W�̐ݒ�(���x���W + �Ԋu * nCnt (+ ��), ���y���W)
		pVtx[0].pos = D3DXVECTOR3(587.0f + 53 * nCount, 10.0f, 0);
		pVtx[1].pos = D3DXVECTOR3(587.0f + 53 * nCount + 50.0f, 10.0f, 0);
		pVtx[2].pos = D3DXVECTOR3(587.0f + 53 * nCount, 80.0f, 0);
		pVtx[3].pos = D3DXVECTOR3(587.0f + 53 * nCount + 50.0f, 80.0f, 0);

		// 1.0�ŌŒ�A�������W
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		// ���_�f�[�^�̃|�C���^��4���i�߂�
		pVtx += 4;
	}
	// ���_�f�[�^���A�����b�N
	g_pVtxBuffTime->Unlock();
}

//================================================================================================
// �^�C���̕ύX
//================================================================================================
void SetTime(int nTime)
{
	int nCount;
	int nNumber;
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	g_nSeconds = nTime / 60 + 1;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCount = 0; nCount < MAX_TIME; nCount++)
	{
		nNumber = (int)g_nSeconds % (int)pow(10, MAX_TIME - nCount) / (int)pow(10, MAX_TIME - 1 - nCount);

		// �e�N�X�`�����W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(nNumber*0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(nNumber*0.1f + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(nNumber*0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(nNumber*0.1f + 0.1f, 1.0f);

		// ���_�f�[�^�̃|�C���^��4���i�߂�
		pVtx += 4;
	}

	// ���_�f�[�^���A�����b�N
	g_pVtxBuffTime->Unlock();
}

//================================================================================================
// �^�C���̕ύX
//================================================================================================
void SetSeconds(int nTime)
{
	g_dStartTime += nTime * 60;
	g_nMaxSeconds = g_dStartTime / 60;
}

//================================================================================================
// �^�C���̎擾
//================================================================================================
int GetTime(void)
{
	return 	g_nSeconds;
}

//================================================================================================
// �^�C���̍ő�l�̎擾
//================================================================================================
int GetMaxTime(void)
{
	return g_nMaxSeconds;
}
