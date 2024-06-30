// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom Atcommands
 * Place the body of custom atcommands in this file.
 * Format:
 *	ACMD_FUNC(command_name)
 *	{
 *		<code>;
 *	}
 **/

//ACMD_FUNC(newcommand)
//{
//	clif_displaymessage(fd, "It works!");
//	clif_specialeffect(&sd->bl, EF_HEARTCASTING, AREA);
//	return 0;
//}

ACMD_FUNC(resist) {
	char resis_state[100];
	char info[CHAT_SIZE_MAX];
	int j, count = 0;
	struct {
		const char* format;
		int value;
	} info_table[] = {
		{ NULL, 0 },
		{ "   [ %d ] Small size resist", 0 }, // 1
		{ "   [ %d ] Medium size resist", 0 },
		{ "   [ %d ] Large size resist", 0 },

		{ "   [ %d ] Normal class resist", 0 },
		{ "   [ %d ] Boss class resist", 0 },
		{ "   [ %d ] Guardian class resist", 0 },
		{ "   [ %d ] Battlefield class resist", 0 }, // 7

		{ "   [ %d ] Formless race resist", 0 },
		{ "   [ %d ] Undead race resist", 0 },
		{ "   [ %d ] Brute race resist", 0 },
		{ "   [ %d ] Plant race resist", 0 },
		{ "   [ %d ] Insect race resist", 0 },
		{ "   [ %d ] Fish race resist", 0 },
		{ "   [ %d ] Demon race resist", 0 },
		{ "   [ %d ] Demi-Human race resist", 0 },
		{ "   [ %d ] Angel race resist", 0 },
		{ "   [ %d ] Dragon race resist", 0 },
		{ "   [ %d ] Player race resist", 0 }, // 18

		{ "   [ %d ] Resistance from Goblin", 0 },
		{ "   [ %d ] Resistance from Kobold", 0 },
		{ "   [ %d ] Resistance from Orc", 0 },
		{ "   [ %d ] Resistance from Golem", 0 },
		{ "   [ %d ] Resistance from Guardian", 0 },
		{ "   [ %d ] Resistance from Ninja", 0 },
		{ "   [ %d ] Resistance from GVG", 0 },
		{ "   [ %d ] Resistance from Battlefield", 0 },
		{ "   [ %d ] Resistance from Treasure", 0 },
		{ "   [ %d ] Resistance from Biolab", 0 },
		{ "   [ %d ] Resistance from Manuk", 0 },
		{ "   [ %d ] Resistance from Splendide", 0 },
		{ "   [ %d ] Resistance from Scaraba", 0 }, // 31

		{ "   [ %d ] Neutral element resist", 0 },
		{ "   [ %d ] Water element resist", 0 },
		{ "   [ %d ] Earth element resist", 0 },
		{ "   [ %d ] Fire element resist", 0 },
		{ "   [ %d ] Wind element resist", 0 },
		{ "   [ %d ] Poison element resist", 0 },
		{ "   [ %d ] Holy element resist", 0 },
		{ "   [ %d ] Dark element resist", 0 },
		{ "   [ %d ] Ghost element resist", 0 },
		{ "   [ %d ] Undead element resist", 0 }, // 41

		{ "   [ %d ] Neutral element defense", 0 },
		{ "   [ %d ] Water element defense", 0 },
		{ "   [ %d ] Earth element defense", 0 },
		{ "   [ %d ] Fire element defense", 0 },
		{ "   [ %d ] Wind element defense", 0 },
		{ "   [ %d ] Poison element defense", 0 },
		{ "   [ %d ] Holy element defense", 0 },
		{ "   [ %d ] Dark element defense", 0 },
		{ "   [ %d ] Ghost element defense", 0 },
		{ "   [ %d ] Undead element defense", 0 }, // 51

		{ "   [ %d ] Long range damage resist", 0 },
		{ "   [ %d ] Melee damage resist", 0 }, // 53
		{ "   [ %d ] Weapon immunity", 0 },
		{ "   [ %d ] Magic immunity", 0 }, 
		{ "   [ %d ] Misc immunity", 0 }, // 56
		{ NULL, 0 }
	};

	memset(resis_state, '\0', sizeof(resis_state));
	memset(info, '\0', sizeof(info));

		
		info_table[0].format = resis_state;

		for (j = 0; j <= 2; j++)
			info_table[j+1].value = sd->indexed_bonus.subsize[SZ_ALL] + sd->indexed_bonus.subsize[j];

		for (j = 0; j <= 3; j++)
			info_table[j+4].value = sd->indexed_bonus.subclass[CLASS_ALL] + sd->indexed_bonus.subclass[j];

		for (j = 0; j <= 10; j++)
			info_table[j+8].value = sd->indexed_bonus.subrace[RC_ALL] + sd->indexed_bonus.subrace[j];

		for (j = 0; j <= 13; j++)
			info_table[j+19].value = sd->indexed_bonus.subrace2[j];

		for (j = 0; j <= 9; j++){
			info_table[j+32].value = (((
				sd->indexed_bonus.subele[ELE_ALL] +
				sd->indexed_bonus.subele_script[ELE_ALL] ) +
				sd->indexed_bonus.subele[j] ) +
				sd->indexed_bonus.subele_script[j] );
		}

		for (j = 0; j <= 9; j++)
			info_table[j+42].value = sd->indexed_bonus.subdefele[ELE_ALL] + sd->indexed_bonus.subdefele[j];

		info_table[52].value = sd->bonus.long_attack_def_rate;
		info_table[53].value = sd->bonus.near_attack_def_rate;
		info_table[54].value = sd->special_state.no_weapon_damage;
		info_table[55].value = sd->special_state.no_magic_damage;
		info_table[56].value = sd->special_state.no_misc_damage;

	for (j = 1; info_table[j].format != NULL; j++){
		if( info_table[j].value != 0 )
			count =+ 1;
	}

	if( count == 0 ){
		sprintf(resis_state, "You don't have any resistance.");
		clif_messagecolor(&sd->bl, color_table[COLOR_RED], resis_state, false, SELF);
	} else {
		sprintf(resis_state, "======== Resistance ========");
		clif_messagecolor(&sd->bl, color_table[COLOR_WHITE], resis_state, false, SELF);
	}

	for (j = 1; info_table[j].format != NULL; j++) {
		sprintf(info, info_table[j].format, info_table[j].value);
		if (info_table[j].value > 0 && info_table[j].value <= 70)
			clif_messagecolor(&sd->bl, color_table[COLOR_CYAN], info, false, SELF);
		else if (info_table[j].value > 70)
			clif_messagecolor(&sd->bl, color_table[COLOR_YELLOW], info, false, SELF);
		else  if (info_table[j].value < 0)
			clif_messagecolor(&sd->bl, color_table[COLOR_RED], info, false, SELF);
	}
	return 0;
}