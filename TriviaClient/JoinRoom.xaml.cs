using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI;
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
    public sealed partial class JoinRoom : Page
    {
        public JoinRoom()
        {
            this.InitializeComponent(); 
        }

        private void refreshButton_Click(object sender, RoutedEventArgs e)
        {
            // Call to the functions that will show on the screen the available rooms again.
        }

        private void moveTCreateRoomButton_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(CreateRoom));
        }
    }
}
