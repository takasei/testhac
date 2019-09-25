//=============================================================================
//
// ���C������ [main.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "fade.h"
#include "mouse.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "shadow.h"
#include "resource.h"
#include "controller.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CLASS_NAME		"WindowClass"			// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"SkyMagician"	// �E�C���h�E�̃L���v�V������

//=============================================================================
// �\���̒�`
//=============================================================================


//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

#ifdef _DEBUG
void DrawFPS(void);
#endif

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Direct3D�f�o�C�X�ւ̃|�C���^(�`��ɕK�v)

MODE g_mode;
#ifdef _DEBUG
LPD3DXFONT			g_pFont = NULL;			// �t�H���g�ւ̃|�C���^
int					g_nCountFPS = 0;		// FPS�J�E���^
#endif

//=============================================================================
// ���C���֐�
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		//�A�C�R���̕ύX
		LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)),
		LoadCursor(NULL, NULL),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		//�A�C�R���̕ύX
		LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1))
	};
	HWND hWnd;
	MSG msg;
	RECT rect =	{0,	0, SCREEN_WIDTH, SCREEN_HEIGHT};

	DWORD dwCurrentTime;		// ���ݎ���
	DWORD dwExecLastTime;		// �Ō�ɏ�����������	

	DWORD dwFrameCount;
	DWORD dwFPSLastTime;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// �E�C���h�E���쐬
	hWnd = CreateWindowEx(0,
						CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						(rect.right - rect.left),
						(rect.bottom - rect.top),
						NULL,
						NULL,
						hInstance,
						NULL);

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// �E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();		// �V�X�e���������~���b�P�ʂŎ擾

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();		// �V�X�e���������~���b�P�ʂŎ擾

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	// ���b�Z�[�W���擾���Ȃ������ꍇ 0 ��Ԃ�
		{// Windows�̏���
			if (msg.message == WM_QUIT)
			{// WM_QUIT���b�Z�[�W�������烋�[�v�𔲂���
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectX�̏���

			dwCurrentTime = timeGetTime();		// �V�X�e���������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);		// FPS�𑪒�
#endif

				dwFPSLastTime = dwCurrentTime;		// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;					// �J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))		// 1/60�b���ƂɎ��s
			{
				dwExecLastTime = dwCurrentTime;		// ��������������ۑ�

				// �X�V����
				Update();

				// �`�揈��
				Draw();

				dwFrameCount++;			// �J�E���g�����Z
			}
		}
	}

	// �I������
	Uninit();

	// ����\��߂�
	timeEndPeriod(1);

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// �E�C���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			// �f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	// �v���[���e�[�V�����p�����[�^

	// Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	
	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@(�y�o�b�t�@)�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;									// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g(���݂̑��x�ɍ��킹��)
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �N���C�A���g�̈�𒼂��ɍX�V����

	// Direct3D�f�o�C�X�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,					// �f�B�X�v���C�A�_�v�^
									D3DDEVTYPE_HAL,						// �f�o�C�X�^�C�v
									hWnd,								// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
									D3DCREATE_HARDWARE_VERTEXPROCESSING,// �f�o�C�X�쐬����̑g�ݍ��킹
									&d3dpp,								// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
									&g_pD3DDevice)))					// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
										D3DDEVTYPE_HAL,
										hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dpp,
										&g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
											D3DDEVTYPE_REF,
											hWnd,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING,
											&d3dpp,
											&g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}
	// �����_�[�X�e�[�g�p�����[�^�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ����(�����)���J�����O����
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ���C�e�B���O���[�h�L��   //bullet
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����
	
#ifdef _DEBUG
	// �f�o�b�O�\���p�t�H���g��ݒ�
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "�l�r �S�V�b�N", &g_pFont);
#endif

	// �}�E�X�J�[�\���̍폜
	ShowCursor(false);

	//�T�E���h�̏���������
	InitSound(hWnd);

	//�L�[�{�[�h�̏���������
	InitKeyboard(hInstance, hWnd);

	//�}�E�X�̏���������
	InitMouse(hInstance, hWnd);

	//�R���g���[���[
	InitController(hInstance, hWnd);

	//���f���̏���������
	InitModel();

	//���[�h�̏�����
	SetMode(MODE_TITLE);

	//�t�F�[�h�̏�����
	InitFade(g_mode);

	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{		
	//�T�E���h�̏I������
	UninitSound();

	//���C�g�̏I������
	UninitLight();

	//�J�����̏I�����
	UninitCamera();

	// ���f���̏I������
	UninitModel();

	// �L�[�{�[�h�̏I������
	UninitKeyboard();

	//�}�E�X�̏I������
	UninitMouse();

	// �R���g���[���[�̏I������
	UninitController();

	// �t�F�[�h�̏I������
	UninitFade();

	// �^�C�g���̏I������
	UninitTitle();

	// �Q�[���̏I������
	UninitGame();

	// ���U���g�̏I������
	UninitResult();

	//�����L���O�̏I������
	UninitRanking();

#ifdef _DEBUG
	if (g_pFont != NULL)
	{// �f�o�b�O�\���p�t�H���g�̊J��
		g_pFont->Release();
		g_pFont = NULL;
	}
#endif
	
	// Direct3D�f�o�C�X�̊J��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̊J��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	//�t�F�[�h�̍X�V����
	UpdateFade();

	// �L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	// �R���g���[���X�V����
	UpdateController();

	// �}�E�X�̍X�V����
	UpdateMouse();

	//���C�g�̏I������
	UpdateLight();

	// ���f���̍X�V����
	UpdateModel();

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;
	case MODE_GAME:
		UpdateGame();
		break;
	case MODE_RESULT:
		UpdateResult();
		break;
	case MODE_RANKING:
		UpdateRanking();
		break;
	}

	//�J�����̏I�����
	UpdateCamera();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	if (GetTriggerKeyboard(DIK_I))
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	
	if(GetTriggerKeyboard(DIK_K))
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(137, 189, 222, 0), 1.0f, 0);

	// �`��̊J�n
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		// ���f���̕`�揈��
		DrawModel();

		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;

		case MODE_GAME:
			DrawGame();
			break;

		case MODE_RESULT:
			DrawResult();
			break;

		case MODE_RANKING:
			DrawRanking();
			break;
		}

		//�t�F�[�h����
		DrawFade();

		//�J�����̃Z�b�g
		SetCamera();

#ifdef _DEBUG
		// FPS�\��
		DrawFPS();

#endif

		// �`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

#ifdef _DEBUG
//=============================================================================
// FPS�\������
//=============================================================================
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	sprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	// �e�L�X�g�`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}
#endif

//=============================================================================
// ���[�h�̎擾
//=============================================================================
MODE GetMode(void)
{
	return g_mode;
}

//========================================================================================
// �f�o�C�X�̎擾
//========================================================================================
void SetMode(MODE mode)
{
	if (g_mode == MODE_TITLE && mode == MODE_GAME || g_mode == MODE_GAME && mode == MODE_RESULT)
	{
		//�T�E���h�̒�~
		StopSound();
	}

	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;

	case MODE_GAME:
		UninitGame();
		break;

	case MODE_RESULT:
		UninitResult();
		break;

	case MODE_RANKING:
		UninitRanking();
		break;
	}

	g_mode = mode;

	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;

	case MODE_GAME:
		InitGame();
		break;

	case MODE_RESULT:
		InitResult();
		break;

	case MODE_RANKING:
		InitRanking();
		break;
	}

	//���f���̔z�u����
	//ChangeModel();

	//�J�����̏�����
	InitCamera();
}