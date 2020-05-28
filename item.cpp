//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------
#include "DxLib.h"
#include "main.h"
#include "item.h"
#include "keycheck.h"

// �萔�錾
#define ITEM_CREATE_MAX ITEM_MAX + 1

// �ϐ��錾
ITEM itemMaster[ITEM_TYPE_MAX];	// �A�C�e���̏��ێ��p
ITEM item[ITEM_CREATE_MAX];	// �A�C�e���p
INVENTORY* inventoryList; // �C���x���g�����̃A�C�e������p
INVENTORY armorInventory;	// �A�[�}�[�p�̃C���x���g��
int inventoryListCnt;	// �C���x���g���z��̍Ō�̃C���f�b�N�X�ێ��p
int itemImage[128+20+2+1];		// �A�C�e���̉摜�p
int inventoryMax;		// �C���x���g���̍ő�l
ITEM_TYPE playerArmor;	// �v���C���[�����Ă�h���p
int selectArmorImage[3];	// �v���C���[���ǂ̑����𒅂Ă��邩�̕\���p

// �A�C�e���̃V�X�e��������
void ItemSystemInit(void)
{
	// ------------------------------------
	//			  �摜�̓ǂݍ��� 
	// ------------------------------------

	// �Ί֌W�A�C�e���̉摜�ǂݍ���
	LoadDivGraph("image/item/item_stone.png", 128, 16, 8, 32, 32, itemImage);
	// �|�[�V�����֌W�A�C�e���̉摜�ǂݍ���
	LoadDivGraph("image/item/item_portion.png", 20, 10, 2, 32, 32, &itemImage[128]);
	// �h��A�C�e���̉摜�ǂݍ���
	itemImage[149] = LoadGraph("image/item/item_whiteDougi.png",true);
	itemImage[150] = LoadGraph("image/item/item_braveDougi.png",true);
	selectArmorImage[0] = LoadGraph("image/character/naked_kancho_view.png", true);
	selectArmorImage[1] = LoadGraph("image/character/dougi_kancho_view.png", true);
	selectArmorImage[2] = LoadGraph("image/character/brave_kancho_view.png", true);

	// ------------------------------------
	//		   �A�C�e����񏉊���
	// ------------------------------------

	// �d���΂̏�񏉊���
	itemMaster[ITEM_TYPE_HARDSTONE].imageIndex = 89;
	itemMaster[ITEM_TYPE_HARDSTONE].type = ITEM_TYPE_HARDSTONE;
	itemMaster[ITEM_TYPE_HARDSTONE].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// �_�炩���΂̏�񏉊���
	itemMaster[ITEM_TYPE_SOFTSTONE].imageIndex = 90;
	itemMaster[ITEM_TYPE_SOFTSTONE].type = ITEM_TYPE_SOFTSTONE;
	itemMaster[ITEM_TYPE_SOFTSTONE].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// �_�C�A�����h�̏�񏉊���
	itemMaster[ITEM_TYPE_DIAMOND].imageIndex = 8;
	itemMaster[ITEM_TYPE_DIAMOND].type = ITEM_TYPE_DIAMOND;
	itemMaster[ITEM_TYPE_DIAMOND].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// �A���W�X�g�̏�񏉊���
	itemMaster[ITEM_TYPE_AMETHYST].imageIndex = 12;
	itemMaster[ITEM_TYPE_AMETHYST].type = ITEM_TYPE_AMETHYST;
	itemMaster[ITEM_TYPE_AMETHYST].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// �G�������h�̏�񏉊���
	itemMaster[ITEM_TYPE_EMERALD].imageIndex = 11;
	itemMaster[ITEM_TYPE_EMERALD].type = ITEM_TYPE_EMERALD;
	itemMaster[ITEM_TYPE_EMERALD].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// �T�t�@�C�A�̏�񏉊���
	itemMaster[ITEM_TYPE_SAPPHIRE].imageIndex = 9;
	itemMaster[ITEM_TYPE_SAPPHIRE].type = ITEM_TYPE_SAPPHIRE;
	itemMaster[ITEM_TYPE_SAPPHIRE].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// ���r�[�̏�񏉊���
	itemMaster[ITEM_TYPE_RUBY].imageIndex = 13;
	itemMaster[ITEM_TYPE_RUBY].type = ITEM_TYPE_RUBY;
	itemMaster[ITEM_TYPE_RUBY].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// �g�p�[�Y�̏�񏉊���
	itemMaster[ITEM_TYPE_TOPAZ].imageIndex = 14;
	itemMaster[ITEM_TYPE_TOPAZ].type = ITEM_TYPE_TOPAZ;
	itemMaster[ITEM_TYPE_TOPAZ].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// �S�̏�񏉊���
	itemMaster[ITEM_TYPE_IRON].imageIndex = 88;
	itemMaster[ITEM_TYPE_IRON].type = ITEM_TYPE_IRON;
	itemMaster[ITEM_TYPE_IRON].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// ���̏�񏉊���
	itemMaster[ITEM_TYPE_GOLD].imageIndex = 87;
	itemMaster[ITEM_TYPE_GOLD].type = ITEM_TYPE_GOLD;
	itemMaster[ITEM_TYPE_GOLD].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// �؂̊��̏�񏉊���
	itemMaster[ITEM_TYPE_WOODLOG].imageIndex = 115;
	itemMaster[ITEM_TYPE_WOODLOG].type = ITEM_TYPE_WOODLOG;
	itemMaster[ITEM_TYPE_WOODLOG].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// �؂̎}�̏�񏉊���
	itemMaster[ITEM_TYPE_WOODBRANCH].imageIndex = 113;
	itemMaster[ITEM_TYPE_WOODBRANCH].type = ITEM_TYPE_WOODBRANCH;
	itemMaster[ITEM_TYPE_WOODBRANCH].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// �񕜃|�[�V������񏉊���
	itemMaster[ITEM_TYPE_HEALPORTION].imageIndex = 128;
	itemMaster[ITEM_TYPE_HEALPORTION].type = ITEM_TYPE_HEALPORTION;
	itemMaster[ITEM_TYPE_HEALPORTION].attribute = ITEM_ATTRIBUTE_ACTIVE;

	// �X�s�[�h�A�b�v�|�[�V������񏉊���
	itemMaster[ITEM_TYPE_SPEEDUPPORTION].imageIndex = 131;
	itemMaster[ITEM_TYPE_SPEEDUPPORTION].type = ITEM_TYPE_SPEEDUPPORTION;
	itemMaster[ITEM_TYPE_SPEEDUPPORTION].attribute = ITEM_ATTRIBUTE_ACTIVE;

	// �ŏ����|�[�V������񏉊���
	itemMaster[ITEM_TYPE_ANTIDOTEPORTION].imageIndex = 132;
	itemMaster[ITEM_TYPE_ANTIDOTEPORTION].type = ITEM_TYPE_ANTIDOTEPORTION;
	itemMaster[ITEM_TYPE_ANTIDOTEPORTION].attribute = ITEM_ATTRIBUTE_ACTIVE;

	// ���������|�[�V������񏉊���
	itemMaster[ITEM_TYPE_ANTIFREEZEPORTION].imageIndex = 129;
	itemMaster[ITEM_TYPE_ANTIFREEZEPORTION].type = ITEM_TYPE_ANTIFREEZEPORTION;
	itemMaster[ITEM_TYPE_ANTIFREEZEPORTION].attribute = ITEM_ATTRIBUTE_ACTIVE;

	// �Ώ������|�[�V������񏉊���
	itemMaster[ITEM_TYPE_ANTIBURNPORTION].imageIndex = 130;
	itemMaster[ITEM_TYPE_ANTIBURNPORTION].type = ITEM_TYPE_ANTIBURNPORTION;
	itemMaster[ITEM_TYPE_ANTIBURNPORTION].attribute = ITEM_ATTRIBUTE_ACTIVE;

	// ���̓�����񏉊���
	itemMaster[ITEM_TYPE_WHITEDOUGI].imageIndex = 149;
	itemMaster[ITEM_TYPE_WHITEDOUGI].type = ITEM_TYPE_WHITEDOUGI;
	itemMaster[ITEM_TYPE_WHITEDOUGI].attribute = ITEM_ATTRIBUTE_ARMOR;

	// �E�҂̓�����񏉊���
	itemMaster[ITEM_TYPE_BRAVEDOUGI].imageIndex = 150;
	itemMaster[ITEM_TYPE_BRAVEDOUGI].type = ITEM_TYPE_BRAVEDOUGI;
	itemMaster[ITEM_TYPE_BRAVEDOUGI].attribute = ITEM_ATTRIBUTE_ARMOR;

	// �A�C�e���������p
	itemMaster[ITEM_TYPE_NON].attribute = ITEM_ATTRIBUTE_MAX;
}

