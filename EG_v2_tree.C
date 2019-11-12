//Explain this code.
#include <iostream>
#include <fstream>
#include <TF1.h> // 1d function class
#include <TRandom3.h>
#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include "MyClasses.C"

using namespace std;

void rootfuncgenerate(Int_t nEvents, Int_t nTracks, Double_t sigmaTracks, Double_t v2, Double_t sigmaV2); 


void rootfuncgenerate(Int_t nEvents, Int_t nTracks, Double_t sigmaTracks, Double_t v2, Double_t sigmaV2){
	cout << "Generating " << nEvents << " events" << endl << endl;
	// Create the outfile and data structure before the loop
	TFile* file = new TFile("phi_dist.root", "RECREATE");
	TTree* tree = new TTree("tree", "Output tree");
	MyEvent* event = new MyEvent();
	tree->Branch("event", &event);
	TClonesArray* trackArray = new TClonesArray("MyTrack", 1000);
	tree->Branch("track", "TClonesArray", &trackArray);
	Int_t nT = 0;
	gRandom = new TRandom3();
	
		
	// Define the function we want to generate
	TF1* PhiFunc = new TF1("PhiFunc", "1+2*[0]*cos(2*x)", 0, 2*TMath::Pi());
  
  // make a loop for the number of events
  for(Int_t n = 0; n < nEvents; n++) {
	event->nTracks = gRandom->Gaus(nTracks, sigmaTracks);
	event-> fV2 = gRandom->Gaus(v2, sigmaV2);

	PhiFunc->SetParameter(0, event->fV2);	
	
	for (Int_t nT; nT < (event->nTracks); nT++) {
		 MyTrack* track=new((*trackArray)[nT]) MyTrack();	 
		 track->fPhi = PhiFunc->GetRandom();
	}
		tree->Fill();
		trackArray->Clear();
  }
	file->Write();
	file->Close();
	tree->StartViewer();
}

