


#include "pch.h"
#include <cmath>
#include <random>
#include <memory>
#include "Timbre.h"



CTimbre::~CTimbre()
{
}



CTimbre::CTimbre(int SampleRate)
:m_bPlay(false)
,m_bKeyOn(true)
,output_rate(SampleRate)
,output_step(0x100000000ull / output_rate)
,output_pos(0)
,m_pFmChip(std::make_unique<FmChip<ymfm::ym2203>>(output_rate * 72, EChipType::YM2203))
,WAVE(4)
,m_aWave(4)
,m_iWave(0)
,m_Rate(0)
,m_Read(0)
,m_Freq(0)
{
	{	// 
		Control.EN.SetValue(1);
		Control.ALG.SetValue(0);
		Control.FB.SetValue(0);
		Control.KML.SetValue(0);
		Control.KMH.SetValue(128);
		Control.BIT.SetValue(8);
		Control.LEN.SetValue(5);
		m_BIT = Control.BIT.GetValue();
		m_LEN = Control.LEN.GetValue();
		
		Control.aRATE[0].SetValue(0);
		Control.aRATE[1].SetValue(1);
		Control.aRATE[2].SetValue(4);
		Control.aRATE[3].SetValue(4);
		
		for (int i = 0; i < _countof(aOperator); ++i){
			aOperator[i].EN.SetValue(1);
			
			aOperator[i].AL.SetValue(0);
			aOperator[i].DL.SetValue(0);
			aOperator[i].SL.SetValue(0);
			aOperator[i].RL.SetValue(0);
			aOperator[i].MT.SetValue(1);
		}
		
		aOperator[0].TL.SetValue(36);
		aOperator[1].TL.SetValue(36);
		aOperator[2].TL.SetValue(36);
		aOperator[3].TL.SetValue(0);
	}
}



IValue& CTimbre::GetValue(int x, int y)
{
	switch (y){
		case 0:{
			switch (x){
				case 0: return Control.EN;
				case 1: return Control.ALG;
				case 2: return Control.FB;
				case 3: return Control.NUM;
				case 4: return Control.KML;
				case 5: return Control.KMH;
				case 6: break;
				case 7: return Control.KT;
				case 8: return Control.FDT;
			}
			break;
		}
		case 1:
		case 2:
		case 3:
		case 4:
		{
			switch (x){
				case 0: return aOperator[y-1].EN;
				case 1: return aOperator[y-1].AL;
				case 2: return aOperator[y-1].DL;
				case 3: return aOperator[y-1].SL;
				case 4: return aOperator[y-1].RL;
				case 5: return aOperator[y-1].TL;
				case 6: return aOperator[y-1].MT;
			}
			break;
		}
		case 5:{
			switch (x){
				case 1: return Control.aRATE[0];
				case 2: return Control.aRATE[1];
				case 3: return Control.aRATE[2];
				case 4: return Control.aRATE[3];
				case 5: return Control.BIT;
				case 6: return Control.LEN;
			}
			break;
		}
	}
	return Dummy;
}



void CTimbre::OnBufferStart(std::vector<int>& aOutput)
{
	SubmitSourceBuffer(aOutput);
	KeyOn();
}



void CTimbre::SubmitSourceBuffer(std::vector<int>& aOutput)
{
	auto BIT = m_BIT;
	auto LEN = m_LEN;
	
	for (auto& i : aOutput){
		auto Read = (int)std::floor(m_Read);
		if (m_iWave < m_aWave.size() && Read < m_aWave[m_iWave].size()){
			i += m_aWave[m_iWave][Read] << (14-BIT);
			
			m_Read += m_Freq;
			if (m_Read >= (1<<LEN)) m_Read -= (1<<LEN);
		} else {
			i = 0;
		}
	}
	
	if (m_Rate >= 0 && m_Rate-- == 0){
		switch (m_iWave){
			case 0://A
			case 1://D
			{
				m_Rate = Control.aRATE[++m_iWave].GetValue();
				//m_Read = 0;
				break;
			}
			case 2:{//S
				m_Rate = Control.aRATE[m_iWave].GetValue();
				break;
			}
			case 3:{//R
				++m_iWave;
				break;
			}
		}
	}
}



