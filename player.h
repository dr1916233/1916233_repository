//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

//#pragma once//----------------------------------

// 定数宣言
#define PLAYER_IMAGENUM_X 4	// プレイヤー画像のX方向の数
#define PLAYER_IMAGENUM_Y 4	// プレイヤー画像のY方向の数
#define PLAYER_IMAGESIZE_X	32	// プレイヤー画像のX方向のサイズ
#define PLAYER_IMAGESIZE_Y	32	// プレイヤー画像のY方向のサイズ

#define PLAYER_LIFE_DEF	100	// プレイヤーのデフォルトHP
#define PLAYER_SPEED_DEF	3	// プレイヤーのデフォルト移動速度

// --------------------
// 構造体
// --------------------



// プロトタイプ宣言

void PlayerSystemInit(void);	// プレイヤー情報の初期化
void PlayerGameInit(void);		// プレイヤーのゲーム関係の初期化
void PlayerGameDraw(XY mapPos);		// プレイヤーのゲーム描画
XY PlayerControl(XY chipNum, XY mapPos);	// プレイヤーの制御処理