// �A�C�e���̃Q�[��������
void ItemGameInit(int invMax)
{
	// �C���x���g���̍ő�l�p�ϐ�
	inventoryMax = invMax;

	// �v���C���[�̖h���񏉊���
	playerArmor = ITEM_TYPE_MAX;

	// �v���C���[�C���x���g�����쐬
	inventoryList = (INVENTORY*)malloc(sizeof(INVENTORY) * invMax);
	for (int list = 0; list < invMax; list++)
	{
		inventoryList[list].itemType = ITEM_TYPE_NON;
		inventoryList[list].num = 0;
		inventoryList[list].imageIndex = 0;
	}

	// �A�[�}�[�p�C���x���g��������
	armorInventory.imageIndex = 0;
	armorInventory.itemType = ITEM_TYPE_NON;
	armorInventory.num = 1;

	// �A�C�e���m�F�p�z�u

	for (int itemCnt = 0; itemCnt < ITEM_CREATE_MAX; itemCnt++)
	{
		item[itemCnt].type = ITEM_TYPE_NON;
		item[itemCnt].state = ITEM_STATE_NON;
		item[itemCnt].pos = {0,0};
	}

	for (int itemCnt = 0; itemCnt < 2; itemCnt++)
	{
		item[itemCnt] = itemMaster[ITEM_TYPE_WHITEDOUGI + itemCnt];
		item[itemCnt].state = ITEM_STATE_DROP;
		item[itemCnt].pos = { 40 * itemCnt + 50 ,200 };
	}
}

