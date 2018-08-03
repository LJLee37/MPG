#include "MPGlib.h"
bool probability(int basis_point)
{
	for (int temp = gen(0,10000); basis_point >= 0; basis_point--)
		if (temp == basis_point)
			return true;
	return false;
}

Character::Character(string character_name,  int inHP, int inMHP, int inatk, int indfs, int incri)//apply stat
{
	char_stat.HP = inHP;
	char_stat.MaxHP = inMHP;
	char_stat.Atk = inatk;
	char_stat.Dfs = indfs;
	char_stat.Cri = incri;//critical is basis point(1 = 0.01%)
	name = character_name;
	bool ifbase_name = false;
	if(name == base_name)
		ifbase_name = true;
	//pre_ene_dmg = 10000;
}

void Character::damage_in(dam_type damage_type, int damage)
{
	switch (damage_type)
	{
	case Fixedtype:
		char_stat.HP -= damage;
		break;
	case ADtype:
		char_stat.HP -= ((100 * damage - char_stat.Dfs) / (char_stat.Dfs + 1));
		break;
	}
}
int Character::damage_out(dam_type damage_type)
{
	switch(damage_type)
	{
	case ADtype:
		return (char_stat.Atk * char_stat.Atk + 100) / (10000 - char_stat.Atk) * 10000 / char_stat.Atk;
		break;
	}
}
bool Character::HealByRatio(int heal_ratio)
{
	if (state == 4)
		return false;
	char_stat.HP += char_stat.MaxHP * (heal_ratio / 10000.0);
	return true;
}
bool Character::HealByAmmount(int heal_ammount)
{
	if (state == 4)
		return false;
	char_stat.HP += heal_ammount;
	return true;
}
int Character::give_HP_by_bp()
{
	return (char_stat.HP / char_stat.MaxHP * 10000.0);
}
state_type Character::give_state()
{
	return state;
}
void Character::calc_value(Character *Enemy)
{
	//calculaing action's value
	switch (pre_atk_type)
	{
	case ADtype:
		atk_value += (char_stat.Atk * 0.1 + (pre_ene_HP - Enemy->give_HP_by_bp())) * (char_stat.Atk * 0.3 - (pre_ene_HP - Enemy->give_HP_by_bp())) / abs(char_stat.Atk * 0.3 - (pre_ene_HP - Enemy->give_HP_by_bp()));
		break;
	}
}

void Character::State_check()
{
	state_duration--;
	if (state_duration <= 0)
	{
		state_duration = 0;
		state = nmlStas;
	}
	if (char_stat.HP == 0)
	{
		state = deadStas;
		state_duration = 999999;
	}
	if (char_stat.HP > char_stat.MaxHP)
		char_stat.HP = char_stat.MaxHP;
}

Action_type Character::AI_action()
{
	if (atk_value >= esc_value)
		return Phs_attack;
	else
		return Escape;
}

/*
Action_type Character::AI_action()
{
	cout << "AI is choosing action..." << endl;//choose action by action's value
	int priority1, priority2, priority3;
	if(atk_value >= spl_atk_value)
	{
		if(atk_value >= heal_value)
		{
			if(atk_value >= run_value)
				return 1;
			else
				return 3;
		}
		else
		{
			if(heal_value >= run_value)
			{
				priority1 = 4;
				if(atk_value >= run_value)
					priority2 = 1;
				else
					priority2 = 3;
			}
			else
				return 3;
		}
	}
	else
	{
		if(spl_atk_value >= heal_value)
		{
			if(spl_atk_value >= run_value)
			{
				priority1 = 2;
				if(atk_value >= heal_value)
					{
					if(atk_value >= run_value)
						priority2 = 1;
					else
						priority2 = 3;
				}
				else
				{
					if(heal_value >= run_value)
					{
						priority2 = 4;
						if(atk_value >= run_value)
							priority3 = 1;
						else
							priority3 = 3;
					}
					else
						priority2 = 3;
				}
			}
			else
			{
				if(heal_value >= run_value)
				{
					priority1 = 4;
					if(spl_atk_value >= run_value)
					{	
						priority2 = 2;
						if(atk_value >= run_value)
							priority3 = 1;
    					else
							priority3 = 3;
					}
					else
						priority2 = 3;
				}
			else
				return 3;
			}
		}
		else
		{
			if(heal_value >= run_value)
			{
				priority1 = 4;
				if(atk_value >= run_value)
						priority2 = 1;
					else
						priority2 = 3;
			}
			else
				return 3;
		}
	}
	switch(priority1)
	{
	case 2:
		if(MP >= 20)
			return priority1;
		else
		{
			switch(priority2)
			{
			case 1:
			case 3:
				return priority2;
				break;
			case 4:
				if(MP >= 10)
					return priority2;
				else
					return priority3;
			}
		}
		break;
	case 4:
		if(MP >= 10)
			return priority1;
		else
			return priority2;
	}
}
*/

///*
Action_type Character::action_choose(Character *Enemy)
{
	//clear screen
	cout << "추천도:" << endl;
	cout << "공격 : " << atk_value << endl;
	//cout << "마법공격 : " << spl_atk_value << endl;
	cout << "도주 : " << esc_value << endl;
	//cout << "자가치유 : " << heal_value << endl;
	cout << endl;
	cout << "할 행동을 선택하십시오." << endl;
	cout << "1: 공격\t2: 마법공격(비활성화됨)" << endl;
	cout << "3: 도주\t4: 자가치유(비활성화됨)" << endl;
	cout << "선택 : ";
	Action_type action;
	int temp;
	cin >> temp;
	action = Action_type(temp);
	if((action != Phs_attack) || (action != Escape))
	{
		cout << "올바르지 않은 선택입니다." << endl;
		//pause
		action = this->action_choose(Enemy);
	}
	return action;
}
//*/
/*
int Character::AI_test(int v1, int v2, int v4, int mp)
{
	int t1, t2, t4, tmp, tmmp, rtn;
	t1 = atk_value;
	t2 = spl_atk_value;
	t4 = heal_value;
	tmp = MP;
	tmmp = MaxMP;
	atk_value = v1;
	spl_atk_value = v2;
	heal_value = v4;
	MP = MaxMP = mp;
	rtn = AI_action();
	atk_value = t1;
	spl_atk_value = t2;
	heal_value = t4;
	MP = tmp;
	MaxMP = tmmp;
	return rtn;
}
*/

void Character::Conduct_action(bool player, Character *Enemy)
{
	Action_type action;
	if(player)
		action = action_choose(Enemy);
	else
		action = AI_action();
	switch(action)
	{
	case Phs_attack:
		Enemy->damage_in(ADtype,damage_out(ADtype));
		break;
	/*
	case Mgc_attack:
		Enemy->damage_in(APtype,damage_out(APtype));
		Stat[MP] -= 20;
		break;
		*/
	case Escape:
		cout << name << "은(는) ";
		if(probability(50))
		{
			cout << "성공적으로 도망쳤다" << endl;
			//...
		}
		else
		{
			cout << "도망에 실패했다!" << endl;
			//...
		}
	}
}


void Character::level_up()
{
    //
}
