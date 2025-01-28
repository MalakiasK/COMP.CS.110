/* Rasse2
 *
 * Kuvaus:
 * Ohjelma on raitiovaunuverkoston tietopankki, jolla voidaan tutkia
 * entuudestaan valmistettua tiedostoa, jossa on tarvittavat tiedot.
 * Tarvittavia tietoja ovat linja, pysäkki ja etäisyys aloituspysäkistä.
 * Vaihtoehtoisesti voidaan rakentaa verkosto manuaalisesti ohjelmalla.
 * Ohjelmalla voidaan käskyjen muodossa lisätä linjoja sekä niihin pysäkkejä.
 * Verkostosta voidaan myös poistaa pysäkkejä.
 *
 * Ohjelman kirjoittaja
 * Nimi: Malakias Kosonen
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 * Kommentit, muuttujat yms. ovat englanniksi, koska se on mielestäni
 * luontevampaa.
 *
 * */

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

// Splits the user's input commands into a vector for easy use.
// From earlier projects.
std::vector<std::string> split(const std::string& s, const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

// Reads a file in CSV-format and updates the main database.
// Performs different error-checks.
bool read_file(std::vector<std::vector<std::string>>& tramdata)
{
    std::string filename;
    std::cout << "Give a name for input file: ";
    getline(std::cin, filename);

    std::ifstream file(filename);
    // File can be opened.
    if ( file )
    {
        std::string line;
        while ( getline(file, line))
        {
            // Stores data in the form of {LINE, STOP, DISTANCE}.
            std::vector<std::string> stopdata;
            // Split a line in the file to the vector with the delimiter ';'.
            stopdata = split(line, ';');

            // For starting STOPs which have no distance,
            // add and set distance as '0'.
            if ( stopdata.size() == 2 ) { stopdata.push_back("0"); }
            else if ( stopdata.back() == "" ) { stopdata.back() = "0"; }

            // Check for format errors.
            // Empty LINE or STOP field, or incorrect info amount.
            if ( (stopdata[0] == "") or (stopdata[1] == "") or
                 (stopdata.size() > 3) or (stopdata.size() < 2))
            {
                std::cout << "Error: Invalid format in file." << std::endl;
                return false;
            }

            // Check for duplicate STOP or DISTANCE data in a LINE.
            // Main container must have at least one LINE to compare.
            if ( tramdata.size() > 0 )
            {
                // Loop through main container.
                for ( unsigned int i = 0; i < tramdata.size(); i++ )
                {
                    // Check info with the same LINE in stopdata.
                    if ( tramdata[i].at(0) == stopdata[0] )
                    {
                        // Compare STOP and DISTANCE.
                        if ( (tramdata[i].at(1) == stopdata[1])
                             or (tramdata[i].at(2) == stopdata[2]) )
                        {
                            std::cout << "Error: Stop/line already exists."
                                      << std::endl;
                            return false;
                        }
                    }
                }
            }

            // Add to main data container.
            tramdata.push_back(stopdata);
        }
        // Data acquisition successful.
        file.close();
        return true;
    }
    // File cannot be opened.
    else
    {
        std::cout << "Error: File could not be read." << std::endl;
        return false;
    }
}

// Creates a vector with every unique STOP.
std::vector<std::string> uniquestops(std::vector<std::vector<std::string>>
                                     tramdata)
{
    std::vector<std::string> stops;
    // Loop through data to find every unique STOP.
    for ( unsigned int i = 0; i < tramdata.size(); i++ )
    {
        // If a LINE doesn't have any STOPs.
        if ( tramdata[i].size() < 2 ) { continue; }
        // The STOP is not yet present in vector <stops>.
        else if ( std::find(stops.begin(),
                       stops.end(),
                       tramdata[i].at(1)) == stops.end())
        {
            stops.push_back(tramdata[i].at(1));
        }
    }
    return stops;
}

// Creates a vector with every unique LINE.
std::vector<std::string> uniquetramlines(std::vector<std::vector<std::string>>
                                         tramdata)
{
    std::vector<std::string> tramlines;
    // Loop through data to find every unique tramline.
    for ( unsigned int i = 0; i < tramdata.size(); i++ )
    {
        // The LINE is not yet present in vector <tramlines>.
        if ( std::find(tramlines.begin(),
                       tramlines.end(),
                       tramdata[i].at(0)) == tramlines.end())
        {
            tramlines.push_back(tramdata[i].at(0));
        }
    }
    return tramlines;
}

// Creates a vector with every unique DISTANCE in a LINE.
std::vector<std::string> uniquedistances(std::vector<std::vector<std::string>>
                                         tramdata, std::string line)
{
    std::vector<std::string> tramdistances;
    // Loop through data to find every unique DISTANCE in the LINE.
    for ( unsigned int i = 0; i < tramdata.size(); i++ )
    {
        // If a LINE doesn't have a DISTANCE or STOP.
        if ( tramdata[i].size() < 2 ) { continue; }
        // LINE matches.
        if ( tramdata[i].at(0) == line )
        {
            // The DISTANCE is not yet present in vector <tramlines>.
            if ( std::find(tramdistances.begin(),
                           tramdistances.end(),
                           tramdata[i].at(2)) == tramdistances.end())
            {
                tramdistances.push_back(tramdata[i].at(2));
            }
        }
    }
    return tramdistances;
}

// Error check for parameters.
bool parameter_error(std::vector<std::vector<std::string>> tramdata,
                     std::string parameter, std::string target_data,
                     std::vector<std::string> cmd_parts = {},
                     unsigned int target_size = 0)
{
    if ( target_data == "SIZE" )
    {
        // User input doesn't have enough parameters.
        if ( cmd_parts.size() < target_size )
        { std::cout << "Error: Invalid input." << std::endl; return true; }
    }

    else if ( target_data == "LINE" )
    {
        // Every unique LINE.
        std::vector<std::string> tramlines = uniquetramlines(tramdata);
        // Given LINE doesn't exist in the database.
        if ( std::find(tramlines.begin(), tramlines.end(), parameter)
             == tramlines.end())
        {
            std::cout << "Error: Line could not be found." << std::endl;
            return true;
        }
    }

    else if ( target_data == "STOP" )
    {
        // Every unique STOP.
        std::vector<std::string> tramstops = uniquestops(tramdata);
        // Given STOP doesn't exist in the database.
        if ( std::find(tramstops.begin(), tramstops.end(), parameter)
             == tramstops.end())
        {
            std::cout << "Error: Stop could not be found." << std::endl;
            return true;
        }
    }

    else if ( target_data == "DUPLICATELINE" )
    {
        // Every unique LINE.
        std::vector<std::string> tramlines = uniquetramlines(tramdata);
        // Given LINE already exists in the database.
        if ( std::find(tramlines.begin(), tramlines.end(), parameter)
             != tramlines.end())
        {
            std::cout << "Error: Stop/line already exists." << std::endl;
            return true;
        }
    }

    else if ( target_data == "DUPLICATESTOP" )
    {
        // Every unique STOP.
        std::vector<std::string> tramstops = uniquestops(tramdata);
        // Given STOP already exists in the database.
        if ( std::find(tramstops.begin(), tramstops.end(), parameter)
             != tramstops.end())
        {
            std::cout << "Error: Stop/line already exists." << std::endl;
            return true;
        }
    }

    else if ( target_data == "DUPLICATEDISTANCE" )
    {
        // Every unique DISTANCE in a LINE.
        std::vector<std::string> tramdistances = uniquedistances(tramdata,
                                                                 cmd_parts[0]);
        // Given DISTANCE already exists in the LINE.
        if ( std::find(tramdistances.begin(), tramdistances.end(), parameter)
             != tramdistances.end())
        {
            std::cout << "Error: Stop/line already exists." << std::endl;
            return true;
        }
    }

    // Parameters pass the vibe checks.
    return false;
}

// Prints every unique LINE in the given database in alphabetical order.
void lines(std::vector<std::vector<std::string>> tramdata)
{
    std::cout << "All tramlines in alphabetical order:" << std::endl;

    // Every unique LINE.
    std::vector<std::string> tramlines = uniquetramlines(tramdata);

    // Sort vector to alphabetical order.
    std::sort(tramlines.begin(), tramlines.end());
    // Print the unique LINEs.
    for ( std::string line : tramlines )
    {
        std::cout << line << std::endl;
    }
}

// Prints every LINE with a given STOP.
void lines_with_stop(std::vector<std::vector<std::string>> tramdata,
                     std::vector<std::string> cmd_parts)
{
    // Error check, if user hasn't given a STOP to search with.
    if ( parameter_error(tramdata, cmd_parts[0], "SIZE", cmd_parts, 2))
    { return; }

    // Check for erroneus STOP.
    if ( parameter_error(tramdata, cmd_parts[1], "STOP") )
    { return; }

    std::cout << "Stop " << cmd_parts[1]
              << " can be found on the following lines:" << std::endl;

    // Every common LINE.
    std::vector<std::string> common_lines;

    // Loop through the main database.
    for ( unsigned int i = 0; i < tramdata.size(); i++ )
    {
        // When the STOP matches.
        if ( tramdata[i].at(1) == cmd_parts[1] )
        {
            common_lines.push_back(tramdata[i].at(0));
        }
    }

    // Sort the vector with the common lines.
    std::sort(common_lines.begin(), common_lines.end());
    // Print sorted vector.
    for ( std::string line : common_lines )
        // Print.
    { std::cout << " - " << line << std::endl; }
}

// Prints every STOP in a given LINE.
void stops_in_line(std::vector<std::vector<std::string>> tramdata,
                   std::vector<std::string> cmd_parts)
{
    // Error check, if user hasn't given a LINE to search from.
    if ( parameter_error(tramdata, cmd_parts[0], "SIZE", cmd_parts, 2))
    { return; }

    // Check for erroneus LINE.
    if ( parameter_error(tramdata, cmd_parts[1], "LINE") )
    { return; }

    std::cout << "Line " << cmd_parts[1]
              << " goes through these stops in the order they are listed:"
              << std::endl;

    // Loop through main database.
    for ( unsigned int i = 0; i < tramdata.size(); i++ )
    {
        // When the LINE matches.
        if ( tramdata[i].at(0) == cmd_parts[1] )
        {
            // If the LINE is empty -> It is a new LINE from ADDLINE
            // -> Nothing to print.
            if ( tramdata[i].size() == 1 ) { break; }
            // Print the STOPs.
            std::cout << " - " << tramdata[i].at(1) << " : "
                      << tramdata[i].at(2) << std::endl;
        }
    }
}

// Prints every unique STOP in the database in alphabetical order.
void stops(std::vector<std::vector<std::string>> tramdata)
{
    std::cout << "All stops in alphabetical order:" << std::endl;

    // Every unique STOP.
    std::vector<std::string> tramstops = uniquestops(tramdata);

    // Sort vector to alphabetical order.
    std::sort(tramstops.begin(), tramstops.end());
    // Print the unique STOPs.
    for ( std::string stop : tramstops )
    {
        std::cout << stop << std::endl;
    }
}

void distance(std::vector<std::vector<std::string>> tramdata,
              std::vector<std::string> cmd_parts)
{
    // Error check, if user hasn't given enough parameters to use.
    if ( parameter_error(tramdata, cmd_parts[0], "SIZE", cmd_parts, 4))
    { return; }

    // Check for erroneus LINE.
    if ( parameter_error(tramdata, cmd_parts[1], "LINE") ) { return; }

    // Check for erroneus STOP1.
    if ( parameter_error(tramdata, cmd_parts[2], "STOP") ) { return; }

    // Check for erroneus STOP2.
    if ( parameter_error(tramdata, cmd_parts[3], "STOP") ) { return; }

    double x1 = 0;
    double x2 = 0;
    double dist = 0;

    // Loop through main database.
    for ( unsigned int i = 0; i < tramdata.size(); i++ )
    {
        // If STOPs are the same -> Distance is zero.
        if ( cmd_parts[2] == cmd_parts[3] ) { break; }
        // LINE matches.
        if ( tramdata[i].at(0) == cmd_parts[1] )
        {
            // Get STOP 1 distance.
            if ( tramdata[i].at(1) == cmd_parts[2] )
            {
                // Convert string to double.
                x1 = std::stod(tramdata[i].at(2));
            }
            // Get STOP 2 distance.
            else if ( tramdata[i].at(1) == cmd_parts[3] )
            {
                x2 = std::stod(tramdata[i].at(2));
            }
        }
    }
    // Calculate distance between STOPs.
    dist = std::abs(x1 - x2);
    // Print distance.
    std::cout << "Distance between " << cmd_parts[2] << " and "
              << cmd_parts[3] << " is " << dist << std::endl;
}

void addline(std::vector<std::vector<std::string>>& tramdata,
             std::vector<std::string> cmd_parts)
{
    // Error check, if user hasn't given enough parameters to use.
    if ( parameter_error(tramdata, cmd_parts[0], "SIZE", cmd_parts, 2))
    { return; }

    // Given LINE already exists in the database.
    if ( parameter_error(tramdata, cmd_parts[1], "DUPLICATELINE") ) { return; }

    // Add LINE to the database as empty -> without stop or distance.
    tramdata.push_back( {cmd_parts[1]} );

    // Print confirmation.
    std::cout << "Line was added." << std::endl;
}

void addstop(std::vector<std::vector<std::string>>& tramdata,
             std::vector<std::string> cmd_parts)
{
    // Error check, if user hasn't given enough parameters to use.
    if ( parameter_error(tramdata, cmd_parts[0], "SIZE", cmd_parts, 4))
    { return; }

    // Check for erroneus LINE.
    if ( parameter_error(tramdata, cmd_parts[1], "LINE") ) { return; }

    // Check for duplicate STOP.
    if ( parameter_error(tramdata, cmd_parts[2], "DUPLICATESTOP") ) { return; }

    // Check for duplicate DISTANCE.
    if ( parameter_error(tramdata, cmd_parts[3],
                         "DUPLICATEDISTANCE", cmd_parts) ) { return; }

    // Every unique DISTANCE in a LINE.
    std::vector<std::string> tramdistances = uniquedistances(tramdata,
                                                             cmd_parts[1]);


    // If LINE doesn't have any stops.
    if ( tramdistances.size() == 0 )
    {
        // Remove empty and replace with new with more info.
        tramdata.erase(tramdata.end());
        tramdata.push_back( {cmd_parts[1], cmd_parts[2], cmd_parts[3]} );
        std::cout << "Stop was added." << std::endl;
        return;
    }

    // STOP will be the new last STOP
    // -> longer than the current longest distance.
    double current_distance = std::stod(tramdistances.back());
    double new_distance = std::stod(cmd_parts[3]);

    // If LINE has STOPs.
    if ( current_distance < new_distance )
    {
        tramdata.push_back( {cmd_parts[1], cmd_parts[2], cmd_parts[3]} );
    }
    else
    {
        // Add stop to database to correct spot based on the DISTANCE.
        //
        // Loop through main database.
        for ( unsigned int i = 0; i < tramdata.size(); i++ )
        {
            // When the LINE matches.
            if ( tramdata[i].at(0) == cmd_parts[1] )
            {
                // Distance is smaller
                // -> continue until a longer distance is found.
                if ( tramdata[i].at(2) < cmd_parts[3] ) { continue; }
                // Longer distance found.
                else if ( tramdata[i].at(2) > cmd_parts[3] )
                {
                    // Iterator for correct position.
                    std::vector<std::vector<std::string>>::iterator itr;
                    itr = (tramdata.begin() + i);
                    // Add STOP to correct position.
                    tramdata.insert(itr, {cmd_parts[1], cmd_parts[2],
                                          cmd_parts[3]});
                    break;
                }
            }
        }
    }
    std::cout << "Stop was added." << std::endl;
}

void remove_stop(std::vector<std::vector<std::string>>& tramdata,
                 std::vector<std::string> cmd_parts)
{
    // Error check, if user hasn't given enough parameters to use.
    if ( parameter_error(tramdata, cmd_parts[0], "SIZE", cmd_parts, 2))
    { return; }

    // Check for erroneus LINE.
    if ( parameter_error(tramdata, cmd_parts[1], "STOP") ) { return; }

    // Iterator for correct position.
    std::vector<std::vector<std::string>>::iterator itr;

    while ( true )
    {
        // Every unique STOP.
        std::vector<std::string> tramstops = uniquestops(tramdata);
        // If STOP still exists.
        if ( std::find(tramstops.begin(), tramstops.end(), cmd_parts[1])
             != tramstops.end())
        {
            // Loop through main database.
            for ( unsigned int i = 0; i < tramdata.size(); i++ )
            {
                // STOP found.
                if ( tramdata[i].at(1) == cmd_parts[1] )
                {
                    itr = (tramdata.begin() + i);
                    // Erase STOP and relevant information.
                    tramdata.erase(itr);
                }
            }
        }
        // Stop is completely removed from the database.
        else { break; }
    }
    // Removal confirmation.
    std::cout << "Stop was removed from all lines." << std::endl;
}

// Converts a given string to UPPERCASE.
// "string" -> "STRING"
void uppercase(std::string& cmd)
{
    for ( unsigned int i = 0; i < cmd.size(); i++ )
    {
        cmd[i] = toupper(cmd[i]);
    }
}

// Check for quote-marks, i.e. single parameter with two or more words.
std::vector<std::string> multiword_check(std::vector<std::string> cmd_parts)
{
    // First element, or command, is always one word.
    // Create vector with only that element.
    std::vector<std::string> temp = {cmd_parts[0]};

    // New string for possible parameter with multiple words.
    std::string new_str;
    // Loop through every part.
    for ( unsigned int i = 1; i < cmd_parts.size(); i++ )
    {
        // Single word quote-marks.
        if ( (cmd_parts[i].at(0) == '"') and (cmd_parts[i].back() == '"') )
        {
            cmd_parts[i].erase(0, 1);
            cmd_parts[i].pop_back();
            temp.push_back(cmd_parts[i]);
            continue;
        }
        // Quote mark in front of word.
        if ( cmd_parts[i].at(0) == '"' )
        {
            // Remove quotation mark.
            new_str = cmd_parts[i].erase(0, 1);
            // Add quotation marks back to old vector for future checks.
            cmd_parts[i].insert(0, 1, '"');
            continue;
        }
        // Quote mark at the end of the word.
        if ( cmd_parts[i].back() == '"' )
        {
            // Remove quote-mark.
            cmd_parts[i].pop_back();
            // Add to string.
            new_str.append(" " + cmd_parts[i]);
            // Add to vector.
            temp.push_back(new_str);
            // Initialize new_str.
            new_str = "";
            continue;
        }
        // Check if the word is in between words
        // with quotation marks on either side.
        else
        {
            std::vector<bool> test_results = {false, false};
            // Check earlier words.
            for ( unsigned int t = i; t > 0; t-- )
            {
                if ( (cmd_parts[t].at(0) == '"')
                     and (cmd_parts[t].back() != '"') )
                {
                    test_results[0] = true;
                    break;
                }
            }
            // Check for later words.
            for ( unsigned int j = i; j < cmd_parts.size(); j++ )
            {
                if ( (cmd_parts[j].at(0) != '"')
                     and (cmd_parts[j].back() == '"') )
                {
                    test_results[1] = true;
                    break;
                }
            }
            // Decide from test results if word is in between
            // words with quotation marks.
            if ( test_results[0] and test_results[1] )
            {
                new_str.append(" " + cmd_parts[i]);
                continue;
            }
        }
        // No quote marks.
        temp.push_back(cmd_parts[i]);
    }
    return temp;
}

// Main user interface, user input commands happen here
// and then get directed to their respective functions.
int interface(std::vector<std::vector<std::string>> tramdata)
{
    // Interface loop.
    while ( true )
    {
        // User input command.
        std::string cmd;
        std::cout << "tramway> ";
        getline(std::cin, cmd);

        // Split command line.
        std::vector<std::string> cmd_parts = split(cmd, ' ', true);
        // Convert the command portion to uppercase.
        uppercase(cmd_parts[0]);
        // Check for quote-marks, i.e. single parameter with two or more words.
        cmd_parts = multiword_check(cmd_parts);

        // Main command.
        std::string command = cmd_parts[0];

        // Commands:
        //
        // Quit command, ends the program.
        if ( command == "QUIT" ) { return EXIT_SUCCESS; }

        // Prints every unique LINE in the given database in alphabetical order.
        else if ( command == "LINES" ) { lines(tramdata); }

        // Prints every STOP in a given LINE.
        else if ( command == "LINE" ) { stops_in_line(tramdata, cmd_parts); }

        // Prints every unique STOP in the given database in alphabetical order.
        else if ( command == "STOPS" ) { stops(tramdata); }

        // Prints every LINE with a given STOP.
        else if ( command == "STOP" ) { lines_with_stop(tramdata, cmd_parts); }

        // Gives the distance between STOPs in a LINE.
        else if ( command == "DISTANCE" ) { distance(tramdata, cmd_parts); }

        // Adds a new LINE to the database.
        else if ( command == "ADDLINE" ) { addline(tramdata, cmd_parts); }

        // Adds a new STOP to a LINE.
        else if ( command == "ADDSTOP" ) { addstop(tramdata, cmd_parts); }

        // Removes a STOP from every LINE.
        else if ( command == "REMOVE" ) { remove_stop(tramdata, cmd_parts); }

        // Erroneus command.
        else { std::cout << "Error: Invalid input." << std::endl; }
    }
}

// The most magnificent function in this whole program.
// Prints a RASSE
void print_rasse()
{
    std::cout <<
                 "=====//==================//===\n"
                 "  __<<__________________<<__   \n"
                 " | ____ ____ ____ ____ ____ |  \n"
                 " | |  | |  | |  | |  | |  | |  \n"
                 " |_|__|_|__|_|__|_|__|_|__|_|  \n"
                 ".|                  RASSE   |. \n"
                 ":|__________________________|: \n"
                 "___(o)(o)___(o)(o)___(o)(o)____\n"
                 "-------------------------------" << std::endl;
}

// Short and sweet main.
int main()
{
    // Main container, inner vector in the form of {LINE, STOP, DISTANCE}.
    std::vector<std::vector<std::string>> tramdata;
    print_rasse();
    // Reads file and updates the main container.
    if ( not read_file(tramdata) ) { return EXIT_FAILURE; }
    // Interface, i.e. user input commands.
    interface(tramdata);

    return EXIT_SUCCESS;
}
