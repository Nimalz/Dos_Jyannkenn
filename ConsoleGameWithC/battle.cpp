#include "battle.h"
#include "main.h"
#include "enemy.h"
#include "player.h"
#include "renderer.h"
#include "input.h"

int cursor_battle;        //カーソルの現在位置を保存する
int kachimageFlag;		  //勝ち負けの結果を保存 1 PLAYER勝ち 0 エネミー勝ち 3 ひきわけ
SkillData* ewaza;
SkillData* pwaza;
bool PlayerDead = false;
bool EnemyDown = false;

BufferLine UI_Battle[DISP_H] =
{
					 { "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n", 1 },
					 { "┃                                ＿＿＿＿＿                                   ┃\n", 2},
					 { "┃                              ／          ＼                                 ┃\n", 3},
					 { "┃                            ／              ＼                               ┃\n", 4},
					 { "┃                          ／                  ＼                             ┃\n", 5},
					 { "┃                        ／＿＿＿＿＿＿＿＿＿＿＿＼                           ┃\n", 6},
					 { "┃                           (                  )                              ┃\n", 7},
					 { "┃                          (     へ     へ      )                             ┃\n", 8},
					 { "┃                          (     の     の      )                             ┃\n", 9},
					 { "┃                           (        も        )                              ┃\n",10},
					 { "┃                            (                )                               ┃\n",11},
					 { "┃                             ＼    WWWW   ／                                 ┃\n",12},
					 { "┃                               =          =                                  ┃\n",13},
					 { "┃                                  ＼\\\\／                                     ┃\n",14},
					 { "┃  ＼＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿／| ＼＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿／ ┃\n",15},
					 { "┃  ==＿＿＼＿＿＿＿＿＿＿＿＿      | |  |    ＿＿＿＿＿＿＿＿＿＿＿＿／＿＿== ┃\n",16},
					 { "┃  ／      |   z      z     z   z／  ＼ ＼   z      z     z   z     |      ＼ ┃\n",17},
					 { "┃          |  z   z z     z      |   /|  |  z   z z     z        z  |         ┃\n",18},
					 { "┃          |＿z＿＿z＿z＿z＿＿z  |  | |  |＿z＿＿z＿z＿z＿＿z z＿z＿|         ┃\n",19},
					 { "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n",20 },
					 { "┃                                                                             ┃\n",21},
					 { "┃                                                                             ┃\n",22},
					 { "┃                                                                             ┃\n",23},
					 { "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n",24},
};

BufferLine UI_Battle1[DISP_H] =
{
					 { "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n", 1 },
					 { "┃                                                                             ┃\n", 2},
					 { "┃                                                                             ┃\n", 3},
					 { "┃                                                                             ┃\n", 4},
					 { "┃                                                                             ┃\n", 5},
					 { "┃                                                                             ┃\n", 6},
					 { "┃                                                                             ┃\n", 7},
					 { "┃                                                                             ┃\n", 8},
					 { "┃                                                                             ┃\n", 9},
					 { "┃                                                                             ┃\n",10},
					 { "┃                                                                             ┃\n",11},
					 { "┃                                                                             ┃\n",12},
					 { "┃                                                                             ┃\n",13},
					 { "┃                                                                             ┃\n",14},
					 { "┃                                                                             ┃\n",15},
					 { "┃                                                                             ┃\n",16},
					 { "┃                                                                             ┃\n",17},
					 { "┃                                                                             ┃\n",18},
					 { "┃                                                                             ┃\n",19},
					 { "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n",20 },
					 { "┃                                                                             ┃\n",21},
					 { "┃                                                                             ┃\n",22},
					 { "┃                                                                             ┃\n",23},
					 { "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n",24},
};

BufferLine UI_Battle2[DISP_H] =
{
					 { "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n", 1 },
					 { "┃                                                                             ┃\n", 2},
					 { "┃                                                                             ┃\n", 3},
					 { "┃                                                                             ┃\n", 4},
					 { "┃                                                                             ┃\n", 5},
					 { "┃                   ＼￣＼                      ／￣／                        ┃\n", 6},
					 { "┃                  /l ＼  ＼                  ／  ／  lヽ                     ┃\n", 7},
					 { "┃                 | ヽ ヽ   |                ｜  /  /   |                     ┃\n", 8},
					 { "┃                 ＼ ` ‐ヽ  ヽ  ●      ●  /  / ‐   ／                     ┃\n", 9},
					 { "┃                   ＼ __ l  |  ｜|＿＿＿|｜ /  l __ ／                       ┃\n",10},
					 { "┃                        ＼  ＼ ／       ＼／  ／                             ┃\n",11},
					 { "┃                         ／＼|   人＿＿人  |／＼                             ┃\n",12},
					 { "┃                       ／／＼|             |／＼＼                           ┃\n",13},
					 { "┃                       ／／＼|             |／＼＼                           ┃\n",14},
					 { "┃                       ／   /＼＿＿＿＿＿／＼   ＼                           ┃\n",15},
					 { "┃                                                                             ┃\n",16},
					 { "┃                                                                             ┃\n",17},
					 { "┃                                                                             ┃\n",18},
					 { "┃                                                                             ┃\n",19},
					 { "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n",20 },
					 { "┃                                                                             ┃\n",21},
					 { "┃                                                                             ┃\n",22},
					 { "┃                                                                             ┃\n",23},
					 { "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n",24},
};

