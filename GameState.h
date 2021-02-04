#pragma once
#include "Misc.h"
#include "Circuit.h"
#include "Level.h"
#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include <list>

class GameState
{
    SDL_Window* sdl_window;
    SDL_Renderer* sdl_renderer;
    SDL_Texture* sdl_texture;
    SDL_Texture* sdl_tutorial_texture;
    SDL_Texture* sdl_levels_texture;

    Rand rand = 3;
    enum MouseState
    {
        MOUSE_STATE_NONE,
        MOUSE_STATE_PIPE,
        MOUSE_STATE_DELETING,
        MOUSE_STATE_PLACING_VALVE,
        MOUSE_STATE_PLACING_SOURCE,
        MOUSE_STATE_PLACING_SUBCIRCUIT,
        MOUSE_STATE_SPEED_SLIDER,
    } mouse_state = MOUSE_STATE_NONE;

    enum PanelState
    {
        PANEL_STATE_LEVEL_SELECT,
        PANEL_STATE_EDITOR,
        PANEL_STATE_MONITOR,
        PANEL_STATE_TEST
    } panel_state = PANEL_STATE_LEVEL_SELECT;

    Direction direction = DIRECTION_N;

    bool full_screen = false;
    int scale = 0;
    XYPos grid_offset = XYPos(32 * scale, 32 * scale);
    XYPos panel_offset = XYPos((8 + 32 * 11) * scale, (8 + 8 + 32) * scale);

    LevelSet* level_set;
    Level* current_level;

    Circuit* current_circuit = NULL;
    unsigned current_level_index = 0;
    unsigned placing_subcircuit_level;
    unsigned selected_monitor = 0;
    
    TestExecType monitor_state = MONITOR_STATE_PLAY_ALL;



    unsigned frame_index = 0;

    unsigned game_speed = 10;

    unsigned slider_pos;
    Direction slider_direction;
    unsigned slider_max;
    unsigned* slider_value_tgt;
    
    
    unsigned test_value[4] = {0};
    unsigned test_drive[4] = {0};
    
    CircuitPressure test_pressures[4];
    
    class PressureRecord
    {
    public:
        unsigned values[4];
        bool set;
    } test_pressure_histroy[192];
    unsigned test_pressure_histroy_index;
    unsigned test_pressure_histroy_sample_downcounter;
    unsigned test_pressure_histroy_sample_frequency = 100;

    bool show_debug = false;
    unsigned debug_last_time = 0;
    unsigned debug_frames = 0;
    unsigned debug_simticks = 0;

    unsigned debug_last_second_frames = 0;
    unsigned debug_last_second_simticks = 0;
    
    unsigned show_help = 1;
    
    bool show_main_menu = false;
    unsigned sound_volume = 100;
    unsigned music_volume = 100;

    XYPos mouse;
    
    XYPos pipe_start_grid_pos;
    bool pipe_start_ns;

public:
    GameState(const char* filename);
    void save(const char* filename);
    ~GameState();
    SDL_Texture* loadTexture(const char* filename);

    void audio();
    void render_number_2digit(XYPos pos, unsigned value, unsigned scale_mul = 1, unsigned bg_colour = 9, unsigned fg_colour = 0);
    void render_number_pressure(XYPos pos, Pressure value, unsigned scale_mul = 1, unsigned bg_colour = 9, unsigned fg_colour = 0);
    void render_number_long(XYPos pos, unsigned value, unsigned scale_mul = 1);
    void render_box(XYPos pos, XYPos size, unsigned colour);
    void render();
    void advance();
    void set_level(unsigned level_index);
    void mouse_click_in_grid();
    void mouse_click_in_panel();
    void mouse_motion();
    bool events();
};
