//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "keycheck.h"
#include "effect.h"

// 変数宣言
CHARACTER player;
int playerImage[2][PLAYER_IMAGENUM_Y * PLAYER_IMAGENUM_X + 4];

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
		playerImage[0],
		true
	);

	LoadDivGraph("image/character/dougi_kancho_attack.png", 4, 4, 1, 32, 32, &playerImage[0][16], true);

	LoadDivGraph(
		"image/character/brave_kancho.png",
		PLAYER_IMAGENUM_X * PLAYER_IMAGENUM_Y,
		PLAYER_IMAGENUM_X,
		PLAYER_IMAGENUM_Y,
		PLAYER_IMAGESIZE_X,
		PLAYER_IMAGESIZE_Y,
		playerImage[1],
		true
	);

	LoadDivGraph("image/character/brave_kancho_attack.png", 4, 4, 1, 32, 32, &playerImage[1][16], true);
}

// プレイヤーのゲーム毎初期化
int PlayerGameInit(void)
{
	// プレイヤー情報初期化
	player.animCnt = 0;
	player.attack = 10;
	player.dir = DIR_DOWN;
	player.lifeMax = PLAYER_LIFE_DEF;
	player.life = player.lifeMax;
	player.moveSpeed = PLAYER_SPEED_DEF;
	player.pos = { 100.0f,180.0f };
	player.size = { 32,32 };
	player.offsetSize = { PLAYER_OFFSET_X,0 };
	player.type = CHARA_PLAYER;
	player.visible = true;
	player.inventoryCnt = PLAYER_INVENTORY_DEF;
	player.statusPoint = 4;

	return player.inventoryCnt;
}

// プレイヤー情報の描画
void PlayerGameDraw(XY mapPos)
{
	player.animCnt++;
	if (player.imageLockCnt > 0) DrawGraph(player.pos.x - mapPos.x, player.pos.y - mapPos.y + SCREEN_OFFSET_Y, playerImage[0][PLAYER_IMAGENUM_Y * PLAYER_IMAGENUM_X + player.dir], true);
	else DrawGraph(player.pos.x - mapPos.x, player.pos.y - mapPos.y + SCREEN_OFFSET_Y, playerImage[0][(player.animCnt / 10 % 4) + player.dir * 4], true);
	DrawFormatString(50, 100, GetColor(255, 255, 255), "プレイヤーのチップ : %d,%d", (int)player.pos.x / 32, (int)player.pos.y / 32);

	DrawBox(
		player.pos.x -player.offsetSize.x - mapPos.x,
		player.pos.y - player.offsetSize.y - mapPos.y,
		player.pos.x + player.offsetSize.x - mapPos.x,
		player.pos.y + player.offsetSize.y - mapPos.y,
		GetColor(255, 255, 255),
		false
	);
}

