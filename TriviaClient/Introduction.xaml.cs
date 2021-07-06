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

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace TriviaClient
{
    public sealed partial class MainPage : Page
    {
        DispatcherTimer _dispatcherTimer;
        public MainPage()
        {
            this.InitializeComponent();
            _dispatcherTimer = new DispatcherTimer();
            _dispatcherTimer.Tick += dispatcherTimer_Tick;
            _dispatcherTimer.Interval = TimeSpan.FromMilliseconds(1);

        }

        private void dispatcherTimer_Tick(object sender, object e)
        {
            skipButton.Opacity += 0.009;
        }

        private void skipButton_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(Login));
        }

        private void skipButton_Loaded(object sender, RoutedEventArgs e)
        {
            _dispatcherTimer.Start();
        }

    }
}
