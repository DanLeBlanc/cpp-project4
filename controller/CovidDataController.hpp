#include <vector>
#include <unordered_map>
#include "../lib/csv_data_parser.hpp"
#include "../dao/CovidDataDAO.hpp"

// constants for defining choices in the menu
const char RELOAD   = 'r';
const char WRITE    = 'w';
const char SEE      = 's';
const char CREATE   = 'c';
const char EDIT     = 'e';
const char DEL      = 'd';
const char EXIT     = 'x';
const char SORT     = 'o';
const char SEARCH   = 'h';

/**
 * A Controller class for the CovidDataSet
 * 
 * CovidDataController is a utitlity for interacting with Canadian Covid data.
 * It can load a list of CovidDataSet objects or directly parse a CSV file.
 * Options for the user are outputted to the console.
 * 
 * @author Dan LeBlanc
 * @studentno 040749264
 */
class CovidDataController {
    std::vector<CovidDataSet> covid_data_set_list;

    public:
    /**
    * Loads a list of CovidDataSets
    *
    * Loads a list of CovidDataSet objects into the CovidDataConroller for manipulation
    *
    * @param cds_list a list of CovidDataSet objects
    */
    void load_list(std::vector<CovidDataSet> cds_list) {covid_data_set_list = cds_list;}

    /**
    *  Loads a CSV file
    * 
    *  Loads a CSV file of CovidDataSet objects given a relative file path.
    *
    * @param filename the relative file path to the csv file
    */
    void load_csv(std::string filename) {
        std::string file_contents;
        std::vector<CovidDataSet> cds_list;
        std::string covid_file = read_file(filename);
        // parse into a list of maps containing column names and data
        std::vector<std::unordered_map<std::string, std::string>> data_list = parse_data_set(covid_file);
        // create a list of CovidDataSet objects
        CovidDataSet cds;
        for (size_t i = 0; i < data_list.size(); i++) {
            cds_list.push_back(cds.build_covid_data_set(data_list[i]));
        }
        covid_data_set_list = cds_list;
    }

