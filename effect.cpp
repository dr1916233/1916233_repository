//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "stage.h"
#include "effect.h"

// �ϐ��錾
int bright;
int circleCntIn;
int circleCntOut;
bool FadeInFlag;
bool FadeOutFlag;
bool pauseFlag;

bool stageFadeInFlag;
bool stageFadeOutFlag;

bool gameFadeInFlag;
bool gameFadeOutFlag;

// �퓬�G�t�F�N�g�̉摜�p
int swordEffectImage[SWORDEFFECT_MAX];
int swordEffectIndex;

EFFECT effectMaster[EFFECT_TYPE_MAX];
EFFECT effect[EFFECT_TYPE_MAX][EFFECT_MAX];

// �t�F�[�h�����̏�����
void EffectInit(void)
{
	circleCntIn = 0;
	circleCntOut = 900;
	bright = 0;
	FadeInFlag = true;
	FadeOutFlag = false;
	pauseFlag = false;
	
	// �G�t�F�N�g�̏�����
	effectMaster[EFFECT_TYPE_FIRESWORD].image = (int*)malloc(sizeof(int) * SWORDEFFECT_MAX);
	LoadDivGraph("image/effect/fireSword.png", 16, 1, 16, 96, 72, effectMaster[EFFECT_TYPE_FIRESWORD].image);
	effectMaster[EFFECT_TYPE_FIRESWORD].disToPos = { 96,96 };
	effectMaster[EFFECT_TYPE_FIRESWORD].imageIndex = -1;
	effectMaster[EFFECT_TYPE_FIRESWORD].imageSize = { 96,72 };
	effectMaster[EFFECT_TYPE_FIRESWORD].pos = { 0,0 };
	effectMaster[EFFECT_TYPE_FIRESWORD].effectType = EFFECT_TYPE_FIRESWORD;

	// �p���`�̃f�[�^������
	effectMaster[EFFECT_TYPE_PUNCH].image = (int*)malloc(sizeof(int) * PUNCHEFFECT_MAX);
	LoadDivGraph("image/effect/punch.png", 8, 8, 1, 32, 32, effectMaster[EFFECT_TYPE_PUNCH].image);
	effectMaster[EFFECT_TYPE_PUNCH].disToPos = { 0,0 };
	effectMaster[EFFECT_TYPE_PUNCH].imageIndex = -1;
	effectMaster[EFFECT_TYPE_PUNCH].imageSize = { 32,32 };
	effectMaster[EFFECT_TYPE_PUNCH].pos = { 0,0 };
	effectMaster[EFFECT_TYPE_PUNCH].effectType = EFFECT_TYPE_PUNCH;

	// ���ʂ̏�����
	for (int effectType = 0; effectType < EFFECT_TYPE_MAX; effectType++)
	{
		for (int effectCnt = 0; effectCnt < EFFECT_MAX; effectCnt++)
		{
			effect[effectType][effectCnt].imageIndex = -1;
		}
	}
}

// �V�[���̃t�F�[�h�C�� �t�F�[�h�A�E�g
void SceneChange(SCENE_ID sceneID, int brightCnt, bool fade)
{
	if (FadeInFlag)
	{
		if (bright <= 255)
		{
			bright += brightCnt;
			SetDrawBright(bright, bright, bright);
			if (bright >= 255)
			{
				bright = 255;
				FadeInFlag = false;
			}
		}
	}

	if (FadeOutFlag)
	{
		if (bright >= 0)
		{
			bright -= brightCnt;
			SetDrawBright(bright, bright, bright);
			if (bright <= 0)
			{
				bright = 0;
				FadeOutFlag = false;
				FadeInFlag = true;
				if (fade)
				{
					scnID = (SCENE_ID)(sceneID + 1);
					if (scnID >= SCENE_MAX)
					{
						scnID = SCENE_INIT;
					}
				}
			}
		}
	}
}


void StageFade(int brightC)
{
	if (stageFadeInFlag)
	{
		if (bright <= 255)
		{
			bright += brightC;
			SetDrawBright(bright, bright, bright);
			if (bright >= 255)
			{
				bright = 255;
				stageFadeInFlag = false;
			}
		}
	}
	if (stageFadeOutFlag)
	{
		if (bright >= 0)
		{
			bright -= brightC;
			SetDrawBright(bright, bright, bright);
			if (bright <= 0)
			{
				bright = 0;
				stageFadeInFlag = true;
				stageFadeOutFlag = false;
			}
		}
	}
}

