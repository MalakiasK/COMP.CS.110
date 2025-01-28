#include "careperiod.hh"
#include <iostream>

CarePeriod::CarePeriod(const std::string& start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::CarePeriod(const Date &start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::~CarePeriod()
{
}



void CarePeriod::SetEndDate(Date endDate)
{
    if ( end_.is_default() )
    {
        end_ = endDate;
    }
}

void CarePeriod::AssignStaff(Person* staff)
{
    // Check if <CarePeriod> has ended.
    if ( not end_.is_default()) { return; }

    // Check if staff is already assigned.
    for ( Person* specialist : staff_ )
    {
        if ( specialist->get_id() == staff->get_id() )
        {
            return;
        }
    }
    staff_.push_back(staff);
}

void CarePeriod::PrintPatientInfo()
{
    std::cout << "* Care period: ";
    start_.print();
    std::cout << " - ";
    if ( not end_.is_default() ) { end_.print(); }
    std::cout << std::endl;

    if ( staff_.empty() )
    {
        std::cout << "  - Staff: None" << std::endl;
    }
    else
    {
        std::cout << "  - Staff: ";
        // Cycle through staff
        for ( auto staff : staff_ )
        {
            staff->print_id();
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void CarePeriod::PrintStaffInfo(Person *staff, int& ctr)
{
    // Check where a staff member has been assigned
    for ( auto specialist : staff_ )
    {
        if ( specialist->get_id() == staff->get_id() )
        {
            start_.print();
            std::cout << " - ";
            if ( not end_.is_default() ) { end_.print(); }
            std::cout << std::endl;
            std::cout << "* Patient: ";
            patient_->print_id();
            std::cout << std::endl;
            ++ctr;
        }
    }
}
