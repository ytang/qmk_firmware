#include QMK_KEYBOARD_H

#include "snippets.h"

enum alt_keycodes {
    L_BRI = SAFE_RANGE, //LED Brightness Increase
    L_BRD,              //LED Brightness Decrease
    L_EDG_I,            //LED Edge Brightness Increase
    L_EDG_D,            //LED Edge Brightness Decrease
    L_EDG_M,            //LED Edge lighting mode
    L_PTN,              //LED Pattern Select Next
    L_PTP,              //LED Pattern Select Previous
    L_PSI,              //LED Pattern Speed Increase
    L_PSD,              //LED Pattern Speed Decrease
    L_T_MD,             //LED Toggle Mode
    L_T_ONF,            //LED Toggle On / Off
    L_ON,               //LED On
    L_OFF,              //LED Off
    L_T_BR,             //LED Toggle Breath Effect
    L_T_PTD,            //LED Toggle Scrolling Pattern Direction and effect
    U_T_AGCR,           //USB Toggle Automatic GCR control
    DBG_TOG,            //DEBUG Toggle On / Off
    DBG_MTRX,           //DEBUG Toggle Matrix Prints
    DBG_KBD,            //DEBUG Toggle Keyboard Prints
    DBG_MOU,            //DEBUG Toggle Mouse Prints
    DBG_FAC,            //DEBUG Factory light testing (All on white)
    MD_BOOT,            //Restart into bootloader after hold timeout
    M_LNAME,
    M_FNAME,
    M_EMAIL,
    M_ADDR,
    M_PHONE,
    VIM_A,
    VIM_B,
    VIM_C,
    VIM_CI,
    VIM_D,
    VIM_DI,
    VIM_E,
    VIM_H,
    VIM_I,
    VIM_J,
    VIM_K,
    VIM_L,
    VIM_O,
    VIM_P,
    VIM_S,
    VIM_U,
    VIM_V,
    VIM_VI,
    VIM_W,
    VIM_X,
    VIM_Y,
};

#define PRESS(keycode) register_code16(keycode)
#define RELEASE(keycode) unregister_code16(keycode)
#define TAP(keycode) tap_code16(keycode)

void CMD(uint16_t keycode) {
    PRESS(KC_LGUI);
        TAP(keycode);
    RELEASE(KC_LGUI);
}

void CTRL(uint16_t keycode) {
    PRESS(KC_LCTRL);
        TAP(keycode);
    RELEASE(KC_LCTRL);
}

void SHIFT(uint16_t keycode) {
    PRESS(KC_LSHIFT);
        TAP(keycode);
    RELEASE(KC_LSHIFT);
}

void ALT(uint16_t keycode) {
    PRESS(KC_LALT);
        TAP(keycode);
    RELEASE(KC_LALT);
}

static uint16_t VIM_QUEUE = KC_NO;

/**
 * Sets the `VIM_QUEUE` variable to the incoming keycode.
 * Pass `KC_NO` to cancel the operation.
 * @param keycode
 */
void VIM_LEADER(uint16_t keycode) {
    VIM_QUEUE = keycode;
}

void VIM_APPEND(void);
void VIM_APPEND_LINE(void);
void VIM_BACK(void);
void VIM_CHANGE_BACK(void);
void VIM_CHANGE_DOWN(void);
void VIM_CHANGE_END(void);
void VIM_CHANGE_INNER_WORD(void);
void VIM_CHANGE_LEFT(void);
void VIM_CHANGE_LINE(void);
void VIM_CHANGE_RIGHT(void);
void VIM_CHANGE_UP(void);
void VIM_CHANGE_WHOLE_LINE(void);
void VIM_CHANGE_WORD(void);
void VIM_CUT(void);
void VIM_DELETE_BACK(void);
void VIM_DELETE_DOWN(void);
void VIM_DELETE_END(void);
void VIM_DELETE_INNER_WORD(void);
void VIM_DELETE_LEFT(void);
void VIM_DELETE_LINE(void);
void VIM_DELETE_RIGHT(void);
void VIM_DELETE_UP(void);
void VIM_DELETE_WHOLE_LINE(void);
void VIM_DELETE_WORD(void);
void VIM_END(void);
void VIM_INSERT(void);
void VIM_INSERT_LINE(void);
void VIM_JOIN(void);
void VIM_OPEN(void);
void VIM_OPEN_ABOVE(void);
void VIM_PUT(void);
void VIM_SUBSTITUTE(void);
void VIM_UNDO(void);
void VIM_VISUAL_BACK(void);
void VIM_VISUAL_DOWN(void);
void VIM_VISUAL_END(void);
void VIM_VISUAL_INNER_WORD(void);
void VIM_VISUAL_LEFT(void);
void VIM_VISUAL_RIGHT(void);
void VIM_VISUAL_UP(void);
void VIM_VISUAL_WORD(void);
void VIM_WORD(void);
void VIM_YANK(void);

