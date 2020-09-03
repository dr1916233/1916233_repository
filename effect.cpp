//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "stage.h"
#include "effect.h"

// 変数宣言
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

// 戦闘エフェクトの画像用
int swordEffectImage[SWORDEFFECT_MAX];
int swordEffectIndex;

EFFECT effectMaster[EFFECT_TYPE_MAX];
EFFECT effect[EFFECT_TYPE_MAX][EFFECT_MAX];

// フェード処理の初期化
void EffectInit(void)
{
	circleCntIn = 0;
	circleCntOut = 900;
	bright = 0;
	FadeInFlag = true;
	FadeOutFlag = false;
	pauseFlag = false;
	
	// エフェクトの初期化
	effectMaster[EFFECT_TYPE_FIRESWORD].image = (int*)malloc(sizeof(int) * SWORDEFFECT_MAX);
	LoadDivGraph("image/effect/fireSword.png", 16, 1, 16, 96, 72, effectMaster[EFFECT_TYPE_FIRESWORD].image);
	effectMaster[EFFECT_TYPE_FIRESWORD].disToPos = { 96,96 };
	effectMaster[EFFECT_TYPE_FIRESWORD].imageIndex = -1;
	effectMaster[EFFECT_TYPE_FIRESWORD].imageSize = { 96,72 };
	effectMaster[EFFECT_TYPE_FIRESWORD].pos = { 0,0 };
	effectMaster[EFFECT_TYPE_FIRESWORD].effectType = EFFECT_TYPE_FIRESWORD;

	// パンチのデータ初期化
	effectMaster[EFFECT_TYPE_PUNCH].image = (int*)malloc(sizeof(int) * PUNCHEFFECT_MAX);
	LoadDivGraph("image/effect/punch.png", 8, 8, 1, 32, 32, effectMaster[EFFECT_TYPE_PUNCH].image);
	effectMaster[EFFECT_TYPE_PUNCH].disToPos = { 0,0 };
	effectMaster[EFFECT_TYPE_PUNCH].imageIndex = -1;
	effectMaster[EFFECT_TYPE_PUNCH].imageSize = { 32,32 };
	effectMaster[EFFECT_TYPE_PUNCH].pos = { 0,0 };
	effectMaster[EFFECT_TYPE_PUNCH].effectType = EFFECT_TYPE_PUNCH;

	// 共通の初期化
	for (int effectType = 0; effectType < EFFECT_TYPE_MAX; effectType++)
	{
		for (int effectCnt = 0; effectCnt < EFFECT_MAX; effectCnt++)
		{
			effect[effectType][effectCnt].imageIndex = -1;
		}
	}
}

// シーンのフェードイン フェードアウト
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

// ゲームエフェクトの生成
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

// ゲームエフェクトの描画
void EffectGameDraw(XY mapPos,int frameCnt)
{
	for (int effectCnt = 0; effectCnt < EFFECT_MAX; effectCnt++)
	{
		SwordEffect(mapPos, frameCnt, effectCnt);
		PunchEffect(mapPos, frameCnt, effectCnt);
	}
}

// 剣エフェクトの描画
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

// パンチエフェクトの描画
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

// エフェクトの画像ハンドル用変数のメモリ解放用
void FreeEffectImage(void)
{
	for (int effectType = 0; effectType < EFFECT_TYPE_MAX; effectType++)
	{
		free(effectMaster[effectType].image);
	}
}

