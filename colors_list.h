/// ARQUIVO COM CADASTRO DE CORES NO FORMATO RGB

#ifndef COLORS_LIST_H
#define COLORS_LIST_H

static Color white = {255, 255, 255};
static Color black = {0, 0, 0};
static Color red = {255, 0, 0};
static Color green = {0, 255, 0};
static Color blue = {0, 0, 255};

static Color magenta = {255, 0, 255};
static Color ciano = {0, 255, 255};
static Color yellow = {255, 255, 0};
static Color gold = {255, 215, 0};
static Color sandy_brown = {244,164,96};
static Color dark_orange = {255,140,0};


///--------------------- CONJUNTOS COMUNS DE CORES --------------------

static Color rgb[] = {red, green, blue};
static Color sea[] = {blue, ciano, blue, magenta};
static Color sun[] = {yellow, gold, yellow, gold};
static Color sand[] = {dark_orange, sandy_brown, sandy_brown, dark_orange};

#endif // COLORS_LIST_H
