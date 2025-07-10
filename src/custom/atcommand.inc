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
	int i;
	struct {
		const char* format;
		int value;
	} output_table[] = {
		{ "   [ %d ] Resistencia Neutral", 0 },
		{ "   [ %d ] Resistencia Agua", 0 },
		{ "   [ %d ] Resistencia Tierra", 0 },
		{ "   [ %d ] Resistencia Fuego", 0 },
		{ "   [ %d ] Resistencia Viento", 0 },
		{ "   [ %d ] Resistencia Veneno", 0 },
		{ "   [ %d ] Resistencia Sagrado", 0 },
		{ "   [ %d ] Resistencia Oscuro", 0 },
		{ "   [ %d ] Resistencia Fantasma", 0 },
		{ "   [ %d ] Resistencia NoMuerto", 0 },
//		{ "   [ %d ] Resist to all", 0 },
		{ NULL, 0 }
	};
	memset(output, '\0', sizeof(output));
	clif_displaymessage(sd->fd, "========= Resistencia Totales =========");
	output_table[0].value = (sd->indexed_bonus.subele[ELE_NEUTRAL] + sd->indexed_bonus.subele_script[ELE_NEUTRAL] + sd->indexed_bonus.subele[ELE_ALL] + sd->indexed_bonus.subele_script[ELE_ALL]);
	output_table[1].value = (sd->indexed_bonus.subele[ELE_WATER] + sd->indexed_bonus.subele_script[ELE_WATER] + sd->indexed_bonus.subele[ELE_ALL] + sd->indexed_bonus.subele_script[ELE_ALL]);
	output_table[2].value = (sd->indexed_bonus.subele[ELE_EARTH] + sd->indexed_bonus.subele_script[ELE_EARTH] + sd->indexed_bonus.subele[ELE_ALL] + sd->indexed_bonus.subele_script[ELE_ALL]);
	output_table[3].value = (sd->indexed_bonus.subele[ELE_FIRE] + sd->indexed_bonus.subele_script[ELE_FIRE] + sd->indexed_bonus.subele[ELE_ALL] + sd->indexed_bonus.subele_script[ELE_ALL]);
	output_table[4].value = (sd->indexed_bonus.subele[ELE_WIND] + sd->indexed_bonus.subele_script[ELE_WIND]) + sd->indexed_bonus.subele[ELE_ALL] + sd->indexed_bonus.subele_script[ELE_ALL];
	output_table[5].value = (sd->indexed_bonus.subele[ELE_POISON] + sd->indexed_bonus.subele_script[ELE_POISON] + sd->indexed_bonus.subele[ELE_ALL] + sd->indexed_bonus.subele_script[ELE_ALL]);
	output_table[6].value = (sd->indexed_bonus.subele[ELE_HOLY] + sd->indexed_bonus.subele_script[ELE_HOLY] + sd->indexed_bonus.subele[ELE_ALL] + sd->indexed_bonus.subele_script[ELE_ALL]);
	output_table[7].value = (sd->indexed_bonus.subele[ELE_DARK] + sd->indexed_bonus.subele_script[ELE_DARK] + sd->indexed_bonus.subele[ELE_ALL] + sd->indexed_bonus.subele_script[ELE_ALL]);
	output_table[8].value = (sd->indexed_bonus.subele[ELE_GHOST] + sd->indexed_bonus.subele_script[ELE_GHOST] + sd->indexed_bonus.subele[ELE_ALL] + sd->indexed_bonus.subele_script[ELE_ALL]);
	output_table[9].value = (sd->indexed_bonus.subele[ELE_UNDEAD] + sd->indexed_bonus.subele_script[ELE_UNDEAD] + sd->indexed_bonus.subele[ELE_ALL] + sd->indexed_bonus.subele_script[ELE_ALL]);
//	output_table[10].value = (sd->subele[ELE_ALL] + sd->subele_script[ELE_ALL]);

	for (i = 0; output_table[i].format != NULL; i++) {
		sprintf(output, output_table[i].format, output_table[i].value);
		clif_displaymessage(fd, output);
	}
	return 0;
}