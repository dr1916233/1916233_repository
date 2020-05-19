//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------
#include "DxLib.h"
#include "main.h"
#include "item.h"
#include "keycheck.h"

// �ϐ��錾
ITEM itemMaster[ITEM_TYPE_MAX];	// �A�C�e���̏��ێ��p
ITEM item[ITEM_MAX];	// �A�C�e���p
INVENTORY* inventoryList; // �C���x���g�����̃A�C�e������p
int inventoryListCnt;	// �C���x���g���z��̍Ō�̃C���f�b�N�X�ێ��p
int itemImage[128];		// �A�C�e���̉摜�p

// �A�C�e���̃V�X�e��������
void ItemSystemInit(void)
{
	// ------------------------------------
	//			  �摜�̓ǂݍ��� 
	// ------------------------------------

	// �Ί֌W�A�C�e���̉摜�ǂݍ���
	LoadDivGraph("image/item/item_stone.png", 128, 16, 8, 32, 32, itemImage);

	// ------------------------------------
	//		   �A�C�e����񏉊���
	// ------------------------------------

	// STONE�̏�񏉊���
	itemMaster[ITEM_TYPE_STONE].imageIndex = 104;
	itemMaster[ITEM_TYPE_STONE].type = ITEM_TYPE_STONE;
	itemMaster[ITEM_TYPE_STONE].state = ITEM_STATE_DROP;
}

// �A�C�e���̃Q�[��������
void ItemGameInit(int invMax)
{
	// �v���C���[�C���x���g�����쐬
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

// �A�C�e���̃Q�[���`��
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
		DrawFormatString(10, 18 * cnt + 10, GetColor(255, 255, 255), "���F%d", inventoryList[cnt].num);
	}

}

// �A�C�e���̃R���g���[��
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

// �v���C���[�̃C���x���g���̃��X�g���X�V
void UpdateInventoryList(int max)
{
	// ���X�g�̃R�s�[���쐬
	INVENTORY* inventoryListCopy = (INVENTORY*)malloc(sizeof inventoryList);
	
	// �R�s�[�ɃC���x���g�����̃A�C�e���ړ�
	inventoryListCopy = inventoryList;

	// ���X�g�̍�蒼��
	free(inventoryList);
	inventoryList = (INVENTORY*)malloc(sizeof(INVENTORY) * max);

	// �R�s�[�ɕۑ���������V�������X�g�ɑ}��
	for (int listCnt = 0; listCnt < inventoryListCnt; listCnt++)
	{
		inventoryList[listCnt].itemType = inventoryListCopy[listCnt].itemType;
		inventoryList[listCnt].num = inventoryListCopy[listCnt].num;
	}

	// �R�s�[�̃��������J��
	free(inventoryListCopy);
}

bool AddInventoryList(ITEM insertItem,int index)
{
	// ���X�g�̈�ԍŌ�ɃA�C�e���������false��Ԃ��ăA�C�e���擾�s�ɂ���
	if (inventoryList[inventoryListCnt].num > 0) return false; 
	
	// �A�C�e���}���ʒu�ۑ��p
	int insertIndex = inventoryListCnt;
	
	// ���X�g�ɂ��łɎ����Ă���A�C�e��������ΐ��𑝂₷
	for (int listCnt = 0; listCnt < inventoryListCnt; listCnt++)
	{
		if (insertItem.type == inventoryList[listCnt].itemType)
		{
			inventoryList[listCnt].num++;
			item[index].state = ITEM_STATE_INVENTORY;
			return true;
		}
	}

	// �����ĂȂ��A�C�e���̏ꍇ��ID���ɕ��ׂĒǉ�
	for (int listCnt = 0; listCnt < insertIndex; listCnt++)
	{
		if ((int)insertItem.type > (int)inventoryList[listCnt].itemType && (int)insertItem.type < (int)inventoryList[listCnt + 1].itemType)
		{
			insertIndex = listCnt + 1;
			break;
		}
	}

	// �}���ʒu������ɑS��1���炷
	for (int listCnt = inventoryListCnt; listCnt > insertIndex; listCnt--)
	{
		inventoryList[listCnt + 1] = inventoryList[listCnt];
	}
	
	// ���X�g�ɑ}��
	inventoryList[insertIndex].itemType = insertItem.type;
	inventoryList[insertIndex].num += 1;
	item[index].state = ITEM_STATE_INVENTORY;
	
	// �C���x���g���ɃA�C�e���������Ă�X���b�g�����X�V
	inventoryListCnt += 1;

	return true;
}

// �w�肵���z��̃C���f�b�N�X���폜�����ёւ�
void DeleteInventoryList(int index)
{
	// �����œn���ꂽ�C���f�b�N�X�������B
	for (int listCnt = index; listCnt > inventoryListCnt; listCnt++)
	{
		inventoryList[listCnt] = inventoryList[listCnt + 1];
	}

	// ��Ԍ��̃��X�g���폜
	inventoryList[inventoryListCnt].itemType = ITEM_TYPE_MAX;
	inventoryList[inventoryListCnt].num = 0;

	// �C���x���g���ɃA�C�e���������Ă�X���b�g�����X�V
	inventoryListCnt -= 1;
}

INVENTORY* GetInventoryPointer(void)
{
	return inventoryList;
}


