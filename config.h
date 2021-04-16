/* constants */
#define TERMINAL "kitty"
/* #define TERMCLASS "Kitty" */
#define MODKEY  WLR_MODIFIER_LOGO
#define ALTKEY  WLR_MODIFIER_ALT
#define CTRLKEY WLR_MODIFIER_CTRL
#define SHIFT   WLR_MODIFIER_SHIFT

/* appearance */
static const int sloppyfocus        = 1;
static const unsigned int borderpx  = 1;
static const unsigned int gappih    = 6;
static const unsigned int gappiv    = 6;
static const unsigned int gappoh    = 6;
static const unsigned int gappov    = 6;
static const int smartgaps          = 0;
static const float rootcolor[]      = {0.3, 0.3, 0.3, 1.0};
static const float bordercolor[]    = {0.5, 0.5, 0.5, 1.0};
static const float focuscolor[]     = {0.3, 0.5, 0.8, 1.0};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
	/* app_id     title       tags mask     isfloating   monitor */
    /* TODO: Find out how to use this */
    /* { "telegramdesktop", NULL, 8, 0, -1 }, */
    /* { "discord",         NULL, 8, 0, -1 }, */
    /* { "Spotify",         NULL, 9, 0, -1 }, */
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol   arrange function */
	{  "[]=",   tile },
	{  "><>",   NULL },    /* no layout function means floating behavior */
	{  "[M]",   monocle },
};

/* monitors */
static const MonitorRule monrules[] = {
	/* name    mfact nmaster scale layout       rotate/reflect x y */
	{ "eDP-1", 0.55, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, 0, 0 },
};

/* keyboard */
static const int repeat_rate = 25;
static const int repeat_delay = 600;
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
    .options = "caps:swapescape,altwin:swap_alt_win",
    .layout  = "gb"
};

/* trackpad */
static const int tap_to_click = 1;
static const int natural_scrolling = 0;

/* mouse commands */
static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};

/* tag commands */
#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,               KEY,      view,            {.ui = 1 << TAG} }, \
	{ MODKEY|CTRLKEY,       KEY,      toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|SHIFT,         SKEY,     tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|CTRLKEY|SHIFT, SKEY,     toggletag,       {.ui = 1 << TAG} }

/* helper for changing virtual terminals */
#define CHVT(n) { CTRLKEY|ALTKEY,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }

/* define extra key(s) */
#define Print 0x0000ff61

/* commands */
static const char *termcmd[] = { TERMINAL, NULL };
static const char *menucmd[] = { "/bin/sh", "-c", "j4-dmenu-desktop --term=" TERMINAL " --dmenu=\"bemenu -i -b -n -p '> ' "
                                                  "--fn 'Hack Nerd Font 10' --tf '#3b84c0' --hf '#3b84c0' --nb '#1e2127' "
                                                  "--nf '#abb2bf' --sf '#61afef' --sb '#5c6370'\"", NULL};

static const char *networkcmd[] =   { "networkmanager_bemenu", NULL };
static const char *bluetoothcmd[] = { "bemenu-bluetooth", NULL };
static const char *browsercmd[] =   {"qutebrowser", NULL };
static const char *lockcmd[] =      { "mylock", NULL };
static const char *powercmd[] =     { "rofi", "-show", "p", "-modi", "p:rofi-power-menu", "-width", "20", "-lines", "5", NULL };

static const char *ranger[] = { TERMINAL, "-e", "ranger", NULL};
static const char *bottom[] = { TERMINAL, "-e", "btm", NULL};

