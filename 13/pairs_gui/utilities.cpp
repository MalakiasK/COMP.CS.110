#include "utilities.hh"
#include "math.h"

#include <fstream>
#include <algorithm>

std::vector<int> utilities::getClosestFactors(int input)
{
    int factor = sqrt(input);
    while ( input % factor != 0 )
    {
        factor--;
    }
    return {factor, input / factor};
}

void utilities::readHighScoreFile(std::string filename,
                                  std::vector<std::string>& nameData)
{
    std::ifstream file(filename);

    if ( not file )
    {
        // std::cout << "Error opening file.";
        return;
    }

    std::string row;
    while ( getline(file, row))
    {
        std::vector<std::string> playerData;
        playerData = split(row, ';');

        if ( playerData.empty()) { break; }

        std::string playerName;
        playerName = playerData.at(0);

        nameData.push_back(playerName);

    }
    file.close();

    return;
}

void utilities::saveToHighScoreFile(std::string filename,
                                    std::vector<Player *> players)
{
    saveNewData(filename, players);
    overwriteOldData(filename, players);
}

void utilities::saveNewData(std::string filename,
                            std::vector<Player *> players)
{
    std::ofstream fileOut;
    fileOut.open((filename), std::ios::app);

    if ( !fileOut )
    {
        // std::cout << "Error opening file!" << std::endl;
        return;
    }

    // Every player in high score data.
    std::vector<std::string> nameData;
    readHighScoreFile(filename, nameData);

    std::string data;
    std::string name;

    for ( Player* player : players )
    {
        // Player not found in database.
        if ( std::find(nameData.begin(), nameData.end(),
                  player->getName().toStdString()) == nameData.end() )
        {
            // Add to file.
            name = player->getName().toStdString();

            // Enter scores as zero, as they will be overwritten
            // to correct values later.
            data = name + ";0;0" + "\n";

            fileOut << data;
        }
    }

    fileOut.close();
}

void utilities::overwriteOldData(std::string filename,
                                 std::vector<Player *> players)
{
    std::ifstream fileIn(filename);
    std::ofstream fileOut("Resources/temp.txt");

    if ( !fileIn || !fileOut )
    {
        // std::cout << "Error opening files!" << std::endl;
        return;
    }

    std::string strTemp;

    std::string name;
    int newLifetimeScore;
    int newHighScore;

    for ( Player* player : players )
    {
        while ( fileIn >> strTemp )
        {
            std::vector<std::string> oldData;
            oldData = split(strTemp, ';');

            name = player->getName().toStdString();

            // Existing data found.
            if ( name == oldData.at(0) )
            {
                std::string oldLifetimeScore = oldData.at(2);
                newLifetimeScore = std::stoi(oldLifetimeScore) +
                                       player->numberOfPairs();

                // New high score from single game.
                if ( player->numberOfPairs() > std::stoul(oldData.at(1)) )
                {
                    newHighScore = player->numberOfPairs();
                }
                // Old high score is still the highest.
                else
                {
                    newHighScore = std::stoi(oldData.at(1));
                }

                strTemp = name + ";" + std::to_string(newHighScore)
                               + ";" + std::to_string(newLifetimeScore);
            }

            strTemp += "\n";
            fileOut << strTemp;
        }
    }

    fileIn.close();
    remove("Resources/highscores.txt");

    fileOut.close();
    rename("Resources/temp.txt", "Resources/highscores.txt");
}

void utilities::getHighScores(std::string filename, unsigned int amount,
                              std::vector<std::vector<std::string>>& topPlayers)
{
    std::ifstream fileIn(filename);

    if ( !fileIn )
    {
        // std::cout << "Error opening file!" << std::endl;
        return;
    }

    std::string row;

    while ( getline(fileIn, row))
    {
        std::vector<std::string> playerData;
        playerData = split(row, ';');

        if ( playerData.empty() ) { break; }

        if ( topPlayers.size() < amount )
        {
            topPlayers.push_back(playerData);
        }
        else
        {
            // Sort based on Lifetime Score.
            sortByLifetimeScore(topPlayers);

            // Compare to smallest score.
            if (std::stoi(playerData.at(2)) > std::stoi(topPlayers.back().at(2)))
            {
                topPlayers.pop_back();
                topPlayers.push_back(playerData);
            }
        }
    }

    fileIn.close();

    // Final sort before returning.
    sortByLifetimeScore(topPlayers);

    return;
}

std::vector<std::string> utilities::split(std::string& str, char delim)
{
    std::vector<std::string> result = {""};
    bool cont = false;
    for ( auto cha : str )
    {
        if ( cha == '"' )
        {
            cont = not cont;
        }
        else if ( cha == delim and not cont)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(cha);
        }
    }
    if ( result.back() == "" )
    {
        result.erase(--result.end());
    }
    return result;
}

void utilities::sortByLifetimeScore(
        std::vector<std::vector<std::string>>& topPlayers)
{
    std::sort(topPlayers.begin(), topPlayers.end(),
              [](const std::vector<std::string>& a,
                 const std::vector<std::string>& b)
    {
        return std::stoi(a.at(2)) > std::stoi(b.at(2));
    });
}
