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
#include <vector>                   // e.g., for std::vector

#include "a4-provided.hpp



//Writing read_card_face()

std::optional<card_face>  read_card_face(std::istream& is)
{
    std::optional<card_face> retval; 
    auto ch = is.get();

    if(ch != std::istream::traits_type::eof())
    {
        switch(ch)
        {
            case 'A': 
                retval = card_face::ace; 
                break; 
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
             case '5':
                retval = card_face::five; 
                break;     
                 case '6':
                retval = card_face::six; 
                break;   case '7':
                retval = card_face::seven; 
                break;   case '8':
                retval = card_face::eight; 
                break;   case '9':
                retval = card_face::nine; 
                break;   case 'J':
                retval = card_face::jack; 
                break;   case 'Q':
                retval = card_face::queen; 
                break;   case 'K':
                retval = card_face::king; 
                break;   case 'C':
                retval = card_face::knight; 
                break;  
                 break;   case 'R':
                retval = card_face::red_joker; 
                break;  
                 break;   case 'W':
                retval = card_face::white_joker; 
                break;  
        }
    }
}








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
}