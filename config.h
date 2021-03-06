/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 10;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 5;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 0;     /* 0 means no systray */
static const unsigned int gappx     = 70;        /* gaps between windows */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *fonts[]          = { "IBM Plex Sans Cond SmBld:size=13" };
static const char dmenufont[]       = "Inconsolata Nerd Font:size=25";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#424242";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#a89983";
static const char *colors[][3]      = {
  /*               fg         bg         border   */
  [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
  [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "" };

#include "nextprevtag.c"

static const Rule rules[] = {
  /* xprop(1):
   *	WM_CLASS(STRING) = instance, class
   *	WM_NAME(STRING) = title
    https://dwm.suckless.org/customisation/tagmask/
   */
  /* class      instance    title       tags mask     iscentered   isfloating   monitor */
  { "Gimp",     NULL,       NULL,       0,            0,           1,           -1 },
  { "firefox",  NULL,       NULL,       1 << 2,       0,           0,           -1 },
  { "Brave",  NULL,       NULL,         1 << 2,       0,           0,           -1 },
  { "Slack",  NULL,       NULL,         1 << 3,       0,           0,           -1 },
  { "discord",  NULL,       NULL,       1 << 3,       0,           0,           -1 },
  { "chrome",  NULL,       NULL,        1 << 1,       0,           0,           -1 },
  { "Peek",     NULL,       NULL,       0,            1,           1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
  /* symbol     arrange function */
  { "ﱖ  ",      tile },    /* first entry is default */
  { "﯑ ",      NULL },    /* no layout function means floating behavior */
  { " ",   monocle },
  { "﬷    ",      deck },
  { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod3Mask
#define TAGKEYS(KEY,TAG) \
  { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-l", "7", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL};
static const char *termcmd[]  = { "kitty", NULL };

static Key keys[] = {
  /* modifier                     key        function        argument */
  { ControlMask,                  XK_space,  spawn,          {.v = dmenucmd } },
  { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
  { MODKEY,                       XK_b,      togglebar,      {0} },
  { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
  { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
  { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
  { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
  { MODKEY,                       XK_x,      view_adjacent,  {.i = +1 } },
  { MODKEY,                       XK_z,      view_adjacent,  {.i = -1 } },
  { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
  { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
  { MODKEY,                       XK_Return, zoom,           {0} },
  { MODKEY,                       XK_Tab,    view,           {0} },
  { ControlMask,                  XK_q,      killclient,     {0} },
  { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
  { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
  { MODKEY,                       XK_p,      setlayout,      {.v = &layouts[2]} },
  { MODKEY,                       XK_space,  setlayout,      {0} },
  { MODKEY,                       XK_y,      setlayout,      {.v = &layouts[3]} },
  { MODKEY,                       XK_bracketleft,  cyclelayout,    {.i = -1 } },
  { MODKEY,                       XK_bracketright, cyclelayout,    {.i = +1 } },
  { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
  // { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
  // { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
  { MODKEY,                       XK_e,  focusmon,           {.i = -1 } },
  { MODKEY,                       XK_r, focusmon,            {.i = +1 } },
  { MODKEY|ShiftMask,             XK_e,  tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,             XK_r, tagmon,         {.i = +1 } },
  { MODKEY|ShiftMask,             XK_n,  setgaps,        {.i = -2 } },
  { MODKEY|ShiftMask,             XK_m,  setgaps,        {.i = +2 } },
  TAGKEYS(                        XK_1,                      0)
  TAGKEYS(                        XK_2,                      1)
  TAGKEYS(                        XK_3,                      2)
  TAGKEYS(                        XK_4,                      3)
  TAGKEYS(                        XK_5,                      4)
  TAGKEYS(                        XK_6,                      5)
  TAGKEYS(                        XK_7,                      6)
  TAGKEYS(                        XK_8,                      7)
  { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  spawn,               1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};

