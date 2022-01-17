#include <iostream>
#include<vector>
#include<forward_list>
#include<string>
#include <fstream>
#include <algorithm>
using namespace std;

class Country{      //the country, and the city, and the populatioln.

    public:
    string countryName;
    vector<pair<string,int>> cityNpopualtion; //this is a vector that holds a city and its population in pairs
};

class CountryStats{

    public:
    string name_;
    int numcitiesinlist_;
    int totalpopulationinlist_;

    // Output the data in this CountryStats object by overloading the << operator
    friend ostream& operator<<(ostream& os, const CountryStats& cs){
        os<< "Country: "<< cs.name_ <<", Number of Cities in List: "<< cs.numcitiesinlist_<<", Total Population In List: "<< cs.totalpopulationinlist_<<endl;
        return os;
    }
};

class WorldCities
{
    forward_list<Country> countrylists_;
    // Create an output filestream object
    ifstream myFile; //Stream class to read from myFiles
    public:

    int getIndexFromCountries(vector<vector<vector<string>>> v, vector<vector<vector<string>>>::iterator x) //This function returns the position of a given iterator x
    {                                                                                                       //from the vector nCountries in PrintAllInSameCountry
        auto it = find(v.begin(), v.end(), *x);
        int index;
        // If element was found
        if (it != v.end())
        {
             index= it - v.begin(); // calculating the index of x
        }
        return index;
    }

    bool isCountryName(string country){   //a bool function that returns a true/false if a country name does exist in countrylists_
        for ( auto it : countrylists_ ){    // this it is type Country that iterates through the countrieslist_.
            if( it.countryName == country){ 
                return true;
            }
        }
        return false;
    }
    
    auto isCityName(string city, forward_list<Country>::iterator it){   //a pointer function that returns a bool true/false if a city name is in the given country inside the countrylists_
        for(int j =0; j < it->cityNpopualtion.size(); ++j){ //iterating through the city|pop pairs of the given country(it)- or iterating through the cities
            if( it->cityNpopualtion.at(j).first == city){ //if Country.pair.city.name == city, then return true
                return true;
            }
        }
        return false;
    }

    auto isCityName(string city){   //a pointer function that returns a pointer to a country if a city name is in that country inside the countrylists_
        
        for ( auto it = countrylists_.begin(); it != countrylists_.end(); ++it ){ //iteratoring through the countries in the countrylists_

            for(int i = 0 ; i < it->cityNpopualtion.size(); ++i ){ //iteratoring through the vector (cityNpopualtion) that contains city names
                
                string curCity = it->cityNpopualtion.at(i).first;
                if( curCity == city){ 
                    return true;
                }
            }
        }
        return false;
    }

    int getTotalPopulation(forward_list<Country>::iterator it){   //an int function that returns the total population of a given country with all its cities combined.
        int population = 0;             //declaring population variable to store all of the given countries population in

        for(int j = 0; j < it->cityNpopualtion.size(); ++j){ //iterating through the city|pop pairs of a specific country
            
            population += it->cityNpopualtion.at(j).second; // adding all of the countries population inside population.
        }
        return population;
    }

    std::forward_list<Country>::iterator getCountry(string country){   //an iterator function that returns the object of the given country name
        std::forward_list<Country>::iterator  x;
        for ( auto it = countrylists_.begin(); it != countrylists_.end(); ++it ){
            if( it->countryName == country){ 
                x = it;
            }
        }
        return x;
    }

    vector<string> getCityNamesFromCountryPtr(forward_list<Country>::iterator country){   //a function that uses a Country iterator to get all the city names inside a vector
        vector<string> cityNames;
            for(int i = 0 ; i < country->cityNpopualtion.size(); ++i ){ //iteratoring through the vector (cityNpopualtion) that contains city names
                string curCity = country->cityNpopualtion.at(i).first;
                cityNames.push_back(curCity);
            }
        return cityNames;
    
    }

