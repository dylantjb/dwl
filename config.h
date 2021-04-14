/* appearance */
static const int sloppyfocus        = 1;  /* focus follows mouse */
static const unsigned int borderpx  = 1;  /* border pixel of windows */
static const unsigned int gappih    = 6;  /* horiz inner gap between windows */
static const unsigned int gappiv    = 6;  /* vert inner gap between windows */
static const unsigned int gappoh    = 6;  /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 6;  /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;  /* 1 means no outer gap when there is only one window */
static const float rootcolor[]      = {0.3, 0.3, 0.3, 1.0};
static const float bordercolor[]    = {0.5, 0.5, 0.5, 1.0};
static const float focuscolor[]     = {0.3, 0.5, 0.8, 1.0};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* app_id     title       tags mask     isfloating   monitor */
	/* examples:
	{ "Gimp",     NULL,       0,            1,           -1 },
	{ "firefox",  NULL,       1 << 8,       0,           -1 },
	*/
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors
 * The order in which monitors are defined determines their position.
 * Non-configured monitors are always added to the left. */
static const MonitorRule monrules[] = {
	/* name       mfact nmaster scale layout       rotate/reflect x y */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, 0, 0 },
	*/
	/* defaults */
	{ NULL,       0.55, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, 0, 0 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
    .options = "caps:swapescape,altwin:swap_alt_win",
    .layout  = "gb"
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 1;
static const int natural_scrolling = 0;

#define MODKEY WLR_MODIFIER_LOGO
#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                                      KEY,                  view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,                    KEY,                  toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT,                   SKEY,                 tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT, SKEY,                 toggletag,       {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* helper for changing virtual terminals */
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }

/* commands */
static const char *termcmd[] = { "/bin/sh", "-c", "$TERMINAL", NULL };
static const char *menucmd[] = { "/bin/sh", "-c", "j4-dmenu-desktop --term=$TERMINAL --dmenu=\"bemenu -i -b -n -p '> ' --fn 'Hack Nerd Font 10' --tf '#3b84c0' --hf '#3b84c0' --nb '#1e2127' --nf '#abb2bf' --sf '#61afef' --sb '#5c6370'\"", NULL };

/* define extra keys */
#define Print 0x0000ff61

#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                       function          argument */

    /* Base keybindings */
	{ MODKEY,                    XKB_KEY_d,                spawn,            {.v = menucmd} },            
	{ MODKEY,                    XKB_KEY_Return,           spawn,            {.v = termcmd} },
	{ MODKEY,                    XKB_KEY_j,                focusstack,       {.i = +1} },
	{ MODKEY,                    XKB_KEY_k,                focusstack,       {.i = -1} },
	{ MODKEY,                    XKB_KEY_i,                incnmaster,       {.i = +1} },
	{ MODKEY,                    XKB_KEY_p,                incnmaster,       {.i = -1} },
	{ MODKEY,                    XKB_KEY_h,                setmfact,         {.f = -0.05} },
	{ MODKEY,                    XKB_KEY_l,                setmfact,         {.f = +0.05} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Return,           zoom,             {0} },
	{ MODKEY,                    XKB_KEY_Tab,              view,             {0} },
	{ MODKEY,                    XKB_KEY_q,                killclient,       {0} },
	{ MODKEY,                    XKB_KEY_z,                setlayout,        {.v = &layouts[0]} },
	{ MODKEY,                    XKB_KEY_f,                setlayout,        {.v = &layouts[1]} },
	{ MODKEY,                    XKB_KEY_m,                setlayout,        {.v = &layouts[2]} },
	{ MODKEY,                    XKB_KEY_space,            setlayout,        {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_space,            togglefloating,   {0} },
	{ MODKEY, 					 XKB_KEY_e,    	           togglefullscreen, {0} },
	{ MODKEY,                    XKB_KEY_0,                view,             {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright,       tag,              {.ui = ~0} },
	{ MODKEY,                    XKB_KEY_comma,            focusmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    XKB_KEY_period,           focusmon,         {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_less,             tagmon,           {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_greater,          tagmon,           {.i = WLR_DIRECTION_RIGHT} },

    /* Custom keybindings */
    { MODKEY,			         XKB_KEY_Escape,           spawn,		     SHCMD("mylock") },
    { MODKEY,			         XKB_KEY_BackSpace,        spawn,		     SHCMD("skippy-wl") },
    { MODKEY,			         XKB_KEY_r,                spawn,		     SHCMD("kitty -e ranger") },
    { MODKEY,			         XKB_KEY_w,                spawn,		     SHCMD("$BROWSER") },
    { MODKEY,			         XKB_KEY_n,                spawn,		     SHCMD("networkmanager_bemenu") },
    { MODKEY,			         XKB_KEY_b,                spawn,		     SHCMD("bemenu-bluetooth") },
    { MODKEY,			         XKB_KEY_t,                spawn,		     SHCMD("$TERMINAL -e btm") },

    /* Function keys */
    { 0,                         XF86XK_AudioRaiseVolume,  spawn,		     SHCMD("volume up") },
    { 0,                         XF86XK_AudioLowerVolume,  spawn,		     SHCMD("volume down") },
    { 0,                         XF86XK_AudioMute,         spawn,		     SHCMD("volume mute") },
    { 0|WLR_MODIFIER_SHIFT,      XF86XK_AudioRaiseVolume,  spawn,		     SHCMD("microphone up") },
    { 0|WLR_MODIFIER_SHIFT,      XF86XK_AudioLowerVolume,  spawn,		     SHCMD("microphone down") },
    { 0|WLR_MODIFIER_SHIFT,      XF86XK_AudioMicMute,      spawn,		     SHCMD("microphone mute") },
    { 0,                         XF86XK_AudioPlay,         spawn,		     SHCMD("playerctl play-pause") },
    { 0,                         XF86XK_AudioStop,         spawn,		     SHCMD("playerctl stop") },
    { 0,                         XF86XK_AudioPrev,         spawn,		     SHCMD("playerctl previous") },
    { 0,                         XF86XK_AudioNext,         spawn,		     SHCMD("playerctl next") },
    { 0,                         XF86XK_MonBrightnessUp,   spawn,		     SHCMD("backlight up") },
    { 0,                         XF86XK_MonBrightnessDown, spawn,		     SHCMD("backlight down") },
    { 0,			             Print,                    spawn,		     SHCMD("grimshot save area") },
    { 0|WLR_MODIFIER_SHIFT,      Print,                    spawn,		     SHCMD("grimshot save screen") },

    /* Exit dwl */
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Q,                spawn,            SHCMD("rofi -show p -modi p:rofi-power-menu -width 20 -lines 5") },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_R,                quit,             {0} },

    /* Tags */
	TAGKEYS(  XKB_KEY_1,         XKB_KEY_exclam,                  0),
	TAGKEYS(  XKB_KEY_2,         XKB_KEY_at,                      1),
	TAGKEYS(  XKB_KEY_3,         XKB_KEY_numbersign,              2),
	TAGKEYS(  XKB_KEY_4,         XKB_KEY_dollar,                  3),
	TAGKEYS(  XKB_KEY_5,         XKB_KEY_percent,                 4),
	TAGKEYS(  XKB_KEY_6,         XKB_KEY_caret,                   5),
	TAGKEYS(  XKB_KEY_7,         XKB_KEY_ampersand,               6),
	TAGKEYS(  XKB_KEY_8,         XKB_KEY_asterisk,                7),
	TAGKEYS(  XKB_KEY_9,         XKB_KEY_parenleft,               8),

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit,     {0} },
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
