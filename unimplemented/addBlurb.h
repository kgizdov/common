#include "TCanvas.h"
#include "TLatex.h"
void addBlurb(TCanvas* can, int year = 0,float xpos = 0.55,bool compact = false,bool prelim=true){

   can->cd(1);
   TLatex *myLatex = new TLatex(0.5,0.5,"");
   myLatex->SetTextFont(132);
   myLatex->SetTextColor(1);
   myLatex->SetNDC(kTRUE);
   myLatex->SetTextAlign(11);
   myLatex->SetTextSize(0.06);
   if(prelim)
   {
     if(!compact)
     {
       if(year == 11)
         myLatex->DrawLatex(xpos, 0.80,"#splitline{LHCb Preliminary}{#scale[1]{2011}}");
       else if(year == 12)
         myLatex->DrawLatex(xpos, 0.80,"#splitline{LHCb Preliminary}{#scale[1]{2012}");
       else if(year == 11+12)
         myLatex->DrawLatex(xpos, 0.80,"#splitline{LHCb Preliminary}{#scale[1]{2011+2012}}");
       else
         myLatex->DrawLatex(xpos, 0.80,"LHCb Simulation");
      }
      else
      {
       if(year == 11)
         myLatex->DrawLatex(xpos, 0.80,"#splitline{LHCb Preliminary}{#scale[1]{2011}}");
       else if(year == 12)
         myLatex->DrawLatex(xpos, 0.80,"#splitline{LHCb Preliminary}{#scale[1]{2012}");
       else if(year == 11+12)
         myLatex->DrawLatex(xpos, 0.80,"#splitline{LHCb Preliminary}{#scale[1]{2011+2012}}");
       else
         myLatex->DrawLatex(xpos, 0.80,"LHCb Simulation");
      }
    }
    else
    {
     if(!compact)
     {
       if(year == 11)
         myLatex->DrawLatex(xpos, 0.80,"#splitline{#scale[1.2]{LHCb}}{#scale[1.0]{2011}}");
       else if(year == 12)
         myLatex->DrawLatex(xpos, 0.80,"#splitline{#scale[1.2]{LHCb}}{#scale[1.0]{2012}}");
       else if(year == 11+12)
         myLatex->DrawLatex(xpos, 0.80,"#splitline{#scale[1.2]{LHCb}}{#scale[1.0]{2011+2012}}");
       else
         myLatex->DrawLatex(xpos, 0.80,"LHCb Simulation");
      }
      else
      {
       if(year == 11)
         myLatex->DrawLatex(xpos, 0.80,"#splitline{#scale[1.2]{LHCb}}{#scale[1.0]{2011}}");
       else if(year == 12)
         myLatex->DrawLatex(xpos, 0.80,"#splitline{#scale[1.2]{LHCb}}{#scale[1.0]{2012}}");
       else if(year == 11+12)
         myLatex->DrawLatex(xpos, 0.80,"#splitline{#scale[1.2]{LHCb}}{#scale[1.0]{2011+2012}}");
       else
         myLatex->DrawLatex(xpos, 0.80,"LHCb Simulation");
      }
    
    }
}


//void addBlurb(TCanvas* can, int year = 0,float xpos = 0.55,bool compact = false,bool prelim=true){