static const char *volup[] =       { "volume", "up", NULL };
static const char *voldown[] =     { "volume", "down", NULL };
static const char *volmute[] =     { "volume", "mute", NULL };
static const char *micup[] =       { "microphone", "up", NULL };
static const char *micdown[] =     { "microphone", "down", NULL };
static const char *micmute[] =     { "microphone", "mute", NULL };
static const char *playtoggle[] =  { "playerctl", "play-pause", NULL };
static const char *playstop[] =    { "playerctl", "stop", NULL };
static const char *playprev[] =    { "playerctl", "previous", NULL };
static const char *playnext[] =    { "playerctl", "next", NULL };
static const char *lightup[] =     { "backlight", "up", NULL };
static const char *lightdown[] =   { "backlight", "down", NULL };
static const char *printarea[] =   { "grimshot", "save", "area", NULL };
static const char *printscreen[] = { "grimshot", "save", "screen", NULL };

#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                       function          argument */

    /* Base keybindings */
	{ MODKEY,                XKB_KEY_d,                spawn,            {.v = menucmd} },
	{ MODKEY,                XKB_KEY_Return,           spawn,            {.v = termcmd} },
	{ MODKEY,                XKB_KEY_j,                focusstack,       {.i = +1} },
	{ MODKEY,                XKB_KEY_k,                focusstack,       {.i = -1} },
	{ MODKEY,                XKB_KEY_i,                incnmaster,       {.i = +1} },
	{ MODKEY,                XKB_KEY_p,                incnmaster,       {.i = -1} },
    { MODKEY|ALTKEY,         XKB_KEY_h,                incrgaps,         {.i = +1 } },
	{ MODKEY|ALTKEY,         XKB_KEY_l,                incrgaps,         {.i = -1 } },
	{ MODKEY|ALTKEY|SHIFT,   XKB_KEY_H,                incrogaps,        {.i = +1 } },
	{ MODKEY|ALTKEY|SHIFT,   XKB_KEY_L,                incrogaps,        {.i = -1 } },
	{ MODKEY|ALTKEY|CTRLKEY, XKB_KEY_h,                incrigaps,        {.i = +1 } },
	{ MODKEY|ALTKEY|CTRLKEY, XKB_KEY_l,                incrigaps,        {.i = -1 } },
	{ MODKEY|ALTKEY,         XKB_KEY_0,                togglegaps,       {0} },
	{ MODKEY|ALTKEY|SHIFT,   XKB_KEY_parenright,       defaultgaps,      {0} },
	{ MODKEY,                XKB_KEY_y,                incrihgaps,       {.i = +1 } },
	{ MODKEY,                XKB_KEY_o,                incrihgaps,       {.i = -1 } },
	{ MODKEY|CTRLKEY,        XKB_KEY_y,                incrivgaps,       {.i = +1 } },
	{ MODKEY|CTRLKEY,        XKB_KEY_o,                incrivgaps,       {.i = -1 } },
	{ MODKEY|ALTKEY,         XKB_KEY_y,                incrohgaps,       {.i = +1 } },
	{ MODKEY|ALTKEY,         XKB_KEY_o,                incrohgaps,       {.i = -1 } },
	{ MODKEY|SHIFT,          XKB_KEY_Y,                incrovgaps,       {.i = +1 } },
	{ MODKEY|SHIFT,          XKB_KEY_O,                incrovgaps,       {.i = -1 } },
	{ MODKEY,                XKB_KEY_h,                setmfact,         {.f = -0.05} },
	{ MODKEY,                XKB_KEY_l,                setmfact,         {.f = +0.05} },
	{ MODKEY|SHIFT,          XKB_KEY_Return,           zoom,             {0} },
	{ MODKEY,                XKB_KEY_Tab,              view,             {0} },
	{ MODKEY,                XKB_KEY_q,                killclient,       {0} },
	{ MODKEY,                XKB_KEY_z,                setlayout,        {.v = &layouts[0]} },
	{ MODKEY,                XKB_KEY_f,                setlayout,        {.v = &layouts[1]} },
	{ MODKEY,                XKB_KEY_m,                setlayout,        {.v = &layouts[2]} },
	{ MODKEY,                XKB_KEY_space,            setlayout,        {0} },
	{ MODKEY|SHIFT,          XKB_KEY_space,            togglefloating,   {0} },
	{ MODKEY, 				 XKB_KEY_e,    	           togglefullscreen, {0} },
	{ MODKEY,                XKB_KEY_0,                view,             {.ui = ~0} },
	{ MODKEY|SHIFT,          XKB_KEY_parenright,       tag,              {.ui = ~0} },
	{ MODKEY,                XKB_KEY_comma,            focusmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                XKB_KEY_period,           focusmon,         {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|SHIFT,          XKB_KEY_less,             tagmon,           {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|SHIFT,          XKB_KEY_greater,          tagmon,           {.i = WLR_DIRECTION_RIGHT} },

    /* Custom keybindings */
    { MODKEY,			     XKB_KEY_r,                spawn,		     {.v = ranger} },
    { MODKEY,			     XKB_KEY_t,                spawn,		     {.v = bottom} },
    { MODKEY,			     XKB_KEY_w,                spawn,		     {.v = browsercmd} },
    { MODKEY,			     XKB_KEY_n,                spawn,		     {.v = networkcmd} },
    { MODKEY,			     XKB_KEY_b,                spawn,		     {.v = bluetoothcmd} },
    /* Wait for dwl to support screen locking */
    { MODKEY,			     XKB_KEY_Escape,           spawn,		     {.v = lockcmd} },

    /* Function keys */
    { 0,                     XF86XK_AudioRaiseVolume,  spawn,		     {.v = volup} },
    { 0,                     XF86XK_AudioLowerVolume,  spawn,		     {.v = voldown} },
    { 0,                     XF86XK_AudioMute,         spawn,		     {.v = volmute} },
    { 0|SHIFT,               XF86XK_AudioRaiseVolume,  spawn,		     {.v = micup} },
    { 0|SHIFT,               XF86XK_AudioLowerVolume,  spawn,		     {.v = micdown} },
    { 0|SHIFT,               XF86XK_AudioMicMute,      spawn,		     {.v = micmute} },
    { 0,                     XF86XK_AudioPlay,         spawn,		     {.v = playtoggle} },
    { 0,                     XF86XK_AudioStop,         spawn,		     {.v = playstop} },
    { 0,                     XF86XK_AudioPrev,         spawn,		     {.v = playprev} },
    { 0,                     XF86XK_AudioNext,         spawn,		     {.v = playnext} },
    { 0,                     XF86XK_MonBrightnessUp,   spawn,		     {.v = lightup} },
    { 0,                     XF86XK_MonBrightnessDown, spawn,		     {.v = lightdown} },
    { 0,			         Print,                    spawn,		     {.v = printarea} },
    { 0|SHIFT,               Print,                    spawn,		     {.v = printscreen} },

    /* Exit dwl */
	{ CTRLKEY|ALTKEY,        XKB_KEY_Terminate_Server, quit,             {0} },
	{ MODKEY|SHIFT,          XKB_KEY_Delete,           quit,             {0} },
	{ MODKEY|SHIFT,          XKB_KEY_Q,                spawn,            {.v = powercmd} },

    /* Tags */
	TAGKEYS(  XKB_KEY_1,     XKB_KEY_exclam,                             0),
	TAGKEYS(  XKB_KEY_2,     XKB_KEY_quotedbl,                           1),
	TAGKEYS(  XKB_KEY_3,     XKB_KEY_sterling,                           2),
	TAGKEYS(  XKB_KEY_4,     XKB_KEY_dollar,                             3),
    TAGKEYS(  XKB_KEY_5,     XKB_KEY_percent,                            4),
	TAGKEYS(  XKB_KEY_6,     XKB_KEY_asciicircum,                        5),
	TAGKEYS(  XKB_KEY_7,     XKB_KEY_ampersand,                          6),
	TAGKEYS(  XKB_KEY_8,     XKB_KEY_asterisk,                           7),
	TAGKEYS(  XKB_KEY_9,     XKB_KEY_parenleft,                          8),

	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};


