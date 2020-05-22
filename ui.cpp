//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "ui.h"
#include "keycheck.h"
#include "item.h"

// 変数宣言
int menuImage[MENU_TYPE_MAX];		// メニュー画像用
int itemboxImage[2];				// アイテムボックスの画像用
XY itemboxPosList[ITEMBOX_MAX];		// アイテムボックスの座標記憶用

// UIのシステム初期化
void UiSystemInit(void)
{
	// 画像の読み込み
	menuImage[MENU_TYPE_CRAFT] = LoadGraph("image/ui/ui_craft.png",true);
	menuImage[MENU_TYPE_STATUS] = LoadGraph("image/ui/ui_status.png", true);
	menuImage[MENU_TYPE_INVENTORY] = LoadGraph("image/ui/ui_inventory.png", true);

	itemboxImage[0] = LoadGraph("image/ui/item_box.png", true);
	itemboxImage[1] = LoadGraph("image/ui/item_box_lock.png", true);
}

// UIのゲーム初期化
void UiGameInit(void)
{

}

// UIの制御
void UiControl(void)
{
	XY mousePos = GetMousePosMain();

	for (int invCnt = 0; invCnt < ITEMBOX_MAX; invCnt++)
	{
		if ((mousePos.x > itemboxPosList[invCnt].x && mousePos.x < itemboxPosList[invCnt].x + ITEMBOX_SIZE_X) &&
			(mousePos.y > itemboxPosList[invCnt].y && mousePos.y < itemboxPosList[invCnt].y + ITEMBOX_SIZE_Y))
		{
			if (mouseTrgUp)
			{
				if (UseItemMain(invCnt))
				{
					DeleteInventoryList(invCnt);
				}
			}
			//if (mouseTrgUp) DeleteItem(invCnt);
		}
	}
}

// UIの描画
void UiGameDraw(void)
{
	XY mousePos = GetMousePosMain();
	// メニュー画面の描画
	DrawGraph(20, 150, menuImage[MENU_TYPE_CRAFT], true);
	DrawGraph(250, 150, menuImage[MENU_TYPE_STATUS], true);
	DrawGraph(600, 150, menuImage[MENU_TYPE_INVENTORY], true);

	// インベントリの開放数を取得してアイテムを描画
	int lockIndex = InventoryItemDrawMain();

	// アイテムボックスをインベントリに描画
	for (int invCnt = 0; invCnt < ITEMBOX_MAX; invCnt++)
	{
		int imageIndex = (invCnt < lockIndex) ? 0 : 1;
		itemboxPosList[invCnt] = { 611 + (4 + 38) * (invCnt % 4) - 2 ,189 + (invCnt / 4 * 40) - 2 };
		DrawGraph(itemboxPosList[invCnt].x,itemboxPosList[invCnt].y, itemboxImage[imageIndex], true);
	}

	// アイテム説明の描画
	for (int invCnt = 0; invCnt < ITEMBOX_MAX; invCnt++)
	{
		if ((mousePos.x > itemboxPosList[invCnt].x && mousePos.x < itemboxPosList[invCnt].x + ITEMBOX_SIZE_X) &&
			(mousePos.y > itemboxPosList[invCnt].y && mousePos.y < itemboxPosList[invCnt].y + ITEMBOX_SIZE_Y))
		{
			DrawFormatString(mousePos.x + 32, mousePos.y + 32, GetColor(255, 255, 255), "アイテム説明");
		}
	}
}