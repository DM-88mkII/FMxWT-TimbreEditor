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
			int NUM;
			int KML;
			int KMH;
			int KT;
			int FDT;
			
			int aRATE[4];
			int BIT;
			int LEN;
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
		
		std::vector<std::vector<int>> WAVE;
	
	public:
		void to_json(nlohmann::json& j) const;
		void from_json(const nlohmann::json& j);
		
		void ToFormat(CSettingTab::EFormatType EFormatType, CString& Text);
		void FromFormat(CSettingTab::EFormatType EFormatType, const CString& Text);
	
	private:
		void Replace(std::string& source, const std::string& target, const std::string& replace);
		std::vector<std::string> GetLines(const CString& Text);
		std::vector<std::string> GetToken(const std::string& Line, char delim);
		std::string CommentCut(const std::string& Line, const std::string& target);
		std::string Trim(const std::string& Token, const std::string& trim);
		int ToValue(const std::string& Token);
		int ToValueHex(const std::string& Token);
		
		void ToMgsDrv(CString& Text);
		void FromMgsDrv(const CString& Text);
};



void to_json(nlohmann::json& j, const CIntermediate& r);
void from_json(const nlohmann::json& j, CIntermediate& r);
