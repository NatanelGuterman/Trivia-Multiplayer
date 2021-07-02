using System;
using System.Collections.Generic;
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
    }
}
