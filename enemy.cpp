//----------------------------------	
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "enemy.h"

// 変数宣言
CHARACTER enemyMaster[ENEMY_TYPE_MAX];	// 敵の変数
CHARACTER enemy[ENEMY_MAX];				// 敵の総数
int enemyImage[ENEMY_TYPE_MAX][16];		// 敵の画像の種類

// 敵の初期化
void EnemySystemInit(void)
{
	for (int cnt = 0; cnt < ENEMY_TYPE_MAX; cnt++)
	{
		enemyMaster[cnt].offsetSize = { 0,0 };	// 敵の初期オフセットサイズ
		enemyMaster[cnt].animCnt = 0;			// 敵の初期アニメーションカウント
		enemyMaster[cnt].life = enemyMaster[cnt].lifeMax;	// 敵の初期ライフ
		enemyMaster[cnt].dir = DIR_DOWN;		// 敵の初期向き
		enemyMaster[cnt].type = CHARA_ENEMY;
		enemyMaster[cnt].moveFlag = true;
	}

	//------------------------------------------------------------------------------------------
// スライム

	enemyMaster[ENEMY_TYPE_SLIME].size = { 32,32 };				// スライムのサイズ
	enemyMaster[ENEMY_TYPE_SLIME].offsetSize = { 3,7 };			// スライムのオフセットサイズ
	enemyMaster[ENEMY_TYPE_SLIME].lifeMax = 2;					// スライムのライフ
	enemyMaster[ENEMY_TYPE_SLIME].moveSpeed = 1;				// スライムのスピード
	enemyMaster[ENEMY_TYPE_SLIME].enemyType = ENEMY_TYPE_SLIME;	// 敵の種類をスライムにセット

	LoadDivGraph("image/character/スライムfin完.png",
		16, 4, 4, 32, 32, enemyImage[ENEMY_TYPE_SLIME]);		// スライムの描画
	//------------------------------------------------------------------------------------------
	// ゴブリン

	enemyMaster[ENEMY_TYPE_GOBLIN].size = { 32,32 };				// ゴブリンのサイズ
	enemyMaster[ENEMY_TYPE_GOBLIN].offsetSize = { 3,7 };			// ゴブリンのオフセットサイズ
	enemyMaster[ENEMY_TYPE_GOBLIN].lifeMax = 2;						// ゴブリンのライフ
	enemyMaster[ENEMY_TYPE_GOBLIN].moveSpeed = 2;					// ゴブリンのスピード
	enemyMaster[ENEMY_TYPE_GOBLIN].enemyType = ENEMY_TYPE_GOBLIN;	// 敵の種類をゴブリンにセット

	LoadDivGraph("image/character/ゴブリンfin完.png",
		16, 4, 4, 32, 32, enemyImage[ENEMY_TYPE_GOBLIN]);			// ゴブリンの描画
	//------------------------------------------------------------------------------------------
	// オーク

	enemyMaster[ENEMY_TYPE_OAK].size = { 41,41 };			// オークのサイズ
	enemyMaster[ENEMY_TYPE_OAK].offsetSize = { 3,7 };		// オークのオフセットサイズ
	enemyMaster[ENEMY_TYPE_OAK].lifeMax = 4;				// オークのライフ
	enemyMaster[ENEMY_TYPE_OAK].moveSpeed = 1;				// オークのスピード
	enemyMaster[ENEMY_TYPE_OAK].enemyType = ENEMY_TYPE_OAK;	// 敵の種類をオークにセット

	LoadDivGraph("image/character/オークfin完.png",
		16, 4, 4, 41, 41, enemyImage[ENEMY_TYPE_OAK]);		// オークの描画
	//------------------------------------------------------------------------------------------

}

// 敵のゲームごとの初期化
void EnemyGameInit(void)
{
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		int rnd = GetRand(ENEMY_TYPE_MAX - 1);
		enemy[en] = enemyMaster[rnd];

		//enemy[en].pos.x += enemy[en].size.x * en;

		// スクリーンのランダムな位置で出現
		enemy[en].pos.x = GetRand(SCREEN_SIZE_X - 1);
		enemy[en].pos.y = GetRand(SCREEN_SIZE_Y - 1);
	}

}

// 敵の制御処理
void EnemyControl(XY playerPos, int cnt)
{
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		enemy[en].animCnt++;

		if (enemy[en].lifeMax > 0)
		{
			switch (enemy[en].enemyType)
			{

				// X移動
			case 	ENEMY_TYPE_SLIME:
			case	ENEMY_TYPE_OAK:
				if (!enemy[en].moveFlag)
				{
					if (MoveEnemyX(&enemy[en], playerPos) == 0)
					{
						MoveEnemyY(&enemy[en], playerPos);
					}
				}
				break;

				// Y移動
			case	ENEMY_TYPE_GOBLIN:
				if (!enemy[en].moveFlag)
				{
					if (MoveEnemyY(&enemy[en], playerPos) == 0)
					{
						MoveEnemyX(&enemy[en], playerPos);
					}
				}
			default:
				break;
			}
			// 敵の移動モードの切り替え
			if (enemy[en].moveFlag && GetRand(100) == 0)
			{
				enemy[en].moveFlag = false;
			}
			else if (!enemy[en].moveFlag && GetRand(360) == 0)
			{
				enemy[en].moveFlag = true;
			}
		}
	}
}

// 敵の描画
void EnemyGameDraw(XY mapPos)
{
		for (int en = 0; en < ENEMY_MAX; en++)
		{
				DrawGraph(
					enemy[en].pos.x - mapPos.x,
					enemy[en].pos.y - mapPos.y,
					enemyImage[enemy[en].enemyType][enemy[en].dir * 4 + enemy[en].animCnt / 10 % 4],
					true);
		}

	//DrawCircle(320, 240, 150, GetColor(255,255,255), false);
}


//　敵を移動させる関数群 X移動
int MoveEnemyX(CHARACTER *enemy, XY playerPos)
{
	int speed = (*enemy).moveSpeed;
	int diff = playerPos.x - (*enemy).pos.x;

	if (diff >= 0)
	{
		// 右
		speed = (diff < speed) ? diff : speed;
		(*enemy).pos.x += speed;
		(*enemy).dir = DIR_RIGHT;
	}
	else
	{
		// 左
		speed = (-diff < speed) ? -diff : speed;
		(*enemy).pos.x -= speed;
		(*enemy).dir = DIR_LEFT;
	}

	return speed;
}

// 敵を移動させる関数群 Y移動
int MoveEnemyY(CHARACTER *enemy, XY playerPos)
{
	int speed = (*enemy).moveSpeed;
	int diff = playerPos.y - (*enemy).pos.y;

	if (diff >= 0)
	{
		// 下
		speed = (diff < speed) ? diff : speed;
		(*enemy).pos.y += speed;
		(*enemy).dir = DIR_DOWN;
	}
	else
	{
		// 上
		speed = (-diff < speed) ? -diff : speed;
		(*enemy).pos.y -= speed;
		(*enemy).dir = DIR_UP;
	}
	return speed;
}



XY GetEnemyPos(int en)
{

	return { (int)enemy[en].pos.x,(int)enemy[en].pos.y };
}

XY GetEnemySize(int en)
{

	return enemy[en].size;
}

void EnemyRad(void)
{
	//17+26= 43/2= 21.5= 21
}