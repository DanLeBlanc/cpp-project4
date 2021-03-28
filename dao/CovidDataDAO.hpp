#include "../model/CovidDataSet.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

// helper function, found at:
// http://www.lonecpluspluscoder.com/2015/08/13/an-elegant-way-to-extract-keys-from-a-c-map/
std::vector<std::string> extract_keys(std::map<std::string, std::string> const& input_map) {
  std::vector<std::string> retval;
  for (auto const& element : input_map) {
    retval.push_back(element.first);
  }
  return retval;
}

/**
* DAO for CovidDataSets
*
* The DAO for CovidDataSets. Provide a list of CovidDataSet objects to perform
* data operations on them.
*
* @author Dan LeBlanc
* @studentno 040749264
*/
class CovidDataDAO {
    std::vector<CovidDataSet> cds_list;
    std::vector<CovidDataSet> old_list;

public:
    // set old_list and don't modify it, used for data recovery
    CovidDataDAO(std::vector<CovidDataSet> arg) {
        cds_list = arg;
        old_list = arg;
    }
    std::vector<CovidDataSet> get_list() {return cds_list;}
    void set_list(std::vector<CovidDataSet> arg) {cds_list = arg;}
    CovidDataSet& get_record(size_t row_number) {return cds_list[row_number];}

    /**
    * Print a table of CovidDataSets
    * 
    * Prints a table of Covid Data Set objects given an argument list for the 
    * number of columns requested.
    *
    * @param covid_data_set_list a vector of CovidDataSet objects
    * @param number_of_columns number of columns to print
    * @param start the number to start printing rows on
    */
    void display_records(size_t row_start, size_t num_of_rows, int num_of_columns) {
        if (row_start > cds_list.size() || row_start + num_of_rows > cds_list.size())
            throw std::runtime_error("Error: Tried to print past max number of rows.");
        if (num_of_columns > TOTAL_COLUMNS) 
            throw std::runtime_error("Number of columns to print exceeds columns in dataset.");
        size_t i = row_start;
        int column_print = i;
        // +1 or else it only prints column names given an arg of 1
        for (; i < row_start+num_of_rows+1; i++) {
            // print row number
            if (i == row_start) std::cout << "Row#";
            // -1 so first row is labeled 0
            else std::cout << std::setw(4) << i-1;
            // print column names first
            if (i == column_print) {
                std::vector<std::string> column_names;
                column_names = cds_list[i].get_column_names();

                for (size_t j = 0; j < num_of_columns; j++) { 
                    std::cout << std::setw(12) << column_names[j];
                }
                // line break
                std::cout << std::endl;
            } else {
                // print data
                CovidDataSet cds = cds_list[i-1];
                for (size_t k = 0; k < num_of_columns; k++) {
                    // Found syntax for this at:
                    // https://stackoverflow.com/questions/46527961/storing-functions-from-class-in-array-and-invoke-them-c
                    std::string data = (cds.*cds.column_data[k])();
                    // truncate size if too large for better visualization
                    if (data.size() > 10) data = data.substr(0,10);
                    std::cout << std::setw(12) << data;
                }
                // line break
                std::cout << std::endl;
            }
        }
    }

    /**
    * Reload data
    * 
    * Reloads data that was initially provided to the DAO.
    */
    void reload_data() {
        cds_list = old_list;
    }

    /**
    * Save data to disk
    *
    * Writes the current list to the disk as a CSV, with filename being the name of the file.
    *
    * @param filename the name of the file you are to create
    */
    // https://www.cplusplus.com/doc/tutorial/files/
    void save_to_disk(std::string& filename){
        std::ofstream csv_file;
        csv_file.open(filename);

        int size = cds_list[0].get_column_names().size();

        for (size_t i = 0; i < size; i++){
            csv_file << cds_list[0].get_column_names()[i];
            // add comma if not at end of row
            if (i < size-1) csv_file << ",";
        }
        // Dan LeBlanc 040749264
        csv_file << "\n"; // add new line to start values

        for (CovidDataSet cds : cds_list) {
            for (size_t i = 0; i < size; i++) {
                csv_file << (cds.*cds.column_data[i])();
                if (i < size-1) csv_file << ",";
            }
            csv_file << "\n"; // add new line
        }
        csv_file.close();
    };

    /**
    * Create a CovidDataSet record
    * 
    * Adds a record to the end of the current list of data.
    * 
    * @param cds the record to be added to the list
    * @return the index position of the inserted record
    */
    size_t create_record(CovidDataSet cds){
        cds_list.push_back(cds);
        // return position it was inserted into
        return cds_list.size()-1;
    }

    /**
    * Edit a record
    * 
    * Edits a record retrieved from the current list of data, given a row number, column number and
    * new data to be replaced.
    * 
    * @param row_num the row number of the record to be edited, 0 indexed
    * @param column the name of the column to be edited
    * @param value the new data to be in the column at the specified row
    */
   // Dan LeBlanc 040749264
    CovidDataSet edit_record(size_t row_num, int column_num, std::string& value){
        CovidDataSet& cds = get_record(row_num);
        (cds.*cds.set_columns[column_num])(value);
        return cds;
    }

    /**
    * Delete a record
    *
    * Deletes a record at the specified row.
    *
    * @param row_number the number of the row to be deleted, 0 indexed 
    */
    // http://www.cplusplus.com/reference/vector/vector/erase/
    void delete_record(size_t row_number) {
        if (row_number > cds_list.size()-1) 
            throw std::runtime_error("Row number exceeds members in dataset.");
        // function takes an iterator, so we plug in .begin() before
        cds_list.erase(cds_list.begin() + row_number);
    }