    vector<CountryStats> PrintAllInSameCountry(string city, bool allcountries=false, bool alphabetical=false){

        //Global variables of this scope
        vector<CountryStats> countries;
        vector<vector<vector<string>>> nCountries; //vector that holds countires with their cities at an element {{country, {city1, city2...} }, {country, {city1, city2...}}  };
        vector<vector<string>> nCountry; // vector that holds a country and its cities {country, {city1, city2...}}
        vector<string> countryName; // string vectors of the city names {city1, city2...}

        for ( auto it = countrylists_.begin(); it != countrylists_.end(); ++it ){ //iteratoring through the countries in the countrylists_
            if (  isCityName(city, it) ){       // if the city name was found in the iterator it
                CountryStats CountryStats;      //declaring an object CountryStats

                vector<string> cityNames = getCityNamesFromCountryPtr(it); // takes all the cities and puts them in one vector

                CountryStats.name_ = it->countryName; // assigning CountryStats object name attribute
                CountryStats.numcitiesinlist_ = cityNames.size(); // assigning CountryStats object name attribute
                CountryStats.totalpopulationinlist_ = getTotalPopulation(it); // assigning CountryStats object name attribute

                countries.push_back(CountryStats);  //adding the country name first at the0th position.

                countryName.push_back(CountryStats.name_); //adding the county name to the countryName vector {CountryStats.name_}

                nCountry.push_back(countryName); //adding the countryName vector to the nCountry vector { {CountryStats.name_} }

                nCountry.push_back(cityNames); //adding the cityNames vector to the nCountry vector { {CountryStats.name_}, {city1, city2, city3 city4..} }
                nCountries.push_back(nCountry);//adding the cityNames vector to the nCountry vector { {{CountryStats.name_}, {city1, city2, city3 city4..}} , {{CountryStats.name_}, {city1, city2, city3 city4..}}  }

                countryName.clear();
                cityNames.clear();
                nCountry.clear();
            }
        }

//Printing Section
        if( !(nCountries.empty()) ){ // if we do have a country and its cities,

            cout<<"\n"<<"Loading data.."<<endl; //Prints Loading data to the user

            if(alphabetical == true){
                vector<vector<vector<string>>>::iterator xCountriesItr; // iterator for the nCountries vector - local to this scope
                for (xCountriesItr = nCountries.begin(); xCountriesItr != nCountries.end(); xCountriesItr++){ 

                    for(int i = 0; i< xCountriesItr->at(1).size(); ++i){

                        sort(xCountriesItr->at(1).begin(), xCountriesItr->at(1).end()); // sorting each set of cities alphabatically.
                    }
                }
                // sorts Country names alphabetical
                if(allcountries == true){
                    vector<vector<vector<string>>>::iterator firstCountriesItr; // iterator for the nCountries vector - local to this scope
                    int f = 0; // integers for indexing country names

                    for (firstCountriesItr = nCountries.begin(); firstCountriesItr != nCountries.end(); firstCountriesItr++){ 
                        int s = 0;
                        //change here VVVVVVV
                        string firstCountryName = firstCountriesItr->at(0).at(0); //getting the country name of the 'first' itreator

                        vector<vector<vector<string>>>::iterator secondCountryItr;

                        for(secondCountryItr = nCountries.begin() ; secondCountryItr != nCountries.end(); secondCountryItr++){

                            string secondCountryName = secondCountryItr->at(0).at(0); //getting the country name of the 'second' itreator
                            //if the first Country name was alphabatically bigger than the secondcountry name, then it moves to second while second replace to first.
                            if( firstCountryName.at(0) > secondCountryName.at(0) && (getIndexFromCountries(nCountries, firstCountriesItr)<getIndexFromCountries(nCountries, secondCountryItr)) ) {  //**
                                vector<vector<string>> tempCountriesItr = *secondCountryItr; // a temp iterator for the nCountries vector
                                *secondCountryItr = *firstCountriesItr;
                                *firstCountriesItr = tempCountriesItr;
                            }
                            if(firstCountryName.at(0) == secondCountryName.at(0) && ( getIndexFromCountries(nCountries, firstCountriesItr)<getIndexFromCountries(nCountries, secondCountryItr))){
                                if( firstCountryName.at(1) > secondCountryName.at(1)){
                                    vector<vector<string>> tempCountriesItr = *secondCountryItr; // a temp iterator for the nCountries vector
                                    *secondCountryItr = *firstCountriesItr;
                                    *firstCountriesItr = tempCountriesItr;
                                }
                            }
                            s++;
                        }
                        f++;
                    }
                }
            }

            if(allcountries == true){ // prints all the countries with the city name
                vector<vector<vector<string>>>::iterator nCountriesItr;
                for(nCountriesItr = nCountries.begin(); nCountriesItr != nCountries.end()  ;nCountriesItr++){
                    cout<<"\nCountry Name: "<<nCountriesItr->at(0).at(0)<<"\n"<< endl;

                    for(int c = 0 ; c<nCountriesItr->at(1).size(); c++){
                        //printing the city names
                        if( c != (nCountriesItr->at(1).size()-1) ){      //if the city isn't the last one in the list add a ,
                                cout << nCountriesItr->at(1).at(c) + ", ";
                        }
                        else{   //if the city is the last one in the list, end the line.
                            cout<<nCountriesItr->at(1).at(c)<<"."<<endl; 
                        } 
                    }
                }
            }

            if(allcountries == false){ // just prints one country with the city name
                vector<vector<vector<string>>>::iterator nCountriesItr = nCountries.begin(); // the first iterator for the nCountries vector - local to this scope
                cout<<"\n"<<(*nCountriesItr).at(0).at(0) << endl; //printing the country name

                vector<string> nCities = nCountriesItr->at(1);

                for(int j = 0; j< nCities.size(); j++){ // iteratinng through the cities j of a specific country i.

                    //printing the city names
                    if( !(j == ( nCities.size()-1 ) ) ) { cout << nCities.at(j) + ", "; } //if the city isn't the last one in the list add a ,

                    else{cout<<nCities.at(j)<<endl; } //if the city is the last one in the list, end the line.
                }
            }
        }

        if (  isCityName(city) == false ){
            cout<<"The city does not appear in the most-populated cities" << endl;
        }
        return countries;
   }
 
