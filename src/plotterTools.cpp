#include <plotterTools.hpp>


plotterTools::plotterTools(char* filename, char*outfname, char* outdname){

  setPlotsFormat () ;
  inputFile_ = TFile::Open(filename);

  if( inputFile_==0 ) {
    std::cout << "ERROR! Din't find file " << filename << std::endl;
    std::cout << "Exiting." << std::endl;
    exit(11);
  }

  inputTree_ = (TChain*) inputFile_->Get("H4tree");
  outputFile_ = TFile::Open(outfname,"RECREATE");
  outputDir_=outdname;

};


void plotterTools::set_plot_blue ()
{
    Double_t Red[3]    = { 0.00, 0.00, 0.00};
    Double_t Green[3]  = { 0.00, 0.00, 0.00};
    Double_t Blue[3]   = { 0.00, 0.00, 1.00};
    Double_t Length[3] = { 0.00, 0.00, 1.00};
    Int_t nb=50;
    TColor::CreateGradientColorTable(3,Length,Red,Green,Blue,nb);
    gStyle->SetNumberContours(nb);
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


void  plotterTools::setPlotsFormat ()
{
    // general root settings
	gROOT->SetStyle ("Plain") ;
    gStyle->SetOptStat ("emruo") ;
	gStyle->SetOptFit (1111) ;
	gStyle->SetCanvasDefH (300) ; //Height of canvas
	gStyle->SetCanvasDefW (300) ; //Width of canvas
	
	// fonts of titles and labels
	gStyle->SetTitleBorderSize (0) ;
	gStyle->SetTitleX (0.08) ;
	gStyle->SetTitleY (0.97) ;
	gStyle->SetPalette (1,0) ;
	gStyle->SetLabelFont (42,"xyz") ;
	gStyle->SetTextFont (42) ;
	gStyle->SetStatFont (42) ;
	gStyle->SetTitleFont (42,"xyz") ;
	//gStyle->SetPadGridX (1) ;
	//gStyle->SetPadGridY (1) ;

	// positioning
	gStyle->SetTitleXOffset (1.25) ;
	gStyle->SetTitleYOffset (1.4) ;

	gStyle->SetTitleX (0.5) ; // put title box in the middle
	gStyle->SetTitleFont (42) ;
	gStyle->SetTitleAlign (23) ; // center title text in title box
	gStyle->SetTitleSize (0.04, "xyz") ;
	gStyle->SetLabelSize (0.05, "xyz") ;

	gStyle->SetPadRightMargin (0.05)  ;
	gStyle->SetPadLeftMargin (0.15) ;
	gStyle->SetPadBottomMargin (0.15) ;
	gStyle->SetPadTopMargin (0.1) ;

	// ticks and divisions on the axes
	gStyle->SetPadTickX (1) ;
	gStyle->SetPadTickY (1) ;
	gStyle->SetNdivisions(7, "xyz");

	// frame drawing options
	gStyle->SetLineWidth (2) ;
	gStyle->SetFillStyle (0) ;
	gStyle->SetStatStyle (0) ;
	
	// histogram default drawing options
	gStyle->SetHistFillColor (kOrange) ;
	gStyle->SetHistLineColor (kBlack) ;
	gStyle->SetHistLineStyle (1) ;
	gStyle->SetHistLineWidth (2) ;
	
	// stats box position
	gStyle->SetStatX (0.95) ;
	gStyle->SetStatY (0.9) ;
	gStyle->SetStatW (0.2) ;
	gStyle->SetStatH (0.15) ;

	set_plot_blue () ;
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


void  plotterTools::plotMe (TH1F * histo)
{
  TString hname = histo->GetName () ;
  TString canvasName = outputDir_+ "/"+hname + "_small.png" ;
  TCanvas * c1 = new TCanvas ("c1", "c1", 300, 300) ;
  histo->Draw () ;
  c1->Print (canvasName, "png") ;
  canvasName =outputDir_+ "/"+ hname + "_large.png" ;
  delete c1 ;
  c1 = new TCanvas ("c1", "c1", 800, 800) ;
  histo->Draw () ;
  c1->Print (canvasName, "png") ;
  delete c1 ;
  return ;
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


void  plotterTools::plotMe (TH2F * histo)
{
  TString hname = histo->GetName () ;
  TString canvasName =  outputDir_+ "/"+hname + "_small.png" ;
  TCanvas * c1 = new TCanvas ("c1", "c1", 300, 300) ;
  histo->Draw ("colz") ;
  c1->Print (canvasName, "png") ;
  canvasName = outputDir_+ "/"+hname + "_large.png" ;
  delete c1 ;
  c1 = new TCanvas ("c1", "c1", 800, 800) ;
  histo->Draw ("colz") ;
  c1->Print (canvasName, "png") ;
  delete c1 ;
  return ;
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


void  plotterTools::plotMe (TGraph * graph, const TString & name)
{
  TString canvasName =  outputDir_+ "/" +name + "_small.png" ;
  TCanvas * c1 = new TCanvas ("c1", "c1", 300, 300) ;
  graph->SetMarkerStyle (8) ;
  graph->SetMarkerSize (1.5) ;
  graph->SetMarkerColor (kBlue) ;  
  graph->Draw ("ALP") ;
  std::cout<<"!!saving"<<std::endl;
  c1->Print (canvasName, "png") ;
  canvasName = outputDir_+ "/"+name + "_large.png" ;
  delete c1 ;
  c1 = new TCanvas ("c1", "c1", 800, 800) ;
  graph->Draw ("ALP") ;
  std::cout<<"!!saving"<<std::endl;
  c1->Print (canvasName, "png") ;
  delete c1 ;
  return ;
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


void  plotterTools::setAxisTitles (TH1 * histo, const TString & xTitle, const TString & yTitle) 
{
  histo->GetXaxis ()->SetTitle (xTitle) ;
  histo->GetYaxis ()->SetTitle (yTitle) ;
  return ;
}

// ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

void  plotterTools::setAxisTitles (TH2 * histo, const TString & xTitle, const TString & yTitle) 
{
  histo->GetXaxis ()->SetTitle (xTitle) ;
  histo->GetYaxis ()->SetTitle (yTitle) ;
  return ;
}

// ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

void  plotterTools::setAxisTitles (TGraph * histo, const TString & xTitle, const TString & yTitle) 
{
  histo->GetXaxis ()->SetTitle (xTitle) ;
  histo->GetYaxis ()->SetTitle (yTitle) ;
  return ;
}

// ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


void  plotterTools::readInputTree ()
{
  //Instantiate the tree branches
  inputTree_->Print();
  inputTree_->SetBranchAddress("evtNumber",&treeStruct_.evtNumber);
  inputTree_->SetBranchAddress("evtTimeDist",&treeStruct_.evtTimeDist);
  inputTree_->SetBranchAddress("evtTimeStart",&treeStruct_.evtTimeStart);
  inputTree_->SetBranchAddress("evtTime",&treeStruct_.evtTime);


  inputTree_->SetBranchAddress("triggerWord",&treeStruct_.triggerWord);

  inputTree_->SetBranchAddress("nAdcChannels",&treeStruct_.nAdcChannels);
  inputTree_->SetBranchAddress("adcBoard",treeStruct_.adcBoard);
  inputTree_->SetBranchAddress("adcChannel",treeStruct_.adcChannel);
  inputTree_->SetBranchAddress("adcData",treeStruct_.adcData);

  inputTree_->SetBranchAddress("nTdcChannels",&treeStruct_.nTdcChannels);
  inputTree_->SetBranchAddress("tdcBoard",treeStruct_.tdcBoard);
  inputTree_->SetBranchAddress("tdcChannel",treeStruct_.tdcChannel);
  inputTree_->SetBranchAddress("tdcData",treeStruct_.tdcData);

  inputTree_->SetBranchAddress("nDigiSamples",&treeStruct_.nDigiSamples);
  inputTree_->SetBranchAddress("digiGroup",treeStruct_.digiGroup);
  inputTree_->SetBranchAddress("digiChannel",treeStruct_.digiChannel);
  inputTree_->SetBranchAddress("digiSampleIndex",treeStruct_.digiSampleIndex);
  inputTree_->SetBranchAddress("digiSampleValue",treeStruct_.digiSampleValue);

  inputTree_->SetBranchAddress("nScalerWords",&treeStruct_.nScalerWords);
  inputTree_->SetBranchAddress("scalerWord",treeStruct_.scalerWord);

  return ;
} 


void  plotterTools::Loop(){

  int nentries = getTreeEntries();

  int nBinsHistory=nentries/getStepHistoryPlots();

  //loop and fill histos
 for( unsigned iEntry=0; iEntry<nentries; ++iEntry ) {
   inputTree_->GetEntry(iEntry);
   if(iEntry%historyStep_==0){
     if( (int)iEntry/historyStep_-1 < nBinsHistory){//all history plots should go here
       ((TGraph*) outObjects_[plotNames_["triggerEff"]])->SetPoint((int)iEntry/historyStep_-1, iEntry,(float)treeStruct_.scalerWord[2]/treeStruct_.scalerWord[1]);
     }
   }
 }
 
 
}


void plotterTools::bookPlotsScaler(int nBinsHistory){
  //in this function you define all the objects for the scaler
  addPlot("triggerEff",nBinsHistory, "history", group_,module_);
  std::cout<<"booked histo"<<outObjects_.size()<<std::endl;  
}


void plotterTools::addPlot(TString name,int nPoints,TString type, TString group, TString module){

  if(type=="history"){
    TString longName=group+TString("_")+module+TString("_")+type+TString("_")+name;
    outObjects_[longName]=((TObject*)  bookGraph(name,nPoints,type, group_,module_));
    plotNames_[name]=longName;
 }

}

TGraph* plotterTools::bookGraph(TString name,int nPoints,TString type, TString group, TString module){

  std::cout<<"daje"<<endl;
  std::cout<<outObjects_.size()<<"......."<<endl;
  TGraph* graph=new TGraph (nPoints);
  setAxisTitles(graph,"Event",name);
  graph->SetTitle(name);
  graph->SetName(group+TString("_")+module+TString("_")+type+TString("_")+TString(graph->GetTitle()));
  std::cout<<outObjects_.size()<<"......."<<endl;

  return graph;

}

void plotterTools::setModule(TString module){
  module_=module;
}

void plotterTools::setGroup(TString group){
  group_=group;
}

void plotterTools::setStepHistoryPlots(int n){
  historyStep_=n;
}

int plotterTools::getTreeEntries(){
  return  inputTree_->GetEntries();
}

int plotterTools::getStepHistoryPlots(){
  return  historyStep_;
}


void plotterTools::saveHistos(){
  std::cout << "==================== Saving histograms =======================" << std::endl;
  std::cout << "outputFile " << outputFile_->GetName() << " opened" << std::endl;
  outputFile_->cd();
  for (std::map<TString,TObject*>::const_iterator out=outObjects_.begin();out!=outObjects_.end();++out)
    out->second->Write(out->first);
  outputFile_->Close();
  std::cout << "outputFile " << outputFile_->GetName() << " closed" << std::endl;
  std::cout << "==================== DQM analysis is done =======================" << std::endl;
}


void plotterTools::plotHistos(){
  std::cout << "==================== Plotting histograms =======================" << std::endl;
  for (std::map<TString,TObject*>::const_iterator out=outObjects_.begin();out!=outObjects_.end();++out)
    plotMe((TGraph*)out->second, out->first);
  std::cout << "==================== Canvas saved in \" "<< outputDir_<<"\" =======================" << std::endl;
}


void plotterTools::printHistos(){
  std::cout << "==================== Booked histograms =======================" << std::endl;
  for (std::map<TString,TObject*>::const_iterator out=outObjects_.begin();out!=outObjects_.end();++out)
    std::cout << out->second->GetName() << std::endl;
  std::cout << "==================== Loop over events =======================" << std::endl;
}
