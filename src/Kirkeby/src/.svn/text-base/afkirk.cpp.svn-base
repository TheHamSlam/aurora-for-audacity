/**********************************************************************

  Aurora for Audacity: A Powerful multiplatform Acoustic calculations 
                       plugin collection
                       
  Invert Kirkeby

  afkirk.cpp

  Angelo Farina - Simone Campanini

*******************************************************************//**

\class AFKirkeby
\brief The main Kirkeby class

  Bla bla bla

*//*******************************************************************/

#include "afkirk.h"


void AFKirkeby::InitVectors()
{
    // When this private function is called, input vectors
    // should be already instantiated, but output vectors 
    // should't...

    switch(m_nFilterType)
    {
        case IK_MONO:
            m_smpcColLength = m_smpcRowLength / m_nCols;
            
            m_aaHf.Create(1, 1, 1 + m_smpcColLength/2);
            m_aaHt.Create(m_nRows, m_nCols, m_smpcColLength);
            break;
            
        case IK_STEREO:
            // Here we've to do a fake: HRL and HRR are obtained
            // by swapping the input IRs, so from 2 IRs, we
            // make 4. For this reason while m_nCols value is 1
            // we have in fact 2 columns...
            m_smpcColLength = m_smpcRowLength;
            
            m_aaHf.Create(m_nRows, 2, 1 + m_smpcColLength/2);
            m_aaHt.Create(m_nRows, 2, m_smpcColLength);
            break;
            
        case IK_DIPOLE:
            m_nCols = 2;
        case IK_MATRIX:
            m_smpcColLength = m_smpcRowLength / m_nCols;
            
            m_aaHf.Create(m_nRows, m_nCols, 1 + m_smpcColLength/2);
            m_aaHt.Create(m_nRows, m_nCols, m_smpcColLength);
            break;
    }
    

}

void AFKirkeby::DeleteVectors()
{
    // TODO should be removed...
}

void AFKirkeby::InitFft()
{
    //Prepare fft plans
    m_fftForwardPlan  = PLAN_DFT_R2C(m_smpcColLength, m_aaHt.GetData(0,0), m_aaHf.GetData(0,0), FFTW_ESTIMATE);
    m_fftBackwardPlan = PLAN_DFT_C2R(m_smpcColLength, m_aaHf.GetData(0,0), m_aaHt.GetData(0,0), FFTW_ESTIMATE);
    m_bFftPlansExist = true;
}

void AFKirkeby::DeleteFft()
{
    if(m_bFftPlansExist)
    {
        DESTROY_DFT_PLAN(m_fftForwardPlan);
        DESTROY_DFT_PLAN(m_fftBackwardPlan);
        m_bFftPlansExist = false;
    }    
}

void AFKirkeby::FFT(FreqVector_t& Xf, TimeVector_t& Xt)
{
    EXEC_DFT_R2C(m_fftForwardPlan, Xt.GetData(), Xf.GetData());
}

void AFKirkeby::IFFT(TimeVector_t& Xt, FreqVector_t& Xf)
{
    EXEC_DFT_C2R(m_fftBackwardPlan, Xf.GetData(), Xt.GetData());
    Xt /= AFSample(m_smpcColLength); // Normalization step.
}
      

   
void AFKirkeby::ApplyGain()
{
   //if(m_bAutorange) m_dbGain = 1/fabs(FindMax());
   int nCol, nRow;
    for(nRow = 0; nRow < m_nRows; nRow++)
        for(nCol = 0; nCol < m_nCols; nCol++)
            m_aaHt.Item(nRow, nCol) *= AFSample(m_dbGain);
}

// --------------------------------------------- Farina's

void AFKirkeby::MovingAverage(FreqVector_t& Hf)
{
    MovingAverage(Hf, 0);
    MovingAverage(Hf, 1);
}