    bool ReadCSVFile(std::string filename="./WorldCities.csv"){ // Returns true if filename was a valid CSV file and was read in correctly, Returns false otherwise

        if( filename == "WorldCities.csv" && myFile.good()){
            return true;
        }
        else{ 
            return false;
        }
    }

    WorldCities(){  //constructor that opens WorldCities.csv and loads all the data 

        myFile.open("WorldCities.csv"); // openening myFiles - foo.csv
        string city, country, population;

        while ( ReadCSVFile("WorldCities.csv") ){ //while the file successfully opens

            getline(myFile, city, ','); // this reads first coloumn city
            getline(myFile, country, ','); // this reads second coloumn country
            getline(myFile, population); // this reads third  coloumn population

            //if the country doesnt exist in the list already, then create a country object and add it.
            if( isCountryName(country) == false ){    // if the country isn't in the countrylists_ then make a new Country
                Country oCountry;

                oCountry.countryName = country;  //adds the country name into the Country object
                oCountry.cityNpopualtion.push_back(make_pair(city, stoi(population))); //adds the city name and the city populatin into a vectr pair

                //adding Country in the countrylists_ at the begining
                countrylists_.push_front(oCountry);
            }
            //if the country exists in our list then no need to make a new object, just locate it and add cities
            else if( isCountryName(country) == true ){    // if the country is in the countrylists_ 

                std::forward_list<Country>::iterator iCountry;
    
                iCountry = getCountry( country);  
            // initilizing the Country pointer to the Country object */
                iCountry->cityNpopualtion.push_back(make_pair(city, stoi(population))); //adds the city name and the city populatin into a vectr pair inside the country
            }
            else{
                break;
            }
        }
        myFile.close();
    }
};

int main() {
    cout<<"\n"<<"Program started."<<endl;

    string city;
    cout<<"\n"<<"Please enter the city name to search: "; 
    cin>>city;

    cout<<"\n"<<"searching for: "<< city<<endl;
    WorldCities WorldCities;
    cout<<"\n"<<"Done reading data."<<endl;  

    vector<CountryStats> countries = WorldCities.PrintAllInSameCountry(city, true, true);
    if ( !(countries.empty()) ) {
        
        cout<<"\n========================== \n"<< city<<" was found in the following countries:"<<endl;
        for( int x = 0; x < countries.size(); ++x){
            cout<<"\n"<<countries.at(x);
        }
    }
    cout<<"\n"<<"Program done."<<endl;

    
    return 0;
}