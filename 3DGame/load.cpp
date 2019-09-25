//========================================================================================
//
// ��{[load.cpp]
//
// Author : masayasu wakita
// 07/13
//
//========================================================================================
#include "load.h"
#include "player.h"
#include "enemy.h"

//========================================================================================
// �}�N����`
//========================================================================================


//========================================================================================
// �O���[�o���ϐ�
//========================================================================================
LOAD g_aLoad;

int g_nMaxModel = 0;

//========================================================================================
// �|���S���̏�����
//========================================================================================
void InitLoad(void)
{

}

//========================================================================================
// �|���S���̏�����
//========================================================================================
int LoadModel(void)
{
	FILE *pFile;
	char cReadText[128];		//����
	char cHeadText[128];		//��r
	char cDie[128];
	int nCntPointer;			//�|�C���^�[�̐��l
	int nAddPlayer = 0;				//�v���C���[�̃J�E���^�[
	int nCntkey = 0;				//�p�[�c�̃J�E���^�[
	int nAnimationType = 0;				//�A�j���[�V�����̎��

	int nCntMaya = 0;				//maya�̃f�[�^�Q��

	PLAYER *pPlayer;

	pPlayer = GetPlayer();

	//�e�L�X�g�f�[�^���[�h
	pFile = fopen("data/motion_TEAM.txt", "r");

	if (pFile != NULL)
	{
		//�|�C���^�[�̃��Z�b�g
		nCntPointer = 0;

		//�X�N���v�g������܂Ń��[�v
		while(strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
		}

		//�X�N���v�g��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			//�G���h�X�N���v�g������܂�
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);

				//���s
				if (strcmp(cHeadText, "\n") == 0)
				{

				}

				//���f����
				if (strcmp(cHeadText, "NUM_MODEL") == 0)
				{
					sscanf(cReadText, "%s %s %d", &cDie, &cDie, &g_nMaxModel);
				}

				//���f���̃A�h���X
				else if (strcmp(cHeadText, "MODEL_FILENAME") == 0)
				{
					sscanf(cReadText, "%s %s %s", &cDie, &cDie, &pPlayer->aModel[nAddPlayer].sAdd[0]);
					nAddPlayer++;
				}

				//�L�����N�^�[�Z�b�g��������
				else if (strcmp(cHeadText, "CHARACTERSET") == 0)
				{
					pPlayer = GetPlayer();
					nCntPointer = 0;

					//�G���h�L�����N�^�[�Z�b�g������܂Ń��[�v
					while (strcmp(cHeadText, "END_CHARACTERSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);

						//�p�[�c�Z�b�g��������
						if (strcmp(cHeadText, "PARTSSET") == 0)
						{
							//�G���h�p�[�c�Z�b�g������܂Ń��[�v
							while (strcmp(cHeadText, "END_PARTSSET") != 0)
							{
								fgets(cReadText, sizeof(cReadText), pFile);
								sscanf(cReadText, "%s", &cHeadText);

								//�C���f�b�N�X
								if (strcmp(cHeadText, "INDEX") == 0)
								{
									sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pPlayer->aModel[nCntPointer].nIndex);
								}

								//�e
								if (strcmp(cHeadText, "PARENT") == 0)
								{
									sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pPlayer->aModel[nCntPointer].nParent);
								}

								//�ʒu
								if (strcmp(cHeadText, "POS") == 0)
								{
									sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, 
										&pPlayer->aModel[nCntPointer].originPos.x,
										&pPlayer->aModel[nCntPointer].originPos.y,
										&pPlayer->aModel[nCntPointer].originPos.z);
								}

								//�ʒu
								if (strcmp(cHeadText, "ROT") == 0)
								{
									sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
										&pPlayer->aModel[nCntPointer].originRot.x,
										&pPlayer->aModel[nCntPointer].originRot.y,
										&pPlayer->aModel[nCntPointer].originRot.z);
								}
							}

							////���f���̊i�[�ꏊ��i�߂�
							nCntPointer++;
						}
					}
				}

				//�L�����N�^�[�Z�b�g��������
				else if (strcmp(cHeadText, "MOTIONSET") == 0)
				{
					pPlayer = GetPlayer();
					nCntPointer = 0;

					//�G���h�L�����N�^�[�Z�b�g������܂Ń��[�v
					while (strcmp(cHeadText, "END_MOTIONSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);

						//���[�v���邩�ǂ���
						if (strcmp(cHeadText, "LOOP") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pPlayer->aModel[nCntPointer].aMotion[nAnimationType].nLoop);

							if (pPlayer->aModel[nCntPointer].aMotion[nAnimationType].nLoop < 0 || pPlayer->aModel[nCntPointer].aMotion[nAnimationType].nLoop > 1)
							{
								//�x��
								//MessageBox(hWnd, "���[�v�̒l���͈͊O�ł��I", "�x���I", MB_ICONWARNING);

								//�Q�[���̏I��
								//DestroyWindow(hWnd);
							}
						}

						//�L�[��
						else if (strcmp(cHeadText, "NUM_KEY") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pPlayer->aModel[nCntPointer].aMotion[nAnimationType].nMaxKey);
						}

						//�L�[�Z�b�g��������
						if (strcmp(cHeadText, "KEYSET") == 0)
						{
							//�G���h�L�[�Z�b�g������܂Ń��[�v
							while (strcmp(cHeadText, "END_KEYSET") != 0)
							{
								fgets(cReadText, sizeof(cReadText), pFile);
								sscanf(cReadText, "%s", &cHeadText);

								//�t���[����
								if (strcmp(cHeadText, "FRAME") == 0)
								{
									sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pPlayer->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntkey].nFrame);
								}

								//�L�[��������
								if (strcmp(cHeadText, "KEY") == 0)
								{
									//�G���h�L�[������܂Ń��[�v
									while (strcmp(cHeadText, "END_KEY") != 0)
									{
										fgets(cReadText, sizeof(cReadText), pFile);
										sscanf(cReadText, "%s", &cHeadText);

										//�ʒu
										if (strcmp(cHeadText, "POS") == 0)
										{
											sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, 
												&pPlayer->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntkey].pos.x,
												&pPlayer->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntkey].pos.y,
												&pPlayer->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntkey].pos.z);
										}

										//��]
										if (strcmp(cHeadText, "ROT") == 0)
										{
											sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
												&pPlayer->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntkey].rot.x,
												&pPlayer->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntkey].rot.y,
												&pPlayer->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntkey].rot.z);
										}
									}

									//���f���̊i�[�ꏊ��i�߂�
									nCntPointer++;
								}
							}

							//key�̃J�E���^�[��1�v���X
							nCntkey++;
							nCntPointer = 0;

							//�v���C���[���̍X�V
							pPlayer = GetPlayer();

							////�L�[�̍ő�l�������Ă��Ȃ������ׂ�
							//if (nCntkey > pPlayer->aMotion[MOTIONTYPE_NEUTRAL].nKey)
							//{
							//	//�x��
							//	MessageBox(hWnd, "key�̒l���͈͊O�ł��I", "�x���I", MB_ICONWARNING);

							//	//�Q�[���̏I��
							//	DestroyWindow(hWnd);
							//}
						}
					}
					
					//�A�j���[�V�����̎�ނ�1�v���X
					nAnimationType++;


					//key�̃J�E���^�[�����Z�b�g
					nCntkey = 0;
				}
			}
		}

		//�t�@�C����
		fclose(pFile);
	}

	////���f���̐��Ɉُ�
	//if (nCntPointer != nMaxPlayer)
	//{
	//	//�x��
	//	MessageBox(hWnd, "���f���̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);

	//	//�Q�[���̏I��
	//	DestroyWindow(hWnd);
	//}
	//�A�h���X�̐��Ɉُ�
	if (nAddPlayer != g_nMaxModel + 1)
	{
		//�x��
		//MessageBox(hWnd, "�A�h���X�̐��������܂���I", "�x���I", MB_ICONWARNING);

		//�Q�[���̏I��
		//DestroyWindow(hWnd);
	}

	//�J���Ȃ�
	else
	{
		printf("�J���܂���ł���\n");
	}

	return g_nMaxModel;
}

