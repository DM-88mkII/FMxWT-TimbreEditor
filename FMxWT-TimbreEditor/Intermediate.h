#pragma once



#include "SettingTab.h"



struct CIntermediate
{
	public:
		virtual ~CIntermediate() = default;
		
		CIntermediate();
	
	public:
		struct Control
		{
			int EN;
			
			int ALG;
			int FB;
			
			int KML;
			int KMH;
			
			int KT;
			int FDT;
			
			
			int aRATE[4];
		};
		Control Control;
		
		struct Operator
		{
			int EN;
			
			int AL;
			int DL;
			int SL;
			int RL;
			int TL;
			int MT;
		};
		Operator aOperator[4];
	
	public:
		void to_json(nlohmann::json& j) const;
		void from_json(const nlohmann::json& j);
};



void to_json(nlohmann::json& j, const CIntermediate& r);
void from_json(const nlohmann::json& j, CIntermediate& r);
