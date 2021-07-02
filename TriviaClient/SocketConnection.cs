using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Popups;

namespace TriviaClient
{
    static class SocketConnection
    {
        public static TcpClient client;
        public static IPEndPoint serverEndPoint;
        public static NetworkStream clientStream;
        public static bool isConnected;

        public static void dialogUpdate(string title, string message)
        {
            var dialog = new MessageDialog(message);
            dialog.Title = title;
            _ = dialog.ShowAsync();
        }

        public static void ConnectSocket()
        {
            isConnected = true;
            client = new TcpClient();
            serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 2620);
            client.Connect(serverEndPoint);
            clientStream = client.GetStream();
        }

        public static void SendMessage(int messageCode, string message)
        {
            int i = 0;
            byte[] buffer = Serializer.MessageInBytes(messageCode, message);
            SocketConnection.clientStream.Write(buffer, 0, buffer.Length);
            SocketConnection.clientStream.Flush();

            buffer = new byte[1024];
            int bytesRead = SocketConnection.clientStream.Read(buffer, 0, 1024);

            Debug.WriteLine("Readed buffer: ");

            for (i = 0; i < bytesRead; i++)
                Debug.Write(buffer[i] + " ");
        }
    }
}