/***
 *     #######  #     #  #######       #####   #     #  #######  #######
 *     #     #  ##    #  #            #     #  #     #  #     #     #
 *     #     #  # #   #  #            #        #     #  #     #     #
 *     #     #  #  #  #  #####         #####   #######  #     #     #
 *     #     #  #   # #  #                  #  #     #  #     #     #
 *     #     #  #    ##  #            #     #  #     #  #     #     #
 *     #######  #     #  #######       #####   #     #  #######     #
 *
 */

/**
 * Vim-like `append` command.
 * Works by sending →.
 */
void VIM_APPEND(void) {
    clear_mods();
    TAP(KC_RIGHT);
    layer_off(1);
}

/**
 * Vim-like `back` command
 * Simulates vim's `b` command by sending ⌥←
 */
void VIM_BACK(void) {
    clear_mods();
    ALT(KC_LEFT);
}

/**
 * Vim-like `cut` command
 * Simulates vim's `x` command by sending ⇧→ then ⌘X.
 */
void VIM_CUT(void) {
    clear_mods();
    SHIFT(KC_RIGHT);
    CMD(KC_X);
}

/**
 * Vim-like `down` command
 * Sends ↓
 */
void VIM_DOWN(void) {
    clear_mods();
    TAP(KC_DOWN);
}

/**
 * Vim-like `end` command
 * Simulates vim's `e` command by sending ⌥→
 */
void VIM_END(void) {
    clear_mods();
    ALT(KC_RIGHT);
}

/**
 * Vim-like `insert` command.
 * Works by switching to insert mode.
 */
void VIM_INSERT(void) {
    clear_mods();
    layer_off(1);
}

/**
 * Vim-like `left` command
 * Sends ←
 */
void VIM_LEFT(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    TAP(KC_LEFT);
}

/**
 * Vim-like `open` command.
 * Works by sending ⌘→ to move to the end of the line, `enter` to open a new line,
 * then switching to insert mode.
 */
void VIM_OPEN(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    CMD(KC_RIGHT);
    TAP(KC_ENTER);
    layer_off(1);
}

/**
 * Vim-like `put` command
 * Simulates vim's `p` command by sending ⌘V
 */
void VIM_PUT(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    CMD(KC_V);
}

/**
 * Vim-like `put before` command
 * Simulates vim's `P` command by sending ↑, ⌘←, then ⌘V
 */
void VIM_PUT_BEFORE(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    TAP(KC_UP);
    CMD(KC_LEFT);
    CMD(KC_V);
}

/**
 * Vim-like `right` command
 * Sends →
 */
void VIM_RIGHT(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    TAP(KC_RIGHT);
}

/**
 * Vim-like `substitute` command
 * Simulates vim's `s` command by sending ⇧→ to select the next character, then
 * ⌘X to cut it, then entering insert mode.
 */
void VIM_SUBSTITUTE(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    SHIFT(KC_RIGHT);
    CMD(KC_X);
    layer_off(1);
}

/**
 * Vim-like `undo` command
 * Simulates vim's `u` command by sending ⌘Z
 */
void VIM_UNDO(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    CMD(KC_Z);
}

/**
 * Vim-like `up` command
 * Sends ↑
 */
void VIM_UP(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    TAP(KC_UP);
}

/**
 * Vim-like `word` command
 * Simulates vim's `w` command by moving the cursor first to the
 * end of the current word, then to the end of the next word,
 * then to the beginning of that word.
 */
void VIM_WORD(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    PRESS(KC_LALT);
        TAP(KC_RIGHT);
        TAP(KC_RIGHT);
        TAP(KC_LEFT);
    RELEASE(KC_LALT);
}

/**
 * Vim-like `yank` command
 * Simulates vim's `y` command by sending ⌘C
 */
void VIM_YANK(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    CMD(KC_C);
}

/**
 * Vim-like `yank line` command
 * Simulates vim's `y` command by sending ⌘← then ⇧⌘→ then ⌘C
 */