//========================================================================================
// �G�̏�����
//========================================================================================
int LoadEnemy(void)
{
	FILE *pFile;
	char cReadText[128];		//����
	char cHeadText[128];		//��r
	char cDie[128];
	int nCntPointer;			//�|�C���^�[�̐��l
	int nAddPlayer = 0;				//�v���C���[�̃J�E���^�[
	int nCntkey = 0;				//�p�[�c�̃J�E���^�[
	int nAnimationType = 0;				//�A�j���[�V�����̎��

	int nCntMaya = 0;				//maya�̃f�[�^�Q��

	ENEMY *pEnemy;

	pEnemy = GetEnemy();

	//�e�L�X�g�f�[�^���[�h
	pFile = fopen("data/motion_TEAMENEMY.txt", "r");

	if (pFile != NULL)
	{
		//�|�C���^�[�̃��Z�b�g
		nCntPointer = 0;

		//�X�N���v�g������܂Ń��[�v
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
		}

		//�X�N���v�g��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			//�G���h�X�N���v�g������܂�
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);

				//���s
				if (strcmp(cHeadText, "\n") == 0)
				{

				}

				//���f����
				if (strcmp(cHeadText, "NUM_MODEL") == 0)
				{
					sscanf(cReadText, "%s %s %d", &cDie, &cDie, &g_nMaxModel);
				}

				//���f���̃A�h���X
				else if (strcmp(cHeadText, "MODEL_FILENAME") == 0)
				{
					sscanf(cReadText, "%s %s %s", &cDie, &cDie, &pEnemy->aModel[nAddPlayer].sAdd[0]);
					nAddPlayer++;
				}

				//�L�����N�^�[�Z�b�g��������
				else if (strcmp(cHeadText, "CHARACTERSET") == 0)
				{
					pEnemy = GetEnemy();
					nCntPointer = 0;

					//�G���h�L�����N�^�[�Z�b�g������܂Ń��[�v
					while (strcmp(cHeadText, "END_CHARACTERSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);

						//�p�[�c�Z�b�g��������
						if (strcmp(cHeadText, "PARTSSET") == 0)
						{
							//�G���h�p�[�c�Z�b�g������܂Ń��[�v
							while (strcmp(cHeadText, "END_PARTSSET") != 0)
							{
								fgets(cReadText, sizeof(cReadText), pFile);
								sscanf(cReadText, "%s", &cHeadText);

								//�C���f�b�N�X
								if (strcmp(cHeadText, "INDEX") == 0)
								{
									sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pEnemy->aModel[nCntPointer].nIndex);
								}

								//�e
								if (strcmp(cHeadText, "PARENT") == 0)
								{
									sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pEnemy->aModel[nCntPointer].nParent);
								}

								//�ʒu
								if (strcmp(cHeadText, "POS") == 0)
								{
									sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
										&pEnemy->aModel[nCntPointer].originPos.x,
										&pEnemy->aModel[nCntPointer].originPos.y,
										&pEnemy->aModel[nCntPointer].originPos.z);
								}

								//�ʒu
								if (strcmp(cHeadText, "ROT") == 0)
								{
									sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
										&pEnemy->aModel[nCntPointer].originRot.x,
										&pEnemy->aModel[nCntPointer].originRot.y,
										&pEnemy->aModel[nCntPointer].originRot.z);
								}
							}

							////���f���̊i�[�ꏊ��i�߂�
							nCntPointer++;
						}
					}
				}

				//�L�����N�^�[�Z�b�g��������
				else if (strcmp(cHeadText, "MOTIONSET") == 0)
				{
					pEnemy = GetEnemy();
					nCntPointer = 0;

					//�G���h�L�����N�^�[�Z�b�g������܂Ń��[�v
					while (strcmp(cHeadText, "END_MOTIONSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);

						//���[�v���邩�ǂ���
						if (strcmp(cHeadText, "LOOP") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pEnemy->aModel[nCntPointer].aMotion[nAnimationType].nLoop);

							if (pEnemy->aModel[nCntPointer].aMotion[nAnimationType].nLoop < 0 || pEnemy->aModel[nCntPointer].aMotion[nAnimationType].nLoop > 1)
							{
								//�x��
								//MessageBox(hWnd, "���[�v�̒l���͈͊O�ł��I", "�x���I", MB_ICONWARNING);

								//�Q�[���̏I��
								//DestroyWindow(hWnd);
							}
						}

						//�L�[��
						else if (strcmp(cHeadText, "NUM_KEY") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pEnemy->aModel[nCntPointer].aMotion[nAnimationType].nMaxKey);
						}

						//�L�[�Z�b�g��������
						if (strcmp(cHeadText, "KEYSET") == 0)
						{
							//�G���h�L�[�Z�b�g������܂Ń��[�v
							while (strcmp(cHeadText, "END_KEYSET") != 0)
							{
								fgets(cReadText, sizeof(cReadText), pFile);
								sscanf(cReadText, "%s", &cHeadText);

								//�t���[����
								if (strcmp(cHeadText, "FRAME") == 0)
								{
									sscanf(cReadText, "%s %s %d", &cDie, &cDie, &pEnemy->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntkey].nFrame);
								}

								//�L�[��������
								if (strcmp(cHeadText, "KEY") == 0)
								{
									//�G���h�L�[������܂Ń��[�v
									while (strcmp(cHeadText, "END_KEY") != 0)
									{
										fgets(cReadText, sizeof(cReadText), pFile);
										sscanf(cReadText, "%s", &cHeadText);

										//�ʒu
										if (strcmp(cHeadText, "POS") == 0)
										{
											sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
												&pEnemy->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntkey].pos.x,
												&pEnemy->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntkey].pos.y,
												&pEnemy->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntkey].pos.z);
										}

										//��]
										if (strcmp(cHeadText, "ROT") == 0)
										{
											sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
												&pEnemy->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntkey].rot.x,
												&pEnemy->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntkey].rot.y,
												&pEnemy->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntkey].rot.z);
										}
									}

									//���f���̊i�[�ꏊ��i�߂�
									nCntPointer++;
								}
							}

							//key�̃J�E���^�[��1�v���X
							nCntkey++;
							nCntPointer = 0;

							//�v���C���[���̍X�V
							pEnemy = GetEnemy();

							////�L�[�̍ő�l�������Ă��Ȃ������ׂ�
							//if (nCntkey > pPlayer->aMotion[MOTIONTYPE_NEUTRAL].nKey)
							//{
							//	//�x��
							//	MessageBox(hWnd, "key�̒l���͈͊O�ł��I", "�x���I", MB_ICONWARNING);

							//	//�Q�[���̏I��
							//	DestroyWindow(hWnd);
							//}
						}
					}

					//�A�j���[�V�����̎�ނ�1�v���X
					nAnimationType++;


					//key�̃J�E���^�[�����Z�b�g
					nCntkey = 0;
				}
			}
		}

		//�t�@�C����
		fclose(pFile);
	}

	////���f���̐��Ɉُ�
	//if (nCntPointer != nMaxPlayer)
	//{
	//	//�x��
	//	MessageBox(hWnd, "���f���̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);

	//	//�Q�[���̏I��
	//	DestroyWindow(hWnd);
	//}
	//�A�h���X�̐��Ɉُ�
	if (nAddPlayer != g_nMaxModel + 1)
	{
		//�x��
		//MessageBox(hWnd, "�A�h���X�̐��������܂���I", "�x���I", MB_ICONWARNING);

		//�Q�[���̏I��
		//DestroyWindow(hWnd);
	}

	//�J���Ȃ�
	else
	{
		printf("�J���܂���ł���\n");
	}

	return g_nMaxModel;
}

