//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "keycheck.h"

// 変数宣言
CHARACTER player;
int playerImage[PLAYER_IMAGENUM_Y][PLAYER_IMAGENUM_X];

// プレイヤー情報の初期化
void PlayerSystemInit(void)
{
	// プレイヤーの画像読み込み
	LoadDivGraph(
		"image/character/kancho.png",
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
	// プレイヤー情報初期化
	player.animCnt = 0;
	player.animCnt = 10;
	player.dir = DIR_DOWN;
	player.lifeMax = PLAYER_LIFE_DEF;
	player.life = player.lifeMax;
	player.moveSpeed = PLAYER_SPEED_DEF;
	player.pos = { 100.0f,100.0f };
	player.size = { 32,32 };
	player.type = CHARA_PLAYER;
	player.visible = true;
}

// プレイヤー情報の描画
void PlayerGameDraw(void)
{
	player.animCnt++;
	DrawGraph(player.pos.x, player.pos.y, playerImage[player.dir][player.animCnt / 10 % 4], true);
}

// プレイヤーの制御処理
XY PlayerControl(void)
{
	XY playerPosRec = { (int)player.pos.x, (int)player.pos.y };
	DIR playerDirRec = player.dir;

	player.dir = DIR_MAX;

	// キー情報を取得する
	if (keyNow[KEY_DOWN]) player.dir = DIR_DOWN;
	if (keyNow[KEY_RIGHT]) player.dir = DIR_RIGHT;
	if (keyNow[KEY_LEFT]) player.dir = DIR_LEFT;
	if (keyNow[KEY_UP]) player.dir = DIR_UP;

	// 移動処理
	switch (player.dir)
	{
	case DIR_DOWN:
		player.pos.y += player.moveSpeed;
		break;
	case DIR_RIGHT:
		player.pos.x += player.moveSpeed;
		break;
	case DIR_LEFT:
		player.pos.x -= player.moveSpeed;
		break;
	case DIR_UP:
		player.pos.y -= player.moveSpeed;
		break;
	default:
		player.dir = playerDirRec;
		break;
	}

	return { (int)player.pos.x - playerPosRec.x ,(int)player.pos.y - playerPosRec.y };
}




