/*
 * =====================================================================================
 *
 *       Filename:  CExperiment.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  24/02/2014 18:50:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shuji Hao (), hao.shuji@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  exit_with_help
 *  Description:  
 * =====================================================================================
 */
#define _CRT_SECURE_NO_DEPRECATE
#include "Experiment.h"
#include <iomanip>
#include <time.h>

using namespace std;
CExperiment::CExperiment()
{
  time_t raw_time;
  struct tm * timeinfo;
  time(&raw_time);
  timeinfo = localtime(&raw_time);
  strftime(date_info, 80, "%F", timeinfo);
}

void CExperiment::Parse_command_line(int argc, char **argv)
{
   
   int i=0;
   // std::string setting_file_name_test;
   for(i=1;i<argc;i++)
   {
       if(argv[i][0] != '-') break;
       if(++i >= argc)
           Exit_with_help();

       switch(argv[i-1][1])
       {
          case 's':
            this->setting_file_fullpath = argv[i];
            //std::cout << "Setting File:\t" << this->setting_file_fullpath << endl;
            break;
		  case 'i':
			this->data_dir = argv[i];
			//std::cout << "Data Location:\t" << this->data_dir << endl;
			break;
          case 'd':
            this->data_name = argv[i];
            //std::cout << "Data:\t" << this->data_name << endl;
            break;
          case 'o':
            output_dir = argv[i];
            //std::cout << "Output Locaiton:\t" << this->output_dir << endl;
            break;
          default:
            cerr << "Unknown option:" << argv[i-1][1] << endl;
            Exit_with_help();
       }
   } 
   this->data_fullpath = this->data_dir + this->data_name;
   std::cout << "Parsed argv" << std::endl;
}

void CExperiment::Exit_with_help( )
{
    cout << "Usage: models [options] data_set_file" << endl;
    cout << "options:" << endl;
    cout << "-s setting_file: set the type fout_fixed task" << endl;
    cout << "-i input_data_dir" << endl;
	cout << "-d data_set_file" << endl;
    cout << "-o output_dir" << endl;       
    exit(EXIT_FAILURE);        
}       /* -----  end fout_fixed function exit_with_help  ----- */

