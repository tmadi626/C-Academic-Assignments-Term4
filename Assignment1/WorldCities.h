#include<iostream>
#include<forward_list>
#include<vector>
using namespace std;

class WorldCities
{
    std::forward_list<Country> countrylists_;
    public:

std::vector<CountryStats> PrintAllInSameCountry(std::string city, bool allcountries, bool alphabetical);
/* Outputs all cities in the same country (countries) as city to standard output. The country name
should first be output to a single line and then all cities in that country on the next line, each city name
separated by a comma from the next, except for the last city, which is followed by a newline character.

If allcountries is true, then all cities in all countries where a city by the same name appears in the list,
should be output to standard output in the same format as just described above. Otherwise, any country
with that city name should have all its cities output to standard output.

If alphabetical is true, then the cities in each country should be output to standard output in standard
alphabetical order

If alphabetical is false, then the cities for each country can be output to standard output in any order,
though cities in the same country should still be grouped together.

If both allcountries and alphabetical are true, then the cities in each country should be output to
standard output in standard alphabetical order, while the ordering of countries should also be
alphabetical.

If the city is not present in the CSV file, then the following message should be output to standard
output: “The city does not appear in the most-populated cities list”
*/

bool ReadCSVFile(std::string filename="./WorldCities.csv");
// Returns true if filename was a valid CSV file and was read in correctly
// Returns false otherwise
};