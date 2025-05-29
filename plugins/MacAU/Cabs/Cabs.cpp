/*
 *	File:		Cabs.cpp
 *	
 *	Version:	1.0
 * 
 *	Created:	3/27/11
 *	
 *	Copyright:  Copyright � 2011 Airwindows, Airwindows uses the MIT license
 * 
 *	Disclaimer:	IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc. ("Apple") in 
 *				consideration of your agreement to the following terms, and your use, installation, modification 
 *				or redistribution of this Apple software constitutes acceptance of these terms.  If you do 
 *				not agree with these terms, please do not use, install, modify or redistribute this Apple 
 *				software.
 *
 *				In consideration of your agreement to abide by the following terms, and subject to these terms, 
 *				Apple grants you a personal, non-exclusive license, under Apple's copyrights in this 
 *				original Apple software (the "Apple Software"), to use, reproduce, modify and redistribute the 
 *				Apple Software, with or without modifications, in source and/or binary forms; provided that if you 
 *				redistribute the Apple Software in its entirety and without modifications, you must retain this 
 *				notice and the following text and disclaimers in all such redistributions of the Apple Software. 
 *				Neither the name, trademarks, service marks or logos of Apple Computer, Inc. may be used to 
 *				endorse or promote products derived from the Apple Software without specific prior written 
 *				permission from Apple.  Except as expressly stated in this notice, no other rights or 
 *				licenses, express or implied, are granted by Apple herein, including but not limited to any 
 *				patent rights that may be infringed by your derivative works or by other works in which the 
 *				Apple Software may be incorporated.
 *
 *				The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO WARRANTIES, EXPRESS OR 
 *				IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY 
 *				AND FITNESS FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE 
 *				OR IN COMBINATION WITH YOUR PRODUCTS.
 *
 *				IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR CONSEQUENTIAL 
 *				DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
 *				OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, 
 *				REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER 
 *				UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN 
 *				IF APPLE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/*=============================================================================
 Cabs.h
 
 =============================================================================*/
#include "Cabs.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

