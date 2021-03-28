#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <map>
#include <functional>

// Dan LeBlanc 040749264

/**
* CovidDataSet model
*
* This header file provides the model for the Canadian Covid Data Set.
*
* @author Dan LeBlanc
* @studentno 040749264
*/

const int TOTAL_COLUMNS = 36;

class CovidDataSet {
    std::string pruid;
    std::string prname;
    std::string prnameFR;
    std::string date;
    std::string update;
    std::string numconf;
    std::string numprob;
    std::string numdeaths;
    std::string numtotal;
    std::string numtested;
    std::string numrecover;
    std::string percentrecover;
    std::string ratetested; 
    std::string numtoday;
    std::string percentoday;
    std::string ratetotal;
    std::string ratedeaths;
    std::string numdeathstoday;
    std::string percentdeath;
    std::string numtestedtoday;
    std::string numrecoveredtoday;
    std::string percentactive;
    std::string numactive;
    std::string rateactive;
    std::string numtotal_last14;
    std::string ratetotal_last14;
    std::string numdeaths_last14;
    std::string ratedeaths_last14;
    std::string numtotal_last7;
    std::string ratetotal_last7;
    std::string numdeaths_last7;
    std::string ratedeaths_last7;
    std::string avgtotal_last7;
    std::string avgincidence_last7;
    std::string avgdeaths_last7;
    std::string avgratedeaths_last7;

    /**
     * Column names 
     * 
     * The names of the columns in a CovidDataSet. They were here the whole time.
     */
    std::vector<std::string> column_names = {      
        "pruid",
        "prname",
        "prnameFR",
        "date",
        "update",
        "numconf",
        "numprob",
        "numdeaths",
        "numtotal",
        "numtested",
        "numrecover",
        "percentrecover",
        "ratetested",
        "numtoday",
        "percentoday",
        "ratetotal",
        "ratedeaths",
        "numdeathstoday",
        "percentdeath",
        "numtestedtoday",
        "numrecoveredtoday",
        "percentactive",
        "numactive",
        "rateactive",
        "numtotal_last14",
        "ratetotal_last14",
        "numdeaths_last14",
        "ratedeaths_last14",
        "numtotal_last7",
        "ratetotal_last7",
        "numdeaths_last7",
        "ratedeaths_last7",
        "avgtotal_last7",
        "avgincidence_last7",
        "avgdeaths_last7",
        "avgratedeaths_last7"
        };
public:
    // Found syntax for this at:
    // https://stackoverflow.com/questions/46527961/storing-functions-from-class-in-array-and-invoke-them-c
    typedef std::string (CovidDataSet::*get_data)();
    typedef void (CovidDataSet::*set_data)(std::string arg);
    set_data set_columns[TOTAL_COLUMNS];
    get_data column_data[TOTAL_COLUMNS];
    CovidDataSet();

    std::vector<std::string> get_column_names() {return column_names;}

    /**
     * Exists
     * 
     * Check if a column exists in the data set
     * 
     * @return the position of the column, or -1 if not found
     */ 
    int exists(std::string& column) {
        for (int i = 0; i < TOTAL_COLUMNS; i++) {
            if (column == column_names[i]) return i;
        }
        return -1;
    }

    /**
    * Build a CovidDataSet object
    * 
    * Builds a CovidDataSet object from the given map.
    *
    * @param mapped_row a mapped row of covid data from the csv
    * @return a CovidDataSet object
    */
    // Dan LeBlanc 040749264
    CovidDataSet build_covid_data_set(std::unordered_map<std::string,std::string> mapped_row){
        for (int i = 0; i < column_names.size(); i++) 
            (this->*this->set_columns[i])(mapped_row[column_names[i]]);
        return *this;
    }