void CExperiment::Run_binary_experiment(int argc, char **argv)
{   
  //cout << "b_last_step.size()" << b_last_step.size() << endl;
  Parse_command_line(argc, argv);
  
  par.ImportParameters(this->setting_file_fullpath);
  
  //Data importing and processing
  int data_suc = data.Import_data(this->data_fullpath);   
  if (!data_suc)
  {
	  cout << "Pls check the data name and path\n";
	  exit(1);
  }
  if (par.Norm2One == 1)
	  data.Norm2One();

 // data.Change_to_Matrix(); 
  
  par.Initialize(data.d, data.n);
  
  
  
  CResult result_tmp(par.num_ticks); 

  
  if (!this->data_name.compare("aloi.b"))
  {
	  par.PAI_C = 0.25;		  	par.find_PAI_C = 0;
	  par.PAII_C = 0.03125;	  	par.find_PAII_C = 0;
	  par.AROW_r = 1;		  	par.find_AROW_r = 0;
	  par.AROW_eta = 16;	  	par.find_AROW_eta = 0;	  
  }
  else if (!this->data_name.compare("isolet1.b")){
	  par.PAI_C = 0.5;		  	par.find_PAI_C = 0;
	  par.PAII_C = 0.25;	  	par.find_PAII_C = 0; 
	  /*par.AROW_r = 1;	  par.AROW_eta = 16;
	  par.find_AROW_eta = 0;	  par.find_AROW_r = 0;*/
  }
  else if (!this->data_name.compare("clean.b")){
	  par.PAI_C = 0.125;	  	par.find_PAI_C = 0;
	  par.PAII_C = 0.03125;   	par.find_PAII_C = 0;	  
  }
  else if (!this->data_name.compare("dexter.b")){
	  par.PAI_C = 4;		  	par.find_PAI_C = 0;
	  par.PAII_C = 8;		  	par.find_PAII_C = 0;
  }
  else if (!this->data_name.compare("mnist.b")){
	  par.PAI_C = 25;			par.find_PAI_C = 0;
	  par.PAII_C = 0.0625;		par.find_PAII_C = 0;
	  par.AROW_eta = 4;			par.find_AROW_eta = 0;
	  par.AROW_r = 0.5;			par.find_AROW_r = 0;
  }
  else if (!this->data_name.compare("a8a.b")){
	  par.PAI_C = 0.25;	  		par.find_PAI_C = 0;
	  par.PAII_C = 0.0625;  	par.find_PAII_C = 0;	  
	  par.AROW_eta = 8;	  		par.find_AROW_eta = 0;
	  par.AROW_r = 0.5;		  	par.find_AROW_r = 0;	  
  }
  else if (!this->data_name.compare("webspam.b"))
  {
	  par.PAI_C = 0.25; 		par.find_PAI_C = 0;
	  par.PAII_C = 0.0625; 		par.find_PAII_C = 0;
	  par.AROW_r = 0.25; 		par.find_AROW_r = 0;
	  par.AROW_eta = 16; 		par.find_AROW_eta = 0;
	  par.AROWC_r = 0.03125; 	par.find_AROWC_r = 0;	  
  }
  else if (!this->data_name.compare("url.balanced.b"))
  {
	  par.PAI_C = 1; 			par.find_PAI_C = 0;
	  par.PAII_C = 0.5; 		par.find_PAII_C = 0;
	  par.AROW_r = 0.0313; 		par.find_AROW_r = 0;
	  par.AROW_eta = 8; 		par.find_AROW_eta = 0;
	  par.AROWC_r = 0.03125; 	par.find_AROWC_r = 0;	  
  }
  else if (!this->data_name.compare("news20.b"))
  {
	  par.PAI_C = 8; 			par.find_PAI_C = 0;
	  par.PAII_C = 16; 			par.find_PAII_C = 0;
	  par.AROW_r = 0.03125; 	par.find_AROW_r = 0;
	  par.AROW_eta = 2; 		par.find_AROW_eta = 0;
	  par.AROWC_r = 1; 			par.find_AROWC_r = 0;	  
  }
  else if (!this->data_name.compare("rcv1_train.b"))
  {
	  par.PAI_C = 1; 			par.find_PAI_C = 0;
	  par.PAII_C = 1; 			par.find_PAII_C = 0;
	  par.AROW_r = 0.125; 		par.find_AROW_r = 0;
	  par.AROW_eta = 2; 		par.find_AROW_eta = 0;
	  par.AROWC_r = 0.03125; 	par.find_AROWC_r = 0;	  
  }
  else if (!this->data_name.compare("gisette.b"))
  {
	  par.PAI_C = 1; 			par.find_PAI_C = 0;
	  par.PAII_C = 1; 			par.find_PAII_C = 0;
	  par.AROW_r = 2; 			par.find_AROW_r = 0;
	  par.AROW_eta = 1; 		par.find_AROW_eta = 0;
	  par.AROWC_r = 0.25; 		par.find_AROWC_r = 0;	  
  }
  else if (!this->data_name.compare("url.b"))
  {
	  par.PAI_C = 0.5; 			par.find_PAI_C = 0;
	  par.PAII_C = 0.25; 		par.find_PAII_C = 0;
	  par.AROW_r = 0.125; 		par.find_AROW_r = 0;
	  par.AROW_eta = 16; 		par.find_AROW_eta = 0;
	  par.AROWC_r = 0.0625; 	par.find_AROWC_r = 0;	  
  }
  
  Find_best_parameter();

 // const char *vinit[] = { "PE", "APE", "RPE", "PA", "APA", "RPA", "PAI", "APAI", "RPAI", "PAII", "APAII", "RPAII", "SOP", "ASOP", "RSOP", "AASOP", "AASOP2", "AROW", "AAROW", "RAROW" };
  CModel** models = new CModel*[4];  
  vector<string> alg_names;
  
  models[0] = new CModelPE;
  // alg_names.push_back("PE"); 
  alg_names.push_back("APE"); 
  // alg_names.push_back("RPE");
  
  models[1] = new CModelPA;
  // alg_names.push_back("PA"); 
  // alg_names.push_back("APA"); 
  // alg_names.push_back("RPA");

  // alg_names.push_back("PAI"); 
  // alg_names.push_back("APAI"); 
  // alg_names.push_back("RPAI");

  // alg_names.push_back("PAII"); 
  alg_names.push_back("APAII"); 
  // alg_names.push_back("RPAII");
  
  if (par.Full_Matrix == 1) // using full matrix
  {
	  models[2] = new CModelSOP;
	  // alg_names.push_back("SOP"); 
	  alg_names.push_back("ASOP"); 
	  // alg_names.push_back("RSOP"); 
	  // alg_names.push_back("AASOP"); alg_names.push_back("AASOP2");

	  models[3] = new CModelAROW;
	  alg_names.push_back("AROW"); 
	  alg_names.push_back("AAROW");  // margin-based query strategy
	  alg_names.push_back("AAROW2"); // proposed in SOAL article
	  alg_names.push_back("RAROW");  // random version
	  
	  // models[4] = new CModelAROWC;
	  // alg_names.push_back("AROWC");
  }
  else	// using sparce matrix
  {
	  models[2] = new CModelSOPD;
	  // alg_names.push_back("SOPD"); 
	  alg_names.push_back("ASOPD"); 
	  // alg_names.push_back("RSOPD");
	 // alg_names.push_back("AASOPD"); alg_names.push_back("AASOPD2");
	  
	  models[3] = new CModelAROWD;
	  alg_names.push_back("AROWD");
	  alg_names.push_back("AAROWD");  
	  alg_names.push_back("AAROWD2"); 
	  alg_names.push_back("RAROWD");

	  // crammer paper, passive query strategy which query all fout_fixed the instances
	  // models[3] = new CModelAROWD;
	  // alg_names.push_back("AROWCD");
  }

  vector<double> b_last_step;
  b_last_step.resize(alg_names.size());
  for(size_t i=0; i<alg_names.size(); i++)
    b_last_step[i] = 0.0;

  vector<vector<vector<CResult> > > result;
  result.resize(par.num_que);
  for(size_t i=0; i<par.num_que; i++)
  {
    result[i].resize(alg_names.size());
    for(size_t j=0; j<alg_names.size(); j++)
    {
      result[i][j].resize(par.num_fold);
      for(size_t k=0; k<par.num_fold; k++)
        result[i][j][k].Initialize(par.num_ticks);
    }
  } 



  //learn
  for(size_t i_que=0; i_que<par.num_que; i_que++)
  {      
      cout << i_que << "-th query" << endl;

	  double b = pow(2.0, (par.b_start + i_que*par.que_increase_speed));
      double b2 = pow(2.0, (par.b_start2 + i_que*par.que_increase_speed2));

      for(size_t j_fold=0; j_fold<par.num_fold; j_fold++)
      {
          cout << "  " << j_fold << "-th fold" << endl;

		  cout.precision(3);
          
		  par.Generate_permutation(data.n);
		  
		  int k_alg = 0;
		  
		  //PE
		  /*
		  if (i_que>0)
		  {
			  result[i_que][k_alg][j_fold] = result[0][k_alg][j_fold];
		  }
		  else{
			  models[0]->SetAlgName(alg_names[k_alg]);
			  result_tmp.Reset(); par.Reset(data.d, data.n);
			  models[0]->Learning(&result_tmp, &data, &par);
			  result[i_que][k_alg][j_fold] = result_tmp;
		  }
		  cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  k_alg++;
		  */

		  //APE
		  par.b = b;
		  models[0]->SetAlgName(alg_names[k_alg]);
		  result_tmp.Reset();	par.Reset(data.d, data.n);
		  models[0]->Learning(&result_tmp, &data, &par);
		  result[i_que][k_alg][j_fold] = result_tmp;
		  cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  k_alg++;

		  /*
		  //RPE
		  par.b = result_tmp.que;
		  models[0]->SetAlgName(alg_names[k_alg]);
		  result_tmp.Reset(); par.Reset(data.d, data.n);
		  models[0]->Learning(&result_tmp, &data, &par);
		  result[i_que][k_alg][j_fold] = result_tmp;
		  cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  k_alg++;

		  
		  //PA
		  if (i_que>0)
		  {
			  result[i_que][k_alg][j_fold] = result[0][k_alg][j_fold];
		  }
		  else{
			  models[1]->SetAlgName(alg_names[k_alg]);
			  result_tmp.Reset(); par.Reset(data.d, data.n);
			  models[1]->Learning(&result_tmp, &data, &par);
			  result[i_que][k_alg][j_fold] = result_tmp;
		  }
		  cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  k_alg++;

		  //APA
		  par.b = b;
		  models[1]->SetAlgName(alg_names[k_alg]);
		  result_tmp.Reset(); par.Reset(data.d, data.n);
		  models[1]->Learning(&result_tmp, &data, &par);
		  result[i_que][k_alg][j_fold] = result_tmp;
		  cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  k_alg++;
		  
		  //RPA
		  par.b = result_tmp.que;
		  models[1]->SetAlgName(alg_names[k_alg]);
		  result_tmp.Reset(); par.Reset(data.d, data.n);
		  models[1]->Learning(&result_tmp, &data, &par);
		  result[i_que][k_alg][j_fold] = result_tmp;
		  cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  k_alg++;

		  //PAI		
		  if (i_que>0)
		  {
			  result[i_que][k_alg][j_fold] = result[0][k_alg][j_fold];
		  }
		  else{
			  models[1]->SetAlgName(alg_names[k_alg]);
			  result_tmp.Reset(); par.Reset(data.d, data.n);
			  models[1]->Learning(&result_tmp, &data, &par);
			  result[i_que][k_alg][j_fold] = result_tmp;
		  }
		  cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  k_alg++;

		  //APAI
		  par.b = b;
		  models[1]->SetAlgName(alg_names[k_alg]);
		  result_tmp.Reset(); par.Reset(data.d, data.n);
		  models[1]->Learning(&result_tmp, &data, &par);
		  result[i_que][k_alg][j_fold] = result_tmp;
		  cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  k_alg++;
		  
		  //RAPI
		  par.b = result_tmp.que;
		  models[1]->SetAlgName(alg_names[k_alg]);
		  result_tmp.Reset();
		  models[1]->Learning(&result_tmp, &data, &par);
		  result[i_que][k_alg][j_fold] = result_tmp;
		  cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  k_alg++;
		

		  //PAII	
		  if (i_que>0)
		  {
			  result[i_que][k_alg][j_fold] = result[0][k_alg][j_fold];
		  }
		  else{
			  models[1]->SetAlgName(alg_names[k_alg]);
			  result_tmp.Reset(); par.Reset(data.d, data.n);
			  models[1]->Learning(&result_tmp, &data, &par);
			  result[i_que][k_alg][j_fold] = result_tmp;
		  }
		  cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  k_alg++;
		  */
		  //APAII
		  par.b = b;
		  models[1]->SetAlgName(alg_names[k_alg]);
		  result_tmp.Reset(); par.Reset(data.d, data.n);
		  models[1]->Learning(&result_tmp, &data, &par);
		  result[i_que][k_alg][j_fold] = result_tmp;
		  cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  k_alg++;

		  /*
		  //RPAII
		  par.b = result_tmp.que;
		  models[1]->SetAlgName(alg_names[k_alg]);
		  result_tmp.Reset(); par.Reset(data.d, data.n);
		  models[1]->Learning(&result_tmp, &data, &par);
		  result[i_que][k_alg][j_fold] = result_tmp;
		  cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  k_alg++;
		  */


		  //SOP	
		  /*	
		  if (i_que>0)
		  {
			  result[i_que][k_alg][j_fold] = result[0][k_alg][j_fold];
		  }
		  else{
			  models[2]->SetAlgName(alg_names[k_alg]);
			  result_tmp.Reset(); par.Reset(data.d, data.n);
			  models[2]->Learning(&result_tmp, &data, &par);
			  result[i_que][k_alg][j_fold] = result_tmp;
		  }
		  cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  k_alg++;
		  */

		  //ASOP
		  par.b = b2;
		  models[2]->SetAlgName(alg_names[k_alg]);
		  result_tmp.Reset(); par.Reset(data.d, data.n);
		  models[2]->Learning(&result_tmp, &data, &par);
		  result[i_que][k_alg][j_fold] = result_tmp;
		  cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  k_alg++;

		  /*
		  //RSOP
		  par.b = result_tmp.que;
		  models[2]->SetAlgName(alg_names[k_alg]);
		  result_tmp.Reset(); par.Reset(data.d, data.n);
		  models[2]->Learning(&result_tmp, &data, &par);
		  result[i_que][k_alg][j_fold] = result_tmp;
		  cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  k_alg++;
		  */
		  ////AASOP
		  //par.b = b;
		  //models[2]->SetAlgName(alg_names[k_alg]);
		  //result_tmp.Reset(); par.Reset(data.d, data.n);
		  //models[2]->Learning(&result_tmp, &data, &par);
		  //result[i_que][k_alg][j_fold] = result_tmp;
		  //cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  //k_alg++;

		  ////AASOP2
		  //par.b = b;
		  //models[2]->SetAlgName(alg_names[k_alg]);
		  //result_tmp.Reset(); par.Reset(data.d, data.n);
		  //models[2]->Learning(&result_tmp, &data, &par);
		  //result[i_que][k_alg][j_fold] = result_tmp;
		  //cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  //k_alg++;

		  //AROW
		  if (i_que>0)
		  {
			  result[i_que][k_alg][j_fold] = result[0][k_alg][j_fold];
		  }
		  else{
			  models[3]->SetAlgName(alg_names[k_alg]);
			  result_tmp.Reset(); par.Reset(data.d, data.n);
			  models[3]->Learning(&result_tmp, &data, &par);
			  result[i_que][k_alg][j_fold] = result_tmp;
		  }
		  cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  k_alg++;

		  //AAROW
		  par.b = b;
		  models[3]->SetAlgName(alg_names[k_alg]);
		  result_tmp.Reset(); par.Reset(data.d, data.n);
		  models[3]->Learning(&result_tmp, &data, &par);
		  result[i_que][k_alg][j_fold] = result_tmp;
		  cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  k_alg++;

		  //AAROW2
		  par.b = b2;
		  models[3]->SetAlgName(alg_names[k_alg]);
		  result_tmp.Reset(); par.Reset(data.d, data.n);
		  models[3]->Learning(&result_tmp, &data, &par);
		  result[i_que][k_alg][j_fold] = result_tmp;
		  cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  k_alg++;

		  //RAROW
		  par.b = result_tmp.que;
		  models[3]->SetAlgName(alg_names[k_alg]);
		  result_tmp.Reset(); par.Reset(data.d, data.n);
		  models[3]->Learning(&result_tmp, &data, &par);
		  result[i_que][k_alg][j_fold] = result_tmp;
		  cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  k_alg++;

		  //  //AROWC
		  // if (i_que>0)
		  // {
			 //  result[i_que][k_alg][j_fold] = result[0][k_alg][j_fold];
		  // }
		  // else{
			 //  models[4]->SetAlgName(alg_names[k_alg]);
			 //  result_tmp.Reset(); par.Reset(data.d, data.n);
			 //  models[4]->Learning(&result_tmp, &data, &par);
			 //  result[i_que][k_alg][j_fold] = result_tmp;
		  // }
		  // cout << alg_names[k_alg] << "\t" << result[i_que][k_alg][j_fold].que << "\t" << result[i_que][k_alg][j_fold].acc << "\t" << result[i_que][k_alg][j_fold].time << endl;
		  // k_alg++;

      }//end fout_fixed second loop, cross validation      
  }//end fout_fixed first loop, different query ratio
  
  //OutputResult(&result);

  //initial
  std::vector<vector<CResult> > res_que_alg;
  res_que_alg.resize(par.num_que);
  for (size_t i = 0; i < par.num_que; ++i)
  {
	  res_que_alg[i].resize(alg_names.size());
	  for (size_t j = 0; j < alg_names.size(); ++j)
	  {
		  res_que_alg[i][j].Initialize(par.num_ticks);
	  }
  }

  //sum fout_fixed fold
  for (size_t i = 0; i < par.num_que; ++i)
  {
	  for (size_t j = 0; j < alg_names.size(); ++j)
	  {
		  for (size_t k = 0; k < par.num_fold; ++k)
		  {
			  res_que_alg[i][j] = res_que_alg[i][j] + result[i][j][k];
		  }
	  }
  }

  //average
  for (size_t i = 0; i < par.num_que; ++i)
  {
	  for (size_t j = 0; j < alg_names.size(); ++j)
	  {
		  res_que_alg[i][j] = res_que_alg[i][j] / par.num_fold;
	  }
  }

  //compute standard deviation
  for (size_t i = 0; i < par.num_que; ++i)
  {
	  for (size_t j = 0; j < alg_names.size(); ++j)
	  {
		  double que_tmp = 0.0, acc_tmp = 0.0, time_tmp = 0.0, F1_tmp = 0.0;
		  for (size_t k = 0; k < par.num_fold; k++)
		  {
			  que_tmp += pow(res_que_alg[i][j].que-result[i][j][k].que,2);
			  acc_tmp += pow(res_que_alg[i][j].acc-result[i][j][k].acc,2);
			  time_tmp += pow(res_que_alg[i][j].time-result[i][j][k].time,2);
			  F1_tmp += pow(res_que_alg[i][j].F1 - result[i][j][k].F1, 2);
		  }
		  res_que_alg[i][j].std_que =  sqrt(que_tmp / par.num_fold);
		  res_que_alg[i][j].std_acc = sqrt(acc_tmp / par.num_fold);
		  res_que_alg[i][j].std_time = sqrt(time_tmp / par.num_fold);
		  res_que_alg[i][j].std_F1 = sqrt(F1_tmp / par.num_fold);
	  }
  }

  //output varied query ratio result  
  string fout_varied_name = output_dir + this->data_name + "_";
  fout_varied_name.append(this->date_info);
  fout_varied_name += ".txt";
  cout << "output_file_name = " << fout_varied_name << endl;
  ofstream fout_varied(fout_varied_name.c_str());
  for (size_t j = 0; j<alg_names.size(); j++)
  {
	  //different query_ratio
  	  fout_varied << alg_names[j] << endl;
  	  fout_varied << "que ";
	  for (size_t i = 0; i<par.num_que; i++)
	  {
		  fout_varied << res_que_alg[i][j].que << " ";
	  }
	  fout_varied << endl;

	  //std_que
	  fout_varied << "std_que ";
	  for (size_t i = 0; i<par.num_que; i++)
	  {
		  fout_varied << res_que_alg[i][j].std_que << " ";
	  }
	  fout_varied << endl;

	  //different query accuracy
	  fout_varied << "acc ";
	  for (size_t i = 0; i<par.num_que; i++)
	  {
		  fout_varied << res_que_alg[i][j].acc << " ";
	  }
	  fout_varied << endl;

	  //std_acc
	  fout_varied << "std_acc ";
	  for (size_t i = 0; i<par.num_que; i++)
	  {
		  fout_varied << res_que_alg[i][j].std_acc << " ";
	  }
	  fout_varied << endl;

	  //different f1 measure
	  fout_varied << "f1 ";
	  for (size_t i = 0; i<par.num_que; i++)
	  {
		  fout_varied << res_que_alg[i][j].F1 << " ";
	  }
	  fout_varied << endl;

	  //std_f1
	  fout_varied << "std_f1 ";
	  for (size_t i = 0; i<par.num_que; i++)
	  {
		  fout_varied << res_que_alg[i][j].std_F1 << " ";
	  }
	  fout_varied << endl;

	  //different time
	  fout_varied << "time ";
	  for (size_t i = 0; i<par.num_que; i++)
	  {
		  fout_varied << res_que_alg[i][j].time << " ";
	  }
	  fout_varied << endl;	 

	  //std_time
	  fout_varied << "std_time ";
	  for (size_t i = 0; i<par.num_que; i++)
	  {
		  fout_varied << res_que_alg[i][j].std_time << " ";
	  }
	  fout_varied << endl;
  }
  fout_varied.close();
  
  //output fixed query ratio
  string fout_fixed_name = output_dir + this->data_name + "_fixed_";
  fout_fixed_name.append(this->date_info);
  fout_fixed_name += ".txt";
  ofstream fout_fixed(fout_fixed_name.c_str());

  // fout_fixed.precision(3);
  // fout_fixed << std::fixed;

  //write basic information
  fout_fixed << "Data\t" << " # Features\t" << "# Instances\t"<<" # Positive Instances\t" << "# Negative Instances" << endl;
  fout_fixed << this->data_name << "\t" << data.d << "\t" << data.n <<"\t" << data.num_pos << "\t" <<data.num_neg<< endl;
  fout_fixed << "PAI_C=" << par.PAI_C << "\t PAII_C=" << par.PAII_C << "\t AROW_r=" << par.AROW_r << "\t AROW_eta=" << par.AROW_eta << endl;
  fout_fixed << "AROWC_r=" << par.AROWC_r << endl;
  fout_fixed << "Norm2One=" << par.Norm2One << "\t num_que=" << par.num_que << "\t num_fold=" << par.num_fold << endl;

  for (size_t i = 0; i<par.num_que; i++)//for each query
  {
	  fout_fixed << endl;
	  fout_fixed << "b=" << par.b_start + i*par.que_increase_speed <<  pow(2.0, (par.b_start + i*par.que_increase_speed)) << endl;
	  fout_fixed << "b2=" << par.b_start2 + i*par.que_increase_speed2 << pow(2.0, (par.b_start2 + i*par.que_increase_speed2)) << endl;
	  fout_fixed << "Dataset & Algorithm & Query (%) & Accuracy & F-measure & Time (s)" << endl;
	  for (size_t j = 0; j < alg_names.size(); j++)
	  {
		  fout_fixed << left << setw(8) << alg_names[j] << "  &  "  << float(res_que_alg[i][j].que * 100) << "$\\pm$"<< res_que_alg[i][j].std_que * 100;
		  fout_fixed << "  &  " << res_que_alg[i][j].acc  << "$\\pm$" <<  res_que_alg[i][j].std_acc ;
		  fout_fixed << "  &  " << res_que_alg[i][j].F1   << "$\\pm$" <<  res_que_alg[i][j].std_F1;
		  fout_fixed << "  &  " << res_que_alg[i][j].time << "$\\pm$" <<  res_que_alg[i][j].std_time << endl;
	  }	  
	  fout_fixed << endl;
  }
  fout_fixed.close();

  /* output with desired order
  fout_fixed_name = output_dir + this->data_name;
  fout_fixed_name += "_fixed_in.txt";
  // int a[6];
  // a[0]=19; a[1]=1; a[2]=10;a[3]=13;a[4]=18;a[5]=17;
//  ofstream fout_fixed;
  fout_fixed.open(fout_fixed_name.c_str());
  fout_fixed.precision(3);
  fout_fixed << std::fixed;
  fout_fixed << "Data\t" << " # Features\t" << "# Instances\t"<<" # Positive Instances\t" << "# Negative Instances" << endl;
  fout_fixed << this->data_name << "\t" << data.d << "\t" << data.n <<"\t" << data.num_pos << "\t" <<data.num_neg<< endl;
  fout_fixed << "PAI_C=" << par.PAI_C << "\t PAII_C=" << par.PAII_C << "\t AROW_r=" << par.AROW_r << "\t AROW_eta=" << par.AROW_eta << endl;
  fout_fixed << "AROWC_r=" << par.AROWC_r << endl;
  fout_fixed << "Norm2One=" << par.Norm2One << "\t num_que=" << par.num_que << "\t num_fold=" << par.num_fold << endl;
  for (int i = 0; i<par.num_que; i++)//for each query
  {
	  fout_fixed << endl ;
	  fout_fixed << "b=" <<  pow(2.0, (par.b_start + i*par.que_increase_speed)) << " \t b2= " << pow(2.0, (par.b_start2 + i*par.que_increase_speed2)) << endl;
	  fout_fixed << "Dataset & Algorithm & Query (%) & Accuracy & Time (s)" << endl;
	  for (int ind_alg = 0; ind_alg < alg_names.size(); ind_alg++)
	  {
		  int j = a[ind_alg];
		  fout_fixed << left << setw(8)  << alg_names[j] << "  &  " << res_que_alg[i][j].que * 100 << "$\\pm$" << res_que_alg[i][j].std_que * 100;
		  fout_fixed << "  &  " << res_que_alg[i][j].acc  << "$\\pm$"  << res_que_alg[i][j].std_acc ;
		 // fout_fixed << " & " << setprecision(3)<< res_que_alg[i][j].F1   << "$\\pm$" << setprecision(3) << res_que_alg[i][j].std_F1;
		  fout_fixed << "  &  " << res_que_alg[i][j].time << "$\\pm$"  << res_que_alg[i][j].std_time << endl;
	  }	  
	  fout_fixed << endl;
  }
  fout_fixed.close();
  */

}//end fout_fixed function

