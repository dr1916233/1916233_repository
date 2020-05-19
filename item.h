//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

//#pragma once

// 定数
#define ITEM_MAX 5	// アイテムの最大数

// アイテムの種類
enum ITEM_TYPE
{
	ITEM_TYPE_STONE,	// ID：0
	ITEM_TYPE_MAX
};

// アイテムの状態
enum ITEM_STATE
{
	ITEM_STATE_INVENTORY,
	ITEM_STATE_DROP,
	ITEM_STATE_MAX
};


// 構造体

// アイテム用構造体
struct ITEM
{
	ITEM_STATE state;
	ITEM_TYPE type;
	int imageIndex;
	XY pos;
};

// インベントリ用構造体
struct INVENTORY
{
	ITEM_TYPE itemType;
	int num;
};

// プロトタイプ宣言
void ItemSystemInit(void);
void ItemGameInit(int invMax);
void ItemGameDraw(XY mapPos);
void ItemControl(void);
void UpdateInventoryList(int max);
bool AddInventoryList(ITEM insertItem, int index);
void DeleteInventoryList(int index);

INVENTORY* GetInventoryPointer(void);




