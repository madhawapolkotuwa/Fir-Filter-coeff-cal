/*==============================================================================================================================================================*
 *	Project name	    : Fir Filter coefficients Calculation
 *	Title			    : Fir_Flter_coeff_cal.c
 *					    : For display board
 *	Program language    : C language
 *  Date of creation    : 2023/01/20 
 *  Author              : Madhawa Polkotuwa
 *	Update			    : 2023/03/17
*==============================================================================================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "pbPlots.h"
#include "supportLib.h"

#include "FIR_fiter_coeff_cal.h"


int main(void){

    int FILT_TYPE;
    int WIN_TYPE;

    int NUM_TOTAL_SAMPLES;
    int NUM_SHIFT_SAMPLES;

    ////////////////////////////////////////////////////////////////////////////
    /// 
    double CUTOFF_FREQUENCY_HZ;
    double CUTOFF_FREQUENCY2_HZ;
    double FS_HZ;

    float BETA;
    float _As=60; // default 60dB

    FILE *fileLp =NULL;
    FILE *fileHp =NULL;
    FILE *fileBp =NULL;

    while (1) {

        printf("enter the filter type window Fs order= ");
        char m_chrtype[10];
        char m_chrwindow[16];
        scanf("%s %s %lf %d",&m_chrtype,&m_chrwindow,&FS_HZ,&NUM_TOTAL_SAMPLES); // get filter

        double SAMPLE_TIME_S = 1.0/FS_HZ;

    
        if(NUM_TOTAL_SAMPLES == 0 || NUM_TOTAL_SAMPLES < 0 ){
            printf("enter correct filter order");
            return 0;
        }else{
            printf("filter order = %d\n",NUM_TOTAL_SAMPLES);
            NUM_SHIFT_SAMPLES = (int)(NUM_TOTAL_SAMPLES/2);
        }

        if (strcmp(m_chrtype,"lowpass") == 0 )
        {
            FILT_TYPE = LowPass;
            printf("enter the lowpass frequency  fc = ");
            scanf("%lf",&CUTOFF_FREQUENCY_HZ);  
            printf("lowpass cutoff frequency %lf\n",CUTOFF_FREQUENCY_HZ);
        }
        else if (strcmp(m_chrtype,"bandpass") == 0 )
        {
            FILT_TYPE = BandPass;
            printf("enter the frequncy passband fc1 fc2 = ");
            scanf("%lf %lf",&CUTOFF_FREQUENCY_HZ,&CUTOFF_FREQUENCY2_HZ);
            printf(" bandpass Frequency fc1 = %lf , fc2 = %lf\n",CUTOFF_FREQUENCY_HZ,CUTOFF_FREQUENCY2_HZ);
        }
        else if(strcmp(m_chrtype,"highpass") == 0)
        {
            FILT_TYPE = HighPass;
            printf("enter the highpass frequency fc = ");
            scanf("%lf",&CUTOFF_FREQUENCY_HZ);
            printf("highpass frequency %f\n",CUTOFF_FREQUENCY_HZ);
        }
        else if(strcmp(m_chrtype,"bandstop") == 0)
        {
            FILT_TYPE = BandStop;
            printf("enter the frequncy stopband fc1 fc2 = ");
            scanf("%lf %lf",&CUTOFF_FREQUENCY_HZ,&CUTOFF_FREQUENCY2_HZ);
            printf("bandstop stopband frequency fc1 = %lf , fc2 = %lf\n",CUTOFF_FREQUENCY_HZ,CUTOFF_FREQUENCY2_HZ);
        }
        else{
            printf("please enter the correct filter type\n");
            return 0;
        }

        if(strcmp(m_chrwindow,"rect") == 0)
        {
            printf("rect window\n");
            WIN_TYPE = Rectangular;
        }
        else if(strcmp(m_chrwindow,"triangular") == 0)
        {
            printf("Triangular window\n");
            WIN_TYPE = Triangular;
        }
        else if(strcmp(m_chrwindow,"welch") == 0)
        {
            printf("Welch window\n");
            WIN_TYPE = Welch;
        }
        else if(strcmp(m_chrwindow,"sine") == 0)
        {
            printf("Sine window\n");
            WIN_TYPE = Sine;
        }
        else if(strcmp(m_chrwindow,"hann") == 0)
        {
            printf("Hann window\n");
            WIN_TYPE = Hann;
        }
        else if(strcmp(m_chrwindow,"hamming") == 0)
        {
            printf("Hamming window\n");
            WIN_TYPE = Hamming;
        }
        else if(strcmp(m_chrwindow,"flatTop") == 0)
        {
            printf("FlatTop window\n");
            WIN_TYPE = FlatTop;
        }
        else if(strcmp(m_chrwindow,"blackman") == 0)
        {
            printf("Blackman window\n");
            WIN_TYPE = Blackman;
        }
        else if(strcmp(m_chrwindow,"nuttall") == 0)
        {
            printf("Nuttall window\n");
            WIN_TYPE = Nuttall;
        }
        else if(strcmp(m_chrwindow,"blackmannuttall") == 0)
        {
            printf("BlackmanNuttall window\n");
            WIN_TYPE = BlackmanNuttall;
        }
        else if(strcmp(m_chrwindow,"blackmanharris") == 0)
        {
            printf("BlackmanHarris window\n");
            WIN_TYPE = BlackmanHarris;
        }
        else if(strcmp(m_chrwindow,"kiser") == 0){
        
            printf("Enter stop-band attenuation [dB] = ");
            scanf("%f",&_As);
            BETA = beta_kaiser(NUM_TOTAL_SAMPLES, _As);
            WIN_TYPE = Kiser;
        }
        else{
            printf("please enter correct format \n");
            return 0;
        }


    double impulseResponse[NUM_TOTAL_SAMPLES];

            for (int n = 0; n < NUM_TOTAL_SAMPLES; n++)
            {
                if (n != NUM_SHIFT_SAMPLES)
                {
                    switch (FILT_TYPE)
                    {
                        case LowPass:
                            impulseResponse[n] = sin(2.0 * M_PI * CUTOFF_FREQUENCY_HZ * SAMPLE_TIME_S * (n - NUM_SHIFT_SAMPLES)) / (M_PI * SAMPLE_TIME_S * (n - NUM_SHIFT_SAMPLES));
                            break;
                        case HighPass:                            
                            impulseResponse[n] = (sin(M_PI * (n - NUM_SHIFT_SAMPLES)) - sin(2.0 * M_PI * CUTOFF_FREQUENCY_HZ * SAMPLE_TIME_S * (n - NUM_SHIFT_SAMPLES))) / (M_PI * SAMPLE_TIME_S * (n - NUM_SHIFT_SAMPLES));
                            break;
                        case BandPass:
                            impulseResponse[n] = (sin(2.0 * M_PI * CUTOFF_FREQUENCY2_HZ * SAMPLE_TIME_S * (n - NUM_SHIFT_SAMPLES)) - sin(2.0 * M_PI * CUTOFF_FREQUENCY_HZ * SAMPLE_TIME_S * (n - NUM_SHIFT_SAMPLES))) / (M_PI * SAMPLE_TIME_S * (n - NUM_SHIFT_SAMPLES));
                            break;
                        case BandStop:
                            impulseResponse[n] = (sin(2.0 * M_PI * CUTOFF_FREQUENCY_HZ * SAMPLE_TIME_S * (n - NUM_SHIFT_SAMPLES)) - sin(2.0 * M_PI * CUTOFF_FREQUENCY2_HZ * SAMPLE_TIME_S * (n - NUM_SHIFT_SAMPLES)) + sin(M_PI * (n - NUM_SHIFT_SAMPLES))) / (M_PI * SAMPLE_TIME_S * (n - NUM_SHIFT_SAMPLES));
                            break;
                    }
                } else /* Avoid divide-by-zero, limit is 2*fc */
                {
                    switch (FILT_TYPE)
                    {
                        case LowPass:
                            impulseResponse[n] = 2.0 * CUTOFF_FREQUENCY_HZ;
                            break;
                        case HighPass:
                            impulseResponse[n] = 1.0 / SAMPLE_TIME_S - 2.0 * CUTOFF_FREQUENCY_HZ;
                            break;
                        case BandPass:
                            impulseResponse[n] = 2.0 * CUTOFF_FREQUENCY2_HZ - 2.0 * CUTOFF_FREQUENCY_HZ;
                            break;
                        case BandStop:
                            impulseResponse[n] = 2.0 * CUTOFF_FREQUENCY_HZ - 2.0 * CUTOFF_FREQUENCY2_HZ + 1.0 / SAMPLE_TIME_S;
                            break;
                    }
                }
            }

            double window[NUM_TOTAL_SAMPLES];
            for (int n = 0; n < NUM_TOTAL_SAMPLES; n++)
            {
                switch (WIN_TYPE)
                {
                    case Rectangular:
                        window[n] = 1.0;
                        break;

                    case Triangular:
                        window[n] = 1.0 - abs((n - 0.5 * NUM_TOTAL_SAMPLES) / (0.5 * NUM_TOTAL_SAMPLES));
                        break;

                    case Welch:
                        window[n] = 1.0 - pow((n - 0.5 * NUM_TOTAL_SAMPLES) / (0.5 * NUM_TOTAL_SAMPLES), 2.0);
                        break;

                    case Sine:
                        window[n] = sin(M_PI * n / ((double) NUM_TOTAL_SAMPLES));
                        break;

                    case Hann:
                        window[n] = 0.5 * (1 - cos(2.0 * M_PI * n / ((double) NUM_TOTAL_SAMPLES)));
                        break;

                    case Hamming:
                        window[n] = (25.0 / 46.0) - (21.0 / 46.0) * cos(2.0 * M_PI * n / ((double) NUM_TOTAL_SAMPLES));
                        break;

                    case Blackman:
                        window[n] = 0.42 - 0.5 * cos(2.0 * M_PI * n / ((double) NUM_TOTAL_SAMPLES)) + 0.08 * cos(4.0 * M_PI * n / ((double) NUM_TOTAL_SAMPLES));
                        break;

                    case Nuttall:
                        window[n] = 0.355768 - 0.487396 * cos(2.0 * M_PI * n / ((double) NUM_TOTAL_SAMPLES)) + 0.144232 * cos(4.0 * M_PI * n / ((double) NUM_TOTAL_SAMPLES)) - 0.012604 * cos(6.0 * M_PI * n / ((double) NUM_TOTAL_SAMPLES));
                        break;

                    case BlackmanNuttall:
                        window[n] = 0.3635819 - 0.4891775 * cos(2.0 * M_PI * n / ((double) NUM_TOTAL_SAMPLES)) + 0.1365995 * cos(4.0 * M_PI * n / ((double) NUM_TOTAL_SAMPLES)) - 0.0106411 * cos(6.0 * M_PI * n / ((double) NUM_TOTAL_SAMPLES));
                        break;

                    case BlackmanHarris:
                        window[n] = 0.35875 - 0.48829 * cos(2.0 * M_PI * n / ((double) NUM_TOTAL_SAMPLES)) + 0.14128 * cos(4.0 * M_PI * n / ((double) NUM_TOTAL_SAMPLES)) - 0.01168 * cos(6.0 * M_PI * n / ((double) NUM_TOTAL_SAMPLES));
                        break;

                    case FlatTop:
                        window[n] = 0.21557895 - 0.41663158 * cos(2.0 * M_PI * n / ((double) NUM_TOTAL_SAMPLES)) + 0.277263158 * cos(4.0 * M_PI * n / ((double) NUM_TOTAL_SAMPLES)) - 0.083578947 * cos(6.0 * M_PI * n / ((double) NUM_TOTAL_SAMPLES)) + 0.006947368 * cos(8.0 * M_PI * n / ((double) NUM_TOTAL_SAMPLES));
                        break;
                    case Kiser:
                        // kaiser window
                        window[n] = kaiser(n,NUM_TOTAL_SAMPLES,BETA);
                        break;
                    default:
                        window[n] = 1.0;
                        break;
                }
            }

            double windowedImpulseResponse[NUM_TOTAL_SAMPLES];        
            for(int n = 0; n < NUM_TOTAL_SAMPLES; n++)
            {
                impulseResponse[n] *= SAMPLE_TIME_S;
                windowedImpulseResponse[n] = impulseResponse[n] * window[n];
                printf("%lf\n",windowedImpulseResponse[n]);  // print the coefficents
            }   

            double xs [NUM_TOTAL_SAMPLES];
            double ys [NUM_TOTAL_SAMPLES];
            _Bool success;
            RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
	        StringReference *errorMessage = CreateStringReference(L"", 0);
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // Save the coefficents
            switch (FILT_TYPE)
                    {
                        case LowPass:
                            fileLp = fopen("LowPass.txt","w");
                            fprintf(fileLp,"LowPass Coef\n");
                            fprintf(fileLp,"Filter order            = %d -th\n",NUM_TOTAL_SAMPLES);
                            fprintf(fileLp,"Sampling Freq fs        = %.1f Hz\n",FS_HZ);
                            fprintf(fileLp,"Low pass Cutoff freq fc = %0.2f Hz\n",CUTOFF_FREQUENCY_HZ);
                            
                            fprintf(fileLp,"\n\n [" );
                            
                            for(int n = 0; n < NUM_TOTAL_SAMPLES; n++)
                                {
                                    xs[n] = n;
                                    impulseResponse[n] *= SAMPLE_TIME_S;
                                    windowedImpulseResponse[n] = impulseResponse[n] * window[n];
                                    ys[n] = windowedImpulseResponse[n];
                                    fprintf(fileLp,"%lf,\n",windowedImpulseResponse[n]);  // print the coefficents
                                }                       
                            fprintf(fileLp,"]" );
                            fclose(fileLp);

	                        //RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
	                        //StringReference *errorMessage = CreateStringReference(L"", 0);
	                        success = DrawScatterPlot(canvasReference, 600, 400, xs, NUM_TOTAL_SAMPLES, ys, NUM_TOTAL_SAMPLES, errorMessage);

	                        if(success){
		                        size_t length;
		                        double *pngdata = ConvertToPNG(&length, canvasReference->image);
		                        WriteToFile(pngdata, length, "Lowpass.png"); // impulse response of the filter
		                        DeleteImage(canvasReference->image);
	                        }else{
		                        fprintf(stderr, "Error: ");
		                        for(int i = 0; i < errorMessage->stringLength; i++){
			                        fprintf(stderr, "%c", errorMessage->string[i]);
		                        }
		                        fprintf(stderr, "\n");
	                        }

	                        FreeAllocations();

                            printf("\n\n***************lowpass filter coefficient calculation is done see the Lowpass.txt and Lowpass.png*****************\n\n\n");
                            break;

                        case HighPass:
                            fileLp = fopen("HighPass.txt","w");
                            fprintf(fileLp,"HighPass Coefficients\n");
                            fprintf(fileLp,"Filter order            = %d -th\n",NUM_TOTAL_SAMPLES);
                            fprintf(fileLp,"Sampling Freq fs        = %.1f Hz\n",FS_HZ);
                            fprintf(fileLp,"Highpass freq fc= %0.2f Hz\n",CUTOFF_FREQUENCY_HZ);
                            
                            fprintf(fileLp,"\n\n [" );
                            
                            for(int n = 0; n < NUM_TOTAL_SAMPLES; n++)
                                {
                                    xs[n] = n;
                                    impulseResponse[n] *= SAMPLE_TIME_S;
                                    windowedImpulseResponse[n] = impulseResponse[n] * window[n];
                                    ys[n] = windowedImpulseResponse[n];
                                    fprintf(fileLp,"%lf,\n",windowedImpulseResponse[n]);  // print the coefficents
                                }                       
                            fprintf(fileLp,"]" );
                            fclose(fileLp);

	                        //RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
	                        //StringReference *errorMessage = CreateStringReference(L"", 0);
	                        success = DrawScatterPlot(canvasReference, 600, 400, xs, NUM_TOTAL_SAMPLES, ys, NUM_TOTAL_SAMPLES, errorMessage);

	                        if(success){
		                        size_t length;
		                        double *pngdata = ConvertToPNG(&length, canvasReference->image);
		                        WriteToFile(pngdata, length, "Highpass.png"); // impulse response of the filter
		                        DeleteImage(canvasReference->image);
	                        }else{
		                        fprintf(stderr, "Error: ");
		                        for(int i = 0; i < errorMessage->stringLength; i++){
			                        fprintf(stderr, "%c", errorMessage->string[i]);
		                        }
		                        fprintf(stderr, "\n");
	                        }

	                        FreeAllocations();

                            printf("\n\n***************Highpass filter coefficient calculation is done see the Highpass.txt and Highpass.png*****************\n\n\n");
                            break;

                        case BandPass:
                            fileLp = fopen("BandPass.txt","w");
                            fprintf(fileLp,"Bandpass Coefficients\n");
                            fprintf(fileLp,"Filter order            = %d -th\n",NUM_TOTAL_SAMPLES);
                            fprintf(fileLp,"Sampling Freq fs        = %.1f Hz\n",FS_HZ);
                            fprintf(fileLp,"Bandpass freq [fc1 fc2] = [%0.2f %0.2f]Hz\n",CUTOFF_FREQUENCY_HZ,CUTOFF_FREQUENCY2_HZ);

                            fprintf(fileLp,"\n\n [" );

                            for(int n = 0; n < NUM_TOTAL_SAMPLES; n++)
                                {
                                    xs[n] = n;
                                    impulseResponse[n] *= SAMPLE_TIME_S;
                                    windowedImpulseResponse[n] = impulseResponse[n] * window[n];
                                    ys[n] = windowedImpulseResponse[n];
                                    fprintf(fileLp,"%lf,\n",windowedImpulseResponse[n]);  // print the coefficents
                                }                       
                            fprintf(fileLp,"]" );
                            fclose(fileLp);

	                        //RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
	                        //StringReference *errorMessage = CreateStringReference(L"", 0);
	                        success = DrawScatterPlot(canvasReference, 600, 400, xs, NUM_TOTAL_SAMPLES, ys, NUM_TOTAL_SAMPLES, errorMessage);

	                        if(success){
		                        size_t length;
		                        double *pngdata = ConvertToPNG(&length, canvasReference->image);
		                        WriteToFile(pngdata, length, "Bandpass.png"); // impulse response of the filter
		                        DeleteImage(canvasReference->image);
	                        }else{
		                        fprintf(stderr, "Error: ");
		                        for(int i = 0; i < errorMessage->stringLength; i++){
			                        fprintf(stderr, "%c", errorMessage->string[i]);
		                        }
		                        fprintf(stderr, "\n");
	                        }

	                        FreeAllocations();

                            printf("\n\n***************Bandpass filter coefficient calculation is done see the Bandpass.txt and Bandpass.png*****************\n\n\n");

                            break;

                        case BandStop:
                            fileLp = fopen("Bandstop.txt","w");
                            fprintf(fileLp,"Bandstop Coefficients\n");
                            fprintf(fileLp,"Filter order            = %d -th\n",NUM_TOTAL_SAMPLES);
                            fprintf(fileLp,"Sampling Freq fs        = %.1f Hz\n",FS_HZ);
                            fprintf(fileLp,"Stop band freq [fc1 fc2] = [%0.2f %0.2f]Hz\n",CUTOFF_FREQUENCY_HZ,CUTOFF_FREQUENCY2_HZ);

                            fprintf(fileLp,"\n\n [" );

                            for(int n = 0; n < NUM_TOTAL_SAMPLES; n++)
                                {
                                    xs[n] = n;
                                    impulseResponse[n] *= SAMPLE_TIME_S;
                                    windowedImpulseResponse[n] = impulseResponse[n] * window[n];
                                    ys[n] = windowedImpulseResponse[n];
                                    fprintf(fileLp,"%lf,\n",windowedImpulseResponse[n]);  // print the coefficents
                                }                       
                            fprintf(fileLp,"]" );
                            fclose(fileLp);

	                        
	                        success = DrawScatterPlot(canvasReference, 600, 400, xs, NUM_TOTAL_SAMPLES, ys, NUM_TOTAL_SAMPLES, errorMessage);

	                        if(success){
		                        size_t length;
		                        double *pngdata = ConvertToPNG(&length, canvasReference->image);
		                        WriteToFile(pngdata, length, "Bandstop.png"); // impulse response of the filter
		                        DeleteImage(canvasReference->image);
	                        }else{
		                        fprintf(stderr, "Error: ");
		                        for(int i = 0; i < errorMessage->stringLength; i++){
			                        fprintf(stderr, "%c", errorMessage->string[i]);
		                        }
		                        fprintf(stderr, "\n");
	                        }

	                        FreeAllocations();

                            printf("\n\n***************Bandstop filter coefficient calculation is done see the Bandstop.txt and Bandstop.png*****************\n\n\n");


                            break;

                    }


        }

        return 0;

}
