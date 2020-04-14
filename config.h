/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/*
static const char *fonts[]          = { "Mononoki:style=Regular:size=12" };
static const char dmenufont[]       = "Mononoki:style=Regular:size=12";
*/

static const char *fonts[]          = { "IBM Plex Mono:style=Regular:size=12" };
//static const char *fonts[]          = { "ZX Spectrum 7:pixelsize=35:antialias=false:autohint=false" };

static const char dmenufont[]       = "IBM Plex Mono:style=Regular:size=12";

static const int gappx				= 15;

/*
static const char col_gray1[]       = "#2e3440";
static const char col_gray2[]       = "#4c566a";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#81a1c1";
*/

static const char col_gray[]   = "#2b2d37"; // background grey
static const char col_white[]   = "#e1eceb"; // foreground white
static const char col_pink[]   = "#FEB1BE"; // accent pink
static const char col_blue[]   = "#91BEBB"; // accent blue

static const char *colors[][4]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_gray, col_gray },
	[SchemeSel]  = { col_white, col_blue,  col_pink },
	[SchemeBar]  = { col_pink, col_gray,  col_pink },
};

/* tagging */

static const char *tags[] = { "", "", "", "", "", "", "", "", "" };
static const char *tagsalt[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      		instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     		NULL,       NULL,       0,            1,           -1 },
	{ "firefox",     	NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Pavucontrol",	NULL,       NULL,       1 << 7,       0,           -1 },
	{ "vlc",		 	NULL,       NULL,     	1 << 6,       0,           -1 },
	{ "discord",		NULL,       NULL,       1 << 2,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.6; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]",      tile },    /* first entry is default */
	{ "[]",      NULL },    /* no layout function means floating behavior */
	{ "[]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray, "-nf", col_white, "-sb", col_pink, "-sf", col_white, NULL };
static const char *utermcmd[]  = { "urxvt", NULL };
static const char *refbarcmd[]  = { "refbar", NULL };
static const char *stermcmd[]  = { "st", NULL };
static const char *discordcmd[]  = { "discord", NULL };
static const char *firefoxcmd[]  = { "firefox", NULL };
// static const char *tabbedsurfcmd[] = { "tabbed", "surf", "-pe", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = stermcmd } },
	{ MODKEY|ShiftMask,             XK_u,	   spawn,          {.v = utermcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	//{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	//{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_n,      togglealttag,   {0} },
	{ MODKEY|ShiftMask,             XK_r,	   spawn,         {.v = refbarcmd } },
	{ MODKEY,                       XK_zcaron,  setgaps,        {.i = -3 } },
	{ MODKEY,                       XK_dstroke, setgaps,        {.i = +3 } },
	{ MODKEY|ShiftMask,             XK_zcaron,  setgaps,        {.i = 0  } },
	{ MODKEY,	            		XK_scaron,  spawn,        	{.v = firefoxcmd } },
	{ MODKEY|ShiftMask,        		XK_d,  		spawn,        	{.v = discordcmd } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = utermcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