    std::vector<CovidDataSet> search(std::map<std::string, std::string> criteria) {
        std::vector<std::string> keys = extract_keys(criteria);
        std::vector<CovidDataSet> result_list;

        for (CovidDataSet cds : cds_list) {
            for (int i = 0; i < keys.size(); i++) {
                int col_num = cds.exists(keys[i]);
                // if a bad column, exit
                if (col_num == -1) throw std::runtime_error("Column does not exist.");

                // if our chosen column matches the data in the map
                if ((cds.*cds.column_data[col_num])() == criteria[keys[i]]) {
                    // if we get to the end of the keys list and we're still matching, it's a match
                    // and we can add it to our list
                    if (i == keys.size()-1) result_list.push_back(cds);
                } else {
                    // will exit the inner loop on first bad match
                    break;
                }
            }
        }

        return result_list;
    }

    /**
     * Sorting class for CovidDataSets.
     * 
     * A utility class that can be used to sort CovidDataSets by various means. 
     * 
     */
    class Sorter {
        std::vector<CovidDataSet> list;

    public:
        Sorter(std::vector<CovidDataSet> arg) {list = arg;}

        /**
         * Check if column exists
         * 
         * Checks if a column by the name of column_name exists.
         * 
         * @param column_name the name of the column to check for
         * 
         * @return the place of the column as integer, or -1 if not found
         */
        int check_exists(std::string column_name) {
            CovidDataSet cds;
            int column_num = cds.exists(column_name);

            if (column_num == -1) {
                throw std::runtime_error("Column does not exist.");
            }
            
            return column_num;
        }

        /**
         * Sort the list numerically.
         * 
         * Sorts the CovidDataDAO internal list numerically by column name, using a provided function.
         * 
         * @param column_name name of the column to sort by
         * @param func the boolean function by which to sort
         * 
         * @return the sorted list
         */
        std::vector<CovidDataSet> sort_numeric(std::string column_name, bool(func)(CovidDataSet, CovidDataSet, int)){
            int column_num = check_exists(column_name);
            // we use std::bind to get the column_num arg in there too so we know what to compare
            std::sort(list.begin(), list.end(), 
                std::bind(func, std::placeholders::_1, std::placeholders::_2, column_num));
            return list;
        }

        /**
         * Sort by province.
         * 
         * Sorts the CovidDataDAO internal list by province.
         * 
         * @param pruid the PRUID of the province to sort the list by
         * 
         * @return the sorted list
         */
        std::vector<CovidDataSet> sort_province(std::string pruid){
            std::vector<CovidDataSet> new_list;
            for (CovidDataSet cds : list) {
                if (pruid == cds.get_pruid()) new_list.push_back(cds);
            }
            return new_list;
        }

        /**
         * Sort by lesser than.
         * 
         * Sort a column by all values that are less than the argument num.
         * 
         * @param column_name column to sort by
         * @param num upper bound of numbers to keep
         * 
         * @return the sorted list
         */
        std::vector<CovidDataSet> less_than(std::string column_name, int num) {
            int column_num = check_exists(column_name);

            std::vector<CovidDataSet> new_list;

            for (CovidDataSet cds : list) {
                std::string value = (cds.*cds.column_data[column_num])();
                // set to 0, if value is empty it'll stay 0 so we don't get stoi errors
                int x = 0;
                if (!value.empty()) x = std::stoi(value);
                if (x < num) {
                    new_list.push_back(cds);
                }
            }

            return new_list;
        }

        /**
         * Sort by date descending.
         * 
         * Sorts the list by dates in reverse order.
         * 
         * @return the sorted list
         */ 
        std::vector<CovidDataSet> date_descending() {
            std::reverse(list.begin(), list.end());

            return list;
        }

    };

    Sorter sorter() {return Sorter(cds_list);}
    
};

/**
 * Function for sorting by ascending.
 * 
 * Pass this function to sort_numerical to sort by ascending values.
 * 
 * @param i first value to compare
 * @param j second value to compare
 * @param column_num the numerical place of the column in the table
 * 
 * @return true if i is lesser than j, false otherwise
 */
bool ascending(CovidDataSet i, CovidDataSet j, int column_num) {
    // get numerical value of first and second args
    std::string value1 = (i.*i.column_data[column_num])();
    std::string value2 = (j.*j.column_data[column_num])();
    // set to 0, in case of empty string will be 0, otherwise stoi throws an error
    int x, y = 0;
    if (!value1.empty()) x = std::stoi(value1);
    if (!value2.empty()) y = std::stoi(value2);
    return x < y;
}

/**
 * Function for sorting by descending.
 * 
 * Pass this function to sort_numerical to sort by descending values.
 * 
 * @param i first value to compare
 * @param j second value to compare
 * @param column_num the numerical place of the column in the table
 * 
 * @return true if i is greater than j, false otherwise
 */
bool descending(CovidDataSet i, CovidDataSet j, int column_num) {    
    // get numerical value of first and second args       
    std::string value1 = (i.*i.column_data[column_num])();
    std::string value2 = (j.*j.column_data[column_num])();
    int x, y = 0;
    if (!value1.empty()) x = std::stoi(value1);
    if (!value2.empty()) y = std::stoi(value2);
    return x > y;
}