// プレイヤーの制御処理
XY_F PlayerControl(XY chipNum, XY_F mapPos)
{
	XY playerPosRec = { (int)player.pos.x, (int)player.pos.y };
	DIR playerDirRec = player.dir;

	player.dir = DIR_MAX;
	float speed = (player.imageLockCnt > 0) ? 0.0f : player.moveSpeed;

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
	XY_F camDiff = { 0,0 };
	// 移動先座標保存用
	XY_F playerPosCopy;
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
		playerPosCopy.y += speed;
		// プレイヤーの左右の座標保持用
		playerHitLeft = { (int)playerPosCopy.x,(int)playerPosCopy.y };
		playerHitRight = { (int)playerPosCopy.x,(int)playerPosCopy.y };;

		// プレイヤーの足元の実座標を右端と左端で取る
		playerHitLeft.y += PLAYER_IMAGESIZE_Y;
		playerHitRight.y += PLAYER_IMAGESIZE_Y;
		playerHitLeft.x += PLAYER_OFFSET_X;
		playerHitRight.x += PLAYER_OFFSET_X + PLAYER_SIZE_X;

		// コピーが移動できたときは実態を移動させ、カメラの位置をずらす
		if (IsPassMain(playerHitLeft) && IsPassMain(playerHitRight))
		{
			if (player.pos.y < chipNum.y * 32 - 32) player.pos.y += speed;
			if (mapPos.y + SCREEN_SIZE_Y - SCREEN_OFFSET_Y < chipNum.y * 32 && player.pos.y > 100 + SCREEN_OFFSET_Y) camDiff.y += speed;
		}
		break;
	case DIR_RIGHT:
		// コピーの座標を進める
		playerPosCopy.x += speed;

		// プレイヤーの上下の座標保持用
		playerHitTop = { (int)playerPosCopy.x,(int)playerPosCopy.y };
		playerHitUnder = { (int)playerPosCopy.x,(int)playerPosCopy.y };

		// プレイヤーの右側の座標を上と下で取る
		playerHitTop.x += PLAYER_OFFSET_X + PLAYER_SIZE_X;
		playerHitUnder.x += PLAYER_OFFSET_X + PLAYER_SIZE_X;
		playerHitUnder.y += PLAYER_SIZE_Y;

		// コピーが移動できたときは実態を移動させ、カメラの位置をずらす
		if (IsPassMain(playerHitTop) && IsPassMain(playerHitUnder))
		{
			if (player.pos.x < chipNum.x * 32 - 32) player.pos.x += speed;
			if (mapPos.x + SCREEN_SIZE_X < chipNum.x * 32 && player.pos.x > 100) camDiff.x += speed;
		}
		break;
	case DIR_LEFT:
		// コピーの座標を進める
		playerPosCopy.x -= speed;

		// プレイヤーの上下の座標保持用
		playerHitTop = { (int)playerPosCopy.x,(int)playerPosCopy.y };;
		playerHitUnder = { (int)playerPosCopy.x,(int)playerPosCopy.y };;

		// プレイヤーの左側の座標を上と下で取る
		playerHitTop.x += PLAYER_OFFSET_X;
		playerHitUnder.x += PLAYER_OFFSET_X;
		playerHitUnder.y += PLAYER_SIZE_Y;

		// コピーが移動できたときは実態を移動させ、カメラの位置をずらす
		if (IsPassMain(playerHitTop) && IsPassMain(playerHitUnder))
		{
			if (player.pos.x > 0) player.pos.x -= speed;
			if (mapPos.x > 0 && player.pos.x < chipNum.x * 32 - 100) camDiff.x -= speed;
		}
		break;
	case DIR_UP:
		// コピーの座標を進める
		playerPosCopy.y -= speed;

		// プレイヤーの左右の座標保持用
		playerHitLeft = { (int)playerPosCopy.x,(int)playerPosCopy.y };
		playerHitRight = { (int)playerPosCopy.x,(int)playerPosCopy.y };

		// プレイヤーの上側の座標を左右で取る
		playerHitLeft.x += PLAYER_OFFSET_X;
		playerHitRight.x += PLAYER_OFFSET_X + PLAYER_SIZE_X;

		// コピーが移動できたときは実態を移動させ、カメラの位置をずらす
		if (IsPassMain(playerHitLeft) && IsPassMain(playerHitRight))
		{
			if (player.pos.y > 0) player.pos.y -= speed;
			if (mapPos.y > 0 && player.pos.y < chipNum.y * 32 - 100) camDiff.y -= speed;
		}
		break;
	default:
		// プレイヤーが動かなかった場合は元の移動方向を代入
		player.dir = playerDirRec;
		break;
	}
	

	// プレイヤーの攻撃処理
	if (keyTrgUp[KEY_NORMAL_ATTACK])
	{
		PlayerAttack();
		player.imageLockCnt = 144;
	}

	XY attackPos = { (int)player.pos.x + player.size.x / 2,(int)player.pos.y + player.size.y / 2 };

	if (keyTrgUp[KEY_SPECIAL_ATTACK])
	{
		CreateGameEffect(CHARA_PLAYER, EFFECT_TYPE_FIRESWORD, attackPos, player.dir);
		player.imageLockCnt = 144;
	}

	// アイテムとの当たり判定
	ItemHitCheckMain({ (int)player.pos.x + PLAYER_OFFSET_X,(int)player.pos.y }, {PLAYER_SIZE_X,PLAYER_SIZE_Y});

	// プレイヤーのマップイベント
	GetEventMain({ (int)player.pos.x,(int)player.pos.y });

	// イメージロックカウントをカウントダウン
	if (player.imageLockCnt > 0) player.imageLockCnt--;

	return camDiff;
}

void PlayerAttack(void)
{
	XY attackHitPos = { (int)player.pos.x + player.size.x / 2,  (int)player.pos.y + player.size.y / 2 };
	XY attackSize = { 32,32 };

	switch (player.dir)
	{
	case DIR_DOWN:
		attackHitPos.y += 32;
		break;
	case DIR_RIGHT:
		attackHitPos.x += 32;
		break;
	case DIR_LEFT:
		attackHitPos.x -= 32;
		break;
	case DIR_UP:
		attackHitPos.y -= 32;
		break;
	default:
		break;
	}

	CreateGameEffect(CHARA_PLAYER, EFFECT_TYPE_PUNCH, attackHitPos, player.dir);

	if (CircleHitCheckMain(CHARA_ENEMY, attackHitPos, attackSize,0))
	{
		DoDamageMain(CHARA_ENEMY, player.attack);
		InsertDamageListMain(CHARA_ENEMY, player.attack);
	}
}

XY_F GetPlayerPos(void)
{
	return player.pos;
}

// プレイヤーのポインターを取得
CHARACTER* GetPlayerPointer(void)
{
	return &player;
}

// プレイヤーの情報を取得
CHARACTER GetPlayer(void)
{
	return player;
}