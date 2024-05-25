﻿


#include "pch.h"
#include "Intermediate.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <string>



CIntermediate::CIntermediate()
:Control{0}
,aOperator{0}
{
	Control.EN = 1;
	Control.KML = 0;
	Control.KMH = 128;
	
	for (int i = 0; i < _countof(aOperator); ++i){
		aOperator[i].EN = 1;
	}
}



void CIntermediate::to_json(nlohmann::json& j) const
{
	#if false//[
	j = nlohmann::json{
		{"Information",{
			{"Summary",		"Timbre for OPN Series",	},
			{"ChipType",	"YM2203",	},
		}},
		{"Meta",{
			{"Application",	"OPNx-TimbreEditor",	},
			{"Version",		"0.0.0",	},
		}},
		{"Timbre",{
			{"Control",{
				{"EN",		Control.EN,	},
				{"FDE",		Control.FDE,},
				{"ALG",		Control.ALG,},
				{"FB",		Control.FB,	},
				{"NUM",		Control.NUM,},
				{"KML",		Control.KML,},
				{"KMH",		Control.KMH,},
				{"SE",		Control.SE,	},
				{"KT",		Control.KT,	},
				{"FDT",		Control.FDT,},
			}},
			{"Operators",{
				{"EN",{		aOperator[0].EN,	aOperator[1].EN,	aOperator[2].EN,	aOperator[3].EN,	}},
				{"FDE",{	aOperator[0].FDE,	aOperator[1].FDE,	aOperator[2].FDE,	aOperator[3].FDE,	}},
				{"AR",{		aOperator[0].AR,	aOperator[1].AR,	aOperator[2].AR,	aOperator[3].AR,	}},
				{"DR",{		aOperator[0].DR,	aOperator[1].DR,	aOperator[2].DR,	aOperator[3].DR,	}},
				{"SR",{		aOperator[0].SR,	aOperator[1].SR,	aOperator[2].SR,	aOperator[3].SR,	}},
				{"RR",{		aOperator[0].RR,	aOperator[1].RR,	aOperator[2].RR,	aOperator[3].RR,	}},
				{"SL",{		aOperator[0].SL,	aOperator[1].SL,	aOperator[2].SL,	aOperator[3].SL,	}},
				{"TL",{		aOperator[0].TL,	aOperator[1].TL,	aOperator[2].TL,	aOperator[3].TL,	}},
				{"KS",{		aOperator[0].KS,	aOperator[1].KS,	aOperator[2].KS,	aOperator[3].KS,	}},
				{"MT",{		aOperator[0].MT,	aOperator[1].MT,	aOperator[2].MT,	aOperator[3].MT,	}},
				{"DT",{		aOperator[0].DT,	aOperator[1].DT,	aOperator[2].DT,	aOperator[3].DT,	}},
				{"SSG",{	aOperator[0].SSG,	aOperator[1].SSG,	aOperator[2].SSG,	aOperator[3].SSG,	}},
				{"SE_FIX",{	aOperator[0].SE_FIX,aOperator[1].SE_FIX,aOperator[2].SE_FIX,aOperator[3].SE_FIX,}},
				{"SE_KT",{	aOperator[0].SE_KT,	aOperator[1].SE_KT,	aOperator[2].SE_KT,	aOperator[3].SE_KT,	}},
				{"SE_FDT",{	aOperator[0].SE_FDT,aOperator[1].SE_FDT,aOperator[2].SE_FDT,aOperator[3].SE_FDT,}},
			}},
		}},
	};
	#endif//]
}



void CIntermediate::from_json(const nlohmann::json& j)
{
	#if false//[
	std::exception_ptr pException;
	try {
		{	// 
			auto Information = j.at("Information");
			auto Application = Information.at("Summary").get<std::string>();
			auto ChipType = Information.at("ChipType").get<std::string>();
		}
		
		{	// 
			auto Meta = j.at("Meta");
			auto Application = Meta.at("Application").get<std::string>();
			auto Version = Meta.at("Version").get<std::string>();
		}
		
		{	// 
			auto Timbre = j.at("Timbre");
			
			{	// 
				auto o = Timbre.at("Control");
				Control.EN = o.at("EN").get<int>();
				Control.FDE = o.at("FDE").get<int>();
				Control.ALG = o.at("ALG").get<int>();
				Control.FB = o.at("FB").get<int>();
				Control.NUM = o.at("NUM").get<int>();
				Control.KML = o.value("KML", 0);
				Control.KMH = o.value("KMH", 128);
				Control.SE = o.at("SE").get<int>();
				Control.KT = o.at("KT").get<int>();
				Control.FDT = o.at("FDT").get<int>();
			}
			
			{	// 
				auto SetOperator = [this](nlohmann::json& Timbre, int i)
				{
					aOperator[i].EN = Timbre.at("EN").at(i).get<int>();
					aOperator[i].FDE = Timbre.at("FDE").at(i).get<int>();
					aOperator[i].AR = Timbre.at("AR").at(i).get<int>();
					aOperator[i].DR = Timbre.at("DR").at(i).get<int>();
					aOperator[i].SR = Timbre.at("SR").at(i).get<int>();
					aOperator[i].RR = Timbre.at("RR").at(i).get<int>();
					aOperator[i].SL = Timbre.at("SL").at(i).get<int>();
					aOperator[i].TL = Timbre.at("TL").at(i).get<int>();
					aOperator[i].KS = Timbre.at("KS").at(i).get<int>();
					aOperator[i].MT = Timbre.at("MT").at(i).get<int>();
					aOperator[i].DT = Timbre.at("DT").at(i).get<int>();
					aOperator[i].SSG = Timbre.at("SSG").at(i).get<int>();
					aOperator[i].SE_FIX = Timbre.at("SE_FIX").at(i).get<int>();
					aOperator[i].SE_KT = Timbre.at("SE_KT").at(i).get<int>();
					aOperator[i].SE_FDT = Timbre.at("SE_FDT").at(i).get<int>();
				};
				
				auto o = Timbre.at("Operators");
				for (int i = 0; i < _countof(aOperator); ++i) SetOperator(o, i);
			}
		}
	}
	catch (...)
	{
		pException = std::current_exception();
	}
	if (pException){
		std::rethrow_exception(pException);
	}
	#endif//]
}



void to_json(nlohmann::json& j, const CIntermediate& r){ r.to_json(j); }
void from_json(const nlohmann::json& j, CIntermediate& r){ r.from_json(j); }