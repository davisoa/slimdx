using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using SlimDX;
using SlimDX.Windows;
using D3D10 = SlimDX.Direct3D10;
using DXGI = SlimDX.DXGI;

namespace MiniTri
{
    static class Program
    {
        static Form RenderForm;
        static Viewport ViewArea;
        static DXGI.SwapChain SwapChain;
        static D3D10.Device Device;
        static D3D10.Effect Effect;
        static D3D10.EffectTechnique Technique;
        static D3D10.EffectPass Pass;
        static D3D10.InputLayout Layout;
        static D3D10.Buffer Vertices;
        static D3D10.RenderTargetView RenderTarget;

        const int vertexSize = 32;
        const int vertexCount = 3;

        [STAThread]
        static void Main()
        {
            RenderForm = new Form();
            RenderForm.ClientSize = new Size(800, 600);
            RenderForm.Text = "SlimDX - MiniTri Direct3D 10 Sample";

            DXGI.SwapChainDescription swapChainDescription = new SlimDX.DXGI.SwapChainDescription();
            DXGI.ModeDescription modeDescription = new DXGI.ModeDescription();
            DXGI.SampleDescription sampleDescription = new DXGI.SampleDescription();

            modeDescription.Format = DXGI.Format.R8G8B8A8_UNorm;
            modeDescription.RefreshRate = new Rational(60, 1);
            modeDescription.Scaling = DXGI.DisplayModeScaling.Unspecified;
            modeDescription.ScanlineOrdering = DXGI.DisplayModeScanlineOrdering.Unspecified;
            modeDescription.Width = RenderForm.ClientRectangle.Width;
            modeDescription.Height = RenderForm.ClientRectangle.Height;

            sampleDescription.Count = 1;
            sampleDescription.Quality = 0;

            swapChainDescription.ModeDescription = modeDescription;
            swapChainDescription.SampleDescription = sampleDescription;
            swapChainDescription.BufferCount = 1;
            swapChainDescription.Flags = DXGI.SwapChainFlags.None;
            swapChainDescription.IsWindowed = true;
            swapChainDescription.OutputHandle = RenderForm.Handle;
            swapChainDescription.SwapEffect = DXGI.SwapEffect.Discard;
            swapChainDescription.Usage = DXGI.Usage.RenderTargetOutput;

            D3D10.Device.CreateWithSwapChain(null, D3D10.DriverType.Hardware, D3D10.DeviceCreationFlags.Debug, swapChainDescription, out Device, out SwapChain);

            using (D3D10.Texture2D resource = SwapChain.GetBuffer<D3D10.Texture2D>(0))
            {
                RenderTarget = new D3D10.RenderTargetView(Device, resource);
            }

            ViewArea = new Viewport();
            ViewArea.X = 0;
            ViewArea.Y = 0;
            ViewArea.Width = RenderForm.ClientRectangle.Width;
            ViewArea.Height = RenderForm.ClientRectangle.Height;
            ViewArea.MinZ = 0.0f;
            ViewArea.MaxZ = 1.0f;

            Device.Rasterizer.SetViewports(ViewArea);
            Device.OutputMerger.SetTargets(RenderTarget);

            Effect = D3D10.Effect.FromFile(Device, "MiniTri.fx", "fx_4_0", D3D10.ShaderFlags.None, D3D10.EffectFlags.None, null, null);
            Technique = Effect.GetTechniqueByIndex(0);
            Pass = Technique.GetPassByIndex(0);

            D3D10.InputElement[] inputElements = new SlimDX.Direct3D10.InputElement[]
			{
				new D3D10.InputElement("POSITION",0,DXGI.Format.R32G32B32A32_Float,0,0),
				new D3D10.InputElement("COLOR",0,DXGI.Format.R32G32B32A32_Float,16,0)
			};

            Layout = new D3D10.InputLayout(Device, inputElements, Pass.Description.Signature);

            DataStream stream = new DataStream(vertexCount * vertexSize, true, true);
            stream.Write(new Vector4(0.0f, 0.5f, 0.5f, 1.0f));
            stream.Write(new Vector4(1.0f, 0.0f, 0.0f, 1.0f));

            stream.Write(new Vector4(0.5f, -0.5f, 0.5f, 1.0f));
            stream.Write(new Vector4(0.0f, 1.0f, 0.0f, 1.0f));

            stream.Write(new Vector4(-0.5f, -0.5f, 0.5f, 1.0f));
            stream.Write(new Vector4(0.0f, 0.0f, 1.0f, 1.0f));

            // Important: when specifying initial buffer data like this, the buffer will
            // read from the current DataStream position; we must rewind the stream to 
            // the start of the data we just wrote.
            stream.Position = 0;

            D3D10.BufferDescription bufferDescription = new D3D10.BufferDescription();
            bufferDescription.BindFlags = D3D10.BindFlags.VertexBuffer;
            bufferDescription.CpuAccessFlags = D3D10.CpuAccessFlags.None;
            bufferDescription.OptionFlags = D3D10.ResourceOptionFlags.None;
            bufferDescription.SizeInBytes = vertexCount * vertexSize;
            bufferDescription.Usage = D3D10.ResourceUsage.Default;

            Vertices = new D3D10.Buffer(Device, stream, bufferDescription);
            stream.Close();

            Application.Idle += new EventHandler(Application_Idle);
            Application.Run(RenderForm);

            Device.ClearState();
            RenderTarget.Dispose();
            Effect.Dispose();
            Vertices.Dispose();
            Layout.Dispose();
            Device.Dispose();
            SwapChain.Dispose();
            RenderForm.Dispose();
        }

        static void Application_Idle(object sender, EventArgs e)
        {
            while (MessagePump.IsApplicationIdle)
            {
                Device.ClearRenderTargetView(RenderTarget, Color.Black);

                Device.InputAssembler.SetInputLayout(Layout);
                Device.InputAssembler.SetPrimitiveTopology(D3D10.PrimitiveTopology.TriangleList);
                Device.InputAssembler.SetVertexBuffers(0, new SlimDX.Direct3D10.VertexBufferBinding(Vertices, vertexSize, 0));

                for (int pass = 0; pass < Technique.Description.PassCount; ++pass)
                {
                    Pass.Apply();
                    Device.Draw(3, 0);
                }

                SwapChain.Present(0, DXGI.PresentFlags.None);
            }
        }
    }
}