void CTimbre::KeyOn()
{
	if (m_bPlay && !m_bKeyOn){
		m_bKeyOn = true;
	}
}



std::vector<int> CTimbre::Render(int L1, int L2, int L3, int L4)
{
	auto BIT = Control.BIT.GetValue();
	auto LEN = Control.LEN.GetValue();
	
	L1 += aOperator[0].TL.GetValue();
	L2 += aOperator[1].TL.GetValue();
	L3 += aOperator[2].TL.GetValue();
	L4 += aOperator[3].TL.GetValue();
	L1 = (L1 < 127)? L1: 127;
	L2 = (L2 < 127)? L2: 127;
	L3 = (L3 < 127)? L3: 127;
	L4 = (L4 < 127)? L4: 127;
	
	m_pFmChip->reset();
	m_pFmChip->write(0x27, 0);//SE
	m_pFmChip->write(0x32, aOperator[0].MT.GetValue());
	m_pFmChip->write(0x3a, aOperator[1].MT.GetValue());
	m_pFmChip->write(0x36, aOperator[2].MT.GetValue());
	m_pFmChip->write(0x3e, aOperator[3].MT.GetValue());
	m_pFmChip->write(0x42, L1);
	m_pFmChip->write(0x4a, L2);
	m_pFmChip->write(0x46, L3);
	m_pFmChip->write(0x4e, L4);
	m_pFmChip->write(0x52, 31);//AR
	m_pFmChip->write(0x5a, 31);//AR
	m_pFmChip->write(0x56, 31);//AR
	m_pFmChip->write(0x5e, 31);//AR
	m_pFmChip->write(0x62, 0);//DR
	m_pFmChip->write(0x6a, 0);//DR
	m_pFmChip->write(0x66, 0);//DR
	m_pFmChip->write(0x6e, 0);//DR
	m_pFmChip->write(0x72, 0);//SR
	m_pFmChip->write(0x7a, 0);//SR
	m_pFmChip->write(0x76, 0);//SR
	m_pFmChip->write(0x7e, 0);//SR
	m_pFmChip->write(0x82, 0);//SL|RR
	m_pFmChip->write(0x8a, 0);//SL|RR
	m_pFmChip->write(0x86, 0);//SL|RR
	m_pFmChip->write(0x8e, 0);//SL|RR
	m_pFmChip->write(0x92, 0);//SSG
	m_pFmChip->write(0x9a, 0);//SSG
	m_pFmChip->write(0x96, 0);//SSG
	m_pFmChip->write(0x9e, 0);//SSG
	m_pFmChip->write(0xb2, ((Control.FB.GetValue()<<3) | Control.ALG.GetValue()));
	
	{	// 
		auto BlockFNumber = ((6-(LEN-4))<<11) | 0x0400;
		m_pFmChip->write(0xa6, BlockFNumber>>8);
		m_pFmChip->write(0xa2, BlockFNumber&0xff);
	}
	
	if (m_Note >= Control.KML.GetValue() && m_Note <= Control.KMH.GetValue()){
		uint8_t KeyOn = 0;
		KeyOn |= (aOperator[0].EN.GetValue()<<4);
		KeyOn |= (aOperator[1].EN.GetValue()<<5);
		KeyOn |= (aOperator[2].EN.GetValue()<<6);
		KeyOn |= (aOperator[3].EN.GetValue()<<7);
		KeyOn = (Control.EN.GetValue() == 0)? 0: KeyOn;
		m_pFmChip->write(0x28, (KeyOn | 0x02));
	}
	
	int32_t Limit = 0x1fff;
	auto aOverSampling = std::vector<int>(1ULL<<(LEN+1));
	for (auto& i : aOverSampling){
		int32_t outputs[1] = {0};
		m_pFmChip->generate(output_pos, output_step, outputs);
		i = outputs[0];
		i = (i > -Limit)? i: -Limit;
		i = (i <  Limit)? i:  Limit;
		output_pos += output_step;
	}
	
	int iOverSampling = 0;
	auto aOutput = std::vector<int>(1ULL<<LEN);
	for (auto& i : aOutput){
		i = aOverSampling[iOverSampling];
		i >>= (14-BIT);
		iOverSampling += 2;
	}
	
	return aOutput;
}



