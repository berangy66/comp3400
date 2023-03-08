#include<filesystem>
#include<fstream>
#include<iomanip>
#include<iostream>
#include<map>
#include<set> 
#include<vector>



#include "a4-provided.hpp"
#include "a5-provided.hpp"
#include "a4-include.hpp"

using namespace std::string_literals;

constexpr std::array suits{
  card_suit::clubs,
  card_suit::spades,
  card_suit::hearts,
  card_suit::diamonds
};

constexpr std::array faces_with_suits{
  card_face::ace, card_face::two, card_face::three, card_face::four,
  card_face::five, card_face::six, card_face::seven, card_face::eight,
  card_face::nine, card_face::ten, card_face::jack, card_face::knight,
  card_face::queen, card_face::king
};


//=============================================================================
// playing card company operator<=>() overload, for use with std::map and std::set, 
std::strong_ordering operator<=>(playing_card_company const& lhs, playing_card_company const& rhs)
{
    return lhs.name() <=> rhs.name();
}//End playing_card_company operator<=>()


//============================================================================== 
//struc/class pcc
struct pcc
{
  playing_card_company comp;
  playing_card card;
};//End struct pcc


// //=============================================================================
// // read_pcc() function definition,
std::optional<pcc> read_pcc(std::istream& is)
{

  std::optional<playing_card> card_variable{read_playing_card(is)}; //playing_card variable to be used to store the card,
  playing_card_company card_comp_variable; //playing_card_company variable to be used to store the company name,

  is >> card_comp_variable; //read in the company name,
  if(card_variable &&  (is >> card_comp_variable))
  {
      return pcc { card_comp_variable , *card_variable};
  }
  else
  {
      return std::nullopt;
  }
}//End read_pcc()


// std::optional<pcc> read_pcc(std::istream& is)
// {
//   std::optional<playing_card> card {read_playing_card(is)};
//   playing_card_company comp;

//   if(card.has_value() && (is >> comp))
//   {
//     return pcc { comp, *card };
//   }
//   else
//   {
//     return std::nullopt;
//   }
// }



//=============================================================================
// set<playing_card> generate_full_deck() function definition, each card is unique, except for the 2 jokers,
std::set<playing_card> generate_full_deck()
{
  std::set<playing_card> retval;

  for (auto const& f : faces_with_suits)
  {
    for (auto const& s : suits)
    {
      retval.insert({ f, s });
    }//End for loop for suits
  }//End for loop for faces_with_suits
  return retval;

}//End generate_full_deck() 



//=============================================================================
// **** Main function definition ****
int 
main(int argc, char* argv[])
{
    namespace fs = std::filesystem;


    //Check for correct number of command line arguments,check if name of program and path to file to be read provided,
    if(argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <path>\n";  
        return 1;
    }//End if statement for argc != 2,

    //Rading in all of the playing cards from the file
    std::map<playing_card_company , std::vector<playing_card>> all_cards ; //map of playing card companies and their cards which are stored in a vector,palying_card_company is sorted by name,

    fs::path const basedir{argv[1]}; //path to the directory to be created,

  for(auto const& entry: fs::directory_iterator(basedir, fs::directory_options::skip_permission_denied))
  {
    
    std::ifstream  entryPath{entry.path().native()}; //open the entry file for reading,from the command line argument, with entry.path().native() being the path to the file with native() being the native path string,
   // auto const& datum = datume.has_value(entryPath); );
     for(auto datume = read_pcc(entryPath); datume.has_value(); datume = read_pcc(entryPath)) //read in the playing cards from the file,
      {
        all_cards[datume->comp].push_back(datume->card);
      }//End for loop for reading in the playing cards from the file,
  }//End for loop for reading in the playing cards from the directory,

    //output the Total number of cards in the deck,
    std::size_t Total_number_of_cards{0};
    for(auto const& entry : all_cards)
    {
      Total_number_of_cards += entry.second.size();
    }
      std::cout << "Total number of cards read in: " <<  Total_number_of_cards << '\n'; //print the total number of cards 
      std::cout << "Total number of companies read in: " << all_cards.size() << '\n'; //print the total number of companies

    //output the Total number of companies
    for(auto const& entry : all_cards)
    {
     std::cout <<"  " <<quoted(entry.first.name()) << "\n";
    
    }

    
    //output the Total number of cards in the deck for each company,
    for(auto const& entry : all_cards )
    {
         std::cout << "\n  " << std::quoted(entry.first.name()) << "card stats:\n";  
        std::cout << "Total Number of cards in the deck  " << entry.second.size() << '\n'; //print the total number of cards in the deck,"
  
   
  
    //Determining the Number of Decks and Missing Cards
    std::vector<std::set<playing_card> > decks; //vector of sets of playing cards, each set is a deck,
  
    for(auto const& card : entry.second)
    {
      
    }
  
  }//End for loop for printing the number of companies in the map,
    
    return 0; //return 0 to indicate success,
}//End function main() 
