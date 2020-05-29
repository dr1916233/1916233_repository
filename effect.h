//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

//#pragma once//----------------------------------
// 定数宣言
#define SWORDEFFECT_MAX 16
#define PUNCHEFFECT_MAX 8
#define EFFECT_MAX 10 // 同時に描画できるエフェクトの最大数

// エフェクトの種類
enum EFFECT_TYPE
{
	EFFECT_TYPE_FIRESWORD,
	EFFECT_TYPE_PUNCH,
	EFFECT_TYPE_MAX
};

// 構造体
struct EFFECT
{
	EFFECT_TYPE effectType;
	CHARATYPE userType;
	CHARATYPE charaType;
	XY pos;
	XY imageSize;
	XY disToPos;
	int* image;
	int imageIndex;
};


// プロトタイプ宣言
void SceneChange(SCENE_ID sceneID, int brightCnt, bool fade);	// シーンのフェードイン/アウト処理(SCENE_ID シーンID, int 1フレームごとの加減数)
void EffectInit(void);
void SwordEffect(XY mapPos, int frameCnt, int effectCnt);
void EffectGameDraw(XY mapPos, int frameCnt);
void CreateGameEffect(CHARATYPE charaType, EFFECT_TYPE effectType, XY pos, DIR dir);
void FreeEffectImage(void);
void PunchEffect(XY mapPos, int frameCnt, int effectCnt);

// extern宣言
extern SCENE_ID scnID;
extern bool FadeOutFlag;
extern bool FadeInFlag;
extern bool gameFadeOutFlag;