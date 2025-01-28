#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <set>
#include <algorithm>

Hospital::Hospital()
{
}

Hospital::~Hospital()
{
    // Deallocate staff.
    for( std::map<std::string, Person*>::iterator
         iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        delete iter->second;
    }

    // Deallocate patient's Care periods.
    // Then deallocate corresponding patient.
    for ( unsigned int i = 0; i < patientDatabase_.size(); ++i )
    {
        // Careperiods.
        for ( auto CareData : patientDatabase_.at(i).second.second )
        {
            delete CareData;
        }
        // Patient.
        delete patientDatabase_.at(i).second.first;
    }
}

void Hospital::recruit(Params params)
{
    std::string specialist_id = params.at(0);
    if( staff_.find(specialist_id) != staff_.end() )
    {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    Person* new_specialist = new Person(specialist_id);
    staff_.insert({specialist_id, new_specialist});
    std::cout << STAFF_RECRUITED << std::endl;
}

void Hospital::enter(Params params)
{
    // ID for new patient.
    std::string patientId;
    patientId = params.at(0);

    // Check if patient with the same ID is currently in the hospital.
    if ( currentPatients_.find(patientId) != currentPatients_.end() )
    {
        std::cout << ALREADY_EXISTS << patientId << std::endl;
        return;
    }

    // Check if patient is in the hospital's database (known patient).
    for ( unsigned int i = 0; i < patientDatabase_.size(); ++i )
    {
        if ( patientDatabase_.at(i).first == patientId )
        {
            Person* oldPatient;
            oldPatient = patientDatabase_.at(i).second.first;

            // Add to <currentPatients_>
            // and hospital's database <patientDatabase_>.
            currentPatients_.insert( {patientId, oldPatient} );

            CarePeriod* newCarePeriod;
            newCarePeriod = new CarePeriod(utils::today, oldPatient);

            // Add care period to vector containing patient's care periods.
            patientDatabase_.at(i).second.second.push_back(newCarePeriod);

            // Print confirmation.
            std::cout << PATIENT_ENTERED << std::endl;
            return;
        }
    }

    // Create Person-object.
    // Create pointer to new person.
    Person* newPatient;
    newPatient = new Person(patientId);

    // Add to <currentPatients_> and hospital's database <patientDatabase_>.
    currentPatients_.insert( {patientId, newPatient} );

    // Create a new <CarePeriod> for the new patient.
    CarePeriod* new_CarePeriod;
    new_CarePeriod = new CarePeriod(utils::today, newPatient);

    patientDatabase_.push_back( {patientId, {newPatient, {new_CarePeriod}}} );

    // Print confirmation.
    std::cout << PATIENT_ENTERED << std::endl;
}

void Hospital::leave(Params params)
{
    // ID of the patient.
    std::string patientId;
    patientId = params.at(0);

    // Check if a patient with the ID is not currently in the hospital.
    if ( currentPatients_.find(patientId) == currentPatients_.end() )
    {
        std::cout << CANT_FIND << patientId << std::endl;
        return;
    }

    // Set an end date for the <CarePeriod>.
    // Get a <CarePeriod> that hasn't ended.
    for ( unsigned int i = 0; i < patientDatabase_.size(); ++i )
    {
        if ( patientDatabase_.at(i).first == patientId )
        {
            for ( auto period : patientDatabase_.at(i).second.second )
            {
                period->SetEndDate(utils::today);
            }
        }
    }

    // Remove from <currentPatients_>.
    currentPatients_.erase(currentPatients_.find(patientId));

    // Print confirmation.
    std::cout << PATIENT_LEFT << std::endl;
}

void Hospital::assign_staff(Params params)
{
    std::string staffId;
    std::string patientId;
    staffId = params.at(0);
    patientId = params.at(1);

    // Check for unknown staff member or patient.
    if ( staff_.find(staffId) == staff_.end() )
    {
        std::cout << CANT_FIND << staffId << std::endl;
        return;
    }
    if ( currentPatients_.find(patientId) == currentPatients_.end() )
    {
        std::cout << CANT_FIND << patientId << std::endl;
        return;
    }

    Person* staff;
    staff = staff_.find(staffId)->second;

    // Add staff to a <Careperiod> that hasn't yet ended.
    // Only one <Careperiod> per patient can be active at a time.
    for ( unsigned int i = 0; i < patientDatabase_.size(); ++i )
    {
        if ( patientDatabase_.at(i).first == patientId )
        {
            for ( auto period : patientDatabase_.at(i).second.second )
            {
                period->AssignStaff(staff);
            }
        }
    }

    // Print confirmation.
    std::cout << STAFF_ASSIGNED << patientId << std::endl;
}

void Hospital::add_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string strength = params.at(1);
    std::string dosage = params.at(2);
    std::string patient = params.at(3);
    if( not utils::is_numeric(strength, true) or
        not utils::is_numeric(dosage, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::map<std::string, Person*>::const_iterator
            patient_iter = currentPatients_.find(patient);
    if( patient_iter == currentPatients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    std::cout << MEDICINE_ADDED << patient << std::endl;
}

void Hospital::remove_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map<std::string, Person*>::const_iterator
            patient_iter = currentPatients_.find(patient);
    if( patient_iter == currentPatients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->remove_medicine(medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}

void Hospital::print_patient_info(Params params)
{
    std::string patientId;
    patientId = params.at(0);

    // Check if patient is not in the hospital's database (unknown patient).
    int ctr = 0;
    for ( unsigned int i = 0; i < patientDatabase_.size(); i++ )
    {
        if ( patientDatabase_.at(i).first == patientId ) { ++ctr; break;}
    }
    if ( ctr == 0 )
    {
        std::cout << CANT_FIND << patientId << std::endl;
        return;
    }

    for ( auto patientData : patientDatabase_ )
    {
        if ( patientData.first == patientId )
        {
            // Print info of a <CarePeriod>.
            for ( auto period : patientData.second.second )
            {
                period->PrintPatientInfo();
            }

            // Print info of possible medicines.
            std::cout << "* Medicines:";
            patientData.second.first->print_medicines("  - ");
        }
    }
}

void Hospital::print_care_periods_per_staff(Params params)
{
    std::string staffId;
    staffId = params.at(0);

    if ( staff_.find(staffId) == staff_.end() )
    {
        std::cout << CANT_FIND << staffId << std::endl;
        return;
    }

    Person* staff;
    staff = staff_.find(staffId)->second;
    int ctr = 0;

    // Cycle through database.
    for ( auto patienData : patientDatabase_ )
    {
        for ( auto period : patienData.second.second )
        {
            period->PrintStaffInfo(staff, ctr);
        }
    }
    if ( ctr == 0 ) { std::cout << "None" << std::endl; }
}

void Hospital::print_all_medicines(Params)
{
    // Collect every unique medicine prescribed to patients.
    std::vector<std::string> uniqueMedicines;

    for ( unsigned int i = 0; i < patientDatabase_.size(); i++ )
    {
        // Vector for a patient's prescribed medicines.
        std::vector<std::string> medicines;
        medicines = patientDatabase_.at(i).second.first->get_medicines();
        for ( auto med : medicines )
        {
            if ( std::find(uniqueMedicines.begin(), uniqueMedicines.end(), med) == uniqueMedicines.end() )
            {
                uniqueMedicines.push_back(med);
            }
        }
    }
    if ( uniqueMedicines.empty() ) { std::cout << "None" << std::endl; return; }

    // Sort unique medicines alphabetically.
    std::sort(uniqueMedicines.begin(), uniqueMedicines.end());

    // Sort hospital's patients alphabetically by ID.
    // Using a lambda function.
    // To be honest, I'm not 100% sure why this works, yet...
    std::sort(patientDatabase_.begin(), patientDatabase_.end(),
              [](std::pair<std::string,
                 std::pair<Person*, std::vector<CarePeriod*>>> a,
                 std::pair<std::string,
                 std::pair<Person*, std::vector<CarePeriod*>>> b)
    {
        return a.first < b.first;
    });

    // Cycle through unique medicines and print corresponding patients.
    for ( std::string med : uniqueMedicines )
    {
        std::cout << med << " prescribed for" << std::endl;
        for ( unsigned int i = 0; i < patientDatabase_.size(); i++ )
        {
            std::vector<std::string> meds;
            meds = patientDatabase_.at(i).second.first->get_medicines();
            if ( std::find(meds.begin(), meds.end(), med) != meds.end())
            {
                std::cout << "* ";
                patientDatabase_.at(i).second.first->print_id();
                std::cout << std::endl;
            }
        }
    }
}

void Hospital::print_all_staff(Params)
{
    if( staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    for( std::map<std::string, Person*>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        std::cout << iter->first << std::endl;
    }
}

void Hospital::print_all_patients(Params)
{
    if ( patientDatabase_.empty() ) {std::cout << "None" << std::endl; return;}
    // Sort hospital patient database to alphabetical order by patient id.
    // Using a lambda function.
    // To be honest, I'm not 100% sure why this works, yet...
    std::sort(patientDatabase_.begin(), patientDatabase_.end(),
              [](std::pair<std::string,
                 std::pair<Person*, std::vector<CarePeriod*>>> a,
                 std::pair<std::string,
                 std::pair<Person*, std::vector<CarePeriod*>>> b)
    {
        return a.first < b.first;
    });

    // Print patient info.
    for ( unsigned int i = 0; i < patientDatabase_.size(); i++ )
    {
        patientDatabase_.at(i).second.first->print_id();
        std::cout << std::endl;
        Params params = {patientDatabase_.at(i).first};
        print_patient_info(params);
    }
}

void Hospital::print_current_patients(Params)
{
    if ( currentPatients_.empty() ) { std::cout << "None" << std::endl; return; }

    // No need to sort,
    // as <Map> is already sorted alphabetically (by ID) by default.

    // Print patients.
    for ( auto patient : currentPatients_ )
    {
        patient.second->print_id();
        std::cout << std::endl;
        Params params = {patient.first};
        print_patient_info(params);
    }
}

void Hospital::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not utils::is_numeric(day, false) or
        not utils::is_numeric(month, false) or
        not utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}