void AFKirkeby::MovingAverage(FreqVector_t& Hf, const int nCpxPart)
{
    // aka MediaLplus
    // A.Farina:
    // differisce da MediaL perche' gestisce "meglio" la media asimmetrica
    // N e' la dimensione effettiva del vettore da mediare, quindi Length/2+1
    // span e' il numero di lineee spettrali su cui si media
    const AFSampleCount smpcLength   = Hf.GetLength();
    const AFSampleCount smpcSpan     = AFSampleCount(m_dbAvgWidth);
    const AFSampleCount smpcHalfSpan = smpcSpan/2;
    
    TimeVector_t Hst(smpcLength);  // results vector [SC]
    TimeVector_t Tempt(smpcSpan);  // in questo vettore memorizzo gli "span"
                                   // valori per eseguire la media
    AFSampleCount j;     // contatore
    AFSampleCount jc;    // centro banda
    AFSampleCount i;      //servono per eseguire la media asimmetrica nella prima frazione
    
    //informazioni per la finestra di Hanning   
    double dbExecWd; // contiene il valore calcolate della finestra nelm punto indicato 
                     // da wd_pnt
                     
    AFSample smpAvg;    //variabile per contenere il risultato della somma
    
    double dbTwoPi = 2*M_PI;
    
    //Calcolo la somma dei pesi TODO -> Precalculate Window and window's weights sum !!
    double dbWeightsSum = 0.0;   //somma dei pesi della finestra
    for(j = 0; j < smpcSpan; j++)   
        dbWeightsSum += 0.5 * (1 - cos(dbTwoPi*j/(smpcSpan-1)));
    
    // 1. jc = 1  ->  half_span (cerco di non mediare la componente DC)
    for(jc = 1; jc <= smpcHalfSpan; jc++) 
    { 
        // Reset temporary vector [SC]
        Tempt.Clear();
        
        //Carico i valori a sinistra di jc
        for(j = (jc-1), i = 1; j > 0; j--, i++) //tolgo l'uguale, non voglio mediare usando la DC
            Tempt[smpcHalfSpan - i] = Hf[j][nCpxPart];
        
        //carico i valori a destra di jc
        for(j = jc, i = 0; j <= (jc+smpcHalfSpan); j++, i++)
            Tempt[smpcHalfSpan + i] = Hf[j][nCpxPart];
        
        //eseguo la finestratura hanning
        for(j = 0; j < smpcHalfSpan; j++) 
        {
            dbExecWd = 0.5 * (1 - cos(dbTwoPi*j/(smpcSpan-1)));
            Tempt[j] *= dbExecWd;
            Tempt[smpcSpan-j-1] *= dbExecWd;
        }
    
        // average
        smpAvg = 0.0;
        for(i = 0; i < smpcSpan; i++)
            smpAvg += Tempt[i];
        
        Hst[jc] = smpAvg/dbWeightsSum;
    
    } //passo ad un altro jc
    
    // 2. jc = N-half_span -> N ---------------------------------
    for(jc = (smpcLength-smpcHalfSpan); jc < smpcLength; jc++)
    {
        // Reset temporary vector [SC]
        Tempt.Clear();
        
        //carico i valori
        for(j = (jc-smpcHalfSpan), i = 0; j < smpcLength; j++, i++)
            Tempt[i] = Hf[j][nCpxPart];
        
        //eseguo la finestratura
        for(j = 0; j < smpcHalfSpan; j++) 
        {   
            dbExecWd = 0.5 * (1 - cos(dbTwoPi*j/(smpcSpan-1)));
            Tempt[j] *= dbExecWd;
            Tempt[smpcSpan-j-1] *= dbExecWd;
        }
    
        // average
        smpAvg = 0.0;
        for(i = 0; i < smpcSpan; i++)
            smpAvg += Tempt[i];
        
        Hst[jc] = smpAvg/dbWeightsSum;
        
    }  //passo ad un'altro jc

    // 3. jc = half_span -> N-half_span ---------------------------------
    for(jc = smpcHalfSpan; jc < (smpcLength-smpcHalfSpan); jc++)
    {
        // Reset temporary vector [SC]
        Tempt.Clear();
        
        //carico i valori che serviranno per il filtraggio TODO -> memcpy???
        for(j = (jc-smpcHalfSpan), i = 0; j < (jc+smpcHalfSpan); j++, i++)  
            Tempt[i] = Hf[j][nCpxPart];
        
        //adesso uso i valori acquisiti per creare il punto j in uscita
        for(j = 0; j < smpcHalfSpan; j++)
        {
            dbExecWd = 0.5 * (1 - cos(dbTwoPi*j/(smpcSpan-1)));
            Tempt[j] *= dbExecWd;
            Tempt[smpcSpan-j-1] *= dbExecWd;
        } // della finestra
    
        //adesso uso i valori finestrati per ottenere il valore "j-esimo" di uscita
        smpAvg = 0.0;
        for(i = 0; i < smpcSpan; i++)
            smpAvg += Tempt[i];
        
        Hst[jc] = smpAvg/dbWeightsSum;
        
    }//del ciclo su "jc"

    for(j = 0; j < smpcLength; j++)
        Hf[j][nCpxPart] = Hst[j];
        
}

void AFKirkeby::OctaveSmoothing(FreqVector_t& Hf)
{
    OctaveSmoothing(Hf, 0);
    OctaveSmoothing(Hf, 1);
}

