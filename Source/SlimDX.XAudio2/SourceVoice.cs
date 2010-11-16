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
using System;

namespace SlimDX.XAudio2
{
    public partial class SourceVoice
    {
        private VoiceCallBackImpl _voiceCallBackImpl;

        /// <summary>	
        /// Creates and configures a source voice.	
        /// </summary>	
        /// <param name="device">an instance of <see cref = "SlimDX.XAudio2.XAudio2" /></param>
        /// <param name="sourceFormat">[in]  Pointer to a <see cref="SlimDX.Multimedia.WaveFormat"/> structure. This structure contains the expected format for all audio buffers submitted to the source voice. XAudio2 supports voice types of PCM, xWMA, ADPCM (Windows only), and XMA (Xbox 360 only). XAudio2 supports the following PCM formats.   8-bit (unsigned) integer PCM   16-bit integer PCM (Optimal format for XAudio2)   20-bit integer PCM (either in 24 or 32 bit containers)   24-bit integer PCM (either in 24 or 32 bit containers)   32-bit integer PCM   32-bit float PCM (Preferred format after 16-bit integer)   The number of channels in a source voice must be less than or equal to XAUDIO2_MAX_AUDIO_CHANNELS. The sample rate of a source voice must be between XAUDIO2_MIN_SAMPLE_RATE and XAUDIO2_MAX_SAMPLE_RATE. Note Data formats such as XMA, {{ADPCM}}, and {{xWMA}} that require more information than provided by <see cref="SlimDX.Multimedia.WaveFormat"/> have a <see cref="SlimDX.Multimedia.WaveFormat"/> structure as the first member in their format structure. When creating a source voice with one of those formats cast the format's structure as a <see cref="SlimDX.Multimedia.WaveFormat"/> structure and use it as the value for pSourceFormat. </param>
        /// <param name="flags">[in]  Flags that specify the behavior of the source voice. A flag can be 0 or a combination of one or more of the following: ValueDescriptionXAUDIO2_VOICE_NOPITCHNo pitch control is available on the voice.?XAUDIO2_VOICE_NOSRCNo sample rate conversion is available on the voice, the voice's  outputs must have the same sample rate.Note The XAUDIO2_VOICE_NOSRC flag causes the voice to behave as though the XAUDIO2_VOICE_NOPITCH flag also is specified. ?XAUDIO2_VOICE_USEFILTERThe filter effect should be available on this voice.?XAUDIO2_VOICE_MUSICThe voice is used to play background music. The system automatically  can replace the voice with music selected by the user.? </param>
        /// <returns>No documentation.</returns>
        /// <unmanaged>HRESULT IXAudio2::CreateSourceVoice([Out] IXAudio2SourceVoice** ppSourceVoice,[In] const WAVEFORMATEX* pSourceFormat,[None] UINT32 Flags,[None] float MaxFrequencyRatio,[In, Optional] IXAudio2VoiceCallback* pCallback,[In, Optional] const XAUDIO2_VOICE_SENDS* pSendList,[In, Optional] const XAUDIO2_EFFECT_CHAIN* pEffectChain)</unmanaged>
        public SourceVoice(XAudio2 device, SlimDX.Multimedia.WaveFormat sourceFormat)
            : this(device, sourceFormat, VoiceFlags.None, 1.0f, null)
        {
        }

