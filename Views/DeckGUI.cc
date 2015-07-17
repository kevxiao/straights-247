
#include "DeckGUI.h"
#include <algorithm>
#include <iterator>
#include <string>
using std::string;
using std::transform;

const char * image_names[] = {   
	"cards_png/0_0.png", "cards_png/0_1.png", "cards_png/0_2.png", "cards_png/0_3.png",
	"cards_png/1_0.png", "cards_png/1_1.png", "cards_png/1_2.png", "cards_png/1_3.png",
	"cards_png/2_0.png", "cards_png/2_1.png", "cards_png/2_2.png", "cards_png/2_3.png",
	"cards_png/3_0.png", "cards_png/3_1.png", "cards_png/3_2.png", "cards_png/3_3.png",
	"cards_png/4_0.png", "cards_png/4_1.png", "cards_png/4_2.png", "cards_png/4_3.png",
	"cards_png/5_0.png", "cards_png/5_1.png", "cards_png/5_2.png", "cards_png/5_3.png",
	"cards_png/back_1.png"
}; 

Glib::RefPtr<Gdk::Pixbuf> createPixbuf(const string & name) {
	return Gdk::Pixbuf::create_from_file( name );
} 

DeckGUI::DeckGUI()  {
	transform( &image_names[0], &image_names[G_N_ELEMENTS(image_names)], 
			   std::back_inserter(deck), &createPixbuf );
}

DeckGUI::~DeckGUI() {
}

Glib::RefPtr<Gdk::Pixbuf> DeckGUI::getCardImage( Faces f, Suits s ) {
	int index = ((int) f)*4 + ((int) s );
	return deck[ index ];
}

Glib::RefPtr<Gdk::Pixbuf> DeckGUI::getNullCardImage() {
	int size = deck.size();
	return deck[ size-1 ];
}