// �A�C�e���̃Q�[���`��
void ItemGameDraw(XY mapPos)
{
	for (int itemCnt = 0; itemCnt < ITEM_MAX; itemCnt++)
	{
		DrawGraph(
			item[itemCnt].pos.x - mapPos.x,
			item[itemCnt].pos.y - mapPos.y + SCREEN_OFFSET_Y,
			itemImage[item[itemCnt].imageIndex],
			true
		);
	}

	for (int cnt = 0; cnt < inventoryMax; cnt++)
	{
		DrawFormatString(10, 18 * cnt + 10, GetColor(255, 255, 255), "���F%d", inventoryList[cnt].num);
	}
}

// �A�C�e���̃R���g���[��
void ItemControl(void)
{
	if (keyTrgUp[KEY_E])
	{
		//AddInventoryList(item[0], 0);
	}

	if (keyTrgUp[KEY_R])
	{
		UpdateInventoryList(20);
	}
}

// �v���C���[�̃C���x���g���̃��X�g���X�V
void UpdateInventoryList(int max)
{
	// ���X�g�̃R�s�[���쐬
	INVENTORY* inventoryListCopy = (INVENTORY*)malloc(sizeof(INVENTORY) * inventoryMax);
	
	// �R�s�[�ɃC���x���g�����̃A�C�e���ړ�
	//inventoryListCopy = inventoryList;
	for (int listCnt = 0; listCnt < inventoryMax; listCnt++)
	{
		inventoryListCopy[listCnt] = inventoryList[listCnt];
	}
	
	// ���X�g�̍�蒼��
	free(inventoryList);
	inventoryList = (INVENTORY*)malloc(sizeof(INVENTORY) * max);

	// �V�������X�g�̏�����
	for (int listCnt = 0; listCnt < max; listCnt++)
	{
		inventoryList[listCnt].itemType = ITEM_TYPE_NON;
		inventoryList[listCnt].num = 0;
		inventoryList[listCnt].imageIndex = 0;
	}

	// �R�s�[�ɕۑ���������V�������X�g�ɑ}��
	for (int listCnt = 0; listCnt < inventoryListCnt; listCnt++)
	{
		inventoryList[listCnt].itemType = inventoryListCopy[listCnt].itemType;
		inventoryList[listCnt].num = inventoryListCopy[listCnt].num;
		inventoryList[listCnt].imageIndex = inventoryListCopy[listCnt].imageIndex;
	}

	// �C���x���g���̍ő�l���X�V
	inventoryMax = max;

	// �R�s�[�̃��������J��
	free(inventoryListCopy);
}

