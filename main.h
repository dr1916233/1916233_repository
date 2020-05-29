//--------------------------	--------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

//#pragma once//----------------------------------

// 定数宣言
#define SCREEN_SIZE_X	800		// ゲームスクリーンのXサイズ
#define SCREEN_SIZE_Y	600		// ゲームスクリーンのYサイズ

#define GAME_SCREEN_X	800		// ゲームエリアのサイズX
#define GAME_SCREEN_Y	540		// ゲームエリアのサイズY

#define SCREEN_OFFSET_Y	60		// ゲームエリア上部の余白Yサイズ

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
	XY_F pos;			// 座標用
	DIR dir;			// オブジェクトの向き
	CHARATYPE type;		// キャラクターのタイプ
	int enemyType;		// 敵の種類
	XY size;			// サイズ
	XY offsetSize;		// 余白なしのサイズ
	XY offsetSizeSide;	// 横から見たときの余白サイズ
	int rad;			// 円で判定を取るオブジェクトの半径
	int lifeMax;		// HPの基礎値
	int life;			// 実際のHP
	int animCnt;		// アニメーションカウント用
	float moveSpeed;	// 移動速度
	bool visible;		// 可視化状態
	int level;			// レベル
	int attack;			// 攻撃力用
	bool moveFlag;		// 動いてるかどうかの判定用
	int inventoryCnt;	// インベントリの数
	int statusPoint;	// ステータスを上昇させる回数用
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
bool CircleHitCheckMain(CHARATYPE type, XY pos1, XY size1, int rad);	// 円と円の当たり判定(接触：0、非接触：-1、ダメージがある場合：1以上の整数)
void ItemHitCheckMain(XY pPos, XY pSize);	// プレイヤーとアイテムの当たり判定
int InventoryItemDrawMain(void);	// アイテムの描画を促し、描画した数を返す
XY GetMousePosMain(void);	// マウスの座標取得用関数
bool UseItemMain(int index);
CHARACTER GetPlayerMain(void);	// プレイヤーの情報取得
CHARACTER* GetPlayerPointerMain(void);	// プレイヤーのポインタを取得
void UpdateInvenyoryListMain(int max);
void DeleteInventoryListMain(int index);
void GetEventMain(XY pos);
void DoDamageMain(CHARATYPE charaType, int damage);	// 引数で渡されたキャラクターのHPをダメージ分減算する