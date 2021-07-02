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
            string message = "", binaryMessage = "";
            int i = 0;
            byte[] buffer;

            message = "{\"username\": \"user1\", \"password\": \"1234\"}";
            binaryMessage = StringToBinaryString(Encoding.UTF8, message);
            buffer = new byte[5 * BYTE + binaryMessage.Length];

            for (i = 0; i < binaryMessage.Length; i++)
            {
                buffer[i + 5 * BYTE] = (byte)int.Parse(binaryMessage[i].ToString());
            }

            binaryMessage = IntToBinaryString(binaryMessage.Length, 32);
            for (i = 0; i < BYTE * 4; i++)
            {
                buffer[i + BYTE] = (byte)int.Parse(binaryMessage[i].ToString());
            }

            binaryMessage = IntToBinaryString(CODE_LOGIN, 8);
            for (i = 0; i < BYTE; i++)
            {
                buffer[i] = (byte)int.Parse(binaryMessage[i].ToString());
            }

            for (i = 0; i < buffer.Length; i++)
            {
                Debug.Write(buffer[i]);
                if ((i + 1) % 8 == 0)
                    Debug.Write(" ");
            }

            return buffer;
        }

        private string StringToBinaryString(Encoding encoding, string text)
        {
            return string.Join("", encoding.GetBytes(text).Select(n => Convert.ToString(n, 2).PadLeft(8, '0')));
        }

        private static string IntToBinaryString(int x, int size)
        {
            if (size == 0)
                size = 32;

            char[] bits = new char[size];
            int i = 0;
            char temp = ' ';

            for (i = 0; i < size; i++)
                bits[i] = '0';
            i = 0;

            while (x != 0)
            {
                bits[i++] = (x & 1) == 1 ? '1' : '0';
                x >>= 1;
            }

            if (size == 32)
            {
                for (i = 0; i < size / 2; i++)
                {
                    temp = bits[i];
                    bits[i] = bits[size - i - 1];
                    bits[size - i - 1] = temp;
                }
            }
            else
            {
                Array.Reverse(bits, 0, i);
            }
            return new string(bits);
        }
    }
}