    /**
    * Runs the CovidDataController
    * 
    * Runs the CovidDataController, giving the user options in the console to execute
    * certain functions on the data.
    *
    * @return the status of the Controller, 0 if ended successfully.
    */
    // Dan LeBlanc 040749264
    int run() {
        if (covid_data_set_list.empty()) throw std::runtime_error("No Covid Data Set has been loaded.");

        char input;
        CovidDataDAO cddao(covid_data_set_list);
        std::cout << "Welcome to the covid data set interface." << "\n\n";

        while (input != EXIT) {
            // print name first
            std::cout << "By: Dan LeBlanc 040749264" << "\n\n";

            // print menu
            std::cout << "Choose option:" << "\n";
            std::cout 
                << "[r]eload data" << "\n"
                << "[w]rite to disk" << "\n"
                << "[s]ee records" << "\n"
                << "[c]reate new record" << "\n"
                << "[e]dit record" << "\n"
                << "[d]elete record" << "\n"
                << "s[o]rt" << "\n"
                << "searc[h]" << "\n"
                << "e[x]it" << "\n";

            std::cin >> input;

            switch(input) {
                case RELOAD: {
                    cddao.reload_data();
                    break;
                }
                case WRITE: {
                    std::string new_filename;
                    std::cout << "Filename: ";
                    std::cin >> new_filename;
                    cddao.save_to_disk(new_filename);
                    break;
                }
                // Dan LeBlanc 040749264
                case SEE: {
                    size_t row_start;
                    size_t num_of_records;
                    int num_of_columns;
                    std::cout << "Total rows: " << cddao.get_list().size() << "\n";
                    std::cout << "Row start: ";
                    std::cin >> row_start;
                    std::cout << "Number of records: ";
                    std::cin >> num_of_records;
                    std::cout << "Number of columns: ";
                    std::cin >> num_of_columns;

                    cddao.display_records(row_start, num_of_records, num_of_columns);
                    break;
                }
                case CREATE: {
                    std::cout << "Creating dummy row of data..." << "\n";
                    CovidDataSet new_cds;
                    for (int i = 0; i < new_cds.get_column_names().size(); i++){
                        (new_cds.*new_cds.set_columns[i])("12");
                    }
                    std::cout << "Done." << "\n";
                    std::cout << "Inserted into position: " << cddao.create_record(new_cds) << "\n";
                    break;
                }
                case EDIT: {
                    size_t row;
                    std::cout << "Choose row to edit: ";
                    std::cin >> row;

                    if (std::cin.fail()) {
                        std::cout << "Must input a number." << "\n";
                        // https://stackoverflow.com/questions/39282953/how-to-reset-stdcin-when-using-it
                        std::cin.clear();
                        std::cin.ignore();
                        break;
                    }

                    cddao.display_records(row, 1, 16);
                    std::cout << "Edit this record? y/n ";
                    char choice;
                    std::cin >> choice;

                    // if they don't choose y just break the switch
                    if (choice != 'y') break;

                    std::string column;
                    std::cout << "Choose column to edit: ";
                    std::cin >> column;
                    
                    CovidDataSet cds;
                    int column_num = cds.exists(column);
                    if (column_num == -1) {
                        std::cout << "Column does not exist." << "\n";
                        break;
                    }

                    std::string value;
                    std::cout << "Enter new value: ";
                    std::cin >> value;

                    cddao.edit_record(row, column_num, value);
                    break;
                }
                case DEL: {
                    size_t row;
                    std::cout << "Choose record row number to delete: ";
                    std::cin >> row;

                    if (std::cin.fail()) {
                        std::cout << "Must input a number.";
                        std::cin.clear();
                        std::cin.ignore();
                        break;
                    }

                    cddao.display_records(row, 1, 16);
                    std::cout << "Delete this record? y/n ";
                    char choice;
                    std::cin >> choice;

                    // only delete if it's y, anything else will just exit
                    if (choice == 'y') {
                        cddao.delete_record(row);
                        std::cout << "Record deleted." << "\n\n";
                    }
                    break;
                }

                case SEARCH: {
                    std::string col_name;
                    std::string col_val;
                    std::map<std::string, std::string> criteria;

                    while (input != 'y') {
                        std::cout << "Enter column name: " << "\n";
                        std::cin >> col_name;

                        std::cout << "Enter value: " << "\n";
                        std::cin >> col_val;

                        criteria.insert({col_name, col_val});

                        std::cout << "Finished? y/n" << "\n";
                        std::cin >> input;
                    }

                    std::vector<CovidDataSet> result_list = cddao.search(criteria);

                    cddao.set_list(result_list);
                    cddao.display_records(0, result_list.size(), 16);
                    break;
                }

                case SORT: {
                    const char COLUMN_ASCENDING     = 'a';
                    const char COLUMN_DESCENDING    = 'd';
                    const char PROVINCE             = 'p';
                    const char LESS_THAN            = 'l';
                    const char REVERSE              = 'r';

                    // print menu
                    std::cout << "Choose option:" << "\n";
                    std::cout 
                        << "column [a]scending" << "\n"
                        << "column [d]escending" << "\n"
                        << "[p]rovince" << "\n"
                        << "[l]ess than" << "\n"
                        << "[r]everse" << "\n";

                    std::cin >> input;

                    CovidDataDAO::Sorter sorter = cddao.sorter();

                    switch(input) {
                        case COLUMN_ASCENDING: {
                            std::string column_name;
                            std::cout << "Choose column to sort: ";
                            std::cin >> column_name;

                            try {
                                cddao.set_list(sorter.sort_numeric(column_name, ascending));
                            } catch (const std::runtime_error e) {
                                std::cout << e.what();
                                break;
                            }

                            std::cout << "List sorted." << "\n";
                            break;
                        }

                        case COLUMN_DESCENDING: {
                            std::string column_name;
                            std::cout << "Choose column to sort: ";
                            std::cin >> column_name;

                            try {
                                cddao.set_list(sorter.sort_numeric(column_name, descending));
                            } catch (const std::runtime_error e) {
                                std::cout << e.what();
                                break;
                            }

                            std::cout << "List sorted." << "\n";
                            break;
                        }

                        case PROVINCE: {
                            const std::string ON        = "35";
                            const std::string BC        = "59";
                            const std::string CA        = "1";
                            const std::string QC        = "24";
                            const std::string AB        = "48";
                            const std::string MA        = "46";
                            const std::string NB        = "13";
                            const std::string NF        = "10";
                            const std::string NWT       = "61";
                            const std::string NS        = "12";
                            const std::string NV        = "62";
                            const std::string PEI       = "11";
                            const std::string RT        = "99";
                            const std::string SK        = "47";
                            const std::string YK        = "60";

                            std::cout << "Choose province:" << "\n";

                            std::cout
                                << "Canada [" << CA << "]\n"
                                << "Ontario [" << ON << "]\n"
                                << "British Columbia [" << BC << "]\n"
                                << "Quebec [" << QC << "]\n"
                                << "Alberta [" << BC << "]\n"
                                << "Manitoba [" << MA << "]\n"
                                << "New Brunswick [" << NB << "]\n"
                                << "Newfoundland [" << NF << "]\n"
                                << "Northwest Territories [" << NWT << "]\n"
                                << "Nova Scotia [" << NS << "]\n"
                                << "Nunavut [" << NV << "]\n"
                                << "Prince Edward Island [" << PEI << "]\n"
                                << "Saskatchewan [" << SK << "]\n"
                                << "Yukon [" << YK << "]\n"
                                << "Repatriated Travellers [" << RT << "]\n";

                            std::string province_input;
                            std::cin >> province_input;

                            try {
                                cddao.set_list(sorter.sort_province(province_input));
                            } catch (const std::runtime_error e) {
                                std::cout << e.what();
                                break;
                            }

                            std::cout << "List sorted." << "\n";
                            break;
                        }

                        case LESS_THAN: {
                            std::string column_name;
                            std::cout << "Choose column to sort: ";
                            std::cin >> column_name;

                            int num;
                            std::cout << "Less than: ";
                            std::cin >> num;

                            try {
                                cddao.set_list(sorter.less_than(column_name, num));
                            } catch (const std::runtime_error e) {
                                std::cout << e.what();
                                break;
                            }

                            std::cout << "List sorted." << "\n";
                            break;
                        }

                        case REVERSE: {
                            cddao.set_list(sorter.date_descending());

                            std::cout << "List sorted." << "\n";
                            break;
                        }
                        
                    }
                }
            }
        }
        return 0;
    }


};

