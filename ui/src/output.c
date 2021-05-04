#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <SDL.h>
#include "../global.h"
#include "../output.h"
#include "../input.h"

const SDL_MessageBoxColorScheme colorScheme = {
        {
                {0, 0, 0},
                {255, 255, 255},
                {255, 255, 0},
                {0, 0, 255},
                {255, 0, 255},
        },
};

const SDL_MessageBoxButtonData warningButtons[] = {
        {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "OK"},
};

void Ui_showWarningDialog(const char *msg) {
    const SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_WARNING,        /* .flags */
            NULL,                          /* .window */
            "Warning",                     /* .title */
            msg,                           /* .message */
            SDL_arraysize(warningButtons), /* .numbuttons */
            warningButtons,                /* .buttons */
            &colorScheme                   /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
    }
}

void Ui_printWithNewLine(const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    vprintf(msg, args);
    printf("\n");
    va_end(args);
}

int Ui_handleMenu(const char *leadingMsg, const char *selectionMsg, const char *items[], int itemsCount, bool clear) {
    int selectedOption = -1;
    do {
        if (clear)
            Ui_clear();
        Ui_printWithNewLine(leadingMsg);
        printf("\n");
        for (int i = 0; i < itemsCount; i++) {
            printf("%d - ", i);
            Ui_printWithNewLine(items[i]);
        }
        printf("\n");
        Ui_readInput(selectionMsg, "%d", &selectedOption);
    } while (selectedOption < 0 || selectedOption >= itemsCount);
    if (clear)
        Ui_clear();
    return selectedOption;
}

void Ui_clear() {
    system(CLEAR);
}