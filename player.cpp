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
	player.pos = { 10.0f,180.0f };
	player.size = { 32,32 };
	player.offsetSize = { PLAYER_OFFSET_X,0 };
	player.type = CHARA_PLAYER;
	player.visible = true;
}

// プレイヤー情報の描画
void PlayerGameDraw(XY mapPos)
{
	player.animCnt++;
	DrawGraph(player.pos.x - mapPos.x, player.pos.y - mapPos.y, playerImage[player.dir][player.animCnt / 10 % 4], true);
	DrawFormatString(50, 100, GetColor(255, 255, 255), "プレイヤーのチップ : %d,%d", (int)player.pos.x / 32, (int)player.pos.y / 32);
}

// プレイヤーの制御処理
XY PlayerControl(XY chipNum, XY mapPos)
{
	XY playerPosRec = { (int)player.pos.x, (int)player.pos.y };
	DIR playerDirRec = player.dir;

	player.dir = DIR_MAX;

	// キー情報を取得する
	if (keyNow[KEY_DOWN])
	{
		player.dir = DIR_DOWN;
	}

	if (keyNow[KEY_RIGHT])
	{
		player.dir = DIR_RIGHT;
	}

	if (keyNow[KEY_LEFT])
	{
		player.dir = DIR_LEFT;
	}


	if (keyNow[KEY_UP])
	{
		player.dir = DIR_UP;
	}
	// 移動量計算用
	XY camDiff = { 0,0 };
	// 移動先座標保存用
	XY playerPosCopy;
	playerPosCopy.x = player.pos.x;
	playerPosCopy.y = player.pos.y;
	// プレイヤーの上下左右の座標保持用
	XY playerHitLeft = { 0,0 };
	XY playerHitRight = { 0,0 };
	XY playerHitTop = { 0,0 };
	XY playerHitUnder = { 0,0 };

	// 移動処理
	switch (player.dir)
	{
	case DIR_DOWN:
		// コピーの座標を進める
		playerPosCopy.y += player.moveSpeed;
		// プレイヤーの左右の座標保持用
		playerHitLeft = playerPosCopy;
		playerHitRight = playerPosCopy;

		// プレイヤーの足元の実座標を右端と左端で取る
		playerHitLeft.y += PLAYER_IMAGESIZE_Y;
		playerHitRight.y += PLAYER_IMAGESIZE_Y;
		playerHitLeft.x += PLAYER_OFFSET_X;
		playerHitRight.x += PLAYER_OFFSET_X + PLAYER_SIZE_X;

		// コピーが移動できたときは実態を移動させ、カメラの位置をずらす
		if (IsPassMain(playerHitLeft)&& IsPassMain(playerHitRight) && CircleHitCheckMain(CHARA_ENEMY,playerPosCopy,player.size) == -1)
		{
			if (player.pos.y < chipNum.y * 32 - 32) player.pos.y += player.moveSpeed;
			if (mapPos.y + SCREEN_SIZE_Y < chipNum.y * 32 && player.pos.y > 100) camDiff.y += player.moveSpeed;
		}
		break;
	case DIR_RIGHT:
		// コピーの座標を進める
		playerPosCopy.x += player.moveSpeed;

		// プレイヤーの上下の座標保持用
		playerHitTop = playerPosCopy;
		playerHitUnder = playerPosCopy;

		// プレイヤーの右側の座標を上と下で取る
		playerHitTop.x += PLAYER_OFFSET_X + PLAYER_SIZE_X;
		playerHitUnder.x += PLAYER_OFFSET_X + PLAYER_SIZE_X;
		playerHitUnder.y += PLAYER_SIZE_Y;

		// コピーが移動できたときは実態を移動させ、カメラの位置をずらす
		if (IsPassMain(playerHitTop) && IsPassMain(playerHitUnder) && CircleHitCheckMain(CHARA_ENEMY, playerPosCopy, player.size) == -1)
		{
			if (player.pos.x < chipNum.x * 32 - 32) player.pos.x += player.moveSpeed;
			if (mapPos.x + SCREEN_SIZE_X < chipNum.x * 32 && player.pos.x > 100) camDiff.x += player.moveSpeed;
		}
		break;
	case DIR_LEFT:
		// コピーの座標を進める
		playerPosCopy.x -= player.moveSpeed;

		// プレイヤーの上下の座標保持用
		playerHitTop = playerPosCopy;
		playerHitUnder = playerPosCopy;

		// プレイヤーの左側の座標を上と下で取る
		playerHitTop.x += PLAYER_OFFSET_X;
		playerHitUnder.x += PLAYER_OFFSET_X;
		playerHitUnder.y += PLAYER_SIZE_Y;

		// コピーが移動できたときは実態を移動させ、カメラの位置をずらす
		if (IsPassMain(playerHitTop) && IsPassMain(playerHitUnder) && CircleHitCheckMain(CHARA_ENEMY, playerPosCopy, player.size) == -1)
		{
			if (player.pos.x > 0) player.pos.x -= player.moveSpeed;
			if (mapPos.x > 0 && player.pos.x < chipNum.x * 32 - 100) camDiff.x -= player.moveSpeed;
		}
		break;
	case DIR_UP:
		// コピーの座標を進める
		playerPosCopy.y -= player.moveSpeed;

		// プレイヤーの左右の座標保持用
		playerHitLeft = playerPosCopy;
		playerHitRight = playerPosCopy;

		// プレイヤーの上側の座標を左右で取る
		playerHitLeft.x += PLAYER_OFFSET_X;
		playerHitRight.x += PLAYER_OFFSET_X + PLAYER_SIZE_X;

		// コピーが移動できたときは実態を移動させ、カメラの位置をずらす
		if (IsPassMain(playerHitLeft) && IsPassMain(playerHitRight) && CircleHitCheckMain(CHARA_ENEMY, playerPosCopy, player.size) == -1)
		{
			if (player.pos.y > 0) player.pos.y -= player.moveSpeed;
			if (mapPos.y > 0 && player.pos.y < chipNum.y * 32 - 100) camDiff.y -= player.moveSpeed;
		}
		break;
	default:
		// プレイヤーが動かなかった場合は元の移動方向を代入
		player.dir = playerDirRec;
		break;
	}

	// アイテムとの当たり判定
	ItemHitCheckMain({ (int)player.pos.x + PLAYER_OFFSET_X,(int)player.pos.y }, {PLAYER_SIZE_X,PLAYER_SIZE_Y});

	return camDiff;
}




