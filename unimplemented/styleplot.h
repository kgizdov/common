

void styleplot(RooPlot* frame, RooPlot* pullframe, TPad* plotpad, TPad* pullpad)
{
  frame->SetTitle("");
  frame->SetXTitle("");
  frame->SetLabelSize(0,"x");
  frame->SetTitleOffset(1.2,"y");
  frame->SetTitleFont(132,"x");
  frame->SetTitleFont(132,"y");
  frame->SetLabelFont(132,"x");
  frame->SetLabelFont(132,"y");
  stringstream ytitle;
  ytitle << "#font[132]{}Candidates / (" << setprecision(1) << fixed << frame->getFitRangeBinW() << "  MeV/#font[12]{c}^{2})";
  frame->SetYTitle(ytitle.str().c_str());
  frame->SetTitleSize(0.07,"y");
  frame->SetLabelSize(0,"x");
  frame->SetLabelSize(0.07,"y");
  frame->SetTitleOffset(1.0,"y");
  frame->GetYaxis()->CenterTitle();
  pullframe->SetTitle("");
  pullframe->SetYTitle("Pull");
  //pullframe->GetXaxis()->CenterTitle();
  pullframe->GetYaxis()->CenterTitle();
  pullframe->SetLabelSize(0.20,"x");
  pullframe->SetLabelSize(0.15,"y");
  pullframe->SetTitleSize(0.20,"x");
  pullframe->SetTitleSize(0.20,"y");
  pullframe->SetTitleFont(132,"x");
  pullframe->SetTitleFont(132,"y");
  pullframe->SetLabelFont(132,"x");
  pullframe->SetLabelFont(132,"y");
  pullframe->SetTitleOffset(1.2,"x");
  pullframe->SetTitleOffset(0.35,"y");
  pullframe->SetTickLength(0.1,"x");
  pullframe->SetNdivisions(5,"y");
  //frame->SetNdivisions(611,"x");
  //pullframe->SetNdivisions(611,"x");
  frame->SetNdivisions(505,"x");
  pullframe->SetNdivisions(505,"x");
  plotpad->SetBottomMargin(0.02);
  plotpad->SetLeftMargin(0.15);
  pullpad->SetLeftMargin(0.15);
  pullpad->SetTopMargin(0);
  pullpad->SetBottomMargin(0.5);
  pullpad->SetTicks(1,0);
  return;
}
