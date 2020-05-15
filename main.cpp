//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "effect.h"
#include "stage.h"
#include "player.h"
#include "enemy.h"


// �ϐ��錾
int SceneCounter;	// �V�[���J�E���^�[�p
int testCount;	

SCENE_ID scnID;			// ���̃V�[��
SCENE_ID scnIDpre;		// 1�t���[���O�̃V�[��

// ���C���֐�
int WINAPI WinMain(HINSTANCE , HINSTANCE , LPSTR, int)
{
	if (!SystemInit())
	{
		return 0;
	}

	// �Q�[�����[�v
 	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();

		KeyCheck();
		SceneCounter++;

		if (scnID != scnIDpre)
		{
			scnIDpre = scnID;
			SceneCounter = 0;
		}
		
		switch (scnID)
		{
		case SCENE_INIT:
			InitScene();
			scnID = SCENE_TITLE;
			break;
		case SCENE_TITLE:
			SceneChange(scnID,10,true);
			TitleScene();
			break;
		case SCENE_GAME:
			SceneChange(scnID,10,true);
			GameScene();
			break;
		case SCENE_GAMEOVER:
			SceneChange(scnID,10,true);
			GameOverScene();
			break;
		}

		ScreenFlip();
	}

	DxLib_End();     

	return 0; 
}

// �V�X�e��������
bool SystemInit(void)
{
	bool rtnFlag = true;

	// �V�X�e������
	SetWindowText("�ِ��E�ْ�");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);

	// DxLib������
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// �ϐ��̏�����
	SceneCounter = 0;


	// �e�֐��̃V�X�e���������@

	EffectInit();		// �G�t�F�N�g�̏�����
	KeyInit();			// �L�[��񏉊���
	StageSystemInit();	// �X�e�[�W�֘A�̏�����
	PlayerSystemInit();	// �v���C���[�֘A�̏�����
	EnemySystemInit();	// �G�֘A�̏�����


	return rtnFlag; 
}

// �������V�[��
void InitScene(void)
{
	PlayerGameInit();	// �v���C���[�̃Q�[�����[�v��������
	StageGameInit();	// �X�e�[�W�̃Q�[�����[�v��������
	EnemyGameInit();	// �G�̃Q�[�����[�v��������
}

// �^�C�g���V�[��
void TitleScene(void)
{
	if (keyTrgUp[KEY_SPACE] && !FadeInFlag && !FadeOutFlag)
	{
		FadeOutFlag = true;
	}

	// �^�C�g���`��
	TitleDraw();
}

// �^�C�g���`��
void TitleDraw(void)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�^�C�g���V�[���J�E���^�[  %d", SceneCounter);
	DrawBox(100, 100, 700, 500, GetColor(0, 0, 255), true);
}

// �Q�[�����C���V�[��
void GameScene(void)
{
	// �X�y�[�X�������ꂽ��t�F�[�h�A�E�g����
	if (keyTrgUp[KEY_SPACE] && !FadeInFlag && !FadeOutFlag)
	{
		FadeOutFlag = true;
	}

	// �e�I�u�W�F�N�g�̐��䏈��

	XY playerMoveDiff = PlayerControl(GetStageSize(), { 0,0 });	// �v���C���[�̐���
	XY mapPosMain = StageControl(playerMoveDiff);		// �X�e�[�W�̐���
	EnemyControl();		// �G�̐���

	// �Q�[���`��
	GameDraw(mapPosMain);
}

// �Q�[�����C���V�[���`��
void GameDraw(XY mapPos)
{

	// �V�[���J�E���^�[�`��
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�Q�[���V�[���J�E���^�[  %d", SceneCounter);

	// �X�e�[�W�̕`��
	if (pauseFlag)
	{
		SetDrawBright(50, 50, 50);
		StageGameDraw(mapPos);
		SetDrawBright(255, 255, 255);
	}
	else
	{
		DrawBox(100, 100, 700, 500, GetColor(255, 0, 0), true);
		// �e�I�u�W�F�N�g�`��
		StageGameDraw(mapPos);
		EnemyGameDraw();
		PlayerGameDraw(mapPos);
	}
}

// �Q�[���I�[�o�[�V�[��
void GameOverScene(void)
{
	if (keyTrgUp[KEY_SPACE] && !FadeInFlag && !FadeOutFlag)
	{
		FadeOutFlag = true;
	}
	GameOverDraw();
}

// �Q�[���I�[�o�[�V�[���`��
void GameOverDraw(void)
{
	DrawFormatString(0, 0, GetColor(255,255,255), "�Q�[���I�[�o�[�V�[���J�E���^�[  %d", SceneCounter);
	DrawBox(100, 100, 700, 500, GetColor(0, 255, 0), true);
}