void CExperiment::Find_best_parameter()
{	
	if (!par.find_PAI_C && !par.find_PAII_C && !par.find_AROW_r && !par.find_AROW_eta && !par.find_AROWC_r)
	{
		return;
	}	


	string fout_par_name = this->output_dir + data_name + "_par_";
	fout_par_name.append(date_info);
	fout_par_name += ".txt"; // Model[j]->Get_alg_name();
	
	cout << "output_file_name = " << fout_par_name << endl;
	ofstream fout_par(fout_par_name.c_str());

	string fout_par_figure_name = this->output_dir + data_name + "_par_figure_";
	fout_par_figure_name.append(date_info);
	fout_par_figure_name += ".txt";

	ofstream fout_par_fig(fout_par_figure_name.c_str());

	if (!fout_par.is_open()){
		cout << fout_par_name << "\t could not be open\n";
		getchar();
		exit(1);
	}
	
	double max_PAI_Acc = 0.0, best_PAI_C = 0.0;
	double max_PAII_Acc = 0.0, best_PAII_C = 0.0;
	CResult result_tmp(par.num_ticks);
	//cout.precision(3);
	
	if (par.find_PAI_C){
		CModel *pa = new CModelPA;
		cout << "Begin to find best parameters for PAI algorithm " << endl;
		cout << "/******************************************/" << endl;
		cout << "max_PAI_F1=" <<"\t best_PAI_C="<< endl;
		fout_par << "/******************************************/" << endl;
		if (par.F1_or_acc){
			fout_par <<"PAI_C\t Acc\t F1\t Max_F1" << endl;
			cout <<"PAI_C\t Acc\t F1\t Max_F1" << endl;
		}else{
			fout_par <<"PAI_C\t Acc\t F1\t Max_Acc" << endl;
			cout <<"PAI_C\t Acc\t F1\t Max_Acc" << endl;
		}
		for (int i = 0; i < 11; i++)
		{
			double C_Test = pow(2, -5 +  i);
			
			par.PAI_C = C_Test;
			pa->SetAlgName("PAI");
			double tmp_acc = 0.0;
			double tmp_F1 = 0.0;
			for (size_t  j = 0; j < par.num_fold; j++)
			{
				par.Generate_permutation(data.n);
				result_tmp.Reset();
				par.Reset(data.d,data.n);
				pa->Learning(&result_tmp, &data, &par);
				tmp_acc += result_tmp.acc;
				tmp_F1 += result_tmp.F1;
			}
			tmp_acc = tmp_acc / par.num_fold;
			tmp_F1 = tmp_F1 / par.num_fold;			
			if (par.F1_or_acc)
			{				
				if (tmp_F1 > max_PAI_Acc){
					max_PAI_Acc = tmp_F1;
					best_PAI_C = C_Test;
				}
				fout_par_fig << tmp_F1 << " ";
			}else{
				if (tmp_acc > max_PAI_Acc){
					max_PAI_Acc = tmp_acc;
					best_PAI_C = C_Test;
				}
				fout_par_fig << tmp_acc << " ";
			}
			fout_par << par.PAI_C << "\t" << tmp_acc << "\t" << tmp_F1 << "\t" << max_PAI_Acc << endl;
			cout << par.PAI_C << "\t" << tmp_acc << "\t" << tmp_F1 << "\t" << max_PAI_Acc << endl;
		}
		par.PAI_C = best_PAI_C;		
		cout << "/******************************************/" << endl;
		fout_par << "/******************************************/" << endl;
		fout_par << "Best PAI_C: \t" << par.PAI_C << endl;
		cout << "Best PAI_C: \t" << par.PAI_C << endl;
		fout_par_fig << endl;
		delete pa;
	}

	if (par.find_PAII_C){
		CModel *pa = new CModelPA;
		cout << "/******************************************/" << endl;
		cout << "Begin to find best parameters for PAII algorithm " << endl;
		fout_par << "/******************************************/" << endl;
		if (par.F1_or_acc){
			fout_par <<"PAII_C\t Acc\t F1\t Max_F1" << endl;
			cout <<"PAII_C\t Acc\t F1\t Max_F1" << endl;
		}else{
			fout_par <<"PAII_C\t Acc\t F1\t Max_Acc" << endl;
			cout <<"PAII_C\t Acc\t F1\t Max_Acc" << endl;
		}
		for (int i = 0; i < 11; i++)
		{
			double C_Test = pow(2, -5 +  i);
			
			par.PAII_C = C_Test;
			pa->SetAlgName("PAII");
			double tmp_acc = 0.0, tmp_F1 = 0.0;
			for (size_t j = 0; j < par.num_fold; j++)
			{
				par.Generate_permutation(data.n);
				result_tmp.Reset();
				par.Reset(data.d,data.n);
				pa->Learning(&result_tmp, &data, &par);
				tmp_acc += result_tmp.acc;
				tmp_F1 += result_tmp.F1;
			}
			tmp_acc = tmp_acc / par.num_fold;
			tmp_F1 = tmp_F1 / par.num_fold;		
			if (par.F1_or_acc)
			{				
				if (tmp_F1 > max_PAII_Acc){
					max_PAII_Acc = tmp_F1;
					best_PAII_C = C_Test;
				}
				fout_par_fig << tmp_F1 << " ";
			}else{
				if (tmp_acc > max_PAII_Acc){
					max_PAII_Acc = tmp_acc;
					best_PAII_C = C_Test;
				}
				fout_par_fig << tmp_acc << " ";
			}
			fout_par << par.PAII_C << "\t" << tmp_acc << "\t" << tmp_F1 << "\t" << max_PAII_Acc << endl;
			cout << par.PAII_C << "\t" << tmp_acc << "\t" << tmp_F1 << "\t" << max_PAII_Acc << endl;
		}
		par.PAII_C = best_PAII_C;		
		cout << "/******************************************/" << endl;
		fout_par << "/******************************************/" << endl;
		fout_par << "Best PAII_C:\t" << par.PAII_C << endl;		
		cout << "Best PAII_C:\t" << par.PAII_C << endl;		
		fout_par_fig << endl;
		delete pa;
	}
	
	if (par.find_AROW_eta && par.find_AROW_r){
		cout << "/******************************************/" << endl;
		fout_par << "/******************************************/" << endl;
		cout << "Begin to find best parameters for AROW algorithm" << endl;
		
		if (par.F1_or_acc){
			fout_par <<"AROW_r\t AROW_eta\t Acc\t F1\t Max_F1" << endl;
			cout <<"AROW_r\t AROW_eta\t Acc\t F1\t Max_F1" << endl;
		}else{
			fout_par <<"AROW_r\t AROW_eta\t Acc\t F1\t Max_Acc" << endl;
			cout <<"AROW_r\t AROW_eta\t Acc\t F1\t Max_Acc" << endl;
		}

		double max_AROW_Acc = 0.0, best_r = 0.0, best_eta = 0.0;
		CModel *arow  = NULL;
		string alg_name;
		if (par.Full_Matrix == 1){
			cout << "Full version" <<endl;
			arow = new CModelAROW;
			alg_name = "AROW";
		}
		else{
			cout << "Diagonal version" <<endl;
			arow = new CModelAROWD;
			alg_name = "AROWD";
		}
		for (int i = 0; i < 11; i++)
		{
			double r = pow(2, -5 + i);
			for (int j = 0; j < 11; j++)
			{
				double eta = pow(2, -5 + j);
				par.AROW_r = r;
				par.AROW_eta = eta;
				double tmp_F1=0.0,tmp_acc=0.0;								
				for (size_t i = 0; i < par.num_fold; i++)
				{
					par.Generate_permutation(data.n);
					result_tmp.Reset();
					par.Reset(data.d,data.n);
					arow->SetAlgName(alg_name);
					arow->Learning(&result_tmp, &data, &par);
					tmp_acc += result_tmp.acc;
					tmp_F1 += result_tmp.F1;
				}
				tmp_acc = tmp_acc / par.num_fold;
				tmp_F1 = tmp_F1 / par.num_fold;			
				if(par.F1_or_acc){
					if (tmp_F1 > max_AROW_Acc){
						max_AROW_Acc = tmp_F1;
						best_r = par.AROW_r;
						best_eta = par.AROW_eta;					
					}
					fout_par_fig << tmp_F1 << " ";
				}else{
					if (tmp_acc > max_AROW_Acc){
						max_AROW_Acc = tmp_acc;
						best_r = par.AROW_r;
						best_eta = par.AROW_eta;					
					}
					fout_par_fig << tmp_acc << " ";
				}
				fout_par << par.AROW_r << "\t" << par.AROW_eta << "\t" << tmp_acc << "\t" << tmp_F1 << "\t" << max_AROW_Acc << endl;
				cout << par.AROW_r << "\t" << par.AROW_eta << "\t" << tmp_acc << "\t" << tmp_F1 << "\t" << max_AROW_Acc << endl;
				//cout << "Time:\t" << result_tmp.time << endl;
			}
		}
		par.AROW_r = best_r;
		par.AROW_eta = best_eta;
		delete arow;		
		//cout << "\t Best AROW_r=" << par.AROW_r << "\t AROW_eta=" << par.AROW_eta << endl;
		cout << "/******************************************/" << endl;
		fout_par << "/******************************************/" << endl;
		fout_par << "Best AROW_r=" << par.AROW_r << "\t AROW_eta=" << par.AROW_eta << endl;
		cout << "Best AROW_r=" << par.AROW_r << "\t AROW_eta=" << par.AROW_eta << endl;
		fout_par_fig << endl;
	}

	if(par.find_AROWC_r == 1.0)
	{
		cout << "/******************************************/" << endl;
		fout_par << "/******************************************/" << endl;
		cout << "Begin to find best parameters for AROWC algorithm" << endl;
		
		if (par.F1_or_acc){
			fout_par <<"AROWC_r\t Acc\t F1\t Max_F1" << endl;
			cout <<"AROWC_r\t Acc\t F1\t Max_F1" << endl;
		}else{
			fout_par <<"AROWC_r\t Acc\t F1\t Max_Acc" << endl;
			cout <<"AROWC_r\t Acc\t F1\t Max_Acc" << endl;
		}

		double max_AROWC_Acc = 0.0, best_r = 0.0;
		CModel *arowc  = NULL;
		string alg_name;
		if (par.Full_Matrix == 1){
			cout << "Full version" <<endl;
			arowc = new CModelAROWC;
			alg_name = "AROWC";
		}
		else{
			cout << "Diagonal version" <<endl;
			arowc = new CModelAROWCD;
			alg_name = "AROWCD";
		}
		for (int i = 0; i < 11; i++)
		{
			double r = pow(2, -5 + i);
			
			par.AROWC_r = r;
			
			double tmp_F1=0.0,tmp_acc=0.0;								
			for (size_t i = 0; i < par.num_fold; i++)
			{
				par.Generate_permutation(data.n);
				result_tmp.Reset();
				par.Reset(data.d,data.n);
				arowc->SetAlgName(alg_name);
				arowc->Learning(&result_tmp, &data, &par);
				tmp_acc += result_tmp.acc;
				tmp_F1 += result_tmp.F1;
			}
			tmp_acc = tmp_acc / par.num_fold;
			tmp_F1 = tmp_F1 / par.num_fold;			
			if(par.F1_or_acc){
				if (tmp_F1 > max_AROWC_Acc){
					max_AROWC_Acc = tmp_F1;
					best_r = par.AROWC_r;					
				}
				fout_par_fig << tmp_F1 << " ";
			}else{
				if (tmp_acc > max_AROWC_Acc){
				max_AROWC_Acc = tmp_acc;
				best_r = par.AROWC_r;					
				}
				fout_par_fig << tmp_acc << " ";
			}
			fout_par << par.AROWC_r<< "\t" << tmp_acc << "\t" << tmp_F1 << "\t" << max_AROWC_Acc << endl;
			cout << par.AROWC_r << "\t" << tmp_acc << "\t" << tmp_F1 << "\t" << max_AROWC_Acc << endl;
		
		}
		par.AROWC_r = best_r;		
		delete arowc;
		
		//cout << "\t Best AROW_r=" << par.AROW_r << endl;
		cout << "/******************************************/" << endl;
		fout_par << "/******************************************/" << endl;
		fout_par << "Best AROWC_r=" << par.AROWC_r << endl;
		cout << "Best AROWC_r=" << par.AROWC_r << endl;

		fout_par_fig << endl;
	}

	fout_par.close();
	fout_par_fig.close();
}