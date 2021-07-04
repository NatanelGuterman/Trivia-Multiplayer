using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.System;
using Windows.UI.Core;
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

        private void input_GotFocus(object sender, RoutedEventArgs e)
        {
            _dispatcherTimer.Stop();
        }

        private void input_LostFocus(object sender, RoutedEventArgs e)
        {
            _dispatcherTimer.Start();
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);
            usernameTextBlock.Text = (string)e.Parameter;
        }

        private void input_KeyDown(object sender, KeyRoutedEventArgs e)
        {
            if (e.Key == Windows.System.VirtualKey.Enter)
            {
                try
                {
                    switch (int.Parse(input.Text))
                    {
                        case 1:
                            {
                                Frame.Navigate(typeof(CreateRoom));
                                break;
                            }
                        case 2:
                            {
                                Frame.Navigate(typeof(JoinRoom));
                                break;
                            }
                        case 3:
                            {
                                //logout
                                break;
                            }
                        default:
                            {
                                var dialog = new MessageDialog("Invalid input!, only 1, 2 or 3!.");
                                dialog.Title = "Erroe";
                                _ = dialog.ShowAsync();
                                break;
                            }
                    }
                }catch(Exception ex)
                {
                    var dialog = new MessageDialog("Invalid input!, only 1, 2 or 3!.");
                    dialog.Title = "Error";
                    _ = dialog.ShowAsync();
                }

            }
        }
    }
}
