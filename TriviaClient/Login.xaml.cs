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
        const int CODE_LOGIN = 201, CODE_SIGNUP = 202;
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
                SocketConnection.ConnectSocket();
            }

            try
            {
                SocketConnection.SendMessage(usernameTextBox.Text, passwordTextBox.Text, CODE_LOGIN, "{\"username\": \"" + usernameTextBox.Text + "\", \"password\": \"" + passwordTextBox.Text + "\"}");
            }
            catch (Exception ex)
            {
                SocketConnection.dialogUpdate("Error!", ex.Message);
            }
            Frame.Navigate(typeof(Menu));
        }
    }
}
