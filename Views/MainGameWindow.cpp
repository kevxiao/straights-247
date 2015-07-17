#include "MainGameWindow.h"
#include <iostream>

MainGameWindow::MainGameWindow() : startGameButton("Start new game"), endGameButton("End game"), gameButtonHBox(false, 100) {
		
	const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = deck.getNullCardImage();
	
	set_border_width( 10 );
		
	frame.set_label( "Straights" );
	frame.set_label_align( Gtk::ALIGN_CENTER, Gtk::ALIGN_TOP );
	frame.set_shadow_type( Gtk::SHADOW_ETCHED_OUT );
	
	add( frame );
	
	frame.add( containerBox );
    containerBox.add(gameButtonHBox);

    startGameButton.signal_clicked().connect( sigc::mem_fun( *this, &MainGameWindow::onStartGameButtonClicked ) );

    gameButtonHBox.add(startGameButton);
    gameButtonHBox.add(endGameButton);

    for(int j = 0; j < 4; j++)
    {
        cardHBoxes[j] = new Gtk::HBox(true, 10);
    	for (int i = 0; i < 13; i++ ) {
    		card[(j * 13) + i] = new Gtk::Image( nullCardPixbuf );
    		cardHBoxes[j]->add( *card[(j * 13) + i] );
    	}
        containerBox.add(*cardHBoxes[j]);
    }
	
	show_all();
}


MainGameWindow::~MainGameWindow() {
	for (int i = 0; i < 52; i++ ) delete card[i];
    for(int i = 0; i < 4; i++) delete cardHBoxes[i];
}

void MainGameWindow::onStartGameButtonClicked() {
    SeedDialogBox * seedDialog = new SeedDialogBox(*this, "Pick a seed:");
    int seed = seedDialog->popupAndGetSeed();
    std::cout<<seed<<std::endl;
    delete seedDialog;
    if(seed != -1)
    {
        PlayerSetupDialogBox * playerSetupDialog = new PlayerSetupDialogBox(*this);
        std::vector<bool> isPlayerHuman = playerSetupDialog->popupAndGetPlayerStatus();
        delete playerSetupDialog;
        //Note: If isPlayerHuman is empty, the window was closed. Otherwise the i-th element signifies if player i+1 is human or if is dancer 
    }
}
