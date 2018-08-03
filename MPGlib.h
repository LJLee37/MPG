#ifndef MPG_LIB1
#define MPG_LIB1
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Random.h"
using namespace std;
const char base_name[] = "Mona" ;
//bool dev_mode = false;
enum dam_type {Fixedtype = 0, ADtype};
bool probability(int percent);
struct Stat
{
	int HP;
	int MaxHP;
	int Atk;
	int Dfs;
	int Cri;
};
enum Action_type {Phs_attack = 1, Mgc_attack, Escape, Self_heal};
enum state_type {nmlStas = 0, slowStas, parzStas, stunStas, deadStas};//normal, slow, paralize, stun, dead
class Character
{
protected:
	Stat char_stat;//HP, MaxJP, Attack, Defense, Critical
	int atk_value = 100, esc_value = 100;//value of action
	state_type state = nmlStas;
	short state_duration = 0;//each number is each turn
	int pre_atk_type = 0, pre_ene_HP = 10000;
	string name = base_name;
public:
	Character(string character_name = base_name, int inHP = 10000, int inMHP = 10000, int instr = 10, int indfs = 10, int incri = 0);//apply stat
	
	void damage_in(dam_type damage_type, int damage);
	
	int damage_out(dam_type damage_type);
	
	bool HealByRatio(int heal_ratio);//parameter is bp
	
	bool HealByAmmount(int heal_ammount);
	
	int give_HP_by_bp();
	
	state_type give_state();
	
	void calc_value(Character *Enemy);
	
	void State_check();
	
	Action_type AI_action();

	Action_type action_choose(Character *Enemy);
	
	//int AI_test(int v1, int v2, int v4, int mp);
	
	void Conduct_action(bool player, Character *Enemy);
	
    void level_up();
};

#endif