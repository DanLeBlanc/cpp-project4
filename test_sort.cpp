#include <unordered_map>
#include <string>
#include "lib/catch_amalgamated.cpp"
#include "lib/csv_data_parser.hpp"
#include "dao/CovidDataDAO.hpp"

/**
* Test Sort By Province
*
* A test case for ensuring that the sort by province functionality works.
*
* @author Dan LeBlanc
* @studentno 040749264
*/
TEST_CASE("Sort records", "[classic]"){
    std::cout << "Dan LeBlanc, 040749264" << "\n";
    std::string filename = "covid19-download.csv";
    std::string covid_file = read_file(filename);
    std::vector<std::unordered_map<std::string, std::string>> data_list = parse_data_set(covid_file);
    CovidDataSet cds;
    std::vector<CovidDataSet> covid_data_set_list;
    for (size_t i = 0; i < data_list.size(); i++) {
        covid_data_set_list.push_back(cds.build_covid_data_set(data_list[i]));
    }
    CovidDataDAO cddao(covid_data_set_list);

    CovidDataDAO::Sorter sorter = cddao.sorter();

    // 35 == pruid for Ontario
    std::string PRUID = "35";
    std::string PROVINCE = "Ontario";

    std::vector<CovidDataSet> sorted_list = sorter.sort_province(PRUID);

    for (CovidDataSet cds : sorted_list) {
        REQUIRE(cds.get_pruid() == PRUID);
        REQUIRE(cds.get_prname() == PROVINCE);
    }

    cddao.reload_data();

    sorter = cddao.sorter();
    
    // 59 == pruid for British Columbia
    PRUID = "59";
    PROVINCE = "British Columbia";

    sorted_list = sorter.sort_province(PRUID);

    for (CovidDataSet cds : sorted_list) {
        REQUIRE(cds.get_pruid() == PRUID);
        REQUIRE(cds.get_prname() == PROVINCE);
    }   
    
}