#include <unordered_map>
#include <string>
#include "lib/catch_amalgamated.cpp"
#include "lib/csv_data_parser.hpp"
#include "dao/CovidDataDAO.hpp"

/**
* Test Edit
*
* A test case for ensuring that the edit functionality works.
*
* @author Dan LeBlanc
* @studentno 040749264
*/
TEST_CASE("Update record", "[classic]"){
    std::string filename = "covid19-download.csv";
    std::string covid_file = read_file(filename);
    std::vector<std::unordered_map<std::string, std::string>> data_list = parse_data_set(covid_file);
    CovidDataSet cds;
    std::vector<CovidDataSet> covid_data_set_list;
    for (size_t i = 0; i < data_list.size(); i++) {
        covid_data_set_list.push_back(cds.build_covid_data_set(data_list[i]));
    }
    CovidDataDAO cddao(covid_data_set_list);
    const int record_num = 0;
    std::string col_name = "pruid";
    std::string init_val = cddao.get_record(record_num).get_pruid();
    std::string foo = "foo";

    cddao.edit_record(record_num, cddao.get_record(0).exists(col_name), foo);

    REQUIRE(cddao.get_record(record_num).get_pruid() != init_val);
    REQUIRE(cddao.get_record(record_num).get_pruid() == foo);
}