void AFKirkeby::OctaveSmoothing(FreqVector_t& Hf, const int nCpxPart)
{
    const AFSampleCount smpcLength = Hf.GetLength();
    TimeVector_t Hst(smpcLength);

    const AFSample smpSmoothFact = AFSample(m_dbAvgWidth);
    
    AFSampleCount j;       // contatore
    AFSampleCount j1,j2;   // estremi banda
    AFSampleCount j1o,j2o; // estremi banda precedente
    AFSampleCount jc;      // centro banda
    AFSampleCount smpcTotjs;   // frequenze presenti in una banda
    
    double dbRad2x = sqrt(pow(2.0, double(smpSmoothFact))); // radice quadrata di 2^SmoothFact
    double dbInvRad2x = 1.0/dbRad2x;              // 1 / radice quadrata di 2^SmoothFact
    AFSample smpHstTot = 0.0; // buffer per le sommatorie
    
    // inizializzo HsTot, Hs[0] e j1o j2o
    Hst[0] = Hf[0][nCpxPart];
    j1o = j2o = 0;
    
    // ciclo principale
    for(jc = 1; jc < smpcLength; jc++)
    {
        j1 = AFSampleCount(dbInvRad2x*jc + 0.5); // estremo inferiore banda
        j2 = AFSampleCount(dbRad2x*jc);        // estremo superiore banda
        smpcTotjs = j2-j1 + 1;              // totale frequenze nella banda
        
        // elimino dal totale tutti i termini della banda precedente 
        // a sinistra della banda corrente
        for(j = j1o; j < j1; j++)
            smpHstTot -= Hf[j][nCpxPart];
        
        // inserisco nel totale tutti i termini a destra della banda precedente 
        // presenti nella banda corrente        
        for(j = (j2o+1); j <= j2; j++)
            smpHstTot += (j<=smpcLength) ? Hf[j][nCpxPart]
                                         : Hf[2*smpcLength-j][nCpxPart]; // N1-(j-N1) = 2*N1-j
            
        // calcolo il valore dell'Hs corrente
        Hst[jc] = AFSample(smpHstTot/smpcTotjs);
        
        // aggiorno il valore di j1o e j2o
        j1o = j1;
        j2o = j2;
    }   
    
    // ricopio la risposta in frequenza smoothed da Hs a H
    for(j = 1; j < smpcLength; j++)
        Hf[jc][nCpxPart] = Hst[jc];
    
}


void AFKirkeby::Average(FreqVector_t& Hf)
{
	switch(m_nAvgMode)
	{
		case AM_REIM: 
		   //MyMedia2(RE,IM,TLen,TipoFinestraFlag,MediaDim,lpAmp,ci); //Medie Re e IM
            switch(m_nAvgType)
            {
                case AT_LINEAR:
                    MovingAverage(Hf);
                    break;

                case AT_OCTAVE:
                    OctaveSmoothing(Hf);
                    break;
            }

            //ScriviDatiName("media_1.txt",H,TLen,ci,lpAmp); //Scrivo nel chiamante
            break;
            
        case AM_MAGPH:
            //calcolo modulo e fase
            Hf.ToPolar();

            //Eseguo l'unwrap della fase
            Hf.UnwrapPhase();

            //Adesso eseguo la media
            //MyMedia2(RE,IM,TLen,TipoFinestraFlag,MediaDim,lpAmp,ci);
            switch(m_nAvgType)
            {
                case AT_LINEAR:
                    MovingAverage(Hf);
                    break;

                case AT_OCTAVE:
                    OctaveSmoothing(Hf);
                    break;
            }

            //Ritorno in coordinate rettangolari
            Hf.ToRectangular();

            //ScriviDatiName("media_2.txt",H,TLen,ci,lpAmp); //Scrivo nel chiamante
            break;
	}
}

void AFKirkeby::Cepstrum(FreqVector_t& Hf)
{
    //This function shuold do following steps with the input vector (Harray)
    //
    //  1) calculates a new complex vector that has, for each element, 
    //      Re = the logarithm of the magnitude square value
    //           of the input vector.
    //      Im = 0
    FreqVector_t Uf(Hf.Length());
    
    AFSampleCount i;
    for(i = 0; i < Hf.Length(); i++)
        Uf.SetReal(i, (Re(Hf[i]) == 0) ? expf(-32)
                                       : logf(Hf.Module(i)));
    
    //  2) calculates the IFFT of the vector previously obtained
    TimeVector_t Xt(m_smpcColLength);
    IFFT(Xt, Uf);

    // [Now psmpXt contains the cepstrum of pcpxH. But there is more...]
    
    //  3) doubles the amplitude of the transformed (real!) vector (!!)
    for(i = 1; i < (Xt.Length()-1); i++) Xt[i] *= 2.0;
    
    //  4) calculates the FFT of the transformed and doubled vector
    FFT(Uf, Xt);
    
    //  5) calculates a new complex vector (MParray) with, for each element,
    //      Re = exp(Re(in))*cos(Im(in))
    //      Im = exp(Re(in))*sin(Im(in))
    FreqVector_t MPf(Hf.Length());
    
    for(i = 0; i < Hf.Length(); i++)
    {
    	 MPf.SetReal(i, expf(Uf.Real(i)) * cosf(Uf.Imag(i)));
    	 MPf.SetImag(i, expf(Uf.Real(i)) * sinf(Uf.Imag(i)));
    }
    
    //  6) calculates the IFFT of the vector previously obtained
    IFFT(Xt, MPf);  // TODO: not really used...can be removed!
    
    //  7) calculates the EP components as EParray = Harray/MParray
    FreqVector_t EPf(Hf.Length());
    EPf = Hf/MPf; // Overload power !!
    
    //  8) converts EParray and MParray from rectangular to polar coordinates
    EPf.ToPolar();
    MPf.ToPolar();
    
    //  9) unwraps 'polar' EParray's phase and puts to '0' all MParray elements 
    //     phase component
    EPf.UnwrapPhase();
    for(i = 0; i < MPf.Length(); i++)  MPf.SetPhas(i, 0.0);
    
    // 10) averages the unwrapped EParray phase and the MParray magnitude with 
    //     'MediaLplus' or 'OctaveSmoothing', depending by the user choice
    switch(m_nAvgType)
    {
        case AT_LINEAR: 
        	  MovingAverage(EPf, CPX_PHASE);
        	  MovingAverage(MPf, CPX_MAGN);
        	  break;
        	  
        case AT_OCTAVE: 
        	  OctaveSmoothing(EPf, CPX_PHASE);
        	  OctaveSmoothing(MPf, CPX_MAGN);
        	  break;
    }
    
    // 11) converts EParray and MParray from polar to rectangular coordinates
    EPf.ToRectangular();
    MPf.ToRectangular();
    
    // 12) obtains averaged system response H = MParray * EParray
    Hf = MPf*EPf;
    
    // 13) frees allocated memory
}

