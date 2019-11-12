
// include C++ STL headers 
#include <iostream>
#include <fstream>
#include "MyClasses.C"

using namespace std;

// ROOT library obejcts
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <TRandom.h> // random generators
#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TRandom3.h>

void rootfuncgenerate(Int_t nEvents,Int_t nTracks, Double_t sigmaTracks, Double_t v2, Double_t sigmaV2); // ROOT method (a bit dangerous since we don't know exactly what happens!)


//________________________________________________________________________
void rootfuncgenerate(Int_t nEvents,Int_t nTracks, Double_t sigmaTracks, Double_t v2, Double_t sigmaV2) 
{
  cout << "Generating " << nEvents << " events " << endl << endl;
//  Double_t phi[nTracks]; //array to store phi angles


  // Define the function we want to generate
  TF1* v2Func = new TF1("v2Func", "1+2*[0]*cos(2*x)", 0, 2*TMath::Pi());
//   v2Func->SetParameter(0,event->fV2);



TFile* file = new TFile("phi_dist.root", "RECREATE");
TTree* tree = new TTree("tree", "Output tree");

MyEvent* event = new MyEvent();

tree->Branch("event", &event);
TClonesArray* trackArray = new TClonesArray("MyTrack", 1000);
tree->Branch("track", "TClonesArray", &trackArray);
Int_t nT = 0;
gRandom = new TRandom3();


  for(Int_t ne = 0; ne < nEvents; ne++) {
    cout << "Event " << ne << endl;
//    file << "Event " << ne << endl;
    cout << "nTracks " << event->nTracks << endl;
//    file << "nTracks " << nTracks << endl;
	
	event->nTracks=gRandom->Gaus(nTracks, sigmaTracks);
	event->fV2=gRandom->Gaus(v2, sigmaV2);
	v2Func->SetParameter(0,event->fV2);
	
    for (Int_t nT = 0; nT < event->nTracks; nT++){
		
		MyTrack* track = new((*trackArray)[nT]) MyTrack();
		track->fPhi=v2Func->GetRandom();
        //cout << nT << " : "<< track->fPhi << endl;
//    file << i << " : "<< phi[i] << endl;
	} 
	tree->Fill();
	trackArray->Clear();
  }
file->Write();
file->Close();

  
/*  
  // create canvas for hPhi
  TCanvas* c1 = new TCanvas("c1", "phi canvas", 900, 600);
  hPhi->SetMinimum(0);
  
  
  // create 1d function that we will use to fit our generated data to ensure
  // that the generation works
  TF1* fitFunc = new TF1("fitFunc", "[0]+[1]*cos(2*x)", 0, 2*TMath::Pi());
  fitFunc->SetParameter(0,10);
  fitFunc->SetParameter(1, 5);
  fitFunc->SetLineColor(kRed);
  fitFunc->Draw();
  
  
  hPhi->Fit(fitFunc);
  // Set ROOT drawing styles
  gStyle->SetOptStat(1111);
  gStyle->SetOptFit(1111);  
  hPhi->Draw();
  
  // Save the canvas as a picture
  c1->SaveAs("v2_rootfunc.jpg");
*/ 
}
