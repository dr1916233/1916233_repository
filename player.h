//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

//#pragma once//----------------------------------

// 定数宣言
#define PLAYER_IMAGENUM_X 4			// プレイヤー画像のX方向の数
#define PLAYER_IMAGENUM_Y 4			// プレイヤー画像のY方向の数
#define PLAYER_IMAGESIZE_X 32		// プレイヤー画像のX方向のサイズ
#define PLAYER_IMAGESIZE_Y 32		// プレイヤー画像のY方向のサイズ
#define PLAYER_SIZE_X 20			// プレイヤーのX方向実サイズ
#define PLAYER_SIZE_Y 32			// プレイヤーのY方向実サイズ
#define PLAYER_OFFSET_X 6	// プレイヤーのX方向の余白サイズ
#define PLAYER_LIFE_DEF	100			// プレイヤーのデフォルトHP
#define PLAYER_SPEED_DEF 3			// プレイヤーのデフォルト移動速度
#define PLAYER_ATTACK_DEF	10		// プレイヤーのデフォルト攻撃力
#define PLAYER_INVENTORY_DEF 8		// プレイヤーのデフォルトインベントリ数

// --------------------
// 構造体
// --------------------

// プロトタイプ宣言

void PlayerSystemInit(void);	// プレイヤー情報の初期化
int PlayerGameInit(void);		// プレイヤーのゲーム関係の初期化
void PlayerGameDraw(XY mapPos);		// プレイヤーのゲーム描画
XY_F PlayerControl(XY chipNum, XY_F mapPos);	// プレイヤーの制御処理
CHARACTER* GetPlayerPointer(void);		// プレイヤーのポインタを取得
CHARACTER GetPlayer(void);		// プレイヤーの情報を取得
void PlayerAttack(void);			// プレイヤーの攻撃処理
XY_F GetPlayerPos(void);				// プレイヤーの座標取得

extern CHARACTER player;