void VIM_YANK_LINE(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    CMD(KC_LEFT);
    PRESS(KC_LSHIFT);
        CMD(KC_RIGHT);
    RELEASE(KC_LSHIFT);
    CMD(KC_C);
}

/***
 *      #####   #     #  ###  #######  #######  #######  ######
 *     #     #  #     #   #   #           #     #        #     #
 *     #        #     #   #   #           #     #        #     #
 *      #####   #######   #   #####       #     #####    #     #
 *           #  #     #   #   #           #     #        #     #
 *     #     #  #     #   #   #           #     #        #     #
 *      #####   #     #  ###  #           #     #######  ######
 *
 */

/**
 * Vim-like `append to line` command
 * Simulates vim's `A` command by sending ⌘→ then switching to insert mode.
 */
void VIM_APPEND_LINE(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    CMD(KC_RIGHT);
    layer_off(1);
}

/**
 * Vim-like `change line` command
 * Simulates vim's `C` command by sending ⌃K then switching to insert mode.
 */
void VIM_CHANGE_LINE(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    VIM_DELETE_LINE();
    layer_off(1);
}

/**
 * Vim-like 'delete line' command
 * Simulates vim's `D` command by sending ⌃K to kill the line
 */
void VIM_DELETE_LINE(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    CTRL(KC_K);
}

/**
 * Vim-like `insert before line` command
 * Simulates vim's `I` command by sending ⌘← then switching to insert mode.
 */
void VIM_INSERT_LINE(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    CMD(KC_LEFT);
    layer_off(1);
}

/**
 * Vim-like 'join lines' command
 * Simulates vim's `J` command by sending ⌘→ to go to the end of the line, then
 * DELETE to join the lines
 */
void VIM_JOIN(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    CMD(KC_RIGHT);
    TAP(KC_DELETE);
    VIM_LEADER(KC_NO);
}

/**
 * Vim-like 'open above' command
 * Simulates vim's `O` command by sending ⌘→ to go to the start of the line,
 * enter to move the line down, ↑ to move up to the new line, then switching to
 * insert mode.
 */
void VIM_OPEN_ABOVE(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    CMD(KC_LEFT);
    TAP(KC_ENTER);
    TAP(KC_UP);
    layer_off(1);
}

/**
 * Vim-like 'change whole line' command
 * Simulates vim's `S` `cc` or `c$` commands by sending ⌘← to go to the start of the line,
 * ⌃K to kill the line, then switching to insert mode.
 */
void VIM_CHANGE_WHOLE_LINE(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    CMD(KC_LEFT);
    VIM_CHANGE_LINE();
}

/***
 *     ######       ######   ######   #######  #######  ###  #     #  #######  ######
 *     #     #      #     #  #     #  #        #         #    #   #   #        #     #
 *     #     #      #     #  #     #  #        #         #     # #    #        #     #
 *     #     #      ######   ######   #####    #####     #      #     #####    #     #
 *     #     #      #        #   #    #        #         #     # #    #        #     #
 *     #     #      #        #    #   #        #         #    #   #   #        #     #
 *     ######       #        #     #  #######  #        ###  #     #  #######  ######
 *
 */

/**
 * Vim-like `delete to end` command
 * Simulates vim's `de` command by sending ⌥⇧→ then ⌘X.
 */
void VIM_DELETE_END(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    PRESS(KC_LALT);
        SHIFT(KC_RIGHT); // select to end of this word
    RELEASE(KC_LALT);
    CMD(KC_X);
}

/**
 * Vim-like `delete whole line` command
 * Simulates vim's `dd` command by sending ⌘← to move to start of line,
 * selecting the whole line, then sending ⌘X to cut the line.
 * alternate method: ⌘⌫, ⌃K
 */
void VIM_DELETE_WHOLE_LINE(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    CMD(KC_LEFT);
    PRESS(KC_LSHIFT);
        CMD(KC_RIGHT);
    RELEASE(KC_LSHIFT);
    CMD(KC_X);
}

/**
 * Vim-like `delete word` command
 * Simulates vim's `dw` command by sending ⌥⇧→→← then ⌘X to select to the start
 * of the next word then cut.
 */
void VIM_DELETE_WORD(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    PRESS(KC_LALT);
        SHIFT(KC_RIGHT); // select to end of this word
        SHIFT(KC_RIGHT); // select to end of next word
        SHIFT(KC_LEFT); // select to start of next word
    RELEASE(KC_LALT);
    CMD(KC_X); // delete selection
}

/**
 * Vim-like `delete back` command
 * Simulates vim's `db` command by selecting to the end of the word then deleting.
 */
