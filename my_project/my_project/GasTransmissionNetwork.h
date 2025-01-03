#pragma once
#include "Pipeline.h"
#include "CompressorComplex.h"
#include "CheckInput.h"
class GasTransmissionNetwork
{
private:
	Pipeline* pipeline;
	CompressorComplex* cc;
	CheckInput* check;
public:
	GasTransmissionNetwork(CheckInput& check, Pipeline& pipeline, CompressorComplex& cc);
	void join();
};