bool AddInventoryList(int index)
{
	ITEM insertItem = item[index];

	// ���X�g�̈�ԍŌ�ɃA�C�e���������false��Ԃ��ăA�C�e���擾�s�ɂ���
	if (inventoryList[inventoryMax -1].num > 0)
	{
		return false;
	}
	
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
	//for (int listCnt = 0; listCnt < insertIndex; listCnt++)
	//{
	//	if (insertItem.type > inventoryList[listCnt].itemType && insertItem.type < inventoryList[listCnt + 1].itemType)
	//	{
	//		insertIndex = listCnt + 1;
	//		break;
	//	}
	//}

	// �}���ʒu������ɑS��1���炷
	/*for (int listCnt = inventoryListCnt; listCnt > insertIndex; listCnt--)
	{
		inventoryList[listCnt + 1] = inventoryList[listCnt];
	}*/
	
	// ���X�g�ɑ}��
	inventoryList[insertIndex].itemType = insertItem.type;
	inventoryList[insertIndex].num += 1;
	inventoryList[insertIndex].imageIndex = insertItem.imageIndex;
	item[index].state = ITEM_STATE_INVENTORY;
	
	// �C���x���g���ɃA�C�e���������Ă�X���b�g�����X�V
	inventoryListCnt += 1;

	return true;
}

// �w�肵���z��̃C���f�b�N�X���폜�����ёւ�
void DeleteInventoryList(int index)
{
	// �����œn���ꂽ�C���f�b�N�X�������B
	//for (int listCnt = index; listCnt > inventoryListCnt; listCnt++)
	//{
	//	inventoryList[listCnt] = inventoryList[listCnt + 1];
	//}

	for (int listCnt = index; listCnt < inventoryListCnt; listCnt++)
	{
		inventoryList[listCnt] = inventoryList[listCnt + 1];
	}

	// ��Ԍ��̃��X�g���폜
	inventoryList[inventoryListCnt].itemType = ITEM_TYPE_MAX;
	inventoryList[inventoryListCnt].num = 0;

	// �C���x���g���ɃA�C�e���������Ă�X���b�g�����X�V
	inventoryListCnt -= 1;
}

// �A�C�e���̐���
int CreateItem(ITEM_TYPE type, XY pos)
{
	for (int itemCnt = 0; itemCnt < ITEM_MAX; itemCnt++)
	{
		if (item[itemCnt].type == ITEM_TYPE_NON)
		{
			item[itemCnt] = itemMaster[type];
			item[itemCnt].pos = pos;
			return itemCnt;
		}
	}

	return -1;
}

