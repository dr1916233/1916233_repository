//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "effect.h"

// �ϐ��錾
int bright;
int circleCntIn;
int circleCntOut;
bool FadeInFlag;
bool FadeOutFlag;
bool pauseFlag;

bool gameFadeInFlag;
bool gameFadeOutFlag;

// �퓬�G�t�F�N�g�̉摜�p
int swordEffectImage[SWORDEFFECT_MAX];
int swordEffectIndex;

EFFECT effect[EFFECT_TYPE_MAX];

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
	effect[EFFECT_TYPE_FIRESWORD].image = (int*)malloc(sizeof(int) * SWORDEFFECT_MAX);
	LoadDivGraph("image/effect/fireSword.png", 16, 1, 16, 96, 72, effect[EFFECT_TYPE_FIRESWORD].image);
	effect[EFFECT_TYPE_FIRESWORD].imageIndex = -1;
	effect[EFFECT_TYPE_FIRESWORD].imageSize = { 96,72 };
	effect[EFFECT_TYPE_FIRESWORD].pos = { 0,0 };
	effect[EFFECT_TYPE_FIRESWORD].type = EFFECT_TYPE_FIRESWORD;
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

// �Q�[���G�t�F�N�g�̐���
void CreateGameEffect(EFFECT_TYPE type,XY pos)
{
	effect[type].imageIndex = 0;

	pos.x -= effect[type].imageSize.x;
	pos.x -= effect[type].imageSize.y;

	effect[type].pos = pos;
}

// �Q�[���G�t�F�N�g�̕`��
void EffectGameDraw(XY mapPos,int frameCnt)
{
	SwordEffect(mapPos,frameCnt);
}

// ���G�t�F�N�g�̕`��
void SwordEffect(XY mapPos,int frameCnt)
{
	if (effect[EFFECT_TYPE_FIRESWORD].imageIndex >= 0)
	{
		DrawGraph(
			effect[EFFECT_TYPE_FIRESWORD].pos.x - mapPos.x,
			effect[EFFECT_TYPE_FIRESWORD].pos.y + SCREEN_OFFSET_Y - mapPos.y,
			effect[EFFECT_TYPE_FIRESWORD].image[effect[EFFECT_TYPE_FIRESWORD].imageIndex], 
			true
		);

		if(frameCnt % 10 == 0) 	effect[EFFECT_TYPE_FIRESWORD].imageIndex++;
		if (effect[EFFECT_TYPE_FIRESWORD].imageIndex >= SWORDEFFECT_MAX - 1) effect[EFFECT_TYPE_FIRESWORD].imageIndex = -1;
	}
}

