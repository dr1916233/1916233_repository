//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "ui.h"
#include "keycheck.h"
#include "item.h"

// �ϐ��錾
int menuImage[MENU_TYPE_MAX];		// ���j���[�摜�p
int itemboxImage[2];				// �A�C�e���{�b�N�X�̉摜�p
XY itemboxPosList[ITEMBOX_MAX];		// �A�C�e���{�b�N�X�̍��W�L���p

// UI�̃V�X�e��������
void UiSystemInit(void)
{
	// �摜�̓ǂݍ���
	menuImage[MENU_TYPE_CRAFT] = LoadGraph("image/ui/ui_craft.png",true);
	menuImage[MENU_TYPE_STATUS] = LoadGraph("image/ui/ui_status.png", true);
	menuImage[MENU_TYPE_INVENTORY] = LoadGraph("image/ui/ui_inventory.png", true);

	itemboxImage[0] = LoadGraph("image/ui/item_box.png", true);
	itemboxImage[1] = LoadGraph("image/ui/item_box_lock.png", true);
}

// UI�̃Q�[��������
void UiGameInit(void)
{

}

// UI�̐���
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

// UI�̕`��
void UiGameDraw(void)
{
	XY mousePos = GetMousePosMain();
	// ���j���[��ʂ̕`��
	DrawGraph(20, 150, menuImage[MENU_TYPE_CRAFT], true);
	DrawGraph(250, 150, menuImage[MENU_TYPE_STATUS], true);
	DrawGraph(600, 150, menuImage[MENU_TYPE_INVENTORY], true);

	// �C���x���g���̊J�������擾���ăA�C�e����`��
	int lockIndex = InventoryItemDrawMain();

	// �A�C�e���{�b�N�X���C���x���g���ɕ`��
	for (int invCnt = 0; invCnt < ITEMBOX_MAX; invCnt++)
	{
		int imageIndex = (invCnt < lockIndex) ? 0 : 1;
		itemboxPosList[invCnt] = { 611 + (4 + 38) * (invCnt % 4) - 2 ,189 + (invCnt / 4 * 40) - 2 };
		DrawGraph(itemboxPosList[invCnt].x,itemboxPosList[invCnt].y, itemboxImage[imageIndex], true);
	}

	// �A�C�e�������̕`��
	for (int invCnt = 0; invCnt < ITEMBOX_MAX; invCnt++)
	{
		if ((mousePos.x > itemboxPosList[invCnt].x && mousePos.x < itemboxPosList[invCnt].x + ITEMBOX_SIZE_X) &&
			(mousePos.y > itemboxPosList[invCnt].y && mousePos.y < itemboxPosList[invCnt].y + ITEMBOX_SIZE_Y))
		{
			DrawFormatString(mousePos.x + 32, mousePos.y + 32, GetColor(255, 255, 255), "�A�C�e������");
		}
	}
}