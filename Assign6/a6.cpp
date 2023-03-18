#include <algorithm>  // e.g., std::for_each, std::sort, std::find
#include <cstddef>    // e.g., std::size_t
#include <functional> // e.g., std::greater
#include <fstream>    // e.g., std::ifstream
#include <iterator>   // e.g., std::iterator_traits, std::forward_iterator
#include <iostream>   // e.g., std::cout, std::clog
#include <map>        // e.g., std::map
#include <set>        // e.g., std::set
#include <string>     // e.g., std::string
#include <vector>     // e.g., std::vector

//==============================================================================
// Writing output() function prototype:
template <std::forward_iterator FwdIter>
std::ostream &output( std::ostream &os,FwdIter first, FwdIter last,bool const with_indices = false) 
{ 
    using count_type = typename std::iterator_traits<FwdIter>::difference_type;
    count_type index = 0;                           // index is a forward iterator
    count_type rindex = std::distance(first, last); // rindex
    std::for_each(first, last, [&os, &index, &rindex, &with_indices ](auto const& value)
    {//can Use '[&]' instead of [&os, &index, &rindex, &with_indices ] Capture any variables defined outside the lambda function by reference.
        os << value; 
        if (with_indices) { os << '(' << index << ':' << -rindex + 1 << ')'; }
       os << ' ';
        index++;
        --rindex;
    });

     return os;
};
//==============================================================================
// Handling main()'s Arguments and Reading In Data
//==============================================================================
int main(int argc, char *argv[])
{
    // Check for correct number of command line arguments,check if name of program and path to file to be read provided,
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <text_file_path>\n";
        return 1;
    } // End if statement for argc != 2,

    std::ifstream ifs{argv[1]}; // open the file for reading,
    if (!ifs.is_open())
    {
        std::cerr << "Error: could not open file " << argv[1] << " for reading" << '\n';
        return 1;
    }

    std::map<std::string,std::size_t> hist;
    std::vector<std::string> revwords;

    //==============================================
    // reading in all the words
    // and fill the vector and histogram
    //=================================================
    for (std::string read_in; ifs >> read_in;)
    {
        ++hist[read_in];
        //++hist.insert({read_in,1}).first; //it should be equiv to : line 69 ++hist[read_in];
        revwords.push_back(read_in); 
    }
    ifs.close(); 
    if (revwords.empty())
        {
            std::cerr << "There is no data.Aborting\n";
            return 2;
        }

    //====================
    // Reversing The words
    std::vector<std::string> rv;
    std::reverse_copy(revwords.begin(), revwords.end(), std::back_inserter(rv));

    //===================
    // Computing the Inverse Frequency Histogram

    std::map<std::size_t, std::set<std::string >> inv_freq_hist;
    std::map<std::string, std::size_t>::const_iterator i = hist.begin();
	std::map<std::string, std::size_t>::const_iterator i_end = hist.end();
	for (; i != i_end; ++i)
    {
      inv_freq_hist.insert(std::make_pair(i->second, std::set<std::string>())).first->second.insert(i->first);
    }

    auto smallest_pos = std::min_element(inv_freq_hist.begin(), inv_freq_hist.end(), [](auto& a, auto& b){ return a.second.size() < b.second.size(); });
    std::cout << "frequency " << smallest_pos->first << " occurs with these strings: ";
    output(std::cout, smallest_pos->second.begin(), smallest_pos->second.end()) << '\n';
    
    std::string lo_value = *smallest_pos->second.begin();
    std::string hi_value = *std::prev(smallest_pos->second.end());
    std::cout << "lo value: " << lo_value << '\n';
    std::cout << "hi value: " << hi_value << '\n';

//=================================================================================================
//Finding the First Position "lo" Appears in revwords + an Adjustment
//==========================================================================
    auto lopos = std::find(rv.begin(), rv.end(), lo_value );
    if(lopos != rv.end())
    {
        ++lopos ; //adjustment
      
    }
      lopos = std::find_if_not(lopos, rv.end(), [&lo_value](auto const& value) { return value == lo_value;});

        auto lo_index = std::distance(rv.begin(), lopos) ;
//=================================================================================================
//Finding the First Position "hi" Appears in revwords + an Adjustment
//==========================================================================
   
    auto rhipos = std::find_end(rv.rbegin(), std::reverse_iterator(lopos), &hi_value, &hi_value + 1);
    if(rhipos != std::reverse_iterator(lopos)){ ++rhipos;}
    auto hi_index = std::distance(rv.begin(), rhipos.base())  ;

//=================================================================================================
//Sorting in Descending Order
//=========================================================================
    std::sort(lopos,rhipos.base(), std::greater<>());
   
//=================================================================================================
//Producing the Final Outputs
//==========================================================================
    std::cout << "All words reversed: ";
    output(std::cout, revwords.rbegin(), revwords.rend(), true);
    std::cout << '\n';
    std::cout << "All words reversed with [" << lo_index << ',' << hi_index << ") sorted: ";
    output(std::cout, rv.begin(),  rv.end(), false);
    std::cout << '\n';

return 0;
}// End of main() function














