// Copyright (c) 2007-2010 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
namespace SlimDX2.XAPO
{
    public partial interface AudioProcessor
    {
        /// <summary>	
        /// Returns the registration properties of an XAPO.	
        /// </summary>	
        /// <returns> a <see cref="SlimDX2.XAPO.RegistrationProperties"/> structure containing theregistration properties the XAPO was created with; use XAPOFree to free thestructure.</returns>
        /// <unmanaged>HRESULT IXAPO::GetRegistrationProperties([Out] XAPO_REGISTRATION_PROPERTIES** ppRegistrationProperties)</unmanaged>
        SlimDX2.XAPO.RegistrationProperties RegistrationProperties { get;}

        /// <summary>	
        /// Queries if a specific input format is supported for a given output format.	
        /// </summary>	
        /// <param name="outputFormat">Output format.</param>
        /// <param name="requestedInputFormat">Input format to check for being supported.</param>
        /// <param name="supportedInputFormat"> If not NULL, and the input format is not supported for the given output format, ppSupportedInputFormat returns a  pointer to the closest input format that is supported. Use {{XAPOFree}} to free the returned structure. </param>
        /// <returns>No documentation.</returns>
        /// <unmanaged>HRESULT IXAPO::IsInputFormatSupported([None] const WAVEFORMATEX* pOutputFormat,[None] const WAVEFORMATEX* pRequestedInputFormat,[Out, Optional] WAVEFORMATEX** ppSupportedInputFormat)</unmanaged>
        bool IsInputFormatSupported(SlimDX2.Windows.WaveFormat outputFormat, SlimDX2.Windows.WaveFormat requestedInputFormat,
                                    out SlimDX2.Windows.WaveFormat supportedInputFormat);

        /// <summary>	
        /// Queries if a specific output format is supported for a given input format.	
        /// </summary>	
        /// <param name="inputFormat">[in]  Input format. </param>
        /// <param name="requestedOutputFormat">[in]  Output format to check for being supported. </param>
        /// <param name="supportedOutputFormat">[out]  If not NULL and the output format is not supported for the given input format, ppSupportedOutputFormat returns a pointer to the closest output format that is supported. Use {{XAPOFree}} to free the returned structure. </param>
        /// <returns>No documentation.</returns>
        /// <unmanaged>HRESULT IXAPO::IsOutputFormatSupported([None] const WAVEFORMATEX* pInputFormat,[None] const WAVEFORMATEX* pRequestedOutputFormat,[Out, Optional] WAVEFORMATEX** ppSupportedOutputFormat)</unmanaged>
        bool IsOutputFormatSupported(SlimDX2.Windows.WaveFormat inputFormat, SlimDX2.Windows.WaveFormat requestedOutputFormat,
                                     out SlimDX2.Windows.WaveFormat supportedOutputFormat);

        /// <summary>	
        /// Performs any effect-specific initialization.	
        /// </summary>	
        /// <param name="stream"> Effect-specific initialization parameters, may be NULL if DataByteSize is 0. </param>
        /// <returns>No documentation.</returns>
        /// <unmanaged>HRESULT IXAPO::Initialize([In, Buffer, Optional] const void* pData,[None] UINT32 DataByteSize)</unmanaged>
        void Initialize(DataStream stream);

        /// <summary>	
        /// Resets variables dependent on frame history. 	
        /// </summary>	
        /// <unmanaged>void IXAPO::Reset()</unmanaged>
        void Reset();

        /// <summary>	
        /// Called by XAudio2 to lock the input and output configurations of an XAPO allowing it to	
        /// do any final initialization before {{Process}} is called on the realtime thread.	
        /// </summary>	
        /// <param name="inputLockedParametersRef"> Array of input <see cref="SlimDX2.XAPO.LockforprocessParameters"/> structures.pInputLockedParameters may be NULL if InputLockedParameterCount is 0, otherwise itmust have InputLockedParameterCount elements.</param>
        /// <param name="outputLockedParametersRef"> Array of output <see cref="SlimDX2.XAPO.LockforprocessParameters"/> structures.pOutputLockedParameters may be NULL if OutputLockedParameterCount is 0, otherwise itmust have OutputLockedParameterCount elements.</param>
        /// <returns>No documentation.</returns>
        /// <unmanaged>HRESULT IXAPO::LockForProcess([None] UINT32 InputLockedParameterCount,[In, Buffer, Optional] const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS* pInputLockedParameters,[None] UINT32 OutputLockedParameterCount,[In, Buffer, Optional] const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS* pOutputLockedParameters)</unmanaged>
        Result LockForProcess(SlimDX2.XAPO.LockParameters[] inputLockedParameters, SlimDX2.XAPO.LockParameters[] outputLockedParameters);

        /// <summary>	
        /// Deallocates variables that were allocated with the {{LockForProcess}} method.	
        /// </summary>	
        /// <unmanaged>void IXAPO::UnlockForProcess()</unmanaged>
        void UnlockForProcess();

        /// <summary>	
        /// Runs the XAPO's digital signal processing (DSP) code on the given input and output buffers.	
        /// </summary>	
        /// <param name="inputProcessParameterCount">[in]          Number of elements in pInputProcessParameters. Note XAudio2 currently supports only one input stream and one output stream. </param>
        /// <param name="inputProcessParametersRef">[in]          Input array of  <see cref="SlimDX2.XAPO.ProcessBufferParameters"/> structures.         </param>
        /// <param name="outputProcessParameterCount">[in]          Number of elements in pOutputProcessParameters. Note XAudio2 currently supports only one input stream and one output stream. </param>
        /// <param name="outputProcessParametersRef">[in, out]          Output array of <see cref="SlimDX2.XAPO.ProcessBufferParameters"/> structures.  On input, the value of <see cref="SlimDX2.XAPO.ProcessBufferParameters"/>.ValidFrameCount indicates the number of frames  that the XAPO should write to the output buffer.  On output, the value of <see cref="SlimDX2.XAPO.ProcessBufferParameters"/>.ValidFrameCount indicates the actual number of frames written.         </param>
        /// <param name="isEnabled"> TRUE to process normally; FALSE to process thru.  See Remarks for additional information.         </param>
        /// <unmanaged>void IXAPO::Process([None] UINT32 InputProcessParameterCount,[In, Buffer, Optional] const XAPO_PROCESS_BUFFER_PARAMETERS* pInputProcessParameters,[None] UINT32 OutputProcessParameterCount,[InOut, Buffer, Optional] XAPO_PROCESS_BUFFER_PARAMETERS* pOutputProcessParameters,[None] BOOL IsEnabled)</unmanaged>
        void Process(SlimDX2.XAPO.BufferParameters[] inputProcessParameters, SlimDX2.XAPO.BufferParameters[] outputProcessParameters, bool isEnabled);

        /// <summary>	
        /// Returns the number of input frames required to generate the given number of output frames.	
        /// </summary>	
        /// <param name="outputFrameCount">The number of output frames desired.</param>
        /// <returns>No documentation.</returns>
        /// <unmanaged>UINT32 IXAPO::CalcInputFrames([None] UINT32 OutputFrameCount)</unmanaged>
        int CalcInputFrames(int outputFrameCount);

        /// <summary>	
        /// Returns the number of output frames that will be generated from a given number of input frames.	
        /// </summary>	
        /// <param name="inputFrameCount">The number of input frames.</param>
        /// <returns>No documentation.</returns>
        /// <unmanaged>UINT32 IXAPO::CalcOutputFrames([None] UINT32 InputFrameCount)</unmanaged>
        int CalcOutputFrames(int inputFrameCount);        
    }
}