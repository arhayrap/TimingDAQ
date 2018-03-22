#ifndef DatAnalyzer_HH
#define DatAnalyzer_HH

// STD INCLUDES
#include <iostream>
#include <string>

// ROOT INCLUDES
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TGraphErrors.h"
#include "TCanvas.h"

// LOCAL INCLUDES
#include "Config.hh"

// This is the base class for .dat --> .root converters.

class DatAnalyzer {
    public:
        DatAnalyzer(int numChannels=36, int numSamples=1024);
        ~DatAnalyzer();
        int getNumChannels() { return NUM_CHANNELS; }
        int getNumSamples() { return NUM_SAMPLES; }

        TString ParseCommandLine( int argc, char* argv[], TString opt );
        void GetCommandLineArgs(int argc, char **argv);

        void InitTree();

        virtual int GetChannelsMeasurement() {
          std::cerr << "Please use a child class of DatAnalyzer" << std::endl;
          return 0;
        }

        unsigned int GetTimeIndex(unsigned int n_ch) { return n_ch; } // Return the index of the time associated with the channel n_ch
        void Analyze();

        void RunEventsLoop();

    protected:

        const int NUM_CHANNELS;
        const int NUM_SAMPLES;

        // Set by command line arguments or default
        Config* config = nullptr;

        TString input_file_path;
        TString output_file_path;
        unsigned int N_evts = 0;

        bool save_raw = false;
        bool save_meas = false;
        bool draw_debug_pulses = false;

        // Reader variables
        FILE* bin_file = nullptr;

        // Analysis variables
        float time[4][1024];
        float channel[36][1024];

        // Output tree vars
        unsigned int i_evt = 0;

        // Output root file
        TFile *file;
        TTree *tree;

        std::map<TString, float*> var;
        const TString var_names[19] = {
          "xmin",
          "xminRestricted",
          "amp",
          "ampRestricted",
          "base",
          "integral",
          "intfull",
          "gauspeak",
          "sigmoidTime",
          "fullFitTime",
          "linearTime0",
          "linearTime15",
          "linearTime30",
          "linearTime45",
          "linearTime60",
          "fallingTime",
          "risetime",
          "constantThresholdTime",
          "isRinging",
        };
        void ResetVar(unsigned int n_ch);

        // TODO: add all tree variables
};

#endif
