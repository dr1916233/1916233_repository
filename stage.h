//#pragma once
//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

//#pragma once//----------------------------------

// 定数宣言
#define MAP_Y_FIELD 20
#define MAP_X_FIELD 30
#define MAP_IMAGESIZE_X	32	// マップ画像のX方向のサイズ
#define MAP_IMAGESIZE_Y	32	// マップ画像のY方向のサイズ

XY GetStageSize(void);

// プロトタイプ宣言	
void StageGameDraw(void);	// ステージ関連の描画
void StageSystemInit(void);	// ステージ関連の初期化
void StageGameInit(void);	// ステージゲーム関連の初期化
void StageControl(void);	// ステージの制御処理