BufferLine PHP = { "┃ かかしに襲われた！                                                  ┃\n",21 };
BufferLine temp1 = { "┃ 格ゲーみたいにコマンドを入力中して「じゃんけん」で戦いましょう！            ┃\n",22 };
BufferLine temp2 = { "┃   WASD=↑←↓→            J=石 K=鋏 L=紙          ESC コマンド表    　　　 ┃\n",23 };

void InitBattle(void)
{
	ewaza = &(GetEnemy()->waza[0]);


}

void UninitBattle(void)
{

}

void UpdateBattle(void)
{
	Player* player = GetPlayer(0);
	pwaza = skilldecode();
	Enemy* enemy = GetEnemy();


	if (enemy->rageFlag)
	{
		int random = rand() % (enemy->wazamax + 2);
		if (random > enemy->wazamax - 1)
			ewaza = &(enemy->oowaza);
		else
			ewaza = &(enemy->waza[random]);
	}
	else
	{
		if ((enemy->wazanum % enemy->wazamax) || (enemy->wazanum == 0))
			ewaza = &(enemy->waza[enemy->wazanum % enemy->wazamax]);
		else
			ewaza = &(enemy->oowaza);
	}
	if (pwaza->index == 999)
	{
		player->hp--;
		pwaza->move = (SkillAttribute)(rand() % 3);
	}
	if (ewaza->index == 999)
	{
		enemy->hp--;
		ewaza->move = (SkillAttribute)(rand() % 3);
	}
	kachimageFlag = syoubuCheck(pwaza, ewaza);


	switch (kachimageFlag)
	{
	case 0:
		player->hp -= ewaza->dam;
		break;
	case 1:
		enemy->hp -= pwaza->dam;
		break;
	case 3:
		break;
	}
	if (player->hp <= 0)
	{
		player->hp = 0;
		PlayerDead = true;
		return;
	}
	else if (enemy->hp <= 0)
	{
		enemy->hp = 0;
		EnemyDown = true;
		return;
	}


}

void DrawBattle(void)
{
	if (!GetInputDone())
	{
		DrawBattleInput();
	}
	else
	{
		DrawBattleDisp();
	}


}

