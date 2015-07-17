#ifndef __DECK_GUI_H
#define __DECK_GUI_H

#include <gdkmm/pixbuf.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

#include "../Lib/Constants.h"

using std::vector;

class DeckGUI {
public:
	DeckGUI();                                                          // constructor
	virtual ~DeckGUI();                                                 // deconstructor
	Glib::RefPtr<Gdk::Pixbuf> getCardImage( Rank f, Suit s ) const;     // accessor - returns the image for the specified card.
	Glib::RefPtr<Gdk::Pixbuf> getNullCardImage() const;                 // accessor - returns the image to use for the placeholder.

private:
    Glib::RefPtr<Gdk::Pixbuf> createPixbuf(const std::string & name) const ;  // accessor - returns a new Pixbuf that was created from filename
	vector< Glib::RefPtr< Gdk::Pixbuf > > deck;                         // contains the pixel buffer images.
};
#endif
