#ifndef __DECK_GUI_H
#define __DECK_GUI_H

#include <gdkmm/pixbuf.h>
#include <vector>
using std::vector;

enum Faces { ACE = 0, TWO = 1, THREE = 2, FOUR = 3, FIVE = 4, SIX = 5, SEVEN = 6, EIGHT = 7, NINE = 8, TEN = 9, JACK = 10, QUEEN = 11, KING = 12 };
enum Suits { CLUB = 0, DIAMOND = 1, HEART = 2, SPADE = 3 };

class DeckGUI {
public:
	DeckGUI();
	virtual ~DeckGUI();
	Glib::RefPtr<Gdk::Pixbuf> getCardImage( Faces f, Suits s );   // Returns the image for the specified card.
	Glib::RefPtr<Gdk::Pixbuf> getNullCardImage();                 // Returns the image to use for the placeholder.

private:
	vector< Glib::RefPtr< Gdk::Pixbuf > > deck;                   // Contains the pixel buffer images.
};
#endif