        /// <summary>	
        /// Creates and configures a source voice.	
        /// </summary>	
        /// <param name="device">an instance of <see cref = "SlimDX.XAudio2.XAudio2" /></param>
        /// <param name="sourceFormat">[in]  Pointer to a <see cref="SlimDX.Multimedia.WaveFormat"/> structure. This structure contains the expected format for all audio buffers submitted to the source voice. XAudio2 supports voice types of PCM, xWMA, ADPCM (Windows only), and XMA (Xbox 360 only). XAudio2 supports the following PCM formats.   8-bit (unsigned) integer PCM   16-bit integer PCM (Optimal format for XAudio2)   20-bit integer PCM (either in 24 or 32 bit containers)   24-bit integer PCM (either in 24 or 32 bit containers)   32-bit integer PCM   32-bit float PCM (Preferred format after 16-bit integer)   The number of channels in a source voice must be less than or equal to XAUDIO2_MAX_AUDIO_CHANNELS. The sample rate of a source voice must be between XAUDIO2_MIN_SAMPLE_RATE and XAUDIO2_MAX_SAMPLE_RATE. Note Data formats such as XMA, {{ADPCM}}, and {{xWMA}} that require more information than provided by <see cref="SlimDX.Multimedia.WaveFormat"/> have a <see cref="SlimDX.Multimedia.WaveFormat"/> structure as the first member in their format structure. When creating a source voice with one of those formats cast the format's structure as a <see cref="SlimDX.Multimedia.WaveFormat"/> structure and use it as the value for pSourceFormat. </param>
        /// <param name="flags">[in]  Flags that specify the behavior of the source voice. A flag can be 0 or a combination of one or more of the following: ValueDescriptionXAUDIO2_VOICE_NOPITCHNo pitch control is available on the voice.?XAUDIO2_VOICE_NOSRCNo sample rate conversion is available on the voice, the voice's  outputs must have the same sample rate.Note The XAUDIO2_VOICE_NOSRC flag causes the voice to behave as though the XAUDIO2_VOICE_NOPITCH flag also is specified. ?XAUDIO2_VOICE_USEFILTERThe filter effect should be available on this voice.?XAUDIO2_VOICE_MUSICThe voice is used to play background music. The system automatically  can replace the voice with music selected by the user.? </param>
        /// <returns>No documentation.</returns>
        /// <unmanaged>HRESULT IXAudio2::CreateSourceVoice([Out] IXAudio2SourceVoice** ppSourceVoice,[In] const WAVEFORMATEX* pSourceFormat,[None] UINT32 Flags,[None] float MaxFrequencyRatio,[In, Optional] IXAudio2VoiceCallback* pCallback,[In, Optional] const XAUDIO2_VOICE_SENDS* pSendList,[In, Optional] const XAUDIO2_EFFECT_CHAIN* pEffectChain)</unmanaged>
        public SourceVoice(XAudio2 device, SlimDX.Multimedia.WaveFormat sourceFormat, SlimDX.XAudio2.VoiceFlags flags)
            : this(device, sourceFormat, flags, 1.0f, null)
        {
        }

