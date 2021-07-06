using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
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
    public sealed partial class Signup : Page
    {
        const int CODE_SIGNUP = 202;
        public Signup()
        {
            this.InitializeComponent();
        }

        private void moveToLoginButton_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(Login));
        }

        private void signup_Click(object sender, RoutedEventArgs e)
        {
            if (!SocketConnection.isConnected)
            {
                SocketConnection.ConnectSocket();
            }

            try
            {
                SocketConnection.SendMessage(CODE_SIGNUP, "{\"username\": \"" + usernameTextBox.Text + "\", \"password\": \"" + passwordTextBox.Text + "\", \"mail\": \"" + emailTextBox.Text + "\"}");
                if (Deserializer.StatusDeserializer(SocketConnection.ReadMessage()).status == 1)
                {
                    Global.username = usernameTextBox.Text;
                    Frame.Navigate(typeof(Menu), usernameTextBox.Text);
                }
                else
                {
                    SocketConnection.dialogUpdate("Error!", "Problem in sign in");
                }
            }
            catch (Exception ex)
            {
                SocketConnection.dialogUpdate("Error!", ex.Message);
            }
        }
    }
}