void VIM_DELETE_BACK(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    PRESS(KC_LALT);
        SHIFT(KC_LEFT); // select to start of word
        SHIFT(KC_DEL); // delete selection
    RELEASE(KC_LSHIFT);
}

/**
 * Vim-like `delete left` command
 * Simulates vim's `dh` command by sending ⇧← then ⌘X.
 */
void VIM_DELETE_LEFT(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    SHIFT(KC_LEFT);
    CMD(KC_X);
}

/**
 * Vim-like `delete right` command
 * Simulates vim's `dl` command by sending ⇧→ then ⌘X.
 */
void VIM_DELETE_RIGHT(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    SHIFT(KC_RIGHT);
    CMD(KC_X);
}

/**
 * Vim-like `delete up` command
 * Simulates vim's `dk` command by sending ↑ then deleting the line.
 */
void VIM_DELETE_UP(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    TAP(KC_UP);
    VIM_DELETE_LINE();
}

/**
 * Vim-like `delete down` command
 * Simulates vim's `dj` command by sending ↓ then deleting the line.
 */
void VIM_DELETE_DOWN(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    TAP(KC_DOWN);
    VIM_DELETE_LINE();
}

/***
 *     ######   ###      ######   ######   #######  #######  ###  #     #  #######  ######
 *     #     #   #       #     #  #     #  #        #         #    #   #   #        #     #
 *     #     #   #       #     #  #     #  #        #         #     # #    #        #     #
 *     #     #   #       ######   ######   #####    #####     #      #     #####    #     #
 *     #     #   #       #        #   #    #        #         #     # #    #        #     #
 *     #     #   #       #        #    #   #        #         #    #   #   #        #     #
 *     ######   ###      #        #     #  #######  #        ###  #     #  #######  ######
 *
 */

/**
 * Vim-like `delete inner word` command
 * Simulates vim's `diw` command by moving back then cutting to the end of the word.
 */
void VIM_DELETE_INNER_WORD(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    VIM_BACK();
    VIM_DELETE_END();
}

/***
 *      #####        ######   ######   #######  #######  ###  #     #  #######  ######
 *     #     #       #     #  #     #  #        #         #    #   #   #        #     #
 *     #             #     #  #     #  #        #         #     # #    #        #     #
 *     #             ######   ######   #####    #####     #      #     #####    #     #
 *     #             #        #   #    #        #         #     # #    #        #     #
 *     #     #       #        #    #   #        #         #    #   #   #        #     #
 *      #####        #        #     #  #######  #        ###  #     #  #######  ######
 *
 */

/**
 * Vim-like `change back` command
 * Simulates vim's `cb` command by first deleting to the start of the word,
 * then switching to insert mode.
 */
void VIM_CHANGE_BACK(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    VIM_DELETE_BACK();
    layer_off(1);
}

/**
 * Vim-like `change down` command
 * Simulates vim's `cj` command by sending ↓ then changing the line.
 */
void VIM_CHANGE_DOWN(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    VIM_DELETE_DOWN();
    layer_off(1);
}

/**
 * Vim-like `change to end` command
 * Simulates vim's `ce` command by first deleting to the end of the word,
 * then switching to insert mode.
 */
void VIM_CHANGE_END(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    VIM_DELETE_END();
    layer_off(1);
}

/**
 * Vim-like `change left` command
 * Simulates vim's `ch` command by deleting left then switching to insert mode.
 */
void VIM_CHANGE_LEFT(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    VIM_DELETE_LEFT();
    layer_off(1);
}

/**
 * Vim-like `change right` command
 * Simulates vim's `cl` command by deleting right then switching to insert mode.
 */
void VIM_CHANGE_RIGHT(void) {
    clear_mods();
    VIM_DELETE_RIGHT();
    layer_off(1);
}

/**
 * Vim-like `change up` command
 * Simulates vim's `ck` command by deleting up then switching to insert mode.
 */
void VIM_CHANGE_UP(void) {
    clear_mods();
    VIM_DELETE_UP();
    layer_off(1);
}

/**
 * Vim-like `change word` command
 * Simulates vim's `cw` command by first deleting to the end of the word,
 * then switching to insert mode.
 */
void VIM_CHANGE_WORD(void) {
    clear_mods();
    VIM_LEADER(KC_NO);
    PRESS(KC_LALT);
        SHIFT(KC_RIGHT); // select to end of this word
        SHIFT(KC_RIGHT); // select to end of next word
        SHIFT(KC_LEFT); // select to start of next word
    RELEASE(KC_LALT);
    SHIFT(KC_LEFT);
    CMD(KC_X); // delete selection
    layer_off(1);
}

