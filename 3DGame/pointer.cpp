//=============================================================================
//
// �|���S������ [polygon.cpp]
// Author : masayasu wakita
//
//=============================================================================
#include "pointer.h"
#include "mouse.h"
#include "camera.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_EXPLOSION	(128)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTexturePointer = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPointer = NULL;			//���_�o�b�t�@�ւ̃|�C���^
POINTER				g_pointer;			//����

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexPointer(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// ����������
//=============================================================================
void InitPointer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �ʒu�E��]�̏����ݒ�
		g_pointer.bUse = true;
		g_pointer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_pointer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_pointer.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/tex/Aim.png", &g_pTexturePointer);

	MakeVertexPointer(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitPointer(void)
{
	//�e�N�X�`���̊J��
	if (g_pTexturePointer != NULL)
	{
		g_pTexturePointer->Release();
		g_pTexturePointer = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPointer != NULL)
	{
		g_pVtxBuffPointer->Release();
		g_pVtxBuffPointer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePointer(void)
{
	CAMERA *pCamera = GetCamera();
	VERTEX_3D *pVtx;										//���_���ւ̃|�C���^

	float fPosX = 0;
	float fPosY = 0;
	LONG pMouseX = 0;
	LONG pMouseY = 0;
	pMouseX = GetMouseX();
	pMouseY = GetMouseY();

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffPointer->Lock(0, 0, (void**)&pVtx, 0);

	//�������g���Ă���ꍇ
	if (g_pointer.bUse == true)
	{
		g_pointer.pos.x = (float)pMouseX + pCamera->posR.x;
		g_pointer.pos.y = (float)pMouseY + pCamera->posR.y;
		g_pointer.pos.z = 0;
	}
	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffPointer->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPointer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX	mtxRot, mtxTrans, mtxView;				//�v�Z�p�}�g���b�N�X

	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_pointer.mtxWorld);

	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	g_pointer.mtxWorld._11 = mtxView._11;
	g_pointer.mtxWorld._12 = mtxView._21;
	g_pointer.mtxWorld._13 = mtxView._31;
	g_pointer.mtxWorld._21 = mtxView._12;
	g_pointer.mtxWorld._22 = mtxView._22;
	g_pointer.mtxWorld._23 = mtxView._32;
	g_pointer.mtxWorld._31 = mtxView._13;
	g_pointer.mtxWorld._32 = mtxView._23;
	g_pointer.mtxWorld._33 = mtxView._33;

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_pointer.rot.y, g_pointer.rot.x, g_pointer.rot.z);
	D3DXMatrixMultiply(&g_pointer.mtxWorld, &g_pointer.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_pointer.pos.x, g_pointer.pos.y, g_pointer.pos.z);
	D3DXMatrixMultiply(&g_pointer.mtxWorld, &g_pointer.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_pointer.mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPointer, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, g_pTexturePointer);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�ʏ�u�����h�ɖ߂�
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexPointer(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffPointer, NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pVtxBuffPointer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-25.0f, 25.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(25.0f, 25.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-25.0f, -25.0f, -0.0f);
	pVtx[3].pos = D3DXVECTOR3(25.0f, -25.0f, -0.0f);

	//�@���x�N�g��
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���`�ʂ̈ʒu
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�f�[�^�̃A�����b�N
	g_pVtxBuffPointer->Unlock();
}

//=============================================================================
// ���擾
//=============================================================================
POINTER *GetPointer(void)
{
	return &g_pointer;
}