// TODO-HACKATHON 3-9: Create scene_settings.h and scene_settings.c.
// No need to do anything for this part. We've already done it for
// you, so this 2 files is like the default scene template.
#include "scene_settings.h"

// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.

/* Define your static vars / function prototypes below. */
bool chart;
// TODO-IF: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.static Button Mute;
static Button Mute;
static Button BGM;
static Button Original;
static Button Relax;
static Button Human;
static Button Pacc;
static void init() {
	Mute = button_create(140, 140, 50, 50, "Assets/checkbox_unchecked.png", "Assets/checkbox_checked.png");
	BGM = button_create(140, 250, 200, 50, "Assets/select_bgm.png", "Assets/select_bgm.png");
	Original = button_create(140, 300, 200, 50, "Assets/orignal_unhovered.png", "Assets/orignal_hovered.png");
	Relax = button_create(140, 350, 200, 50, "Assets/relax_unhovered.png", "Assets/relax_hovered.png");
	Human = button_create(450, 300, 50, 50, "Assets/human.png", "Assets/human.png");
	Pacc = button_create(550, 300, 50, 50, "Assets/pacc.png", "Assets/pacc.png");
}

static void draw(void){
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W/2,
		SCREEN_H - 150,
		ALLEGRO_ALIGN_CENTER,
		"<ENTER> Back to menu"
	);	
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		550,
		250,
		ALLEGRO_ALIGN_CENTER,
		"Choose Character"
	);
	al_draw_text(
		menuFont,
		al_map_rgb(255, 255, 255),
		250,
		155,
		ALLEGRO_ALIGN_CENTER,
		"Mute"
	);
	drawButton1(Mute);
	drawButton(Human);
	drawButton(Pacc);
	drawButton(BGM);
	if (BGM.clicked) {
		drawButton(Original);
		drawButton(Relax);
	}
}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
	//	TODO-HACKATHON 3-7: Update button's status(hovered), and utilize the function `pnt_in_rect`, which you just implemented
	//	Uncomment and fill the code below
	Mute.hovered = pnt_in_rect(mouse_x, mouse_y, Mute.body);
	BGM.hovered = pnt_in_rect(mouse_x, mouse_y, BGM.body);
	Original.hovered = pnt_in_rect(mouse_x, mouse_y, Original.body);
	Relax.hovered = pnt_in_rect(mouse_x, mouse_y, Relax.body);
	Human.hovered = pnt_in_rect(mouse_x, mouse_y, Human.body);
	Pacc.hovered = pnt_in_rect(mouse_x, mouse_y, Pacc.body);
}


static void on_mouse_down() {
	int ch;
	if (Mute.hovered) {
		if (effect_volume == 0) Mute.clicked = true;
		else Mute.clicked = false;
		if (!Mute.clicked) {
			Mute.clicked = true;
			game_log("TRUE");
			music_volume = 0;
			effect_volume = 0;
		}
		else {
			Mute.clicked = false;
			game_log("FALSE");
			music_volume = 0.5;
			effect_volume = 0.5;
		}
	}
	else if (BGM.hovered)
	{
		if (!BGM.clicked) {
			game_log("BGM_success");
			BGM.clicked = true;
		}
		else BGM.clicked = false;
	}
	else if (Original.hovered)
		themeMusic = load_audio("Assets/Music/original_theme.ogg");
	else if (Relax.hovered)
		themeMusic = load_audio("Assets/Music/Relax-Main-version_Royalty Free Music By 500Audio from httpszh.500audio.comfree-music.ogg");
	else if (Human.hovered) {
		game_log("Human_success");
		chart = false;
	}
	else if (Pacc.hovered) {
			game_log("Pacc_success");
			chart = true;
	}
	
}

static void destroy() {

	al_destroy_bitmap(Mute.default_img);
	al_destroy_bitmap(Mute.hovered_img);
	al_destroy_bitmap(BGM.default_img);
	al_destroy_bitmap(BGM.hovered_img);
	al_destroy_bitmap(Original.default_img);
	al_destroy_bitmap(Original.hovered_img);
	al_destroy_bitmap(Relax.default_img);
	al_destroy_bitmap(Relax.hovered_img);
	al_destroy_bitmap(Human.default_img);
	al_destroy_bitmap(Human.hovered_img);
	al_destroy_bitmap(Pacc.default_img);
	al_destroy_bitmap(Pacc.hovered_img);
}

static void on_key_down(int keycode) {
	switch (keycode) {
		case ALLEGRO_KEY_ENTER:
			game_change_scene(scene_menu_create());
			break;
		default:
			break;
	}
}

// The only function that is shared across files.
Scene scene_settings_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Settings";
	scene.draw = &draw;
	scene.on_key_down = &on_key_down;
	scene.initialize = &init;
	scene.destroy = &destroy;
	scene.on_mouse_down = &on_mouse_down;
	scene.on_mouse_move = &on_mouse_move;
	// TODO-IF: Register more event callback functions such as keyboard, mouse, ...
	game_log("Settings scene created");
	return scene;
}

// TODO-Graphical_Widget:
// Just suggestions, you can create your own usage.
	// Selecting BGM:
	// 1. Declare global variables for storing the BGM. (see `shared.h`, `shared.c`)
	// 2. Load the BGM in `shared.c`.
	// 3. Create dropdown menu for selecting BGM in setting scene, involving `scene_settings.c` and `scene_setting.h.
	// 4. Switch and play the BGM if the corresponding option is selected.

	// Adjusting Volume:
	// 1. Declare global variables for storing the volume. (see `shared.h`, `shared.c`)
	// 2. Create a slider for adjusting volume in setting scene, involving `scene_settings.c` and `scene_setting.h.
		// 2.1. You may use checkbox to switch between mute and unmute.


	// 3. Adjust the volume and play when the button is pressed.

	// Selecting Map:
	// 1. Preload the map to `shared.c`.
	// 2. Create buttons(or dropdown menu) for selecting map in setting scene, involving `scene_settings.c` and `scene_setting.h.
		// 2.1. For player experience, you may also create another scene between menu scene and game scene for selecting map.
	// 3. Create buttons(or dropdown menu) for selecting map in setting scene, involving `scene_settings.c` and `scene_setting.h.
	// 4. Switch and draw the map if the corresponding option is selected.
		// 4.1. Suggestions: You may use `al_draw_bitmap` to draw the map for previewing. 
							// But the map is too large to be drawn in original size. 
							// You might want to modify the function to allow scaling.