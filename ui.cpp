//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "ui.h"
#include "keycheck.h"

// �ϐ��錾
int menuImage[MENU_TYPE_MAX];		// ���j���[�摜�p
int itemboxImage[2];				// �A�C�e���{�b�N�X�̉摜�p
int playerHpbarImage;				// �v���C���[��HP�o�[�̃C���[�W

XY itemboxPosList[ITEMBOX_MAX];		// �A�C�e���{�b�N�X�̍��W�L���p
int statusUp;						// �X�e�[�^�X���グ��邩�̔���p

// UI�̃V�X�e��������
void UiSystemInit(void)
{
	// �摜�̓ǂݍ���
	menuImage[MENU_TYPE_CRAFT] = LoadGraph("image/ui/ui_craft.png",true);
	menuImage[MENU_TYPE_STATUS] = LoadGraph("image/ui/ui_status.png", true);
	menuImage[MENU_TYPE_INVENTORY] = LoadGraph("image/ui/ui_inventory.png", true);

	itemboxImage[0] = LoadGraph("image/ui/item_box.png", true);
	itemboxImage[1] = LoadGraph("image/ui/item_box_lock.png", true);
	playerHpbarImage = LoadGraph("image/ui/player_hpbar.png", true);
}

// UI�̃Q�[��������
void UiGameInit(void)
{

}

// UI�̐���
void UiControl(void)
{
	// �}�E�X�̍��W�L���p
	XY mousePos = GetMousePosMain();

	// �A�C�e���{�b�N�X�̏�ɃJ�[�\�������邩�𔻒肵�Ă��A������Ă���A�C�e�����g�p����
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

	// �X�e�[�^�X�A�b�vUI�̏�ɃJ�[�\�������邩�𔻒肵�āA��������Ă���X�e�[�^�X���グ��
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

// UI�̕`��
void UiGameDraw(bool menuFlag)
{
	// �v���C���[�̏����擾
	CHARACTER playerInfo = GetPlayerMain();

	// �}�E�X�̏����擾
	XY mousePos = GetMousePosMain();

	if (menuFlag)
	{
		// ----------------------------------------
		//			  ���j���[��ʂ̕`�� 
		// ----------------------------------------


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
			DrawGraph(itemboxPosList[invCnt].x, itemboxPosList[invCnt].y, itemboxImage[imageIndex], true);
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

		for (int barCnt = 0; barCnt < 4; barCnt++)
		{
			if (barCnt == 0) DrawFormatString(267, 370 + barCnt * 45, GetColor(255, 0, 0), "HP�F%d", playerInfo.life);
			if (barCnt == 1)DrawFormatString(267, 370 + barCnt * 45, GetColor(255, 0, 0), "�ړ����x�F%d��", (int)(playerInfo.moveSpeed / 3.0f * 100.0f));
			if (barCnt == 2)DrawFormatString(267, 370 + barCnt * 45, GetColor(255, 0, 0), "�U���́F%d��", (int)((float)playerInfo.attack / 10.0f * 100.0f));
			if (barCnt == 3)DrawFormatString(267, 370 + barCnt * 45, GetColor(255, 0, 0), "�C���x���g�����F%d��", playerInfo.inventoryCnt);
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

		DrawFormatString(30 + 250, 150 + 190, GetColor(255, 0, 0), "�c��X�e�[�^�X�㏸�񐔁F%d��", statusUp);
	}
	else // ���j���[��ʈȊO
	{
		// �v���C���[��HP�o�[
		DrawBox(15, 7, 186, 53, GetColor(70, 70, 70), true);
		DrawBox(15, 7, 15 +  (171.0f / (float)playerInfo.lifeMax) * (float)playerInfo.life , 53, GetColor(0, 255, 0), true);
		DrawGraph(0, 0, playerHpbarImage, true);
		DrawFormatString(60, 22, GetColor(0, 0, 150), "HP�F%d / %d", playerInfo.life, playerInfo.lifeMax);
	}
}