//========================================================================================
// maya����̃f�[�^���[�h
//========================================================================================
void LoadMaya(void)
{
	FILE *pFile;
	char cReadText[128];		//����
	char cReadType[128];		//�^�C�v
	char cHeadText[128];		//��r
	char cBodyType[128];		//parts
	char cDie[128];				//�폜
	int nCntPointer;			//�|�C���^�[�̐��l
	int nCntKey = 0;			//�L�[��//�p�[�c�̃J�E���^�[
	int nMaxPlayer = NULL;
	int nAddPlayer = 0;			//�v���C���[�̃J�E���^�[
	int nAnimationType = MOTIONTYPE_NEUTRAL;		//�A�j���[�V�����̎��

	int nCntMaya = 0;			//maya�̃f�[�^�Q��

	PLAYER *pPlayer;

	pPlayer = GetPlayer();

	//=============== Maya ==================//
	//�e�L�X�g�f�[�^���[�h
	pFile = fopen("data/test.anim", "r");
	nCntPointer = 0;

	//�J������
	if (pFile != NULL)
	{
		while (14 > nCntPointer)
		{
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s %s %s %s", &cHeadText, &cReadType, &cDie, &cBodyType);

			//================== �ړ�X�̏�񂾂����� ==================//
			if (strcmp(cBodyType, "body") == 0 && strcmp(cReadType, "translate.translateX") == 0)
			{
				//�L�[�܂Ŕ�΂�
				while ((strcmp(cHeadText, "keys") != 0))
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s %s", &cHeadText, &cReadType);
				}

				//���s
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s %s", &cHeadText, &cReadType);

				nCntKey = 0;				//�L�[���̏�����

				//�ړ�X�̓ǂݍ���
				while ((strcmp(cHeadText, "}") != 0))
				{
					sscanf(cReadText, "%s %f",
						&cDie,
						&pPlayer->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntKey].pos.x);

					//���s
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s %s", &cHeadText, &cReadType);

					nCntKey++;				//�L�[���̉��Z
				}

				//�L�[��
				pPlayer->aModel[nCntPointer].aMotion[nAnimationType].nMaxKey = nCntKey;
			}

			//================== �ړ�Y�̏�񂾂����� ==================//
			else if (strcmp(cBodyType, "body") == 0 && strcmp(cReadType, "translate.translateY") == 0)
			{
				//�L�[�܂Ŕ�΂�
				while ((strcmp(cHeadText, "keys") != 0))
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s %s", &cHeadText, &cReadType);
				}

				//���s
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s %s", &cHeadText, &cReadType);

				nCntKey = 0;				//�L�[���̏�����

				//�ړ�Y�̓ǂݍ���
				while ((strcmp(cHeadText, "}") != 0))
				{
					sscanf(cReadText, "%s %f",
						&cDie,
						&pPlayer->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntKey].pos.y);

					//���s
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s %s", &cHeadText, &cReadType);

					nCntKey++;				//�L�[���̉��Z
				}

				//�L�[��
				pPlayer->aModel[nCntPointer].aMotion[nAnimationType].nMaxKey = nCntKey;
			}

			//================== �ړ�Z�̏�񂾂����� ==================//
			else if (strcmp(cBodyType, "body") == 0 && strcmp(cReadType, "translate.translateZ") == 0)
			{
				//�L�[�܂Ŕ�΂�
				while ((strcmp(cHeadText, "keys") != 0))
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s %s", &cHeadText, &cReadType);
				}

				//���s
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s %s", &cHeadText, &cReadType);

				nCntKey = 0;				//�L�[���̏�����

				//�ړ�Z�̓ǂݍ���
				while ((strcmp(cHeadText, "}") != 0))
				{
					sscanf(cReadText, "%s %f",
						&cDie,
						&pPlayer->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntKey].pos.z);

					//���s
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s %s", &cHeadText, &cReadType);

					nCntKey++;				//�L�[���̉��Z
				}

				//�L�[��
				pPlayer->aModel[nCntPointer].aMotion[nAnimationType].nMaxKey = nCntKey;
			}

			//================== ��]X�̏�񂾂����� ==================//
			else if (strcmp(cReadType, "rotate.rotateX") == 0)
			{
				//�L�[�܂Ŕ�΂�
				while ((strcmp(cHeadText, "keys") != 0))
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s %s", &cHeadText, &cReadType);
				}

				//���s
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s %s", &cHeadText, &cReadType);

				nCntKey = 0;				//�L�[���̏�����

				//��]X�̓ǂݍ���
				while ((strcmp(cHeadText, "}") != 0))
				{
					sscanf(cReadText, "%d %f",
						&pPlayer->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntKey].nFrame,
						&pPlayer->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntKey].rot.x);
					//���s
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s %s", &cHeadText, &cReadType);

					pPlayer->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntKey].nFrame -= pPlayer->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntKey - 1].nFrame;

					nCntKey++;				//�L�[���̉��Z
				}

				//�L�[��
				pPlayer->aModel[nCntPointer].aMotion[nAnimationType].nMaxKey = nCntKey;
			}

			//================== ��]X�̏�񂾂����� ==================//
			else if (strcmp(cReadType, "rotate.rotateY") == 0)
			{
				//�L�[�܂Ŕ�΂�
				while ((strcmp(cHeadText, "keys") != 0))
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s %s", &cHeadText, &cReadType);
				}

				//���s
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s %s", &cHeadText, &cReadType);

				nCntKey = 0;				//�L�[���̏�����

				//�ړ�Y�̓ǂݍ���
				while ((strcmp(cHeadText, "}") != 0))
				{
					sscanf(cReadText, "%s %f",
						&cDie,
						&pPlayer->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntKey].rot.y);

					//���s
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s %s", &cHeadText, &cReadType);

					nCntKey++;				//�L�[���̉��Z
				}

				//�L�[��
				pPlayer->aModel[nCntPointer].aMotion[nAnimationType].nMaxKey = nCntKey;
			}

			//================== ��]Z�̏�񂾂����� ==================//
			else if (strcmp(cReadType, "rotate.rotateZ") == 0)
			{
				//�L�[�܂Ŕ�΂�
				while ((strcmp(cHeadText, "keys") != 0))
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s %s", &cHeadText, &cReadType);
				}

				//���s
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s %s", &cHeadText, &cReadType);

				nCntKey = 0;				//�L�[���̏�����

											//�ړ�X�̓ǂݍ���
				while ((strcmp(cHeadText, "}") != 0))
				{
					sscanf(cReadText, "%s %f",
						&cDie,
						&pPlayer->aModel[nCntPointer].aMotion[nAnimationType].aKey[nCntKey].rot.z);

					//���s
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s %s", &cHeadText, &cReadType);

					nCntKey++;				//�L�[���̉��Z
				}

				//�L�[��
				pPlayer->aModel[nCntPointer].aMotion[nAnimationType].nMaxKey = nCntKey;
				nCntPointer++;
			}
		}
	}
	else
	{
		printf("�J���܂���ł���\n");
	}
}