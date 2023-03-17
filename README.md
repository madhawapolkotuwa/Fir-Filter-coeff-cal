##################################################################################################
# Fir-Filter-coeff-cal
# Fir Filter Coefficient calculation for Embeded programs
##################################################################################################
# Compiler gcc
##################################################################################################
# Filter types
#   1. Lowpass
#   2. Highpass
#   3. Bandpass
#   4. Bandstop
##################################################################################################
# Window types //Reference (https://en.wikipedia.org/wiki/Window_function)
##################################################################################################
#   1. Rectangular    
#   2. Triangular                 
#   3. Welch                      
#   4. Sine                       
#   5. Hann                       
#   6. Hamming                    
#   7. Blackman                   
#   8. Nuttall                    
#   9. BlackmanNuttall            
#   10. BlackmanHarris            
#   11. FlatTop                   
#   12. Kiser                      
###################################################################################################
# How to Run 
###################################################################################################
# Open FIR_filter_coeff.exe for windows users 
###################################################################################################
# Linux users open the terminal in files location and type (compiled C program with math.h library)
# ~/FIR_fiter_coeff_cal
# (if gcc compliler didi not install on your linux os
# first install the GCC Compiler 
# Perform the steps below to install the GCC Compiler linux:- $ sudo apt install build-essential
#                                                             $ sudo apt-get install manpages-dev
###################################################################################################                                                             
#                                                             
#
# Ex 1 :-> (Lowpass hann window Fs=100 and order = 128th) lowpass Fc = 2.2Hz
>>enter the filter type window Fs order= lowpass hann 100 128 
>>enter the lowpass frequency  fc = 2.2
![Lowpass](https://user-images.githubusercontent.com/32560614/225819842-d453a4bf-d19d-478c-80d2-1945d1fb45ef.png)

# Ex 2 :-> (Highpass blackman window Fs=100 and order = 64th) highpass Fc=10Hz
>>enter the filter type window Fs order= highpass blackman 100 64
>>enter the highpass frequency fc = 10
![Highpass](https://user-images.githubusercontent.com/32560614/225820154-a4728821-491a-4a94-a081-e8a46ffa3c89.png)

# Ex 3 :-> (Bandpass BlackmanNuttall window Fs=200 and order = 84th) passband [fc1  fc2] = 2.2Hz - 4.4Hz
>>enter the filter type window Fs order= bandpass blackmannuttall 200 84
>>enter the frequncy passband fc1 fc2 = 2.2 4.4
![Bandpass](https://user-images.githubusercontent.com/32560614/225820876-87d6a864-7a64-43ab-adae-135def1cbe0f.png)

# Ex 4 :-> (Bandstop kiser window Fs=100 and order = 64th) stopband [fc1  fc2] = 10Hz - 15Hz stop band attenuation 60dB
>>enter the filter type window Fs order= bandstop kiser 100 64
>>enter the frequncy stopband fc1 fc2 = 10 15
>>Enter stop-band attenuation [dB] = 60
![Bandstop](https://user-images.githubusercontent.com/32560614/225821146-15b02459-7f95-44bc-9850-a3f3a64cd439.png)

#####################################################################################################
# Outputs
#####################################################################################################
# .txt files & .png files for coefficients & impulse response
