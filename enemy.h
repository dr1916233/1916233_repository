//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

//#pragma once//----------------------------------

#define ENEMY_MAX 4	// 敵の総数

// 定数
enum ENEMY_TYPE
{
	// 敵の種類
	ENEMY_TYPE_SLIME,	//スライム
	ENEMY_TYPE_GOBLIN,	//ゴブリン
	ENEMY_TYPE_OAK,		//オーク
	ENEMY_TYPE_BOSS,
	ENEMY_TYPE_MAX,
};

// プロトタイプ宣言
void EnemySystemInit(void);		// 敵のシステム初期化
void EnemyGameInit(void);		// 敵のゲーム初期化
void EnemyGameDraw(XY mapPos);	// 敵のゲーム描画
void EnemyControl(XY playerPos, int cnt);		// 敵の制御処理
void EnemyRad(void);

bool EnemyPlayerDiff(int index, int diff);
int PlayerEnemyHitCheck(int playerSize);	// プレイヤーと敵の当たり判定



// 敵を移動させる関数群
//int MoveEnemyY(CHARACTER* enemy, XY playerPos);
//int MoveEnemyX(CHARACTER* enemy, XY playerPos);

XY GetEnemyPos(int en);
XY GetEnemySize(int en);

void DoDamageEnemy(int index, int damage);	// 渡されたインデックスの敵のHPをダメージ分減算する
