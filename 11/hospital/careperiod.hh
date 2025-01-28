/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "person.hh"
#include "date.hh"
#include <string>

class CarePeriod
{
public:
    // Constructor, start date given as a string (ddmmyyyy).
    CarePeriod(const std::string& start, Person* patient);

    // Constructor, start date given as a Date object.
    CarePeriod(const Date& start, Person* patient);

    // Destructor.
    ~CarePeriod();

    // More public methods

    /**
     * @brief SetEndDate
     * @param endDate
     */
    void SetEndDate(Date endDate);

    /**
     * @brief AssignStaff
     * @param staff
     */
    void AssignStaff(Person* staff);

    /**
     * @brief PrintPatientInfo
     * Prints a patient's Care period and possible staff that is related.
     */
    void PrintPatientInfo();

    /**
     * @brief PrintStaffInfo
     * @param staff
     * @param ctr, counter
     *
     * @note ctr/'counter' is used to measure if a staff member
     * has zero patients.
     */
    void PrintStaffInfo(Person* staff, int& ctr);

private:

    Person* patient_;
    Date start_;
    Date end_;

    // Staff linked to CarePeriod.
    std::vector<Person*> staff_;

};

#endif // CAREPERIOD_HH