void AFKirkeby::KirkebyModulusInversion(FreqVector_t& Hf)
{
    // input data:  Hf
    // output data: Hf

    //float RegPar=lpAmp->RegParam;   --> m_dbInRP
    //float RegPar2=lpAmp->RegParam2; --> m_dbOutRP
    //float Transwidth=lpAmp->trwid;  --> m_dbTransWidth
    AFSampleCount smpcLength = Hf.Length();
    AFSampleCount i1a = smpcLength * afround(m_dbLowCutFrq  * pow(2,-m_dbTransWidth/2)/m_dbRate);
    AFSampleCount i1b = smpcLength * afround(m_dbLowCutFrq  * pow(2, m_dbTransWidth/2)/m_dbRate);
    AFSampleCount i2a = smpcLength * afround(m_dbHighCutFrq * pow(2,-m_dbTransWidth/2)/m_dbRate);
    AFSampleCount i2b = smpcLength * afround(m_dbHighCutFrq * pow(2, m_dbTransWidth/2)/m_dbRate);

    FreqVector_t Hsf(Hf.Length());

    // DC and FNyquist don't have imaginary part
    Hsf.SetDC( Hf.GetDC() / (Hf.GetDC() * Hf.GetDC() + m_dbOutRP) );
    Hsf.SetNy( Hf.GetNy() / (Hf.GetNy() * Hf.GetNy() + m_dbOutRP) );

    // Check extremes
    if(i1a < 1) i1a = 1;
    if(i1b < 1) i1b = 1;
    if(i2a < (smpcLength-1)) i2a = (smpcLength-1);
    if(i2b < (smpcLength-1)) i2b = (smpcLength-1);

    // Lower Out band
    AFSampleCount i;
    for(i = 1; i < i1a; i++)
    {
        Hsf.SetReal(i, Hf.Real(i) /
                      (Hf.SquareModule(i) + m_dbOutRP));
        Hsf.SetImag(i, -Hf.Imag(i) /
                       (Hf.SquareModule(i) + m_dbOutRP));
    }
    AFSample smpRp;
    for(i = i1a; i < i1b; i++)
    {
        smpRp = expf( logf(m_dbOutRP) + (logf(m_dbInRP)-logf(m_dbOutRP))*(i-i1a)/(i1b-i1a) );
        Hsf.SetReal(i, Hf.Real(i) /
                      (Hf.SquareModule(i) + smpRp));
        Hsf.SetImag(i, -Hf.Imag(i) /
                       (Hf.SquareModule(i) + smpRp));
    }

    // Inner band
    for(i = i1b; i < i2a; i++)
    {
        Hsf.SetReal(i, Hf.Real(i) /
                      (Hf.SquareModule(i) + m_dbInRP));
        Hsf.SetImag(i, -Hf.Imag(i) /
                       (Hf.SquareModule(i) + m_dbInRP));
    }

    // Superior transition band
    for(i = i2a; i < i2b; i++)
    {
        smpRp = expf( logf(m_dbInRP) + (logf(m_dbOutRP)-logf(m_dbInRP))*(i-i2a)/(i2b-i2a) );
        Hsf.SetReal(i, Hf.Real(i) /
                      (Hf.SquareModule(i) + smpRp));
        Hsf.SetImag(i, -Hf.Imag(i) /
                       (Hf.SquareModule(i) + smpRp));
    }

    // Lower Out band
    for(i = i2b; i < smpcLength; i++)
    {
        Hsf.SetReal(i, Hf.Real(i) /
                      (Hf.SquareModule(i) + m_dbOutRP));
        Hsf.SetImag(i, -Hf.Imag(i) /
                       (Hf.SquareModule(i) + m_dbOutRP));
    }

    //Store result
    Hf = Hsf;
}

