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

enum CHARATYPE
{
	CHARA_PLAYER,
	CHARA_ENEMY,
	CHARA_MAGIC,
	CHARATYPE_MAX
};

// --------------------
// 構造体
// --------------------

// 2次元ベクトル用
struct XY
{
	int x;
	int y;
};

// 2次元float用
struct XY_F
{
	float x;
	float y;
};

// キャラクター用構造体
struct CHARACTER
{
	XY_F pos;
	DIR dir;
	CHARATYPE type;
	XY size;
	XY offsetSize;
	int lifeMax;
	int life;
	int animCnt;
	float moveSpeed;
	bool visible;
	int level;
	int attack;
};

// プロトタイプ宣言
bool SystemInit(void);	// システム初期化
void InitScene(void);	// 初期化シーン
void TitleScene(void);	// タイトルシーン
void TitleDraw(void);	// タイトル描画
void GameScene(void);	// ゲームシーン
void GameDraw(XY mapPos);	// ゲーム描画
void GameOverScene(void);	// ゲームオーバーシーン
void GameOverDraw(void);	// ゲームオーバー描画
bool IsPassMain(XY playerPos); // プレイヤーから座標をもらって通過可能化を返す
int RectHitCheckMain(CHARATYPE type, XY pos1, XY size1);	// 矩形の当たり判定(接触：0、非接触：-1、ダメージがある場合：1以上の整数)
int CircleHitCheckMain(CHARACTER type, XY pos1, XY size1);	// 円と円の当たり判定(接触：0、非接触：-1、ダメージがある場合：1以上の整数)