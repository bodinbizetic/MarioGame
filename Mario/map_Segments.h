#ifndef map_segments_h
#define map_segments_h
#include "map.h"
#include "all.h"

/*!	\file map_Segments.h
*	\brief Contains designed map segments, start segment and finish segment
*/

/*!
*	\brief Number of map designed map segments
*/
#define MAP_SEGMENTS_PREDEFINED_NUMBER 24
static int map_Segment[MAP_SEGMENTS_PREDEFINED_NUMBER][MAP_HEIGHT][MAP_WIDTH] =

{
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,16,0,0,0,0,0,0,2,0,0},
	{0,0,0,0,0,6,0,0,0,0,14,0,2,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*0*/,
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,14,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,2,2,2,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,15,0},
	{0,0,0,16,0,0,0,0,0,0,16,0,0,0,0},
	{0,0,0,6,0,0,0,15,0,0,6,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*1*/,
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,2,2,2,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,2,2,3,2,2,0,0,0,2,2,2,2,2},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,15,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*2*/,
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,2,3,2,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,15,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2,2,2,2,2,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
	{0,0,16,0,0,0,0,0,0,0,0,0,2,2,2},
	{0,0,6,0,0,0,6,0,0,0,0,2,2,2,2},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*3*/,
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,4,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,6,0,15,0,6,0,15,0,6,0,0,2},
	{2,0,0,1,1,1,1,1,1,1,1,1,1,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,15,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*4*/,
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,16,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,1,6,0,1,1,0,0,0,0},
	{0,0,15,1,1,1,1,1,1,1,1,1,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*5*/,
	{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,1,0,0,0,0,0,6,0,0,0,0,0 },
	{ 0,0,0,1,1,1,4,1,1,1,1,2,2,1,0 },
	{ 0,0,0,0,1,0,0,0,0,0,0,0,0,1,0 },	
	{ 0,0,0,0,1,0,0,0,0,0,0,0,0,1,0 },
	{ 0,0,1,0,1,0,0,0,0,0,0,0,0,1,0 },
	{ 0,0,1,0,1,1,3,0,1,1,1,1,1,1,0 },
	{ 0,1,1,0,0,0,0,0,0,0,0,0,0,1,0 },
	{ 0,1,1,0,0,0,0,0,0,0,15,0,0,1,0 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	}/*6*/,
	{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,9,0,0,9,0,0,9,0,0,9,0,0,9,0 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	}/*7*/,
	{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,4,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0,1,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,1,1,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,9,9,9,9,9,9,9,9,9,9,9,9,9,0 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	}/*8*/,
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,16,0,0,0,0,16,0,0,0,0,0,0},
	{0,0,0,6,0,0,0,0,6,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,6,0,0,0,0,6,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,6,0,0,0,0,6,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,6,9,9,9,9,6,0,0,14,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*9*/,
	{
	{0,0,0,0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,3,0,0,2,0,0,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,1,4,0,0,0,1,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,1,0,3,0},
	{0,0,0,0,0,0,1,0,0,0,0,1,0,0,0},
	{0,0,0,9,14,0,1,0,15,0,0,1,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*10*/,
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,1,0,0,0,0,1,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,1,0,0},
	{0,0,1,0,16,0,0,0,0,0,0,0,1,0,0},
	{0,0,1,0,6,0,15,0,0,0,1,0,1,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,0,1,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,1,0,0},
	{0,0,1,0,1,1,4,1,1,1,1,1,1,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,1,0,0},
	{9,0,1,1,1,1,1,1,1,1,1,0,1,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*11*/,
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,1,0,0,1,1,0,0,0,1,1,1},
	{1,1,0,1,1,0,0,1,0,1,0,0,1,0,1},
	{1,0,1,0,1,0,0,1,1,0,0,0,1,0,1},
	{1,0,0,0,1,0,0,1,0,1,0,0,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,1,0,0,0,0},
	{0,0,0,0,1,0,1,0,0,0,1,0,0,0,0},
	{0,0,0,0,1,1,1,0,0,0,1,0,0,0,0},
	{0,0,0,0,1,0,1,0,0,0,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,16,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,6,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*12*/,
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,2,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,15,0,0,15,0,0,15,0,0,1,0,0},
	{0,0,1,9,9,9,9,9,9,9,9,9,1,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*13*/	,
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,3,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,2,2,2,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2,2,2,0,0,0,0,0},
	{0,0,2,2,2,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,14,0,0,0,0,15,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*14*/,
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,3,2,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,1,0,0,0,0,0,0,1,0,0,0,0},
	{0,0,0,0,1,0,16,0,0,1,0,0,0,0,0},
	{0,0,0,0,1,1,6,0,1,1,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*15*/,
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0},
	{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0},
	{0,1,0,0,0,0,1,0,0,0,0,0,1,0,0},
	{0,1,1,0,0,0,1,0,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,1,0,0,1,1,1,0,0,0,0,0},
	{0,0,1,0,1,0,0,1,0,0,0,0,0,0,0},
	{0,0,1,0,1,0,0,1,0,1,0,0,0,0,0},
	{0,0,1,1,1,0,0,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*16*/,
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,2,2,2,2,2,2,2,0,0},
	{0,0,0,0,0,2,0,0,0,0,0,0,2,0,0},
	{0,0,0,0,2,0,0,0,0,0,0,0,2,0,0},
	{0,0,0,2,0,0,0,0,0,0,0,0,2,0,0},
	{0,0,2,1,1,1,1,3,1,1,0,0,1,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,1,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,1,0,0},
	{0,0,1,0,15,0,0,0,0,0,0,0,1,0,0},
	{0,3,1,1,1,1,1,1,1,2,2,1,1,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,14,0,0,0,0,0,1,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*17*/,
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,16,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,6,0,0,0,0,0},
	{0,0,0,0,0,0,0,16,0,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,6,0,1,1,0,0,0,0},
	{0,0,0,0,0,16,0,1,1,1,1,16,0,0,0},
	{0,0,0,0,0,6,0,1,1,1,1,6,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*18*/,
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
	{0,0,1,0,0,1,0,0,1,0,0,0,0,0,0},
	{0,0,1,0,0,1,0,0,1,0,0,0,0,0,0},
	{0,0,1,0,0,1,0,0,1,0,0,0,0,0,0},
	{0,0,1,9,9,1,9,9,1,0,0,15,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*19*/,
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,2,0,0,2,0,0,0,0,0},
	{0,0,0,0,0,2,0,0,0,0,2,0,0,0,0},
	{0,0,0,15,2,0,0,0,0,0,0,2,0,0,0},
	{0,0,0,2,0,0,0,0,0,0,0,0,2,0,0},
	{0,0,2,9,9,9,9,9,9,9,9,9,9,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*20*/,
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,2,2,3,2,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,9,9,15,0,9,9,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*21*/,
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,2,0,15,0,0,0,0,2,0,0,0,0,0,0},
	{0,2,1,2,2,2,2,1,2,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,1,1,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,1,0,0,3,1,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,14,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*22*/,
	{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,1,9,9,9,9,9,0,9,9,9,9,9,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}/*23*/

};

/*!
*	\brief Starting Segment
*/
static int map_Start_Segment[MAP_HEIGHT][MAP_WIDTH] = 
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

/*!	
*	\brief Last segment
*/
static int map_Finish_Segment[MAP_HEIGHT][MAP_WIDTH] =
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,1,1,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,1,1,0,0,0,0,7,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

#endif