COMPONENT_ENTRY(Cabs)


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Cabs::Cabs
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Cabs::Cabs(AudioUnit component)
: AUEffectBase(component)
{
	CreateElements();
	Globals()->UseIndexedParameters(kNumberOfParameters);
	SetParameter(kParam_One, kDefaultValue_ParamOne );
	SetParameter(kParam_Two, kDefaultValue_ParamTwo );
	SetParameter(kParam_Three, kDefaultValue_ParamThree );
	SetParameter(kParam_Four, kDefaultValue_ParamFour );
	SetParameter(kParam_Five, kDefaultValue_ParamFive );
	SetParameter(kParam_Six, kDefaultValue_ParamSix );
	
#if AU_DEBUG_DISPATCHER
	mDebugDispatcher = new AUDebugDispatcher (this);
#endif
	
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Cabs::GetParameterValueStrings
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult		Cabs::GetParameterValueStrings(AudioUnitScope		inScope,
												   AudioUnitParameterID	inParameterID,
												   CFArrayRef *		outStrings)
{
    if ((inScope == kAudioUnitScope_Global) && (inParameterID == kParam_One)) //ID must be actual name of parameter identifier, not number
	{
		if (outStrings == NULL) return noErr;
		CFStringRef strings [] =
		{
			kMenuItem_HighPowerStack,
			kMenuItem_VintageStack,
			kMenuItem_BoutiqueStack,
			kMenuItem_LargeCombo,
			kMenuItem_SmallCombo,
			kMenuItem_Bass,
		};
		*outStrings = CFArrayCreate (
									 NULL,
									 (const void **) strings,
									 (sizeof (strings) / sizeof (strings [0])),
									 NULL
									 );
		return noErr;
	}
    return kAudioUnitErr_InvalidProperty;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Cabs::GetParameterInfo
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult		Cabs::GetParameterInfo(AudioUnitScope		inScope,
										   AudioUnitParameterID	inParameterID,
										   AudioUnitParameterInfo	&outParameterInfo )
{
	ComponentResult result = noErr;
	
	outParameterInfo.flags = 	kAudioUnitParameterFlag_IsWritable
	|		kAudioUnitParameterFlag_IsReadable;
    
    if (inScope == kAudioUnitScope_Global) {
        switch(inParameterID)
        {
            case kParam_One:
                AUBase::FillInParameterName (outParameterInfo, kParameterOneName, false);
				outParameterInfo.unit = kAudioUnitParameterUnit_Indexed;
                outParameterInfo.minValue = kHighPowerStack;
                outParameterInfo.maxValue = kBass;
                outParameterInfo.defaultValue = kDefaultValue_ParamOne;
                break;
            case kParam_Two:
                AUBase::FillInParameterName (outParameterInfo, kParameterTwoName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = 0.0;
                outParameterInfo.maxValue = 1.0;
                outParameterInfo.defaultValue = kDefaultValue_ParamTwo;
                break;
            case kParam_Three:
                AUBase::FillInParameterName (outParameterInfo, kParameterThreeName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = 0.0;
                outParameterInfo.maxValue = 1.0;
                outParameterInfo.defaultValue = kDefaultValue_ParamThree;
                break;
			case kParam_Four:
                AUBase::FillInParameterName (outParameterInfo, kParameterFourName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = 0.0;
                outParameterInfo.maxValue = 1.0;
                outParameterInfo.defaultValue = kDefaultValue_ParamFour;
                break;
			case kParam_Five:
                AUBase::FillInParameterName (outParameterInfo, kParameterFiveName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = 0.0;
                outParameterInfo.maxValue = 1.0;
                outParameterInfo.defaultValue = kDefaultValue_ParamFive;
                break;
			case kParam_Six:
                AUBase::FillInParameterName (outParameterInfo, kParameterSixName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = 0.0;
                outParameterInfo.maxValue = 1.0;
                outParameterInfo.defaultValue = kDefaultValue_ParamSix;
                break;
			default:
                result = kAudioUnitErr_InvalidParameter;
                break;
		}
	} else {
        result = kAudioUnitErr_InvalidParameter;
    }
    
	
	
	return result;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Cabs::GetPropertyInfo
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult		Cabs::GetPropertyInfo (AudioUnitPropertyID	inID,
										   AudioUnitScope		inScope,
										   AudioUnitElement	inElement,
										   UInt32 &		outDataSize,
										   Boolean &		outWritable)
{
	return AUEffectBase::GetPropertyInfo (inID, inScope, inElement, outDataSize, outWritable);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Cabs::GetProperty
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult		Cabs::GetProperty(	AudioUnitPropertyID inID,
									  AudioUnitScope 		inScope,
									  AudioUnitElement 	inElement,
									  void *			outData )
{
	return AUEffectBase::GetProperty (inID, inScope, inElement, outData);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Cabs::Initialize
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult Cabs::Initialize()
{
    ComponentResult result = AUEffectBase::Initialize();
    if (result == noErr)
        Reset(kAudioUnitScope_Global, 0);
    return result;
}

#pragma mark ____CabsEffectKernel


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Cabs::CabsKernel::Reset()
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void		Cabs::CabsKernel::Reset()
{
	ataLast3Sample = ataLast2Sample = ataLast1Sample = 0.0;
	ataHalfwaySample = ataHalfDrySample = ataHalfDiffSample = 0.0;
	ataA = ataB = ataC = ataDrySample = ataDiffSample = ataPrevDiffSample = 0.0;
	
	for(int count = 0; count < 90; count++) {b[count] = 0;}
	lastSample = 0.0;
	lastHalfSample = 0.0;
	lastPostSample = 0.0;
	lastPostHalfSample = 0.0;
	postPostSample = 0.0;
	for(int count = 0; count < 20; count++) {d[count] = 0;}
	control = 0;
	iirHeadBumpA = 0.0;
	iirHeadBumpB = 0.0;
	iirHalfHeadBumpA = 0.0;
	iirHalfHeadBumpB = 0.0;
	for(int count = 0; count < 6; count++) lastRef[count] = 0.0;

	flip = false;
	ataFlip = false;
	gcount = 0;
	cycle = 0;
	fpd = 1.0; while (fpd < 16386) fpd = rand()*UINT32_MAX;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Cabs::CabsKernel::Process
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void		Cabs::CabsKernel::Process(	const Float32 	*inSourceP,
									  Float32		 	*inDestP,
									  UInt32 			inFramesToProcess,
									  UInt32			inNumChannels,
									  bool			&ioSilence )
{
	UInt32 nSampleFrames = inFramesToProcess;
	const Float32 *sourceP = inSourceP;
	Float32 *destP = inDestP;
	
	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= GetSampleRate();
	int cycleEnd = floor(overallscale);
	if (cycleEnd < 1) cycleEnd = 1;
	if (cycleEnd > 4) cycleEnd = 4;
	//this is going to be 2 for 88.1 or 96k, 3 for silly people, 4 for 176 or 192k
	if (cycle > cycleEnd-1) cycle = cycleEnd-1; //sanity check
	
	int speaker = (int) GetParameter( kParam_One );
	double colorIntensity = pow(GetParameter( kParam_Two ),4);
	double correctboost = 1.0 + (colorIntensity*4);
	double correctdrygain = 1.0 - colorIntensity;
	double threshold = pow((1.0-GetParameter( kParam_Three )),5)+0.021; //room loud is slew
	double rarefaction = cbrt(threshold);
	double postThreshold = sqrt(rarefaction);
	double postRarefaction = cbrt(postThreshold);
	double postTrim = sqrt(postRarefaction);
	double HeadBumpFreq = 0.0298+((1.0-GetParameter( kParam_Four ))/8.0);
	double LowsPad = 0.12 + (HeadBumpFreq*12.0);
	double dcblock = pow(HeadBumpFreq,2) / 8.0;
	double heavy = pow(GetParameter( kParam_Five ),3); //wet of head bump
	double output = pow(GetParameter( kParam_Six ),2);
	double dynamicconv = 5.0;
	dynamicconv *= pow(GetParameter( kParam_Two ),2);
	dynamicconv *= pow(GetParameter( kParam_Three ),2);
	//set constants for sag speed
	int offsetA = 4+((int)(GetParameter( kParam_Four )*5.0));

	while (nSampleFrames-- > 0) {
		double inputSample = *sourceP;
		if (fabs(inputSample)<1.18e-23) inputSample = fpd * 1.18e-17;
		
		cycle++;
		if (cycle == cycleEnd) { //hit the end point and we do a chorus sample
			//everything in here is undersampled, including the dry/wet		
			
			double ataDrySample = inputSample;		
			double ataHalfwaySample = (inputSample + ataLast1Sample + ((-ataLast2Sample + ataLast3Sample) * 0.05)) / 2.0;
			double ataHalfDrySample = ataHalfwaySample;
			ataLast3Sample = ataLast2Sample; ataLast2Sample = ataLast1Sample; ataLast1Sample = inputSample;
			//setting up oversampled special antialiasing
			//pre-center code on inputSample and halfwaySample in parallel
			//begin raw sample- inputSample and ataDrySample handled separately here
			double clamp = inputSample - lastSample;
			if (clamp > threshold) inputSample = lastSample + threshold;
			if (-clamp > rarefaction) inputSample = lastSample - rarefaction;
			lastSample = inputSample;
			//end raw sample
			
			//begin interpolated sample- change inputSample -> ataHalfwaySample, ataDrySample -> ataHalfDrySample
			clamp = ataHalfwaySample - lastHalfSample;
			if (clamp > threshold) ataHalfwaySample = lastHalfSample + threshold;
			if (-clamp > rarefaction) ataHalfwaySample = lastHalfSample - rarefaction;
			lastHalfSample = ataHalfwaySample;
			//end interpolated sample
			
			//begin center code handling conv stuff tied to 44.1K, or stuff in time domain like delays
			ataHalfwaySample -= inputSample;
			//retain only difference with raw signal
			
			if (gcount < 0 || gcount > 10) {gcount = 10;}
			d[gcount+10] = d[gcount] = fabs(inputSample);
			control += (d[gcount] / offsetA);
			control -= (d[gcount+offsetA] / offsetA);
			control -= 0.0001;				
			if (control < 0) {control = 0;}
			if (control > 13) {control = 13;}
			gcount--;
			double applyconv = (control / offsetA) * dynamicconv;
			//now we have a 'sag' style average to apply to the conv
			b[82] = b[81]; b[81] = b[80]; b[80] = b[79]; 
			b[79] = b[78]; b[78] = b[77]; b[77] = b[76]; b[76] = b[75]; b[75] = b[74]; b[74] = b[73]; b[73] = b[72]; b[72] = b[71]; 
			b[71] = b[70]; b[70] = b[69]; b[69] = b[68]; b[68] = b[67]; b[67] = b[66]; b[66] = b[65]; b[65] = b[64]; b[64] = b[63]; 
			b[63] = b[62]; b[62] = b[61]; b[61] = b[60]; b[60] = b[59]; b[59] = b[58]; b[58] = b[57]; b[57] = b[56]; b[56] = b[55]; 
			b[55] = b[54]; b[54] = b[53]; b[53] = b[52]; b[52] = b[51]; b[51] = b[50]; b[50] = b[49]; b[49] = b[48]; b[48] = b[47]; 
			b[47] = b[46]; b[46] = b[45]; b[45] = b[44]; b[44] = b[43]; b[43] = b[42]; b[42] = b[41]; b[41] = b[40]; b[40] = b[39]; 
			b[39] = b[38]; b[38] = b[37]; b[37] = b[36]; b[36] = b[35]; b[35] = b[34]; b[34] = b[33]; b[33] = b[32]; b[32] = b[31]; 
			b[31] = b[30]; b[30] = b[29]; b[29] = b[28]; b[28] = b[27]; b[27] = b[26]; b[26] = b[25]; b[25] = b[24]; b[24] = b[23]; 
			b[23] = b[22]; b[22] = b[21]; b[21] = b[20]; b[20] = b[19]; b[19] = b[18]; b[18] = b[17]; b[17] = b[16]; b[16] = b[15]; 
			b[15] = b[14]; b[14] = b[13]; b[13] = b[12]; b[12] = b[11]; b[11] = b[10]; b[10] = b[9]; b[9] = b[8]; b[8] = b[7]; 
			b[7] = b[6]; b[6] = b[5]; b[5] = b[4]; b[4] = b[3]; b[3] = b[2]; b[2] = b[1]; b[1] = b[0]; b[0] = inputSample;
			//load conv
			
			double tempSample = 0.0; //set up for applying the cab sound
			switch (speaker)
			{
				case 1:
					//begin HighPowerStack conv
					tempSample += (b[1] * (1.29550481610475132  + (0.19713872057074355*applyconv)));
					tempSample += (b[2] * (1.42302569895462616  + (0.30599505521284787*applyconv)));
					tempSample += (b[3] * (1.28728195804197565  + (0.23168333460446133*applyconv)));
					tempSample += (b[4] * (0.88553784290822690  + (0.14263256172918892*applyconv)));
					tempSample += (b[5] * (0.37129054918432319  + (0.00150040944205920*applyconv)));
					tempSample -= (b[6] * (0.12150959412556320  + (0.32776273620569107*applyconv)));
					tempSample -= (b[7] * (0.44900065463203775  + (0.74101214925298819*applyconv)));
					tempSample -= (b[8] * (0.54058781908186482  + (1.07821707459008387*applyconv)));
					tempSample -= (b[9] * (0.49361966401791391  + (1.23540109014850508*applyconv)));
					tempSample -= (b[10] * (0.39819495093078133  + (1.11247213730917749*applyconv)));
					tempSample -= (b[11] * (0.31379279985435521  + (0.80330360359638298*applyconv)));
					tempSample -= (b[12] * (0.30744359242808555  + (0.42132528876858205*applyconv)));
					tempSample -= (b[13] * (0.33943170284673974  + (0.09183418349389982*applyconv)));
					tempSample -= (b[14] * (0.33838775119286391  - (0.06453051658561271*applyconv)));
					tempSample -= (b[15] * (0.30682305697961665  - (0.09549380253249232*applyconv)));
					tempSample -= (b[16] * (0.23408741339295336  - (0.08083404732361277*applyconv)));
					tempSample -= (b[17] * (0.10411746814025019  + (0.00253651281245780*applyconv)));
					tempSample += (b[18] * (0.00133623776084696  - (0.04447267870865820*applyconv)));
					tempSample += (b[19] * (0.02461903992114161  + (0.07530671732655550*applyconv)));
					tempSample += (b[20] * (0.02086715842475373  + (0.22795860236804899*applyconv)));
					tempSample += (b[21] * (0.02761433637100917  + (0.26108320417844094*applyconv)));
					tempSample += (b[22] * (0.04475285369162533  + (0.19160705011061663*applyconv)));
					tempSample += (b[23] * (0.09447338372862381  + (0.03681550508743799*applyconv)));
					tempSample += (b[24] * (0.13445890343722280  - (0.13713036462146147*applyconv)));
					tempSample += (b[25] * (0.13872868945088121  - (0.22401242373298191*applyconv)));
					tempSample += (b[26] * (0.14915650097434549  - (0.26718804981526367*applyconv)));
					tempSample += (b[27] * (0.12766643217091783  - (0.27745664795660430*applyconv)));
					tempSample += (b[28] * (0.03675849788393101  - (0.18338278173550679*applyconv)));
					tempSample -= (b[29] * (0.06307306864232835  + (0.06089480869040766*applyconv)));
					tempSample -= (b[30] * (0.14947389348962944  + (0.04642103054798480*applyconv)));
					tempSample -= (b[31] * (0.25235266566401526  + (0.08423062596460507*applyconv)));
					tempSample -= (b[32] * (0.33496344048679683  + (0.09808328256677995*applyconv)));
					tempSample -= (b[33] * (0.36590030482175445  + (0.10622650888958179*applyconv)));
					tempSample -= (b[34] * (0.35015197011464372  + (0.08982043516016047*applyconv)));
					tempSample -= (b[35] * (0.26808437585665090  + (0.00735561860229533*applyconv)));
					tempSample -= (b[36] * (0.11624318543291220  - (0.07142484314510467*applyconv)));
					tempSample += (b[37] * (0.05617084165377551  + (0.11785854050350089*applyconv)));
					tempSample += (b[38] * (0.20540028692589385  + (0.20479174663329586*applyconv)));
					tempSample += (b[39] * (0.30455415003043818  + (0.29074864580096849*applyconv)));
					tempSample += (b[40] * (0.33810750937829476  + (0.29182307921316802*applyconv)));
					tempSample += (b[41] * (0.31936133365277430  + (0.26535537727394987*applyconv)));
					tempSample += (b[42] * (0.27388548321981876  + (0.19735049990538350*applyconv)));
					tempSample += (b[43] * (0.21454597517994098  + (0.06415909270247236*applyconv)));
					tempSample += (b[44] * (0.15001045817707717  - (0.03831118543404573*applyconv)));
					tempSample += (b[45] * (0.07283437284653138  - (0.09281952429543777*applyconv)));
					tempSample -= (b[46] * (0.03917872184241358  + (0.14306291461398810*applyconv)));
					tempSample -= (b[47] * (0.16695932032148642  + (0.19138995946950504*applyconv)));
					tempSample -= (b[48] * (0.27055854466909462  + (0.22531296466343192*applyconv)));
					tempSample -= (b[49] * (0.33256357307578271  + (0.23305840475692102*applyconv)));
					tempSample -= (b[50] * (0.33459770116834442  + (0.24091822618917569*applyconv)));
					tempSample -= (b[51] * (0.27156687236338090  + (0.24062938573512443*applyconv)));
					tempSample -= (b[52] * (0.17197093288412094  + (0.19083085091993421*applyconv)));
					tempSample -= (b[53] * (0.06738628195910543  + (0.10268609751019808*applyconv)));
					tempSample += (b[54] * (0.00222429218204290  + (0.01439664435720548*applyconv)));
					tempSample += (b[55] * (0.01346992803494091  + (0.15947137113534526*applyconv)));
					tempSample -= (b[56] * (0.02038911881377448  - (0.26763170752416160*applyconv)));
					tempSample -= (b[57] * (0.08233579178189687  - (0.29415931086406055*applyconv)));
					tempSample -= (b[58] * (0.15447855089824883  - (0.26489186990840807*applyconv)));
					tempSample -= (b[59] * (0.20518281113362655  - (0.16135382257522859*applyconv)));
					tempSample -= (b[60] * (0.22244686050232007  + (0.00847180390247432*applyconv)));
					tempSample -= (b[61] * (0.21849243134998034  + (0.14460595245753741*applyconv)));
					tempSample -= (b[62] * (0.20256105734574054  + (0.18932793221831667*applyconv)));
					tempSample -= (b[63] * (0.18604070054295399  + (0.17250665610927965*applyconv)));
					tempSample -= (b[64] * (0.17222844322058231  + (0.12992472027850357*applyconv)));
					tempSample -= (b[65] * (0.14447856616566443  + (0.09089219002147308*applyconv)));
					tempSample -= (b[66] * (0.10385520794251019  + (0.08600465834570559*applyconv)));
					tempSample -= (b[67] * (0.07124435678265063  + (0.09071532210549428*applyconv)));
					tempSample -= (b[68] * (0.05216857461197572  + (0.06794061706070262*applyconv)));
					tempSample -= (b[69] * (0.05235381920184123  + (0.02818101717909346*applyconv)));
					tempSample -= (b[70] * (0.07569701245553526  - (0.00634228544764946*applyconv)));
					tempSample -= (b[71] * (0.10320125382718826  - (0.02751486906644141*applyconv)));
					tempSample -= (b[72] * (0.12122120969079088  - (0.05434007312178933*applyconv)));
					tempSample -= (b[73] * (0.13438969117200902  - (0.09135218559713874*applyconv)));
					tempSample -= (b[74] * (0.13534390437529981  - (0.10437672041458675*applyconv)));
					tempSample -= (b[75] * (0.11424128854188388  - (0.08693450726462598*applyconv)));
					tempSample -= (b[76] * (0.08166894518596159  - (0.06949989431475120*applyconv)));
					tempSample -= (b[77] * (0.04293976378555305  - (0.05718625137421843*applyconv)));
					tempSample += (b[78] * (0.00933076320644409  + (0.01728285211520138*applyconv)));
					tempSample += (b[79] * (0.06450430362918153  - (0.02492994833691022*applyconv)));
					tempSample += (b[80] * (0.10187400687649277  - (0.03578455940532403*applyconv)));
					tempSample += (b[81] * (0.11039763294094571  - (0.03995523517573508*applyconv)));
					tempSample += (b[82] * (0.08557960776024547  - (0.03482514309492527*applyconv)));
					tempSample += (b[83] * (0.02730881850805332  - (0.00514750108411127*applyconv)));
					//end HighPowerStack conv
					break;
				case 2:
					//begin VintageStack conv
					tempSample += (b[1] * (1.31698250313308396  - (0.08140616497621633*applyconv)));
					tempSample += (b[2] * (1.47229016949915326  - (0.27680278993637253*applyconv)));
					tempSample += (b[3] * (1.30410109086044956  - (0.35629113432046489*applyconv)));
					tempSample += (b[4] * (0.81766210474551260  - (0.26808782337659753*applyconv)));
					tempSample += (b[5] * (0.19868872545506663  - (0.11105517193919669*applyconv)));
					tempSample -= (b[6] * (0.39115909132567039  - (0.12630622002682679*applyconv)));
					tempSample -= (b[7] * (0.76881891559343574  - (0.40879849500403143*applyconv)));
					tempSample -= (b[8] * (0.87146861782680340  - (0.59529560488000599*applyconv)));
					tempSample -= (b[9] * (0.79504575932563670  - (0.60877047551611796*applyconv)));
					tempSample -= (b[10] * (0.61653017622406314  - (0.47662851438557335*applyconv)));
					tempSample -= (b[11] * (0.40718195794382067  - (0.24955839378539713*applyconv)));
					tempSample -= (b[12] * (0.31794900040616203  - (0.04169792259600613*applyconv)));
					tempSample -= (b[13] * (0.41075032540217843  + (0.00368483996076280*applyconv)));
					tempSample -= (b[14] * (0.56901352922170667  - (0.11027360805893105*applyconv)));
					tempSample -= (b[15] * (0.62443222391889264  - (0.22198075154245228*applyconv)));
					tempSample -= (b[16] * (0.53462856723129204  - (0.22933544545324852*applyconv)));
					tempSample -= (b[17] * (0.34441703361995046  - (0.12956809502269492*applyconv)));
					tempSample -= (b[18] * (0.13947052337867882  + (0.00339775055962799*applyconv)));
					tempSample += (b[19] * (0.03771252648928484  - (0.10863931549251718*applyconv)));
					tempSample += (b[20] * (0.18280210770271693  - (0.17413646599296417*applyconv)));
					tempSample += (b[21] * (0.24621986701761467  - (0.14547053270435095*applyconv)));
					tempSample += (b[22] * (0.22347075142737360  - (0.02493869490104031*applyconv)));
					tempSample += (b[23] * (0.14346348482123716  + (0.11284054747963246*applyconv)));
					tempSample += (b[24] * (0.00834364862916028  + (0.24284684053733926*applyconv)));
					tempSample -= (b[25] * (0.11559740296078347  - (0.32623054435304538*applyconv)));
					tempSample -= (b[26] * (0.18067604561283060  - (0.32311481551122478*applyconv)));
					tempSample -= (b[27] * (0.22927997789035612  - (0.26991539052832925*applyconv)));
					tempSample -= (b[28] * (0.28487666578669446  - (0.22437227250279349*applyconv)));
					tempSample -= (b[29] * (0.31992973037153838  - (0.15289876100963865*applyconv)));
					tempSample -= (b[30] * (0.35174606303520733  - (0.05656293023086628*applyconv)));
					tempSample -= (b[31] * (0.36894898011375254  + (0.04333925421463558*applyconv)));
					tempSample -= (b[32] * (0.32567576055307507  + (0.14594589410921388*applyconv)));
					tempSample -= (b[33] * (0.27440135050585784  + (0.15529667398122521*applyconv)));
					tempSample -= (b[34] * (0.21998973785078091  + (0.05083553737157104*applyconv)));
					tempSample -= (b[35] * (0.10323624876862457  - (0.04651829594199963*applyconv)));
					tempSample += (b[36] * (0.02091603687851074  + (0.12000046818439322*applyconv)));
					tempSample += (b[37] * (0.11344930914138468  + (0.17697142512225839*applyconv)));
					tempSample += (b[38] * (0.22766779627643968  + (0.13645102964003858*applyconv)));
					tempSample += (b[39] * (0.38378309953638229  - (0.01997653307333791*applyconv)));
					tempSample += (b[40] * (0.52789400804568076  - (0.21409137428422448*applyconv)));
					tempSample += (b[41] * (0.55444630296938280  - (0.32331980931576626*applyconv)));
					tempSample += (b[42] * (0.42333237669264601  - (0.26855847463044280*applyconv)));
					tempSample += (b[43] * (0.21942831522035078  - (0.12051365248820624*applyconv)));
					tempSample -= (b[44] * (0.00584169427830633  - (0.03706970171280329*applyconv)));
					tempSample -= (b[45] * (0.24279799124660351  - (0.17296440491477982*applyconv)));
					tempSample -= (b[46] * (0.40173760787507085  - (0.21717989835163351*applyconv)));
					tempSample -= (b[47] * (0.43930035724188155  - (0.16425928481378199*applyconv)));
					tempSample -= (b[48] * (0.41067765934041811  - (0.10390115786636855*applyconv)));
					tempSample -= (b[49] * (0.34409235547165967  - (0.07268159377411920*applyconv)));
					tempSample -= (b[50] * (0.26542883122568151  - (0.05483457497365785*applyconv)));
					tempSample -= (b[51] * (0.22024754776138800  - (0.06484897950087598*applyconv)));
					tempSample -= (b[52] * (0.20394367993632415  - (0.08746309731952180*applyconv)));
					tempSample -= (b[53] * (0.17565242431124092  - (0.07611309538078760*applyconv)));
					tempSample -= (b[54] * (0.10116623231246825  - (0.00642818706295112*applyconv)));
					tempSample -= (b[55] * (0.00782648272053632  + (0.08004141267685004*applyconv)));
					tempSample += (b[56] * (0.05059046006747323  - (0.12436676387548490*applyconv)));
					tempSample += (b[57] * (0.06241531553254467  - (0.11530779547021434*applyconv)));
					tempSample += (b[58] * (0.04952694587101836  - (0.08340945324333944*applyconv)));
					tempSample += (b[59] * (0.00843873294401687  - (0.03279659052562903*applyconv)));
					tempSample -= (b[60] * (0.05161338949440241  - (0.03428181149163798*applyconv)));
					tempSample -= (b[61] * (0.08165520146902012  - (0.08196746092283110*applyconv)));
					tempSample -= (b[62] * (0.06639532849935320  - (0.09797462781896329*applyconv)));
					tempSample -= (b[63] * (0.02953430910661621  - (0.09175612938515763*applyconv)));
					tempSample += (b[64] * (0.00741058547442938  + (0.05442091048731967*applyconv)));
					tempSample += (b[65] * (0.01832866125391727  + (0.00306243693643687*applyconv)));
					tempSample += (b[66] * (0.00526964230373573  - (0.04364102661136410*applyconv)));
					tempSample -= (b[67] * (0.00300984373848200  + (0.09742737841278880*applyconv)));
					tempSample -= (b[68] * (0.00413616769576694  + (0.14380661694523073*applyconv)));
					tempSample -= (b[69] * (0.00588769034931419  + (0.16012843578892538*applyconv)));
					tempSample -= (b[70] * (0.00688588239450581  + (0.14074464279305798*applyconv)));
					tempSample -= (b[71] * (0.02277307992926315  + (0.07914752191801366*applyconv)));
					tempSample -= (b[72] * (0.04627166091180877  - (0.00192787268067208*applyconv)));
					tempSample -= (b[73] * (0.05562045897455786  - (0.05932868727665747*applyconv)));
					tempSample -= (b[74] * (0.05134243784922165  - (0.08245334798868090*applyconv)));
					tempSample -= (b[75] * (0.04719409472239919  - (0.07498680629253825*applyconv)));
					tempSample -= (b[76] * (0.05889738914266415  - (0.06116127018043697*applyconv)));
					tempSample -= (b[77] * (0.09428363535111127  - (0.06535868867863834*applyconv)));
					tempSample -= (b[78] * (0.15181756953225126  - (0.08982979655234427*applyconv)));
					tempSample -= (b[79] * (0.20878969456036670  - (0.10761070891499538*applyconv)));
					tempSample -= (b[80] * (0.22647885581813790  - (0.08462542510349125*applyconv)));
					tempSample -= (b[81] * (0.19723482443646323  - (0.02665160920736287*applyconv)));
					tempSample -= (b[82] * (0.16441643451155163  + (0.02314691954338197*applyconv)));
					tempSample -= (b[83] * (0.15201914054931515  + (0.04424903493886839*applyconv)));
					tempSample -= (b[84] * (0.15454370641307855  + (0.04223203797913008*applyconv)));
					//end VintageStack conv
					break;
				case 3:
					//begin BoutiqueStack conv
					tempSample += (b[1] * (1.30406584776167445  - (0.01410622186823351*applyconv)));
					tempSample += (b[2] * (1.09350974154373559  + (0.34478044709202327*applyconv)));
					tempSample += (b[3] * (0.52285510059938256  + (0.84225842837363574*applyconv)));
					tempSample -= (b[4] * (0.00018126260714707  - (1.02446537989058117*applyconv)));
					tempSample -= (b[5] * (0.34943699771860115  - (0.84094709567790016*applyconv)));
					tempSample -= (b[6] * (0.53068048407937285  - (0.49231169327705593*applyconv)));
					tempSample -= (b[7] * (0.48631669406792399  - (0.08965111766223610*applyconv)));
					tempSample -= (b[8] * (0.28099201947014130  + (0.23921137841068607*applyconv)));
					tempSample -= (b[9] * (0.10333290012666248  + (0.35058962687321482*applyconv)));
					tempSample -= (b[10] * (0.06605032198166226  + (0.23447405567823365*applyconv)));
					tempSample -= (b[11] * (0.10485808661261729  + (0.05025985449763527*applyconv)));
					tempSample -= (b[12] * (0.13231190973014911  - (0.05484648240248013*applyconv)));
					tempSample -= (b[13] * (0.12926184767180304  - (0.04054223744746116*applyconv)));
					tempSample -= (b[14] * (0.13802696739839460  + (0.01876754906568237*applyconv)));
					tempSample -= (b[15] * (0.16548980700926913  + (0.06772130758771169*applyconv)));
					tempSample -= (b[16] * (0.14469310965751475  + (0.10590928840978781*applyconv)));
					tempSample -= (b[17] * (0.07838457396093310  + (0.13120101199677947*applyconv)));
					tempSample -= (b[18] * (0.05123031606187391  + (0.13883400806512292*applyconv)));
					tempSample -= (b[19] * (0.08906103481939850  + (0.07840461228402337*applyconv)));
					tempSample -= (b[20] * (0.13939265522625241  + (0.01194366471800457*applyconv)));
					tempSample -= (b[21] * (0.14957600717294034  + (0.07687598594361914*applyconv)));
					tempSample -= (b[22] * (0.14112708654047090  + (0.20118461131186977*applyconv)));
					tempSample -= (b[23] * (0.14961020766492997  + (0.30005716443826147*applyconv)));
					tempSample -= (b[24] * (0.16130382224652270  + (0.40459872030013055*applyconv)));
					tempSample -= (b[25] * (0.15679868471080052  + (0.47292767226083465*applyconv)));
					tempSample -= (b[26] * (0.16456530552807727  + (0.45182121471666481*applyconv)));
					tempSample -= (b[27] * (0.16852385701909278  + (0.38272684270752266*applyconv)));
					tempSample -= (b[28] * (0.13317562760966850  + (0.28829580273670768*applyconv)));
					tempSample -= (b[29] * (0.09396196532150952  + (0.18886898332071317*applyconv)));
					tempSample -= (b[30] * (0.10133496956734221  + (0.11158788414137354*applyconv)));
					tempSample -= (b[31] * (0.16097596389376778  + (0.02621299102374547*applyconv)));
					tempSample -= (b[32] * (0.21419006394821866  - (0.03585678078834797*applyconv)));
					tempSample -= (b[33] * (0.21273234570555244  - (0.02574469802924526*applyconv)));
					tempSample -= (b[34] * (0.16934948798707830  + (0.01354331184333835*applyconv)));
					tempSample -= (b[35] * (0.11970436472852493  + (0.04242183865883427*applyconv)));
					tempSample -= (b[36] * (0.09329023656747724  + (0.06890873292358397*applyconv)));
					tempSample -= (b[37] * (0.10255328436608116  + (0.11482972519137427*applyconv)));
					tempSample -= (b[38] * (0.13883223352796811  + (0.18016014431438840*applyconv)));
					tempSample -= (b[39] * (0.16532844286979087  + (0.24521957638633446*applyconv)));
					tempSample -= (b[40] * (0.16254607738965438  + (0.25669472097572482*applyconv)));
					tempSample -= (b[41] * (0.15353207135544752  + (0.15048064682912729*applyconv)));
					tempSample -= (b[42] * (0.13039046390746015  - (0.00200335414623601*applyconv)));
					tempSample -= (b[43] * (0.06707245032180627  - (0.06498125592578702*applyconv)));
					tempSample += (b[44] * (0.01427326441869788  + (0.01940451360783622*applyconv)));
					tempSample += (b[45] * (0.06151238306578224  - (0.07335755969763329*applyconv)));
					tempSample += (b[46] * (0.04685840498892526  - (0.14258849371688248*applyconv)));
					tempSample -= (b[47] * (0.00950136304466093  + (0.14379354707665129*applyconv)));
					tempSample -= (b[48] * (0.06245771575493557  + (0.07639718586346110*applyconv)));
					tempSample -= (b[49] * (0.07159593175777741  - (0.00595536565276915*applyconv)));
					tempSample -= (b[50] * (0.03167929390245019  - (0.03856769526301793*applyconv)));
					tempSample += (b[51] * (0.01890898565110766  + (0.00760539424271147*applyconv)));
					tempSample += (b[52] * (0.04926161137832240  - (0.06411014430053390*applyconv)));
					tempSample += (b[53] * (0.05768814623421683  - (0.15068618173358578*applyconv)));
					tempSample += (b[54] * (0.06144258297076708  - (0.21200636329120301*applyconv)));
					tempSample += (b[55] * (0.06348341960185613  - (0.19620269813094307*applyconv)));
					tempSample += (b[56] * (0.04877736350310589  - (0.11864999881200111*applyconv)));
					tempSample += (b[57] * (0.01010950997574472  - (0.02630070679113791*applyconv)));
					tempSample -= (b[58] * (0.02929178864801191  - (0.04439260202207482*applyconv)));
					tempSample -= (b[59] * (0.03484517126321562  - (0.04508635396034735*applyconv)));
					tempSample -= (b[60] * (0.00547176780437610  - (0.00205637806941426*applyconv)));
					tempSample += (b[61] * (0.02278296865283977  - (0.00063732526427685*applyconv)));
					tempSample += (b[62] * (0.02688982591366477  + (0.05333738901586284*applyconv)));
					tempSample += (b[63] * (0.01942012754957055  + (0.10942832669749143*applyconv)));
					tempSample += (b[64] * (0.01572585258756565  + (0.11189204189054594*applyconv)));
					tempSample += (b[65] * (0.01490550715016034  + (0.04449822818925343*applyconv)));
					tempSample += (b[66] * (0.01715683226376727  - (0.06944648050933899*applyconv)));
					tempSample += (b[67] * (0.02822659878011318  - (0.17843652160132820*applyconv)));
					tempSample += (b[68] * (0.03758307610456144  - (0.21986013433664692*applyconv)));
					tempSample += (b[69] * (0.03275008021608433  - (0.15869878676112170*applyconv)));
					tempSample += (b[70] * (0.01855749786752354  - (0.02337224995718105*applyconv)));
					tempSample += (b[71] * (0.00217095395782931  + (0.10971764224593601*applyconv)));
					tempSample -= (b[72] * (0.01851381451105007  - (0.17214910008793413*applyconv)));
					tempSample -= (b[73] * (0.04722574936345419  - (0.14341588977845254*applyconv)));
					tempSample -= (b[74] * (0.07151540514482006  - (0.04684695724814321*applyconv)));
					tempSample -= (b[75] * (0.06827195484995092  + (0.07022207121861397*applyconv)));
					tempSample -= (b[76] * (0.03290227240464227  + (0.16328400808152735*applyconv)));
					tempSample += (b[77] * (0.01043861198275382  - (0.20184486126076279*applyconv)));
					tempSample += (b[78] * (0.03236563559476477  - (0.17125821306380920*applyconv)));
					tempSample += (b[79] * (0.02040121529932702  - (0.09103660189829657*applyconv)));
					tempSample -= (b[80] * (0.00509649513318102  + (0.01170360991547489*applyconv)));
					tempSample -= (b[81] * (0.01388353426600228  - (0.03588955538451771*applyconv)));
					tempSample -= (b[82] * (0.00523671715033842  - (0.07068798057534148*applyconv)));
					tempSample += (b[83] * (0.00665852487721137  + (0.11666210640054926*applyconv)));
					tempSample += (b[84] * (0.01593540832939290  + (0.15844892856402149*applyconv)));
					tempSample += (b[85] * (0.02080509201836796  + (0.17186274420065850*applyconv)));
					//end BoutiqueStack conv
					break;
				case 4:
					//begin LargeCombo conv
					tempSample += (b[1] * (1.31819680801404560  + (0.00362521700518292*applyconv)));
					tempSample += (b[2] * (1.37738284126127919  + (0.14134596126256205*applyconv)));
					tempSample += (b[3] * (1.09957637225311622  + (0.33199581815501555*applyconv)));
					tempSample += (b[4] * (0.62025358899656258  + (0.37476042042088142*applyconv)));
					tempSample += (b[5] * (0.12926194402137478  + (0.24702655568406759*applyconv)));
					tempSample -= (b[6] * (0.28927985011367602  - (0.13289168298307708*applyconv)));
					tempSample -= (b[7] * (0.56518146339033448  - (0.11026641793526121*applyconv)));
					tempSample -= (b[8] * (0.59843200696815069  - (0.10139909232154271*applyconv)));
					tempSample -= (b[9] * (0.45219971861789204  - (0.13313355255903159*applyconv)));
					tempSample -= (b[10] * (0.32520490032331351  - (0.29009061730364216*applyconv)));
					tempSample -= (b[11] * (0.29773131872442909  - (0.45307495356996669*applyconv)));
					tempSample -= (b[12] * (0.31738895975218867  - (0.43198591958928922*applyconv)));
					tempSample -= (b[13] * (0.33336150604703757  - (0.24240412850274029*applyconv)));
					tempSample -= (b[14] * (0.32461638442042151  - (0.02779297492397464*applyconv)));
					tempSample -= (b[15] * (0.27812829473787770  + (0.15565718905032455*applyconv)));
					tempSample -= (b[16] * (0.19413454458668097  + (0.32087693535188599*applyconv)));
					tempSample -= (b[17] * (0.12378036344480114  + (0.37736575956794161*applyconv)));
					tempSample -= (b[18] * (0.12550494837257106  + (0.25593811142722300*applyconv)));
					tempSample -= (b[19] * (0.17725736033713696  + (0.07708896413593636*applyconv)));
					tempSample -= (b[20] * (0.22023699647700670  - (0.01600371273599124*applyconv)));
					tempSample -= (b[21] * (0.21987645486953747  + (0.00973336938352798*applyconv)));
					tempSample -= (b[22] * (0.15014276479707978  + (0.11602269600138954*applyconv)));
					tempSample -= (b[23] * (0.05176520203073560  + (0.20383164255692698*applyconv)));
					tempSample -= (b[24] * (0.04276687165294867  + (0.17785002166834518*applyconv)));
					tempSample -= (b[25] * (0.15951546388137597  + (0.06748854885822464*applyconv)));
					tempSample -= (b[26] * (0.30211952144352616  - (0.03440494237025149*applyconv)));
					tempSample -= (b[27] * (0.36462803375134506  - (0.05874284362202409*applyconv)));
					tempSample -= (b[28] * (0.32283960219377539  + (0.01189623197958362*applyconv)));
					tempSample -= (b[29] * (0.19245178663350720  + (0.11088858383712991*applyconv)));
					tempSample += (b[30] * (0.00681589563349590  - (0.16314250963457660*applyconv)));
					tempSample += (b[31] * (0.20927798345622584  - (0.16952981620487462*applyconv)));
					tempSample += (b[32] * (0.25638846543430976  - (0.11462562122281153*applyconv)));
					tempSample += (b[33] * (0.04584495673888605  + (0.04669671229804190*applyconv)));
					tempSample -= (b[34] * (0.25221561978187662  - (0.19250758741703761*applyconv)));
					tempSample -= (b[35] * (0.35662801992424953  - (0.12244680002787561*applyconv)));
					tempSample -= (b[36] * (0.21498114329314663  + (0.12152120956991189*applyconv)));
					tempSample += (b[37] * (0.00968605571673376  - (0.30597812512858558*applyconv)));
					tempSample += (b[38] * (0.18029119870614621  - (0.31569386468576782*applyconv)));
					tempSample += (b[39] * (0.22744437185251629  - (0.18028438460422197*applyconv)));
					tempSample += (b[40] * (0.09725687638959078  + (0.05479918522830433*applyconv)));
					tempSample -= (b[41] * (0.17970389267353537  - (0.29222750363124067*applyconv)));
					tempSample -= (b[42] * (0.42371969704763018  - (0.34924957781842314*applyconv)));
					tempSample -= (b[43] * (0.43313266755788055  - (0.11503731970288061*applyconv)));
					tempSample -= (b[44] * (0.22178165627851801  + (0.25002925550036226*applyconv)));
					tempSample -= (b[45] * (0.00410198176852576  + (0.43283281457037676*applyconv)));
					tempSample += (b[46] * (0.09072426344812032  - (0.35318250460706446*applyconv)));
					tempSample += (b[47] * (0.08405839183965140  - (0.16936391987143717*applyconv)));
					tempSample -= (b[48] * (0.01110419756114383  - (0.01247164991313877*applyconv)));
					tempSample -= (b[49] * (0.18593334646855278  - (0.14513260199423966*applyconv)));
					tempSample -= (b[50] * (0.33665010871497486  - (0.14456206192169668*applyconv)));
					tempSample -= (b[51] * (0.32644968491439380  + (0.01594380759082303*applyconv)));
					tempSample -= (b[52] * (0.14855437679485431  + (0.23555511219002742*applyconv)));
					tempSample += (b[53] * (0.05113019250820622  - (0.35556617126595202*applyconv)));
					tempSample += (b[54] * (0.12915754942362243  - (0.28571671825750300*applyconv)));
					tempSample += (b[55] * (0.07406865846069306  - (0.10543886479975995*applyconv)));
					tempSample -= (b[56] * (0.03669573814193980  - (0.03194267657582078*applyconv)));
					tempSample -= (b[57] * (0.13429103278009327  - (0.06145796486786051*applyconv)));
					tempSample -= (b[58] * (0.17884021749974641  - (0.00156626902982124*applyconv)));
					tempSample -= (b[59] * (0.16138212225178239  + (0.09402070836837134*applyconv)));
					tempSample -= (b[60] * (0.10867028245257521  + (0.15407963447815898*applyconv)));
					tempSample -= (b[61] * (0.06312416389213464  + (0.11241095544179526*applyconv)));
					tempSample -= (b[62] * (0.05826376574081994  - (0.03635253545701986*applyconv)));
					tempSample -= (b[63] * (0.07991631148258237  - (0.18041947557579863*applyconv)));
					tempSample -= (b[64] * (0.07777397532506500  - (0.20817156738202205*applyconv)));
					tempSample -= (b[65] * (0.03812528734394271  - (0.13679963125162486*applyconv)));
					tempSample += (b[66] * (0.00204900323943951  + (0.04009000730101046*applyconv)));
					tempSample += (b[67] * (0.01779599498119764  - (0.04218637577942354*applyconv)));
					tempSample += (b[68] * (0.00950301949319113  - (0.07908911305044238*applyconv)));
					tempSample -= (b[69] * (0.04283600714814891  + (0.02716262334097985*applyconv)));
					tempSample -= (b[70] * (0.14478320837041933  - (0.08823515277628832*applyconv)));
					tempSample -= (b[71] * (0.23250267035795688  - (0.15334197814956568*applyconv)));
					tempSample -= (b[72] * (0.22369031446225857  - (0.08550989980799503*applyconv)));
					tempSample -= (b[73] * (0.11142757883989868  + (0.08321482928259660*applyconv)));
					tempSample += (b[74] * (0.02752318631713307  - (0.25252906099212968*applyconv)));
					tempSample += (b[75] * (0.11940028414727490  - (0.34358127205009553*applyconv)));
					tempSample += (b[76] * (0.12702057126698307  - (0.31808560130583663*applyconv)));
					tempSample += (b[77] * (0.03639067777025356  - (0.17970282734717846*applyconv)));
					tempSample -= (b[78] * (0.11389848143835518  + (0.00470616711331971*applyconv)));
					tempSample -= (b[79] * (0.23024072979374310  - (0.09772245468884058*applyconv)));
					tempSample -= (b[80] * (0.24389015061112601  - (0.09600959885615798*applyconv)));
					tempSample -= (b[81] * (0.16680269075295703  - (0.05194978963662898*applyconv)));
					tempSample -= (b[82] * (0.05108041495077725  - (0.01796071525570735*applyconv)));
					tempSample += (b[83] * (0.06489835353859555  - (0.00808013770331126*applyconv)));
					tempSample += (b[84] * (0.15481511440233464  - (0.02674063848284838*applyconv)));
					tempSample += (b[85] * (0.18620867857907253  - (0.01786423699465214*applyconv)));
					tempSample += (b[86] * (0.13879832139055756  + (0.01584446839973597*applyconv)));
					tempSample += (b[87] * (0.04878235109120615  + (0.02962866516075816*applyconv)));
					//end LargeCombo conv
					break;
				case 5:
					//begin SmallCombo conv
					tempSample += (b[1] * (1.42133070619855229  - (0.18270903813104500*applyconv)));
					tempSample += (b[2] * (1.47209686171873821  - (0.27954009590498585*applyconv)));
					tempSample += (b[3] * (1.34648011331265294  - (0.47178343556301960*applyconv)));
					tempSample += (b[4] * (0.82133804036124580  - (0.41060189990353935*applyconv)));
					tempSample += (b[5] * (0.21628057120466901  - (0.26062442734317454*applyconv)));
					tempSample -= (b[6] * (0.30306716082877883  + (0.10067648425439185*applyconv)));
					tempSample -= (b[7] * (0.69484313178531876  - (0.09655574841702286*applyconv)));
					tempSample -= (b[8] * (0.88320822356980833  - (0.26501644327144314*applyconv)));
					tempSample -= (b[9] * (0.81326147029423723  - (0.31115926837054075*applyconv)));
					tempSample -= (b[10] * (0.56728759049069222  - (0.23304233545561287*applyconv)));
					tempSample -= (b[11] * (0.33340326645198737  - (0.12361361388240180*applyconv)));
					tempSample -= (b[12] * (0.20280263733605616  - (0.03531960962500105*applyconv)));
					tempSample -= (b[13] * (0.15864533788751345  + (0.00355160825317868*applyconv)));
					tempSample -= (b[14] * (0.12544767480555119  + (0.01979010423176500*applyconv)));
					tempSample -= (b[15] * (0.06666788902658917  + (0.00188830739903378*applyconv)));
					tempSample += (b[16] * (0.02977793355081072  + (0.02304216615605394*applyconv)));
					tempSample += (b[17] * (0.12821526330916558  + (0.02636238376777800*applyconv)));
					tempSample += (b[18] * (0.19933812710210136  - (0.02932657234709721*applyconv)));
					tempSample += (b[19] * (0.18346460191225772  - (0.12859581955080629*applyconv)));
					tempSample -= (b[20] * (0.00088697526755385  + (0.15855257539277415*applyconv)));
					tempSample -= (b[21] * (0.28904286712096761  + (0.06226286786982616*applyconv)));
					tempSample -= (b[22] * (0.49133546282552537  - (0.06512851581813534*applyconv)));
					tempSample -= (b[23] * (0.52908013030763046  - (0.13606992188523465*applyconv)));
					tempSample -= (b[24] * (0.45897241332311706  - (0.15527194946346906*applyconv)));
					tempSample -= (b[25] * (0.35535938629924352  - (0.13634771941703441*applyconv)));
					tempSample -= (b[26] * (0.26185269405237693  - (0.08736651482771546*applyconv)));
					tempSample -= (b[27] * (0.19997351944186473  - (0.01714565029656306*applyconv)));
					tempSample -= (b[28] * (0.18894054145105646  + (0.04557612705740050*applyconv)));
					tempSample -= (b[29] * (0.24043993691153928  + (0.05267500387081067*applyconv)));
					tempSample -= (b[30] * (0.29191852873822671  + (0.01922151122971644*applyconv)));
					tempSample -= (b[31] * (0.29399783430587761  - (0.02238952856106585*applyconv)));
					tempSample -= (b[32] * (0.26662219155294159  - (0.07760819463416335*applyconv)));
					tempSample -= (b[33] * (0.20881206667122221  - (0.11930017354479640*applyconv)));
					tempSample -= (b[34] * (0.12916658879944876  - (0.11798638949823513*applyconv)));
					tempSample -= (b[35] * (0.07678815166012012  - (0.06826864734598684*applyconv)));
					tempSample -= (b[36] * (0.08568505484529348  - (0.00510459741104792*applyconv)));
					tempSample -= (b[37] * (0.13613615872486634  + (0.02288223583971244*applyconv)));
					tempSample -= (b[38] * (0.17426657494209266  + (0.02723737220296440*applyconv)));
					tempSample -= (b[39] * (0.17343619261009030  + (0.01412920547179825*applyconv)));
					tempSample -= (b[40] * (0.14548368977428555  - (0.02640418940455951*applyconv)));
					tempSample -= (b[41] * (0.10485295885802372  - (0.06334665781931498*applyconv)));
					tempSample -= (b[42] * (0.06632268974717079  - (0.05960343688612868*applyconv)));
					tempSample -= (b[43] * (0.06915692039882040  - (0.03541337869596061*applyconv)));
					tempSample -= (b[44] * (0.11889611687783583  - (0.02250608307287119*applyconv)));
					tempSample -= (b[45] * (0.14598456370320673  + (0.00280345943128246*applyconv)));
					tempSample -= (b[46] * (0.12312084125613143  + (0.04947283933434576*applyconv)));
					tempSample -= (b[47] * (0.11379940289994711  + (0.06590080966570636*applyconv)));
					tempSample -= (b[48] * (0.12963290754003182  + (0.02597647654256477*applyconv)));
					tempSample -= (b[49] * (0.12723837402978638  - (0.04942071966927938*applyconv)));
					tempSample -= (b[50] * (0.09185015882996231  - (0.10420810015956679*applyconv)));
					tempSample -= (b[51] * (0.04011592913036545  - (0.10234174227772008*applyconv)));
					tempSample += (b[52] * (0.00992597785057113  + (0.05674042373836896*applyconv)));
					tempSample += (b[53] * (0.04921452178306781  - (0.00222698867111080*applyconv)));
					tempSample += (b[54] * (0.06096504883783566  - (0.04040426549982253*applyconv)));
					tempSample += (b[55] * (0.04113530718724200  - (0.04190143593049960*applyconv)));
					tempSample += (b[56] * (0.01292699017654650  - (0.01121994018532499*applyconv)));
					tempSample -= (b[57] * (0.00437123132431870  - (0.02482497612289103*applyconv)));
					tempSample -= (b[58] * (0.02090571264211918  - (0.03732746039260295*applyconv)));
					tempSample -= (b[59] * (0.04749751678612051  - (0.02960060937328099*applyconv)));
					tempSample -= (b[60] * (0.07675095194206227  - (0.02241927084099648*applyconv)));
					tempSample -= (b[61] * (0.08879414028581609  - (0.01144281133042115*applyconv)));
					tempSample -= (b[62] * (0.07378854974999530  + (0.02518742701599147*applyconv)));
					tempSample -= (b[63] * (0.04677309194488959  + (0.08984657372223502*applyconv)));
					tempSample -= (b[64] * (0.02911874044176449  + (0.14202665940555093*applyconv)));
					tempSample -= (b[65] * (0.02103564720234969  + (0.14640411976171003*applyconv)));
					tempSample -= (b[66] * (0.01940626429101940  + (0.10867274382865903*applyconv)));
					tempSample -= (b[67] * (0.03965401793931531  + (0.04775225375522835*applyconv)));
					tempSample -= (b[68] * (0.08102486457314527  - (0.03204447425666343*applyconv)));
					tempSample -= (b[69] * (0.11794849372825778  - (0.12755667382696789*applyconv)));
					tempSample -= (b[70] * (0.11946469076758266  - (0.20151394599125422*applyconv)));
					tempSample -= (b[71] * (0.07404630324668053  - (0.21300634351769704*applyconv)));
					tempSample -= (b[72] * (0.00477584437144086  - (0.16864707684978708*applyconv)));
					tempSample += (b[73] * (0.05924822014377220  + (0.09394651445109450*applyconv)));
					tempSample += (b[74] * (0.10060989907457370  + (0.00419196431884887*applyconv)));
					tempSample += (b[75] * (0.10817907203844988  - (0.07459664480796091*applyconv)));
					tempSample += (b[76] * (0.08701102204768002  - (0.11129477437630560*applyconv)));
					tempSample += (b[77] * (0.05673785623180162  - (0.10638640242375266*applyconv)));
					tempSample += (b[78] * (0.02944190197442081  - (0.08499792583420167*applyconv)));
					tempSample += (b[79] * (0.01570145445652971  - (0.06190456843465320*applyconv)));
					tempSample += (b[80] * (0.02770233032476748  - (0.04573713136865480*applyconv)));
					tempSample += (b[81] * (0.05417160459175360  - (0.03965651064634598*applyconv)));
					tempSample += (b[82] * (0.06080831637644498  - (0.02909500789113911*applyconv)));
					//end SmallCombo conv
					break;
				case 6:
					//begin Bass conv
					tempSample += (b[1] * (1.35472031405494242  + (0.00220914099195157*applyconv)));
					tempSample += (b[2] * (1.63534207755253003  - (0.11406232654509685*applyconv)));
					tempSample += (b[3] * (1.82334575691525869  - (0.42647194712964054*applyconv)));
					tempSample += (b[4] * (1.86156386235405868  - (0.76744187887586590*applyconv)));
					tempSample += (b[5] * (1.67332739338852599  - (0.95161997324293013*applyconv)));
					tempSample += (b[6] * (1.25054130794899021  - (0.98410433514572859*applyconv)));
					tempSample += (b[7] * (0.70049121047281737  - (0.87375612110718992*applyconv)));
					tempSample += (b[8] * (0.15291791448081560  - (0.61195266024519046*applyconv)));
					tempSample -= (b[9] * (0.37301992914152693  + (0.16755422915252094*applyconv)));
					tempSample -= (b[10] * (0.76568539228498433  - (0.28554435228965386*applyconv)));
					tempSample -= (b[11] * (0.95726568749937369  - (0.61659719162806048*applyconv)));
					tempSample -= (b[12] * (1.01273552193911032  - (0.81827288407943954*applyconv)));
					tempSample -= (b[13] * (0.93920108117234447  - (0.80077111864205874*applyconv)));
					tempSample -= (b[14] * (0.79831898832953974  - (0.65814750339694406*applyconv)));
					tempSample -= (b[15] * (0.64200088100452313  - (0.46135833001232618*applyconv)));
					tempSample -= (b[16] * (0.48807302802822128  - (0.15506178974799034*applyconv)));
					tempSample -= (b[17] * (0.36545171501947982  + (0.16126103769376721*applyconv)));
					tempSample -= (b[18] * (0.31469581455759105  + (0.32250870039053953*applyconv)));
					tempSample -= (b[19] * (0.36893534817945800  + (0.25409418897237473*applyconv)));
					tempSample -= (b[20] * (0.41092557722975687  + (0.13114730488878301*applyconv)));
					tempSample -= (b[21] * (0.38584044480710594  + (0.06825323739722661*applyconv)));
					tempSample -= (b[22] * (0.33378434007178670  + (0.04144255489164217*applyconv)));
					tempSample -= (b[23] * (0.26144203061699706  + (0.06031313105098152*applyconv)));
					tempSample -= (b[24] * (0.25818342000920502  + (0.03642289242586355*applyconv)));
					tempSample -= (b[25] * (0.28096018498822661  + (0.00976973667327174*applyconv)));
					tempSample -= (b[26] * (0.25845682019095384  + (0.02749015358080831*applyconv)));
					tempSample -= (b[27] * (0.26655607865953096  - (0.00329839675455690*applyconv)));
					tempSample -= (b[28] * (0.30590085026938518  - (0.07375043215328811*applyconv)));
					tempSample -= (b[29] * (0.32875683916470899  - (0.12454134857516502*applyconv)));
					tempSample -= (b[30] * (0.38166643180506560  - (0.19973911428609989*applyconv)));
					tempSample -= (b[31] * (0.49068186937289598  - (0.34785166842136384*applyconv)));
					tempSample -= (b[32] * (0.60274753867622777  - (0.48685038872711034*applyconv)));
					tempSample -= (b[33] * (0.65944678627090636  - (0.49844657885975518*applyconv)));
					tempSample -= (b[34] * (0.64488955808717285  - (0.40514406499806987*applyconv)));
					tempSample -= (b[35] * (0.55818730353434354  - (0.28029870614987346*applyconv)));
					tempSample -= (b[36] * (0.43110859113387556  - (0.15373504582939335*applyconv)));
					tempSample -= (b[37] * (0.37726894966096269  - (0.11570983506028532*applyconv)));
					tempSample -= (b[38] * (0.39953242355200935  - (0.17879231130484088*applyconv)));
					tempSample -= (b[39] * (0.36726676379100875  - (0.22013553023983223*applyconv)));
					tempSample -= (b[40] * (0.27187029469227386  - (0.18461171768478427*applyconv)));
					tempSample -= (b[41] * (0.21109334552321635  - (0.14497481318083569*applyconv)));
					tempSample -= (b[42] * (0.19808797405293213  - (0.14916579928186940*applyconv)));
					tempSample -= (b[43] * (0.16287926785495671  - (0.15146098461120627*applyconv)));
					tempSample -= (b[44] * (0.11086621477163359  - (0.13182973443924018*applyconv)));
					tempSample -= (b[45] * (0.07531043236890560  - (0.08062172796472888*applyconv)));
					tempSample -= (b[46] * (0.01747364473230771  + (0.02201865873632456*applyconv)));
					tempSample += (b[47] * (0.03080279125662693  - (0.08721756240972101*applyconv)));
					tempSample += (b[48] * (0.02354148659185142  - (0.06376361763053796*applyconv)));
					tempSample -= (b[49] * (0.02835772372098715  + (0.00589978513642627*applyconv)));
					tempSample -= (b[50] * (0.08983370744565244  - (0.02350960427706536*applyconv)));
					tempSample -= (b[51] * (0.14148947620055380  - (0.03329826628693369*applyconv)));
					tempSample -= (b[52] * (0.17576502674572581  - (0.06507546651241880*applyconv)));
					tempSample -= (b[53] * (0.17168865666573860  - (0.07734801128437317*applyconv)));
					tempSample -= (b[54] * (0.14107027738292105  - (0.03136459344220402*applyconv)));
					tempSample -= (b[55] * (0.12287163395380074  + (0.01933408169185258*applyconv)));
					tempSample -= (b[56] * (0.12276622398112971  + (0.01983508766241737*applyconv)));
					tempSample -= (b[57] * (0.12349721440213673  - (0.01111031415304768*applyconv)));
					tempSample -= (b[58] * (0.08649454142716655  + (0.02252815645513927*applyconv)));
					tempSample -= (b[59] * (0.00953083685474757  + (0.13778878548343007*applyconv)));
					tempSample += (b[60] * (0.06045983158868478  - (0.23966318224935096*applyconv)));
					tempSample += (b[61] * (0.09053229817093242  - (0.27190119941572544*applyconv)));
					tempSample += (b[62] * (0.08112662178843048  - (0.22456862606452327*applyconv)));
					tempSample += (b[63] * (0.07503525686243730  - (0.14330154410548213*applyconv)));
					tempSample += (b[64] * (0.07372595404399729  - (0.06185193766408734*applyconv)));
					tempSample += (b[65] * (0.06073789200080433  + (0.01261857435786178*applyconv)));
					tempSample += (b[66] * (0.04616712695742254  + (0.05851771967084609*applyconv)));
					tempSample += (b[67] * (0.01036235510345900  + (0.08286534414423796*applyconv)));
					tempSample -= (b[68] * (0.03708389413229191  - (0.06695282381039531*applyconv)));
					tempSample -= (b[69] * (0.07092204876981217  - (0.01915829199112784*applyconv)));
					tempSample -= (b[70] * (0.09443579589460312  + (0.01210082455316246*applyconv)));
					tempSample -= (b[71] * (0.07824038577769601  + (0.06121988546065113*applyconv)));
					tempSample -= (b[72] * (0.00854730633079399  + (0.14468518752295506*applyconv)));
					tempSample += (b[73] * (0.06845589924191028  - (0.18902431382592944*applyconv)));
					tempSample += (b[74] * (0.10351569998375465  - (0.13204443060279647*applyconv)));
					tempSample += (b[75] * (0.10513368758532179  - (0.02993199294485649*applyconv)));
					tempSample += (b[76] * (0.08896978950235003  + (0.04074499273825906*applyconv)));
					tempSample += (b[77] * (0.03697537734050980  + (0.09217751130846838*applyconv)));
					tempSample -= (b[78] * (0.04014322441280276  - (0.14062297149365666*applyconv)));
					tempSample -= (b[79] * (0.10505934581398618  - (0.16988861157275814*applyconv)));
					tempSample -= (b[80] * (0.13937661651676272  - (0.15083294570551492*applyconv)));
					tempSample -= (b[81] * (0.13183458845108439  - (0.06657454442471208*applyconv)));
					//end Bass conv
					break;
			}
			inputSample *= correctdrygain;
			inputSample += (tempSample*colorIntensity);
			inputSample /= correctboost;
			ataHalfwaySample += inputSample;
			//restore interpolated signal including time domain stuff now
			//end center code for handling timedomain/conv stuff
			
			//second wave of Cabs style slew clamping
			clamp = inputSample - lastPostSample;
			if (clamp > threshold) inputSample = lastPostSample + threshold;
			if (-clamp > rarefaction) inputSample = lastPostSample - rarefaction;
			lastPostSample = inputSample;
			//end raw sample
			
			//begin interpolated sample- change inputSample -> ataHalfwaySample, ataDrySample -> ataHalfDrySample
			clamp = ataHalfwaySample - lastPostHalfSample;
			if (clamp > threshold) ataHalfwaySample = lastPostHalfSample + threshold;
			if (-clamp > rarefaction) ataHalfwaySample = lastPostHalfSample - rarefaction;
			lastPostHalfSample = ataHalfwaySample;
			//end interpolated sample
			
			//post-center code on inputSample and halfwaySample in parallel
			//begin raw sample- inputSample and ataDrySample handled separately here
			double HeadBump;
			if (flip)
			{
				iirHeadBumpA += (inputSample * HeadBumpFreq);
				iirHeadBumpA -= (iirHeadBumpA * iirHeadBumpA * iirHeadBumpA * HeadBumpFreq);
				if (iirHeadBumpA > 0) iirHeadBumpA -= dcblock;
				if (iirHeadBumpA < 0) iirHeadBumpA += dcblock;
				if (fabs(iirHeadBumpA) > 100.0)
				{iirHeadBumpA = 0.0; iirHeadBumpB = 0.0; iirHalfHeadBumpA = 0.0; iirHalfHeadBumpB = 0.0;}
				HeadBump = iirHeadBumpA;
			}
			else
			{
				iirHeadBumpB += (inputSample * HeadBumpFreq);
				iirHeadBumpB -= (iirHeadBumpB * iirHeadBumpB * iirHeadBumpB * HeadBumpFreq);
				if (iirHeadBumpB > 0) iirHeadBumpB -= dcblock;
				if (iirHeadBumpB < 0) iirHeadBumpB += dcblock;
				if (fabs(iirHeadBumpB) > 100.0)
				{iirHeadBumpA = 0.0; iirHeadBumpB = 0.0; iirHalfHeadBumpA = 0.0; iirHalfHeadBumpB = 0.0;}
				HeadBump = iirHeadBumpB;
			}
			HeadBump /= LowsPad;
			inputSample = (inputSample * (1.0-heavy)) + (HeadBump * heavy);
			//end raw sample
			
			//begin interpolated sample- change inputSample -> ataHalfwaySample, ataDrySample -> ataHalfDrySample
			if (flip)
			{
				iirHalfHeadBumpA += (ataHalfwaySample * HeadBumpFreq);
				iirHalfHeadBumpA -= (iirHalfHeadBumpA * iirHalfHeadBumpA * iirHalfHeadBumpA * HeadBumpFreq);
				if (iirHalfHeadBumpA > 0) iirHalfHeadBumpA -= dcblock;
				if (iirHalfHeadBumpA < 0) iirHalfHeadBumpA += dcblock;
				if (fabs(iirHalfHeadBumpA) > 100.0)
				{iirHeadBumpA = 0.0; iirHeadBumpB = 0.0; iirHalfHeadBumpA = 0.0; iirHalfHeadBumpB = 0.0;}
				HeadBump = iirHalfHeadBumpA;
			}
			else
			{
				iirHalfHeadBumpB += (ataHalfwaySample * HeadBumpFreq);
				iirHalfHeadBumpB -= (iirHalfHeadBumpB * iirHalfHeadBumpB * iirHalfHeadBumpB * HeadBumpFreq);
				if (iirHalfHeadBumpB > 0) iirHalfHeadBumpB -= dcblock;
				if (iirHalfHeadBumpB < 0) iirHalfHeadBumpB += dcblock;
				if (fabs(iirHalfHeadBumpB) > 100.0)
				{iirHeadBumpA = 0.0; iirHeadBumpB = 0.0; iirHalfHeadBumpA = 0.0; iirHalfHeadBumpB = 0.0;}
				HeadBump = iirHalfHeadBumpB;
			}
			HeadBump /= LowsPad;
			ataHalfwaySample = (ataHalfwaySample * (1.0-heavy)) + (HeadBump * heavy);
			//end interpolated sample
						
			//begin antialiasing section for halfway sample
			ataC = ataHalfwaySample - ataHalfDrySample;
			if (flip) {ataA *= 0.94; ataB *= 0.94; ataA += ataC; ataB -= ataC; ataC = ataA;}
			else {ataB *= 0.94; ataA *= 0.94; ataB += ataC; ataA -= ataC; ataC = ataB;}
			ataHalfDiffSample = (ataC * 0.94);
			//end antialiasing section for halfway sample
			
			//begin antialiasing section for raw sample
			ataC = inputSample - ataDrySample;
			if (flip) {ataA *= 0.94; ataB *= 0.94; ataA += ataC; ataB -= ataC; ataC = ataA;}
			else {ataB *= 0.94; ataA *= 0.94; ataB += ataC; ataA -= ataC; ataC = ataB;}
			ataDiffSample = (ataC * 0.94);
			//end antialiasing section for input sample
			flip = !flip;
			
			inputSample = ataDrySample; inputSample += ((ataDiffSample + ataHalfDiffSample + ataPrevDiffSample) / 1.0);
			ataPrevDiffSample = ataDiffSample / 2.0;
			//apply processing as difference to non-oversampled raw input
			
			clamp = inputSample - postPostSample;
			if (clamp > postThreshold) inputSample = postPostSample + postThreshold;
			if (-clamp > postRarefaction) inputSample = postPostSample - postRarefaction;
			postPostSample = inputSample;
			inputSample /= postTrim;
			
			inputSample *= output;
			
			if (cycleEnd == 4) {
				lastRef[0] = lastRef[4]; //start from previous last
				lastRef[2] = (lastRef[0] + inputSample)/2; //half
				lastRef[1] = (lastRef[0] + lastRef[2])/2; //one quarter
				lastRef[3] = (lastRef[2] + inputSample)/2; //three quarters
				lastRef[4] = inputSample; //full
			}
			if (cycleEnd == 3) {
				lastRef[0] = lastRef[3]; //start from previous last
				lastRef[2] = (lastRef[0]+lastRef[0]+inputSample)/3; //third
				lastRef[1] = (lastRef[0]+inputSample+inputSample)/3; //two thirds
				lastRef[3] = inputSample; //full
			}
			if (cycleEnd == 2) {
				lastRef[0] = lastRef[2]; //start from previous last
				lastRef[1] = (lastRef[0] + inputSample)/2; //half
				lastRef[2] = inputSample; //full
			}
			if (cycleEnd == 1) {
				lastRef[0] = inputSample;
			}
			cycle = 0; //reset
			inputSample = lastRef[cycle];
		} else {
			inputSample = lastRef[cycle];
			//we are going through our references now
		}
		
		//begin 32 bit stereo floating point dither
		int expon; frexpf((float)inputSample, &expon);
		fpd ^= fpd << 13; fpd ^= fpd >> 17; fpd ^= fpd << 5;
		inputSample += ((double(fpd)-uint32_t(0x7fffffff)) * 5.5e-36l * pow(2,expon+62));
		//end 32 bit stereo floating point dither
		*destP = inputSample;
		
		sourceP += inNumChannels; destP += inNumChannels;
	}
}

