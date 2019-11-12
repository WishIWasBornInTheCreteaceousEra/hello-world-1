#include <TObject.h>
#include <Rtypes.h>

class MyEvent : public TObject
{
public:
	Int_t nTracks;
	Double_t fV2;
	MyEvent();
	ClassDef(MyEvent, 1); 
};

ClassImp(MyEvent)
MyEvent::MyEvent(): TObject(), nTracks(-1), fV2(-1){
//default constructor
}

class MyTrack : public TObject {
public:
	Double_t fPhi;
	MyTrack();
	ClassDef(MyTrack, 1); 
};

ClassImp(MyTrack)
MyTrack::MyTrack(): TObject(), fPhi(-1){
	//default constructor
}

