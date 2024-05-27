#pragma once



#include "FmChip.h"
#include "Value.h"
#include "Intermediate.h"



class CTimbre
{
	public:
		virtual ~CTimbre();
		
		CTimbre(int SampleRate);
		
		IValue& GetValue(int x, int y);
	
	private:
		CDummy Dummy;
		
		struct Control
		{
			CValue<1, 0, 1> EN;
			
			CValue<1, 0, 7> ALG;
			CValue<1, 0, 7> FB;
			CValue<3, 0, 999> NUM;
			CValue<3, 0, 128> KML;
			CValue<3, 0, 128> KMH;
			CValue<1, 0, 1> EPR;
			CValue<4, -128, 128> KT;
			CValue<4, -999, 999> FDT;
			
			CValue<2, 0, 15> aRATE[4];
			CValue<1, 4, 8> BIT;
			CValue<1, 4, 8> LEN;
		};
		Control Control;
		
		struct Operator
		{
			CValue<1, 0, 1> EN;
			
			CValue<3, 0, 127> AL;
			CValue<3, 0, 127> DL;
			CValue<3, 0, 127> SL;
			CValue<3, 0, 127> RL;
			CValue<3, 0, 127> TL;
			CValue<1, 1, 8> MT;
		};
		Operator aOperator[4];
		
		std::vector<std::vector<int>> WAVE;
		
		int m_Note;
		bool m_bPlay;
		bool m_bKeyOn;
		int m_EPR;
		int m_BIT;
		int m_LEN;
		
		uint32_t output_rate;
		emulated_time output_step;
		emulated_time output_pos;
		std::unique_ptr<FmChipBase> m_pFmChip;
		
		std::vector<std::vector<int>> m_aWave;
		int m_iWave;
		int m_Rate;
		double m_Read;
		double m_Freq;
	
	private:
		void SubmitSourceBuffer(std::vector<int>& aOutput);
		
		void KeyOn();
		
		std::vector<int> Render(int L1, int L2, int L3, int L4);
		void Render();
	
	public:
		void Play(int Note);
		void Stop();
		
		void OnBufferStart(std::vector<int>& aOutput);
		
		void SetIntermediate(CIntermediate v);
		CIntermediate GetIntermediate();
};