/***
 *      #####   ###      ######   ######   #######  #######  ###  #     #  #######  ######
 *     #     #   #       #     #  #     #  #        #         #    #   #   #        #     #
 *     #         #       #     #  #     #  #        #         #     # #    #        #     #
 *     #         #       ######   ######   #####    #####     #      #     #####    #     #
 *     #         #       #        #   #    #        #         #     # #    #        #     #
 *     #     #   #       #        #    #   #        #         #    #   #   #        #     #
 *      #####   ###      #        #     #  #######  #        ###  #     #  #######  ######
 *
 */

/**
 * Vim-like `change inner word` command
 * Simulates vim's `ciw` command by deleting the inner word then switching to insert mode.
 */
void VIM_CHANGE_INNER_WORD(void) {
    clear_mods();
    VIM_DELETE_INNER_WORD();
    layer_off(1);
}

/***
 *     #     #      ######   ######   #######  #######  ###  #     #  #######  ######
 *     #     #      #     #  #     #  #        #         #    #   #   #        #     #
 *     #     #      #     #  #     #  #        #         #     # #    #        #     #
 *     #     #      ######   ######   #####    #####     #      #     #####    #     #
 *      #   #       #        #   #    #        #         #     # #    #        #     #
 *       # #        #        #    #   #        #         #    #   #   #        #     #
 *        #         #        #     #  #######  #        ###  #     #  #######  ######
 *
 */

/**
 * Vim-like `visual select back` command
 * Simulates vim's `vb` command by selecting to the enc of the word.
 */
void VIM_VISUAL_BACK(void) {
    clear_mods();
    PRESS(KC_LALT);
        SHIFT(KC_LEFT); // select to start of word
    RELEASE(KC_LALT);
}

/**
 * Vim-like `visual select to end` command
 * Simulates vim's `ve` command by selecting to the end of the word.
 */
void VIM_VISUAL_END(void) {
    clear_mods();
    PRESS(KC_LALT);
        SHIFT(KC_RIGHT); // select to end of this word
    RELEASE(KC_LALT);
}

/**
 * Vim-like `visual select word` command
 * Simulates vim's `vw` command by selecting to the end of the word.
 */
void VIM_VISUAL_WORD(void) {
    clear_mods();
    PRESS(KC_LALT);
        SHIFT(KC_RIGHT); // select to end of this word
        SHIFT(KC_RIGHT); // select to end of next word
        SHIFT(KC_LEFT); // select to start of next word
    RELEASE(KC_LALT);
}

/**
 * Vim-like `visual left` command
 * Simulates vim's `vh` command by sending ⇧←.
 */
void VIM_VISUAL_LEFT(void) {
    clear_mods();
    SHIFT(KC_LEFT);
}

/**
 * Vim-like `visual right` command
 * Simulates vim's `vl` command by sending ⇧→.
 */
void VIM_VISUAL_RIGHT(void) {
    clear_mods();
    SHIFT(KC_RIGHT);
}

/**
 * Vim-like `visual up` command
 * Simulates vim's `vk` command by sending ⇧↑.
 */
void VIM_VISUAL_UP(void) {
    clear_mods();
    SHIFT(KC_UP);
}

/**
 * Vim-like `visual down` command
 * Simulates vim's `vj` command by sending ⇧↓.
 */
void VIM_VISUAL_DOWN(void) {
    clear_mods();
    SHIFT(KC_DOWN);
}

/***
 *     #     #  ###      ######   ######   #######  #######  ###  #     #  #######  ######
 *     #     #   #       #     #  #     #  #        #         #    #   #   #        #     #
 *     #     #   #       #     #  #     #  #        #         #     # #    #        #     #
 *     #     #   #       ######   ######   #####    #####     #      #     #####    #     #
 *      #   #    #       #        #   #    #        #         #     # #    #        #     #
 *       # #     #       #        #    #   #        #         #    #   #   #        #     #
 *        #     ###      #        #     #  #######  #        ###  #     #  #######  ######
 *
 */

/**
 * Vim-like `visual inner word` command
 * Simulates vim's `viw` command by moving back then selecting to the end of the word.
 */
void VIM_VISUAL_INNER_WORD(void) {
    clear_mods();
    VIM_BACK();
    VIM_VISUAL_END();
}

