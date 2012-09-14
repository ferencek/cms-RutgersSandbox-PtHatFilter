// -*- C++ -*-
//
// Package:    PtHatFilter
// Class:      PtHatFilter
// 
/**\class PtHatFilter PtHatFilter.cc RutgersSandbox/PtHatFilter/src/PtHatFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Dinko Ferencek
//         Created:  Fri Sep 14 15:41:16 CDT 2012
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

//
// class declaration
//

class PtHatFilter : public edm::EDFilter {
   public:
      explicit PtHatFilter(const edm::ParameterSet&);
      ~PtHatFilter();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual bool beginRun(edm::Run&, edm::EventSetup const&);
      virtual bool endRun(edm::Run&, edm::EventSetup const&);
      virtual bool beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual bool endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

      // ----------member data ---------------------------
      const std::string      moduleLabel_;
      const edm::InputTag    genEvtInfoTag_;
      const double           ptHatMin_;
      const double           ptHatMax_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
PtHatFilter::PtHatFilter(const edm::ParameterSet& iConfig) :
  moduleLabel_(iConfig.getParameter<std::string>("@module_label")),
  genEvtInfoTag_(iConfig.getParameter<edm::InputTag>("GenEventInfoTag")),
  ptHatMin_(iConfig.getParameter<double>("PtHatMin")),
  ptHatMax_(iConfig.getParameter<double>("PtHatMax"))
{
   //now do what ever initialization is needed

}


PtHatFilter::~PtHatFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
PtHatFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   bool ret = false;

   if( !iEvent.isRealData() )
   {
     // GenEventInfo
     edm::Handle<GenEventInfoProduct> genEvtInfoProduct;
     iEvent.getByLabel(genEvtInfoTag_, genEvtInfoProduct);

     if( genEvtInfoProduct.isValid() )
     {
       edm::LogInfo(moduleLabel_.c_str()) << "Successfully obtained " << genEvtInfoTag_;

       double ptHat = ( genEvtInfoProduct->hasBinningValues() ? genEvtInfoProduct->binningValues()[0] : -999. );

       if(ptHat>0 && (ptHat>=ptHatMin_ || ptHatMin_<0) && (ptHat<=ptHatMax_ || ptHatMax_<0))
         ret = true;
     }
     else
     {
       edm::LogError(moduleLabel_.c_str()) << "Error! Can't get the product " << genEvtInfoTag_;
     }
   }

   return ret;
}

// ------------ method called once each job just before starting event loop  ------------
void 
PtHatFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
PtHatFilter::endJob() {
}

// ------------ method called when starting to processes a run  ------------
bool 
PtHatFilter::beginRun(edm::Run&, edm::EventSetup const&)
{ 
  return true;
}

// ------------ method called when ending the processing of a run  ------------
bool 
PtHatFilter::endRun(edm::Run&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when starting to processes a luminosity block  ------------
bool 
PtHatFilter::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when ending the processing of a luminosity block  ------------
bool 
PtHatFilter::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
PtHatFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(PtHatFilter);
