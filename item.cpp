//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------
#include "DxLib.h"
#include "main.h"
#include "item.h"
#include "keycheck.h"

// 変数宣言
ITEM itemMaster[ITEM_TYPE_MAX];	// アイテムの情報保持用
ITEM item[ITEM_MAX];	// アイテム用
INVENTORY* inventoryList; // インベントリ内のアイテム制御用
int inventoryListCnt;	// インベントリ配列の最後のインデックス保持用
int itemImage[128];		// アイテムの画像用

// アイテムのシステム初期化
void ItemSystemInit(void)
{
	// ------------------------------------
	//			  画像の読み込み 
	// ------------------------------------

	// 石関係アイテムの画像読み込み
	LoadDivGraph("image/item/item_stone.png", 128, 16, 8, 32, 32, itemImage);

	// ------------------------------------
	//		   アイテム情報初期化
	// ------------------------------------

	// STONEの情報初期化
	itemMaster[ITEM_TYPE_STONE].imageIndex = 104;
	itemMaster[ITEM_TYPE_STONE].type = ITEM_TYPE_STONE;
	itemMaster[ITEM_TYPE_STONE].state = ITEM_STATE_DROP;
}

// アイテムのゲーム初期化
void ItemGameInit(int invMax)
{
	// プレイヤーインベントリを作成
	inventoryList = (INVENTORY*)malloc(sizeof(INVENTORY) * invMax);
	for (int list = 0; list < 10; list++)
	{
		inventoryList[list].itemType = ITEM_TYPE_MAX;
		inventoryList[list].num = 0;
	}


	item[0] = itemMaster[ITEM_TYPE_STONE];
	item[0].pos = { 200,200 };

	item[1] = itemMaster[ITEM_TYPE_MAX];
}

// アイテムのゲーム描画
void ItemGameDraw(XY mapPos)
{
	for (int itemCnt = 0; itemCnt < ITEM_MAX; itemCnt++)
	{
		DrawGraph(
			item[itemCnt].pos.x - mapPos.x,
			item[itemCnt].pos.y - mapPos.y,
			itemImage[item[itemCnt].imageIndex],
			true
		);
	}

	for (int cnt = 0; cnt < 10; cnt++)
	{
		DrawFormatString(10, 18 * cnt + 10, GetColor(255, 255, 255), "個数：%d", inventoryList[cnt].num);
	}

}

// アイテムのコントロール
void ItemControl(void)
{
	if (keyTrgUp[KEY_E])
	{
		AddInventoryList(item[0], 0);
	}

	if (keyTrgUp[KEY_R])
	{
		AddInventoryList(item[1], 0);
	}
}

// プレイヤーのインベントリのリストを更新
void UpdateInventoryList(int max)
{
	// リストのコピーを作成
	INVENTORY* inventoryListCopy = (INVENTORY*)malloc(sizeof inventoryList);
	
	// コピーにインベントリ内のアイテム移動
	inventoryListCopy = inventoryList;

	// リストの作り直し
	free(inventoryList);
	inventoryList = (INVENTORY*)malloc(sizeof(INVENTORY) * max);

	// コピーに保存した情報を新しいリストに挿入
	for (int listCnt = 0; listCnt < inventoryListCnt; listCnt++)
	{
		inventoryList[listCnt].itemType = inventoryListCopy[listCnt].itemType;
		inventoryList[listCnt].num = inventoryListCopy[listCnt].num;
	}

	// コピーのメモリを開放
	free(inventoryListCopy);
}

bool AddInventoryList(ITEM insertItem,int index)
{
	// リストの一番最後にアイテムがあればfalseを返してアイテム取得不可にする
	if (inventoryList[inventoryListCnt].num > 0) return false; 
	
	// アイテム挿入位置保存用
	int insertIndex = inventoryListCnt;
	
	// リストにすでに持っているアイテムがあれば数を増やす
	for (int listCnt = 0; listCnt < inventoryListCnt; listCnt++)
	{
		if (insertItem.type == inventoryList[listCnt].itemType)
		{
			inventoryList[listCnt].num++;
			item[index].state = ITEM_STATE_INVENTORY;
			return true;
		}
	}

	// 持ってないアイテムの場合はID順に並べて追加
	for (int listCnt = 0; listCnt < insertIndex; listCnt++)
	{
		if ((int)insertItem.type > (int)inventoryList[listCnt].itemType && (int)insertItem.type < (int)inventoryList[listCnt + 1].itemType)
		{
			insertIndex = listCnt + 1;
			break;
		}
	}

	// 挿入位置から後ろに全部1つずらす
	for (int listCnt = inventoryListCnt; listCnt > insertIndex; listCnt--)
	{
		inventoryList[listCnt + 1] = inventoryList[listCnt];
	}
	
	// リストに挿入
	inventoryList[insertIndex].itemType = insertItem.type;
	inventoryList[insertIndex].num += 1;
	item[index].state = ITEM_STATE_INVENTORY;
	
	// インベントリにアイテムが入ってるスロット数を更新
	inventoryListCnt += 1;

	return true;
}

// 指定した配列のインデックスを削除し並び替え
void DeleteInventoryList(int index)
{
	// 引数で渡されたインデックスを消す。
	for (int listCnt = index; listCnt > inventoryListCnt; listCnt++)
	{
		inventoryList[listCnt] = inventoryList[listCnt + 1];
	}

	// 一番後ろのリストを削除
	inventoryList[inventoryListCnt].itemType = ITEM_TYPE_MAX;
	inventoryList[inventoryListCnt].num = 0;

	// インベントリにアイテムが入ってるスロット数を更新
	inventoryListCnt -= 1;
}

INVENTORY* GetInventoryPointer(void)
{
	return inventoryList;
}