//   can->cd(1);
//   TLatex *myLatex = new TLatex(0.5,0.5,"");
//   myLatex->SetTextFont(132);
//   myLatex->SetTextColor(1);
//   myLatex->SetNDC(kTRUE);
//   myLatex->SetTextAlign(11);
//   myLatex->SetTextSize(0.06);
//   if(prelim)
//   {
//     if(!compact)
//     {
//       if(year == 11)
//         myLatex->DrawLatex(xpos, 0.80,"#splitline{LHCb Preliminary}{#scale[1]{#sqrt{#font[12]{s}} = 7 TeV, #font[12]{#scale[0.5]{#int} L dt} = 1 fb^{-1}}}");
//       else if(year == 12)
//         myLatex->DrawLatex(xpos, 0.80,"#splitline{LHCb Preliminary}{#scale[1]{#sqrt{#font[12]{s}} = 8 TeV, #font[12]{#scale[0.5]{#int} L dt} = 2 fb^{-1}}}");
//       else if(year == 11+12)
//         myLatex->DrawLatex(xpos, 0.80,"#splitline{LHCb Preliminary}{#scale[1]{#sqrt{#font[12]{s}} = 7 + 8 TeV, #font[12]{#scale[0.5]{#int} L dt} = 3 fb^{-1}}}");
//       else
//         myLatex->DrawLatex(xpos, 0.80,"LHCb Simulation");
//      }
//      else
//      {
//       if(year == 11)
//         myLatex->DrawLatex(xpos, 0.80,"#splitline{LHCb Preliminary}{#splitline{#sqrt{#font[12]{s}} = 7 TeV}{#font[12]{#scale[0.5]{#int} L dt} = 1 fb^{-1}}}");
//       else if(year == 12)
//         myLatex->DrawLatex(xpos, 0.80,"#splitline{LHCb Preliminary}{#splitline{#sqrt{#font[12]{s}} = 8 TeV}{#font[12]{#scale[0.5]{#int} L dt} = 2 fb^{-1}}}");
//       else if(year == 11+12)
//         myLatex->DrawLatex(xpos, 0.80,"#splitline{LHCb Preliminary}{#splitline{#sqrt{#font[12]{s}} = 7 + 8 TeV}{#font[12]{#scale[0.5]{#int} L dt} = 3 fb^{-1}}}");
//       else
//         myLatex->DrawLatex(xpos, 0.80,"LHCb Simulation");
//      }
//    }
//    else
//    {
//     if(!compact)
//     {
//       if(year == 11)
//         myLatex->DrawLatex(xpos, 0.80,"#splitline{#scale[1.2]{LHCb}}{#scale[0.8]{#sqrt{#font[12]{s}} = 7 TeV, #font[12]{#scale[0.5]{#int} L dt} = 1 fb^{-1}}}");
//       else if(year == 12)
//         myLatex->DrawLatex(xpos, 0.80,"#splitline{#scale[1.2]{LHCb}}{#scale[0.8]{#sqrt{#font[12]{s}} = 8 TeV, #font[12]{#scale[0.5]{#int} L dt} = 2 fb^{-1}}}");
//       else if(year == 11+12)
//         myLatex->DrawLatex(xpos, 0.80,"#splitline{#scale[1.2]{LHCb}}{#scale[0.8]{#sqrt{#font[12]{s}} = 7 + 8 TeV, #font[12]{#scale[0.5]{#int} L dt} = 3 fb^{-1}}}");
//       else
//         myLatex->DrawLatex(xpos, 0.80,"LHCb Simulation");
//      }
//      else
//      {
//       if(year == 11)
//         myLatex->DrawLatex(xpos, 0.80,"#splitline{#scale[1.2]{LHCb}}{#scale[0.8]{#splitline{#sqrt{#font[12]{s}} = 7 TeV}{ #font[12]{#scale[0.5]{#int} L dt} = 1 fb^{-1}}}}");
//       else if(year == 12)
//         myLatex->DrawLatex(xpos, 0.80,"#splitline{#scale[1.2]{LHCb}}{#scale[0.8]{#splitline{#sqrt{#font[12]{s}} = 8 TeV}{ #font[12]{#scale[0.5]{#int} L dt} = 2 fb^{-1}}}}");
//       else if(year == 11+12)
//         myLatex->DrawLatex(xpos, 0.80,"#splitline{#scale[1.2]{LHCb}}{#scale[0.8]{#splitline{#sqrt{#font[12]{s}} = 7 + 8 TeV}{ #font[12]{#scale[0.5]{#int} L dt} = 3 fb^{-1}}}}");
//       else
//         myLatex->DrawLatex(xpos, 0.80,"LHCb Simulation");
//      }
//    
//    }
//}
