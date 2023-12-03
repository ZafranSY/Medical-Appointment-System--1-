#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <functional>  // Include for std::function

using namespace std;

class Appointment {
public:
    string patientName;
    string doctorName;
    string appointmentDate; // Date for the appointment
    string appointmentTime;
    string icNumber;       // Identity Card number
    string phoneNumber;    // Phone number
    string appointmentReason; // Reason for the appointment

    Appointment(const string& pName, const string& dName, const string& aTime,
                const string& aDate, const string& icNum, const string& phone, const string& reason)
        : patientName(pName), doctorName(dName), appointmentTime(aTime), appointmentDate(aDate),
          icNumber(icNum), phoneNumber(phone), appointmentReason(reason) {}

    void display() const {
        cout << "Patient: " << patientName << ", IC Number: " << icNumber
             << ", Phone: " << phoneNumber << ", Doctor: " << doctorName
             << ", Date: " << appointmentDate << ", Time: " << appointmentTime << ", Reason: " << appointmentReason << endl;
    }
    
    void reschedule(const string& newDate, const string& newTime) {
        appointmentDate = newDate;
        appointmentTime = newTime;
    }
};


void displayAppointments(const vector<Appointment>& appointments) {
    for (int i = 0; i < appointments.size(); i++) {
        cout << i + 1 << ". ";
        appointments[i].display();
    }
}

void addAppointment(vector<Appointment>& appointments) {
    string patientName, doctorName, appointmentTime, appointmentDate, icNumber, phoneNumber, appointmentReason;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

    cout << "Enter patient name: ";
    getline(cin, patientName);

    cout << "Enter IC number: ";
    getline(cin, icNumber);

    cout << "Enter phone number: ";
    getline(cin, phoneNumber);

    cout << "Enter doctor name: ";
    getline(cin, doctorName);

    cout << "Enter appointment date: ";
    getline(cin, appointmentDate);

    cout << "Enter appointment time: ";
    getline(cin, appointmentTime);

    cout << "Enter reason for appointment: ";
    getline(cin, appointmentReason);

    appointments.emplace_back(patientName, doctorName, appointmentDate, appointmentTime, icNumber, phoneNumber, appointmentReason);
}



void rescheduleAppointment(vector<Appointment>& appointments) {
    int index;
    string newTime, newDate;

    displayAppointments(appointments);
    cout << "Select the appointment number to reschedule: ";
    cin >> index;

    if (index < 1 || index > appointments.size()) {
        cout << "Invalid appointment number!" << endl;
        return;
    }

    cout << "Enter new appointment date: ";
    cin >> newDate;

    cout << "Enter new appointment time: ";
    cin >> newTime;

    appointments[index - 1].reschedule(newDate, newTime);
    cout << "Appointment rescheduled." << endl;
}

void showMenuAdmin() {
    cout << "1. View Appointments" << endl;
    cout << "2. Add Appointment" << endl;
    cout << "3. Reschedule Appointment" << endl;
    cout << "4. Filter Appointment" << endl;
    cout << "0. Exit" << endl;
}



void showMenuPatient() {
    cout << "1. Check My Appointments" << endl;
    cout << "0. Exit" << endl;
}

void saveAppointmentsToFile(const vector<Appointment>& appointments) {
    ofstream file("appointments.txt");
    for (const auto& appointment : appointments) {
        file << appointment.patientName << "|" 
             << appointment.icNumber << "|"
             << appointment.phoneNumber << "|"
             << appointment.doctorName << "|" 
             << appointment.appointmentDate << "|"
             << appointment.appointmentTime << "|"
             << appointment.appointmentReason << endl;
    }
    file.close();
    cout << "Appointments saved to file." << endl;
}


void loadAppointmentsFromFile(vector<Appointment>& appointments) {
    ifstream file("appointments.txt");
    string line;
    string patientName, doctorName, appointmentDate, appointmentTime, icNumber, phoneNumber, appointmentReason;

    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, patientName, '|');
        getline(iss, icNumber, '|');
        getline(iss, phoneNumber, '|');
        getline(iss, doctorName, '|');
        getline(iss, appointmentDate, '|');
        getline(iss, appointmentTime, '|');
        getline(iss, appointmentReason);

        // Trim leading and trailing spaces
        patientName.erase(patientName.find_last_not_of(" \n\r\t") + 1);
        icNumber.erase(icNumber.find_last_not_of(" \n\r\t") + 1);
        phoneNumber.erase(phoneNumber.find_last_not_of(" \n\r\t") + 1);
        doctorName.erase(doctorName.find_last_not_of(" \n\r\t") + 1);
        appointmentDate.erase(appointmentDate.find_last_not_of(" \n\r\t") + 1);
        appointmentTime.erase(appointmentTime.find_last_not_of(" \n\r\t") + 1);
        appointmentReason.erase(appointmentReason.find_last_not_of(" \n\r\t") + 1);

        appointments.emplace_back(patientName, doctorName, appointmentDate, appointmentTime, icNumber, phoneNumber, appointmentReason);
    }
    file.close();
}

