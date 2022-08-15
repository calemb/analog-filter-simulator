#include "ra/filters.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>


/*
Purpose: Take a user's input and check if valid
Inputs:
    value   (T) :   Value which has its value set to input

Note: T will only ever value_type (double) or int
*/
template <class T>
void get_input(T& value){
    std::string user_input;
    std::cin >> user_input;
    int decimal = 0;
    T scale = 1.0;

    // Check if input is valid number
    for (int i = 0; i < user_input.length(); ++i){
        if (decimal && user_input[i] == '.'){
            std::cout << "Invalid input: please re-enter value.\n";
            get_input(value);
            return;
        } else if (user_input[i] == '.'){
            decimal = 1;
        }
        if (i == user_input.length() - 1) {
            // Last digit
            if (isdigit(user_input[i]) == false && user_input[i] != '.' && user_input[i] != 'p' && user_input[i] != 'n' && user_input[i] != 'u'
                    && user_input[i] != 'm' && user_input[i] != 'k' && user_input[i] != 'M'){
                std::cout << "Invalid input: please re-enter value.\n";
                get_input(value);
                return;
            } else {
                if (user_input[i] == 'p' || user_input[i] == 'n' || user_input[i] == 'u'
                    || user_input[i] == 'm' || user_input[i] == 'k' ||user_input[i] == 'M'){
                    // Input has post-fix
                    if (user_input[i] == 'p')
                        scale = 1e-12;
                    else if (user_input[i] == 'n')
                        scale = 1e-9;
                    else if (user_input[i] == 'u')
                        scale = 1e-6;
                    else if (user_input[i] == 'm')
                        scale = 1e-3;
                    else if (user_input[i] == 'k')
                        scale = 1e3;
                    else if (user_input[i] == 'M')
                        scale = 1e6;
                    
                    // Remove last character of input
                    user_input.pop_back();
                }
                
            }
        } else if (isdigit(user_input[i]) == false && user_input[i] != '.'){
            std::cout << "Invalid input: please re-enter value.\n";
            get_input(value);
            return;
        }
    }

    // Convert to T
    value = T(std::atof(user_input.c_str())) * scale;
}

/*
Purpose: Given a filter, choose and return the desired output data
Inputs:
    f   (filter)    :   filter object
*/
std::string choose_output(ra::filters::filter f, int filter_type, int filter_order){
    // User chooses output
    int output_type;
    std::cout << "Please enter desired output type:\n1. Magnitude Response 2. Phase Response\n";
    get_input(output_type);

    // Get result
    std::string result;

    if (output_type == 1){
        double fmin, fmax, step;
        std::cout << "Please enter desired minimum frequency, maximum frequency, and step size\n";
        get_input(fmin);
        get_input(fmax);
        get_input(step);
        result = f.get_magnitude_response(fmin, fmax, step, filter_type, filter_order);
    } else if (output_type == 2){
        double fmin, fmax, step;
        std::cout << "Please enter desired minimum frequency, maximum frequency, and step size\n";
        get_input(fmin);
        get_input(fmax);
        get_input(step);
        result = f.get_phase_response(fmin, fmax, step, filter_type, filter_order);
    } else {
        // Invalid
        std::cout << "Invalid input. Please choose 1, 2, or 3.\n";
        return choose_output(f, filter_type, filter_order);
    }
    
    return result;
}

/*
Purpose: Given a string s, print to file or console
Inputs:
    s   (std::string)   :   input string to be printed
*/
void print_output(const std::string& s){
    // Choose output format
    int output_format;

    std::cout << "Please choose output format:\n1. Text file 2. Console\n";
    get_input(output_format);

    if (output_format == 1){
        // Print to text file

        // Get file name
        std::string file_name;
        std::cout << "Please enter desired file name (note that this will overwrite the file's current contents)\n";
        std::cin >> file_name;

        // Print to file
        std::ofstream out(file_name);
        out << s;
        out.close();
        std::cout << "Printed output to " << file_name << "\n";
    } else if (output_format == 2){
        // Print to console
        std::cout << s;
    } else {
        // Invalid input
        std::cout << "Invalid choice. Please choose either 1 or 2.\n";
        print_output(s);
        return;
    }
    return;
}


/*
Purpose: Main function which calls sequence of user input requests, calculations, and prints
*/
int main() {

    int filter_type = 0;
    int filter_order = 0;
    double R, L, C;

    std::cout << "Welcome to the analog filter simulator!\n";

    // Get filter type and sub-type
    std::cout << "Please enter desired filter components:\n1. RC 2. RL 3. RLC\n";
    get_input(filter_order);
    if (filter_order == 1 || filter_order == 2) {
        // RC or RL
        std::cout << "Please enter desired filter's type:\n1. Lowpass filter 2. Highpass filter\n";
    } else if (filter_order == 3){
        // RLC
        std::cout << "Please enter desired filter's type:\n1. Lowpass filter 2. Highpass filter 3. Bandpass filter 4. Bandstop filter\n";
    } else {
        std::cout << "Invalid input. Please enter a valid number.\n";
        return 1;
    }
    get_input(filter_type);

    // Get filter values
    std::vector<double> values;
    std::cout << "Please enter desired filter values:\n";

    if (filter_order == 1){
        // RC
        std::cout << "R: ";
        get_input(R);
        std::cout << "C: ";
        get_input(C);
        values.push_back(R);
        values.push_back(C);
    } else if (filter_order == 2){
        // RL
        std::cout << "R: ";
        get_input(R);
        std::cout << "L: ";
        get_input(L);
        values.push_back(R);
        values.push_back(L);
    } else if (filter_order == 3){
        // RLC
        std::cout << "R: ";
        get_input(R);
        std::cout << "L: ";
        get_input(L);
        std::cout << "C: ";
        get_input(C);
        values.push_back(R);
        values.push_back(L);
        values.push_back(C);
    } else {
        std::cout << "Invalid user input.";
        return 1;
    }

    // Create filter
    ra::filters::filter f(values, filter_type, filter_order);

    int done = 0;
    
    while(!done){
        std::string result = choose_output(f, filter_type, filter_order);
        std::string answer;
        print_output(result);
        std::cout << "Compute another output? (y/n)\n";
        std::cin >> answer;
        if (answer == "n"){
            done = 1;
        }
    }

    return 0;

}