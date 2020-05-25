//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

//#pragma once

// �萔
#define ITEM_MAX 19		// �A�C�e���̍ő吔
#define ITEM_SIZE_X	32	
#define ITEM_SIZE_Y 32

#define PORTION_HEAL	100

// �A�C�e���̎��
enum ITEM_TYPE
{
	ITEM_TYPE_HARDSTONE,			// ID�F 0 �d����
	ITEM_TYPE_SOFTSTONE,			// ID�F 1 �_�炩����
	ITEM_TYPE_DIAMOND,				// ID�F 2 �_�C�A�����h
	ITEM_TYPE_AMETHYST,				// ID�F 3 �A���W�X�g
	ITEM_TYPE_EMERALD,				// ID�F 4 �G�������h
	ITEM_TYPE_SAPPHIRE,				// ID�F 5 �T�t�@�C�A
	ITEM_TYPE_RUBY,					// ID�F 6 ���r�[
	ITEM_TYPE_TOPAZ,				// ID�F 7 �g�p�[�Y
	ITEM_TYPE_IRON,					// ID�F 8 �S
	ITEM_TYPE_GOLD,					// ID�F 9 ��
	ITEM_TYPE_WOODLOG,				// ID�F10 �؂̊�
	ITEM_TYPE_WOODBRANCH,			// ID�F11 �؂̎}
	ITEM_TYPE_HEALPORTION,			// ID�F12 �񕜃|�[�V����
	ITEM_TYPE_SPEEDUPPORTION,		// ID�F13 �X�s�[�h�A�b�v�|�[�V����
	ITEM_TYPE_ANTIDOTEPORTION,		// ID�F14 �ŏ����|�[�V����
	ITEM_TYPE_ANTIFREEZEPORTION,	// ID�F15 ���������|�[�V����
	ITEM_TYPE_ANTIBURNPORTION,		// ID�F16 �Ώ������|�[�V����
	ITEM_TYPE_WHITEDOUGI,			// ID�F17 ���̓���
	ITEM_TYPE_BRAVEDOUGI,			// ID�F18 �E�҂̓���
	ITEM_TYPE_NON,			
	ITEM_TYPE_MAX
};

// �A�C�e���̏��
enum ITEM_STATE
{
	ITEM_STATE_INVENTORY,
	ITEM_STATE_DROP,
	ITEM_STATE_NON,
	ITEM_STATE_MAX
};

// �A�C�e���̑���
enum ITEM_ATTRIBUTE
{
	ITEM_ATTRIBUTE_ACTIVE,
	ITEM_ATTRIBUTE_PASSIVE,
	ITEM_ATTRIBUTE_MATERIAL,
	ITEM_ATTRIBUTE_ARMOR,
	ITEM_ATTRIBUTE_MAX
};


// �\����

// �A�C�e���p�\����
struct ITEM
{
	ITEM_STATE state;
	ITEM_TYPE type;
	ITEM_ATTRIBUTE attribute;
	int imageIndex;
	XY pos;
};

// �C���x���g���p�\����
struct INVENTORY
{
	ITEM_TYPE itemType;
	int num;
	int imageIndex;
};

// �v���g�^�C�v�錾
void ItemSystemInit(void);
void ItemGameInit(int invMax);
void ItemGameDraw(XY mapPos);
void ItemControl(void);
void UpdateInventoryList(int max);
bool AddInventoryList(int index);
void DeleteInventoryList(int index);
XY GetItemPos(int index);
INVENTORY* GetInventoryPointer(void);
void DeleteItem(int index);
int InventoryItemDraw(void);
bool UseItem(CHARACTER* player, int index);