void bubbleSort(vector<Appointment>& appointments, function<bool(const Appointment&, const Appointment&)> comparator) {
    int n = appointments.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (comparator(appointments[j], appointments[j + 1])) {
                swap(appointments[j], appointments[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

void displayAppointments(vector<Appointment>& appointments) {
    int sortOption;
    cout << "Sort by: 1 - Name, 2 - IC Number, 3 - Phone Number, 4 - Doctor Name, 5 - Appointment Date, 6 - Appointment Reason, 0 - No Sort: ";
    cin >> sortOption;

    if (sortOption == 1) {
        bubbleSort(appointments, [](const Appointment& a, const Appointment& b) {
            return a.patientName > b.patientName;
        });
    } else if (sortOption == 2) {
        bubbleSort(appointments, [](const Appointment& a, const Appointment& b) {
            return a.icNumber > b.icNumber;
        });
    } else if (sortOption == 3) {
        bubbleSort(appointments, [](const Appointment& a, const Appointment& b) {
            return a.phoneNumber > b.phoneNumber;
        });
    } else if (sortOption == 4) {
        bubbleSort(appointments, [](const Appointment& a, const Appointment& b) {
            return a.doctorName > b.doctorName;
        });
    } else if (sortOption == 5 || sortOption == 0) {
	    bubbleSort(appointments, [](const Appointment& a, const Appointment& b) {
	        if (a.appointmentDate == b.appointmentDate) {
	            return a.appointmentTime > b.appointmentTime;
	        }
	        return a.appointmentDate > b.appointmentDate;
	    });
	} else if (sortOption == 6) {
        bubbleSort(appointments, [](const Appointment& a, const Appointment& b) {
            return a.appointmentReason > b.appointmentReason;
        });
    }

    for (const auto& appointment : appointments) {
        appointment.display();
    }
}

void filterAppointments(const vector<Appointment>& appointments) {
    int filterOption;
    string filterValue;

    cout << "Filter by: 1 - Name, 2 - IC Number, 3 - Phone Number, 4 - Doctor Name, 5 - Date, 6 - Time: ";
    cin >> filterOption;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

    cout << "Enter value to filter by: ";
    getline(cin, filterValue);

    bool found = false;
    for (const auto& appointment : appointments) {
        switch (filterOption) {
            case 1: // Name
                if (appointment.patientName == filterValue) {
                    appointment.display();
                    found = true;
                }
                break;
            case 2: // IC Number
                if (appointment.icNumber == filterValue) {
                    appointment.display();
                    found = true;
                }
                break;
            case 3: // Phone Number
                if (appointment.phoneNumber == filterValue) {
                    appointment.display();
                    found = true;
                }
                break;
            case 4: // Doctor Name
                if (appointment.doctorName == filterValue) {
                    appointment.display();
                    found = true;
                }
                break;
            case 5: // Date
                if (appointment.appointmentDate == filterValue) {
                    appointment.display();
                    found = true;
                }
                break;
            case 6: // Time
                if (appointment.appointmentTime == filterValue) {
                    appointment.display();
                    found = true;
                }
                break;
            default:
                cout << "Invalid filter option." << endl;
                return;
        }
    }

    if (!found) {
        cout << "No appointments found for the given criteria." << endl;
    }
}

int linearSearchByIC(const vector<Appointment>& appointments, const string& icNumber) {
    for (int i = 0; i < appointments.size(); i++) {
        if (appointments[i].icNumber == icNumber) {
            return i; // Return the index of the appointment that matches the IC number
        }
    }
    return -1; // Return -1 if no matching appointment is found
}

void searchAppointmentsByUserDetails(const vector<Appointment>& appointments) {
    string icNumber, phoneNumber, fullName;
    
    
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    
    cout << "Enter your full name: ";
    getline(cin, fullName);
    cout << "Enter your IC number: ";
    getline(cin, icNumber);
    cout << "Enter your phone number: ";
    getline(cin, phoneNumber);

    bool found = false;
    for (const auto& appointment : appointments) {
        if (appointment.patientName == fullName && 
            appointment.icNumber == icNumber && 
            appointment.phoneNumber == phoneNumber) {
            appointment.display();
            found = true;
        }
    }

    if (!found) {
        cout << "No matching appointments found." << endl;
    }
}



int main() {
    vector<Appointment> appointments;
    int userType, choice;
    loadAppointmentsFromFile(appointments);

    do {  	
	    cout << "Select User Type: 1 for Patient, 2 for Administrator, 0 for Exit" << endl;
	    cin >> userType;
	    system("cls");
        if (userType == 1) {
            showMenuPatient();
            cin >> choice;
	    	system("cls");
            switch (choice) {
                case 1:
                    searchAppointmentsByUserDetails(appointments);
                    break;
                case 0:
                    break;
                default:
                    cout << "Invalid choice" << endl;
            }
        } else if (userType == 2) {
            showMenuAdmin();
            cin >> choice;
	    	system("cls");
            switch (choice) {
                case 1:
                    displayAppointments(appointments);
                    break;
                case 2:
                    addAppointment(appointments);
                    break;
                case 3:
                    rescheduleAppointment(appointments);
                    break;
                case 4:
					filterAppointments(appointments);
                    break;
                case 0:
                    break;
                default:
                    cout << "Invalid choice" << endl;
            }
        }
        cout << endl << endl;
        system("pause");
	    system("cls");
        saveAppointmentsToFile(appointments);
        cout << endl << endl;
        system("pause");
	    system("cls");
    } while (userType != 0);

    return 0;
}

