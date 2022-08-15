#ifndef filters_hpp
#define filters_hpp

#include <string>
#include <vector>
#include <complex>
#include <cmath>
#include <iostream>

# define M_PI 3.14159265358979323846

namespace ra {
    namespace filters {

        class filter {
        public:

            using value_type = double;

            // Constructor for filter (given type (string) and values (vector))

            // Constructor where R, L, C given
            // Values listed: R1 R2 R3 L1 L2 C1 etc.
            filter(std::vector<value_type> values, int filter_type, int filter_order) : values_(values), filter_type_(filter_type), filter_order_(filter_order) {}

            // Copy & Move & operator=
            filter(const filter&) = default;
            filter(filter&&) = default;
            filter& operator=(const filter&) = default;
            filter& operator=(filter&&) = default;
            
            // Destructor
            ~filter() = default;

            // Get values of filter
            std::vector<value_type> get_values() const {
                return values_;
            }

            // Get type of filter
            int get_filter_type() const {
                return filter_type_;
            }

            /*
            Purpose: Return string including coordinate points for magnitude response of filter
            Inputs:     fmin (value_type)       :   minimum frequency
                        fmax (value_type)       :   maximum frequency
                        step_size (value_type)  :   step size of plot
            */
            std::string get_magnitude_response(value_type fmin, value_type fmax, value_type step_size = 1.0, int filter_type = 1, int filter_order = 1){
                std::string result;
                std::complex<value_type> w(0,0);
                std::complex<value_type> j(0,1);
                value_type f(0);

                // Switch to filter sub-type: RC, RL, or RLC
                switch(filter_order){
                    case 1:
                        {
                            // RC Filter

                            // Get circuit parameters
                            std::complex<value_type> R = values_.at(0);
                            std::complex<value_type> C = values_.at(1);
                            std::complex<value_type> tmp;

                            // Iterate through frequencies
                            for (value_type f = 0; f <= fmax; f += step_size){
                                
                                // Calculate w and H(w)
                                w = 2 * M_PI * f;

                                // Switch to filter type: Lowpass or highpass
                                switch(filter_type){
                                    case 1:
                                        {
                                            // Lowpass
                                            tmp = 1.0 / (1.0 + j * w * R * C);
                                            break;
                                        }
                                    case 2:
                                        {
                                            // Highpass
                                            tmp = (j * w * R * C) / (1.0 + j * w * R * C);
                                            break;
                                        }
                                    default:
                                        {
                                            return "Invalid";
                                            break;
                                        }
                                }

                                // Append frequency, H(f)
                                std::string str_tmp = std::to_string(f);
                                str_tmp.append(", ");
                                str_tmp.append(std::to_string(abs(tmp)));
                                str_tmp.append("\n");

                                result.append(str_tmp);
                            }
                            break;
                        }
                    case 2:
                        {
                            // RL Filter

                            // Get circuit parameters
                            std::complex<value_type> R = values_.at(0);
                            std::complex<value_type> L = values_.at(1);
                            std::complex<value_type> tmp;

                            // Iterate through frequencies
                            for (value_type f = 0; f <= fmax; f += step_size){
                                
                                // Calculate w and H(w)
                                w = 2 * M_PI * f;

                                // Switch to filter type: Lowpass or highpass
                                switch(filter_type){
                                    case 1:
                                        {
                                            // Lowpass
                                            tmp = R / (R + j * w * L);
                                            break;
                                        }
                                    case 2:
                                        {
                                            // Highpass
                                            tmp = (j * w * L) / (R + j * w * L);
                                            break;
                                        }
                                    default:
                                        {
                                            return "Invalid";
                                            break;
                                        }
                                }

                                // Append frequency, H(f)
                                std::string str_tmp = std::to_string(f);
                                str_tmp.append(", ");
                                str_tmp.append(std::to_string(abs(tmp)));
                                str_tmp.append("\n");

                                result.append(str_tmp);
                            }
                            break;
                        }
                    case 3:
                        {
                            // RLC filter

                            // Get circuit parameters
                            std::complex<value_type> R = values_.at(0);
                            std::complex<value_type> L = values_.at(1);
                            std::complex<value_type> C = values_.at(2);
                            std::complex<value_type> tmp;

                            // Iterate through frequencies
                            for (value_type f = 0; f <= fmax; f += step_size){
                                
                                // Calculate w and H(w)
                                w = 2 * M_PI * f;

                                // Switch to filter type: lowpass, highpass, bandpass, bandstop
                                switch(filter_type){
                                    case 1:
                                        {
                                            // Lowpass
                                            tmp = 1.0 / (1.0 - w * w * C * L + j * w * R * C);
                                            break;
                                        }
                                    case 2:
                                        {
                                            // Highpass
                                            tmp = (-w * w) / ((-w * w) + (R * j * w / L) + (1.0 /(L * C)));
                                            break;
                                        }
                                    case 3:
                                        {
                                            // Bandpass
                                            tmp = (j * w * R / L) / ((-w * w) + (j * w * R / L) + (1.0 / (L * C)));
                                            break;
                                        }
                                    case 4:
                                        {
                                            // Bandstop
                                            tmp = ((-w * w) + (1.0 / (L * C))) / ((-w * w) + (j * w * R / L) + (1.0 / (L * C)));
                                            break;
                                        }
                                    default:
                                        {
                                            return "Invalid";
                                            break;
                                        }
                                }

                                // Append frequency, H(f)
                                std::string str_tmp = std::to_string(f);
                                str_tmp.append(", ");
                                str_tmp.append(std::to_string(abs(tmp)));
                                str_tmp.append("\n");

                                result.append(str_tmp);
                            }
                            break;
                        }
                    default:
                        {
                            // Invalid filter type
                            return "Invalid";
                            break;
                        }

                }

                return result;
            }