    // these are methods, they were here the whole time too
    std::string get_pruid() {return pruid;}
    void set_pruid(std::string arg) {pruid = arg;}
    std::string get_prname() {return prname;}
    void set_prname(std::string arg) {prname = arg;}
    std::string get_prnameFR() {return prnameFR;}
    void set_prnameFR(std::string arg) {prnameFR = arg;}
    std::string get_date() {return date;}
    void set_date(std::string arg) {date = arg;}
    std::string get_update() {return update;}
    void set_update(std::string arg) {update = arg;}
    std::string get_numconf() {return numconf;}
    void set_numconf(std::string arg) {numconf = arg;}
    std::string get_numprob() {return numprob;}
    void set_numprob(std::string arg) {numprob = arg;}
    std::string get_numdeaths() {return numdeaths;}
    void set_numdeaths(std::string arg) {numdeaths = arg;}
    std::string get_numtotal() {return numtotal;}
    void set_numtotal(std::string arg) {numtotal = arg;}
    std::string get_numtested() {return numtested;}
    void set_numtested(std::string arg) {numtested = arg;}
    std::string get_numrecover() {return numrecover;}
    void set_numrecover(std::string arg) {numrecover = arg;}
    std::string get_percentrecover() {return percentrecover;}
    void set_percentrecover(std::string arg) {percentrecover = arg;}
    std::string get_ratetested() {return ratetested;}
    void set_ratetested(std::string arg) {ratetested = arg;}
    std::string get_numtoday() {return numtoday;}
    void set_numtoday(std::string arg) {numtoday = arg;}
    std::string get_percentoday() {return percentoday;}
    void set_percentoday(std::string arg) {percentoday = arg;}
    std::string get_ratetotal() {return ratetotal;}
    void set_ratetotal(std::string arg) {ratetotal = arg;}
    std::string get_ratedeaths() {return ratedeaths;}
    void set_ratedeaths(std::string arg) {ratedeaths = arg;}
    std::string get_numdeathstoday() {return numdeathstoday;}
    void set_numdeathstoday(std::string arg) {numdeathstoday = arg;}
    std::string get_percentdeath() {return percentdeath;}
    void set_percentdeath(std::string arg) {percentdeath = arg;}
    std::string get_numtestedtoday() {return numtestedtoday;}
    void set_numtestedtoday(std::string arg) {numtestedtoday = arg;}
    std::string get_numrecoveredtoday() {return numrecoveredtoday;}
    void set_numrecoveredtoday(std::string arg) {numrecoveredtoday = arg;}        
    std::string get_percentactive() {return percentactive;}
    void set_percentactive(std::string arg) {percentactive = arg;}
    std::string get_numactive() {return numactive;}
    void set_numactive(std::string arg) {numactive = arg;}
    std::string get_rateactive() {return rateactive;}
    void set_rateactive(std::string arg) {rateactive = arg;}
    std::string get_numtotal_last14() {return numtotal_last14;}
    void set_numtotal_last14(std::string arg) {numtotal_last14 = arg;}
    std::string get_ratetotal_last14() {return ratetotal_last14;}
    void set_ratetotal_last14(std::string arg) {ratetotal_last14 = arg;}
    std::string get_numdeaths_last14() {return numdeaths_last14;}
    void set_numdeaths_last14(std::string arg) {numdeaths_last14 = arg;}
    std::string get_ratedeaths_last14() {return ratedeaths_last14;}
    void set_ratedeaths_last14(std::string arg) {ratedeaths_last14 = arg;}
    std::string get_numtotal_last7() {return numtotal_last7;}
    void set_numtotal_last7(std::string arg) {numtotal_last7 = arg;}
    std::string get_ratetotal_last7() {return ratetotal_last7;}
    void set_ratetotal_last7(std::string arg) {ratetotal_last7 = arg;}
    std::string get_numdeaths_last7() {return numdeaths_last7;}
    void set_numdeaths_last7(std::string arg) {numdeaths_last7 = arg;}
    std::string get_ratedeaths_last7() {return ratedeaths_last7;}
    void set_ratedeaths_last7(std::string arg) {ratedeaths_last7 = arg;}
    std::string get_avgtotal_last7() {return avgtotal_last7;}
    void set_avgtotal_last7(std::string arg) {avgtotal_last7 = arg;}
    std::string get_avgincidence_last7() {return avgincidence_last7;}
    void set_avgincidence_last7(std::string arg) {avgincidence_last7 = arg;}
    std::string get_avgdeaths_last7() {return avgdeaths_last7;}
    void set_avgdeaths_last7(std::string arg) {avgdeaths_last7 = arg;}
    std::string get_avgratedeaths_last7() {return avgratedeaths_last7;}
    void set_avgratedeaths_last7(std::string arg) {avgratedeaths_last7 = arg;}

};

