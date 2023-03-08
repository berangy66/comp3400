#ifndef a4_provided_hpp_
#define a4_provided_hpp_

//=============================================================================

#include <compare>          // e.g., for operator<=>
#include <istream>          // e.g., for std::istream
#include <optional>         // e.g., for std::optional
#include <ostream>          // e.g., for std::ostream
#include <string>           // e.g., for std::string
#include <type_traits>      // e.g., for std::underlying_type_t

//=============================================================================

enum class card_suit { clubs, spades, hearts, diamonds }; // NOTE: You must define these functions in your code: 1 is clubs, 2 is spades, 3 is hearts, 4 is diamonds
std::optional<card_suit> read_card_suit(std::istream& is); //this function reads a card suit from the input stream and returns the suit as an optional value if the suit is valid. If the suit is invalid, the function returns an empty optional value. If the stream fails, the function returns an empty optional value. If the character read in is not a valid suit, the character is returned to the stream using is.unget().

inline std::istream& operator>>(std::istream& is, card_suit& s) //Overload the >> operator to read a card suit from the input stream. If the stream fails, the function returns an empty optional value. If the character read in is not a valid suit, the character is returned to the stream using is.unget().
{
  auto result = read_card_suit(is); //call the read_card_suit function to read a card suit from the input stream
  if (result)
    s = *result;
  return is;
}

inline std::ostream& operator<<(std::ostream& os, card_suit const& s) //Overload the << operator to write a card suit to the output stream. If the stream fails, the function returns an empty optional value. If the character read in is not a valid suit, the character is returned to the stream using is.unget().
{
  switch (s)
  {
    case card_suit::clubs:      os.put('c'); break; //if the suit is clubs, the function writes a c to the output stream
    case card_suit::diamonds:   os.put('d'); break; //if the suit is diamonds, the function writes a d to the output stream
    case card_suit::hearts:     os.put('h'); break; //if the suit is hearts, the function writes a h to the output stream
    case card_suit::spades:     os.put('s'); break; //if the suit is spades, the function writes a s to the output stream

    default:  // NOTE: This should never happen!, but just in case... 
      os.setstate(std::ios_base::failbit);  // fail the stream
      break; 
  }
  return os; //return the output stream, os, by reference
}

//=============================================================================
// NOTE: You must define these functions in your code: 1 is ace, 2 is two, 3 is three, 4 is four, 5 is five, 6 is six,
// 7 is seven, 8 is eight, 9 is nine, 10 is ten, 11 is jack, 12 is queen, 13 is knight, 14 is king, 15 is red_joker, 16 is white_joker
enum class card_face
{
  ace, two, three, four, five,
  six, seven, eight, nine, ten,
  jack, queen, knight, king,
  red_joker,
  white_joker
};

// NOTE: You must define these functions in your code:
std::optional<card_face> read_card_face(std::istream& is);  //this function reads a card face from the input stream and returns the face as an optional value if the face is valid. If the face is invalid, the function returns an empty optional value. If the stream fails, the function returns an empty optional value. If the character read in is not a valid face, the character is returned to the stream using is.unget().
std::istream& operator>>(std::istream& is, card_face& s); //Overload the >> operator to read a card face from the input stream. If the stream fails, the function returns an empty optional value. If the character read in is not a valid face, the character is returned to the stream using is.unget().
std::ostream& operator<<(std::ostream& os, card_face const& s); //Overload the << operator to write a card face to the output stream. If the stream fails, the function returns an empty optional value. If the character read in is not a valid face, the character is returned to the stream using is.unget().

//=============================================================================

// NOTE: You must define this class in your code:
class playing_card;

// NOTE: You must define these functions in your code:
bool operator==(playing_card const&, playing_card const&); //comparison operator for comparing two palying cards from the same deck
std::strong_ordering operator<=>(playing_card const&, playing_card const&); //comparison operator for comparing two palying cards from the same deck
std::optional<playing_card> read_playing_card(std::istream& is); //this function reads a playing card from the input stream and returns the card as an optional value if the card is valid. If the card is invalid, the function returns an empty optional value. If the stream fails, the function returns an empty optional value. If the character read in is not a valid card, the character is returned to the stream using is.unget().
std::istream& operator>>(std::istream& is, playing_card& c); //Overload the >> operator to read a playing card from the input stream. If the stream fails, the function returns an empty optional value. If the character read in is not a valid card, the character is returned to the stream using is.unget().
std::ostream& operator<<(std::ostream& os, playing_card const& c);// Overload the << operator to write a playing card to the output stream. If the stream fails, the function returns an empty optional value. If the character read in is not a valid card, the character is returned to the stream using is.unget().

//=============================================================================

std::string all_playing_cards_as_string(); //this function returns a string containing all the playing cards in the deck, one per line, in the order they are stored in the deck. The cards are separated by newlines. The cards are printed in the format: <face><suit>, e.g., ace of clubs is printed as ac, two of spades is printed as 2s, knight of hearts is printed as kh, red joker is printed as rj, white joker is printed as wj.

//=============================================================================

#endif // #ifndef a4_provided_hpp_
