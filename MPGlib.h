#ifndef MPG_LIB1
#define MPG_LIB1
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;
extern const char base_name[5] = "Mona" ;
extern bool dev_mode = false;
enum dam_type {Fixedtype = 0, ADtype};
bool probability(int percent);
enum Action_type {Phs_attack = 1, Mgc_attack, Escape, Self_heal};
enum stats {HP = 0, MaxHP, Atk, Dfs, Crt};//Attack, Defense, Critical
enum status_type {nmlStas = 0, slowStas, parzStas, stunStas, deadStas};//normal, slow, paralize, stun, dead
enum char_code {Player = 0, NPC, Monster};
class Character
{
protected:
	int Stat[5];//HP, MaxJP, Attack, Defense, Critical
	int atk_value = 100, spl_atk_value = 100, heal_value = 100, run_value = 100;//value of action
	status_type status = nmlStas;
	short status_duration = 0;//each number is each turn
	char_code character_code = Player;
	int pre_atk_type = 0, pre_ene_HP = 10000;
	stirng name = base_name;
public:
	Character(const char *character_name = base_name, char_code charac_code = Player);//apply stat
	
	void damage_in(int damage_type, int damage);
	
	int damage_out(int damage_type);
	
	bool HealByRatio(int heal_ratio);
	
	bool HealByAmmount(int heal_ammount);
	
	int give_HP_by_bp();
	
	int give_status();
	
	void calc_value(Character *Enemy);
	
	void Status_check();
	
	int AI_action();

	int action_choose(Character *Enemy);
	
	int AI_test(int v1, int v2, int v4, int mp);
	
	void Conduct_action(bool player, Character *Enemy);
	
    void level_up();
};

#endif