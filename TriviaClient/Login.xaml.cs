using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

namespace TriviaClient
{
    public sealed partial class Login : Page
    {
        const int CODE_LOGIN = 201, CODE_SIGNUP = 202, BYTE = 8;
        public Login()
        {
            this.InitializeComponent();
        }

        private void moveToSignupButton_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(Signup));
        }

        private void login_Click(object sender, RoutedEventArgs e)
        {
            if(!SocketConnection.isConnected)
            {
                SocketConnection.isConnected = true;
                SocketConnection.client = new TcpClient();
                SocketConnection.serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 2620);
                SocketConnection.client.Connect(SocketConnection.serverEndPoint);
                SocketConnection.clientStream = SocketConnection.client.GetStream();
            }

            try
            {
                int i = 0;
                byte[] buffer = loginMessageInBytes();
                SocketConnection.clientStream.Write(buffer, 0, buffer.Length);
                SocketConnection.clientStream.Flush();

                buffer = new byte[1024];
                int bytesRead = SocketConnection.clientStream.Read(buffer, 0, 1024);

                Debug.WriteLine("Readed buffer: ");

                for (i = 0; i < bytesRead; i++)
                    Debug.Write(buffer[i] + " ");
            }
            catch (Exception ex)
            {
                SocketConnection.dialogUpdate("Error!", ex.Message);
            }
            Frame.Navigate(typeof(Menu));
        }

        private byte[] loginMessageInBytes()
        {
            string message = "";
            int i = 0;
            byte[] codeLengthBuffer, dataBuffer, finalBuffer, result, temp;

            message = "{\"username\": \"user1\", \"password\": \"1234\"}";
            codeLengthBuffer = new byte[5];
            codeLengthBuffer[0] = BitConverter.GetBytes(CODE_LOGIN)[0];

            temp = BitConverter.GetBytes(message.Length);
            Array.Reverse(temp);
            result = temp;

            for (i = 1; i <= result.Length; i++)
            {
                codeLengthBuffer[i] = result[i - 1];
            }

            dataBuffer = Encoding.ASCII.GetBytes(message);
            finalBuffer = new byte[codeLengthBuffer.Length + dataBuffer.Length];

            for (i = 0; i < codeLengthBuffer.Length; i++)
                finalBuffer[i] = codeLengthBuffer[i];

            for (i = 0; i < dataBuffer.Length; i++)
                finalBuffer[i + codeLengthBuffer.Length] = dataBuffer[i];

            Debug.WriteLine("\nFinal buffer before sending: ");
            for (i = 0; i < finalBuffer.Length; i++)
                Debug.Write(finalBuffer[i] + " ");

            return finalBuffer;
        }
    }
}
