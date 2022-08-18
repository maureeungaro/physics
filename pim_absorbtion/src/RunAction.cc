#include "RunAction.hh"
#include "Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


RunAction::RunAction() : G4UserRunAction()
{ 
	// set printing event number per each event
	G4RunManager::GetRunManager()->SetPrintProgress(1000);
	
	// Create analysis manager
	// The choice of analysis technology is done via selectin of a namespace in Analysis.hh
	auto analysisManager = G4AnalysisManager::Instance();
	G4cout << "Using " << analysisManager->GetType() << G4endl;
	
	// Create directories
	analysisManager->SetVerboseLevel(1);
	analysisManager->SetNtupleMerging(true);
	
	// Note: merging ntuples is available only with Root output
	
	// Book histograms, ntuple
	analysisManager->CreateNtuple("pima", "pim absorbtion test");
	analysisManager->CreateNtupleDColumn("PDGE");
	analysisManager->CreateNtupleDColumn("KE");
	analysisManager->FinishNtuple();
	
	/*  analysisManager->CreateNtupleSColumn("proc");
	 analysisManager->CreateNtupleDColumn("M");
	 analysisManager->CreateNtupleDColumn("Lgap");
	 analysisManager->CreateNtupleDColumn("Egamma");
	 analysisManager->CreateNtupleDColumn("x");
	 analysisManager->CreateNtupleDColumn("y");
	 analysisManager->CreateNtupleDColumn("z");
	 analysisManager->CreateNtupleDColumn("px");
	 analysisManager->CreateNtupleDColumn("py");
	 analysisManager->CreateNtupleDColumn("pz");
	 analysisManager->CreateNtupleDColumn("pdir_x");
	 analysisManager->CreateNtupleDColumn("pdir_y");
	 analysisManager->CreateNtupleDColumn("pdir_z");
	 analysisManager->CreateNtupleSColumn("pids");
	 analysisManager->CreateNtupleDColumn("pdgencode");
	 analysisManager->CreateNtupleDColumn("inTarget");
	 analysisManager->FinishNtuple();*/
	
}


RunAction::~RunAction()
{
	delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
	// Get analysis manager
	auto analysisManager = G4AnalysisManager::Instance();
	
	// Open an output file
	G4String fileName = "pima";               // file opening command moved to the class constructor
	analysisManager->OpenFile(fileName);
}


void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
	// print histogram statistics
	auto analysisManager = G4AnalysisManager::Instance();
	
	// save histograms & ntuple
	analysisManager->Write();
	analysisManager->CloseFile();
}