#define TG_NKRO MAGIC_TOGGLE_NKRO //Toggle 6KRO / NKRO mode

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
 HYPR_T(KC_CAPS),KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,          KC_UP,   KC_PGDN, \
        TD(0),   KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, MO(2),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, VIM_W,   VIM_E,   _______, _______, VIM_Y,   VIM_U,   VIM_I,   VIM_O,   VIM_P,   _______, _______, _______, _______, \
        _______, VIM_A,   VIM_S,   VIM_D,   _______, _______, VIM_H,   VIM_J,   VIM_K,   VIM_L,   _______, _______,          _______, _______, \
        _______, _______, VIM_X,   VIM_C,   VIM_V,   VIM_B,   _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    [2] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_EJCT, KC_MUTE, \
        L_T_BR,  L_PSD,   L_BRI,   L_PSI,   L_EDG_I, M_LNAME, M_FNAME, KC_BTN1, KC_MS_U, KC_BTN2, KC_PSCR, KC_SLCK, KC_PAUS,G(KC_ESC),KC_END,  \
        L_T_PTD, L_PTP,   L_BRD,   L_PTN,   L_EDG_D, M_EMAIL, M_ADDR,  KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U, KC_WH_D,          KC_INS,  KC_VOLU, \
        _______, L_T_MD,  L_T_ONF, M_PHONE, L_EDG_M, MD_BOOT, TG_NKRO,S(KC_ESC),KC_MRWD, KC_MFFD, KC_MPLY, _______,          KC_PGUP, KC_VOLD, \
        _______, _______, _______,                            DBG_FAC,                            _______, _______, KC_HOME, KC_PGDN, KC_END   \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    */
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    VIM_LEADER(KC_NO);
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

