//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "player.h"

// 変数宣言
int playerImage[PLAYER_IMAGENUM_Y][PLAYER_IMAGENUM_X];

// プレイヤー情報の初期化
void PlayerSystemInit(void)
{
	// プレイヤーの画像読み込み
	LoadDivGraph(
		"image/kancho.png",
		PLAYER_IMAGENUM_X * PLAYER_IMAGENUM_Y,
		PLAYER_IMAGENUM_X,
		PLAYER_IMAGENUM_Y,
		PLAYER_IMAGESIZE_X,
		PLAYER_IMAGESIZE_Y,
		*playerImage,
		true
	);
}

// プレイヤーのゲーム毎初期化
void PlayerGameInit(void)
{

}

// プレイヤー情報の描画
void PlayerGameDraw(void)
{
	DrawGraph(100, 100, playerImage[0][0], true);
}

// プレイヤーの制御処理
void PlayerControl(void)
{

}



