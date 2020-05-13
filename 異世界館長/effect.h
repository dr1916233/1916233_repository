//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

//#pragma once//----------------------------------

// プロトタイプ宣言
void SceneChange(SCENE_ID sceneID, int brightCnt, bool fade);	// シーンのフェードイン/アウト処理(SCENE_ID シーンID, int 1フレームごとの加減数)
void EffectInit(void);

// extern宣言
extern SCENE_ID scnID;
extern bool FadeOutFlag;
extern bool FadeInFlag;
extern bool pauseFlag;
extern bool gameFadeOutFlag;