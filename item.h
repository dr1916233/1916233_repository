//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

//#pragma once

// �萔
#define ITEM_MAX 5	// �A�C�e���̍ő吔
#define ITEM_SIZE_X	32
#define ITEM_SIZE_Y 32

// �A�C�e���̎��
enum ITEM_TYPE
{
	ITEM_TYPE_STONE,	// ID�F0
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


// �\����

// �A�C�e���p�\����
struct ITEM
{
	ITEM_STATE state;
	ITEM_TYPE type;
	int imageIndex;
	XY pos;
	XY size;
};

// �C���x���g���p�\����
struct INVENTORY
{
	ITEM_TYPE itemType;
	int num;
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