void AFKirkeby::KirkebyRatioModulusInversion(FreqVector_t& Uf, FreqVector_t& Wf)
{
    // input data:  pcpxU and pcpxW
    // output data: pcpxU

    assert(Uf.Length() == Wf.Length());
    const AFSampleCount smpcLength = Uf.Length();
    
    //float RegPar=lpAmp->RegParam;   --> m_dbInRP
    //float RegPar2=lpAmp->RegParam2; --> m_dbOutRP
    //float Transwidth=lpAmp->trwid;  --> m_dbTransWidth
    AFSampleCount i1a = smpcLength * afround(m_dbLowCutFrq  * pow(2,-m_dbTransWidth/2)/m_dbRate);
    AFSampleCount i1b = smpcLength * afround(m_dbLowCutFrq  * pow(2, m_dbTransWidth/2)/m_dbRate);
    AFSampleCount i2a = smpcLength * afround(m_dbHighCutFrq * pow(2,-m_dbTransWidth/2)/m_dbRate);
    AFSampleCount i2b = smpcLength * afround(m_dbHighCutFrq * pow(2, m_dbTransWidth/2)/m_dbRate);

    FreqVector_t Hsf(Uf.Length());
    
    // DC and FNyquist don't have imaginary part
    Hsf.SetDC(Uf.GetDC() * Wf.GetDC() /  (Uf.GetDC() * Wf.GetDC() + m_dbOutRP));
    Hsf.SetNy(Uf.GetNy() * Wf.GetNy() /  (Uf.GetNy() * Wf.GetNy() + m_dbOutRP));

    // Check extremes
    if(i1a < 1) i1a = 1;
    if(i1b < 1) i1b = 1;
    if(i2a < (smpcLength-1)) i2a = (smpcLength-1);
    if(i2b < (smpcLength-1)) i2b = (smpcLength-1);

        // Lower Out band
    AFSampleCount i;
    for(i = 1; i < i1a; i++)
    {
        Hsf.SetReal(i, (Uf.Real(i) * Wf.Real(i) + Uf.Imag(i) * Wf.Imag(i)) /
                       (Wf.SquareModule(i) + m_dbOutRP));
        Hsf.SetImag(i, (Uf.Imag(i) * Wf.Real(i) - Uf.Real(i) * Wf.Imag(i)) /
                       (Wf.SquareModule(i) + m_dbOutRP));
    }
    AFSample smpRp;
    for(i = i1a; i < i1b; i++)
    {
        smpRp = expf( logf(m_dbOutRP) + (logf(m_dbInRP)-logf(m_dbOutRP))*(i-i1a)/(i1b-i1a) );
        Hsf.SetReal(i, (Uf.Real(i) * Wf.Real(i) + Uf.Imag(i) * Wf.Imag(i)) /
                       (Wf.SquareModule(i) + smpRp));
        Hsf.SetImag(i, (Uf.Imag(i) * Wf.Real(i) - Uf.Real(i) * Wf.Imag(i)) /
                       (Wf.SquareModule(i) + smpRp));
    }

    // Inner band
    for(i = i1b; i < i2a; i++)
    {
        Hsf.SetReal(i, (Uf.Real(i) * Wf.Real(i) + Uf.Imag(i) * Wf.Imag(i)) /
                       (Wf.SquareModule(i) + m_dbInRP));
        Hsf.SetImag(i, (Uf.Imag(i) * Wf.Real(i) - Uf.Real(i) * Wf.Imag(i)) /
                       (Wf.SquareModule(i) + m_dbInRP));
    }

    // Superior transition band
    for(i = i2a; i < i2b; i++)
    {
        smpRp = expf( logf(m_dbInRP) + (logf(m_dbOutRP)-logf(m_dbInRP))*(i-i2a)/(i2b-i2a) );
        Hsf.SetReal(i, (Uf.Real(i) * Wf.Real(i) + Uf.Imag(i) * Wf.Imag(i)) /
                       (Wf.SquareModule(i) + smpRp));
        Hsf.SetImag(i, (Uf.Imag(i) * Wf.Real(i) - Uf.Real(i) * Wf.Imag(i)) /
                       (Wf.SquareModule(i) + smpRp));
    }

    // Lower Out band
    for(i = i2b; i < smpcLength; i++)
    {
        Hsf.SetReal(i, (Uf.Real(i) * Wf.Real(i) + Uf.Imag(i) * Wf.Imag(i)) /
                       (Wf.SquareModule(i) + m_dbOutRP));
        Hsf.SetImag(i, (Uf.Imag(i) * Wf.Real(i) - Uf.Real(i) * Wf.Imag(i)) /
                       (Wf.SquareModule(i) + m_dbOutRP));
    }

    //Store result
    Uf = Hsf;
}

// -----------------------------------------------------------------------------------------
// Main functions
// -----------------------------------------------------------------------------------------
bool AFKirkeby::MonoInverseFilter(TimeVector_t& Ht)
{
    printf("MonoInverseFilter (rows: %d, cols: %d, avgmode: %d\n", m_nRows, m_nCols, m_nAvgMode);
    // 1) Calculate FFT
    FFT(m_aaHf.Item(0,0), Ht); printf("1.");

    // 2) Calculate Average
    switch(m_nAvgMode)
    {
        case AM_REIM:
        case AM_MAGPH:
            Average(m_aaHf.Item(0,0));
            break;

        case AM_CEPSTRUM:
            Cepstrum(m_aaHf.Item(0,0));
            break;
    } printf("2.");

    // 3) inversione modulo, trasformazione in numeri complessi (e aggiunta fase lineare)
    KirkebyModulusInversion(m_aaHf.Item(0,0)); printf("3.");

    // 4) calculate iFFt
    IFFT(Ht, m_aaHf.Item(0,0)); printf("done.\n");

    return true;
}