            /*
            Purpose: Return string including coordinate points for phase response of filter
            Inputs:     fmin (value_type)       :   minimum frequency
                        fmax (value_type)       :   maximum frequency
                        step_size (value_type)  :   step size of plot
            */
            std::string get_phase_response(value_type fmin, value_type fmax, value_type step_size = 1.0, int filter_type = 1, int filter_order = 1){
                std::string result;
                std::complex<value_type> w(0,0);
                std::complex<value_type> j(0,1);
                value_type f(0);

                // Switch to filter sub-type: RC, RL, or RLC
                switch(filter_order){
                    case 1:
                        {
                            // RC Filter

                            // Get circuit parameters
                            std::complex<value_type> R = values_.at(0);
                            std::complex<value_type> C = values_.at(1);
                            std::complex<value_type> tmp;

                            // Iterate through frequencies
                            for (value_type f = 0; f <= fmax; f += step_size){
                                
                                // Calculate w and H(w)
                                w = 2 * M_PI * f;

                                // Switch to filter type: Lowpass or highpass
                                switch(filter_type){
                                    case 1:
                                        {
                                            // Lowpass
                                            tmp = 1.0 / (1.0 + j * w * R * C);
                                            break;
                                        }
                                    case 2:
                                        {
                                            // Highpass
                                            tmp = (j * w * R * C) / (1.0 + j * w * R * C);
                                            break;
                                        }
                                    default:
                                        {
                                            return "Invalid";
                                            break;
                                        }
                                }

                                // Append frequency, H(f)
                                std::string str_tmp = std::to_string(f);
                                str_tmp.append(", ");
                                str_tmp.append(std::to_string(std::arg(tmp) * 180.0 / M_PI));
                                str_tmp.append("\n");

                                result.append(str_tmp);
                            }
                            break;
                        }
                    case 2:
                        {
                            // RL Filter

                            // Get circuit parameters
                            std::complex<value_type> R = values_.at(0);
                            std::complex<value_type> L = values_.at(1);
                            std::complex<value_type> tmp;

                            // Iterate through frequencies
                            for (value_type f = 0; f <= fmax; f += step_size){
                                
                                // Calculate w and H(w)
                                w = 2 * M_PI * f;

                                // Switch to filter type: Lowpass or highpass
                                switch(filter_type){
                                    case 1:
                                        {
                                            // Lowpass
                                            tmp = R / (R + j * w * L);
                                            break;
                                        }
                                    case 2:
                                        {
                                            // Highpass
                                            tmp = (j * w * L) / (R + j * w * L);
                                            break;
                                        }
                                    default:
                                        {
                                            return "Invalid";
                                            break;
                                        }
                                }

                                // Append frequency, H(f)
                                std::string str_tmp = std::to_string(f);
                                str_tmp.append(", ");
                                str_tmp.append(std::to_string(std::arg(tmp) * 180.0 / M_PI));
                                str_tmp.append("\n");

                                result.append(str_tmp);
                            }
                            break;
                        }
                    case 3:
                        {
                            // RLC filter

                            // Get circuit parameters
                            std::complex<value_type> R = values_.at(0);
                            std::complex<value_type> L = values_.at(1);
                            std::complex<value_type> C = values_.at(2);
                            std::complex<value_type> tmp;

                            // Iterate through frequencies
                            for (value_type f = 0; f <= fmax; f += step_size){
                                
                                // Calculate w and H(w)
                                w = 2 * M_PI * f;

                                // Switch to filter type: lowpass, highpass, bandpass, bandstop
                                switch(filter_type){
                                    case 1:
                                        {
                                            // Lowpass
                                            tmp = 1.0 / (1.0 - w * w * C * L + j * w * R * C);
                                            break;
                                        }
                                    case 2:
                                        {
                                            // Highpass
                                            tmp = (-w * w) / ((-w * w) + (R * j * w / L) + (1.0 /(L * C)));
                                            break;
                                        }
                                    case 3:
                                        {
                                            // Bandpass
                                            tmp = (j * w * R / L) / ((-w * w) + (j * w * R / L) + (1.0 / (L * C)));
                                            break;
                                        }
                                    case 4:
                                        {
                                            // Bandstop
                                            tmp = ((-w * w) + (1.0 / (L * C))) / ((-w * w) + (j * w * R / L) + (1.0 / (L * C)));
                                            break;
                                        }
                                    default:
                                        {
                                            return "Invalid";
                                            break;
                                        }
                                }

                                // Append frequency, H(f)
                                std::string str_tmp = std::to_string(f);
                                str_tmp.append(", ");
                                str_tmp.append(std::to_string(std::arg(tmp) * 180.0 / M_PI));
                                str_tmp.append("\n");

                                result.append(str_tmp);
                            }
                            break;
                        }
                    default:
                        {
                            // Invalid filter type
                            return "Invalid";
                            break;
                        }

                }

                return result;
            }

        private:
            // Filter type (int)
            // Types: lowpass(1), highpass(2), bandpass(3), bandstop(4)
            int filter_type_;

            // Filter order / sub-type (int)
            // Types: RC(1), RL(2), RLC(3)
            int filter_order_;

            // Filter values (vector)
            std::vector<value_type> values_;

        };


        // Function to get filter, given filter type, order, and values
        filter create_filter_vals(std::vector<double> values, int filter_type, int filter_order){
            return filter(values, filter_type, filter_order);
        }


    }
}

#endif