#define CLASS    "PMenu"
#define TTPAD    4              /* padding for the tooltip */
#define TTVERT   30             /* vertical distance from mouse to place tooltip */

/* macros */
#define LEN(x)              (sizeof (x) / sizeof (x[0]))
#define MAX(x,y)            ((x)>(y)?(x):(y))
#define MIN(x,y)            ((x)<(y)?(x):(y))
#define BETWEEN(x, a, b)    ((a) <= (x) && (x) <= (b))

/* color enum */
enum {ColorFG, ColorBG, ColorLast};

/* state of command to popen */
enum {NO_CMD = 0, CMD_NOTRUN = 1, CMD_RUN = 2};

/* atoms */
enum {
	NET_WM_WINDOW_TYPE,
	NET_WM_WINDOW_TYPE_TOOLTIP,
	NET_WM_WINDOW_TYPE_POPUP_MENU,
	ATOM_LAST
};

/* configuration structure */
struct Config {
	const char *font;
	const char *background_color;
	const char *foreground_color;
	const char *selbackground_color;
	const char *selforeground_color;
	const char *separator_color;
	const char *border_color;
	int border_pixels;
	int separator_pixels;
	int triangle_width;
	int triangle_height;
	int triangle_distance;
	unsigned diameter_pixels;
	double separatorbeg;
	double separatorend;
};

/* draw context structure */
struct DC {
	XftColor normal[ColorLast];     /* color of unselected slice */
	XftColor selected[ColorLast];   /* color of selected slice */
	XftColor border;                /* color of border */
	XftColor separator;             /* color of the separator */

	GC gc;                          /* graphics context */

	FcPattern *pattern;
	XftFont **fonts;
	size_t nfonts;
	int fonth;

	XRenderPictureAttributes pictattr;
};

/* pie slice structure */
struct Slice {
	struct Slice *prev, *next;
	struct Menu *submenu;   /* submenu spawned by clicking on slice */
	struct Menu *parent;

	char *label;            /* string to be drawed on the slice */
	char *output;           /* string to be outputed when slice is clicked */
	char *file;             /* filename of the icon */
	size_t labellen;        /* strlen(label) */
	int iscmd;              /* whether output is actually a command to popen */

	unsigned slicen;
	int x, y;               /* position of the pointer of the slice */
	int labelx, labely;     /* position of the label */
	int iconx, icony;       /* position of the icon */
	double anglea, angleb;  /* angle of the borders of the slice */

	int drawn;              /* whether the pixmap have been drawn */
	Drawable pixmap;        /* pixmap containing the pie menu with the slice selected */
	Picture picture;        /* XRender picture */
	Imlib_Image icon;       /* icon */

	int ttdrawn;            /* whether the pixmap for the tooltip have been drawn */
	int ttw;                /* tooltip width */
	Window tooltip;         /* tooltip that appears when hovering a slice */
	Drawable ttpix;         /* pixmap for the tooltip */
};

/* menu structure */
struct Menu {
	struct Menu *parent;    /* parent menu */
	struct Slice *caller;   /* slice that spawned the menu */
	struct Slice *list;     /* list of slices contained by the pie menu */
	struct Slice *selected; /* slice currently selected in the menu */
	unsigned nslices;       /* number of slices */
	int x, y;               /* menu position */
	double half;            /* angle of half a slice of the pie menu */
	int level;              /* menu level relative to root */

	int drawn;              /* whether the pixmap have been drawn */
	Drawable pixmap;        /* pixmap to draw the menu on */
	Picture picture;        /* XRender picture */
	Window win;             /* menu window to map on the screen */
};

/* monitor and cursor geometry structure */
struct Monitor {
	int x, y, w, h;         /* monitor geometry */
	int cursx, cursy;
};

/* geometry of the pie and bitmap that shapes it */
struct Pie {
	GC gc;              /* graphic context of the bitmaps */
	Drawable clip;      /* bitmap shaping the clip region (without borders) */
	Drawable bounding;  /* bitmap shaping the bounding region (with borders)*/

	int fulldiameter;   /* diameter of the pie + 2*border*/
	int diameter;       /* diameter of the pie */
	int radius;         /* radius of the pie */
	int border;         /* border of the pie */
	int tooltiph;

	int triangleinner;
	int triangleouter;
	int separatorbeg;
	int separatorend;
	double triangleangle;
	double innerangle;
	double outerangle;

	Picture bg;
	Picture fg;
	Picture selbg;
	Picture selfg;
	Picture separator;
};
