//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------
#define ENEMY_IMAGENUM_X 4	// エネミー画像のX方向の数
#define ENEMY_IMAGENUM_Y 4	// エネミー画像のY方向の数
#define ENEMY_IMAGESIZE_X	32	// エネミー画像のX方向のサイズ
#define ENEMY_IMAGESIZE_Y	32	// エネミー画像のY方向のサイズ

// 定数
enum ENEMY_TYPE
{
	// 敵の種類
	ENEMY_TYPE_SURAIMU,	
	ENEMY_TYPE_MAX
};

//#pragma once//----------------------------------

// プロトタイプ宣言
void EnemySystemInit(void);		// 敵のシステム初期化
void EnemyGameInit(void);		// 敵のゲーム初期化
void EnemyGameDraw(void);		// 敵のゲーム描画
void EnemyControl(void);		// 敵の制御処理