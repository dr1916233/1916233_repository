//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "enemy.h"
#include "keycheck.h"
#include "effect.h"
#include "stage.h"
#include "player.h"
#include "item.h"



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
	free(GetInventoryPointer());
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
	ItemSystemInit();	// �A�C�e���̏�����

	return rtnFlag; 
}

// �������V�[��
void InitScene(void)
{
	PlayerGameInit();	// �v���C���[�̃Q�[�����[�v��������
	StageGameInit();	// �X�e�[�W�̃Q�[�����[�v��������
	EnemyGameInit();	// �G�̃Q�[�����[�v��������
	ItemGameInit(10);	// �A�C�e���̃Q�[�����[�v��������
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

	XY playerMoveDiff = PlayerControl(GetStageSize(), GetMapPos());	// �v���C���[�̐���
	XY mapPosMain = StageControl(playerMoveDiff);		// �X�e�[�W�̐���
	EnemyControl(playerMoveDiff,SceneCounter);		// �G�̐���
	ItemControl();	// �A�C�e���̐���

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
		EnemyGameDraw(mapPos);
		PlayerGameDraw(mapPos);
		ItemGameDraw(mapPos);
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

// ��`�̓����蔻��(�ڐG�F0�A��ڐG�F-1�A�_���[�W������ꍇ�F1�ȏ�̐���)
int RectHitCheckMain(CHARATYPE type, XY pos1,  XY size1)
{
	// �����̃L�����N�^�[�^�C�v�̏�ԕێ��p�ϐ�
	XY pos2 = {0,0};
	XY size2 = {0,0};
	// �����̃I�u�W�F�N�g�̍U���͎擾�p�ϐ�
	int attack = -1;
	
	// �������肽���I�u�W�F�N�g�����擾
	switch (type)
	{
	case CHARA_PLAYER:
		// pos1 = GetPlayerPos();
		// size2 = GetPlayerSize();
		//if ((pos1.x + size1.x > pos2.x) &&
		//	(pos1.x < pos2.x + size2.x) &&
		//	(pos1.y + size1.y > pos2.y) &&
		//	(pos1.y < pos2.y + size2.y))
		//{
		//	attack = -1;
		//}
		break;
	case CHARA_ENEMY:
		for (int en = 0; en < ENEMY_MAX; en++)
		{
			pos2 = GetEnemyPos(en);
			size2 = GetEnemySize(en);
	/*		if ((pos1.x + size1.x >= pos2.x) &&
				(pos1.y <= pos2.x + size2.x) &&
				(pos1.x <= pos2.x + size2.x) &&
				(pos1.y >= pos2.y - size2.y))
			{
				attack = 0;
			}*/
			if ((pos1.x + size1.x >= pos2.x) &&
				(pos1.y <= pos2.x + size2.x) &&
				(pos1.x <= pos2.x + size2.x) &&
				(pos1.y >= pos2.y - size2.y))
			{
				attack = 0;
			}
		}
		break;
	case CHARA_MAGIC:
		// pos1 = GetMagicPos();
		// size2 = GetMagicSize();
		//if ((pos1.x + size1.x > pos2.x) &&
		//	(pos1.x < pos2.x + size2.x) &&
		//	(pos1.y + size1.y > pos2.y) &&
		//	(pos1.y < pos2.y + size2.y))
		//{
		//	attack = -1;
		//}
		break;
	default:
		break;
	}
	
	return attack;
}

// �~�Ɖ~�̓����蔻��
int CircleHitCheckMain(CHARATYPE type, XY pos1, XY size1)
{
	// ��������I�u�W�F�N�g�̏��p�ϐ�
	XY pos2 = { 0,0 };
	XY size2 = { 0,0 };

	pos1.x += size1.x / 2;
	pos1.y += size1.y / 2;

	int attack = -1;

	switch (type)
	{
	case CHARA_PLAYER:
		break;
	case CHARA_ENEMY:
		for (int en = 0; en < ENEMY_MAX; en++)
		{
			pos2 = GetEnemyPos(en);
			size2 = GetEnemySize(en);
			// �摜�̐^�񒆂����W�̒��S�ɂ���
			pos2.x = pos2.x + size2.x / 2;
			pos2.y = pos2.y + size2.y / 2;
			size2.x = (size2.x + size2.y) / 2; // �摜�̏c�T�C�Y�Ɖ��T�C�Y�̔����̕��ς𔼌a�Ƃ��Ĕ�������
			if ((pos2.x - pos1.x) * (pos2.x - pos1.x) + (pos2.y - pos1.y) * (pos2.y - pos1.y) <= 22*22)
			{
				attack = 0;
			}
		}
		break;
	case CHARA_MAGIC:
		break;
	default:
		break;
	}

	return attack;
}

// �A�C�e���ƃv���C���[�̓����蔻��
void ItemHitCheckMain(XY pPos, XY pSize)
{
	for (int itemCnt = 0; itemCnt < ITEM_MAX; itemCnt++)
	{
		// �A�C�e���̍��W���擾
		XY itemPos = GetItemPos(itemCnt);

		if ((pPos.x + pSize.x > itemPos.x) &&
			(itemPos.x + ITEM_SIZE_X > pPos.x) &&
			(pPos.y + pSize.x > itemPos.y) &&
			(itemPos.y + ITEM_SIZE_Y > pPos.y))
		{
			if (keyTrgUp[KEY_E])
			{
				AddInventoryList(itemCnt);
				DeleteItem(itemCnt);
			}
		}
	}
}

// �v���C���[����ړ��\����W�̍��W�����Ĉړ��ł��邩�𒲂ׂ�
bool IsPassMain(XY playerPos)
{
	if (IsPass(playerPos)) return true;
	else return false;
}