// �A�C�e���̔z�񂩂�Y���A�C�e�����폜
void DeleteItem(int index)
{
	//// �A�C�e�������炵�č폜
	//for (int sortHead = index; sortHead < ITEM_MAX; sortHead++)
	//{
	//	item[sortHead] = item[sortHead + 1];
	//}

	//// �Ō�̔z����폜
	//for (int head = index; head < ITEM_MAX; head++)
	//{
	//	if (item[head].type != ITEM_TYPE_NON && item[head + 1].type == ITEM_TYPE_NON)
	//	{
	//		item[head].imageIndex = 0;
	//		item[head].pos = { 0,0 };
	//		item[head].state = ITEM_STATE_NON;
	//		item[head].type = ITEM_TYPE_NON;
	//	}
	//}

	item[index].attribute = ITEM_ATTRIBUTE_MAX;
	item[index].imageIndex = -1;
	item[index].type = ITEM_TYPE_NON;
	item[index].state = ITEM_STATE_NON;
	item[index].pos = { -32,-32 };
}

// �A�C�e���C���x���g���̃A�h���X�擾�p
INVENTORY* GetInventoryPointer(void)
{
	return inventoryList;
}

// �A�C�e���̍��W�擾�p
XY GetItemPos(int index)
{
	return item[index].pos;
}

// �w�肳�ꂽ���W�ɃC���x���g�����A�C�e����`�悳����
int InventoryItemDraw(void)
{
	for (int invCnt = 0; invCnt < inventoryListCnt; invCnt++)
	{
		DrawGraph(611 + (4 + 38) * (invCnt % 4), 189 + (invCnt/4*40),itemImage[inventoryList[invCnt].imageIndex],true);
	}

	// �v���C���[�̑I�𒆖h��̃r���[�`��
	int imageIndex = 0;
	if (playerArmor == ITEM_TYPE_WHITEDOUGI)
	{
		imageIndex = 1;
		DrawGraph(185 + 250, 90 + 150, itemImage[149], true);
	}
	if (playerArmor == ITEM_TYPE_BRAVEDOUGI)
	{
		imageIndex = 2;
		DrawGraph(185 + 250, 90 + 150, itemImage[150], true);
	}

	DrawGraph(200 + 100,  150 + 55, selectArmorImage[imageIndex], true);

	return inventoryMax;
}

// �A�C�e���̎g�p
bool UseItem(CHARACTER* player,int index)
{
	if (itemMaster[inventoryList[index].itemType].attribute == ITEM_ATTRIBUTE_MATERIAL ||
		itemMaster[inventoryList[index].itemType].attribute == ITEM_ATTRIBUTE_PASSIVE ||
		itemMaster[inventoryList[index].itemType].attribute == ITEM_ATTRIBUTE_MAX) return false;
	//(*player)
	switch (inventoryList[index].itemType)
	{
	case ITEM_TYPE_HEALPORTION:
		/*if ((*player).life < (*player).lifeMax) (*player).life += PORTION_HEAL;
		if ((*player).life > (*player).lifeMax) (*player).life = (*player).lifeMax;*/

		(*player).lifeMax += PORTION_HEAL;
		break;
	case ITEM_TYPE_SPEEDUPPORTION:
		(*player).moveSpeed += 10;
		break;
	case ITEM_TYPE_ANTIDOTEPORTION:
		break;
	case ITEM_TYPE_ANTIFREEZEPORTION:
		break;
	case ITEM_TYPE_ANTIBURNPORTION:
		break;
	case ITEM_TYPE_WHITEDOUGI:
		playerArmor = inventoryList[index].itemType;
		if (armorInventory.itemType == ITEM_TYPE_NON) armorInventory = inventoryList[index];
		else
		{
			int index = CreateItem(armorInventory.itemType, { -32,-32 });
			AddInventoryList(index);
			DeleteItem(index);
			armorInventory = inventoryList[index];
		}
		break;
	case ITEM_TYPE_BRAVEDOUGI:
		playerArmor = inventoryList[index].itemType;
		if (armorInventory.itemType == ITEM_TYPE_NON) armorInventory = inventoryList[index];
		else
		{
			int index = CreateItem(armorInventory.itemType, { -32,-32 });
			AddInventoryList(index);
			DeleteItem(index);
			armorInventory = inventoryList[index];
		}
		break;
	default:
		break;
	}

	return true;
}
