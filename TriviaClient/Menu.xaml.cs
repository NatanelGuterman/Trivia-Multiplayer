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
    public sealed partial class Menu : Page
    {
        DispatcherTimer _dispatcherTimer;
        public Menu()
        {
            this.InitializeComponent();
            this.InitializeComponent();
            _dispatcherTimer = new DispatcherTimer();
            _dispatcherTimer.Tick += dispatcherTimer_Tick;
            _dispatcherTimer.Interval = TimeSpan.FromSeconds(1);
            _dispatcherTimer.Start();
        }

        private void dispatcherTimer_Tick(object sender, object e)
        {
            if (input.Visibility == Visibility.Visible)
                input.Visibility = Visibility.Collapsed;
            else
                input.Visibility = Visibility.Visible;
        }

        private void createRoomButton_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(CreateRoom));
        }

        private void joinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(JoinRoom));
        }

        private void input_GotFocus(object sender, RoutedEventArgs e)
        {
            _dispatcherTimer.Stop();
        }

        private void input_LostFocus(object sender, RoutedEventArgs e)
        {
            _dispatcherTimer.Start();
        }
    }
}
