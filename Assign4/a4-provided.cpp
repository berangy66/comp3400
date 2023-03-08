//=============================================================================

#include <array>  // for std::array
#include <istream>  // for std::istream, std::ostream, std::getline, std::getline, 
#include <optional>   // for std::optional types, std::nullopt, std::has_value , std::value , std::make_optional
#include <string>    // for std::string, std::to_string, std::stoi 
#include <sstream> // for std::stringstream, std::istringstream, std::ostringstream, std::stringstream, 

#include "a4-provided.hpp" // 

//=============================================================================

//
// std::optional<card_suit> read_card_suit(std::istream)
//
// read_card_suit reads a card suit from an input stream returning a
// an optional value. The return value only holds a card_suit if a valid 
// card_suit was read in. If an error occurs on the stream while reading in
// the data, then stream is failed. If the character on the stream read in
// is not a valid suit, then the character read in is returned to the stream
// using is.unget().
//
std::optional<card_suit> read_card_suit(std::istream& is)
{
  std::optional<card_suit> retval; // create a optional card_suit, retval, and set it to nullopt with no value 
  auto ch = is.get();              // get a character from the stream, ch , and set it to the next character in the stream, or EOF if there is no more characters in the stream, or if the stream is in a fail state, isget() returns EOF, and sets the stream to a fail state, (failbit)
  if (!std::istream::traits_type::eq_int_type(ch,std::istream::traits_type::eof()))   // if ch is not EOF, then ch is a valid character, and the stream is not in a fail state,trait_type::eq_int_type() returns true if the two characters are equal, and false if they are not equal,
  {
    switch (ch)
    {
      case 'c': // if ch is 'c' for clubs, then set retval to card_suit::clubs
        retval = card_suit::clubs;  //assign the diamand suit to the optional value retval
        break;

      case 'd': // if ch is 'd' for diamonds, then set retval to card_suit::diamonds
        retval = card_suit::diamonds;
        break;

      case 'h':  // if ch is 'h' for hearts, then set retval to card_suit::hearts
        retval = card_suit::hearts;
        break;

      case 's': // if ch is 's' for spades, then set retval to card_suit::spades
        retval = card_suit::spades;
        break;

      default:                                    // if ch is not a valid suit, then
        is.unget();                               // return the ch to the stream
        is.setstate(std::ios_base::failbit);      // fail the stream, set the failbit on the stream to mark the stream as in a fail state
    }
  }
  else // if ch is EOF, then the stream is in a fail state, or there is no more characters in the stream,
    is.setstate(std::ios_base::failbit);          // fail the stream
  return retval;  // return the optional value retval with the suit, or without a value if the stream is in a fail state, or if ch is not a valid suit
}

//=============================================================================

//
// Provide a simple way to generate all playing cards without requiring 
// card_face, card_suit, playing_card, and all supporting operations to be
// written first.
//
std::string all_playing_cards_as_string()
{
  std::array<char,4> const special_face{ 'A', 'J', 'Q', 'K' };  // create an array of characters, special_face, with the values 'A', 'J', 'Q', 'K'
  std::array<char,4> const suit{ 'c', 'd', 'h', 's' };         // create an array of characters, suit, with the values 'c', 'd', 'h', 's'

  std::ostringstream buf; // create an output string stream, buf, to hold the string of all playing cards

  // generate all numeric face cards...
  for (int face=2; face != 11; ++face) // for each face value from 2 to 10, 
    for (auto const s : suit)         // for each suit, auto const s, in the array suit, 
      buf << face << s;              // append the face value and suit to the string stream, buf,

  // generate all special face cards...
  for (auto const f : special_face) // for each face value in the array special_face,
    for (auto const s : suit)      // for each suit in the array suit, auto const s, in the array suit,
      buf << f << s;              // append the face value and suit to the string stream, buf,

  // generate two jokers (red and white)...
  buf << "RW"; // append the two jokers to the string stream, buf,

  // return string...
  return buf.str(); // return the string of all playing cards in the string stream, buf, as a string, str()
}

//=============================================================================
