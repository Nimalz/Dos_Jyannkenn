#include "tutorial.h"
#include "renderer.h"
#include "main.h"
#include "player.h"

int control = 0;
BufferLine current;
//BufferLine temp2;
//BufferLine temp3;
BufferLine UI_Intro[DISP_H] =
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
					 { "┃                             ＼     へ   　／                                ┃\n",12},
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

//BufferLine narry1 =  { "┃「じゃんけん」の世界へようこそ                                             ┃\n",21 }; 
void InitTuto(void)
{
	control = 0;
}

void UpdateTuto(void)
{
	control++;
	switch (control)
	{
	case 1:
		system("cls");
		CharToBufferline("┃「じゃんけん」の世界へようこそ。                                             ┃\n", 21, &current);
		system("cls");
		break;
	case 2:
		system("cls");
		UI_Intro[20].line = current.line;
		CharToBufferline("┃ 僕はかかしです。　　　　　　　　　　　                                      ┃\n", 22, &current);
		break;
	case 3:
		system("cls");
		UI_Intro[20].line = current.line;
		CharToBufferline("┃ この世界は怖いんです。　　　　　　　                               　       ┃\n", 22, &current);
		break;
	case 4:
		system("cls");
		UI_Intro[20].line = current.line;
		CharToBufferline("┃ 「じゃんけん」ができないものは生きる価値もないだよ。            　　　　    ┃\n", 22, &current);
		break;
	case 5:
		system("cls");
		UI_Intro[20].line = current.line;
		CharToBufferline("┃ あなたはちゃんと「じゃんけん」できます？                           　       ┃\n", 22, &current);
		break;
	case 6:
		system("cls");
		UI_Intro[20].line = "┃                                                                             ┃\n";
		UI_Intro[11].line = "┃                             ＼    WWWW  　／                                ┃\n";
		CharToBufferline("┃ かかしに襲われた！                   　                   　　　　　　　    ┃\n",21, &current);
		break;

	}

}

void DrawTuto(void)
{
	if (control)
	{
		printWithRenew(UI_Intro, current);
	
		rewind(stdin);
		(void)_getch();
		if (control==6)
		SetMode(GAME_INTRO);
	}


}