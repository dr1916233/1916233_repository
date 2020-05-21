//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

//#pragma once//----------------------------------

// 定数宣言
#define MAP_X_FIELD 40		// フィールドの横大きさ
#define MAP_Y_FIELD 30		// フィールドの縦大きさ
#define MAP_IMAGESIZE_X	32	// マップ画像のX方向のサイズ
#define MAP_IMAGESIZE_Y	32	// マップ画像のY方向のサイズ

XY GetStageSize(void);
XY GetMapPos(void);

// プロトタイプ宣言	
void StageGameDraw(XY mapPos);				// ステージ関連の描画
void StageSystemInit(void);					// ステージ関連の初期化
void StageGameInit(void);					// ステージゲーム関連の初期化
XY StageControl(XY playerMoveDiff);			// ステージの制御処理
bool IsPass(XY pos);						// プレイヤーが次のブロックを通過できるか判定
XY PosToIndex(XY pos);						// プレイヤーの座標をマップのインデックスに変換して返す