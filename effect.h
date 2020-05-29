//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

//#pragma once//----------------------------------
// 定数宣言
#define SWORDEFFECT_MAX 16

// エフェクトの種類
enum EFFECT_TYPE
{
	EFFECT_TYPE_FIRESWORD,
	EFFECT_TYPE_MAX
};

// 構造体
struct EFFECT
{
	EFFECT_TYPE type;
	XY pos;
	XY imageSize;
	int* image;
	int imageIndex;
};


// プロトタイプ宣言
void SceneChange(SCENE_ID sceneID, int brightCnt, bool fade);	// シーンのフェードイン/アウト処理(SCENE_ID シーンID, int 1フレームごとの加減数)
void EffectInit(void);
void SwordEffect(XY mapPos, int frameCnt);
void EffectGameDraw(XY mapPos, int frameCnt);
void CreateGameEffect(EFFECT_TYPE type, XY pos);

// extern宣言
extern SCENE_ID scnID;
extern bool FadeOutFlag;
extern bool FadeInFlag;
extern bool gameFadeOutFlag;