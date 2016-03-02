#ifndef TotemRPDQMSource_H
#define TotemRPDQMSource_H

// Framework
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

// event
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

// DQM
#include "DQMServices/Core/interface/DQMEDAnalyzer.h"
#include "DQMServices/Core/interface/DQMStore.h"
#include "DQMServices/Core/interface/MonitorElement.h"

// Candidate handling
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"

// Electron
#include "DataFormats/EgammaCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"

// PFMET
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/PFMETCollection.h"

// Vertex utilities
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

// CaloJets
#include "DataFormats/JetReco/interface/CaloJet.h"

// Conversions
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"

// Trigger
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "FWCore/Common/interface/TriggerNames.h"

#include "DataFormats/Common/interface/DetSetVector.h"

#include "DataFormats/TotemRPDataTypes/interface/RPStripDigi.h"
#include "DataFormats/TotemRPDataTypes/interface/RPDigCluster.h"
#include "DataFormats/TotemRPDataTypes/interface/RPRecoHit.h"
#include "RecoTotemRP/RPRecoDataFormats/interface/RPRecognizedPatternsCollection.h"
#include "RecoTotemRP/RPRecoDataFormats/interface/RPFittedTrack.h"
#include "RecoTotemRP/RPRecoDataFormats/interface/RPFittedTrackCollection.h"
#include "RecoTotemRP/RPRecoDataFormats/interface/RPTrackCandidateCollection.h"
#include "RecoTotemRP/RPRecoDataFormats/interface/RPMulFittedTrackCollection.h"
#include "DataFormats/TotemRPDetId/interface/TotRPDetId.h"
#include "Geometry/TotemRPDetTopology/interface/RPTopology.h"


 
class TotemRPDQMSource: public DQMEDAnalyzer
{
	public:
		TotemRPDQMSource(const edm::ParameterSet& ps);
		virtual ~TotemRPDQMSource();
  
	protected:
		void dqmBeginRun(edm::Run const &, edm::EventSetup const &) override;
		void bookHistograms(DQMStore::IBooker &, edm::Run const &, edm::EventSetup const &) override;
		void analyze(edm::Event const& e, edm::EventSetup const& eSetup);
		void beginLuminosityBlock(edm::LuminosityBlock const& lumi, edm::EventSetup const& eSetup);
		void endLuminosityBlock(edm::LuminosityBlock const& lumi, edm::EventSetup const& eSetup);
		void endRun(edm::Run const& run, edm::EventSetup const& eSetup);

	private:
  	  edm::EDGetTokenT< edm::DetSetVector<RPStripDigi> > tokenStripDigi;
  	  edm::EDGetTokenT< edm::DetSetVector<RPDigCluster> > tokenDigiCluster;
  	  edm::EDGetTokenT< edm::DetSetVector<RPRecoHit> > tokenRecoHit;
  	  edm::EDGetTokenT< RPRecognizedPatternsCollection > tokenPatternColl;
  	  edm::EDGetTokenT< RPTrackCandidateCollection > tokenTrackCandColl;
  	  edm::EDGetTokenT< RPFittedTrackCollection > tokenTrackColl;
  	  edm::EDGetTokenT< RPMulFittedTrackCollection > tokenMultiTrackColl;

      /*
      bool buildCorrelationPlots;                           ///< decides wheather the correlation plots are created
      std::string correlationPlotsFilter;                   ///< decides which correlation plots are created
      unsigned int correlationPlotsLimit;                   ///< maximum number of created correlation plots
      CorrelationPlotsSelector correlationPlotsSelector;
      */

    /// plots related to one (anti)diagonal
    struct DiagonalPlots
    {
      int id;

      MonitorElement *h_lrc_x_d, *h_lrc_x_n, *h_lrc_x_f;
      MonitorElement *h_lrc_y_d, *h_lrc_y_n, *h_lrc_y_f;

      DiagonalPlots() {}

      DiagonalPlots(DQMStore::IBooker &ibooker, int _id);
    };

    std::map<unsigned int, DiagonalPlots> diagonalPlots;

    /// plots related to one arm
    struct ArmPlots
    {
      int id;

      TH1D *h_numRPWithTrack_top, *h_numRPWithTrack_hor, *h_numRPWithTrack_bot;
      TH2D *h_trackCorr, *h_trackCorr_overlap;

      ArmPlots() : id(0), h_numRPWithTrack_top(NULL), h_numRPWithTrack_hor(NULL), h_numRPWithTrack_bot(NULL) {}

      ArmPlots(int _id);
    };

    std::map<unsigned int, ArmPlots> armPlots;

    /// plots related to one station
    /*
    struct StationPlots
    {
      std::map<int, std::map<int, THnSparseD*> > hist;
      int id;
      CorrelationPlotsSelector *correlationPlotsSelector;

      StationPlots() : correlationPlotsSelector(NULL), rpHits(NULL) {}
      StationPlots(int _id, std::set<unsigned int> planes, bool allocateCorrelationPlots, 
        CorrelationPlotsSelector *correlationPlotsSelector, int limit = -1);
      void Add(std::set<unsigned int> planes, int limit = -1);
    };

	std::map<unsigned int, StationPlots> stationPlots;
    */

    /// plots related to one RP
    struct PotPlots
    {
      TH1D *activity, *activity_u, *activity_v;
      TH2D *hit_plane_hist;
      TH1D *patterns_u, *patterns_v;
      TH1D *h_planes_fit_u, *h_planes_fit_v;
      TH1D *event_category;
      TH2D *trackHitsCumulativeHist;
      TH1D *track_u_profile, *track_v_profile;

      PotPlots();
      PotPlots(unsigned int id);
    };

	std::map<unsigned int, PotPlots> potPlots;

    /// plots related to one RP plane
    struct PlanePlots
    {
      TH1D *digi_profile_cumulative;
      TH1D *digi_profile_one_event;
      TH1D *cluster_profile_cumulative;
      TH1D *cluster_profile_one_event;
      TH1D *hit_multiplicity;
      TH1D *cluster_size;

      PlanePlots() : digi_profile_cumulative(NULL), digi_profile_one_event(NULL) {}
      PlanePlots(unsigned int id);
    };

	std::map<unsigned int, PlanePlots> planePlots;
};

#endif
