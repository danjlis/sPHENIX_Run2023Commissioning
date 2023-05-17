#pragma once
#if ROOT_VERSION_CODE >= ROOT_VERSION(6,00,0)
#include <fun4all/SubsysReco.h>
#include <fun4all/Fun4AllServer.h>
#include <fun4all/Fun4AllInputManager.h>
#include <fun4allraw/Fun4AllPrdfInputManager.h>
#include <fun4all/Fun4AllDstInputManager.h>
#include <phool/recoConsts.h>


// #include <calotowerbuilder/CaloTowerBuilder.h>
#include <caloreco/CaloTowerBuilder.h>

#include <ffamodules/FlagHandler.h>
#include <ffamodules/HeadReco.h>
#include <ffamodules/SyncReco.h>
#include <ffamodules/CDBInterface.h>

// #include <runtowerinfo/RunTowerInfo.h>

#include "/sphenix/user/jpark4/EMCAL_PRDF/analysis/src/build/include/caloana/CaloAna.h"
#include <caloana/CaloAna.h>

#include <fun4all/Fun4AllDstOutputManager.h>

R__LOAD_LIBRARY(libfun4all.so)
R__LOAD_LIBRARY(libfun4allraw.so)
R__LOAD_LIBRARY(libcalo_reco.so)
R__LOAD_LIBRARY(libffamodules.so)
R__LOAD_LIBRARY(libcaloana.so)

#endif
//void Fun4All_Comissioning(const char *fname = "/sphenix/lustre01/sphnxpro/commissioning/emcal/calib/calib-00005027-0000.prdf", const char *outfile = "testtree.root")
  // void Fun4All_Comissioning(const char *fname = "/sphenix/lustre01/sphnxpro/commissioning/emcal/calib/calib_1E1-00005951-0000.prdf", const char *outfile = "testtree_junk.root")
//void Fun4All_Comissioning(const char *fname = "full-00006354-0000.prdf", const char *outfile = "testtree_junk.root")

//void Fun4All_Comissioning(const char *fname = "/gpfs/mnt/gpfs02/sphenix/user/ahodges/prdfMerging/apr13_23/calib_1E3_1W3_3C9_1E1_3A6-00000001-0000.prdf", const char *outfile = "testtree_junk.root")
//void Fun4All_Comissioning(const char *fname = "/gpfs/mnt/gpfs02/sphenix/user/ahodges/macros_git/analysis/ledCaloTowerBuilder/macro/emcalSectors16.prdf", const char *outfile = "testtree_junk.root")
//void Fun4All_Comissioning(const char *fname = "calib_test-00005086-0000.prdf", const char *outfile = "testtree_junk.root")

void Fun4All_Comissioning(const char *fname = "/gpfs/mnt/gpfs02/sphenix/user/trinn/emcal_comissioning/full-00005906-0000.prdf", const char *outfile = "testtree_junk.root")
{
  gSystem->Load("libg4dst");
  Fun4AllServer *se = Fun4AllServer::instance();
  se->Verbosity(0);
  recoConsts *rc = recoConsts::instance();

 //===============
  // conditions DB flags
  //===============
  // ENABLE::CDB = true;
  // global tag
  rc->set_StringFlag("CDB_GLOBALTAG","MDC2");
  // // 64 bit timestamp
  rc->set_uint64Flag("TIMESTAMP",6);

  CaloTowerBuilder *ca = new CaloTowerBuilder();
  ca->set_detector_type(CaloTowerBuilder::CEMC);
  ca->set_nsamples(31);
  se->registerSubsystem(ca);

  CaloAna *caloana = new CaloAna("CALOANA",outfile);
  caloana->Detector("CEMC");
  se->registerSubsystem(caloana);




  Fun4AllInputManager *in = new Fun4AllPrdfInputManager("in");
  in->fileopen(fname);
  se->registerInputManager(in);


  Fun4AllDstOutputManager *out = new Fun4AllDstOutputManager("DSTOUT", "testoutput_hcalfile.root");
  out->StripNode("WAVEFORMS_CEMC");
  se->registerOutputManager(out);


  se->skip(10);
  se->run(10);
  se->End();
  se->PrintTimer();
  gSystem->Exit(0);
}
