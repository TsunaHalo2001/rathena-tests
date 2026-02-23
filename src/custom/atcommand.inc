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
		{ "   [ %d ] Resistencia a todos los elementos", 0 },
		{ NULL, 0 }
	};
	memset(output, '\0', sizeof(output));
	clif_displaymessage(sd->fd, "========= Resistencia Totales =========");

	for (j = 0; j <= 10; j++) {
		output_table[j].value = (sd->indexed_bonus.subele[j] + sd->indexed_bonus.subele_script[j] + sd->indexed_bonus.subele[ELE_ALL] + sd->indexed_bonus.subele_script[ELE_ALL]);
	}
	
	for (i = 0; output_table[i].format != NULL; i++) {
		sprintf(output, output_table[i].format, output_table[i].value);
		clif_displaymessage(fd, output);
	}
	return 0;
}