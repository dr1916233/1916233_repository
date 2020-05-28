//--------------------------	--------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

//#pragma once//----------------------------------

// �萔�錾
#define SCREEN_SIZE_X	800		// �Q�[���X�N���[����X�T�C�Y
#define SCREEN_SIZE_Y	600		// �Q�[���X�N���[����Y�T�C�Y

#define GAME_SCREEN_X	800		// �Q�[���G���A�̃T�C�YX
#define GAME_SCREEN_Y	540		// �Q�[���G���A�̃T�C�YY

#define SCREEN_OFFSET_Y	60		// �Q�[���G���A�㕔�̗]��Y�T�C�Y

// �V�[���J�ڗp
enum SCENE_ID {
	SCENE_INIT,		// �������p
	SCENE_TITLE,	// �^�C�g��
	SCENE_GAME,		// �Q�[�����C��
	SCENE_GAMEOVER,	// �Q�[���I�[�o�[
	SCENE_MAX
};

// �����p
enum DIR
{
	DIR_DOWN,		// ��
	DIR_RIGHT,		// �E
	DIR_LEFT,		// ��
	DIR_UP,			// ��
	DIR_MAX
};

enum CHARATYPE
{
	CHARA_PLAYER,
	CHARA_ENEMY,
	CHARA_MAGIC,
	CHARATYPE_MAX
};

// --------------------
// �\����
// --------------------

// 2�����x�N�g���p
struct XY
{
	int x;
	int y;
};

// 2����float�p
struct XY_F
{
	float x;
	float y;
};

// �L�����N�^�[�p�\����
struct CHARACTER
{
	XY_F pos;			// ���W�p
	DIR dir;			// �I�u�W�F�N�g�̌���
	CHARATYPE type;		// �L�����N�^�[�̃^�C�v
	int enemyType;		// �G�̎��
	XY size;			// �T�C�Y
	XY offsetSize;		// �]���Ȃ��̃T�C�Y
	XY offsetSizeSide;	// �����猩���Ƃ��̗]���T�C�Y
	int rad;			// �~�Ŕ�������I�u�W�F�N�g�̔��a
	int lifeMax;		// HP�̊�b�l
	int life;			// ���ۂ�HP
	int animCnt;		// �A�j���[�V�����J�E���g�p
	float moveSpeed;	// �ړ����x
	bool visible;		// �������
	int level;			// ���x��
	int attack;			// �U���͗p
	bool moveFlag;		// �����Ă邩�ǂ����̔���p
	int inventoryCnt;	// �C���x���g���̐�
	int statusPoint;	// �X�e�[�^�X���㏸������񐔗p
};

// �v���g�^�C�v�錾
bool SystemInit(void);	// �V�X�e��������
void InitScene(void);	// �������V�[��
void TitleScene(void);	// �^�C�g���V�[��
void TitleDraw(void);	// �^�C�g���`��
void GameScene(void);	// �Q�[���V�[��
void GameDraw(XY mapPos);	// �Q�[���`��
void GameOverScene(void);	// �Q�[���I�[�o�[�V�[��
void GameOverDraw(void);	// �Q�[���I�[�o�[�`��
bool IsPassMain(XY playerPos); // �v���C���[������W��������Ēʉ߉\����Ԃ�
int RectHitCheckMain(CHARATYPE type, XY pos1, XY size1);	// ��`�̓����蔻��(�ڐG�F0�A��ڐG�F-1�A�_���[�W������ꍇ�F1�ȏ�̐���)
bool CircleHitCheckMain(CHARATYPE type, XY pos1, XY size1, int rad);	// �~�Ɖ~�̓����蔻��(�ڐG�F0�A��ڐG�F-1�A�_���[�W������ꍇ�F1�ȏ�̐���)
void ItemHitCheckMain(XY pPos, XY pSize);	// �v���C���[�ƃA�C�e���̓����蔻��
int InventoryItemDrawMain(void);	// �A�C�e���̕`��𑣂��A�`�悵������Ԃ�
XY GetMousePosMain(void);	// �}�E�X�̍��W�擾�p�֐�
bool UseItemMain(int index);
CHARACTER GetPlayerMain(void);	// �v���C���[�̏��擾
CHARACTER* GetPlayerPointerMain(void);	// �v���C���[�̃|�C���^���擾
void UpdateInvenyoryListMain(int max);
void DeleteInventoryListMain(int index);
void GetEventMain(XY pos);
void DoDamageMain(CHARATYPE charaType, int damage);	// �����œn���ꂽ�L�����N�^�[��HP���_���[�W�����Z����