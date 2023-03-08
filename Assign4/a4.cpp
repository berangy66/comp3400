#include <algorithm>                // e.g., for std::shuffle
#include <compare>                  // e.g., for operator<=>
#include <iostream>                 // e.g., for std::cout, std::clog
#include <istream>                  // e.g., for std::istream
#include <iterator>                 // e.g., for std::inserter
#include <optional>                 // e.g., for std::optional
#include <ostream>                  // e.g., for std::ostream
#include <random>                   // e.g., for std::random_device
#include <set>                      // e.g., for std::set
#include <stdexcept>                // e.g., for std::domain_error
#include <string>                   // e.g., for std::string
#include <type_traits>              // e.g., for std::underlying_type_t
#include <vector>  

#include "a4-provided.hpp"


//Writing read_card_face()
std::optional<card_face> read_card_face(std::istream& is)
{
      std::optional<card_face> retval;
      auto ch = is.get();
       if (!std::istream::traits_type::eq_int_type(ch,std::istream::traits_type::eof()))
    {
        switch(ch)
        {
            
            case '2':
                retval = card_face::two;
                break; 
            case '3':
                retval = card_face::three; 
                break;
            case '4':
                retval = card_face::four;
                break; 
            case '5':
                retval = card_face::five; 
                break;      
             case '6':
                retval = card_face::six; 
                break;  
                 case '7':
                retval = card_face::seven; 
                break;   
                case '8':
                retval = card_face::eight; 
                break;   
                case '9':
                retval = card_face::nine; 
                break;   
                case 'J':
                retval = card_face::jack; 
                break;   
                case 'A': 
                retval = card_face::ace; 
                break; 
                case 'Q':
                retval = card_face::queen; 
                break;  
                 case 'K':
                retval = card_face::king; 
                break;  
                 case 'C':
                retval = card_face::knight; 
                break;  
                 case 'R':
                retval = card_face::red_joker; 
                break;  
                  case 'W':
                retval = card_face::white_joker; 
                break;  
                case '1':
                 // auto ch2 = is.get();
                  if(auto ch2 = is.peek(); ch2 == '0')
                  {
                      retval = card_face::ten;
                      is.ignore();
                  }
                  else
                  {
                      is.unget();
                     
                  }
                break;
             default:
        is.unget();                               // return ch to stream
        is.setstate(std::ios_base::failbit);      // fail the stream
    }
  }
  else
    is.setstate(std::ios_base::failbit);          // fail the stream
  return retval;
}

std::istream& operator>>(std::istream& is, card_face& s)
{
    std::optional<card_face> cf = read_card_face(is);
    if(cf.has_value())
    {
        s = cf.value();
    }
    return is;
}//end operator>>(std::istream& is, card_face& s


std::ostream& operator<<(std::ostream& os, card_face const& s)
{
    switch (s)
    {
    case card_face::two:
      os<<'2';
      break;
    case card_face::three:
      os<<'3';
      break;
    case card_face::four:
      os<<'4';
      break;  
    case card_face::five:
      os<<'5';
      break;  
    case card_face::six:  
      os<<'6';
      break;  

    case card_face::seven:  
      os<<'7';
      break;  

    case card_face::eight:
      os<<'8';
      break;  

    case card_face::nine: 
      os<<'9';
      break;

    case card_face::ten:
      os<<"10";
      break;

    case card_face::jack:
      os<<'J';
      break;
      case card_face::ace:
      os<<'A';
      break;
      case card_face::knight:
      os<<'C';
      break;

    case card_face::queen:
      os<<'Q';
      break;

    case card_face::king:
      os<<'K';
      break;

    case card_face::red_joker:
      os<<'R';
      break;

    case card_face::white_joker:
      os<<'W';
      break;
    }//end switch
    return os;
}//end operator<<


//playing_card class
class playing_card
{
  private:
  card_face cardface;
  std::optional<card_suit> cardsuit;

public:
  playing_card() = delete; 
 playing_card(card_face const& f, std::optional<card_suit>const& s = std::nullopt) : cardface{f}, cardsuit{s}
  {
      if( !cardsuit.has_value()  && cardface != card_face::red_joker && cardface != card_face::white_joker)
      {
          throw std::domain_error("Playing card without suit must be a joker");
      }
  }//end playing_card

  card_face const& face() const 
  {
      return cardface;
  }//end face

  bool has_suit() const
  {
      return cardsuit.has_value();
  }//end has_suit

   card_suit const& suit() const
  {
    return cardsuit.value();
  }//end suit

  friend bool operator==(playing_card const&, playing_card const&) = default;
  friend std::strong_ordering operator<=>(playing_card const&, playing_card const&) = default; 
};//end playing_card


std::optional<playing_card> read_playing_card(std::istream& is)
{
    std::optional<playing_card> retval;
    auto face = read_card_face(is);
    if(face.has_value() )
    {
      if( face.value() != card_face::red_joker && face.value() != card_face::white_joker)
      {
        auto suit = read_card_suit(is);
        if(suit.has_value())
        {
         retval = playing_card(face.value(), suit.value());

        }
      }
        else
        {
            retval = playing_card(face.value());
        }
    }
    if(!retval)
    {
      is.setstate(std::ios_base::failbit);
    }
    return retval;
}//end read_playing_card


std::istream& operator>>(std::istream& is, playing_card& c)
  {
      std::optional<playing_card> card = read_playing_card(is);
      if(card.has_value())
      {
          c = card.value();
      }
      return is;
  }//end operator>>


std::ostream& operator<<(std::ostream& os, playing_card const& c)
{
    os<<c.face();
    if(c.has_suit())
    {
        os<<c.suit();
    }
    return os;
}//end operator<<



//****** MAIN FUNCTION ******//
//Writing read_card_suit()
int main()
{
  using namespace std;

  // declare a vector to hold a deck of cards read cards from cin...
  vector<playing_card> deck;
  while (auto card = read_playing_card(cin))
    deck.push_back(*card);

  // output the playing cards read in from cin to clog...
  clog << "DEBUG: " << deck.size() << " playing_cards: ";
  for (auto const& e : deck)
    clog << e;
  clog << '\n';

  // using std::random_device, instantiate a Mersenne Twister RNG...
  random_device rd;
  mt19937 rg(rd());

  // declare a set to hold playing cards sorted...
  set<playing_card> s;

  // and select up to 5 cards without replacement from deck for s...
  sample(deck.begin(), deck.end(), inserter(s, s.end()), 5, rg);

  // output the sampled cards...
  cout << "cards: ";
  for (auto const& e : s)
    cout << e << ' ';
  cout << '\n';
}//end main