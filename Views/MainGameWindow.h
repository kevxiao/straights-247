#ifndef __MARKOWINDOW_H
#define __MARKOWINDOW_H
#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>

#include "DeckGUI.h"
#include "SeedDialogBox.h"
#include "PlayerSetupDialogBox.h"

class MainGameWindow : public Gtk::Window {
public:
	MainGameWindow();
	virtual ~MainGameWindow();
	
private:

    void                            onStartGameButtonClicked();

	DeckGUI                         deck;             // Knows all of the card pixel buffers.
	
	// Member widgets:
	Gtk::Image                    * card[52];          // Images to display.
    Gtk::HBox                     * cardHBoxes[4];
    Gtk::Button                     startGameButton;
    Gtk::Button                     endGameButton;
    Gtk::VBox                       containerBox;
    Gtk::HBox                       gameButtonHBox;
	Gtk::HBox                       hbox;             // Horizontal box for aligning widgets in the window.
	Gtk::Frame                      frame;            // Create a nice framed border for the box.
};

#endif
