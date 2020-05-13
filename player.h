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

// プロトタイプ宣言

void PlayerSystemInit(void);	// プレイヤー情報の初期化
void PlayerGameInit(void);		// プレイヤーのゲーム関係の初期化
void PlayerGameDraw(void);		// プレイヤーのゲーム描画
void PlayerControl(void);		// プレイヤーの制御処理