//指令入力完了後の描画処理
void DrawBattleDisp(void)
{
	Player* player = GetPlayer(0);
	Enemy* enemy = GetEnemy();
	int lenp = strlen(pwaza->movename);
	int lene = strlen(ewaza->movename);
	if (enemy->name == kakashi)
		printBufferFrameWithIndex(UI_Battle, 0, 20);
	else if (enemy->name == kani)
		printBufferFrameWithIndex(UI_Battle2, 0, 20);
	printf("┃");
	for (int i = 0; i < 36 - (lenp + lene) / 2; i++)
	{
		printf(" ");
	}

	printf("%s VS %s", pwaza->movename, ewaza->movename);
	for (int i = 0; i < 37 - (lenp + lene) / 2; i++)
	{
		printf(" ");
	}
	printf("┃\n");

	printf("┃ PLAYER HP:%2d        ", player->hp);
	for (int i = 0; i < 9; i++)
	{
		printf(" ");
	}
	if (pwaza->move == guu)
		printf("石属性");
	if (pwaza->move == choki)
		printf("鋏属性");
	if (pwaza->move == paa)
		printf("紙属性");
	/*if (pwaza->move == SkillAttribute::random)
		printf("ランダム");*/
	printf("  ");
	if (kachimageFlag == 1)
		printf(">");
	else if (kachimageFlag == 0)
		printf("<");
	else
		printf("=");
	printf("  ");
	if (ewaza->move == guu)
		printf("石属性");
	if (ewaza->move == choki)
		printf("鋏属性");
	if (ewaza->move == paa)
		printf("紙属性");
	/*if (ewaza->move == SkillAttribute::random)
		printf("ランダム");*/

	for (int i = 0; i < 19; i++)
	{
		printf(" ");
	}
	printf("%2d:ENEMY HP", enemy->hp);
	printf("┃\n");

	printf("┃                   ");
	printf("コマンド：");
	for (int i = 0; i < pwaza->input.len; i++)
	{
		switch (pwaza->input.Input[i])
		{
		case IS_UP_PRESSED:
			printf("↑");
			break;
		case IS_DOWN_PRESSED:
			printf("↓");
			break;
		case IS_LEFT_PRESSED:
			printf("←");
			break;
		case IS_RIGHT_PRESSED:
			printf("→");
			break;
		case IS_GUU_PRESSED:
			printf("石");
			break;
		case IS_CHOKI_PRESSED:
			printf("鋏");
			break;
		case IS_PAA_PRESSED:
			printf("紙");
			break;
		}
	}
	for (int i = 0; i < 48 - (pwaza->input.len) * 2; i++)
	{
		printf(" ");
	}

	printf("┃\n");

	if (enemy->name == kakashi)
		printBufferFrameWithIndex(UI_Battle, 23, 24);
	else if (enemy->name == kani)
		printBufferFrameWithIndex(UI_Battle2, 23, 24);

	SetInputDone(false);
	initInputBuffer(&player->Input);
	rewind(stdin);
	(void)_getch();
	if (PlayerDead)
	{
		system("cls");
		if (enemy->name == kakashi)
			printWithRenew(UI_Battle, { "┃プレイヤーが倒されました、、、                                               ┃\n",21 });
		else if (enemy->name == kani)
			printWithRenew(UI_Battle2, { "┃プレイヤーが倒されました、、、                                               ┃\n",21 });
		rewind(stdin);
		(void)_getch();
		SetMode(GAME_MENU);
		PlayerDead = false;
		InitPlayer();
		LoadEnemy(kakashi);
		SkillFukugenn();
		return;
	}

	if (EnemyDown)
	{
		system("cls");
		printWithRenew(UI_Battle1, { "┃エネミーを倒した。新しい技を覚えたかも…                           　        ┃\n",21 });
		if (enemy->name == kakashi)
		{
			GetSkillTable()->KakashiAtt1.leanrned = true;
			GetSkillTable()->KakashiAtt2.leanrned = true;
			GetSkillTable()->KakashiAtt3.leanrned = true;
		}
		else if (enemy->name == kani)
		{
			GetSkillTable()->KaniAtt1.leanrned = true;
			GetSkillTable()->KaniAtt2.leanrned = true;
			GetSkillTable()->KaniAtt3.leanrned = true;

			GetSkillTable()->KaniOowaza.leanrned = true;
		}
		rewind(stdin);
		(void)_getch();
		Sleep(1000);
		printWithRenew(UI_Battle2, { "┃変な蟹に見つかられました！                                          　       ┃\n",21 });
		rewind(stdin);
		(void)_getch();
		Sleep(1000);
		SetMode(GAME_BATTLE);
		LoadEnemy(kani);
		EnemyDown = false;
		InitPlayer();

		return;
	}


	temp1 = { "┃ 次は何技を使う？                                   　　　　                 ┃\n",22 };
}

//指令入力中の描画処理
void DrawBattleInput(void)
{
	Player* player = GetPlayer(0);
	Enemy* enemy = GetEnemy();
	if (enemy->name == kakashi)
	{
		
		printBufferFrameWithIndex(UI_Battle, 0, 20);
		DrawLine(temp1.line);
		DrawLine(UI_Battle[21].line);
		DrawLine(temp2.line);
		DrawLine(UI_Battle[23].line);
	}
	else if (enemy->name == kani)
	{
		
		printBufferFrameWithIndex(UI_Battle2, 0, 20);
		DrawLine(temp1.line);
		DrawLine(UI_Battle2[21].line);
		DrawLine(temp2.line);
		DrawLine(UI_Battle2[23].line);
	}


	for (int i = 0; i < player->Input.count; i++)
	{
		switch (player->Input.buffer[i])
		{
		case IS_UP_PRESSED:
			printf("%s", "↑");
			break;
		case IS_DOWN_PRESSED:
			printf("%s", "↓");
			break;
		case IS_LEFT_PRESSED:
			printf("%s", "←");
			break;
		case IS_RIGHT_PRESSED:
			printf("%s", "→");
			break;
		case IS_GUU_PRESSED:
			printf("%s", "石");
			break;
		case IS_CHOKI_PRESSED:
			printf("%s", "鋏");
			break;
		case IS_PAA_PRESSED:
			printf("%s", "紙");
			break;

		}
	}
	Sleep(100);
}

int syoubuCheck(SkillData* pin, SkillData* ein)
{
	//if (pin->movename)
	if (((ein->move - (pin->move)) == -1) || ((ein->move - (pin->move)) == 2))
	{
		return 0;//エネミー勝利
	}
	else if (((ein->move - (pin->move)) == 1) || ((ein->move - (pin->move)) == -2))
	{
		return 1;//プレイヤー勝利
	}

	return 3;//ひきわけ
}

