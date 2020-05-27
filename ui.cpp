//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "ui.h"
#include "keycheck.h"

// 変数宣言
int menuImage[MENU_TYPE_MAX];		// メニュー画像用
int itemboxImage[2];				// アイテムボックスの画像用
int playerHpbarImage;				// プレイヤーのHPバーのイメージ

XY itemboxPosList[ITEMBOX_MAX];		// アイテムボックスの座標記憶用
int statusUp;						// ステータスを上げれるかの判定用

// UIのシステム初期化
void UiSystemInit(void)
{
	// 画像の読み込み
	menuImage[MENU_TYPE_CRAFT] = LoadGraph("image/ui/ui_craft.png",true);
	menuImage[MENU_TYPE_STATUS] = LoadGraph("image/ui/ui_status.png", true);
	menuImage[MENU_TYPE_INVENTORY] = LoadGraph("image/ui/ui_inventory.png", true);

	itemboxImage[0] = LoadGraph("image/ui/item_box.png", true);
	itemboxImage[1] = LoadGraph("image/ui/item_box_lock.png", true);
	playerHpbarImage = LoadGraph("image/ui/player_hpbar.png", true);
}

// UIのゲーム初期化
void UiGameInit(void)
{

}

// UIの制御
void UiControl(void)
{
	// マウスの座標記憶用
	XY mousePos = GetMousePosMain();

	// アイテムボックスの上にカーソルがあるかを判定してかつ、押されてたらアイテムを使用する
	for (int invCnt = 0; invCnt < ITEMBOX_MAX; invCnt++)
	{
		if ((mousePos.x > itemboxPosList[invCnt].x && mousePos.x < itemboxPosList[invCnt].x + ITEMBOX_SIZE_X) &&
			(mousePos.y > itemboxPosList[invCnt].y && mousePos.y < itemboxPosList[invCnt].y + ITEMBOX_SIZE_Y))
		{
			if (mouseTrgUp)
			{
				if (UseItemMain(invCnt))
				{
					DeleteInventoryListMain(invCnt);
				}
			}
		}
	}

	// ステータスアップUIの上にカーソルがあるかを判定して、かつ押されてたらステータスを上げる
	CHARACTER* playerStatus = GetPlayerPointerMain();

	if ((*playerStatus).statusPoint > 0)
	{
		if (mousePos.x > 510 && mousePos.x < 534 && mousePos.y > 366 && mousePos.y < 390 && mouseTrgUp)
		{
			//(*playerStatus).life += 20;
			(*playerStatus).lifeMax += 20;
			(*playerStatus).statusPoint--;
		}
		if (mousePos.x > 510 && mousePos.x < 534 && mousePos.y > 411 && mousePos.y < 435 && mouseTrgUp)
		{
			(*playerStatus).moveSpeed += 0.5f;
			(*playerStatus).statusPoint--;
		}
		if (mousePos.x > 510 && mousePos.x < 534 && mousePos.y > 456 && mousePos.y < 480 && mouseTrgUp)
		{
			(*playerStatus).attack += 2;
			(*playerStatus).statusPoint--;
		}
		if (mousePos.x > 510 && mousePos.x < 534 && mousePos.y > 501 && mousePos.y < 525 && mouseTrgUp)
		{
			(*playerStatus).inventoryCnt += 2;
			UpdateInvenyoryListMain((*playerStatus).inventoryCnt);
			(*playerStatus).statusPoint--;
		}
	}

	statusUp = (*playerStatus).statusPoint;
}

// UIの描画
void UiGameDraw(bool menuFlag)
{
	// プレイヤーの情報を取得
	CHARACTER playerInfo = GetPlayerMain();

	// マウスの情報を取得
	XY mousePos = GetMousePosMain();

	if (menuFlag)
	{
		// ----------------------------------------
		//			  メニュー画面の描画 
		// ----------------------------------------


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
			DrawGraph(itemboxPosList[invCnt].x, itemboxPosList[invCnt].y, itemboxImage[imageIndex], true);
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

		for (int barCnt = 0; barCnt < 4; barCnt++)
		{
			if (barCnt == 0) DrawFormatString(267, 370 + barCnt * 45, GetColor(255, 0, 0), "HP：%d", playerInfo.life);
			if (barCnt == 1)DrawFormatString(267, 370 + barCnt * 45, GetColor(255, 0, 0), "移動速度：%d％", (int)(playerInfo.moveSpeed / 3.0f * 100.0f));
			if (barCnt == 2)DrawFormatString(267, 370 + barCnt * 45, GetColor(255, 0, 0), "攻撃力：%d％", (int)((float)playerInfo.attack / 10.0f * 100.0f));
			if (barCnt == 3)DrawFormatString(267, 370 + barCnt * 45, GetColor(255, 0, 0), "インベントリ数：%d個", playerInfo.inventoryCnt);
		}

		if (statusUp <= 0)
		{
			for (int barCnt = 0; barCnt < 4; barCnt++)
			{
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
				DrawBox(510, 366 + barCnt * 45, 535, 391 + barCnt * 45, GetColor(0, 0, 0), true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
		}

		DrawFormatString(30 + 250, 150 + 190, GetColor(255, 0, 0), "残りステータス上昇回数：%d回", statusUp);
	}
	else // メニュー画面以外
	{
		// プレイヤーのHPバー
		DrawBox(15, 7, 186, 53, GetColor(70, 70, 70), true);
		DrawBox(15, 7, 15 +  (171.0f / (float)playerInfo.lifeMax) * (float)playerInfo.life , 53, GetColor(0, 255, 0), true);
		DrawGraph(0, 0, playerHpbarImage, true);
		DrawFormatString(60, 22, GetColor(0, 0, 150), "HP：%d / %d", playerInfo.life, playerInfo.lifeMax);
	}
}