


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
	j = nlohmann::json{
		{"Information",{
			{"Summary",		"Timbre for WaveTable",	},
			{"ChipType",	"WaveTable",	},
		}},
		{"Meta",{
			{"Application",	"FMxWT-TimbreEditor",	},
			{"Version",		"0.0.0",	},
		}},
		{"Timbre",{
			{"Control",{
				{"EN",		Control.EN,	},
				{"ALG",		Control.ALG,},
				{"FB",		Control.FB,	},
				{"NUM",		Control.NUM,},
				{"KML",		Control.KML,},
				{"KMH",		Control.KMH,},
				{"KT",		Control.KT,	},
				{"FDT",		Control.FDT,},
				{"AR",		Control.aRATE[0],},
				{"DR",		Control.aRATE[1],},
				{"SR",		Control.aRATE[2],},
				{"RR",		Control.aRATE[3],},
				{"BIT",		Control.BIT,},
				{"LEN",		Control.LEN,},
			}},
			{"Operators",{
				{"EN",{		aOperator[0].EN,	aOperator[1].EN,	aOperator[2].EN,	aOperator[3].EN,	}},
				{"AL",{		aOperator[0].AL,	aOperator[1].AL,	aOperator[2].AL,	aOperator[3].AL,	}},
				{"DL",{		aOperator[0].DL,	aOperator[1].DL,	aOperator[2].DL,	aOperator[3].DL,	}},
				{"SL",{		aOperator[0].SL,	aOperator[1].SL,	aOperator[2].SL,	aOperator[3].SL,	}},
				{"RL",{		aOperator[0].RL,	aOperator[1].RL,	aOperator[2].RL,	aOperator[3].RL,	}},
				{"TL",{		aOperator[0].TL,	aOperator[1].TL,	aOperator[2].TL,	aOperator[3].TL,	}},
				{"MT",{		aOperator[0].MT,	aOperator[1].MT,	aOperator[2].MT,	aOperator[3].MT,	}},
			}},
		}},
	};
}



void CIntermediate::from_json(const nlohmann::json& j)
{
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
				Control.ALG = o.at("ALG").get<int>();
				Control.FB = o.at("FB").get<int>();
				Control.NUM = o.at("NUM").get<int>();
				Control.KML = o.value("KML", 0);
				Control.KMH = o.value("KMH", 128);
				Control.KT = o.at("KT").get<int>();
				Control.FDT = o.at("FDT").get<int>();
				Control.aRATE[0] = o.at("AR").get<int>();
				Control.aRATE[1] = o.at("DR").get<int>();
				Control.aRATE[2] = o.at("SR").get<int>();
				Control.aRATE[3] = o.at("RR").get<int>();
				Control.BIT = o.at("BIT").get<int>();
				Control.LEN = o.at("LEN").get<int>();
			}
			
			{	// 
				auto SetOperator = [this](nlohmann::json& Timbre, int i)
				{
					aOperator[i].EN = Timbre.at("EN").at(i).get<int>();
					aOperator[i].AL = Timbre.at("AL").at(i).get<int>();
					aOperator[i].DL = Timbre.at("DL").at(i).get<int>();
					aOperator[i].SL = Timbre.at("SL").at(i).get<int>();
					aOperator[i].RL = Timbre.at("RL").at(i).get<int>();
					aOperator[i].TL = Timbre.at("TL").at(i).get<int>();
					aOperator[i].MT = Timbre.at("MT").at(i).get<int>();
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
}



void to_json(nlohmann::json& j, const CIntermediate& r){ r.to_json(j); }
void from_json(const nlohmann::json& j, CIntermediate& r){ r.from_json(j); }



void CIntermediate::ToFormat(CSettingTab::EFormatType EFormatType, CString& Text)
{
	switch (EFormatType){
		case CSettingTab::EFormatType::MgsDrv:{		ToMgsDrv(Text);			break;	}
	}
}



void CIntermediate::FromFormat(CSettingTab::EFormatType EFormatType, const CString& Text)
{
	switch (EFormatType){
		case CSettingTab::EFormatType::MgsDrv:{		FromMgsDrv(Text);		break;	}
	}
}



void CIntermediate::Replace(std::string& source, const std::string& target, const std::string& replace)
{
	while (true){
		size_t p = 0;
		size_t o = 0;
		size_t n = target.length();
		int c = 0;
		while ((p = source.find(target, o)) != std::string::npos){
			source.replace(p, n, replace);
			o = p + replace.length();
			++c;
		}
		if (c == 0) break;
	}
}


std::vector<std::string> CIntermediate::GetLines(const CString& Text)
{
	std::string s = CStringA(Text).GetBuffer();
	Replace(s, "\r\n", "\n");
	
	std::stringstream ss(s);
	std::string Line;
	std::vector<std::string> Lines;
	while (std::getline(ss, Line, '\n')) Lines.push_back(Line);
	return Lines;
}



std::vector<std::string> CIntermediate::GetToken(const std::string& Line, char delim)
{
	std::stringstream ss(Line);
	std::string Token;
	std::vector<std::string> Tokens;
	while (std::getline(ss, Token, delim)) Tokens.push_back(Token);
	return Tokens;
}



std::string CIntermediate::CommentCut(const std::string& Line, const std::string& target)
{
	auto First = Line.find(target);
	if (First != std::string::npos){
		return Line.substr(0, First);
	} else {
		return Line;
	}
}



std::string CIntermediate::Trim(const std::string& Token, const std::string& trim)
{
	std::string Result;
	auto First = Token.find_first_not_of(trim);
	if (First != std::string::npos){
		auto Last = Token.find_last_not_of(trim);
		Result = Token.substr(First, Last - First + 1);
	}
	return Result;
}



int CIntermediate::ToValue(const std::string& Token)
{
	auto Value = Trim(Token, " ");
	return (Value.empty() || (Value.find_first_of("0123456789") == std::string::npos))? 0: std::stoi(Value);
}



int CIntermediate::ToValueHex(const std::string& Token)
{
	auto Value = Trim(Token, " ");
	return (Value.empty() || (Value.find_first_of("0123456789abcdefABCDEF") == std::string::npos))? 0: std::stoi(Value, nullptr, 16);
}



void CIntermediate::ToMgsDrv(CString& Text)
{
	if (Control.BIT == 8 && Control.LEN == 5){
		int NUM = Control.NUM;
		
		std::string s;
		for (auto& w : WAVE){
			s += std::format("@s{:02}", NUM++);
			s += " = {";
			int n = 0;
			for (auto& v : w){
				s += std::format("{:02x}", (unsigned char)v);
				s += (++n == 16)? " ": "";
			}
			s += "}\n";
		}
		Text = s.c_str();
	}
}



void CIntermediate::FromMgsDrv(const CString& Text)
{
	throw std::runtime_error("Format Error");
}