        /// <summary>	
        /// Creates and configures a source voice.	
        /// </summary>	
        /// <param name="device">an instance of <see cref = "SlimDX.XAudio2.XAudio2" /></param>
        /// <param name="sourceFormat">[in]  Pointer to a <see cref="SlimDX.Multimedia.WaveFormat"/> structure. This structure contains the expected format for all audio buffers submitted to the source voice. XAudio2 supports voice types of PCM, xWMA, ADPCM (Windows only), and XMA (Xbox 360 only). XAudio2 supports the following PCM formats.   8-bit (unsigned) integer PCM   16-bit integer PCM (Optimal format for XAudio2)   20-bit integer PCM (either in 24 or 32 bit containers)   24-bit integer PCM (either in 24 or 32 bit containers)   32-bit integer PCM   32-bit float PCM (Preferred format after 16-bit integer)   The number of channels in a source voice must be less than or equal to XAUDIO2_MAX_AUDIO_CHANNELS. The sample rate of a source voice must be between XAUDIO2_MIN_SAMPLE_RATE and XAUDIO2_MAX_SAMPLE_RATE. Note Data formats such as XMA, {{ADPCM}}, and {{xWMA}} that require more information than provided by <see cref="SlimDX.Multimedia.WaveFormat"/> have a <see cref="SlimDX.Multimedia.WaveFormat"/> structure as the first member in their format structure. When creating a source voice with one of those formats cast the format's structure as a <see cref="SlimDX.Multimedia.WaveFormat"/> structure and use it as the value for pSourceFormat. </param>
        /// <param name="flags">[in]  Flags that specify the behavior of the source voice. A flag can be 0 or a combination of one or more of the following: ValueDescriptionXAUDIO2_VOICE_NOPITCHNo pitch control is available on the voice.?XAUDIO2_VOICE_NOSRCNo sample rate conversion is available on the voice, the voice's  outputs must have the same sample rate.Note The XAUDIO2_VOICE_NOSRC flag causes the voice to behave as though the XAUDIO2_VOICE_NOPITCH flag also is specified. ?XAUDIO2_VOICE_USEFILTERThe filter effect should be available on this voice.?XAUDIO2_VOICE_MUSICThe voice is used to play background music. The system automatically  can replace the voice with music selected by the user.? </param>
        /// <param name="maxFrequencyRatio">[in]  Highest allowable frequency ratio that can be set on this voice. The value for this argument must be between XAUDIO2_MIN_FREQ_RATIO and XAUDIO2_MAX_FREQ_RATIO. Subsequent calls to <see cref="SlimDX.XAudio2.SourceVoice.SetFrequencyRatio"/> are clamped between XAUDIO2_MIN_FREQ_RATIO and MaxFrequencyRatio. The maximum value for this argument is defined as XAUDIO2_MAX_FREQ_RATIO, which allows pitch to be raised by up to 10 octaves. If MaxFrequencyRatio is less than 1.0, the voice will use that ratio immediately after being created (rather than the default of 1.0). Xbox 360  For XMA voices there is an additional restriction on the MaxFrequencyRatio argument and the voice's sample rate. The product of these two numbers cannot exceed XAUDIO2_MAX_RATIO_TIMES_RATE_XMA_MONO for one-channel voices or XAUDIO2_MAX_RATIO_TIMES_RATE_XMA_MULTICHANNEL for voices with any other number of channels. If the value specified for MaxFrequencyRatio is too high for the specified format, the call to CreateSourceVoice fails and produces a debug message.  Note XAudio2's memory usage can be reduced by using the lowest possible MaxFrequencyRatio value. </param>
        /// <returns>No documentation.</returns>
        /// <unmanaged>HRESULT IXAudio2::CreateSourceVoice([Out] IXAudio2SourceVoice** ppSourceVoice,[In] const WAVEFORMATEX* pSourceFormat,[None] UINT32 Flags,[None] float MaxFrequencyRatio,[In, Optional] IXAudio2VoiceCallback* pCallback,[In, Optional] const XAUDIO2_VOICE_SENDS* pSendList,[In, Optional] const XAUDIO2_EFFECT_CHAIN* pEffectChain)</unmanaged>
        public SourceVoice(XAudio2 device, SlimDX.Multimedia.WaveFormat sourceFormat, SlimDX.XAudio2.VoiceFlags flags, float maxFrequencyRatio)
            : this(device, sourceFormat, flags, maxFrequencyRatio, null)
        {
        }