static const double s_aFreq[]={
//	c       	c+      	d       	d+      	e       	f       	f+      	g       	g+      	a       	a+      	b
	261.65/64,	277.2/64,	293.7/64,	311.1/64,	329.6/64,	349.2/64,	370.0/64,	392.0/64,	415.3/64,	440.0/64,	466.2/64,	493.9/64,	//o-1
	261.65/32,	277.2/32,	293.7/32,	311.1/32,	329.6/32,	349.2/32,	370.0/32,	392.0/32,	415.3/32,	440.0/32,	466.2/32,	493.9/32,	//o0
	261.65/16,	277.2/16,	293.7/16,	311.1/16,	329.6/16,	349.2/16,	370.0/16,	392.0/16,	415.3/16,	440.0/16,	466.2/16,	493.9/16,	//o1
	261.65/8,	277.2/8,	293.7/8,	311.1/8,	329.6/8,	349.2/8,	370.0/8,	392.0/8,	415.3/8,	440.0/8,	466.2/8,	493.9/8,	//o2
	261.65/4,	277.2/4,	293.7/4,	311.1/4,	329.6/4,	349.2/4,	370.0/4,	392.0/4,	415.3/4,	440.0/4,	466.2/4,	493.9/4,	//o3
	261.65/2,	277.2/2,	293.7/2,	311.1/2,	329.6/2,	349.2/2,	370.0/2,	392.0/2,	415.3/2,	440.0/2,	466.2/2,	493.9/2,	//o4
	261.65*1,	277.2*1,	293.7*1,	311.1*1,	329.6*1,	349.2*1,	370.0*1,	392.0*1,	415.3*1,	440.0*1,	466.2*1,	493.9*1,	//o5
	261.65*2,	277.2*2,	293.7*2,	311.1*2,	329.6*2,	349.2*2,	370.0*2,	392.0*2,	415.3*2,	440.0*2,	466.2*2,	493.9*2,	//o6
	261.65*4,	277.2*4,	293.7*4,	311.1*4,	329.6*4,	349.2*4,	370.0*4,	392.0*4,	415.3*4,	440.0*4,	466.2*4,	493.9*4,	//o7
	261.65*8,	277.2*8,	293.7*8,	311.1*8,	329.6*8,	349.2*8,	370.0*8,	392.0*8,	415.3*8,	440.0*8,	466.2*8,	493.9*8,	//o8
	261.65*16,	277.2*16,	293.7*16,	311.1*16,	329.6*16,	349.2*16,	370.0*16,	392.0*16,	415.3*16,	440.0*16,	466.2*16,	493.9*16,	//o9
};



void CTimbre::Render()
{
	WAVE[0] = Render(aOperator[0].AL.GetValue(), aOperator[1].AL.GetValue(), aOperator[2].AL.GetValue(), aOperator[3].AL.GetValue());
	WAVE[1] = Render(aOperator[0].DL.GetValue(), aOperator[1].DL.GetValue(), aOperator[2].DL.GetValue(), aOperator[3].DL.GetValue());
	WAVE[2] = Render(aOperator[0].SL.GetValue(), aOperator[1].SL.GetValue(), aOperator[2].SL.GetValue(), aOperator[3].SL.GetValue());
	WAVE[3] = Render(aOperator[0].RL.GetValue(), aOperator[1].RL.GetValue(), aOperator[2].RL.GetValue(), aOperator[3].RL.GetValue());
};



