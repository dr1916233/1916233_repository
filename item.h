//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

//#pragma once

// �萔
#define ITEM_MAX 5	// �A�C�e���̍ő吔

// �A�C�e���̎��
enum ITEM_TYPE
{
	ITEM_TYPE_MAX
};

// �A�C�e���̏��
enum ITEM_STATE
{
	ITEM_STATE_INVENTORY,
	ITEM_STATE_DROP,
	ITEM_STATE_MAX
};


// �\����

// �A�C�e���p�\����
struct ITEM
{
	ITEM_STATE state;
	ITEM_TYPE type;
};

// �C���x���g���p�\����
struct INVENTORY
{
	ITEM_TYPE itemType;
	int num;
};

// �v���g�^�C�v�錾
void ItemSystemInit(void);
void ItemGameInit(void);
void ItemGameDraw(XY mapPos);
void ItemControl(void);




