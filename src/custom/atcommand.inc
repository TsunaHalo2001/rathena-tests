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

/*=========================================
* Check values of resistance [keitenai]
*-----------------------------------------*/
ACMD_FUNC(resist) {
	char output[CHAT_SIZE_MAX];
	int i, j;
	struct {
		const char* format;
		int value;
	} output_table[] = {
		{ "   [ %d ] Resistencia Neutral", 0 }, // 0
		{ "   [ %d ] Resistencia Agua", 0 },
		{ "   [ %d ] Resistencia Tierra", 0 },
		{ "   [ %d ] Resistencia Fuego", 0 },
		{ "   [ %d ] Resistencia Viento", 0 },
		{ "   [ %d ] Resistencia Veneno", 0 },
		{ "   [ %d ] Resistencia Sagrado", 0 },
		{ "   [ %d ] Resistencia Oscuro", 0 },
		{ "   [ %d ] Resistencia Fantasma", 0 },
		{ "   [ %d ] Resistencia NoMuerto", 0 }, // 9

		{ "   [ %d ] Defensa Neutral", 0 }, // 10
		{ "   [ %d ] Defensa Agua", 0 },
		{ "   [ %d ] Defensa Tierra", 0 },
		{ "   [ %d ] Defensa Fuego", 0 },
		{ "   [ %d ] Defensa Viento", 0 },
		{ "   [ %d ] Defensa Veneno", 0 },
		{ "   [ %d ] Defensa Sagrado", 0 },
		{ "   [ %d ] Defensa Oscuro", 0 },
		{ "   [ %d ] Defensa Fantasma", 0 },
		{ "   [ %d ] Defensa NoMuerto", 0 }, // 19

		{ "   [ %d ] Resistencia a enemigos pequenos", 0 }, // 20
		{ "   [ %d ] Resistencia a enemigos medianos", 0 },
		{ "   [ %d ] Resistencia a enemigos grandes", 0 }, // 22

		{ "   [ %d ] Resistencia a enemigos normales", 0 }, // 23
		{ "   [ %d ] Resistencia a enemigos jefes", 0 },
		{ "   [ %d ] Resistencia a enemigos guardianes", 0 },
		{ "   [ %d ] Resistencia a enemigos campo de batalla", 0 }, // 26

		{ "   [ %d ] Resistencia a enemigos sin forma", 0 }, // 27
		{ "   [ %d ] Resistencia a enemigos no muertos", 0 },
		{ "   [ %d ] Resistencia a enemigos brutos", 0 },
		{ "   [ %d ] Resistencia a enemigos plantas", 0 },
		{ "   [ %d ] Resistencia a enemigos insectos", 0 },
		{ "   [ %d ] Resistencia a enemigos pescados", 0 },
		{ "   [ %d ] Resistencia a enemigos demonios", 0 },
		{ "   [ %d ] Resistencia a enemigos demi-humanos", 0 },
		{ "   [ %d ] Resistencia a enemigos angeles", 0 },
		{ "   [ %d ] Resistencia a enemigos dragones", 0 },
		{ "   [ %d ] Resistencia a jugadores", 0 }, // 38

		{ "   [ %d ] Resistencia a duendes", 0 }, // 39
		{ "   [ %d ] Resistencia a kobolds", 0 },
		{ "   [ %d ] Resistencia a orcos", 0 },
		{ "   [ %d ] Resistencia a golems", 0 },
		{ "   [ %d ] Resistencia a guardianes", 0 },
		{ "   [ %d ] Resistencia a ninjas", 0 },
		{ "   [ %d ] Resistencia a GVG", 0 },
		{ "   [ %d ] Resistencia a campo de batalla", 0 },
		{ "   [ %d ] Resistencia a tesoros", 0 },
		{ "   [ %d ] Resistencia a bio-laboratorio", 0 },
		{ "   [ %d ] Resistencia a Manuk", 0 },
		{ "   [ %d ] Resistencia a Splendide", 0 },
		{ "   [ %d ] Resistencia a Scaraba", 0 }, // 52

		{ "   [ %d ] Resistencia al dano a distancia", 0 }, // 53
		{ "   [ %d ] Resistencia al dano cuerpo a cuerpo", 0 },
		{ "   [ %d ] Inmunidad a las armas", 0 },
		{ "   [ %d ] Inmunidad a la magia", 0 },
		{ "   [ %d ] Inmunidad a otros", 0 }, // 56

		{ NULL, 0 }
	};
	memset(output, '\0', sizeof(output));
	clif_displaymessage(sd->fd, "========= Resistencia Totales =========");

	for (j = 0; j <= 9; j++) {
		output_table[j].value = (((sd->indexed_bonus.subele[j] + 
								   sd->indexed_bonus.subele_script[j]) + 
								   sd->indexed_bonus.subele[ELE_ALL]) + 
								   sd->indexed_bonus.subele_script[ELE_ALL]);
	}

	for (j = 0; j <= 9; j++) {
		output_table[j + 10].value = sd->indexed_bonus.subdefele[j] + 
								     sd->indexed_bonus.subdefele[ELE_ALL];
	}

	for (j = 0; j <= 2; j++) {
		output_table[j + 20].value = sd->indexed_bonus.subsize[j] + 
									 sd->indexed_bonus.subsize[SZ_ALL];
	}

	for (j = 0; j <= 3; j++) {
		output_table[j + 23].value = sd->indexed_bonus.subclass[j] + 
									 sd->indexed_bonus.subclass[CLASS_ALL];
	}

	for (j = 0; j <= 10; j++) {
		output_table[j + 27].value = sd->indexed_bonus.subrace[j] + 
									 sd->indexed_bonus.subrace[RC_ALL];
	}

	for (j = 0; j <= 13; j++) {
		output_table[j + 39].value = sd->indexed_bonus.subrace2[j];
	}

	output_table[53].value = sd->bonus.long_attack_def_rate;
	output_table[54].value = sd->bonus.near_attack_def_rate;
	output_table[55].value = sd->special_state.no_weapon_damage;
	output_table[56].value = sd->special_state.no_magic_damage;
	output_table[57].value = sd->special_state.no_misc_damage;

	for (i = 0; output_table[i].format != NULL; i++) {
		sprintf(output, output_table[i].format, output_table[i].value);
		clif_displaymessage(fd, output);
	}
	return 0;
}
/*
ACMD_FUNC(attack) {
	char output[CHAT_SIZE_MAX];
	int i, j;
	struct {
		const char* format;
		int value;
	} output_table[] = {
		{ "   [ %d ] atk_rate", 0 }, // 0


		{ NULL, 0 }
	};

	memset(output, '\0', sizeof(output));
	clif_displaymessage(sd->fd, "========= Bonus de Ataque Totales (test) =========");

	output_table[0].value = sd->bonus.atk_rate;
}*/