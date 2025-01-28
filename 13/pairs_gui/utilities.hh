#ifndef UTILITIES_HH
#define UTILITIES_HH

#include "player.hh"
#include <vector>
#include <QString>

namespace utilities
{
    /**
     * @brief getClosestFactors
     * @param input
     * @return Returns the two closest factors to a given number.
     * i.e. 12 -> {4,3}
     */
    std::vector<int> getClosestFactors(int input);

    /**
     * @brief readHighScoreFile
     * @param filename, highscores.txt
     * @param nameData, container for every name.
     * Gets every name in the highscores.txt file.
     */
    void readHighScoreFile(std::string filename,
                           std::vector<std::string>& nameData);

    /**
     * @brief saveToHighScoreFile
     * @param filename, highscores.txt
     * @param players, Current game's players' datas.
     * Save new data to the file and overwrite old data.
     */
    void saveToHighScoreFile(std::string filename, std::vector<Player*> players);

    /**
     * @brief saveNewData
     * @param filename, highscores.txt
     * @param players, Current game's players' datas.
     * Save new data to the file.
     */
    void saveNewData(std::string filename, std::vector<Player*> players);

    /**
     * @brief overwriteOldData
     * @param filename, highscores.txt
     * @param players, Current game's players' datas.
     * Overwrites old data.
     */
    void overwriteOldData(std::string filename, std::vector<Player*> players);

    /**
     * @brief getHighScores
     * @param filename, highscores.txt
     * @param amount, How big the top list should be.
     * @param topPlayers, Container for the top players.
     * Gets the highest scores in the file, sort using sortByLifetimeScore.
     */
    void getHighScores(std::string filename, unsigned int amount,
                       std::vector<std::vector<std::string>>& topPlayers);

    /**
     * @brief split
     * @param str
     * @param delim
     * @return vector containing the parts, no delim chars
     * Splits the given string at every delim char
     * Taken from the 'Hospital' project.
     */
    std::vector<std::string> split( std::string& str, char delim = ';');

    /**
     * @brief sortByLifetimeScore
     * @param topPlayers, Container for the top players.
     * Sorts the container by lifetime score from greatest to lowest.
     */
    void sortByLifetimeScore(std::vector<std::vector<std::string>>& topPlayers);

}

#endif // UTILITIES_HH
