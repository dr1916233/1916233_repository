//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "keycheck.h"

// �ϐ��錾
bool keyTrgUp[KEY_MAX];
bool keyTrgDown[KEY_MAX];
bool keyNow[KEY_MAX];
bool keyOld[KEY_MAX];


// �L�[���̏�����
void KeyInit(void)
{
	// �L�[���̏�����
	for (int keyID = 0; keyID < KEY_MAX; keyID++)
	{
		keyTrgUp[keyID] = false;
		keyTrgDown[keyID] = false;
		keyNow[keyID] = false;
		keyOld[keyID] = false;
	}
}

// �L�[�̏�Ԃ��`�F�b�N
void KeyCheck(void)
{
	//�@1�t���[���O�̏�Ԃ��`�F�b�N
	for (int keyID = 0; keyID < KEY_MAX; keyID++)
	{
		keyOld[keyID] = keyNow[keyID];
		//keyTrgUp[keyID] = true;
	}

	// ���̃t���[���̏�Ԃ�ۑ�
	keyNow[KEY_SPACE] = (bool)CheckHitKey(KEY_INPUT_SPACE);
	keyNow[KEY_DOWN] = (bool)CheckHitKey(KEY_INPUT_DOWN);
	keyNow[KEY_RIGHT] = (bool)CheckHitKey(KEY_INPUT_RIGHT);
	keyNow[KEY_LEFT] = (bool)CheckHitKey(KEY_INPUT_LEFT);
	keyNow[KEY_UP] = (bool)CheckHitKey(KEY_INPUT_UP);

	// �g���K�[����
	for (int keyID = 0; keyID < KEY_MAX; keyID++)
	{
		// �g���K�[�̏��̏�����
		keyTrgDown[keyID] = false;
		keyTrgUp[keyID] = false;

		// �g���K�[���̎擾
		if (!keyOld[keyID] && keyNow[keyID])
		{
			keyTrgUp[keyID] = true;
		}
	}
}