#pragma once
#include "skill.h"
#define ENEMY_SKILL_MAX (5)
#define DEBUT_ENEMY     (kakashi)

enum EnemyName
{
	kakashi,
	kani,
	doeromon,
	monkey,
};

struct Enemy
{
	int diff;			//難易度制御変数
	int hp;	
	int wazamax;		//使える技の数
	int wazanum;        //次何番目の技を使う
	bool rageFlag;     //暴走mode　flag
	EnemyName name;		
	SkillData oowaza;
	SkillData waza[ENEMY_SKILL_MAX];
};



void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);

void LoadKakashi(void);
void LoadKani(void);
void LoadDoeromon(void);
void LoadMonkey(void);

void LoadEnemy(EnemyName);
Enemy* GetEnemy(void);