#define Hllf m_aaHf.Item(0,0)
#define Hlrf m_aaHf.Item(0,1)
#define Hrrf m_aaHf.Item(1,1)
#define Hrlf m_aaHf.Item(1,0)

bool AFKirkeby::QuadInverseFilter(TimeMatrix_t& Ht)
{
    FFT(m_aaHf.Item(0,0), Ht.Item(0,0)); // Hll
    FFT(m_aaHf.Item(0,1), Ht.Item(0,1)); // Hlr
    FFT(m_aaHf.Item(1,1), Ht.Item(1,1)); // Hrr
    FFT(m_aaHf.Item(1,0), Ht.Item(1,0)); // Hrl

    // 2) Calculate Average
    switch(m_nAvgMode)
    {
        case AM_REIM:
        case AM_MAGPH:
            Average(m_aaHf.Item(0,0)); // Hll
            Average(m_aaHf.Item(0,1)); // Hlr
            Average(m_aaHf.Item(1,0)); // Hrl
            Average(m_aaHf.Item(1,1)); // Hrr            
            break;

        case AM_CEPSTRUM:
            Cepstrum(m_aaHf.Item(0,0)); // Hll
            Cepstrum(m_aaHf.Item(0,1)); // Hlr
            Cepstrum(m_aaHf.Item(1,0)); // Hrl
            Cepstrum(m_aaHf.Item(1,1)); // Hrr
            break;
    }

    // 3) inversione modulo, trasformazione in numeri complessi (e aggiunta fase lineare)
    AFSampleCount i;
    FreqVector_t Df;

    if(m_bCancelCrosstalk)
    {
        // inversione con il solo scopo di cancellare il cross-talk, senza equalizzazione
        // Ora calcolo il rapporto n. 1 (filtro Frl=-Hrl/Hll)
        KirkebyRatioModulusInversion(m_aaHf.Item(1,0), m_aaHf.Item(0,0)); //Hrl holds result
        for(i=0; i < m_aaHf.Item(0,0).Length(); i++)
            m_aaHf.Item(0,0).SetItem(i, AFSample(1.0), AFSample(0.0)); // Hll = 1 + i*0

        // Ora calcolo il rapporto n. 2 (filtro Flr=-Hlr/Hrr)
        KirkebyRatioModulusInversion(m_aaHf.Item(0,1), m_aaHf.Item(1,1)); //Hrl holds result
        for(i=0; i < m_aaHf.Item(0,0).Length(); i++)
            m_aaHf.Item(1,1).SetItem(i, AFSample(1.0), AFSample(0.0)); // Hrr = 1 + i*0

    }
    else if(m_bActiveNoiseControl)
    {
        // inversione per calcolo filtro inverso ANC per Sasib
        // Ora calcolo il denominatore
        Df.Create(m_aaHf.Item(0,0).Length());

        Df.SetDC( m_aaHf.Item(0,0).GetDC()*m_aaHf.Item(1,1).GetDC() - m_aaHf.Item(0,1).GetDC()*m_aaHf.Item(1,0).GetDC() ); // Hll*Hrr - Hlr*Hrl
        Df.SetNy( m_aaHf.Item(0,0).GetNy()*m_aaHf.Item(1,1).GetNy() - m_aaHf.Item(0,1).GetNy()*m_aaHf.Item(1,0).GetNy() ); // Hll*Hrr - Hlr*Hrl

        for(i=1; i < Df.Length()-1; i++)
        {
            // Re(Df) = Re(Hll)*Re(Hrr) - Im(Hll)*Im(Hrr) - Re(Hlr)*Re(Hrl) + Im(Hlr)*Im(Hrl)
            Df.SetReal(i, m_aaHf.Item(0,0).Real(i)*m_aaHf.Item(1,1).Real(i) - m_aaHf.Item(0,0).Imag(i)*m_aaHf.Item(1,1).Imag(i) -
                          m_aaHf.Item(0,1).Real(i)*m_aaHf.Item(1,0).Real(i) + m_aaHf.Item(0,1).Imag(i)*m_aaHf.Item(1,0).Imag(i) );
            
            // Im(Df) = Re(Hll)*Im(Hrr) + Im(Hll)*Re(Hrr) - Re(Hlr)*Im(Hrl) - Im(Hlr)*Re(Hrl)
            Df.SetImag(i, m_aaHf.Item(0,0).Real(i)*m_aaHf.Item(1,1).Imag(i) + m_aaHf.Item(0,0).Imag(i)*m_aaHf.Item(1,1).Real(i) -
                          m_aaHf.Item(0,1).Real(i)*m_aaHf.Item(1,0).Imag(i) - m_aaHf.Item(0,1).Imag(i)*m_aaHf.Item(1,0).Real(i) );
        }

        // inversione denominatore
        KirkebyModulusInversion(Df);

        // Hll = Hrr*Df
        m_aaHf.Item(0,0).SetDC(m_aaHf.Item(1,1).GetDC() * Df.GetDC());
        m_aaHf.Item(0,0).SetNy(m_aaHf.Item(1,1).GetNy() * Df.GetNy());
        for(i=1; i < Df.Length()-1; i++)
        {
            m_aaHf.Item(0,0).SetReal(i, m_aaHf.Item(1,1).Real(i)*Df.Real(i) - m_aaHf.Item(1,1).Imag(i)*Df.Imag(i));
            m_aaHf.Item(0,0).SetImag(i, m_aaHf.Item(1,1).Imag(i)*Df.Real(i) + m_aaHf.Item(1,1).Real(i)*Df.Imag(i));
        }
        //pcpxHll holds the result
    }
    else
    {
        // inversione completa alla Kirkeby, cross-talk cancelling ed equalizzazione
        // Ora calcolo il denominatore
        Df.Create(m_aaHf.Item(0,0).Length());

        Df.SetDC( m_aaHf.Item(0,0).GetDC()*m_aaHf.Item(1,1).GetDC() - m_aaHf.Item(0,1).GetDC()*m_aaHf.Item(1,0).GetDC() ); // Hll*Hrr - Hlr*Hrl
        Df.SetNy( m_aaHf.Item(0,0).GetNy()*m_aaHf.Item(1,1).GetNy() - m_aaHf.Item(0,1).GetNy()*m_aaHf.Item(1,0).GetNy() ); // Hll*Hrr - Hlr*Hrl
        
        for(i=1; i < Df.Length()-1; i++)
        {
            // Re(Df) = Re(Hll)*Re(Hrr) - Im(Hll)*Im(Hrr) - Re(Hlr)*Re(Hrl) + Im(Hlr)*Im(Hrl)
            Df.SetReal(i, m_aaHf.Item(0,0).Real(i)*m_aaHf.Item(1,1).Real(i) - m_aaHf.Item(0,0).Imag(i)*m_aaHf.Item(1,1).Imag(i) -
            m_aaHf.Item(0,1).Real(i)*m_aaHf.Item(1,0).Real(i) + m_aaHf.Item(0,1).Imag(i)*m_aaHf.Item(1,0).Imag(i) );
            
            // Im(Df) = Re(Hll)*Im(Hrr) + Im(Hll)*Re(Hrr) - Re(Hlr)*Im(Hrl) - Im(Hlr)*Re(Hrl)
            Df.SetImag(i, m_aaHf.Item(0,0).Real(i)*m_aaHf.Item(1,1).Imag(i) + m_aaHf.Item(0,0).Imag(i)*m_aaHf.Item(1,1).Real(i) -
            m_aaHf.Item(0,1).Real(i)*m_aaHf.Item(1,0).Imag(i) - m_aaHf.Item(0,1).Imag(i)*m_aaHf.Item(1,0).Real(i) );
        }
        
        // inversione denominatore
        KirkebyModulusInversion(Df);

        AFSample smpTemp = m_aaHf.Item(1,1).GetDC() * Df.GetDC();
        m_aaHf.Item(0,1).SetDC( - m_aaHf.Item(0,1).GetDC() * Df.GetDC()); // Hlr
        m_aaHf.Item(1,0).SetDC( - m_aaHf.Item(1,0).GetDC() * Df.GetDC()); // Hrl
        m_aaHf.Item(1,1).SetDC(   m_aaHf.Item(0,0).GetDC() * Df.GetDC()); // Hrr
        m_aaHf.Item(0,0).SetDC(  smpTemp * Df.GetDC()); // Hll

        smpTemp = m_aaHf.Item(1,1).GetNy() * Df.GetNy();
        m_aaHf.Item(0,1).SetNy( - m_aaHf.Item(0,1).GetNy() * Df.GetNy()); // Hlr
        m_aaHf.Item(1,0).SetNy( - m_aaHf.Item(1,0).GetNy() * Df.GetNy()); // Hrl
        m_aaHf.Item(1,1).SetNy(   m_aaHf.Item(0,0).GetNy() * Df.GetNy()); // Hrr
        m_aaHf.Item(0,0).SetNy(   smpTemp * Df.GetNy()); // Hll
        
        AFSample smpReTempL, smpImTempL;
        AFSample smpReTempR, smpImTempR;

        for(i=1; i < Df.Length()-1; i++)
        {
            smpReTempL = m_aaHf.Item(1,1).Real(i)*Df.Real(i) - m_aaHf.Item(1,1).Imag(i)*Df.Imag(i); // Hrr
            smpImTempL = m_aaHf.Item(1,1).Imag(i)*Df.Real(i) + m_aaHf.Item(1,1).Real(i)*Df.Imag(i); // Hrr
            smpReTempR = m_aaHf.Item(0,0).Real(i)*Df.Real(i) - m_aaHf.Item(0,0).Imag(i)*Df.Imag(i); // Hll
            smpImTempR = m_aaHf.Item(0,0).Imag(i)*Df.Real(i) + m_aaHf.Item(0,0).Real(i)*Df.Imag(i); // Hll
            m_aaHf.Item(0,0).SetItem(i, smpReTempL, smpImTempL);
            m_aaHf.Item(1,1).SetItem(i, smpReTempR, smpImTempR);

            smpReTempL = m_aaHf.Item(0,1).Real(i)*Df.Real(i) - m_aaHf.Item(0,1).Imag(i)*Df.Imag(i); // Hlr
            smpImTempL = m_aaHf.Item(0,1).Imag(i)*Df.Real(i) + m_aaHf.Item(0,1).Real(i)*Df.Imag(i); // Hlr
            smpReTempR = m_aaHf.Item(1,0).Real(i)*Df.Real(i) - m_aaHf.Item(1,0).Imag(i)*Df.Imag(i); // Hrl
            smpImTempR = m_aaHf.Item(1,0).Imag(i)*Df.Real(i) + m_aaHf.Item(1,0).Real(i)*Df.Imag(i); // Hrl
            m_aaHf.Item(0,1).SetItem(i, smpReTempL, smpImTempL);
            m_aaHf.Item(1,0).SetItem(i, smpReTempR, smpImTempR);
        }
    }

    // 4) calculate iFFt 
    IFFT(Ht.Item(0,0), m_aaHf.Item(0,0)); // Hll
    IFFT(Ht.Item(0,1), m_aaHf.Item(0,1)); // Hlr
    IFFT(Ht.Item(1,1), m_aaHf.Item(1,1)); // Hrr
    IFFT(Ht.Item(1,0), m_aaHf.Item(1,0)); // Hrl
    
    return true;
}