#define MODS_SHIFT (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;
    static uint8_t scroll_effect = 0;

    switch (keycode) {
        case L_BRI:
            if (record->event.pressed) {
                if (LED_GCR_STEP > LED_GCR_MAX - gcr_desired) gcr_desired = LED_GCR_MAX;
                else gcr_desired += LED_GCR_STEP;
                if (led_animation_breathing) gcr_breathe = gcr_desired;
            }
            return false;
        case L_BRD:
            if (record->event.pressed) {
                if (LED_GCR_STEP > gcr_desired) gcr_desired = 0;
                else gcr_desired -= LED_GCR_STEP;
                if (led_animation_breathing) gcr_breathe = gcr_desired;
            }
            return false;
        case L_EDG_M:
            if (record->event.pressed) {
                led_edge_mode++;
                if (led_edge_mode > LED_EDGE_MODE_MAX) {
                    led_edge_mode = LED_EDGE_MODE_ALL;
                }
            }
            return false;
        case L_EDG_I:
            if (record->event.pressed) {
                led_edge_brightness += 0.1;
                if (led_edge_brightness > 1) { led_edge_brightness = 1; }
            }
            return false;
        case L_EDG_D:
            if (record->event.pressed) {
                led_edge_brightness -= 0.1;
                if (led_edge_brightness < 0) { led_edge_brightness = 0; }
            }
            return false;
        case L_PTN:
            if (record->event.pressed) {
                if (led_animation_id == led_setups_count - 1) led_animation_id = 0;
                else led_animation_id++;
            }
            return false;
        case L_PTP:
            if (record->event.pressed) {
                if (led_animation_id == 0) led_animation_id = led_setups_count - 1;
                else led_animation_id--;
            }
            return false;
        case L_PSI:
            if (record->event.pressed) {
                led_animation_speed += ANIMATION_SPEED_STEP;
            }
            return false;
        case L_PSD:
            if (record->event.pressed) {
                led_animation_speed -= ANIMATION_SPEED_STEP;
                if (led_animation_speed < 0) led_animation_speed = 0;
            }
            return false;
        case L_T_MD:
            if (record->event.pressed) {
                led_lighting_mode++;
                if (led_lighting_mode > LED_MODE_MAX_INDEX) led_lighting_mode = LED_MODE_NORMAL;
            }
            return false;
        case L_T_ONF:
            if (record->event.pressed) {
                I2C3733_Control_Set(!I2C3733_Control_Get());
            }
            return false;
        case L_ON:
            if (record->event.pressed) {
                I2C3733_Control_Set(1);
            }
            return false;
        case L_OFF:
            if (record->event.pressed) {
                I2C3733_Control_Set(0);
            }
            return false;
        case L_T_BR:
            if (record->event.pressed) {
                led_animation_breathing = !led_animation_breathing;
                if (led_animation_breathing) {
                    gcr_breathe = gcr_desired;
                    led_animation_breathe_cur = BREATHE_MIN_STEP;
                    breathe_dir = 1;
                }
            }
            return false;
        case L_T_PTD:
            if (record->event.pressed) {
                scroll_effect++;
                if (scroll_effect == 1) {               //Patterns with scroll move horizontal (Right to left)
                    led_animation_direction = 1;
                    led_animation_orientation = 0;
                    led_animation_circular = 0;
                } else if (scroll_effect == 2) {        //Patterns with scroll move vertical (Top to bottom)
                    led_animation_direction = 1;
                    led_animation_orientation = 1;
                    led_animation_circular = 0;
                } else if (scroll_effect == 3) {        //Patterns with scroll move vertical (Bottom to top)
                    led_animation_direction = 0;
                    led_animation_orientation = 1;
                    led_animation_circular = 0;
                } else if (scroll_effect == 4) {        //Patterns with scroll explode from center
                    led_animation_direction = 0;
                    led_animation_orientation = 0;
                    led_animation_circular = 1;
                } else if (scroll_effect == 5) {        //Patterns with scroll implode on center
                    led_animation_direction = 1;
                    led_animation_orientation = 0;
                    led_animation_circular = 1;
                } else {                                //Patterns with scroll move horizontal (Left to right)
                    scroll_effect = 0;
                    led_animation_direction = 0;
                    led_animation_orientation = 0;
                    led_animation_circular = 0;
                }
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_FAC:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                led_lighting_mode = LED_MODE_NORMAL;
                led_edge_brightness = 1;
                led_edge_mode = LED_EDGE_MODE_ALL;
                led_animation_breathing = 0;
                led_animation_id = 7; //led_programs.c led_setups leds_white index
                gcr_desired = LED_GCR_MAX;
                I2C3733_Control_Set(1);
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= BOOTKEY_HOLD_MS) {
                    reset_keyboard();
                }
            }
            return false;
        case M_LNAME:
            if (record->event.pressed) {
                SEND_STRING(SNIPPET_LNAME);
            }
            return true;
        case M_FNAME:
            if (record->event.pressed) {
                SEND_STRING(SNIPPET_FNAME);
            }
            return true;
        case M_EMAIL:
            if (record->event.pressed) {
                SEND_STRING(SNIPPET_EMAIL);
            }
            return true;
        case M_ADDR:
            if (record->event.pressed) {
                SEND_STRING(SNIPPET_ADDR);
            }
            return true;
        case M_PHONE:
            if (record->event.pressed) {
                SEND_STRING(SNIPPET_PHONE);
            }
            return true;
        case VIM_A:
            if (record->event.pressed) { MODS_SHIFT ? VIM_APPEND_LINE() : VIM_APPEND(); }
            return false;
        case VIM_B:
            if (record->event.pressed) {
                switch(VIM_QUEUE) {
                    case KC_NO: VIM_BACK(); break;
                    case VIM_C: VIM_CHANGE_BACK(); break;
                    case VIM_D: VIM_DELETE_BACK(); break;
                    case VIM_V: VIM_VISUAL_BACK(); break;
                    default: VIM_LEADER(KC_NO);
                }
            }
            return false;
        case VIM_C:
            if (record->event.pressed) {
                switch(VIM_QUEUE) {
                    case KC_NO: MODS_SHIFT ? VIM_CHANGE_LINE() : VIM_LEADER(VIM_C); break;
                    case VIM_C: VIM_CHANGE_WHOLE_LINE(); break;
                    default: VIM_LEADER(KC_NO);
                }
            }
            return false;
        case VIM_D:
            if (record->event.pressed) {
                switch(VIM_QUEUE) {
                    case KC_NO: MODS_SHIFT ? VIM_DELETE_LINE() : VIM_LEADER(VIM_D); break;
                    case VIM_D: VIM_DELETE_WHOLE_LINE(); break;
                    default: VIM_LEADER(KC_NO);
                }
            }
            return false;
        case VIM_E:
            if (record->event.pressed) {
                switch (VIM_QUEUE) {
                    case KC_NO: VIM_END(); break;
                    case VIM_C: VIM_CHANGE_END(); break;
                    case VIM_D: VIM_DELETE_END(); break;
                    case VIM_V: VIM_VISUAL_END(); break;
                    default: VIM_LEADER(KC_NO);
                }
            }
            return false;
        case VIM_H:
            if (record->event.pressed) {
                switch (VIM_QUEUE) {
                    case KC_NO: VIM_LEFT(); break;
                    case VIM_C: VIM_CHANGE_LEFT(); break;
                    case VIM_D: VIM_DELETE_LEFT(); break;
                    case VIM_V: VIM_VISUAL_LEFT(); break;
                    default: VIM_LEADER(KC_NO);
                }
            }
            return false;
        case VIM_I:
            if (record->event.pressed) {
                switch (VIM_QUEUE) {
                    case KC_NO: MODS_SHIFT ? VIM_INSERT_LINE() : VIM_INSERT(); break;
                    case VIM_C: VIM_LEADER(VIM_CI); break;
                    case VIM_D: VIM_LEADER(VIM_DI); break;
                    case VIM_V: VIM_LEADER(VIM_VI); break;
                    default: VIM_LEADER(KC_NO);
                }
            }
            return false;
        case VIM_J:
            if (record->event.pressed) {
                switch (VIM_QUEUE) {
                    case KC_NO: MODS_SHIFT ? VIM_JOIN() : VIM_DOWN(); break;
                    case VIM_C: VIM_CHANGE_DOWN(); break;
                    case VIM_D: VIM_DELETE_DOWN(); break;
                    case VIM_V: VIM_VISUAL_DOWN(); break;
                    default: VIM_LEADER(KC_NO);
                }
            }
            return false;
        case VIM_K:
            if (record->event.pressed) {
                switch (VIM_QUEUE) {
                    case KC_NO: VIM_UP(); break;
                    case VIM_C: VIM_CHANGE_UP(); break;
                    case VIM_D: VIM_DELETE_UP(); break;
                    case VIM_V: VIM_VISUAL_UP(); break;
                    default: VIM_LEADER(KC_NO);
                }
            }
            return false;
        case VIM_L:
            if (record->event.pressed) {
                switch (VIM_QUEUE) {
                    case KC_NO: VIM_RIGHT(); break;
                    case VIM_C: VIM_CHANGE_RIGHT(); break;
                    case VIM_D: VIM_DELETE_RIGHT(); break;
                    case VIM_V: VIM_VISUAL_RIGHT(); break;
                    default: VIM_LEADER(KC_NO);
                }
            }
            return false;
        case VIM_O:
            if (record->event.pressed) { MODS_SHIFT ? VIM_OPEN_ABOVE() : VIM_OPEN(); }
            return false;
        case VIM_P:
            if (record->event.pressed) { MODS_SHIFT ? VIM_PUT_BEFORE() : VIM_PUT(); }
            return false;
        case VIM_S:
            if (record->event.pressed) { MODS_SHIFT ? VIM_CHANGE_WHOLE_LINE() : VIM_SUBSTITUTE(); }
            return false;
        case VIM_U:
            if (record->event.pressed) { VIM_UNDO(); }
            return false;
        case VIM_V:
            if (record->event.pressed) { VIM_LEADER(VIM_V); }
            return false;
        case VIM_W:
            if (record->event.pressed) {
                switch (VIM_QUEUE) {
                    case KC_NO: VIM_WORD(); break;
                    case VIM_C: VIM_CHANGE_WORD(); break;
                    case VIM_CI: VIM_CHANGE_INNER_WORD(); break;
                    case VIM_D: VIM_DELETE_WORD(); break;
                    case VIM_DI: VIM_DELETE_INNER_WORD(); break;
                    case VIM_V: VIM_VISUAL_WORD(); break;
                    case VIM_VI: VIM_VISUAL_INNER_WORD(); break;
                    default: VIM_LEADER(KC_NO);
                }
            }
            return false;
        case VIM_X:
            if (record->event.pressed) { VIM_CUT(); }
            return false;
        case VIM_Y:
            if (record->event.pressed) { MODS_SHIFT ? VIM_YANK_LINE() : VIM_YANK(); }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}

led_instruction_t led_instructions[] = {
    //Please see ../default_md/keymap.c for examples

    //All LEDs use the user's selected pattern (this is the factory default)
     { .flags = LED_FLAG_USE_ROTATE_PATTERN },

    //end must be set to 1 to indicate end of instruction set
     { .end = 1 }
};

static bool td_pressed = false;

void td_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_pressed = state->pressed;
    if (td_pressed) {
        PRESS(KC_LCTRL);
    } else {
        layer_on(1);
    }
}

void td_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (td_pressed) {
        RELEASE(KC_LCTRL);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [0] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_finished, td_reset)
};