// �Q�[���G�t�F�N�g�̐���
void CreateGameEffect(CHARATYPE charaType, EFFECT_TYPE effectType, XY pos, DIR dir)
{
	for (int effectCnt = 0; effectCnt < EFFECT_MAX; effectCnt++)
	{
		if (effect[effectType][effectCnt].imageIndex < 0)
		{
			effect[effectType][effectCnt] = effectMaster[effectType];

			effect[effectType][effectCnt].charaType = charaType;

			effect[effectType][effectCnt].imageIndex = 0;

			pos.x -= effect[effectType][effectCnt].imageSize.x / 2;
			pos.y -= effect[effectType][effectCnt].imageSize.y / 2;

			effect[effectType][effectCnt].pos = pos;

			switch (dir)
			{
			case DIR_DOWN:
				effect[effectType][effectCnt].pos.y += effect[effectType][effectCnt].disToPos.y;
				break;
			case DIR_RIGHT:
				effect[effectType][effectCnt].pos.x += effect[effectType][effectCnt].disToPos.x;
				break;
			case DIR_LEFT:
				effect[effectType][effectCnt].pos.x -= effect[effectType][effectCnt].disToPos.x;
				break;
			case DIR_UP:
				effect[effectType][effectCnt].pos.y -= effect[effectType][effectCnt].disToPos.y;
				break;
			default:
				break;
			}
			break;
		}
	}
}

// �Q�[���G�t�F�N�g�̕`��
void EffectGameDraw(XY mapPos,int frameCnt)
{
	for (int effectCnt = 0; effectCnt < EFFECT_MAX; effectCnt++)
	{
		SwordEffect(mapPos, frameCnt, effectCnt);
		PunchEffect(mapPos, frameCnt, effectCnt);
	}
}

// ���G�t�F�N�g�̕`��
void SwordEffect(XY mapPos,int frameCnt,int effectCnt)
{
	if (effect[EFFECT_TYPE_FIRESWORD][effectCnt].imageIndex >= 0)
	{
		DrawGraph(
			effect[EFFECT_TYPE_FIRESWORD][effectCnt].pos.x - mapPos.x,
			effect[EFFECT_TYPE_FIRESWORD][effectCnt].pos.y + SCREEN_OFFSET_Y - mapPos.y,
			effect[EFFECT_TYPE_FIRESWORD][effectCnt].image[effect[EFFECT_TYPE_FIRESWORD][effectCnt].imageIndex],
			true
		);

		if(frameCnt % 10 == 0) 	effect[EFFECT_TYPE_FIRESWORD][effectCnt].imageIndex++;
		if (effect[EFFECT_TYPE_FIRESWORD][effectCnt].imageIndex >= SWORDEFFECT_MAX - 1) effect[EFFECT_TYPE_FIRESWORD][effectCnt].imageIndex = -1;
	}
}

// �p���`�G�t�F�N�g�̕`��
void PunchEffect(XY mapPos, int frameCnt, int effectCnt)
{
	if (effect[EFFECT_TYPE_PUNCH][effectCnt].imageIndex >= 0)
	{
		DrawGraph(
			effect[EFFECT_TYPE_PUNCH][effectCnt].pos.x - mapPos.x,
			effect[EFFECT_TYPE_PUNCH][effectCnt].pos.y + SCREEN_OFFSET_Y - mapPos.y,
			effect[EFFECT_TYPE_PUNCH][effectCnt].image[effect[EFFECT_TYPE_PUNCH][effectCnt].imageIndex],
			true
		);

		if (frameCnt % 10 == 0) effect[EFFECT_TYPE_PUNCH][effectCnt].imageIndex++;
		if (effect[EFFECT_TYPE_PUNCH][effectCnt].imageIndex >= PUNCHEFFECT_MAX - 1) effect[EFFECT_TYPE_PUNCH][effectCnt].imageIndex = -1;
	}
}

// �G�t�F�N�g�̉摜�n���h���p�ϐ��̃���������p
void FreeEffectImage(void)
{
	for (int effectType = 0; effectType < EFFECT_TYPE_MAX; effectType++)
	{
		free(effectMaster[effectType].image);
	}
}