// --------------------------------------------- Setup methods
bool AFKirkeby::Init()
{
    InitVectors();
    InitFft();
    return true;
}

// --------------------------------------------- Processig methods
bool AFKirkeby::PreProcess()
{
    printf("Preprocess\n"); fflush(stdout);
   if(m_nFilterType == IK_STEREO)
   {
       // Here we have to fix the fake done in InitVectors()
        m_nCols = 2;
        m_aaHt.Item(1,0) = m_aaHt.Item(0,1); // Hrl = Hlr
        m_aaHt.Item(1,1) = m_aaHt.Item(0,0); // Hrr = Hll
   }
   
   int nCol, nRow;
   
   // Do fade in/out 
   for(nRow = 0; nRow < m_nRows; nRow++)
   {
      for(nCol = 0; nCol < m_nCols; nCol++) 
      {
         if(m_smpcFadeIn > 0) 
             m_aaHt.Item(nRow, nCol).FadeIn(m_smpcFadeIn);
   
         if(m_smpcFadeOut > 0)
             m_aaHt.Item(nRow, nCol).FadeOut(m_smpcFadeOut);
      }
   }
   return true;
}


bool AFKirkeby::Process() 
{
    int nRow, nCol;
    printf("Process (rows: %d, cols: %d, avgmode: %d\n", m_nRows, m_nCols, m_nAvgMode);
   // 1) Init() should be already called!
   
   // 2) Pre-process (fade-in/out, ecc.)
   if(!PreProcess()) return false;
 
   // 3) Spectrum inversion cycle
   
   switch(m_nFilterType)
   {
      //Farina: 0 - mono, 1 - dual mono, 
      //        2 - stereo (stereo dipole symm.), 
      //        3 - 2x2 (complete stereo dipole)

        case IK_MONO:
            for(nRow = 0; nRow < m_nRows; nRow++)
                for(nCol = 0; nCol < m_nCols; nCol++)
                    MonoInverseFilter(m_aaHt.Item(nRow, nCol));
            break;
            
        case IK_STEREO:
            if(m_bCancelCrosstalk)
            {
                QuadInverseFilter(m_aaHt);
            }
            else
            {
                MonoInverseFilter(m_aaHt.Item(0,0));
                MonoInverseFilter(m_aaHt.Item(1,0));
            }
            break;
            
        case IK_DIPOLE:
            QuadInverseFilter(m_aaHt);
            break;
   }
   
   if(!PostProcess()) return false;
   
   return true;
}

