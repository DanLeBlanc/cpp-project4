#define strtk_no_tr1_or_boost

#include <string>
#include <vector>
#include "strtk.hpp"
#include <string.h>
// Dan LeBlanc 040749264 
/**
* CSV Parser
*
* This header file is a general purpose csv parser. The functions of 
* note to the user are read_file(std::string&) and parse_data_set(std::string&).
* The read_file function returns contents of a text file as a std::string, which 
* can then be fed into the parse_data_set function, which will return a list
* of maps, with column names as keys and column data as values. These maps 
* can then easily be built into the object type of your choice, if you so desire.
*
* This header makes use of the strtk library.
*
* @author Dan LeBlanc
* @studentno 040479264
*/

/**
* Seperate Strings
*
* Function from the string.h library but can require defines that do not always 
* work, so I've copied the source code.
*
* https://stackoverflow.com/questions/58244300/getting-the-error-undefined-reference-to-strsep-with-clang-and-mingw
*
* @param stringp char array to be parsed and delimited
* @param delim delimiter character, for example ','
*
* @return char * array of characters between delimiters
*/
char *strsep(char **stringp, const char *delim) {
    char *rv = *stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0; }
    return rv;
}

/**
* String to Char Array
*
* Takes a std::string and converts it into an array of characters.
*
*  @param arg std::string to be converted into character array
*  @return character array of std::string
*/
char *string_to_char_array(std::string& arg) {
    char * char_array = new char[arg.length()+1];
    strcpy(char_array, arg.c_str());
    return char_array;
}

/**
* Map a row
*
* Function to turn two arrays into a key, value pair map. Used to pair
* names of columns with their values.
*
* @param column_names a std::vector containing strings that are names of columns
* @param column_values a std::vector containing strings that are the data for these columns
* @return a map containing key, value pairs of the column names and data
*/
std::unordered_map<std::string, std::string> map_row(std::vector<std::string>& column_names, std::vector<std::string>& column_values){
    // Dan LeBlanc 040749264
    std::unordered_map<std::string, std::string> mapped_row;
    // Dan LeBlanc 040749264
    for (int k = 0; k < column_names.size(); k++) {
        // Dan LeBlanc 040749264
        mapped_row.insert({column_names[k], column_values[k]});
    }
    // Dan LeBlanc 040749264
    return mapped_row;
}

/**
* Parses a CSV
*
* Parses a CSV. Pass in a std::string representation of a csv file and receive
* a list of maps back that have column names as keys and column data as values.
*
* Found syntax for some of these operations from:
* https://stackoverflow.com/questions/20302014/parsing-csv-file-with-missing-entries
*
* @param data std::string representation of a csv file
* @return a list of maps containing column names as keys and column data as values.
*/
std::vector<std::unordered_map<std::string, std::string>> parse_data_set(std::string& data) {
    // Dan LeBlanc 040749264
    std::istringstream lines(data);
    // Dan LeBlanc 040749264
    std::string line;
    // Dan LeBlanc 040749264
    char * field;
    // Dan LeBlanc 040749264
    std::vector<std::string> column_names;
    // Dan LeBlanc 040749264
    std::vector<std::string> column_values;
    // Dan LeBlanc 040749264
    std::vector<std::unordered_map<std::string, std::string>> map_list;
    // Dan LeBlanc 040749264
    int i = 0;
    // pushes a line out of the collection of lines on each iteration
    // until none remain
    while (std::getline(lines, line)) {
        // Dan LeBlanc 040749264
        char * buff = string_to_char_array(line);
        // Dan LeBlanc 040749264
        // gets each field in the row
        while ((field = strsep(&buff, ",")) != NULL) {
            if (i == 0) {
                // Dan LeBlanc 040749264
                // get column names
                column_names.push_back(field);
            } else {
                // Dan LeBlanc 040749264
                // get data
                column_values.push_back(field);
            }
        }
        if (i > 0){
            // only do this after one iteration so we don't 
            // have a row that's just column names
            map_list.push_back(map_row(column_names, column_values));
        }
        // buff is declared as a pointer and is therefore on the heap, to avoid
        // memory issues we have to manually clean it up each cycle
        delete[] buff;
        // clear column_values so we don't end up pushing more onto the end 
        // of a pre-existing list
        column_values.clear();     
        i++;   
    }
    return map_list;
}

/**
* Read a file
*
* Reads a text file by giving it the path to the file as a std::string.
*
* Found syntax for this at:
* https://stackoverflow.com/questions/20902945/reading-a-std::string-from-file-c
*
*  @param filepath path to file
*  @return the text files contents as a string
*/
std::string read_file(std::string& filepath) {
    std::ifstream input_stream(filepath, std::ios_base::binary);

    if (input_stream.fail()) throw std::runtime_error("Error opening file");

    std::stringstream buffer;
    buffer << input_stream.rdbuf();

    return buffer.str();
}