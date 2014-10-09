#ifndef Event_hpp
#define Event_hpp

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <iostream>
#include <math.h>
#include "interface/StandardIncludes.hpp"


#define MAX_ADC_CHANNELS 200
#define MAX_DIGI_SAMPLES 100000
#define MAX_TDC_CHANNELS 200
#define MAX_SCALER_WORDS 16
#define MAX_PATTERNS 16

using namespace std ;


// data format used as bridge between the high level structures and the root tree
struct treeStructData
{
  // unsigned int runNumber ; to be added soon
  unsigned int evtNumber ;
  unsigned int evtTimeDist ;
  unsigned int evtTimeStart ;
  unsigned int evtTime ;

  unsigned int triggerWord ;

//  unsigned int triggerBits ;

  unsigned int nAdcChannels ;
  //PG FIXME tranform these into vectors
  unsigned int adcBoard[MAX_ADC_CHANNELS] ;
  unsigned int adcChannel[MAX_ADC_CHANNELS] ;
  unsigned int adcData[MAX_ADC_CHANNELS] ;

  unsigned int nDigiSamples ;
  unsigned int digiGroup[MAX_DIGI_SAMPLES] ;
  unsigned int digiChannel[MAX_DIGI_SAMPLES] ;
  unsigned int digiSampleIndex[MAX_DIGI_SAMPLES] ;
  float digiSampleValue[MAX_DIGI_SAMPLES] ;

  unsigned int nTdcChannels ;
  unsigned int tdcBoard[MAX_TDC_CHANNELS] ;
  unsigned int tdcChannel[MAX_TDC_CHANNELS] ;
  unsigned int tdcData[MAX_TDC_CHANNELS] ;

  unsigned int nScalerWords ;
  WORD scalerWord[MAX_SCALER_WORDS] ;

  unsigned int nPatterns ;
  WORD pattern[MAX_PATTERNS] ;
} ;

struct adcData
{
  unsigned int board ;
  unsigned int channel ;
  unsigned int adcReadout ;
} ;

struct tdcData
{
  unsigned int board ;
  unsigned int channel ;
  unsigned int tdcReadout ;
} ;

struct digiData
{
  unsigned int group ;
  unsigned int channel ;
  unsigned int sampleIndex ;
  float sampleValue ;
} ;

struct Event
{
  Event (TFile * outFile, TTree * outTree) :
    outFile_ (outFile), 
    outTree_ (outTree) 
    { 
      createOutBranches (outTree_, thisTreeEvent_) ;   
    }

  ~Event () { }

  unsigned int evtNumber ;
  unsigned int triggerWord ;
  std::vector<bool> triggerBits ;
  std::vector<adcData> adcValues ; 
  std::vector<tdcData> tdcValues ; 
  std::vector<digiData> digiValues ; 
  std::vector<WORD> scalerWords ; 
  std::vector<WORD> patterns ; 
  unsigned int evtTimeDist ;
  unsigned int evtTimeStart ;
  uint64_t evtTime ;

  void clear () ;
  void Fill () ;

private :
  
  TFile * outFile_ ;
  TTree * outTree_ ;
  treeStructData thisTreeEvent_ ;

  // move events from the structures to the variables to be put into the root tree
  //PG FIXME does this slow down a lot?
  void fillTreeData (treeStructData & treeData) ;
  void createOutBranches (TTree* tree,treeStructData& treeData) ;

} ;

#endif
