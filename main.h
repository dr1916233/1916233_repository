//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

//#pragma once//----------------------------------

// 定数宣言
#define SCREEN_SIZE_X	800		// ゲームスクリーンのXサイズ
#define SCREEN_SIZE_Y	600		// ゲームスクリーンのYサイズ

// シーン遷移用
enum SCENE_ID {
	SCENE_INIT,		// 初期化用
	SCENE_TITLE,	// タイトル
	SCENE_GAME,		// ゲームメイン
	SCENE_GAMEOVER,	// ゲームオーバー
	SCENE_MAX
};

// 方向用
enum DIR
{
	DIR_DOWN,		// 下
	DIR_RIGHT,		// 右
	DIR_LEFT,		// 左
	DIR_UP,			// 上
	DIR_MAX
};

// --------------------
// 構造体
// --------------------

// 2次元ベクトル用
struct Pos
{
	int x;
	int y;
};

// 2次元float用
struct Pos_F
{
	float x;
	float y;
};

// プロトタイプ宣言
bool SystemInit(void);	// システム初期化
void InitScene(void);	// 初期化シーン
void TitleScene(void);	// タイトルシーン
void TitleDraw(void);	// タイトル描画
void GameScene(void);	// ゲームシーン
void GameDraw(void);	// ゲーム描画
void GameOverScene(void);	// ゲームオーバーシーン
void GameOverDraw(void);	// ゲームオーバー描画