bool AFKirkeby::PostProcess()
{
   // if(m_bAutorange) ApplyGain();  TODO: Enable autorange & gain!!!!
   return true;
}




// --------------------------------------------- 'ctors

AFKirkeby::AFKirkeby(const int nRows, const int nCols)
  : m_dbRate(44100),
    m_nRows(nRows), m_nCols(nCols),
    m_aaHt(0), m_aaHf(0),
    m_bFftPlansExist(false),
    m_smpcColLength(0),  m_smpcRowLength(0),
    m_nFilterType(IK_MONO),
    m_bCancelCrosstalk(false),
    m_dbInRP(0.001), m_dbOutRP(1.0),
    m_dbLowCutFrq(80), m_dbHighCutFrq(16000), //Hz
    m_dbTransWidth(0.3333),      // Oct
    m_smpcFadeIn(0), m_smpcFadeOut(0),  //Smpls
    m_nAvgMode(AM_NONE), m_nAvgType(AT_LINEAR),
    m_dbAvgWidth(5.0),  // Spectral points
    m_bAutorange(true), m_dbGain(1.0)
{}

AFKirkeby::~AFKirkeby()
{
   DeleteVectors();
   DeleteFft();
}

// Indentation settings for Vim and Emacs and unique identifier for Arch, a
// version control system. Please do not modify past this point.
//
// Local Variables:
// c-basic-offset: 3
// indent-tabs-mode: nil
// End:
//
// vim: et sts=3 sw=3
// arch-tag: c05d7383-e7cd-410e-b7b8-f45f47c9e283