        /// <summary>	
        /// Creates and configures a source voice.	
        /// </summary>	
        /// <param name="device">an instance of <see cref = "SlimDX.XAudio2.XAudio2" /></param>
        /// <param name="sourceFormat">[in]  Pointer to a <see cref="SlimDX.Multimedia.WaveFormat"/> structure. This structure contains the expected format for all audio buffers submitted to the source voice. XAudio2 supports voice types of PCM, xWMA, ADPCM (Windows only), and XMA (Xbox 360 only). XAudio2 supports the following PCM formats.   8-bit (unsigned) integer PCM   16-bit integer PCM (Optimal format for XAudio2)   20-bit integer PCM (either in 24 or 32 bit containers)   24-bit integer PCM (either in 24 or 32 bit containers)   32-bit integer PCM   32-bit float PCM (Preferred format after 16-bit integer)   The number of channels in a source voice must be less than or equal to XAUDIO2_MAX_AUDIO_CHANNELS. The sample rate of a source voice must be between XAUDIO2_MIN_SAMPLE_RATE and XAUDIO2_MAX_SAMPLE_RATE. Note Data formats such as XMA, {{ADPCM}}, and {{xWMA}} that require more information than provided by <see cref="SlimDX.Multimedia.WaveFormat"/> have a <see cref="SlimDX.Multimedia.WaveFormat"/> structure as the first member in their format structure. When creating a source voice with one of those formats cast the format's structure as a <see cref="SlimDX.Multimedia.WaveFormat"/> structure and use it as the value for pSourceFormat. </param>
        /// <param name="flags">[in]  Flags that specify the behavior of the source voice. A flag can be 0 or a combination of one or more of the following: ValueDescriptionXAUDIO2_VOICE_NOPITCHNo pitch control is available on the voice.?XAUDIO2_VOICE_NOSRCNo sample rate conversion is available on the voice, the voice's  outputs must have the same sample rate.Note The XAUDIO2_VOICE_NOSRC flag causes the voice to behave as though the XAUDIO2_VOICE_NOPITCH flag also is specified. ?XAUDIO2_VOICE_USEFILTERThe filter effect should be available on this voice.?XAUDIO2_VOICE_MUSICThe voice is used to play background music. The system automatically  can replace the voice with music selected by the user.? </param>
        /// <param name="maxFrequencyRatio">[in]  Highest allowable frequency ratio that can be set on this voice. The value for this argument must be between XAUDIO2_MIN_FREQ_RATIO and XAUDIO2_MAX_FREQ_RATIO. Subsequent calls to <see cref="SlimDX.XAudio2.SourceVoice.SetFrequencyRatio"/> are clamped between XAUDIO2_MIN_FREQ_RATIO and MaxFrequencyRatio. The maximum value for this argument is defined as XAUDIO2_MAX_FREQ_RATIO, which allows pitch to be raised by up to 10 octaves. If MaxFrequencyRatio is less than 1.0, the voice will use that ratio immediately after being created (rather than the default of 1.0). Xbox 360  For XMA voices there is an additional restriction on the MaxFrequencyRatio argument and the voice's sample rate. The product of these two numbers cannot exceed XAUDIO2_MAX_RATIO_TIMES_RATE_XMA_MONO for one-channel voices or XAUDIO2_MAX_RATIO_TIMES_RATE_XMA_MULTICHANNEL for voices with any other number of channels. If the value specified for MaxFrequencyRatio is too high for the specified format, the call to CreateSourceVoice fails and produces a debug message.  Note XAudio2's memory usage can be reduced by using the lowest possible MaxFrequencyRatio value. </param>
        /// <param name="callback">[in, optional]  Pointer to a client-provided callback interface, <see cref="SlimDX.XAudio2.VoiceCallback"/>. </param>
        /// <returns>No documentation.</returns>
        /// <unmanaged>HRESULT IXAudio2::CreateSourceVoice([Out] IXAudio2SourceVoice** ppSourceVoice,[In] const WAVEFORMATEX* pSourceFormat,[None] UINT32 Flags,[None] float MaxFrequencyRatio,[In, Optional] IXAudio2VoiceCallback* pCallback,[In, Optional] const XAUDIO2_VOICE_SENDS* pSendList,[In, Optional] const XAUDIO2_EFFECT_CHAIN* pEffectChain)</unmanaged>
        public SourceVoice(XAudio2 device, SlimDX.Multimedia.WaveFormat sourceFormat, SlimDX.XAudio2.VoiceFlags flags, float maxFrequencyRatio, VoiceCallback callback)
            : base(IntPtr.Zero)
        {
            SourceVoice temp;

            _voiceCallBackImpl = callback==null?null:new VoiceCallBackImpl(callback);
            device.CreateSourceVoice_(out temp, ref sourceFormat, flags, maxFrequencyRatio, callback==null?IntPtr.Zero:_voiceCallBackImpl.NativePointer, null, null);
            NativePointer = temp.NativePointer;
        }

        /// <summary>	
        /// Starts consumption and processing of audio by the voice. Delivers the result to any connected submix or mastering voices, or to the output device, with CommitNow changes.
        /// </summary>	
        /// <returns>No documentation.</returns>
        /// <unmanaged>HRESULT IXAudio2SourceVoice::Start([None] UINT32 Flags,[None] UINT32 OperationSet)</unmanaged>
        public SlimDX.Result Start()
        {
            return this.Start(0, 0);
        }

        /// <summary>	
        /// Starts consumption and processing of audio by the voice. Delivers the result to any connected submix or mastering voices, or to the output device.	
        /// </summary>	
        /// <param name="operationSet">[in]  Identifies this call as part of a deferred batch. See the {{XAudio2 Operation Sets}} overview for more information. </param>
        /// <returns>No documentation.</returns>
        /// <unmanaged>HRESULT IXAudio2SourceVoice::Start([None] UINT32 Flags,[None] UINT32 OperationSet)</unmanaged>
        public SlimDX.Result Start(int operationSet)
        {
            return this.Start(0, operationSet);
        }
    }
}