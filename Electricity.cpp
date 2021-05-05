#include <iostream>
#include <fstream>

using namespace std;

const int ARRAY_LENGTH = 18; //No. of registers.
const int CATEGORIES = 7; //all, coal, nat. gas, nuclear, hydro, wind, solar.

void report(std::string year);
void yearOfPeakProduction(std::string category);
void writeCSV(std::string category);
void loadArrays(std::ifstream &file, std::string years[], std::string categories[], double * all_fuels_vals, double * coal_vals, double * natural_gas_vals, double * nuclear_vals, double * hydroelectric_vals, double * wind_vals, double * solar_vals);

int main(int argc, const char * argv[]){
    
    string command;
    bool validInput = false;

    //Arrays
    std::string years[ARRAY_LENGTH];
    std::string categories[CATEGORIES] = {"all fuels", "coal", "natural gas", "nuclear", "hydroelectric", "wind", "solar"};
    double all_fuels_vals[ARRAY_LENGTH];
    double coal_vals[ARRAY_LENGTH];
    double natural_gas_vals[ARRAY_LENGTH];
    double nuclear_vals[ARRAY_LENGTH];
    double hydroelectric_vals[ARRAY_LENGTH];
    double wind_vals[ARRAY_LENGTH];
    double solar_vals[ARRAY_LENGTH];

    //Command prompt
    std::cout << "Please enter one of the following options:" << std::endl;
    std::cout << "a\tDisplay a report showing the energy source, the energy produced and the percentage of the energy for all fuels for a given year\n";
    std::cout << "b\tDisplay the year in which the peak production (and amount) of electricity occurred for any of the 7 categories\n";
    std::cout << "c\tCreate an output data file\n";

    while(1){
        //Open file
        std::ifstream file("Electricity.txt");
        std::cout << "$ ";
        getline(cin, command);
        if(file.is_open()){
            //Load file
            //Passing arrays to be initialized in loadFile() function
            loadArrays(file, years, categories, all_fuels_vals, coal_vals, natural_gas_vals, nuclear_vals, hydroelectric_vals, wind_vals, solar_vals);
            
            if((command.find("a") | command.find("A")) != string::npos){
                std::cout << "Please enter the year:" << std::endl;
                std::string year;
                getline(cin, year);
                try{
                    //Validate year
                    for(int i = 0; i < ARRAY_LENGTH; i++){
                        if(year == years[i])
                            validInput = true;
                    }
                    if(!validInput){
                        throw std::runtime_error("year not valid");
                    }

                    //report(std::string year);
                }
                catch(std::exception e){
                    std::cout << "It was not possible to display a report: " << e.what() << std::endl;
                }
            }
            std::string category;
            if((command.find("b") | command.find("B")) != string::npos){
                std::cout << "Please enter the category:" << std::endl;
                getline(cin, category);
                try{
                    //Validate category
                    for(int i = 0; i < CATEGORIES; i++){
                        if(category == categories[i])
                            validInput = true;
                    }
                    if(!validInput){
                        throw std::runtime_error("category not valid");
                    }

                    //yearOfPeakProduction(std::string category);
                }
                catch(std::exception e){
                    std::cout << "It was not possible to display the year of peak production: " << e.what() << std::endl;
                }
            }
            if((command.find("c") | command.find("C")) != string::npos){
                std::cout << "Please enter the category for which you want a csv file:" << std::endl;
                getline(cin, category);
                try{
                    //Validate category
                    for(int i = 0; i < CATEGORIES; i++){
                        if(category == categories[i])
                            validInput = true;
                    }
                    if(!validInput){
                        throw std::runtime_error("category not valid.");
                    }

                    //writeCSV(std::string category);
                }
                catch(std::exception e){
                    std::cout << "It was not possible to create the file: " << e.what() << std::endl;
                }
            }
        }
        else{
            std::cout << "File could not be loaded" << std::endl;
        }
    }
    return 0;
}

void report(std::string year){}

void yearOfPeakProduction(std::string category){}

void writeCSV(std::string category){}

void loadArrays(std::ifstream &file, std::string years[], std::string categories[], double * all_fuels_vals, double * coal_vals, double * natural_gas_vals, double * nuclear_vals, double * hydroelectric_vals, double * wind_vals, double * solar_vals){
    std::string line;
    int lineIndex = 0;
    while(getline(file, line)){
        //Extract data
        if(line[0] == '2'){
            std::size_t index = line.find('\t');
            //Year
            years[lineIndex] = line.substr(0, index);
            index += 1;
            line = line.substr(index, '\n');
            //All fuels
            all_fuels_vals[lineIndex] = std::stod(line.substr(0, line.find('\t')));
            index = line.find('\t') + 1;
            line = line.substr(index, '\n');
            //Coal
            coal_vals[lineIndex] = std::stod(line.substr(index, line.find('\t')));
            index = line.find('\t') + 1;
            line = line.substr(index, '\n');
            //Natural gas
            natural_gas_vals[lineIndex] = std::stod(line.substr(index, line.find('\t')));
            index = line.find('\t') + 1;
            line = line.substr(index, '\n');
            //Nuclear
            nuclear_vals[lineIndex] = std::stod(line.substr(index, line.find('\t')));
            index = line.find('\t') + 1;
            line = line.substr(index, '\n');
            //Hydroelectric
            hydroelectric_vals[lineIndex] = std::stod(line.substr(index, line.find('\t')));
            index = line.find('\t') + 1;
            line = line.substr(index, '\n');
            //Wind
            wind_vals[lineIndex] = std::stod(line.substr(index, line.find('\t')));
            index = line.find('\t') + 1;
            line = line.substr(index, '\n');
            //Solar
            solar_vals[lineIndex] = std::stod(line.substr(index, line.find('\n')));
            
            //PRUEBA
            std::cout << years[lineIndex] << '\t';
            std::cout << all_fuels_vals[lineIndex] << '\t';
            std::cout << coal_vals[lineIndex] << '\t';
            std::cout << natural_gas_vals[lineIndex] << '\t';
            std::cout << nuclear_vals[lineIndex] << '\t';
            std::cout << hydroelectric_vals[lineIndex] << '\t';
            std::cout << wind_vals[lineIndex] << '\t';
            std::cout << solar_vals[lineIndex] << std::endl;
        }
    }
    
}