/*
*  Color definitions (RGB values taken from POV-Ray sources).
*
*  Copyright (C) 1998, 1999 Angel Jimenez Jimenez and Carlos Jimenez Moreno
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful, but
*  WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

Color CWhite   = Color (1, 1, 1);
Color CBlack   = Color (0, 0, 0);
Color CRed     = Color (1, 0, 0);
Color CGreen   = Color (0, 1, 0);
Color CBlue    = Color (0, 0, 1);
Color CYellow  = Color (1, 1, 0);
Color CCyan    = Color (0, 1, 1);
Color CMagenta = Color (1, 0, 1);

/*
define Color CDimGrey		{ red 0.329412	green 0.329412	blue 0.329412 }
define Color CGrey		{ red 0.752941	green 0.752941	blue 0.752941 }
define Color CLightGrey		{ red 0.658824	green 0.658824	blue 0.658824 }
define Color CVLightGrey	{ red 0.80	green 0.80	blue 0.80 }

define Color CAquamarine	{ red 0.439216	green 0.858824	blue 0.576471 }
define Color CViolet		{ red 0.62352	green 0.372549	blue 0.623529 }
define Color CBrown		{ red 0.647059	green 0.164706	blue 0.164706 }
define Color CCadet		{ red 0.372549	green 0.623529	blue 0.623529 }
define Color CCoral		{ red 1.0	green 0.498039	blue 0.0 }
define Color CCornflower	{ red 0.258824	green 0.258824	blue 0.435294 }
define Color CDark		{ red 0.184314	green 0.309804	blue 0.184314 }
define Color CDarkOlive		{ red 0.309804	green 0.309804	blue 0.184314 }
define Color CDarkOrchid	{ red 0.6	green 0.196078	blue 0.8 }
define Color CDarkSlate		{ red 0.419608	green 0.137255	blue 0.556863 }
define Color CDarkSlateGray	{ red 0.184314	green 0.309804	blue 0.309804 }
define Color CDarkSlateGrey	{ red 0.184314	green 0.309804	blue 0.309804 }
define Color CDarkTurquoise	{ red 0.439216	green 0.576471	blue 0.858824 }
define Color CFirebrick		{ red 0.556863	green 0.137255	blue 0.137255 }
define Color CForest		{ red 0.137255	green 0.556863	blue 0.137255 }
define Color CGold		{ red 0.8	green 0.498039	blue 0.196078 }
define Color CGoldenrod		{ red 0.858824	green 0.858824	blue 0.439216 }
define Color CIndian		{ red 0.309804	green 0.184314	blue 0.184314 }
define Color CKhaki		{ red 0.623529	green 0.623529	blue 0.372549 }
define Color CLight		{ red 0.74902	green 0.847059	blue 0.847059 }
define Color CLightSteel	{ red 0.560784	green 0.560784	blue 0.737255 }
define Color CLime		{ red 0.196078	green 0.8	blue 0.196078 }
define Color CMaroon		{ red 0.556863	green 0.137255	blue 0.419608 }
define Color CMediumAquamarine	{ red 0.196078	green 0.8	blue 0.6 }
define Color CMedium		{ red 0.196078	green 0.196078	blue 0.8 }
define Color CMediumForest	{ red 0.419608	green 0.556863	blue 0.137255 }
define Color CMediumGoldenrod	{ red 0.917647	green 0.917647	blue 0.678431 }
define Color CMediumOrchid	{ red 0.576471	green 0.439216	blue 0.858824 }
define Color CMediumSea		{ red 0.258824	green 0.435294	blue 0.258824 }
define Color CMediumTurquoise	{ red 0.439216	green 0.858824	blue 0.858824 }
define Color CMediumViolet	{ red 0.858824	green 0.439216	blue 0.576471 }
define Color CMidnight		{ red 0.184314	green 0.184314	blue 0.309804 }
define Color CNavy		{ red 0.137255	green 0.137255	blue 0.556863 }
define Color COrange		{ red 1		green 0.5	blue 0.0 }
define Color COrchid		{ red 0.858824	green 0.439216	blue 0.858824 }
define Color CPale		{ red 0.560784	green 0.737255	blue 0.560784 }
define Color CPink		{ red 0.737255	green 0.560784	blue 0.560784 }
define Color CPlum		{ red 0.917647	green 0.678431	blue 0.917647 }
define Color CSalmon		{ red 0.435294	green 0.258824	blue 0.258824 }
define Color CSea		{ red 0.137255	green 0.556863	blue 0.419608 }
define Color CSienna		{ red 0.556863	green 0.419608	blue 0.137255 }
define Color CSky		{ red 0.196078	green 0.6	blue 0.8 }
define Color CSteel		{ red 0.137255	green 0.419608	blue 0.556863 }
define Color CTan		{ red 0.858824	green 0.576471	blue 0.439216 }
define Color CThistle		{ red 0.847059	green 0.74902	blue 0.847059 }
define Color CTurquoise		{ red 0.678431	green 0.917647	blue 0.917647 }
define Color CWheat		{ red 0.847059	green 0.847059	blue 0.74902 }
define Color CSummerSky		{ red 0.22	green 0.69	blue 0.87 }
define Color CRich		{ red 0.35	green 0.35	blue 0.67 }
define Color CBrass		{ red 0.71	green 0.65	blue 0.26 }
define Color CCopper		{ red 0.72	green 0.45	blue 0.20 }
define Color CBronze		{ red 0.55	green 0.47	blue 0.14 }
define Color CBronze2		{ red 0.65	green 0.49	blue 0.24 }
define Color CSilver		{ red 0.90	green 0.91	blue 0.98 }
define Color CBrightGold	{ red 0.85	green 0.85	blue 0.10 }
define Color COldGold		{ red 0.81	green 0.71	blue 0.23 }
define Color CFeldspar		{ red 0.82	green 0.57	blue 0.46 }
define Color CQuartz		{ red 0.85	green 0.85	blue 0.95 }
define Color CMica : extends CBlack {}
define Color CNeonPink		{ red 1.00	green 0.43	blue 0.78 }
define Color CDarkPurple	{ red 0.53	green 0.12	blue 0.47 }
define Color CNeon		{ red 0.30	green 0.30	blue 1.00 }
define Color CCoolCopper	{ red 0.85	green 0.53	blue 0.10 }
define Color CMandarinOrange	{ red 0.89	green 0.47	blue 0.20 }
define Color CLightWood		{ red 0.91	green 0.76	blue 0.65 }
define Color CMediumWood	{ red 0.65	green 0.50	blue 0.39 }
define Color CDarkWood		{ red 0.52	green 0.37	blue 0.26 }
define Color CSpicyPink		{ red 1.00	green 0.11	blue 0.68 }
define Color CSemiSweetChoc	{ red 0.42	green 0.26	blue 0.15 }
define Color CBakersChoc	{ red 0.36	green 0.20	blue 0.09 }
define Color CFlesh		{ red 0.96	green 0.80	blue 0.69 }
define Color CNewTan		{ red 0.92	green 0.78	blue 0.62 }
define Color CNewMidnight	{ red 0.00	green 0.00	blue 0.61 }
define Color CVeryDarkBrown	{ red 0.35	green 0.16	blue 0.14 }
define Color CDarkBrown		{ red 0.36	green 0.25	blue 0.20 }
define Color CDarkTan		{ red 0.59	green 0.41	blue 0.31 }
define Color CDkCopper		{ red 0.29	green 0.46	blue 0.43 }
define Color CDustyRose		{ red 0.52	green 0.39	blue 0.39 }
define Color CHunters		{ red 0.13	green 0.37	blue 0.31 }
define Color CScarlet		{ red 0.55	green 0.09	blue 0.09 }

define Color CMed_Purple	{ red 0.73	green 0.16	blue 0.96 }
define Color CLight_Purple	{ red 0.87	green 0.58	blue 0.98 }
define Color CVery_Light_Purple	{ red 0.94	green 0.81	blue 0.99 }
*/
