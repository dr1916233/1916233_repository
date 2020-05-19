//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------
#include "DxLib.h"
#include "main.h"
#include "item.h"

// �ϐ��錾
ITEM item[ITEM_MAX];	// �A�C�e���p
INVENTORY* inventoryList; // �C���x���g�����̃A�C�e������p
int inventoryListCnt;	// �C���x���g���z��̍Ō�̃C���f�b�N�X�ێ��p

// �A�C�e���̃V�X�e��������
void ItemSystemInit(void)
{

}

// �A�C�e���̃Q�[��������
void ItemGameInit(int invMax)
{
	// �v���C���[�C���x���g�����쐬
	inventoryList = (INVENTORY*)malloc(sizeof(INVENTORY) * invMax);
}

// �A�C�e���̃Q�[���`��
void ItemGameDraw(XY mapPos)
{

}

// �A�C�e���̃R���g���[��
void ItemControl(void)
{
	
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
		inventoryList[listCnt] = inventoryListCopy[listCnt];
	}

	// �R�s�[�̃��������J��
	free(inventoryListCopy);
}

bool AddInventoryList(ITEM insertItem,int index)
{
	// ���X�g�̈�ԍŌ�ɃA�C�e���������false��Ԃ��ăA�C�e���擾�s�ɂ���
	if (inventoryList[inventoryListCnt].num > 0) return false; 
	
	// �A�C�e���}���ʒu�ۑ��p
	int insertIndex = 0;
	
	// ���X�g�ɂ��łɎ����Ă���A�C�e��������ΐ��𑝂₷
	for (int listCnt = 0; listCnt < insertIndex; listCnt++)
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