// Found syntax for this at:
// https://stackoverflow.com/questions/46527961/storing-functions-from-class-in-array-and-invoke-them-c
CovidDataSet::CovidDataSet() {        
    // Dan LeBlanc 040479264
    column_data[0] = &CovidDataSet::get_pruid;
    // Dan LeBlanc 040479264
    column_data[1] = &CovidDataSet::get_prname;
    // Dan LeBlanc 040479264
    column_data[2] = &CovidDataSet::get_prnameFR;
    // Dan LeBlanc 040479264
    column_data[3] = &CovidDataSet::get_date;
    // Dan LeBlanc 040479264
    column_data[4] = &CovidDataSet::get_update;
    // Dan LeBlanc 040479264
    column_data[5] = &CovidDataSet::get_numconf;
    // Dan LeBlanc 040479264
    column_data[6] = &CovidDataSet::get_numprob;
    column_data[7] = &CovidDataSet::get_numdeaths;
    column_data[8] = &CovidDataSet::get_numtotal;
    column_data[9] = &CovidDataSet::get_numtested;
    column_data[10] = &CovidDataSet::get_numrecover;
    column_data[11] = &CovidDataSet::get_percentrecover;
    column_data[12] = &CovidDataSet::get_ratetested;
    column_data[13] = &CovidDataSet::get_numtoday;
    column_data[14] = &CovidDataSet::get_percentoday;
    column_data[15] = &CovidDataSet::get_ratetotal;
    column_data[16] = &CovidDataSet::get_ratedeaths;
    column_data[17] = &CovidDataSet::get_numdeathstoday;
    column_data[18] = &CovidDataSet::get_percentdeath;
    column_data[19] = &CovidDataSet::get_numtestedtoday;
    column_data[20] = &CovidDataSet::get_numrecoveredtoday;
    column_data[21] = &CovidDataSet::get_percentactive;
    column_data[22] = &CovidDataSet::get_numactive;
    column_data[23] = &CovidDataSet::get_rateactive;
    column_data[24] = &CovidDataSet::get_numtotal_last14;
    column_data[25] = &CovidDataSet::get_ratetotal_last14;
    column_data[26] = &CovidDataSet::get_numdeaths_last14;
    column_data[27] = &CovidDataSet::get_ratedeaths_last14;
    column_data[28] = &CovidDataSet::get_numtotal_last7;
    column_data[29] = &CovidDataSet::get_ratetotal_last7;
    column_data[30] = &CovidDataSet::get_numdeaths_last7;
    column_data[31] = &CovidDataSet::get_ratedeaths_last7;
    column_data[32] = &CovidDataSet::get_avgtotal_last7;
    column_data[33] = &CovidDataSet::get_avgincidence_last7;
    column_data[34] = &CovidDataSet::get_avgdeaths_last7;
    column_data[35] = &CovidDataSet::get_avgratedeaths_last7;

    set_columns[0] = &CovidDataSet::set_pruid;
    set_columns[1] = &CovidDataSet::set_prname;
    set_columns[2] = &CovidDataSet::set_prnameFR;
    set_columns[3] = &CovidDataSet::set_date;
    set_columns[4] = &CovidDataSet::set_update;
    set_columns[5] = &CovidDataSet::set_numconf;
    set_columns[6] = &CovidDataSet::set_numprob;
    set_columns[7] = &CovidDataSet::set_numdeaths;
    set_columns[8] = &CovidDataSet::set_numtotal;
    set_columns[9] = &CovidDataSet::set_numtested;
    set_columns[10] = &CovidDataSet::set_numrecover;
    set_columns[11] = &CovidDataSet::set_percentrecover;
    set_columns[12] = &CovidDataSet::set_ratetested;
    set_columns[13] = &CovidDataSet::set_numtoday;
    set_columns[14] = &CovidDataSet::set_percentoday;
    set_columns[15] = &CovidDataSet::set_ratetotal;
    set_columns[16] = &CovidDataSet::set_ratedeaths;
    set_columns[17] = &CovidDataSet::set_numdeathstoday;
    set_columns[18] = &CovidDataSet::set_percentdeath;
    set_columns[19] = &CovidDataSet::set_numtestedtoday;
    set_columns[20] = &CovidDataSet::set_numrecoveredtoday;
    set_columns[21] = &CovidDataSet::set_percentactive;
    set_columns[22] = &CovidDataSet::set_numactive;
    set_columns[23] = &CovidDataSet::set_rateactive;
    set_columns[24] = &CovidDataSet::set_numtotal_last14;
    set_columns[25] = &CovidDataSet::set_ratetotal_last14;
    set_columns[26] = &CovidDataSet::set_numdeaths_last14;
    set_columns[27] = &CovidDataSet::set_ratedeaths_last14;
    set_columns[28] = &CovidDataSet::set_numtotal_last7;
    set_columns[29] = &CovidDataSet::set_ratetotal_last7;
    set_columns[30] = &CovidDataSet::set_numdeaths_last7;
    set_columns[31] = &CovidDataSet::set_ratedeaths_last7;
    set_columns[32] = &CovidDataSet::set_avgtotal_last7;
    set_columns[33] = &CovidDataSet::set_avgincidence_last7;
    set_columns[34] = &CovidDataSet::set_avgdeaths_last7;
    set_columns[35] = &CovidDataSet::set_avgratedeaths_last7;
};