
#include "DeckGUI.h"
#include <algorithm>
#include <iterator>
#include <string>
using std::string;
using std::transform;

const char * image_names[] = {   
	"Assets/0_0.png", "Assets/0_1.png", "Assets/0_2.png", "Assets/0_3.png",
    "Assets/0_4.png", "Assets/0_5.png", "Assets/0_6.png", "Assets/0_7.png",
    "Assets/0_8.png", "Assets/0_9.png", "Assets/0_j.png", "Assets/0_q.png", "Assets/0_k.png",
	"Assets/1_0.png", "Assets/1_1.png", "Assets/1_2.png", "Assets/1_3.png",
    "Assets/1_4.png", "Assets/1_5.png", "Assets/1_6.png", "Assets/1_7.png",
    "Assets/1_8.png", "Assets/1_9.png", "Assets/1_j.png", "Assets/1_q.png", "Assets/1_k.png",
    "Assets/2_0.png", "Assets/2_1.png", "Assets/2_2.png", "Assets/2_3.png",
    "Assets/2_4.png", "Assets/2_5.png", "Assets/2_6.png", "Assets/2_7.png",
    "Assets/2_8.png", "Assets/2_9.png", "Assets/2_j.png", "Assets/2_q.png", "Assets/2_k.png",
    "Assets/3_0.png", "Assets/3_1.png", "Assets/3_2.png", "Assets/3_3.png",
    "Assets/3_4.png", "Assets/3_5.png", "Assets/3_6.png", "Assets/3_7.png",
    "Assets/3_8.png", "Assets/3_9.png", "Assets/3_j.png", "Assets/3_q.png", "Assets/3_k.png",
	"Assets/nothing.png"
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

Glib::RefPtr<Gdk::Pixbuf> DeckGUI::getCardImage( Rank f, Suit s ) {
	int index = (int)f + ((int)s  * (int) RANK_COUNT);
	return deck[ index ];
}

Glib::RefPtr<Gdk::Pixbuf> DeckGUI::getNullCardImage() {
	unsigned long size = deck.size();
	return deck[ size-1 ];
}