void CTimbre::Play(int Note)
{
	if (!m_bPlay){
		m_Note = Note;
		
		m_bPlay = true;
		m_bKeyOn = false;
		m_BIT = Control.BIT.GetValue();
		m_LEN = Control.LEN.GetValue();
		
		Render();
		
		{	// 
			Note += Control.KT.GetValue();
			Note = (Note > 0)? Note: 0;
			Note = (Note < std::size(s_aFreq))? Note: std::size(s_aFreq)-1;
			
			m_aWave = WAVE;
			m_iWave = 0;//A
			m_Rate = Control.aRATE[m_iWave].GetValue();
			m_Read = 0;
			m_Freq = (s_aFreq[Note] * (1<<m_LEN)) / 55555.0;
		}
	}
}



void CTimbre::Stop()
{
	if (m_bPlay){
		m_bPlay = false;
		
		m_iWave = 3;//R
		m_Rate = Control.aRATE[m_iWave].GetValue();
		//m_Read = 0;
	}
}



void CTimbre::SetIntermediate(CIntermediate v)
{
	Control.EN.SetValue(v.Control.EN);
	Control.ALG.SetValue(v.Control.ALG);
	Control.FB.SetValue(v.Control.FB);
	Control.NUM.SetValue(v.Control.NUM);
	Control.KML.SetValue(v.Control.KML);
	Control.KMH.SetValue(v.Control.KMH);
	Control.KT.SetValue(v.Control.KT);
	Control.FDT.SetValue(v.Control.FDT);
	
	Control.aRATE[0].SetValue(v.Control.aRATE[0]);
	Control.aRATE[1].SetValue(v.Control.aRATE[1]);
	Control.aRATE[2].SetValue(v.Control.aRATE[2]);
	Control.aRATE[3].SetValue(v.Control.aRATE[3]);
	Control.BIT.SetValue(v.Control.BIT);
	Control.LEN.SetValue(v.Control.LEN);
	
	for (int i = 0; i < _countof(aOperator); ++i){
		aOperator[i].EN.SetValue(v.aOperator[i].EN);
		aOperator[i].AL.SetValue(v.aOperator[i].AL);
		aOperator[i].DL.SetValue(v.aOperator[i].DL);
		aOperator[i].SL.SetValue(v.aOperator[i].SL);
		aOperator[i].RL.SetValue(v.aOperator[i].RL);
		aOperator[i].TL.SetValue(v.aOperator[i].TL);
		aOperator[i].MT.SetValue(v.aOperator[i].MT);
	}
	
	WAVE = v.WAVE;
}



CIntermediate CTimbre::GetIntermediate()
{
	CIntermediate v;
	
	Render();
	
	v.Control.EN = Control.EN.GetValue();
	v.Control.ALG = Control.ALG.GetValue();
	v.Control.FB = Control.FB.GetValue();
	v.Control.NUM = Control.NUM.GetValue();
	v.Control.KML = Control.KML.GetValue();
	v.Control.KMH = Control.KMH.GetValue();
	v.Control.KT = Control.KT.GetValue();
	v.Control.FDT = Control.FDT.GetValue();
	
	v.Control.aRATE[0] = Control.aRATE[0].GetValue();
	v.Control.aRATE[1] = Control.aRATE[1].GetValue();
	v.Control.aRATE[2] = Control.aRATE[2].GetValue();
	v.Control.aRATE[3] = Control.aRATE[3].GetValue();
	v.Control.BIT = Control.BIT.GetValue();
	v.Control.LEN = Control.LEN.GetValue();
	
	for (int i = 0; i < _countof(aOperator); ++i){
		v.aOperator[i].EN = aOperator[i].EN.GetValue();
		v.aOperator[i].AL = aOperator[i].AL.GetValue();
		v.aOperator[i].DL = aOperator[i].DL.GetValue();
		v.aOperator[i].SL = aOperator[i].SL.GetValue();
		v.aOperator[i].RL = aOperator[i].RL.GetValue();
		v.aOperator[i].TL = aOperator[i].TL.GetValue();
		v.aOperator[i].MT = aOperator[i].MT.GetValue();
	}
	
	v.WAVE = WAVE;
	
	return std::move(v);
}
